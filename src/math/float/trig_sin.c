
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Sin, sin)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_SIN(BITS) \
t_f##BITS	F##BITS##_Sin(t_f##BITS x) \
{ \
	t_f##BITS	result; \
	t_bool		sign; /* `TRUE` for negative */ \
	t_f##BITS	x_pow2; \
	t_f##BITS	x_pow3; \
	t_f##BITS	x_pow5; \
	t_f##BITS	x_pow7; \
	t_f##BITS	x_pow9; \
	t_f##BITS	x_pow11; \
	t_f##BITS	x_pow13; \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	sign = 0; \
	if (x < 0.) \
	{ \
		x = -x; \
		sign = !sign; \
	} \
	if (x > TAU) \
		x = F##BITS##_Mod(x, TAU); \
	if (x > PI) \
	{ \
		x = PI - (x - PI); \
		sign = !sign; \
	} \
	if (x > PI_HALF) \
		x = PI_HALF - (x - PI_HALF); \
	x_pow2  = x * x; \
	x_pow3  = x * x_pow2; \
	x_pow5  = x_pow2 * x_pow3; \
	x_pow7  = x_pow2 * x_pow5; \
	x_pow9  = x_pow2 * x_pow7; \
	x_pow11 = x_pow2 * x_pow9; \
	x_pow13 = x_pow2 * x_pow11; \
	result = x; \
	result -= x_pow3  * __inv_factorial(3); \
	result += x_pow5  * __inv_factorial(5); \
	result -= x_pow7  * __inv_factorial(7); \
	result += x_pow9  * __inv_factorial(9); \
	result -= x_pow11 * __inv_factorial(11); \
	result += x_pow13 * __inv_factorial(13); \
	result -= x_pow13 * x_pow2 * __inv_factorial(15); \
	return (sign ? -result : result); \
} \

DEFINEFUNC_FLOAT_SIN(32)
DEFINEFUNC_FLOAT_SIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SIN(128)
#endif



#else

/*! sin(x)
**	Return sine function of x.
**
**	kernel function:
**		__sin            ... sine function on [-pi/4,pi/4]
**		__cos            ... cose function on [-pi/4,pi/4]
**		__rem_pi2       ... argument reduction routine
**
**	Method.
**		Let S,C and T denote the sin, cos and tan respectively on
**		[-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
**		in [-pi/4 , +pi/4], and let n = k mod 4.
**		We have
**
**          n        sin(x)      cos(x)        tan(x)
**     ----------------------------------------------------------
**          0          S           C             T
**          1          C          -S            -1/T
**          2         -S          -C             T
**          3         -C           S            -1/T
**     ----------------------------------------------------------
**
**	Special cases:
**		Let trig be any of sin, cos, or tan.
**		trig(+-INF)  is NaN, with signals;
**		trig(NaN)    is that NaN;
**
**	Accuracy:
**		TRIG(x) returns trig(x) nearly rounded
*/

t_f32	F32_Sin(t_f32 x)
{
	/* Small multiples of pi/2 rounded to t_f64 precision. */
	static const t_f64 s1pio2 = 1*PI_HALF; /* 0x3FF921FB, 0x54442D18 */
	static const t_f64 s2pio2 = 2*PI_HALF; /* 0x400921FB, 0x54442D18 */
	static const t_f64 s3pio2 = 3*PI_HALF; /* 0x4012D97C, 0x7F3321D2 */
	static const t_f64 s4pio2 = 4*PI_HALF; /* 0x401921FB, 0x54442D18 */
	t_f64 y;
	t_u32 ix;
	t_sint n, sign;

	ix = AS_U32(x);
	sign = ix >> 31;
	ix &= 0x7fffffff;
	if (ix <= 0x3f490fda) /* |x| ~<= pi/4 */
	{
		if (ix < 0x39800000) /* |x| < 2**-12 */
		{
			/* raise inexact if x!=0 and underflow if subnormal */
			/*FORCE_EVAL(ix < 0x00800000 ? x/0x1p120f : x+0x1p120f);*/
			return x;
		}
		return +__sin_f32(x);
	}
	if (ix <= 0x407b53d1) /* |x| ~<= 5*pi/4 */
	{
		if (ix <= 0x4016cbe3) /* |x| ~<= 3pi/4 */
		{
			if (sign)
				return -__cos_f32(x + s1pio2, 0);
			else
				return +__cos_f32(x - s1pio2, 0);
		}
		else
			return +__sin_f32(sign ? -(x + s2pio2) : -(x - s2pio2));
	}
	if (ix <= 0x40e231d5) /* |x| ~<= 9*pi/4 */
	{
		if (ix <= 0x40afeddf) /* |x| ~<= 7*pi/4 */
		{
			if (sign)
				return +__cos_f32(x + s3pio2, 0);
			else
				return -__cos_f32(x - s3pio2, 0);
		}
		else
			return +__sin_f32(sign ? x + s4pio2 : x - s4pio2);
	}
	/* sin(Inf or NaN) is NaN */
	if (ix >= F32_EXPONENT)
		return x - x;
	/* general argument reduction needed */
	n = __rem_pi2_f32(x, &y);
	switch (n&3)
	{
		case 0:	return +__sin_f32(+y);
		case 1:	return +__cos_f32(+y, 0);
		case 2:	return +__sin_f32(-y);
		case 3:	return -__cos_f32(+y, 0);
		default:
			return NAN;
	}
}

t_f64	F64_Sin(t_f64 x)
{
	t_f64 y[2];
	t_u32 ix;
	unsigned n;
	/* High word of x. */
	ix = AS_U64(x) >> 32;
	ix &= 0x7fffffff;
	if (ix <= 0x3fe921fb) /* |x| ~< pi/4 */
	{
		if (ix < 0x3e500000) /* |x| < 2**-26 */
		{
			/* raise inexact if x != 0 and underflow if subnormal*/
			/*FORCE_EVAL(ix < 0x00100000 ? x/0x1p120f : x+0x1p120f);*/
			return x;
		}
		return __sin_f64(x, 0.0, 0);
	}
	/* sin(Inf or NaN) is NaN */
	if (ix >= 0x7ff00000)
		return x - x;
	/* argument reduction needed */
	n = __rem_pi2_f64(x, y);
	switch (n&3)
	{
		case 0:	return +__sin_f64(y[0], y[1], 1);
		case 1:	return +__cos_f64(y[0], y[1]);
		case 2:	return -__sin_f64(y[0], y[1], 1);
		case 3:	return -__cos_f64(y[0], y[1]);
		default:
			return NAN;
	}
}

#define DEFINEFUNC_FLOAT_SIN(BITS) \
t_f##BITS	F##BITS##_Sin(t_f##BITS x) \
{ \
	union ldshape	u = {x}; \
	unsigned n; \
	t_f80 y[2], hi, lo; \
 \
	u.i.se &= 0x7fff; \
	if (u.i.se == 0x7fff) \
		return x - x; \
	if (u.f < PI_QUARTER) \
	{ \
		if (u.i.se < 0x3fff - F##BITS##_MANTISSA_BITS / 2) \
		{ \
			/* raise inexact if x!=0 and underflow if subnormal */ \
			/*FORCE_EVAL(u.i.se == 0 ? x*0x1p-120f : x+0x1p120f);*/ \
			return x; \
		} \
		return __sin_f128(x, 0.0, 0); \
	} \
	n = __rem_pi2_f128(x, y); \
	hi = y[0]; \
	lo = y[1]; \
	switch (n & 3) \
	{ \
		case 0:	return +__sin_f128(hi, lo, 1); \
		case 1:	return +__cos_f128(hi, lo); \
		case 2:	return -__sin_f128(hi, lo, 1); \
		case 3:	return -__cos_f128(hi, lo); \
		default: \
			return NAN; \
	} \
} \

//DEFINEFUNC_FLOAT_SIN(32)
//DEFINEFUNC_FLOAT_SIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SIN(128)
#endif

#endif
