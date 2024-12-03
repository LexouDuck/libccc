
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(CosH, cosh)
#else
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 1.63	for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_COSH(BITS) \
t_f##BITS	F##BITS##_CosH(t_f##BITS x)							\
{																\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)				\
		return (NAN);											\
	if (x == 0)													\
		return (1);												\
	else if (x < -3.2457)	return (F##BITS##_Exp(-x - LN_2));	\
	else if (x > +3.2457)	return (F##BITS##_Exp(+x - LN_2));	\
	t_f##BITS result = 1.0;										\
	t_f##BITS power = x * x;									\
	result += (0.5000000000 * power);	power *= power;			\
	result += (0.0416666666 * power);	power *= x * x;			\
	result += (0.0016666666 * power);							\
	return (result);											\
}

DEFINEFUNC_FLOAT_COSH(32)
DEFINEFUNC_FLOAT_COSH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COSH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COSH(128)
#endif

#endif
