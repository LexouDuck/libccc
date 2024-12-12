
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Sin, sin)
#elif 1 // LIBCONFIG_USE_CCC_MATH
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
#define DEFINEFUNC_FLOAT_SIN(BITS) \
t_f##BITS	F##BITS##_Sin(t_f##BITS x)					\
{														\
	t_f##BITS	result;									\
	t_bool		sign; /* `TRUE` for negative */			\
	t_f##BITS	x_pow2;									\
	t_f##BITS	x_pow3;									\
	t_f##BITS	x_pow5;									\
	t_f##BITS	x_pow7;									\
	t_f##BITS	x_pow9;									\
	t_f##BITS	x_pow11;								\
	t_f##BITS	x_pow13;								\
	if CCCERROR(IS_NAN(x), ERROR_NANARGUMENT, NULL)		\
		return (NAN);									\
	sign = 0;											\
	if (x < 0.)											\
	{													\
		x = -x;											\
		sign = !sign;									\
	}													\
	if (x > TAU)										\
		x = F##BITS##_Mod(x, TAU);						\
	if (x > PI)											\
	{													\
		x = PI - (x - PI);								\
		sign = !sign;									\
	}													\
	if (x > PI_HALF)									\
		x = PI_HALF - (x - PI_HALF);					\
	x_pow2  = x * x;									\
	x_pow3  = x * x_pow2;								\
	x_pow5  = x_pow2 * x_pow3;							\
	x_pow7  = x_pow2 * x_pow5;							\
	x_pow9  = x_pow2 * x_pow7;							\
	x_pow11 = x_pow2 * x_pow9;							\
	x_pow13 = x_pow2 * x_pow11;							\
	result = x;											\
	result -= x_pow3  * inv_factorial(3);				\
	result += x_pow5  * inv_factorial(5);				\
	result -= x_pow7  * inv_factorial(7);				\
	result += x_pow9  * inv_factorial(9);				\
	result -= x_pow11 * inv_factorial(11);				\
	result += x_pow13 * inv_factorial(13);				\
	result -= x_pow13 * x_pow2 * inv_factorial(15);		\
	return (sign ? -result : result);					\
}

DEFINEFUNC_FLOAT_SIN(32)
DEFINEFUNC_FLOAT_SIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_SIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_SIN(128)
#endif

#endif
