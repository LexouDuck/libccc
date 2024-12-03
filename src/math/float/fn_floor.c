
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Floor, floor)
#else
#define DEFINEFUNC_FLOAT_FLOOR(BITS) \
extern inline \
t_f##BITS	F##BITS##_Floor(t_f##BITS x)	\
{													\
	if (x == 0.)									\
		return (0.);								\
	if (x < 0.)										\
		return (x - F##BITS##_Mod(x, 1.) - 1.);		\
	return (x - F##BITS##_Mod(x, 1.));				\
}

DEFINEFUNC_FLOAT_FLOOR(32)
DEFINEFUNC_FLOAT_FLOOR(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_FLOOR(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_FLOOR(128)
#endif

#endif
