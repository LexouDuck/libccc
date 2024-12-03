
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(TanH, tanh)
#else
// fast sigmoid approximation
// score: 0.84 for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_TANH(BITS) \
t_f##BITS	F##BITS##_TanH(t_f##BITS x)							\
{																\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)				\
		return (NAN);											\
	if (x == 0)													\
		return (0);												\
	t_f##BITS abs_x = F##BITS##_Abs(x);							\
	t_f##BITS n = 1 - 0.37 * (abs_x / (1 + abs_x));				\
	if (n < 0.7)												\
		n = 0.7;												\
	n -= abs_x / (1 + abs_x);									\
	if (n < 0.)													\
		n = 0.;													\
	return (x / (n + abs_x));									\
}
// fast sigmoid approximation for [-1,+1], and exponential approximation for the rest
// score: 1.95	for [-6,+6]-> 250 tests
#if 0
	else if (x < -1.)
		return (+F##BITS##_Exp(1.43378091 * x) - 1);
	else if (x > 1.)
		return (-F##BITS##_Exp(-1.43378091 * x) + 1);
	else
		return ((2 * x) / (1.6260705 + F##BITS##_Abs(x)));
#endif

DEFINEFUNC_FLOAT_TANH(32)
DEFINEFUNC_FLOAT_TANH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TANH(128)
#endif

#endif
