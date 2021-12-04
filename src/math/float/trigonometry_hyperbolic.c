
#include "libccc/math/math.h"
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
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)			\
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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(SinH, sinh)
#else
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 0.96	for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_SINH(BITS) \
t_f##BITS	F##BITS##_SinH(t_f##BITS x)							\
{																\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)			\
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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(TanH, tanh)
#else
// fast sigmoid approximation
// score: 0.84 for [-6,+6]-> 200 tests
#define DEFINEFUNC_FLOAT_TANH(BITS) \
t_f##BITS	F##BITS##_TanH(t_f##BITS x)							\
{																\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)			\
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



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvCosH, acosh)
#else
// fast sqrt approximation for [+1,+20] and natural log for the rest
// score: 5.00	for [+1,+50]-> 250 tests
#define DEFINEFUNC_FLOAT_INVCOSH(BITS) \
t_f##BITS	F##BITS##_InvCosH(t_f##BITS x)								\
{																		\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)					\
	HANDLE_ERROR(MATHDOMAIN, (x < 1.), return (NAN);)					\
	if (x < 20)															\
		return (1.37 * F##BITS##_Root2(x - 1) - 0.122 * (x - 1));		\
	else																\
		return (F##BITS##_Ln(x - 1) + INV_SQRT_2);						\
}

DEFINEFUNC_FLOAT_INVCOSH(32)
DEFINEFUNC_FLOAT_INVCOSH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVCOSH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVCOSH(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvSinH, asinh)
#else
// fast sigmoid approximation for [-20,+20] and natural log for the rest
// score: 9.09	for [-40,+40]-> 200 tests
#define DEFINEFUNC_FLOAT_INVSINH(BITS) \
t_f##BITS	F##BITS##_InvSinH(t_f##BITS x)								\
{																		\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)					\
	if (x == 0)															\
		return (0);														\
	else if (x < -20)	return (-F##BITS##_Ln(-x - 1) - INV_SQRT_2);	\
	else if (x > +20)	return (+F##BITS##_Ln(+x - 1) + INV_SQRT_2);	\
	else																\
		return (x / (1 + F##BITS##_Abs(-0.22103915 * x)));				\
}

DEFINEFUNC_FLOAT_INVSINH(32)
DEFINEFUNC_FLOAT_INVSINH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVSINH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVSINH(128)
#endif

#endif



#if LIBCONFIG_USE_STD_MATH
MATH_DECL_REALFUNCTION(InvTanH, atanh)
#else
// taylor series approximation
// score: 4.81	for [-1,+1]-> 200 tests
#define DEFINEFUNC_FLOAT_INVTANH(BITS) \
t_f##BITS	F##BITS##_InvTanH(t_f##BITS x)								\
{																		\
	static const t_f##BITS p = 0.6232;									\
	HANDLE_ERROR(NANARGUMENT, IS_NAN(x), return (NAN);)					\
	HANDLE_ERROR(MATHDOMAIN, (F##BITS##_Abs(x) > 1.), return (NAN);)	\
	if (x == 0)															\
		return (0);														\
	if (x < -0.6)	return (+F##BITS##_Ln(p * +x + p) * 0.5);			\
	if (x > +0.6)	return (-F##BITS##_Ln(p * -x + p) * 0.5);			\
	t_f##BITS result = x / (1 - 0.418 * F##BITS##_Abs(x));				\
	t_f##BITS power = x * x * x;										\
	result += (-1.5 * power);	power *= (x * x);						\
	result += (+4.4 * power);	power *= (x * x);						\
	result += (-2.4 * power);	power *= (x * x);						\
	result += (-5.8 * power);											\
	return (result);													\
}

DEFINEFUNC_FLOAT_INVTANH(32)
DEFINEFUNC_FLOAT_INVTANH(64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_FLOAT_INVTANH(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_FLOAT_INVTANH(128)
#endif

#endif
