
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(SinH, sinh)
#else
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 0.96	for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_SINH(BITS) \
t_f##BITS	F##BITS##_SinH(t_f##BITS x)							\
{																\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)				\
		return (NAN);											\
	if (x == 0)													\
		return (0);												\
	else if (x < -PI)	return (-F##BITS##_Exp(-x - LN_2));		\
	else if (x > +PI)	return (+F##BITS##_Exp(+x - LN_2));		\
	t_f##BITS result = x;										\
	t_f##BITS power = x * x * x;								\
	result += (0.1666666666 * power);	power *= (x * x);		\
	result += (0.0083333333 * power);	power *= (x * x);		\
	result += (0.0001500000 * power);	power *= (x * x);		\
	result += (0.0000083000 * power);							\
	return (result);											\
}

DEFINEFUNC_FLOAT_SINH(32)
DEFINEFUNC_FLOAT_SINH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SINH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SINH(128)
#endif

#endif
