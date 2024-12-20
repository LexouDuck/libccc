
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(LT, isless)
#else
#define DEFINEFUNC_FIXED_LT(BITS) \
_INLINE() \
t_bool	F##BITS##_LessThan(t_q##BITS a, t_q##BITS b) \
{ \
	return (a < b); \
} \

DEFINEFUNC_FIXED_LT(16)
DEFINEFUNC_FIXED_LT(32)
DEFINEFUNC_FIXED_LT(64)
#if LIBCONFIG_USE_FIXED128
DEFINEFUNC_FIXED_LT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(LTE, islessequal)
#else
#define DEFINEFUNC_FIXED_LTE(BITS) \
_INLINE() \
t_bool	F##BITS##_LessThanOrEqual(t_q##BITS a, t_q##BITS b) \
{ \
	return (a <= b); \
} \

DEFINEFUNC_FIXED_LTE(16)
DEFINEFUNC_FIXED_LTE(32)
DEFINEFUNC_FIXED_LTE(64)
#if LIBCONFIG_USE_FIXED128
DEFINEFUNC_FIXED_LTE(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(GT, isgreater)
#else
#define DEFINEFUNC_FIXED_GT(BITS) \
_INLINE() \
t_bool	F##BITS##_GreaterThan(t_q##BITS a, t_q##BITS b) \
{ \
	return (a > b); \
} \

DEFINEFUNC_FIXED_GT(16)
DEFINEFUNC_FIXED_GT(32)
DEFINEFUNC_FIXED_GT(64)
#if LIBCONFIG_USE_FIXED128
DEFINEFUNC_FIXED_GT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(GTE, isgreaterequal)
#else
#define DEFINEFUNC_FIXED_GTE(BITS) \
_INLINE() \
t_bool	F##BITS##_GreaterThanOrEqual(t_q##BITS a, t_q##BITS b) \
{ \
	return (a >= b); \
} \

DEFINEFUNC_FIXED_GTE(16)
DEFINEFUNC_FIXED_GTE(32)
DEFINEFUNC_FIXED_GTE(64)
#if LIBCONFIG_USE_FIXED128
DEFINEFUNC_FIXED_GTE(128)
#endif

#endif
