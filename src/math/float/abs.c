
#include "libccc/float.h"
#include "libccc/math/float.h"
#include "libccc/math/math.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Abs, fabs)
#else
#define DEFINEFUNC_FLOAT_ABS(BITS) \
inline t_f##BITS	F##BITS##_Abs(t_f##BITS x)	\
{												\
	u_f##BITS##_cast	result;					\
												\
	result.value_float = x;						\
	if (result.value_int & F##BITS##_SIGNED)	\
	{											\
		result.value_int &= ~F##BITS##_SIGNED;	\
	}											\
	return (result.value_float);				\
}



DEFINEFUNC_FLOAT_ABS(32)

DEFINEFUNC_FLOAT_ABS(64)

#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ABS(80)
#endif

#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ABS(128)
#endif

#endif
