
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C23__)
MATH_DECL_REALFUNCTION(Sub, fsub)
#else
#define DEFINEFUNC_FLOAT_SUB(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Sub(t_f##BITS x, t_f##BITS y) \
{ \
	return (x - y); \
} \

DEFINEFUNC_FLOAT_SUB(32)
DEFINEFUNC_FLOAT_SUB(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SUB(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SUB(128)
#endif

#endif
