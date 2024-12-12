
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(Pow, pow)
#elif 1 // LIBCONFIG_USE_CCC_MATH

#if 1
// crazy approximate method
#define DEFINEFUNC_MATH_FLOAT_POW(BITS, HALF, MAGIC) \
t_f##BITS	F##BITS##_Pow(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
    union { t_f##BITS f; t_s##HALF i[2]; } u = { x }; \
    u.i[1] = (t_s##HALF)(y * (t_f##BITS)(u.i[1] - MAGIC) + MAGIC); \
    u.i[0] = 0; \
    return u.f; \
} \

DEFINEFUNC_MATH_FLOAT_POW(32, 16, 1064866816)
DEFINEFUNC_MATH_FLOAT_POW(64, 32, 1072632447)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_MATH_FLOAT_POW(80, 40, ?)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_MATH_FLOAT_POW(128, 64, ?)
#endif

#endif

#if 0
	u_float_cast result;
	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.value_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
#endif

// lame exp*ln method
#if 0 
	return (F##BITS##_Exp(y * F##BITS##_Ln(x)));
#endif



#else




/*
POWF_LOG2_POLY_ORDER = 5
EXP2F_TABLE_BITS = 5

ULP error: 0.82 (~ 0.5 + relerr*2^24)
relerr: 1.27 * 2^-26 (Relative error ~= 128*Ln2*relerr_log2 + relerr_exp2)
relerr_log2: 1.83 * 2^-33 (Relative error of logx.)
relerr_exp2: 1.69 * 2^-34 (Relative error of exp2(ylogx).)
*/

#define N (1 << POWF_LOG2_TABLE_BITS)
#define T __powf_log2_data.tab
#define A __powf_log2_data.poly
#define OFF 0x3f330000

/* Subnormal input is normalized so ix has negative biased exponent.
   Output is multiplied by N (POWF_SCALE) if TOINT_INTRINICS is set.  */
static inline
t_f64 log2_inline(uint32_t ix)
{
	t_f64 z, r, r2, r4, p, q, y, y0, invc, logc;
	uint32_t iz, top, tmp;
	int k, i;

	/* x = 2^k z; where z is in range [OFF,2*OFF] and exact.
	   The range is split into N subintervals.
	   The ith subinterval contains z and c is near its center.  */
	tmp = ix - OFF;
	i = (tmp >> (23 - POWF_LOG2_TABLE_BITS)) % N;
	top = tmp & 0xff800000;
	iz = ix - top;
	k = (int32_t)top >> (23 - POWF_SCALE_BITS); /* arithmetic shift */
	invc = T[i].invc;
	logc = T[i].logc;
	z = (t_f64)asfloat(iz);

	/* log2(x) = log1p(z/c-1)/ln2 + log2(c) + k */
	r = z * invc - 1;
	y0 = logc + (t_f64)k;

	/* Pipelined polynomial evaluation to approximate log1p(r)/ln2.  */
	r2 = r * r;
	y = A[0] * r + A[1];
	p = A[2] * r + A[3];
	r4 = r2 * r2;
	q = A[4] * r + y0;
	q = p * r2 + q;
	y = y * r4 + q;
	return y;
}

#undef N
#undef T
#define N (1 << EXP2F_TABLE_BITS)
#define T __exp2f_data.tab
#define SIGN_BIAS (1 << (EXP2F_TABLE_BITS + 11))

/* The output of log2 and thus the input of exp2 is either scaled by N
   (in case of fast toint intrinsics) or not.  The unscaled xd must be
   in [-1021,1023], sign_bias sets the sign of the result.  */
static inline
float exp2_inline(t_f64 xd, uint32_t sign_bias)
{
	uint64_t ki, ski, t;
	t_f64 kd, z, r, r2, y, s;

#if TOINT_INTRINSICS
#define C __exp2f_data.poly_scaled
	/* N*x = k + r with r in [-1/2, 1/2] */
	kd = roundtoint(xd); /* k */
	ki = converttoint(xd);
#else
#define C __exp2f_data.poly
#define SHIFT __exp2f_data.shift_scaled
	/* x = k/N + r with r in [-1/(2N), 1/(2N)] */
	kd = eval_as_double(xd + SHIFT);
	ki = asuint64(kd);
	kd -= SHIFT; /* k/N */
#endif
	r = xd - kd;

	/* exp2(x) = 2^(k/N) * 2^r ~= s * (C0*r^3 + C1*r^2 + C2*r + 1) */
	t = T[ki % N];
	ski = ki + sign_bias;
	t += ski << (52 - EXP2F_TABLE_BITS);
	s = asdouble(t);
	z = C[0] * r + C[1];
	r2 = r * r;
	y = C[2] * r + 1;
	y = z * r2 + y;
	y = y * s;
	return eval_as_float(y);
}

/* Returns 0 if not int, 1 if odd int, 2 if even int.  The argument is
   the bit representation of a non-zero finite floating-point value.  */
static inline
int checkint(uint32_t iy)
{
	int e = iy >> 23 & 0xff;
	if (e < 0x7f)
		return 0;
	if (e > 0x7f + 23)
		return 2;
	if (iy & ((1 << (0x7f + 23 - e)) - 1))
		return 0;
	if (iy & (1 << (0x7f + 23 - e)))
		return 1;
	return 2;
}

static inline
int zeroinfnan(uint32_t ix)
{
	return 2 * ix - 1 >= 2u * 0x7f800000 - 1;
}

float powf(float x, float y)
{
	uint32_t sign_bias = 0;
	uint32_t ix, iy;

	ix = asuint(x);
	iy = asuint(y);
	if (predict_false(ix - 0x00800000 >= 0x7f800000 - 0x00800000 || zeroinfnan(iy)))
	{
		/* Either (x < 0x1p-126 or inf or nan) or (y is 0 or inf or nan).  */
		if (predict_false(zeroinfnan(iy)))
		{
			if (2 * iy == 0)
				return issignalingf_inline(x) ? x + y : 1.0f;
			if (ix == 0x3f800000)
				return issignalingf_inline(y) ? x + y : 1.0f;
			if (2 * ix > 2u * 0x7f800000 ||
			    2 * iy > 2u * 0x7f800000)
				return x + y;
			if (2 * ix == 2 * 0x3f800000)
				return 1.0f;
			if ((2 * ix < 2 * 0x3f800000) == !(iy & 0x80000000))
				return 0.0f; /* |x|<1 && y==inf or |x|>1 && y==-inf.  */
			return y * y;
		}
		if (predict_false(zeroinfnan(ix)))
		{
			float_t x2 = x * x;
			if (ix & 0x80000000 && checkint(iy) == 1)
				x2 = -x2;
			/* Without the barrier some versions of clang hoist the 1/x2 and
			   thus division by zero exception can be signaled spuriously.  */
			return iy & 0x80000000 ? fp_barrierf(1 / x2) : x2;
		}
		/* x and y are non-zero finite.  */
		if (ix & 0x80000000)
		{
			/* Finite x < 0.  */
			int yint = checkint(iy);
			if (yint == 0)
				return __math_invalidf(x);
			if (yint == 1)
				sign_bias = SIGN_BIAS;
			ix &= 0x7fffffff;
		}
		if (ix < 0x00800000)
		{
			/* Normalize subnormal x so exponent becomes negative.  */
			ix = asuint(x * 0x1p23f);
			ix &= 0x7fffffff;
			ix -= 23 << 23;
		}
	}
	t_f64 logx = log2_inline(ix);
	t_f64 ylogx = y * logx; /* cannot overflow, y is single prec.  */
	if (predict_false((asuint64(ylogx) >> 47 & 0xffff) >=
			  asuint64(126.0 * POWF_SCALE) >> 47))
	{
		/* |y*log(x)| >= 126.  */
		if (ylogx > 0x1.fffffffd1d571p+6 * POWF_SCALE)
			return __math_oflowf(sign_bias);
		if (ylogx <= -150.0 * POWF_SCALE)
			return __math_uflowf(sign_bias);
	}
	return exp2_inline(ylogx, sign_bias);
}




/*
Worst-case error: 0.54 ULP (~= ulperr_exp + 1024*Ln2*relerr_log*2^53)
relerr_log: 1.3 * 2^-68 (Relative error of log, 1.5 * 2^-68 without fma)
ulperr_exp: 0.509 ULP (ULP error of exp, 0.511 ULP without fma)
*/

#define T __pow_log_data.tab
#define A __pow_log_data.poly
#define Ln2hi __pow_log_data.ln2hi
#define Ln2lo __pow_log_data.ln2lo
#define N (1 << POW_LOG_TABLE_BITS)
#define OFF 0x3fe6955500000000

/* Top 12 bits of a double (sign and exponent bits).  */
static inline
uint32_t top12(double x)
{
	return asuint64(x) >> 52;
}

/* Compute y+TAIL = log(x) where the rounded result is y and TAIL has about
   additional 15 bits precision.  IX is the bit representation of x, but
   normalized in the subnormal range using the sign bit for the exponent.  */
static inline
t_f64 log_inline(uint64_t ix, t_f64 *tail)
{
	/* t_f64 for better performance on targets with FLT_EVAL_METHOD==2.  */
	t_f64 z, r, y, invc, logc, logctail, kd, hi, t1, t2, lo, lo1, lo2, p;
	uint64_t iz, tmp;
	int k, i;

	/* x = 2^k z; where z is in range [OFF,2*OFF) and exact.
	   The range is split into N subintervals.
	   The ith subinterval contains z and c is near its center.  */
	tmp = ix - OFF;
	i = (tmp >> (52 - POW_LOG_TABLE_BITS)) % N;
	k = (int64_t)tmp >> 52; /* arithmetic shift */
	iz = ix - (tmp & 0xfffULL << 52);
	z = asdouble(iz);
	kd = (t_f64)k;

	/* log(x) = k*Ln2 + log(c) + log1p(z/c-1).  */
	invc = T[i].invc;
	logc = T[i].logc;
	logctail = T[i].logctail;

	/* Note: 1/c is j/N or j/N/2 where j is an integer in [N,2N) and
     |z/c - 1| < 1/N, so r = z/c - 1 is exactly representible.  */
#if __FP_FAST_FMA
	r = __builtin_fma(z, invc, -1.0);
#else
	/* Split z such that rhi, rlo and rhi*rhi are exact and |rlo| <= |r|.  */
	t_f64 zhi = asdouble((iz + (1ULL << 31)) & (-1ULL << 32));
	t_f64 zlo = z - zhi;
	t_f64 rhi = zhi * invc - 1.0;
	t_f64 rlo = zlo * invc;
	r = rhi + rlo;
#endif

	/* k*Ln2 + log(c) + r.  */
	t1 = kd * Ln2hi + logc;
	t2 = t1 + r;
	lo1 = kd * Ln2lo + logctail;
	lo2 = t1 - t2 + r;

	/* Evaluation is optimized assuming superscalar pipelined execution.  */
	t_f64 ar, ar2, ar3, lo3, lo4;
	ar = A[0] * r; /* A[0] = -0.5.  */
	ar2 = r * ar;
	ar3 = r * ar2;
	/* k*Ln2 + log(c) + r + A[0]*r*r.  */
#if __FP_FAST_FMA
	hi = t2 + ar2;
	lo3 = __builtin_fma(ar, r, -ar2);
	lo4 = t2 - hi + ar2;
#else
	t_f64 arhi = A[0] * rhi;
	t_f64 arhi2 = rhi * arhi;
	hi = t2 + arhi2;
	lo3 = rlo * (ar + arhi);
	lo4 = t2 - hi + arhi2;
#endif
	/* p = log1p(r) - r - A[0]*r*r.  */
	p = (ar3 * (A[1] + r * A[2] +
		    ar2 * (A[3] + r * A[4] + ar2 * (A[5] + r * A[6]))));
	lo = lo1 + lo2 + lo3 + lo4 + p;
	y = hi + lo;
	*tail = hi - y + lo;
	return y;
}

#undef N
#undef T
#define N (1 << EXP_TABLE_BITS)
#define InvLn2N __exp_data.invln2N
#define NegLn2hiN __exp_data.negln2hiN
#define NegLn2loN __exp_data.negln2loN
#define Shift __exp_data.shift
#define T __exp_data.tab
#define C2 __exp_data.poly[5 - EXP_POLY_ORDER]
#define C3 __exp_data.poly[6 - EXP_POLY_ORDER]
#define C4 __exp_data.poly[7 - EXP_POLY_ORDER]
#define C5 __exp_data.poly[8 - EXP_POLY_ORDER]
#define C6 __exp_data.poly[9 - EXP_POLY_ORDER]

/* Handle cases that may overflow or underflow when computing the result that
   is scale*(1+TMP) without intermediate rounding.  The bit representation of
   scale is in SBITS, however it has a computed exponent that may have
   overflown into the sign bit so that needs to be adjusted before using it as
   a double.  (int32_t)KI is the k used in the argument reduction and exponent
   adjustment of scale, positive k here means the result may overflow and
   negative k means the result may underflow.  */
static inline
double specialcase(t_f64 tmp, uint64_t sbits, uint64_t ki)
{
	t_f64 scale, y;

	if ((ki & 0x80000000) == 0)
	{
		/* k > 0, the exponent of scale might have overflowed by <= 460.  */
		sbits -= 1009ull << 52;
		scale = asdouble(sbits);
		y = 0x1p1009 * (scale + scale * tmp);
		return eval_as_double(y);
	}
	/* k < 0, need special care in the subnormal range.  */
	sbits += 1022ull << 52;
	/* Note: sbits is signed scale.  */
	scale = asdouble(sbits);
	y = scale + scale * tmp;
	if (fabs(y) < 1.0)
	{
		/* Round y to the right precision before scaling it into the subnormal
		   range to avoid double rounding that can cause 0.5+E/2 ulp error where
		   E is the worst-case ulp error outside the subnormal range.  So this
		   is only useful if the goal is better than 1 ulp worst-case error.  */
		t_f64 hi, lo, one = 1.0;
		if (y < 0.0)
			one = -1.0;
		lo = scale - y + scale * tmp;
		hi = one + y;
		lo = one - hi + y + lo;
		y = eval_as_double(hi + lo) - one;
		/* Fix the sign of 0.  */
		if (y == 0.0)
			y = asdouble(sbits & 0x8000000000000000);
		/* The underflow exception needs to be signaled explicitly.  */
		fp_force_eval(fp_barrier(0x1p-1022) * 0x1p-1022);
	}
	y = 0x1p-1022 * y;
	return eval_as_double(y);
}

#define SIGN_BIAS (0x800 << EXP_TABLE_BITS)

/* Computes sign*exp(x+xtail) where |xtail| < 2^-8/N and |xtail| <= |x|.
   The sign_bias argument is SIGN_BIAS or 0 and sets the sign to -1 or 1.  */
static inline
double exp_inline(t_f64 x, t_f64 xtail, uint32_t sign_bias)
{
	uint32_t abstop;
	uint64_t ki, idx, top, sbits;
	/* t_f64 for better performance on targets with FLT_EVAL_METHOD==2.  */
	t_f64 kd, z, r, r2, scale, tail, tmp;

	abstop = top12(x) & 0x7ff;
	if (predict_false(abstop - top12(0x1p-54) >=
			  top12(512.0) - top12(0x1p-54)))
	{
		if (abstop - top12(0x1p-54) >= 0x80000000)
		{
			/* Avoid spurious underflow for tiny x.  */
			/* Note: 0 is common input.  */
			t_f64 one = WANT_ROUNDING ? 1.0 + x : 1.0;
			return sign_bias ? -one : one;
		}
		if (abstop >= top12(1024.0))
		{
			/* Note: inf and nan are already handled.  */
			if (asuint64(x) >> 63)
				return __math_uflow(sign_bias);
			else
				return __math_oflow(sign_bias);
		}
		/* Large x is special cased below.  */
		abstop = 0;
	}

	/* exp(x) = 2^(k/N) * exp(r), with exp(r) in [2^(-1/2N),2^(1/2N)].  */
	/* x = ln2/N*k + r, with int k and r in [-ln2/2N, ln2/2N].  */
	z = InvLn2N * x;
#if TOINT_INTRINSICS
	kd = roundtoint(z);
	ki = converttoint(z);
#elif EXP_USE_TOINT_NARROW
	/* z - kd is in [-0.5-2^-16, 0.5] in all rounding modes.  */
	kd = eval_as_double(z + Shift);
	ki = asuint64(kd) >> 16;
	kd = (t_f64)(int32_t)ki;
#else
	/* z - kd is in [-1, 1] in non-nearest rounding modes.  */
	kd = eval_as_double(z + Shift);
	ki = asuint64(kd);
	kd -= Shift;
#endif
	r = x + kd * NegLn2hiN + kd * NegLn2loN;
	/* The code assumes 2^-200 < |xtail| < 2^-8/N.  */
	r += xtail;
	/* 2^(k/N) ~= scale * (1 + tail).  */
	idx = 2 * (ki % N);
	top = (ki + sign_bias) << (52 - EXP_TABLE_BITS);
	tail = asdouble(T[idx]);
	/* This is only a valid scale when -1023*N < k < 1024*N.  */
	sbits = T[idx + 1] + top;
	/* exp(x) = 2^(k/N) * exp(r) ~= scale + scale * (tail + exp(r) - 1).  */
	/* Evaluation is optimized assuming superscalar pipelined execution.  */
	r2 = r * r;
	/* Without fma the worst case error is 0.25/N ulp larger.  */
	/* Worst case error is less than 0.5+1.11/N+(abs poly error * 2^53) ulp.  */
	tmp = tail + r + r2 * (C2 + r * C3) + r2 * r2 * (C4 + r * C5);
	if (predict_false(abstop == 0))
		return specialcase(tmp, sbits, ki);
	scale = asdouble(sbits);
	/* Note: tmp == 0 or |tmp| > 2^-200 and scale > 2^-739, so there
	   is no spurious underflow here even without fma.  */
	return eval_as_double(scale + scale * tmp);
}

/*!
**	Returns 0 if not int, 1 if odd int, 2 if even int.
**	The argument is the bit representation of a non-zero finite floating-point value.
*/
static inline
int checkint(uint64_t iy)
{
	int e = iy >> 52 & 0x7ff;
	if (e < 0x3ff)
		return 0;
	if (e > 0x3ff + 52)
		return 2;
	if (iy & ((1ULL << (0x3ff + 52 - e)) - 1))
		return 0;
	if (iy & (1ULL << (0x3ff + 52 - e)))
		return 1;
	return 2;
}

/*!
**	Returns 1 if input is the bit representation of 0, infinity or nan.
*/
static inline
int zeroinfnan(uint64_t i)
{
	return 2 * i - 1 >= 2 * asuint64(INFINITY) - 1;
}

double pow(double x, double y)
{
	uint32_t sign_bias = 0;
	uint64_t ix, iy;
	uint32_t topx, topy;

	ix = asuint64(x);
	iy = asuint64(y);
	topx = top12(x);
	topy = top12(y);
	if (predict_false(topx - 0x001 >= 0x7ff - 0x001 ||
			  (topy & 0x7ff) - 0x3be >= 0x43e - 0x3be))
	{
		/* Note: if |y| > 1075 * ln2 * 2^53 ~= 0x1.749p62 then pow(x,y) = inf/0
		   and if |y| < 2^-54 / 1075 ~= 0x1.e7b6p-65 then pow(x,y) = +-1.  */
		/* Special cases: (x < 0x1p-126 or inf or nan) or
		   (|y| < 0x1p-65 or |y| >= 0x1p63 or nan).  */
		if (predict_false(zeroinfnan(iy)))
		{
			if (2 * iy == 0)
				return issignaling_inline(x) ? x + y : 1.0;
			if (ix == asuint64(1.0))
				return issignaling_inline(y) ? x + y : 1.0;
			if (2 * ix > 2 * asuint64(INFINITY) ||
			    2 * iy > 2 * asuint64(INFINITY))
				return x + y;
			if (2 * ix == 2 * asuint64(1.0))
				return 1.0;
			if ((2 * ix < 2 * asuint64(1.0)) == !(iy >> 63))
				return 0.0; /* |x|<1 && y==inf or |x|>1 && y==-inf.  */
			return y * y;
		}
		if (predict_false(zeroinfnan(ix)))
		{
			t_f64 x2 = x * x;
			if (ix >> 63 && checkint(iy) == 1)
				x2 = -x2;
			/* Without the barrier some versions of clang hoist the 1/x2 and
			   thus division by zero exception can be signaled spuriously.  */
			return iy >> 63 ? fp_barrier(1 / x2) : x2;
		}
		/* Here x and y are non-zero finite.  */
		if (ix >> 63)
		{
			/* Finite x < 0.  */
			int yint = checkint(iy);
			if (yint == 0)
				return __math_invalid(x);
			if (yint == 1)
				sign_bias = SIGN_BIAS;
			ix &= 0x7fffffffffffffff;
			topx &= 0x7ff;
		}
		if ((topy & 0x7ff) - 0x3be >= 0x43e - 0x3be)
		{
			/* Note: sign_bias == 0 here because y is not odd.  */
			if (ix == asuint64(1.0))
				return 1.0;
			if ((topy & 0x7ff) < 0x3be)
			{
				/* |y| < 2^-65, x^y ~= 1 + y*log(x).  */
				if (WANT_ROUNDING)
					return ix > asuint64(1.0) ? 1.0 + y :
								    1.0 - y;
				else
					return 1.0;
			}
			return (ix > asuint64(1.0)) == (topy < 0x800) ?
				       __math_oflow(0) :
				       __math_uflow(0);
		}
		if (topx == 0)
		{
			/* Normalize subnormal x so exponent becomes negative.  */
			ix = asuint64(x * 0x1p52);
			ix &= 0x7fffffffffffffff;
			ix -= 52ULL << 52;
		}
	}

	t_f64 lo;
	t_f64 hi = log_inline(ix, &lo);
	t_f64 ehi, elo;
#if __FP_FAST_FMA
	ehi = y * hi;
	elo = y * lo + __builtin_fma(y, hi, -ehi);
#else
	t_f64 yhi = asdouble(iy & -1ULL << 27);
	t_f64 ylo = y - yhi;
	t_f64 lhi = asdouble(asuint64(hi) & -1ULL << 27);
	t_f64 llo = hi - lhi + lo;
	ehi = yhi * lhi;
	elo = ylo * lhi + y * llo; /* |elo| < |ehi| * 2^-25.  */
#endif
	return exp_inline(ehi, elo, sign_bias);
}



/*
 * Copyright (c) 2008 Stephen L. Moshier <steve@moshier.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*                                                      powl.c
 *
 *      Power function, long double precision
 *
 *
 * SYNOPSIS:
 *
 * long double x, y, z, powl();
 *
 * z = powl( x, y );
 *
 *
 * DESCRIPTION:
 *
 * Computes x raised to the yth power.  Analytically,
 *
 *      x**y  =  exp( y log(x) ).
 *
 * Following Cody and Waite, this program uses a lookup table
 * of 2**-i/32 and pseudo extended precision arithmetic to
 * obtain several extra bits of accuracy in both the logarithm
 * and the exponential.
 *
 *
 * ACCURACY:
 *
 * The relative error of pow(x,y) can be estimated
 * by   y dl ln(2),   where dl is the absolute error of
 * the internally computed base 2 logarithm.  At the ends
 * of the approximation interval the logarithm equal 1/32
 * and its relative error is about 1 lsb = 1.1e-19.  Hence
 * the predicted relative error in the result is 2.3e-21 y .
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *
 *    IEEE     +-1000       40000      2.8e-18      3.7e-19
 * .001 < x < 1000, with log(x) uniformly distributed.
 * -1000 < y < 1000, y uniformly distributed.
 *
 *    IEEE     0,8700       60000      6.5e-18      1.0e-18
 * 0.99 < x < 1.01, 0 < y < 8700, uniformly distributed.
 *
 */

#if LIBCONFIG_USE_FLOAT80

/* Table size */
#define NXT 32

/*!
**	log(1+x) =  x - .5x^2 + x^3 *  P(z)/Q(z)
**	on the domain  2^(-1/32) - 1  <=  x  <=  2^(1/32) - 1
*/
static const long double P[] =
{
	+8.3319510773868690346226E-4L,
	+4.9000050881978028599627E-1L,
	+1.7500123722550302671919E0L,
	+1.4000100839971580279335E0L,
};
static const long double Q[] =
{
/*	+1.0000000000000000000000E0L,*/
	+5.2500282295834889175431E0L,
	+8.4000598057587009834666E0L,
	+4.2000302519914740834728E0L,
};
/* A[i] = 2^(-i/32), rounded to IEEE long double precision.
 * If i is even, A[i] + B[i/2] gives additional accuracy.
 */
static const long double A[33] =
{
	+1.0000000000000000000000E0L,
	+9.7857206208770013448287E-1L,
	+9.5760328069857364691013E-1L,
	+9.3708381705514995065011E-1L,
	+9.1700404320467123175367E-1L,
	+8.9735453750155359320742E-1L,
	+8.7812608018664974155474E-1L,
	+8.5930964906123895780165E-1L,
	+8.4089641525371454301892E-1L,
	+8.2287773907698242225554E-1L,
	+8.0524516597462715409607E-1L,
	+7.8799042255394324325455E-1L,
	+7.7110541270397041179298E-1L,
	+7.5458221379671136985669E-1L,
	+7.3841307296974965571198E-1L,
	+7.2259040348852331001267E-1L,
	+7.0710678118654752438189E-1L,
	+6.9195494098191597746178E-1L,
	+6.7712777346844636413344E-1L,
	+6.6261832157987064729696E-1L,
	+6.4841977732550483296079E-1L,
	+6.3452547859586661129850E-1L,
	+6.2092890603674202431705E-1L,
	+6.0762367999023443907803E-1L,
	+5.9460355750136053334378E-1L,
	+5.8186242938878875689693E-1L,
	+5.6939431737834582684856E-1L,
	+5.5719337129794626814472E-1L,
	+5.4525386633262882960438E-1L,
	+5.3357020033841180906486E-1L,
	+5.2213689121370692017331E-1L,
	+5.1094857432705833910408E-1L,
	+5.0000000000000000000000E-1L,
};
static const long double B[17] =
{
	+0.0000000000000000000000E0L,
	+2.6176170809902549338711E-20L,
	-1.0126791927256478897086E-20L,
	+1.3438228172316276937655E-21L,
	+1.2207982955417546912101E-20L,
	-6.3084814358060867200133E-21L,
	+1.3164426894366316434230E-20L,
	-1.8527916071632873716786E-20L,
	+1.8950325588932570796551E-20L,
	+1.5564775779538780478155E-20L,
	+6.0859793637556860974380E-21L,
	-2.0208749253662532228949E-20L,
	+1.4966292219224761844552E-20L,
	+3.3540909728056476875639E-21L,
	-8.6987564101742849540743E-22L,
	-1.2327176863327626135542E-20L,
	+0.0000000000000000000000E0L,
};

/* 2^x = 1 + x P(x),
 * on the interval -1/32 <= x <= 0
 */
static const long double R[] =
{
	+1.5089970579127659901157E-5L,
	+1.5402715328927013076125E-4L,
	+1.3333556028915671091390E-3L,
	+9.6181291046036762031786E-3L,
	+5.5504108664798463044015E-2L,
	+2.4022650695910062854352E-1L,
	+6.9314718055994530931447E-1L,
};

#define MEXP (NXT*16384.0L)
/* The following if denormal numbers are supported, else -MEXP: */
#define MNEXP (-NXT*(16384.0L+64.0L))
/* log2(e) - 1 */
#define LOG2EA 0.44269504088896340735992L

#define F W
#define Fa Wa
#define Fb Wb
#define G W
#define Ga Wa
#define Gb u
#define H W
#define Ha Wb
#define Hb Wb

static const long double MAXLOGL = 1.1356523406294143949492E4L;
static const long double MINLOGL = -1.13994985314888605586758E4L;
static const long double LOGE2L = 6.9314718055994530941723E-1L;
static const long double huge = 0x1p10000L;
/* XXX Prevent gcc from erroneously constant folding this. */
static const volatile long double twom10000 = 0x1p-10000L;

static long double reducl(long double);
static long double powil(long double, int);

long double powl(long double x, long double y)
{
	/* double F, Fa, Fb, G, Ga, Gb, H, Ha, Hb */
	int i, nflg, iyflg, yoddint;
	long e;
	volatile long double z=0;
	long double w=0, W=0, Wa=0, Wb=0, ya=0, yb=0, u=0;

	/* make sure no invalid exception is raised by nan comparision */
	if (isnan(x))
	{
		if (!isnan(y) && y == 0.0)
			return 1.0;
		return x;
	}
	if (isnan(y))
	{
		if (x == 1.0)
			return 1.0;
		return y;
	}
	if (x == 1.0)
		return 1.0; /* 1**y = 1, even if y is nan */
	if (y == 0.0)
		return 1.0; /* x**0 = 1, even if x is nan */
	if (y == 1.0)
		return x;
	/* if y*log2(x) < log2(LDBL_TRUE_MIN)-1 then x^y uflows to 0
	   if y*log2(x) > -log2(LDBL_TRUE_MIN)+1 > LDBL_MAX_EXP then x^y oflows
	   if |x|!=1 then |log2(x)| > |log(x)| > LDBL_EPSILON/2 so
	   x^y oflows/uflows if |y|*LDBL_EPSILON/2 > -log2(LDBL_TRUE_MIN)+1 */
	if (fabsl(y) > 2*(-LDBL_MIN_EXP+LDBL_MANT_DIG+1)/LDBL_EPSILON)
	{
		/* y is not an odd int */
		if (x == -1.0)
			return 1.0;
		if (y == INFINITY)
		{
			if (x > 1.0 || x < -1.0)
				return INFINITY;
			return 0.0;
		}
		if (y == -INFINITY)
		{
			if (x > 1.0 || x < -1.0)
				return 0.0;
			return INFINITY;
		}
		if ((x > 1.0 || x < -1.0) == (y > 0))
			return huge * huge;
		return twom10000 * twom10000;
	}
	if (x == INFINITY)
	{
		if (y > 0.0)
			return INFINITY;
		return 0.0;
	}

	w = floorl(y);

	/* Set iyflg to 1 if y is an integer. */
	iyflg = 0;
	if (w == y)
		iyflg = 1;

	/* Test for odd integer y. */
	yoddint = 0;
	if (iyflg)
	{
		ya = fabsl(y);
		ya = floorl(0.5 * ya);
		yb = 0.5 * fabsl(w);
		if( ya != yb )
			yoddint = 1;
	}

	if (x == -INFINITY)
	{
		if (y > 0.0)
		{
			if (yoddint)
				return -INFINITY;
			return INFINITY;
		}
		if (y < 0.0)
		{
			if (yoddint)
				return -0.0;
			return 0.0;
		}
	}
	nflg = 0; /* (x<0)**(odd int) */
	if (x <= 0.0)
	{
		if (x == 0.0)
		{
			if (y < 0.0)
			{
				if (signbit(x) && yoddint)
					/* (-0.0)**(-odd int) = -inf, divbyzero */
					return -1.0/0.0;
				/* (+-0.0)**(negative) = inf, divbyzero */
				return 1.0/0.0;
			}
			if (signbit(x) && yoddint)
				return -0.0;
			return 0.0;
		}
		if (iyflg == 0)
			return (x - x) / (x - x); /* (x<0)**(non-int) is NaN */
		/* (x<0)**(integer) */
		if (yoddint)
			nflg = 1; /* negate result */
		x = -x;
	}
	/* (+integer)**(integer)  */
	if (iyflg && floorl(x) == x && fabsl(y) < 32768.0)
	{
		w = powil(x, (int)y);
		return nflg ? -w : w;
	}

	/* separate significand from exponent */
	x = frexpl(x, &i);
	e = i;

	/* find significand in antilog table A[] */
	i = 1;
	if (x <= A[17])
		i = 17;
	if (x <= A[i+8])
		i += 8;
	if (x <= A[i+4])
		i += 4;
	if (x <= A[i+2])
		i += 2;
	if (x >= A[1])
		i = -1;
	i += 1;

	/* Find (x - A[i])/A[i]
	 * in order to compute log(x/A[i]):
	 *
	 * log(x) = log( a x/a ) = log(a) + log(x/a)
	 *
	 * log(x/a) = log(1+v),  v = x/a - 1 = (x-a)/a
	 */
	x -= A[i];
	x -= B[i/2];
	x /= A[i];

	/* rational approximation for log(1+v):
	 *
	 * log(1+v)  =  v  -  v**2/2  +  v**3 P(v) / Q(v)
	 */
	z = x*x;
	w = x * (z * __polevll(x, P, 3) / __p1evll(x, Q, 3));
	w = w - 0.5*z;

	/* Convert to base 2 logarithm:
	 * multiply by log2(e) = 1 + LOG2EA
	 */
	z = LOG2EA * w;
	z += w;
	z += LOG2EA * x;
	z += x;

	/* Compute exponent term of the base 2 logarithm. */
	w = -i;
	w /= NXT;
	w += e;
	/* Now base 2 log of x is w + z. */

	/* Multiply base 2 log by y, in extended precision. */

	/* separate y into large part ya
	 * and small part yb less than 1/NXT
	 */
	ya = reducl(y);
	yb = y - ya;

	/* (w+z)(ya+yb)
	 * = w*ya + w*yb + z*y
	 */
	F = z * y  +  w * yb;
	Fa = reducl(F);
	Fb = F - Fa;

	G = Fa + w * ya;
	Ga = reducl(G);
	Gb = G - Ga;

	H = Fb + Gb;
	Ha = reducl(H);
	w = (Ga + Ha) * NXT;

	/* Test the power of 2 for overflow */
	if (w > MEXP)
		return huge * huge;  /* overflow */
	if (w < MNEXP)
		return twom10000 * twom10000;  /* underflow */

	e = w;
	Hb = H - Ha;

	if (Hb > 0.0)
	{
		e += 1;
		Hb -= 1.0/NXT;  /*0.0625L;*/
	}

	/* Now the product y * log2(x)  =  Hb + e/NXT.
	 *
	 * Compute base 2 exponential of Hb,
	 * where -0.0625 <= Hb <= 0.
	 */
	z = Hb * __polevll(Hb, R, 6);  /*  z = 2**Hb - 1  */

	/* Express e/NXT as an integer plus a negative number of (1/NXT)ths.
	 * Find lookup table entry for the fractional power of 2.
	 */
	if (e < 0)
		i = 0;
	else
		i = 1;
	i = e/NXT + i;
	e = NXT*i - e;
	w = A[e];
	z = w * z;  /*  2**-e * ( 1 + (2**Hb-1) )  */
	z = z + w;
	z = scalbnl(z, i);  /* multiply by integer power of 2 */

	if (nflg)
		z = -z;
	return z;
}


/* Find a multiple of 1/NXT that is within 1/NXT of x. */
static
long double reducl(long double x)
{
	long double t;

	t = x * NXT;
	t = floorl(t);
	t = t / NXT;
	return t;
}

/*
 *      Positive real raised to integer power, long double precision
 *
 *
 * SYNOPSIS:
 *
 * long double x, y, powil();
 * int n;
 *
 * y = powil( x, n );
 *
 *
 * DESCRIPTION:
 *
 * Returns argument x>0 raised to the nth power.
 * The routine efficiently decomposes n as a sum of powers of
 * two. The desired power is a product of two-to-the-kth
 * powers of x.  Thus to compute the 32767 power of x requires
 * 28 multiplications instead of 32767 multiplications.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   x domain   n domain  # trials      peak         rms
 *    IEEE     .001,1000  -1022,1023  50000       4.3e-17     7.8e-18
 *    IEEE        1,2     -1022,1023  20000       3.9e-17     7.6e-18
 *    IEEE     .99,1.01     0,8700    10000       3.6e-16     7.2e-17
 *
 * Returns MAXNUM on overflow, zero on underflow.
 */

static
long double powil(long double x, int nn)
{
	long double ww, y;
	long double s;
	int n, e, sign, lx;

	if (nn == 0)
		return 1.0;

	if (nn < 0)
	{
		sign = -1;
		n = -nn;
	}
	else
	{
		sign = 1;
		n = nn;
	}
	/* Overflow detection */
	/* Calculate approximate logarithm of answer */
	s = x;
	s = frexpl( s, &lx);
	e = (lx - 1)*n;
	if ((e == 0) || (e > 64) || (e < -64))
	{
		s = (s - 7.0710678118654752e-1L) / (s +  7.0710678118654752e-1L);
		s = (2.9142135623730950L * s - 0.5 + lx) * nn * LOGE2L;
	}
	else
	{
		s = LOGE2L * e;
	}
	if (s > MAXLOGL)
		return huge * huge;  /* overflow */
	if (s < MINLOGL)
		return twom10000 * twom10000;  /* underflow */
	/* Handle tiny denormal answer, but with less accuracy
	 * since roundoff error in 1.0/x will be amplified.
	 * The precise demarcation should be the gradual underflow threshold.
	 */
	if (s < -MAXLOGL+2.0)
	{
		x = 1.0/x;
		sign = -sign;
	}
	/* First bit of the power */
	if (n & 1)
		y = x;
	else
		y = 1.0;
	ww = x;
	n >>= 1;
	while (n)
	{
		ww = ww * ww;   /* arg to the 2-to-the-kth power */
		if (n & 1)     /* if that bit is set, then include in product */
			y *= ww;
		n >>= 1;
	}
	if (sign < 0)
		y = 1.0/y;
	return y;
}
#endif



#if LIBCONFIG_USE_FLOAT128
#warning "not implemented"
#endif



#endif
