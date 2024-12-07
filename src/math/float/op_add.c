
#include "libccc/float.h"
#include "libccc/math/float.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH && (__STDC_VERSION__ >= __STDC_VERSION_C23__)
MATH_DECL_REALFUNCTION(Add, fadd)
#else
#define DEFINEFUNC_FLOAT_ADD(BITS) \
extern inline t_f##BITS	F##BITS##_Add(t_f##BITS a, t_f##BITS b)	\
{															\
	return (a + b);											\
}

DEFINEFUNC_FLOAT_ADD(32)
DEFINEFUNC_FLOAT_ADD(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ADD(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ADD(128)
#endif

#endif
