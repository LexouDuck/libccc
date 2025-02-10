
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Abs, fabs)
#else
#define DEFINEFUNC_FLOAT_ABS(BITS) \
_INLINE() \
t_f##BITS	F##BITS##_Abs(t_f##BITS x) \
{ \
	u_cast_f##BITS	result; \
	result.as_f = x; \
	result.as_u &= ~F##BITS##_SIGN_BIT_MASK; \
	return (result.as_f); \
} \

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_FLOAT_ABS(16)
#endif
DEFINEFUNC_FLOAT_ABS(32)

DEFINEFUNC_FLOAT_ABS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ABS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ABS(128)
#endif

#endif
