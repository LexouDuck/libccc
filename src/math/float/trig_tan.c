
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Tan, tan)
#else
// trigonometric formula method
#define DEFINEFUNC_FLOAT_TAN(BITS) \
t_f##BITS	F##BITS##_Tan(t_f##BITS x)						\
{															\
	t_f##BITS	cosine;										\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)			\
		return (NAN);										\
	cosine = F##BITS##_Cos(x);								\
	if CCCERROR((cosine == 0.), ERROR_MATHDOMAIN, NULL)		\
		return (NAN);										\
	return (F##BITS##_Sin(x) / cosine);						\
}
// fast polynomial approximation for [-1,+1] and 1/x approximation for the rest
// score: 0.23	for [-40,+40]=> 200 tests
#if 0
	t_f##BITS	a;
	t_s64		floor_a;

	if (x < -PI_HALF)
	{
		x = -x + PI_HALF;
		a = x / PI;
		floor_a = a;
		x = (a - floor_a) * PI;
		x = PI - x;
		x -= PI_HALF;
	}
	else if (x > PI_HALF)
	{
		x += PI_HALF;
		a = x / PI;
		floor_a = a;
		x = (a - floor_a) * PI;
		x -= PI_HALF;
	}
	if (x < -0.997592567)
		return (-1 / (x + PI_HALF) + 0.343 * x + 0.538);
	if (x > 0.997592567)
		return (-(1 / (x - PI_HALF) - 0.343 * x + 0.538));

	t_f##BITS result = x;
	t_f##BITS power = x * x * x;

	result += power * 0.33333333333;	power *= (x * x);
	result += power * 0.13333333333;	power *= (x * x);
	result += power * 0.09;
	return (result);
#endif

DEFINEFUNC_FLOAT_TAN(32)
DEFINEFUNC_FLOAT_TAN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_TAN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_TAN(128)
#endif

#endif
