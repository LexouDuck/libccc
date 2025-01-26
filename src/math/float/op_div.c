
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C23__)
MATH_DECL_REALFUNCTION(Div, fdiv)
#else
#define DEFINEFUNC_FLOAT_DIV(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Div(t_f##BITS x, t_f##BITS y) \
{ \
	if CCCERROR((IS_NAN(x) || IS_NAN(y)), ERROR_NANARGUMENT, NULL) \
		return (x + y); \
	return (x / y); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_DIV(16)
#endif
DEFINEFUNC_FLOAT_DIV(32)

DEFINEFUNC_FLOAT_DIV(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_DIV(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_DIV(128)
#endif

#endif
