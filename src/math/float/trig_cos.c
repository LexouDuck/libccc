
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Cos, cos)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_COS(BITS) \
t_f##BITS	F##BITS##_Cos(t_f##BITS x) \
{ \
	t_f##BITS	result; \
	t_bool		sign; /* `TRUE` for negative */ \
	t_f##BITS	x_pow2; \
	t_f##BITS	x_pow4; \
	t_f##BITS	x_pow6; \
	t_f##BITS	x_pow8; \
	t_f##BITS	x_pow10; \
	t_f##BITS	x_pow12; \
	t_f##BITS	x_pow14; \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	sign = 0; \
	if (x < 0.) \
		x = -x; \
	if (x > TAU) \
		x = F##BITS##_Mod(x, TAU); \
	if (x > PI) \
		x = PI - (x - PI); \
	if (x > PI_HALF) \
	{ \
		x = PI_HALF - (x - PI_HALF); \
		sign = -1; \
	} \
	x_pow2  = x * x; \
	x_pow4  = x_pow2 * x_pow2; \
	x_pow6  = x_pow4 * x_pow2; \
	x_pow8  = x_pow4 * x_pow4; \
	x_pow10 = x_pow8 * x_pow2; \
	x_pow12 = x_pow8 * x_pow4; \
	x_pow14 = x_pow8 * x_pow6; \
	result = 1.; \
	result -= x_pow2  * __inv_factorial(2); \
	result += x_pow4  * __inv_factorial(4); \
	result -= x_pow6  * __inv_factorial(6); \
	result += x_pow8  * __inv_factorial(8); \
	result -= x_pow10 * __inv_factorial(10); \
	result += x_pow12 * __inv_factorial(12); \
	result -= x_pow14 * __inv_factorial(14); \
	return (sign ? -result : result); \
} \

DEFINEFUNC_FLOAT_COS(32)
DEFINEFUNC_FLOAT_COS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COS(128)
#endif



#else

/*! cos(x)
**	Return cosine function of x.
**
**	kernel function:
**		__sin           ... sine function on [-pi/4,pi/4]
**		__cos           ... cosine function on [-pi/4,pi/4]
**		__rem_pi2_      ... argument reduction routine
**
**	Method.
**		Let S,C and T denote the sin, cos and tan respectively on
**		[-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
**		in [-pi/4 , +pi/4], and let n = k mod 4.
**		We have
**
**		| n |sin(x)|cos(x)|tan(x)|
**		|---|------|------|------|
**		| 0 | +sin | +cos | +tan |
**		| 1 | +cos | -sin |-1/tan|
**		| 2 | -sin | -cos | +tan |
**		| 3 | -cos | +sin |-1/tan|
**		|---|------|------|------|
**
**	Special cases:
**		Let trig be any of sin, cos, or tan.
**		trig(+-INF)  is NaN, with signals;
**		trig(NaN)    is that NaN;
**
**	Accuracy:
**		TRIG(x) returns trig(x) nearly rounded
*/

t_f32	F32_Cos(t_f32 x)
{
	/* Small multiples of pi/2 rounded to t_f64 precision. */
	static const t_f64 c1pio2 = 1*PI_HALF; /* 0x3FF921FB, 0x54442D18 */
	static const t_f64 c2pio2 = 2*PI_HALF; /* 0x400921FB, 0x54442D18 */
	static const t_f64 c3pio2 = 3*PI_HALF; /* 0x4012D97C, 0x7F3321D2 */
	static const t_f64 c4pio2 = 4*PI_HALF; /* 0x401921FB, 0x54442D18 */
	t_f64 y;
	t_u32 ix;
	t_uint n, sign;

	ix = AS_U32(x);
	sign = ix >> 31;
	ix &= 0x7FFFFFFF;
	if (ix <= 0x3F490FDA) /* |x| ~<= pi/4 */
	{
		if (ix < 0x39800000) /* |x| < 2**-12 */
		{
			/* raise inexact if x != 0 */
			/*FORCE_EVAL(x + 0x1p120f);*/
			return 1.0f;
		}
		return +__cos_f32(x);
	}
	if (ix <= 0x407B53D1) /* |x| ~<= 5*pi/4 */
	{
		if (ix > 0x4016CBE3) /* |x|  ~> 3*pi/4 */
			return -__cos_f32(sign ? x+c2pio2 : x-c2pio2);
		else
		{
			if (sign)
				return +__sin_f32(x + c1pio2);
			else
				return +__sin_f32(c1pio2 - x);
		}
	}
	if (ix <= 0x40E231D5) /* |x| ~<= 9*pi/4 */
	{
		if (ix > 0x40AFEDDF) /* |x| ~> 7*pi/4 */
			return +__cos_f32(sign ? x+c4pio2 : x-c4pio2);
		else
		{
			if (sign)
				return +__sin_f32(-x - c3pio2);
			else
				return +__sin_f32(+x - c3pio2);
		}
	}
	/* cos(Inf or NaN) is NaN */
	if (ix >= F32_EXPONENT)
		return x - x;
	/* general argument reduction needed */
	n = __rem_pi2_f32(x, &y);
	switch (n&3)
	{
		case 0: return +__cos_f32(+y);
		case 1: return +__sin_f32(-y);
		case 2: return -__cos_f32(+y);
		case 3:	return +__sin_f32(+y);
		default:
			return NAN;
	}
}

t_f64	F64_Cos(t_f64 x)
{
	t_f64 y[2];
	t_u32 ix;
	unsigned n;
	/* High word of x. */
	ix = AS_U64(x) >> 32;
	ix &= 0x7FFFFFFF;
	if (ix <= 0x3FE921FB) /* |x| ~< pi/4 */
	{
		if (ix < 0x3E46A09E) /* |x| < 2**-27 * sqrt(2) */
		{
			/* raise inexact if x!=0 */
			/*FORCE_EVAL(x + 0x1p120f);*/
			return 1.0;
		}
		return __cos_f64(x, 0);
	}
	/* cos(Inf or NaN) is NaN */
	if (ix >= 0x7FF00000)
		return x - x;
	/* argument reduction needed */
	n = __rem_pi2_f64(x, y);
	switch (n&3)
	{
		case 0: return +__cos_f64(y[0], y[1]);
		case 1: return -__sin_f64(y[0], y[1], 1);
		case 2: return -__cos_f64(y[0], y[1]);
		case 3:	return +__sin_f64(y[0], y[1], 1);
		default:
			return NAN;
	}
}

#define DEFINEFUNC_FLOAT_COS(BITS) \
t_f##BITS	F##BITS##_Cos(t_f##BITS x) \
{ \
	union ldshape	u = {x}; \
	unsigned n; \
	t_f80 y[2], hi, lo; \
 \
	u.i.se &= 0x7FFF; \
	if (u.i.se == 0x7FFF) \
		return x - x; \
	x = u.f; \
	if (x < PI_QUARTER) \
	{ \
		if (u.i.se < 0x3FFF - F##BITS##_MANTISSA_BITS) \
		{ \
			/* raise inexact if x!=0 */ \
			return 1.0 + x; \
		} \
		return __cos_f128(x, 0); \
	} \
	n = __rem_pi2_f128(x, y); \
	hi = y[0]; \
	lo = y[1]; \
	switch (n & 3) \
	{ \
		case 0:	return +__cos_f128(hi, lo); \
		case 1:	return -__sin_f128(hi, lo, 1); \
		case 2:	return -__cos_f128(hi, lo); \
		case 3:	return +__sin_f128(hi, lo, 1); \
		default: \
			return NAN; \
	} \
} \

//DEFINEFUNC_FLOAT_COS(32)
//DEFINEFUNC_FLOAT_COS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COS(128)
#endif

#endif
