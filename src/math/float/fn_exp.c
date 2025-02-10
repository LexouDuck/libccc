
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Exp, exp)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_EXP(BITS) \
t_f##BITS		F##BITS##_Exp(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x < -10.) \
		return (0.); \
	t_f##BITS result = 1.; \
	result *= (x + 8.); \
	result *= (x + 56.); \
	result *= (x + 336.); \
	result *= (x + 1680.); \
	result *= (x + 6720.); \
	result *= (x + 20160.); \
	result *= (x + 40320.); \
	result *= (x + 40320.); \
	result *= 2.4801587301e-5; \
	return (result); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_EXP(16)
#endif
DEFINEFUNC_FLOAT_EXP(32)

DEFINEFUNC_FLOAT_EXP(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EXP(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EXP(128)
#endif

#if 0 // crazy fast approximate method TODO: fix infinite loop ??
	u_float_cast result = { x };

	result.value_int = (1512775 * result.value_int + 1072632447);
	result.value_int <<= (BITS / 2);
	return (result.value_float);
#endif

#if 0 // precise but slow iterative method
	t_f##BITS		result;
	t_f##BITS		result_prev;
	t_f##BITS		acc_x;
	t_f##BITS		acc_i;
	t_u32		i;

	if (x < 100.)
		return (0.);
	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	result_prev = 0.;
	while (F##BITS##_Abs(result - result_prev) > FLOAT_APPROX)
	{
		result_prev = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
#endif



#else



/* Top 12 bits of a t_f64 (sign and exponent bits). */
static inline
t_u32	top12bits_f32(t_f32 x)
{
	return AS_U32(x) >> 20;
}

static inline
t_u32	top12bits_f64(t_f64 x)
{
	return AS_U64(x) >> 52;
}

/*!
**	Handle cases that may overflow or underflow when computing the result that is scale*(1+TMP) without intermediate rounding.
**	The bit representation of scale is in SBITS, however it has a computed exponent
**	that may have overflown into the sign bit so that needs to be adjusted before using it as a t_f64.
**	(t_s32)KI is the k used in the argument reduction and exponent adjustment of scale,
**	positive k here means the result may overflow and negative k means the result may underflow.
*/
static inline
t_f64	specialcase(t_f64 tmp, t_u64 sbits, t_u64 ki)
{
	t_f64 scale, y;

	if ((ki & 0x80000000) == 0)
	{	/* k > 0, the exponent of scale might have overflowed by <= 460. */
		sbits -= 1009ull << 52;
		scale = AS_F64(sbits);
		y = 0x1p1009 * (scale + scale * tmp);
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
		E is the worst-case ulp error outside the subnormal range.
		So this is only useful if the goal is better than 1 ulp worst-case error.
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



t_f32	F32_Exp(t_f32 x)
{
	t_u32 abstop;
	t_u64 ki, t;
	t_f64 kd, xd, z, r, r2, y, s;
	/* Filter out exceptional cases. */
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)
		return (NAN);
	xd = (t_f64)x;
	abstop = top12bits_f32(x) & 0x7ff;
	if (predict_false(abstop >= top12bits_f32(88.0f))) /* |x| >= 88 or x is nan. */
	{
		if (AS_U32(x) == AS_U32((t_f32)-INFINITY))
			return 0.0f;
		if (abstop >= top12bits_f32(INFINITY))
			return x + x;
		if (x > +0x1.62E42Ep6f) /* x > log(0x1p128) ~= 88.72 */
			return __math_oflowf(x);
		if (x < -0x1.9FE368p6f) /* x < log(0x1p-150) ~= -103.97 */
			return __math_uflowf(x);
	}
	/* x*N/Ln2 = k + r with r in [-1/2, 1/2] and int k. */
	z = __data_exp_f32.invln2_scaled * xd;
	/*
	Round and convert z to int, the result is in [-150*N, 128*N] and ideally ties-to-even rule is used,
	otherwise the magnitude of r can be bigger which gives larger approximation error.
	*/
#if TOINT_INTRINSICS
	kd = roundtoint(z);
	ki = converttoint(z);
#else
	kd = (z + __data_exp_f32.shift);
	ki = AS_U64(kd);
	kd -= __data_exp_f32.shift;
#endif
	r = z - kd;
	/* exp(x) = 2^(k/N) * 2^(r/N) ~= s * (C0*r^3 + C1*r^2 + C2*r + 1) */
	t = __data_exp_f32.table[ki % N_EXP_F32];
	t += ki << (F64_MANTISSA_BITS - TABLEBITS_EXP_F32);
	s = AS_F64(t);
	z = __data_exp_f32.poly_scaled[0] * r + __data_exp_f32.poly_scaled[1];
	r2 = r * r;
	y = __data_exp_f32.poly_scaled[2] * r + 1;
	y = z * r2 + y;
	y = y * s;
	return (t_f32)(y);
}

t_f64	F64_Exp(t_f64 x)
{
	t_u32 abstop;
	t_u64 ki, idx, top, sbits;
	t_f64 kd, z, r, r2, scale, tail, tmp;
	/* Filter out exceptional cases. */
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)
		return (NAN);
	abstop = top12bits_f64(x) & 0x7ff;
	if (predict_false(abstop - top12bits_f64(0x1p-54) >= top12bits_f64(512.0) - top12bits_f64(0x1p-54)))
	{
		if (abstop - top12bits_f64(0x1p-54) >= 0x80000000) /* Avoid spurious underflow for tiny x. */
			return WANT_ROUNDING ? 1.0 + x : 1.0; /* Note: 0 is common input. */
		if (abstop >= top12bits_f64(1024.0))
		{
			if (AS_U64(x) == AS_U64(-INFINITY))
				return 0.0;
			if (abstop >= top12bits_f64(INFINITY))
				return 1.0 + x;
			if (AS_U64(x) >> 63)
				return __math_uflow(x);
			else
				return __math_oflow(x);
		}
		/* Large x is special cased below. */
		abstop = 0;
	}
	/* exp(x) = 2^(k/N) * exp(r), with exp(r) in [2^(-1/2N),2^(1/2N)]. */
	/* x = ln2/N*k + r, with int k and r in [-ln2/2N, ln2/2N]. */
	z = __data_exp_f64.invln2N * x;
#if TOINT_INTRINSICS
	kd = roundtoint(z);
	ki = converttoint(z);
#elif EXP_USE_TOINT_NARROW
	/* z - kd is in [-0.5-2^-16, 0.5] in all rounding modes. */
	kd = (z + __data_exp_f64.shift);
	ki = AS_U64(kd) >> 16;
	kd = (t_f64)(t_s32)ki;
#else
	/* z - kd is in [-1, 1] in non-nearest rounding modes. */
	kd = (z + __data_exp_f64.shift);
	ki = AS_U64(kd);
	kd -= __data_exp_f64.shift;
#endif
	r = x + kd * __data_exp_f64.negln2hiN + kd * __data_exp_f64.negln2loN;
	/* 2^(k/N) ~= scale * (1 + tail). */
	idx = 2 * (ki % N_EXP_F64);
	top = ki << (F64_MANTISSA_BITS - TABLEBITS_EXP_F64);
	tail = AS_F64(__data_exp_f64.table[idx]);
	/* This is only a valid scale when -1023*N < k < 1024*N. */
	sbits = __data_exp_f64.table[idx + 1] + top;
	/* exp(x) = 2^(k/N) * exp(r) ~= scale + scale * (tail + exp(r) - 1). */
	/* Evaluation is optimized assuming superscalar pipelined execution. */
	r2 = r * r;
	/* Without fma the worst case error is 0.25/N ulp larger. */
	/* Worst case error is less than 0.5+1.11/N+(abs poly error * 2^53) ulp. */
	tmp = tail + r + r2 * (
		__data_exp_f64.poly[0] + r * 
		__data_exp_f64.poly[1]) + r2 * r2 * (
		__data_exp_f64.poly[2] + r * 
		__data_exp_f64.poly[3]);
	if (predict_false(abstop == 0))
		return specialcase(tmp, sbits, ki);
	scale = AS_F64(sbits);
	/* Note: tmp == 0 or |tmp| > 2^-200 and scale > 2^-739, so there
	   is no spurious underflow here even without fma. */
	return (t_f64)(scale + scale * tmp);
}

#define DEFINEFUNC_FLOAT_EXP(BITS) \
t_f##BITS	F##BITS##_Exp(t_f##BITS x) \
{ \
	t_f##BITS px, x2; \
	int k; \
 \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x > 11356.5234062941439488L) /* x > ln(2^16384 - 0.5) */ \
		return x * 0x1p16383L; \
	if (x < -11399.4985314888605581L) /* x < ln(2^-16446) */ \
		return -0x1p-16445L / x; \
	/* Express e**x = e**f 2**k = e**(f + k ln(2)) */ \
	px = F##BITS##_Floor(__data_exp_f##BITS.log2e * x + 0.5); \
	k = px; \
	x -= px * __data_exp_f##BITS.ln2hi; \
	x -= px * __data_exp_f##BITS.ln2lo; \
	/* rational approximation of the fractional part: e**x =  1 + 2x P(x**2)/(Q(x**2) - x P(x**2)) */ \
	x2 = x * x; \
	px = x * (__polynomial(x2, __data_exp_f##BITS.exp_poly_p, 2)); \
	x = px / (__polynomial(x2, __data_exp_f##BITS.exp_poly_q, 3) - px); \
	x = 1.0 + 2.0 * x; \
	return F##BITS##_From(x, k); \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_EXP(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_EXP(128)
#endif



#endif
