
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(SinH, sinh)
#elif LIBCONFIG_USE_CCC_MATH
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 0.96	for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_SINH(BITS) \
t_f##BITS	F##BITS##_SinH(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x == 0) \
		return (0); \
	else if (x < -PI)	return (-F##BITS##_Exp(-x - LN_2)); \
	else if (x > +PI)	return (+F##BITS##_Exp(+x - LN_2)); \
	t_f##BITS result = x; \
	t_f##BITS power = x * x * x; \
	result += (0.1666666666 * power);	power *= (x * x); \
	result += (0.0083333333 * power);	power *= (x * x); \
	result += (0.0001500000 * power);	power *= (x * x); \
	result += (0.0000083000 * power); \
	return (result); \
} \

DEFINEFUNC_FLOAT_SINH(32)
DEFINEFUNC_FLOAT_SINH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SINH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SINH(128)
#endif



#else



/* sinh(x) = (exp(x) - 1/exp(x))/2
**         = (exp(x)-1 + (exp(x)-1)/exp(x))/2
**         = x + x^3/6 + o(x^5)
*/

t_f32	F32_SinH(t_f32 x)
{
	union {t_f32 f; t_u32 i;} u = {.f = x};
	t_u32 w;
	t_f32 t, h, absx;

	h = 0.5;
	if (u.i >> 31)
		h = -h;
	/* |x| */
	u.i &= 0x7fffffff;
	absx = u.f;
	w = u.i;
	/* |x| < log(FLT_MAX) */
	if (w < 0x42b17217)
	{
		t = F32_Exp(absx) - 1.;
		if (w < 0x3f800000)
		{
			if (w < 0x3f800000 - (12<<23))
				return x;
			return h*(2*t - t*t/(t+1));
		}
		return h*(t + t/(t+1));
	}

	/* |x| > logf(FLT_MAX) or nan */
	t = __expo2_f32(absx, 2*h);
	return t;
}

t_f64	F64_SinH(t_f64 x)
{
	union {t_f64 f; t_u64 i;} u = {.f = x};
	t_u32 w;
	t_f64 t, h, absx;

	h = 0.5;
	if (u.i >> 63)
		h = -h;
	/* |x| */
	u.i &= (t_u64)-1/2;
	absx = u.f;
	w = u.i >> 32;
	/* |x| < log(DBL_MAX) */
	if (w < 0x40862e42)
	{
		t = F64_Exp(absx) - 1.;
		if (w < 0x3ff00000)
		{
			if (w < 0x3ff00000 - (26<<20))
				/* note: inexact and underflow are raised by expm1 */
				/* note: this branch avoids spurious underflow */
				return x;
			return h*(2*t - t*t/(t+1));
		}
		/* note: |x|>log(0x1p26)+eps could be just h*exp(x) */
		return h*(t + t/(t+1));
	}

	/* |x| > log(DBL_MAX) or nan */
	/* note: the result is stored to handle overflow */
	t = __expo2_f64(absx, 2*h);
	return t;
}

#define DEFINEFUNC_FLOAT_SINH(BITS) \
t_f##BITS	F##BITS##_SinH(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	unsigned ex = u.i.se & 0x7fff; \
	t_f##BITS h, t, absx; \
 \
	h = 0.5; \
	if (u.i.se & 0x8000) \
		h = -h; \
	/* |x| */ \
	u.i.se = ex; \
	absx = u.f; \
	/* |x| < log(LDBL_MAX) */ \
	if (ex < 0x3fff+13 || (ex == 0x3fff+13 && u.i.m>>32 < 0xb17217f7)) \
	{ \
		t = F##BITS##_Exp(absx) - 1.; \
		if (ex < 0x3fff) \
		{ \
			if (ex < 0x3fff-32) \
				return x; \
			return h*(2*t - t*t/(1+t)); \
		} \
		return h*(t + t/(t+1)); \
	} \
	/* |x| > log(LDBL_MAX) or nan */ \
	t = F##BITS##_Exp(0.5*absx); \
	return h*t*t; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SINH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SINH(128)
#endif

#endif
