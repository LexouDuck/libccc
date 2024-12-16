
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C23__)
MATH_DECL_REALFUNCTION(Div, fdiv)
#else
#define DEFINEFUNC_FLOAT_DIV(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Div(t_f##BITS a, t_f##BITS b) \
{ \
	return (a / b); \
} \

DEFINEFUNC_FLOAT_DIV(32)
DEFINEFUNC_FLOAT_DIV(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_DIV(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_DIV(128)
#endif

#endif
