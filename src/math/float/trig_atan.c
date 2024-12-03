
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcTan, atan)
#else
// very fast sigmoid approximation
// score: 0.77	for [-5,+5]-> 200 tests
#define DEFINEFUNC_FLOAT_ARCTAN(BITS) \
t_f##BITS	F##BITS##_ArcTan(t_f##BITS x)				\
{														\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)		\
		return (NAN);									\
	if (x == 0)											\
		return (0);										\
	t_f##BITS abs_x = F##BITS##_Abs(x);					\
	t_f##BITS n = 1.54 - abs_x / (0.9 + abs_x);			\
	if (n < 0.65)										\
		n = 0.65;										\
	return ((PI_HALF * x) / (n + abs_x));				\
}
// 3 different curves, some discontinuity
// score: 38.20	for [-5,+5]-> 200 tests
#if 0
	static const t_f##BITS result_1_0 = 0x1.921fb54442d18p-1;
	static const t_f##BITS result_2_5 = 0x1.30b6d796a4da7p0;
	t_f##BITS abs_x;
	t_f##BITS add = 0;

	abs_x = F##BITS##_Abs(x);
	if (abs_x == 1.0)	return (result_1_0);
	if (abs_x == 2.5)	return (result_2_5);
	else if (abs_x > 2.5)
		x *= 1.3;
	else if (abs_x > 1.0)
	{
		x *= 0.9;
		add = (0.05 * x);
	}
	else
	{
		x *= 0.57;
		add = (0.22 * x);
	}
	return ((PI_HALF * x) / (1. + abs_x) + add);
#endif
// crazy simple exp() approximation
// score: 60.59	for [-5, 5]-> 200 tests
#if 0
	return (3. / (1 + Float_Exp(-1.1 * x)) - 1.5);
#endif

DEFINEFUNC_FLOAT_ARCTAN(32)
DEFINEFUNC_FLOAT_ARCTAN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCTAN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCTAN(128)
#endif

#endif
