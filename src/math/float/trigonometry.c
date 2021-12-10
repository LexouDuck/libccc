
#include "libccc/math.h"
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#if !LIBCONFIG_USE_STD_MATH
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
#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Cos, cos)
#else
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
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)	\
	sign = 0;											\
	if (x < 0.)											\
		x = -x;											\
	if (x > TAU)										\
		x = F##BITS##_Mod(x, TAU);						\
	if (x > PI)											\
		x = PI - (x - PI);								\
	if (x > HALF_PI)									\
	{													\
		x = HALF_PI - (x - HALF_PI);					\
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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Sin, sin)
#else
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
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)	\
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
	if (x > HALF_PI)									\
		x = HALF_PI - (x - HALF_PI);					\
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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(Tan, tan)
#else
// trigonometric formula method
#define DEFINEFUNC_FLOAT_TAN(BITS) \
t_f##BITS	F##BITS##_Tan(t_f##BITS x)						\
{															\
	t_f##BITS	cosine;										\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)		\
	cosine = F##BITS##_Cos(x);								\
	HANDLE_ERROR(MATHDOMAIN, (cosine == 0.), return (NAN);)	\
	return (F##BITS##_Sin(x) / cosine);						\
}
// fast polynomial approximation for [-1,+1] and 1/x approximation for the rest
// score: 0.23	for [-40,+40]=> 200 tests
#if 0
	t_f##BITS	a;
	t_s64		floor_a;

	if (x < -HALF_PI)
	{
		x = -x + HALF_PI;
		a = x / PI;
		floor_a = a;
		x = (a - floor_a) * PI;
		x = PI - x;
		x -= HALF_PI;
	}
	else if (x > HALF_PI)
	{
		x += HALF_PI;
		a = x / PI;
		floor_a = a;
		x = (a - floor_a) * PI;
		x -= HALF_PI;
	}
	if (x < -0.997592567)
		return (-1 / (x + HALF_PI) + 0.343 * x + 0.538);
	if (x > 0.997592567)
		return (-(1 / (x - HALF_PI) - 0.343 * x + 0.538));

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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcCos, acos)
#else
// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
#define DEFINEFUNC_FLOAT_ARCCOS(BITS) \
t_f##BITS		F##BITS##_ArcCos(t_f##BITS x)						\
{																	\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)				\
	HANDLE_ERROR(MATHDOMAIN, (F##BITS##_Abs(x) > 1.), return (NAN);)\
	if (F##BITS##_Abs(x) == 1.)										\
		return (INFINITY * SIGN(x));								\
	t_f##BITS result = HALF_PI;										\
	t_f##BITS power = x;											\
	result += power * -1.;			power *= (x * x);				\
	result += power * -0.0584;		power *= (x * x);				\
	result += power * -0.6852;		power *= (x * x);				\
	result += power * +1.16616;		power *= (x * x);				\
	result += power * -0.9933563268;								\
	return (result);												\
}
// very fast cubic approximation
// score: 11.53	for [-1,+1]-> 200 tests
#if 0
	return ((-0.8047926 * x * x - 0.766) * x + HALF_PI); // (-0.69813170079773212 * x * x - 0.87266462599716477)
#endif

DEFINEFUNC_FLOAT_ARCCOS(32)
DEFINEFUNC_FLOAT_ARCCOS(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCCOS(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCCOS(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcSin, asin)
#else
// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
#define DEFINEFUNC_FLOAT_ARCSIN(BITS) \
t_f##BITS	F##BITS##_ArcSin(t_f##BITS x)							\
{																	\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)				\
	HANDLE_ERROR(MATHDOMAIN, (F##BITS##_Abs(x) > 1.), return (NAN);)\
	if (F##BITS##_Abs(x) == 1.)										\
		return (INFINITY * SIGN(x));								\
	t_f##BITS result = 0;											\
	t_f##BITS power = x;											\
	result += power * -1.;			power *= (x * x);				\
	result += power * -0.0584;		power *= (x * x);				\
	result += power * -0.6852;		power *= (x * x);				\
	result += power * +1.16616;		power *= (x * x);				\
	result += power * -0.9933563268;								\
	return (-result);												\
}
// very fast cubic approximation
// score: 11.53	for [-1,+1]-> 200 tests
#if 0
	return ((0.8047926 * x * x + 0.766) * x); // (-0.69813170079773212 * x * x - 0.87266462599716477)
#endif

DEFINEFUNC_FLOAT_ARCSIN(32)
DEFINEFUNC_FLOAT_ARCSIN(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCSIN(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCSIN(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(ArcTan, atan)
#else
// very fast sigmoid approximation
// score: 0.77	for [-5,+5]-> 200 tests
#define DEFINEFUNC_FLOAT_ARCTAN(BITS) \
t_f##BITS	F##BITS##_ArcTan(t_f##BITS x)				\
{														\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)	\
	if (x == 0)											\
		return (0);										\
	t_f##BITS abs_x = F##BITS##_Abs(x);					\
	t_f##BITS n = 1.54 - abs_x / (0.9 + abs_x);			\
	if (n < 0.65)										\
		n = 0.65;										\
	return ((HALF_PI * x) / (n + abs_x));				\
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
	return ((HALF_PI * x) / (1. + abs_x) + add);
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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALOPERATOR(ArcTan2, atan2)
#else
#define DEFINEFUNC_FLOAT_ARCTAN2(BITS) \
t_f##BITS	F##BITS##_ArcTan2(t_f##BITS y, t_f##BITS x)					\
{																		\
	HANDLE_ERROR(NANARGUMENT, (IS_NAN(x) || IS_NAN(y)), return (NAN);)	\
	static const t_f##BITS pi_lo = 1.2246467991473531772E-16;			\
	if (y == 0.0)														\
		return ((x < 0 ? PI : 0) * SIGN(x));							\
	if (x == 0.0)														\
		return (HALF_PI * SIGN(y));										\
	if (IS_INFINITY(x))													\
	{																	\
		if (IS_INFINITY(y))												\
			return ((x < 0 ? 3 * QUARTER_PI : QUARTER_PI) * SIGN(y));	\
		else															\
			return ((x < 0 ? PI : 0) * SIGN(y));						\
	}																	\
	if (IS_INFINITY(y))													\
		return (HALF_PI * SIGN(y));										\
	if (x == 1.0)														\
		return (F##BITS##_ArcTan(y));									\
	t_s32 exp_x = F##BITS##_GetExp2(x);									\
	t_s32 exp_y = F##BITS##_GetExp2(y);									\
	t_f##BITS result = F##BITS##_Abs(y / x);							\
	if ((exp_y - exp_x) > 60)		/* |y / x| > +2^60 */				\
		result = HALF_PI + 0.5 * pi_lo;									\
	else if ((exp_y - exp_x) < -60)	/* |y| / x < -2^60 */				\
		result = 0.0;													\
	else																\
		result = F##BITS##_ArcTan(result);								\
	if (x < 0)															\
		return ((PI - (result - pi_lo)) * SIGN(y));						\
	else																\
		return (y < 0 ? -result : result);								\
}

DEFINEFUNC_FLOAT_ARCTAN2(32)
DEFINEFUNC_FLOAT_ARCTAN2(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_ARCTAN2(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_ARCTAN2(128)
#endif

#endif
