
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(CosH, cosh)
#elif LIBCONFIG_USE_CCC_MATH
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 1.63	for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_COSH(BITS) \
t_f##BITS	F##BITS##_CosH(t_f##BITS x) \
{ \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if (x == 0) \
		return (1); \
	else if (x < -3.2457)	return (F##BITS##_Exp(-x - LN_2)); \
	else if (x > +3.2457)	return (F##BITS##_Exp(+x - LN_2)); \
	t_f##BITS result = 1.0; \
	t_f##BITS power = x * x; \
	result += (0.5000000000 * power);	power *= power; \
	result += (0.0416666666 * power);	power *= x * x; \
	result += (0.0016666666 * power); \
	return (result); \
} \

DEFINEFUNC_FLOAT_COSH(32)
DEFINEFUNC_FLOAT_COSH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COSH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COSH(128)
#endif



#else



/* cosh(x) = (exp(x) + 1/exp(x))/2
**         = 1 + 0.5*(exp(x)-1)*(exp(x)-1)/exp(x)
**         = 1 + x*x/2 + o(x^4)
*/

t_f32	F32_CosH(t_f32 x)
{
	union {t_f32 f; t_u32 i;} u = {.f = x};
	t_u32 w;
	t_f32 t;

	/* |x| */
	u.i &= 0x7fffffff;
	x = u.f;
	w = u.i;
	/* |x| < log(2) */
	if (w < 0x3f317217)
	{
		if (w < 0x3f800000 - (12<<23))
		{
			/*FORCE_EVAL(x + 0x1p120f);*/
			return 1;
		}
		t = F32_Exp(x) - 1.;
		return 1 + t*t/(2*(1+t));
	}
	/* |x| < log(FLT_MAX) */
	if (w < 0x42b17217)
	{
		t = F32_Exp(x);
		return 0.5f*(t + 1/t);
	}
	/* |x| > log(FLT_MAX) or nan */
	t = __expo2_f32(x, 1.0f);
	return t;
}

t_f64	F64_CosH(t_f64 x)
{
	union {t_f64 f; t_u64 i;} u = {.f = x};
	t_u32 w;
	t_f64 t;

	/* |x| */
	u.i &= (t_u64)-1/2;
	x = u.f;
	w = u.i >> 32;
	/* |x| < log(2) */
	if (w < 0x3fe62e42)
	{
		if (w < 0x3ff00000 - (26<<20))
		{
			/* raise inexact if x!=0 */
			/*FORCE_EVAL(x + 0x1p120f);*/
			return 1;
		}
		t = F64_Exp(x) - 1.;
		return 1 + t*t/(2*(1+t));
	}
	/* |x| < log(DBL_MAX) */
	if (w < 0x40862e42)
	{
		t = F64_Exp(x);
		/* note: if x>log(0x1p26) then the 1/t is not needed */
		return 0.5*(t + 1/t);
	}
	/* |x| > log(DBL_MAX) or nan */
	/* note: the result is stored to handle overflow */
	t = __expo2_f64(x, 1.0);
	return t;
}

#define DEFINEFUNC_FLOAT_COSH(BITS) \
t_f##BITS	F##BITS##_CosH(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	unsigned ex = u.i.se & 0x7fff; \
	t_u32 w; \
	t_f##BITS t; \
 \
	/* |x| */ \
	u.i.se = ex; \
	x = u.f; \
	w = u.i.m >> 32; \
	/* |x| < log(2) */ \
	if (ex < 0x3fff-1 || (ex == 0x3fff-1 && w < 0xb17217f7)) \
	{ \
		if (ex < 0x3fff-32) \
		{ \
			/*FORCE_EVAL(x + 0x1p120f);*/ \
			return 1; \
		} \
		t = F##BITS##_Exp(x) - 1.; \
		return 1 + t*t/(2*(1+t)); \
	} \
	/* |x| < log(LDBL_MAX) */ \
	if (ex < 0x3fff+13 || (ex == 0x3fff+13 && w < 0xb17217f7)) \
	{ \
		t = F##BITS##_Exp(x); \
		return 0.5*(t + 1/t); \
	} \
	/* |x| > log(LDBL_MAX) or nan */ \
	t = F##BITS##_Exp(0.5*x); \
	return 0.5*t*t; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COSH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COSH(128)
#endif

#endif
