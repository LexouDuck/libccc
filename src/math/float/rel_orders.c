
#include "libccc.h"
#include "libccc/int.h"
#include "libccc/math/int.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(LessThan, isless)
#else
#define DEFINEFUNC_FLOAT_LT(BITS) \
_INLINE() \
t_bool	F##BITS##_LessThan(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(isunordered(x, y), ERROR_NANARGUMENT, \
		"cannot compare (%g < %g)", x, y) \
		return FALSE; \
	return (x < y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_LT(16)
#endif
DEFINEFUNC_FLOAT_LT(32)

DEFINEFUNC_FLOAT_LT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(LessThanOrEqual, islessequal)
#else
#define DEFINEFUNC_FLOAT_LTE(BITS) \
_INLINE() \
t_bool	F##BITS##_LessThanOrEqual(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(isunordered(x, y), ERROR_NANARGUMENT, \
		"cannot compare (%g <= %g)", x, y) \
		return FALSE; \
	return (x <= y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_LTE(16)
#endif
DEFINEFUNC_FLOAT_LTE(32)

DEFINEFUNC_FLOAT_LTE(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_LTE(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_LTE(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(GreaterThan, isgreater)
#else
#define DEFINEFUNC_FLOAT_GT(BITS) \
_INLINE() \
t_bool	F##BITS##_GreaterThan(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(isunordered(x, y), ERROR_NANARGUMENT, \
		"cannot compare (%g > %g)", x, y) \
		return FALSE; \
	return (x > y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_GT(16)
#endif
DEFINEFUNC_FLOAT_GT(32)

DEFINEFUNC_FLOAT_GT(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GT(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C99__)
MATH_DECL_ENDORELATION(GreaterThanOrEqual, isgreaterequal)
#else
#define DEFINEFUNC_FLOAT_GTE(BITS) \
_INLINE() \
t_bool	F##BITS##_GreaterThanOrEqual(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR(isunordered(x, y), ERROR_NANARGUMENT, \
		"cannot compare (%g >= %g)", x, y) \
		return FALSE; \
	return (x >= y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_GTE(16)
#endif
DEFINEFUNC_FLOAT_GTE(32)

DEFINEFUNC_FLOAT_GTE(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_GTE(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_GTE(128)
#endif

#endif
