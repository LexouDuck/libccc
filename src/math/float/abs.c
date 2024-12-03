
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Abs, fabs)
#else
#define DEFINEFUNC_FLOAT_ABS(BITS) \
extern inline t_f##BITS	F##BITS##_Abs(t_f##BITS x) \
{ \
	u_cast_f##BITS	result; \
	result.value_float = x; \
	result.value_uint &= ~F##BITS##_SIGNED; \
	return (result.value_float); \
} \

DEFINEFUNC_FLOAT_ABS(32)
DEFINEFUNC_FLOAT_ABS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ABS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ABS(128)
#endif

#endif
