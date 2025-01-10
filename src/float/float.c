
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
	if (IS_NAN(x) || IS_NAN(y)) \
		return (x + y); \
	if (ux.value_uint == uy.value_uint) \
		return y; \
	ax = ux.value_uint & (t_u##BITS)-1 / 2; \
	ay = uy.value_uint & (t_u##BITS)-1 / 2; \
	if (ax == 0) \
	{ \
		if (ay == 0) \
			return (y); \
		ux.value_uint = (uy.value_uint & (t_u##BITS)1 << (BITS - 1)) | 1; \
	} \
	else if (ax > ay || ((ux.value_uint ^ uy.value_uint) & (t_u##BITS)1 << (BITS - 1))) \
		ux.value_uint--; \
	else \
		ux.value_uint++; \
	/* t_s##BITS e; */ \
	/* e = ux.value_uint & F##BITS##_EXPONENT; */ \
	/* // raise overflow if ux.value_float is infinite and x is finite */ \
	/* if (e == F##BITS##_EXPONENT)	FORCE_EVAL(x + x); */ \
	/* // raise underflow if ux.value_float is subnormal or zero */ \
	/* if (e == 0)	FORCE_EVAL(x * x + ux.value_float * ux.value_float); */ \
	return (ux.value_float); \
} \

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
	t_u##BITS e = (u.value_uint >> F##BITS##_MANTISSA_BITS) & ((1 << F##BITS##_EXPONENT_BITS) - 1); \
	t_u##BITS s = (u.value_uint >> (BITS - 1)); \
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
t_sint	F##BITS##_ToInt(t_f##BITS x) \
{ \
	u_cast_f64 u = {(t_f64)x}; \
	t_u32 abstop = u.value_uint >> 32 & 0x7FFFFFFF; \
	t_u64 sign = u.value_uint & ((t_u64)1 << 63); \
	if (abstop < 0x41DFFFFF) \
	{ \
		/* |x| < 0x7FFFFC00, no overflow */ \
		u.value_float = 1. / F64_EPSILON; \
		u.value_uint |= sign; \
		t_f64 toint = u.value_float; \
		t_f64 y = x + toint - toint; \
		return ((t_sint)y); \
	} \
	return F##BITS##_NearbyInt(x); \
} \

DEFINEFUNC_FLOAT_TOINT(32)
DEFINEFUNC_FLOAT_TOINT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TOINT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TOINT(128)
#endif

#endif
