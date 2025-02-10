
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(NextAfter, nextafter)
#else
#define DEFINEFUNC_FLOAT_NEXTAFTER(BITS) \
t_f##BITS	F##BITS##_NextAfter(t_f##BITS x, t_f##BITS y) \
{ \
	u_cast_f##BITS ux = {x}; \
	u_cast_f##BITS uy = {y}; \
	t_u##BITS ax; \
	t_u##BITS ay; \
	if (F##BITS##_IsNaN(x) || F##BITS##_IsNaN(y)) \
		return (x + y); \
	if (ux.as_u == uy.as_u) \
		return y; \
	ax = ux.as_u & (t_u##BITS)-1 / 2; \
	ay = uy.as_u & (t_u##BITS)-1 / 2; \
	if (ax == 0) \
	{ \
		if (ay == 0) \
			return (y); \
		ux.as_u = (uy.as_u & (t_u##BITS)1 << (BITS - 1)) | 1; \
	} \
	else if (ax > ay || ((ux.as_u ^ uy.as_u) & (t_u##BITS)1 << (BITS - 1))) \
		ux.as_u--; \
	else \
		ux.as_u++; \
	/* t_s##BITS e; */ \
	/* e = ux.as_u & F##BITS##_EXPONENT_MASK; */ \
	/* // raise overflow if ux.as_f is infinite and x is finite */ \
	/* if (e == F##BITS##_EXPONENT_MASK)	FORCE_EVAL(x + x); */ \
	/* // raise underflow if ux.as_f is subnormal or zero */ \
	/* if (e == 0)	FORCE_EVAL(x * x + ux.as_f * ux.as_f); */ \
	return (ux.as_f); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_NEXTAFTER(16)
#endif
DEFINEFUNC_FLOAT_NEXTAFTER(32)

DEFINEFUNC_FLOAT_NEXTAFTER(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_NEXTAFTER(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_NEXTAFTER(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(NearbyInt, rint)
#else
#define DEFINEFUNC_FLOAT_NEARBYINT(BITS) \
t_f##BITS F##BITS##_NearbyInt(t_f##BITS x) \
{ \
	static const t_f##BITS toint = 1. / F##BITS##_EPSILON; \
	u_cast_f##BITS u = {x}; \
	t_u##BITS e = (u.as_u >> F##BITS##_MANTISSA_BITS) & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	t_u##BITS s = (u.as_u >> (BITS - 1)); \
	t_f##BITS y; \
	if (e >= ((1 << (F##BITS##_EXPONENT_BITS - 1)) - 1) + F##BITS##_MANTISSA_BITS) \
		return (x); \
	if (s) \
		y = x - toint + toint; \
	else \
		y = x + toint - toint; \
	if (y == 0) \
		return (s ? (t_f##BITS)-0. : (t_f##BITS)+0.); \
	return (y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_NEARBYINT(16)
#endif
DEFINEFUNC_FLOAT_NEARBYINT(32)

DEFINEFUNC_FLOAT_NEARBYINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_NEARBYINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_NEARBYINT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_FUNCTION(t_sint, ToInt, lrint)
#else
#define DEFINEFUNC_FLOAT_TOINT(BITS) \
_INLINE() \
t_sint	F##BITS##_ToInt(t_f##BITS x) \
{ \
	return F##BITS##_NearbyInt(x); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_TOINT(16)
#endif
DEFINEFUNC_FLOAT_TOINT(32)

DEFINEFUNC_FLOAT_TOINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TOINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TOINT(128)
#endif

#endif
