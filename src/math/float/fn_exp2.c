
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Exp2, exp2)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_EXP2(BITS) \
t_f##BITS	F##BITS##_Exp2(t_f##BITS x) \
{ \
	return (F##BITS##_Pow(2, x)); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_EXP2(16)
#endif
DEFINEFUNC_FLOAT_EXP2(32)

DEFINEFUNC_FLOAT_EXP2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EXP2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EXP2(128)
#endif



#else



/*
EXP2F_TABLE_BITS = 5
EXP2F_POLY_ORDER = 3

ULP error: 0.502 (nearest rounding.)
Relative error: 1.69 * 2^-34 in [-1/64, 1/64] (before rounding.)
Wrong count: 168353 (all nearest rounding wrong results with fma.)
Non-nearest ULP error: 1 (rounded ULP error)
*/

/*
Handle cases that may overflow or underflow when computing the result that
is scale*(1+TMP) without intermediate rounding.
The bit representation of scale is in SBITS, however it has a computed exponent that may have
overflown into the sign bit so that needs to be adjusted before using it as a t_f64.
(t_s32)KI is the k used in the argument reduction and exponent adjustment of scale,
positive k here means the result may overflow and negative k means the result may underflow.
*/
static inline
t_f64	specialcase(t_f64 tmp, t_u64 sbits, t_u64 ki)
{
	t_f64 scale, y;

	if ((ki & 0x80000000) == 0)
	{
		/* k > 0, the exponent of scale might have overflowed by 1. */
		sbits -= 1ull << 52;
		scale = AS_F64(sbits);
		y = 2 * (scale + scale * tmp);
		return (y);
	}
	/* k < 0, need special care in the subnormal range. */
	sbits += 1022ull << 52;
	scale = AS_F64(sbits);
	y = scale + scale * tmp;
	if (y < 1.0)
	{
		/*
		Round y to the right precision before scaling it into the subnormal
		range to avoid t_f64 rounding that can cause 0.5+E/2 ulp error where
		E is the worst-case ulp error outside the subnormal range.  So this
		is only useful if the goal is better than 1 ulp worst-case error.
		*/
		t_f64 hi, lo;
		lo = scale - y + scale * tmp;
		hi = 1.0 + y;
		lo = 1.0 - hi + y + lo;
		y = (hi + lo) - 1.0;
		/* Avoid -0.0 with downward rounding. */
		if (WANT_ROUNDING && y == 0.0)
			y = 0.0;
		/* The underflow exception needs to be signaled explicitly. */
		/* fp_force_eval(fp_barrier(0x1p-1022) * 0x1p-1022); */
	}
	y = 0x1p-1022 * y;
	return (y);
}


/*! Top 12 bits of a t_f32 (sign and exponent bits). */
static inline
t_u32	top12_f32(t_f32 x)
{
	return AS_U32(x) >> 20;
}
/*! Top 12 bits of a t_f64 (sign and exponent bits). */
static inline
t_u32	top12_f64(t_f64 x)
{
	return AS_U64(x) >> 52;
}

t_f32	F32_Exp2(t_f32 x)
{
	t_u32 abstop;
	t_u64 ki, t;
	t_f64 kd, xd, z, r, r2, y, s;
	/* Filter out exceptional cases. */
	xd = (t_f64)x;
	abstop = top12_f32(x) & 0x7ff;
	if (predict_false(abstop >= top12_f32(128.0f))) /* |x| >= 128 or x is nan. */
	{
		if (AS_U32(x) == AS_U32((t_f32)-INFINITY))
			return 0.0f;
		if (abstop >= top12_f32(INFINITY))
			return x + x;
		if (x > 0.0f) //TODO: CCCERROR((x > 0.0f), ERROR_MATHROUNDING, "value overflowed to inf")?
			return __math_oflowf(x);
		if (x <= -150.0f) //TODO: CCCERROR((x <= -150.0f), ERROR_MATHROUNDING, "value underflowed to 0")?
			return __math_uflowf(x);
	}
	/* x = k/N + r with r in [-1/(2N), 1/(2N)] and int k. */
	kd = xd + __data_exp_f32.shift_scaled;
	ki = AS_U64(kd);
	kd -= __data_exp_f32.shift_scaled; /* k/N for int k. */
	r = xd - kd;
	/* exp2(x) = 2^(k/N) * 2^r ~= s * (C0*r^3 + C1*r^2 + C2*r + 1) */
	t = __data_exp_f32.table[ki % N_EXP_F32];
	t += ki << (F64_MANTISSA_BITS - TABLEBITS_EXP_F32);
	s = AS_F64(t);
	z = __data_exp_f32.poly[0] * r + __data_exp_f32.poly[1];
	r2 = r * r;
	y = __data_exp_f32.poly[2] * r + 1;
	y = z * r2 + y;
	y = y * s;
	return (t_f32)(y);
}

t_f64	F64_Exp2(t_f64 x)
{
	t_u32 abstop;
	t_u64 ki, idx, top, sbits;
	t_f64 kd, r, r2, scale, tail, tmp;
	/* Filter out exceptional cases. */
	abstop = top12_f64(x) & 0x7ff;
	if (predict_false(abstop - top12_f64(0x1p-54) >= top12_f64(512.0) - top12_f64(0x1p-54)))
	{
		if (abstop - top12_f64(0x1p-54) >= 0x80000000) /* Avoid spurious underflow for tiny x. */
			return WANT_ROUNDING ? 1.0 + x : 1.0; /* Note: 0 is common input. */
		if (abstop >= top12_f64(1024.0))
		{
			if (AS_U64(x) == AS_U64(-INFINITY))
				return 0.0;
			if (abstop >= top12_f64(INFINITY))
				return 1.0 + x;
			if (!(AS_U64(x) >> 63)) //TODO: CCCERROR((!(AS_U64(x) >> 63)), ERROR_MATHROUNDING, "value overflowed to inf")?
				return __math_oflowf(x);
			if (AS_U64(x) >= AS_U64(-1075.0)) //TODO: CCCERROR((AS_U64(x) >= AS_U64(-1075.0)), ERROR_MATHROUNDING, "value underflowed to 0")?
				return __math_uflowf(x);
		}
		if (2 * AS_U64(x) > 2 * AS_U64(928.0)) /* Large x is special cased below. */
			abstop = 0;
	}
	/* exp2(x) = 2^(k/N) * 2^r, with 2^r in [2^(-1/2N),2^(1/2N)]. */
	/* x = k/N + r, with int k and r in [-1/2N, 1/2N]. */
	kd = (x + __data_exp_f64.exp_shift);
	ki = AS_U64(kd); /* k. */
	kd -= __data_exp_f64.exp_shift; /* k/N for int k. */
	r = x - kd;
	/* 2^(k/N) ~= scale * (1 + tail). */
	idx = 2 * (ki % N_EXP_F64);
	top = ki << (F64_MANTISSA_BITS - TABLEBITS_EXP_F64);
	tail = AS_F64(__data_exp_f64.table[idx]);
	/* This is only a valid scale when -1023*N < k < 1024*N. */
	sbits = __data_exp_f64.table[idx + 1] + top;
	/* exp2(x) = 2^(k/N) * 2^r ~= scale + scale * (tail + 2^r - 1). */
	/* Evaluation is optimized assuming superscalar pipelined execution. */
	r2 = r * r;
	/* Without fma the worst case error is 0.5/N ulp larger. */
	/* Worst case error is less than 0.5+0.86/N+(abs poly error * 2^53) ulp. */
	tmp = tail + r * __data_exp_f64.exp_poly[0] + r2 *
		(__data_exp_f64.exp_poly[1] + r * __data_exp_f64.exp_poly[2]) + r2 * r2 *
		(__data_exp_f64.exp_poly[3] + r * __data_exp_f64.exp_poly[4]);
	if (predict_false(abstop == 0))
		return specialcase(tmp, sbits, ki);
	scale = AS_F64(sbits);
	/* Note: tmp == 0 or |tmp| > 2^-65 and scale > 2^-928, so there
	   is no spurious underflow here even without fma. */
	return (scale + scale * tmp);
}

#if LIBCONFIG_USE_FLOAT80
/*
**	exp2l(x): compute the base 2 exponential of x
**
**	Accuracy: Peak error < 0.511 ulp.
**
**	Method: (equally-spaced tables)
**
**	Reduce x:
**		x = 2**k + y, for integer k and |y| <= 1/2.
**		Thus we have exp2l(x) = 2**k * exp2(y).
**
**	Reduce y:
**		y = i/N + z for integer i near y * N.
**		Thus we have exp2(y) = exp2(i/N) * exp2(z),
**		with |z| <= 2**-(EXP_TABLE_BITS+1).
**
**	We compute exp2(i/N) via table lookup and exp2(z) via a
**	degree-6 minimax polynomial with maximum error under 2**-69.
**	The table entries each have 104 bits of accuracy, encoded as
**	a pair of t_f64 precision values.
*/
t_f80	F80_Exp2(t_f80 x)
{
	union ldshape u = {x};
	t_sint e = u.i.se & 0x7fff;
	t_f80 r, z;
	t_u32 i0;
	u_cast_f32 k;
	/* Filter out exceptional cases. */
	if (e >= 0x3fff + 13) /* |x| >= 8192 or x is NaN */
	{
		if (u.i.se >= 0x3fff + 14 && u.i.se >> 15 == 0) /* overflow */
			return x * 0x1p16383L;
		if (e == 0x7fff) /* -inf or -nan */
			return -1/x;
		if (x < -16382)
		{
			if (x <= -16446 || x - 0x1p63 + 0x1p63 != x) /* underflow */
				FORCE_EVAL((t_f32)(-0x1p-149/x));
			if (x <= -16446)
				return 0;
		}
	}
	else if (e < 0x3fff - 64)
	{
		return 1 + x;
	}
	/*
	** Reduce x, computing z, i0, and k. The low bits of x + redux
	** contain the 16-bit integer part of the exponent (k) followed by
	** EXP_TABLE_BITS fractional bits (i0). We use bit tricks to extract these
	** as integers, then set z to the remainder.
	**
	** Example: Suppose x is 0xabc.123456p0 and EXP_TABLE_BITS is 8.
	** Then the low-order word of x + redux is 0x000abc12,
	** We split this into k = 0xabc and i0 = 0x12 (adjusted to
	** index into the table), then we compute z = 0x0.003456p0.
	*/
	u.f = x + __data_exp_f80.redux;
	i0 = u.i.m + N_EXP_F80 / 2;
	k.as_u = i0 / N_EXP_F80 * N_EXP_F80;
	k.as_s /= N_EXP_F80;
	i0 %= N_EXP_F80;
	u.f -= __data_exp_f80.redux;
	z = x - u.f;
	/* Compute r = exp2l(y) = exp2lt[i0] * p(z). */
	t_f80 tbl_hi = table[2*i0];
	t_f80 tbl_lo = table[2*i0 + 1];
	/* XXX This gives > 1 ulp errors outside of FE_TONEAREST mode */
	r = tbl_lo+(tbl_hi+tbl_lo)*
		z*(__data_exp_f80.poly[1]+
		z*(__data_exp_f80.poly[2]+
		z*(__data_exp_f80.poly[3]+
		z*(__data_exp_f80.poly[4]+
		z*(__data_exp_f80.poly[5]+
		z*(__data_exp_f80.poly[6])
		)))))+tbl_hi;
	return F80_From(r, k.as_s);
}
#endif

#if LIBCONFIG_USE_FLOAT128
/*
**	exp2l(x): compute the base 2 exponential of x
**
**	Accuracy: Peak error < 0.502 ulp.
**
**	Method: (accurate tables)
**
**	Reduce x:
**		x = 2**k + y, for integer k and |y| <= 1/2.
**		Thus we have exp2(x) = 2**k * exp2(y).
**
**	Reduce y:
**		y = i/N + z - eps[i] for integer i near y * N.
**		Thus we have exp2(y) = exp2(i/N) * exp2(z - eps[i]),
**		with |z - eps[i]| <= 2**-8 + 2**-98 for the table used.
**
**	We compute exp2(i/N) via table lookup and exp2(z - eps[i]) via
**	a degree-10 minimax polynomial with maximum error under 2**-120.
**	The values in exp2t[] and eps[] are chosen such that
**	exp2t[i] = exp2(i/N + eps[i]), and eps[i] is a small offset such
**	that exp2t[i] is accurate to 2**-122.
**
**	Note that the range of i is +-N/2, so we actually index the tables
**	by i0 = i + N/2.
**
**	This method is due to Gal, with many details due to Gal and Bachelis:
**
**	Gal, S. and Bachelis, B.  An Accurate Elementary Mathematical Library
**	for the IEEE Floating Point Standard.  TOMS 17(1), 26-46 (1991).
*/
t_f128	F128_Exp2(t_f128 x)
{
	union ldshape u = {x};
	t_sint e = u.i.se & 0x7fff;
	t_f128 r, z, t;
	t_u32 i0;
	u_cast_f32 k;
	/* Filter out exceptional cases. */
	if (e >= 0x3fff + 14) /* |x| >= 16384 or x is NaN */
	{
		if (u.i.se >= 0x3fff + 15 && u.i.se >> 15 == 0) /* overflow */
			return x * 0x1p16383L;
		if (e == 0x7fff) /* -inf or -nan */
			return -1/x;
		if (x < -16382)
		{
			if (x <= -16495 || x - 0x1p112 + 0x1p112 != x) /* underflow */
				FORCE_EVAL((t_f32)(-0x1p-149/x));
			if (x <= -16446)
				return 0;
		}
	}
	else if (e < 0x3fff - 114)
	{
		return 1 + x;
	}
	/*
	** Reduce x, computing z, i0, and k. The low bits of x + redux
	** contain the 16-bit integer part of the exponent (k) followed by
	** EXP_TABLE_BITS fractional bits (i0). We use bit tricks to extract these
	** as integers, then set z to the remainder.
	**
	** Example: Suppose x is 0xabc.123456p0 and EXP_TABLE_BITS is 8.
	** Then the low-order word of x + redux is 0x000abc12,
	** We split this into k = 0xabc and i0 = 0x12 (adjusted to
	** index into the table), then we compute z = 0x0.003456p0.
	*/
	u.f = x + __data_exp_f128.redux;
	i0 = u.i2.lo + N_EXP_F128 / 2;
	k.as_u = i0 / N_EXP_F128 * N_EXP_F128;
	k.as_s /= N_EXP_F128;
	i0 %= N_EXP_F128;
	u.f -= __data_exp_f128.redux;
	z = x - u.f;
	/* Compute r = exp2(y) = exp2t[i0] * p(z - eps[i]). */
	t = __data_exp_f128.table[i0];
	z -= __data_exp_f128.eps[i0];
	r = t+t*
		z*(__data_exp_f128.poly[1]+
		z*(__data_exp_f128.poly[2]+
		z*(__data_exp_f128.poly[3]+
		z*(__data_exp_f128.poly[4]+
		z*(__data_exp_f128.poly[5]+
		z*(__data_exp_f128.poly[6]+
		z*(__data_exp_f128.poly[7]+
		z*(__data_exp_f128.poly[8]+
		z*(__data_exp_f128.poly[9]+
		z*(__data_exp_f128.poly[10])
		)))))))));
	return F128_From(r, k.as_s);
}
#endif


/*
DEFINEFUNC_FLOAT_EXP2(32)
DEFINEFUNC_FLOAT_EXP2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EXP2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EXP2(128)
#endif
*/
#endif
