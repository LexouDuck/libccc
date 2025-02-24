
#include "libccc/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#ifndef FP_ILOGB0
#define FP_ILOGB0	SINT_MIN
#endif
#ifndef FP_ILOGBINF
#define FP_ILOGBINF	SINT_MAX
#endif
#ifndef FP_ILOGBNAN
#define FP_ILOGBNAN	SINT_MIN
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_FUNCTION(t_sint, GetExp2, ilogb)
#elif LIBCONFIG_USE_CCC_MATH
#define DEFINEFUNC_FLOAT_GETEXP2(BITS) \
t_sint	F##BITS##_GetExp2(t_f##BITS number) \
{ \
	u_cast_f##BITS	cast; \
	cast.as_f = number; \
	if (F##BITS##_IsNaN(number))	return (FP_ILOGBNAN); \
	if (F##BITS##_IsInf(number))	return (FP_ILOGBINF); \
	return (((cast.as_u & F##BITS##_EXPONENT_MASK) >> F##BITS##_MANTISSA_BITS) - F##BITS##_EXPONENT_BIAS); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_GETEXP2(16)
#endif
DEFINEFUNC_FLOAT_GETEXP2(32)

DEFINEFUNC_FLOAT_GETEXP2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GETEXP2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GETEXP2(128)
#endif



#else

#define DEFINEFUNC_FLOAT_GETEXP2(BITS) \
t_sint	F##BITS##_GetExp2(t_f##BITS x) \
{ \
	union {t_f##BITS f; t_u##BITS i;} u = {x}; \
	t_u##BITS i = u.i; \
	int e = (i & F##BITS##_EXPONENT_MASK) >> F##BITS##_MANTISSA_BITS; \
	if (F##BITS##_IsNaN(x))	return (FP_ILOGBNAN); \
	if (F##BITS##_IsInf(x))	return (FP_ILOGBINF); \
	if (!e) \
	{ \
		i <<= (F##BITS##_EXPONENT_BITS + 1); \
		if (i == 0) \
		{ \
			/*FORCE_EVAL(0/0.0f);*/ \
			return (FP_ILOGB0); \
		} \
		for (e = -(1<<(F##BITS##_EXPONENT_BITS-1)); (i >> (BITS-1)) == 0; e--, i<<=1); \
		return (e); \
	} \
	if (e == (1<<F##BITS##_EXPONENT_BITS)) \
	{ \
		/*FORCE_EVAL(0/0.0f);*/ \
		return (i << F##BITS##_EXPONENT_BITS) ? FP_ILOGBNAN : SINT_MAX; \
	} \
	return (e - (1<<(F##BITS##_EXPONENT_BITS - 1)) + 1); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_GETEXP2(16)
#endif
DEFINEFUNC_FLOAT_GETEXP2(32)

DEFINEFUNC_FLOAT_GETEXP2(64)

#if LIBCONFIG_USE_FLOAT80
#define DEFINEFUNC_FLOAT_GETEXP2(BITS, HANDLE_SUBNORMAL) \
t_sint	F80_GetExp2(t_f80 x) \
{ \
	union ldshape u = {x}; \
	int e = u.i.se & 0x7FFF; \
	t_u64 m = u.i.m; \
	if (!e) \
	{ \
		if (m == 0) \
		{ \
			/*FORCE_EVAL(0/0.0f);*/ \
			return (FP_ILOGB0); \
		} \
		HANDLE_SUBNORMAL \
	} \
	if (e == 0x7FFF) \
	{ \
		/*FORCE_EVAL(0/0.0f);*/ \
		return ((m << 1) ? FP_ILOGBNAN : SINT_MAX); \
	} \
	return (e - 0x3FFF); \
} \

DEFINEFUNC_FLOAT_GETEXP2(80, for (e = -0x3FFF+1; m>>63 == 0; e--, m<<=1);	return e;)

#endif

#if LIBCONFIG_USE_FLOAT128
#define DEFINEFUNC_FLOAT_GETEXP2(BITS, HANDLE_SUBNORMAL) \
t_sint	F128_GetExp2(t_f128 x) \
{ \
	union ldshape u = {x}; \
	int e = u.i.se & 0x7FFF; \
 \
	if (!e) \
	{ \
		if (x == 0) \
		{ \
			/*FORCE_EVAL(0/0.0f);*/ \
			return (FP_ILOGB0); \
		} \
		HANDLE_SUBNORMAL \
	} \
	if (e == 0x7FFF) \
	{ \
		/*FORCE_EVAL(0/0.0f);*/ \
		u.i.se = 0; \
		return (u.f ? FP_ILOGBNAN : SINT_MAX); \
	} \
	return (e - 0x3FFF); \
} \

DEFINEFUNC_FLOAT_GETEXP2(128, x *= 0x1p120;	return F128_GetExp2(x) - 120;)

#endif

#endif



#ifndef FP_ILOGD0
#define FP_ILOGD0	SINT_MIN
#endif
#ifndef FP_ILOGDINF
#define FP_ILOGDINF	SINT_MAX
#endif
#ifndef FP_ILOGDNAN
#define FP_ILOGDNAN	SINT_MIN
#endif



#define DEFINEFUNC_FLOAT_GETEXP10(BITS) \
t_sint	F##BITS##_GetExp10(t_f##BITS x) \
{ \
	if (F##BITS##_IsNaN(x))	return (FP_ILOGDNAN); \
	if (F##BITS##_IsInf(x))	return (FP_ILOGDINF); \
	if (x == 0.0) \
		return (FP_ILOGD0); \
	return (F##BITS##_Floor(F##BITS##_Log10(F##BITS##_Abs(x)))); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_GETEXP10(16)
#endif
DEFINEFUNC_FLOAT_GETEXP10(32)

DEFINEFUNC_FLOAT_GETEXP10(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GETEXP10(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GETEXP10(128)
#endif
