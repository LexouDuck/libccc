
#include "libccc/math.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvTanH, atanh)
#elif LIBCONFIG_USE_CCC_MATH
// taylor series approximation
// score: 4.81	for [-1,+1]-> 200 tests
#define DEFINEFUNC_FLOAT_INVTANH(BITS) \
t_f##BITS	F##BITS##_InvTanH(t_f##BITS x) \
{ \
	static const t_f##BITS p = 0.6232; \
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL) \
		return (NAN); \
	if CCCERROR((F##BITS##_Abs(x) > 1.), ERROR_MATHDOMAIN, NULL) \
		return (NAN); \
	if (x == 0) \
		return (0); \
	if (x < -0.6)	return (+F##BITS##_Log(p * +x + p) * 0.5); \
	if (x > +0.6)	return (-F##BITS##_Log(p * -x + p) * 0.5); \
	t_f##BITS result = x / (1 - 0.418 * F##BITS##_Abs(x)); \
	t_f##BITS power = x * x * x; \
	result += (-1.5 * power);	power *= (x * x); \
	result += (+4.4 * power);	power *= (x * x); \
	result += (-2.4 * power);	power *= (x * x); \
	result += (-5.8 * power); \
	return (result); \
} \

DEFINEFUNC_FLOAT_INVTANH(32)
DEFINEFUNC_FLOAT_INVTANH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVTANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVTANH(128)
#endif



#else

/* atanh(x) = log((1+x)/(1-x))/2 = log1p(2x/(1-x))/2 ~= x + x^3/3 + o(x^5) */
/* atanh(x) = log((1+x)/(1-x))/2 = log1p(2x/(1-x))/2 ~= x + x^3/3 + o(x^5) */
/* atanh(x) = log((1+x)/(1-x))/2 = log1p(2x/(1-x))/2 ~= x + x^3/3 + o(x^5) */

t_f32	F32_InvTanH(t_f32 x)
{
	union {t_f32 f; t_u32 i;} u = {.f = x};
	unsigned s = u.i >> 31;
	t_f32 y;

	/* |x| */
	u.i &= 0x7fffffff;
	y = u.f;

	if (u.i < 0x3f800000 - (1<<23))
	{
		if (u.i < 0x3f800000 - (32<<23))
		{
			/* handle underflow */
			if (u.i < (1<<23))
				{}/*FORCE_EVAL((t_f32)(y*y));*/
		}
		else
		{
			/* |x| < 0.5, up to 1.7ulp error */
			y = 0.5f*F32_Log(1 + (2*y + 2*y*y/(1-y)));
		}
	}
	else
	{
		/* avoid overflow */
		y = 0.5f*F32_Log(1 + (2*(y/(1-y))));
	}
	return s ? -y : y;
}

t_f64	F64_InvTanH(t_f64 x)
{
	union {t_f64 f; t_u64 i;} u = {.f = x};
	unsigned e = u.i >> 52 & 0x7ff;
	unsigned s = u.i >> 63;
	t_f64 y;

	/* |x| */
	u.i &= (t_u64)-1/2;
	y = u.f;
	if (e < 0x3ff - 1)
	{
		if (e < 0x3ff - 32)
		{
			/* handle underflow */
			if (e == 0)
				{}/*FORCE_EVAL((t_f32)y);*/
		}
		else
		{
			/* |x| < 0.5, up to 1.7ulp error */
			y = 0.5*F64_Log(1 + (2*y + 2*y*y/(1-y)));
		}
	}
	else
	{
		/* avoid overflow */
		y = 0.5*F64_Log(1 + (2*(y/(1-y))));
	}
	return s ? -y : y;
}

#define DEFINEFUNC_FLOAT_INVTANH(BITS) \
t_f##BITS	F##BITS##_InvTanH(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	unsigned e = u.i.se & 0x7fff; \
	unsigned s = u.i.se >> 15; \
 \
	/* |x| */ \
	u.i.se = e; \
	x = u.f; \
	if (e < 0x3ff - 1) \
	{ \
		if (e < 0x3ff - LDBL_MANT_DIG/2) \
		{ \
			/* handle underflow */ \
			if (e == 0) \
				{}/*FORCE_EVAL((t_f32)x);*/ \
		} \
		else \
		{ \
			/* |x| < 0.5, up to 1.7ulp error */ \
			x = 0.5*F##BITS##_Log(1 + (2*x + 2*x*x/(1-x))); \
		} \
	} \
	else \
	{ \
		/* avoid overflow */ \
		x = 0.5*F##BITS##_Log(1 + (2*(x/(1-x)))); \
	} \
	return s ? -x : x; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVTANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVTANH(128)
#endif

#endif
