
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

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_INVTANH(16)
#endif
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

#define DEFINEFUNC_FLOAT_INVTANH(BITS) \
t_f##BITS	F##BITS##_InvTanH(t_f##BITS x) \
{ \
	u_cast_f##BITS u = {x}; \
	t_uint exp = (u.as_u & F##BITS##_EXPONENT_MASK) >> F##BITS##_MANTISSA_BITS; \
	t_bool sign = (u.as_u >> (BITS - 1)); \
	/* |x| */ \
	u.as_u &= (~(t_u##BITS)0 >> 1); \
	x = u.as_f; \
	if (exp < (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) - 1) \
	{ \
		if (exp < (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) - 32) /* |x| < 2^-32 */ \
		{	/* handle underflow */ \
			if (exp == 0) \
			{}	/*FORCE_EVAL((t_f32)x);*/ \
		} \
		else if (exp < (F##BITS##_EXPONENT_ZERO >> F##BITS##_MANTISSA_BITS) - 15) /* |x| < 2^-15 */ \
		{ \
			x = 0.5 * F64_Log(1 + (2 * (t_f64)x + 2 * (t_f64)x*x / (1 - x))); \
		} \
		else /* |x| < 0.5, up to 1.7ulp error */ \
		{ \
			x = 0.5 * F##BITS##_Log(1 + (2 * x + 2 * x*x / (1 - x))); \
		} \
	} \
	else /* avoid overflow */ \
	{ \
		x = 0.5 * F##BITS##_Log(1 + (2 * (x / (1 - x)))); \
	} \
	return (sign ? -x : x); \
} \

DEFINEFUNC_FLOAT_INVTANH(32)
DEFINEFUNC_FLOAT_INVTANH(64)

#define DEFINEFUNC_FLOAT_INVTANH_LD(BITS) \
t_f##BITS	F##BITS##_InvTanH(t_f##BITS x) \
{ \
	union ldshape u = {x}; \
	unsigned e = u.i.se & 0x7fff; \
	unsigned s = u.i.se >> 15; \
	/* |x| */ \
	u.i.se = e; \
	x = u.f; \
	if (e < 0x3ff - 1) \
	{ \
		if (e < 0x3ff - LDBL_MANT_DIG/2) \
		{	/* handle underflow */ \
			if (e == 0) \
			{}	/*FORCE_EVAL((t_f32)x);*/ \
		} \
		else /* |x| < 0.5, up to 1.7ulp error */ \
		{ \
			x = 0.5 * F##BITS##_Log(1 + (2*x + 2*x*x/(1-x))); \
		} \
	} \
	else /* avoid overflow */ \
	{ \
		x = 0.5 * F##BITS##_Log(1 + (2*(x/(1-x)))); \
	} \
	return s ? -x : x; \
} \

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVTANH_LD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVTANH_LD(128)
#endif

#endif
