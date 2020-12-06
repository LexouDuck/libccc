
#include "libft_math.h"
#include "libft_memory.h"



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float		ft_cosh(t_float x)
{
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 1.63	for [-6,+6]-> 200 tests

	if (IS_NAN(x))
		return (NAN);
	else if (x == 0)
		return (1);
	else if (x < -3.2457)
		return (ft_exp(-x - LN_2));
	else if (x > 3.2457)
		return (ft_exp(x - LN_2));

	t_float result = 1.0;
	t_float power = x * x;
	result += 0.5000000000 * power;	power *= power;
	result += 0.0416666666 * power;	power *= x * x;
	result += 0.0016666666 * power;
	return (result);
}
#else
MATH_DECL_REALFUNCTION(cosh, cosh)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float		ft_sinh(t_float x)
{
// fast polynomial approximation for [-PI,+PI], exponential for the rest
// score: 0.96	for [-6,+6]-> 200 tests

	if (IS_NAN(x))
		return (NAN);
	else if (x == 0)
		return (0);
	else if (x < -PI)
		return (-ft_exp(-x - LN_2));
	else if (x > PI)
		return (ft_exp(x - LN_2));

	t_float result = x;
	t_float power = x * x * x;
	result += 0.1666666666 * power;		power *= (x * x);
	result += 0.0083333333 * power;		power *= (x * x);
	result += 0.0001500000 * power;		power *= (x * x);
	result += 0.0000083000 * power;
	return (result);
}
#else
MATH_DECL_REALFUNCTION(sinh, sinh)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float		ft_tanh(t_float x)
{
//	fast sigmoid approximation
//	score: 0.84 for [-6,+6]-> 200 tests

	if (IS_NAN(x))
		return (NAN);
	else if (x == 0)
		return (0);

	t_float abs_x = ft_fabs(x);
	t_float n = 1 - 0.37 * (abs_x / (1 + abs_x));
	if (n < 0.7)
		n = 0.7;
	n -= abs_x / (1 + abs_x);
	if (n < 0.)
		n = 0.;
	return (x / (n + abs_x));

//	fast sigmoid approximation for [-1,+1], and exponential approximation for the rest
//	score: 1.95	for [-6,+6]-> 250 tests
/*
	else if (x < -1.)
		return (ft_exp(1.43378091 * x) - 1);
	else if (x > 1.)
		return (-ft_exp(-1.43378091 * x) + 1);
	else
		return ((2 * x) / (1.6260705 + ft_fabs(x)));
*/
}
#else
MATH_DECL_REALFUNCTION(tanh, tanh)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float		ft_acosh(t_float x)
{
// fast sqrt approximation for [+1,+20] and natural log for the rest
// score: 5.00	for [+1,+50]-> 250 tests

	if (IS_NAN(x) || x < 1)
		return (NAN);
	if (x < 20)
		return (1.37 * ft_sqrt(x - 1) - 0.122 * (x - 1));
	else
		return (ft_ln(x - 1) + INV_SQRT_2);
}
#else
MATH_DECL_REALFUNCTION(acosh, acosh)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float		ft_asinh(t_float x)
{
// fast sigmoid approximation for [-20,+20] and natural log for the rest
// score: 9.09	for [-40,+40]-> 200 tests

	if (IS_NAN(x))
		return (NAN);
	else if (x == 0)
		return (0);
	else if (x < -20)
		return (-ft_ln(-x - 1) - INV_SQRT_2);
	else if (x > 20)
		return (ft_ln(x - 1) + INV_SQRT_2);
	else
		return (x / (1 + ft_fabs(-0.22103915 * x)));
}
#else
MATH_DECL_REALFUNCTION(asinh, asinh)
#endif



#if LIBFTCONFIG_FAST_APPROX_MATH
t_float		ft_atanh(t_float x)
{
//	approximation
//	score: 4.81	for [-1,+1]-> 200 tests

	if (IS_NAN(x) || ft_fabs(x) > 1.)
		return (NAN);
	else if (x == 0)
		return (0);

	static const t_float p = 0.6232;
	if (x < -0.6)
		return (ft_ln(p * x + p) * 0.5);
	if (x > 0.6)
		return (-ft_ln(p * -x + p) * 0.5);

	t_float result = x / (1 - 0.418 * ft_fabs(x));
	t_float power = x * x * x;
	result += -1.5 * power;		power *= (x * x);
	result +=  4.4 * power;		power *= (x * x);
	result += -2.4 * power;		power *= (x * x);
	result += -5.8 * power;
	return (result);
}
#else
MATH_DECL_REALFUNCTION(atanh, atanh)
#endif
