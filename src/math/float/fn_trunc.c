
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Trunc, trunc)
#else
#define DEFINEFUNC_FLOAT_TRUNC(BITS) \
extern inline \
t_f##BITS	F##BITS##_Trunc(t_f##BITS x)	\
{													\
	if (x == 0.)									\
		return (0.);								\
	return (x - F##BITS##_Mod(x, 1.));				\
}

DEFINEFUNC_FLOAT_TRUNC(32)
DEFINEFUNC_FLOAT_TRUNC(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TRUNC(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TRUNC(128)
#endif

#endif
