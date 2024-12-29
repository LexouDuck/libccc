
#include "libccc/float.h"
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Ln, log)
#elif LIBCONFIG_USE_CCC_MATH
/*
**	The following pair of functions return the natural logarithm of x.
**	ln(x) = ln(x*2^n) = n*ln(2) + ln(x) with (1 <= x < 2) and (n = exp_b2)
**	F##BITS##_EXPONENT_ZERO is exponent bits except the MSB for exponent:
**	this corresponds precisely to an exponent of zero when unbiased.
*/
#define DEFINEFUNC_FLOAT_LN(BITS) \
static \
t_f##BITS	F##BITS##_Ln_TaylorSeries(t_f##BITS x) \
{ \
	t_f##BITS	result; \
	t_f##BITS	result_previous; \
	t_f##BITS	power; \
	t_f##BITS	i; \
	/* Taylor series approximation method */ \
	i = 2.; \
	power = x; \
	result = x; \
	result_previous = NAN; \
	while (ABS(power) > FLOAT_APPROX) \
	{ \
		power *= x; \
		result += (((((t_sint)i % 2)) * 2.) - 1.) * (power / i); \
		if (result == result_previous) \
			break; \
		result_previous = result; \
		++i; \
	} \
	return (result); \
} \
t_f##BITS	F##BITS##_Log(t_f##BITS x) \
{ \
	static const t_f##BITS LN_3_2  = 0x1.9F323ECBF984Cp-2L; \
	static const t_f##BITS DIV_2_3 = 0x1.5555555555556p-1L; \
	t_f##BITS	result; \
	t_u64	tmp = 0;	/* a raw memory copy */ \
	t_u64	norm = 0;	/* the t_f32 x in x*2^n in raw memory */ \
	t_s32	exp_b2; \
	/* Taylor series approximation method */ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((x < 0.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if (x == 0.) \
		return (-INFINITY); \
	if (x == 1.) \
		return (0.); \
	if (x == INFINITY) \
		return (INFINITY); \
	if (x < 1. || 2. <= x) \
	{ \
		Memory_Copy(&tmp, &x, sizeof(t_f##BITS)); \
		norm = (tmp & F##BITS##_MANTISSA_SIGNED) | F##BITS##_EXPONENT_ZERO; \
		Memory_Copy(&x, &norm, sizeof(t_f##BITS)); \
		result = F##BITS##_Log(x); \
		exp_b2 = ((tmp << 1) >> (F##BITS##_MANTISSA_BITS + 1)) - F##BITS##_EXPONENT_BIAS; \
		return (LN_2 * exp_b2 + result); \
	} \
	if (1.9 <= x && x < 2.) \
		return (F##BITS##_Log(x * DIV_2_3) + LN_3_2); \
	result = F##BITS##_Ln_TaylorSeries(x - 1.); \
	return (result); \
} \

DEFINEFUNC_FLOAT_LN(32)
DEFINEFUNC_FLOAT_LN(64)
#if LIBCONFIG_USE_FLOAT80
// TODO: DEFINEFUNC_FLOAT_LN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
// TODO: DEFINEFUNC_FLOAT_LN(128)
#endif

#else


/*
LOGF_TABLE_BITS = 4
LOGF_POLY_ORDER = 4

ULP error: 0.818 (nearest rounding.)
Relative error: 1.957 * 2^-26 (before rounding.)
*/

#define N (1 << LOGF_TABLE_BITS)

t_f32	F32_Log(t_f32 x)
{
	static const t_u32 OFF = 0x3f330000;
	t_f64 z, r, r2, y, y0, invc, logc;
	t_u32 ix, iz, tmp;
	int k, i;

	ix = AS_U32(x);
	/* Fix sign of zero with downward rounding when x==1. */
	if (WANT_ROUNDING && predict_false(ix == 0x3f800000))
		return 0;
	if (predict_false(ix - 0x00800000 >= 0x7f800000 - 0x00800000))
	{
		/* x < 0x1p-126 or inf or nan. */
		if (ix * 2 == 0)
			return __math_divzerof(1);
		if (ix == 0x7f800000) /* log(inf) == inf. */
			return x;
		if ((ix & 0x80000000) || ix * 2 >= 0xff000000)
			return __math_invalidf(x);
		/* x is subnormal, normalize it. */
		ix = AS_U32(x * 0x1p23f);
		ix -= (t_u32)F32_MANTISSA_BITS << F32_MANTISSA_BITS;
	}
	/*
	x = 2^k z; where z is in range [OFF,2*OFF] and exact.
	The range is split into N subintervals.
	The ith subinterval contains z and c is near its center.
	*/
	tmp = ix - OFF;
	i = (tmp >> (F32_MANTISSA_BITS - TABLEBITS_LOG_F32)) % N_LOG_F32;
	k = (t_s32)tmp >> F32_MANTISSA_BITS; /* arithmetic shift */
	iz = ix - (tmp & 0xff800000);
	invc = __data_log_f32.table[i].invc;
	logc = __data_log_f32.table[i].logc;
	z = (t_f64)AS_F32(iz);
	/* log(x) = log1p(z/c-1) + log(c) + k*__data_log_f32.ln2 */
	r = z * invc - 1;
	y0 = logc + (t_f64)k * __data_log_f32.ln2;
	/* Pipelined polynomial evaluation to approximate log1p(r). */
	r2 = r * r;
	y = __data_log_f32.poly[1] * r + __data_log_f32.poly[2];
	y = __data_log_f32.poly[0] * r2 + y;
	y = y * r2 + (y0 + r);
	return (t_f32)(y);
}



/* Top 16 bits of a t_f64. */
static inline
t_u32	top16(t_f64 x)
{
	return AS_U64(x) >> 48;
}

t_f64	F64_Log(t_f64 x)
{
	static const t_u64 OFF = 0x3fe6000000000000;
	t_f64 w, z, r, r2, r3, y, invc, logc, kd, hi, lo;
	t_u64 ix, iz, tmp;
	t_u32 top;
	int k, i;

	ix = AS_U64(x);
	top = top16(x);
	if (predict_false(ix - AS_U64(1.0 - 0x1p-4) < AS_U64(1.0 + 0x1.09p-4) - AS_U64(1.0 - 0x1p-4)))
	{
		/* Handle close to 1.0 inputs separately. */
		/* Fix sign of zero with downward rounding when x==1. */
		if (WANT_ROUNDING && predict_false(ix == AS_U64(1.0)))
			return 0;
		r = x - 1.0;
		r2 = r * r;
		r3 = r * r2;
		y = r3 * (__data_log_f64.poly1[1] + r * __data_log_f64.poly1[2] + r2 * __data_log_f64.poly1[3] +
			r3 * (__data_log_f64.poly1[4] + r * __data_log_f64.poly1[5] + r2 * __data_log_f64.poly1[6] +
			r3 * (__data_log_f64.poly1[7] + r * __data_log_f64.poly1[8] + r2 * __data_log_f64.poly1[9] +
			r3 * (__data_log_f64.poly1[10]))));
		/* Worst-case error is around 0.507 ULP. */
		w = r * 0x1p27;
		t_f64 rhi = r + w - w;
		t_f64 rlo = r - rhi;
		w = rhi * rhi * __data_log_f64.poly1[0]; /* __data_log_f64.poly1[0] == -0.5. */
		hi = r + w;
		lo = r - hi + w;
		lo += __data_log_f64.poly1[0] * rlo * (rhi + r);
		y += lo;
		y += hi;
		return (t_f64)(y);
	}
	if (predict_false(top - 0x0010 >= 0x7ff0 - 0x0010))
	{
		/* x < 0x1p-1022 or inf or nan. */
		if (ix * 2 == 0)
			return __math_divzero(1);
		if (ix == AS_U64(INFINITY)) /* log(inf) == inf. */
			return x;
		if ((top & 0x8000) || (top & 0x7ff0) == 0x7ff0)
			return __math_invalid(x);
		/* x is subnormal, normalize it. */
		ix = AS_U64(x * 0x1p52);
		ix -= (t_u64)F64_MANTISSA_BITS << F64_MANTISSA_BITS;
	}
	/*
	x = 2^k z; where z is in range [OFF,2*OFF) and exact.
	The range is split into N subintervals.
	The ith subinterval contains z and c is near its center.
	*/
	tmp = ix - OFF;
	i = (tmp >> (F64_MANTISSA_BITS - TABLEBITS_EXP_F64)) % N_EXP_F64;
	k = (t_s64)tmp >> F64_MANTISSA_BITS; /* arithmetic shift */
	iz = ix - (tmp & 0xfffULL << F64_MANTISSA_BITS);
	invc = __data_log_f64.table[i].invc;
	logc = __data_log_f64.table[i].logc;
	z = AS_F64(iz);
	/* log(x) = log1p(z/c-1) + log(c) + k*Ln2. */
	/* r ~= z/c - 1, |r| < 1/(2*N). */
#if __FP_FAST_FMA
	/* rounding error: 0x1p-55/N. */
	r = __builtin_fma(z, invc, -1.0);
#else
	/* rounding error: 0x1p-55/N + 0x1p-66. */
	r = (z - __data_log_f64.table2[i].chi - __data_log_f64.table2[i].clo) * invc;
#endif
	kd = (t_f64)k;
	/* hi + lo = r + log(c) + k*Ln2. */
	w = kd * __data_log_f64.ln2hi + logc;
	hi = w + r;
	lo = w - hi + r + kd * __data_log_f64.ln2lo;
	/* log(x) = lo + (log1p(r) - r) + hi. */
	r2 = r * r; /* rounding error: 0x1p-54/N^2. */
	/*
	Worst case error if |y| > 0x1p-5:
	0.5 + 4.13/N + abs-poly-error*2^57 ULP (+ 0.002 ULP without fma)
	Worst case error if |y| > 0x1p-4:
	0.5 + 2.06/N + abs-poly-error*2^56 ULP (+ 0.001 ULP without fma).
	*/
	y = lo + r2 *
		__data_log_f64.poly[0] + r * r2 * (
		__data_log_f64.poly[1] + r *
		__data_log_f64.poly[2] + r2 * (
		__data_log_f64.poly[3] + r *
		__data_log_f64.poly[4])) + hi;
	return (t_f64)(y);
}

/*!
**	Natural logarithm, t_f80 precision
**
**
**	SYNOPSIS:
**
**	t_f80 x, y, logl();
**
**	y = logl( x );
**
**
**	DESCRIPTION:
**
**	Returns the base e (2.718...) logarithm of x.
**
**	The argument is separated into its exponent and fractional parts.
**	If the exponent is between -1 and +1, the logarithm of the fraction is approximated by
**
**		log(1+x) = x - 0.5 x**2 + x**3 P(x)/Q(x).
**
**	Otherwise, setting  z = 2(x-1)/(x+1),
**
**		log(x) = log(1+z/2) - log(1-z/2) = z + z**3 P(z)/Q(z).
**
**
**	ACCURACY:
**
**		Relative error:
**	arithmetic   domain     # trials      peak         rms
**		IEEE      0.5, 2.0    150000      8.71e-20    2.75e-20
**		IEEE     exp(+-10000) 100000      5.39e-20    2.34e-20
**
**	In the tests over the interval exp(+-10000), the logarithms
**	of the random arguments were uniformly distributed over
**	[-10000, +10000].
*/

#define DEFINEFUNC_FLOAT_LN(BITS) \
t_f##BITS	F##BITS##_Log(t_f##BITS x) \
{ \
	t_f##BITS y, z; \
	int e; \
 \
	if (IS_NAN(x)) \
		return x; \
	if (x == INFINITY) \
		return x; \
	if (x <= 0.0) \
	{ \
		if (x == 0.0) \
			return -1/(x*x); /* -inf with divbyzero */ \
		return 0/0.0f; /* nan with invalid */ \
	} \
	/* separate mantissa from exponent */ \
	/* Note, frexp is used so that denormal numbers will be handled properly. */ \
	x = F##BITS##_SplitExp(x, &e); \
	/* logarithm using log(x) = z + z**3 P(z)/Q(z), where z = 2(x-1)/(x+1) */ \
	if (e > 2 || e < -2) \
	{ \
		if (x < __data_log_f##BITS.SQRTH) /* 2(2x-1)/(2x+1) */ \
		{ \
			e -= 1; \
			z = x - 0.5; \
			y = 0.5 * z + 0.5; \
		} \
		else /* 2 (x-1)/(x+1) */ \
		{ \
			z = x - 0.5; \
			z -= 0.5; \
			y = 0.5 * x  + 0.5; \
		} \
		x = z / y; \
		z = x*x; \
		z = x * (z * __polynomial_f##BITS(z, __data_log_f##BITS.R, 3) / __polynomial_f##BITS(z, __data_log_f##BITS.S, 3)); \
		z = z + e * __data_log_f##BITS.C2; \
		z = z + x; \
		z = z + e * __data_log_f##BITS.C1; \
		return z; \
	} \
	/* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */ \
	if (x < __data_log_f##BITS.SQRTH) \
	{ \
		e -= 1; \
		x = 2.0 * x - 1.0; \
	} \
	else \
	{ \
		x = x - 1.0; \
	} \
	z = x*x; \
	y = x * (z * __polynomial_f##BITS(x, __data_log_f##BITS.P, 6) / __polynomial_f##BITS(x, __data_log_f##BITS.Q, 6)); \
	y = y + e * __data_log_f##BITS.C2; \
	z = y - 0.5 * z; \
	/* Note, the sum of above terms does not exceed x/4, so it contributes at most about 1/4 lsb to the error. */ \
	z = z + x; \
	z = z + e * __data_log_f##BITS.C1; /* This sum has an error of 1/2 lsb. */ \
	return z; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LN(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LN(128)
#endif

#endif
