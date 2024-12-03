
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Cos, cos)
#else
static t_float	inv_factorial(t_uint n)
{
	static const t_float	result[16] =
	{
		1.0,
		1.0,
		1.0 / 2,
		1.0 / 6,
		1.0 / 24,
		1.0 / 120,
		1.0 / 720,
		1.0 / 5040,
		1.0 / 40320,
		1.0 / 362880,
		1.0 / 3628800,
		1.0 / 39916800,
		1.0 / 479001600,
		1.0 / 6227020800,
		1.0 / 87178291200,
		1.0 / 1307674368000,
	};
	return (result[n]); //static so it shouldn't be called with any weird values
//	return (n >= 16) ? 0. : result[n];
}
// taylor series approximation
#define DEFINEFUNC_FLOAT_COS(BITS) \
t_f##BITS	F##BITS##_Cos(t_f##BITS x)					\
{														\
	t_f##BITS	result;									\
	t_bool		sign; /* `TRUE` for negative */			\
	t_f##BITS	x_pow2;									\
	t_f##BITS	x_pow4;									\
	t_f##BITS	x_pow6;									\
	t_f##BITS	x_pow8;									\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)		\
		return (NAN);									\
	sign = 0;											\
	if (x < 0.)											\
		x = -x;											\
	if (x > TAU)										\
		x = F##BITS##_Mod(x, TAU);						\
	if (x > PI)											\
		x = PI - (x - PI);								\
	if (x > PI_HALF)									\
	{													\
		x = PI_HALF - (x - PI_HALF);					\
		sign = -1;										\
	}													\
	x_pow2 = x * x;										\
	x_pow4 = x_pow2 * x_pow2;							\
	x_pow6 = x_pow2 * x_pow4;							\
	x_pow8 = x_pow4 * x_pow4;							\
	result = 1.;										\
	result -= x_pow2 * 0.5;								\
	result += x_pow4 * inv_factorial(4);				\
	result -= x_pow6 * inv_factorial(6);				\
	result += x_pow8 * inv_factorial(8);				\
	result -= x_pow8 * x_pow2 * inv_factorial(10);		\
	result += x_pow8 * x_pow4 * inv_factorial(12);		\
	result -= x_pow8 * x_pow6 * inv_factorial(14);		\
	return (sign ? -result : result);					\
}

DEFINEFUNC_FLOAT_COS(32)
DEFINEFUNC_FLOAT_COS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_COS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_COS(128)
#endif

#endif
