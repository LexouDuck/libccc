/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/ft_trigonometry.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_memory.h"



static t_float	inv_factorial(t_u32 n)
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
		1.0 / 1307674368000
	};

	return (result[n]); //static so it shouldn'x be called with any weird values
//	return (n >= 16) ? 0. : result[n];
}



t_float			ft_cos(t_float x)
{
	t_float		result;
	t_bool		sign; //True for negative
	t_float		x_pow2;
	t_float		x_pow4;
	t_float		x_pow6;
	t_float		x_pow8;

	sign = 0;
	if (x < 0.)
		x = -x;
	if (x > TAU)
		x = ft_fmod(x, TAU);
	if (x > PI)
		x = PI - (x - PI);
	if (x > HALF_PI)
	{
		x = HALF_PI - (x - HALF_PI);
		sign = -1;
	}

	x_pow2 = x * x;
	x_pow4 = x_pow2 * x_pow2;
	x_pow6 = x_pow2 * x_pow4;
	x_pow8 = x_pow4 * x_pow4;

	result = 1.;
	result -= x_pow2 * 0.5;
	result += x_pow4 * inv_factorial(4);
	result -= x_pow6 * inv_factorial(6);
	result += x_pow8 * inv_factorial(8);
	result -= x_pow8 * x_pow2 * inv_factorial(10);
	result += x_pow8 * x_pow4 * inv_factorial(12);
	result -= x_pow8 * x_pow6 * inv_factorial(14);

	return (sign ? -result : result);
}

t_float			ft_sin(t_float x)
{
	t_float		result;
	t_bool		sign; //True for negative
	t_float		x_pow2;
	t_float		x_pow3;
	t_float		x_pow5;
	t_float		x_pow7;
	t_float		x_pow9;
	t_float		x_pow11;
	t_float		x_pow13;

	sign = 0;
	if (x < 0.)
	{
		x = -x;
		sign = !sign;
	}
	if (x > TAU)
		x = ft_fmod(x, TAU);
	if (x > PI)
	{
		x = PI - (x - PI);
		sign = !sign;
	}
	if (x > HALF_PI)
		x = HALF_PI - (x - HALF_PI);

	x_pow2 = x * x;
	x_pow3 = x * x_pow2;
	x_pow5 = x_pow2 * x_pow3;
	x_pow7 = x_pow2 * x_pow5;
	x_pow9 = x_pow2 * x_pow7;
	x_pow11 = x_pow2 * x_pow9;
	x_pow13 = x_pow2 * x_pow11;

	result = x;
	result -= x_pow3 * inv_factorial(3);
	result += x_pow5 * inv_factorial(5);
	result -= x_pow7 * inv_factorial(7);
	result += x_pow9 * inv_factorial(9);
	result -= x_pow11 * inv_factorial(11);
	result += x_pow13 * inv_factorial(13);
	result -= x_pow13 * x_pow2 * inv_factorial(15);

	return (sign ? -result : result);
}



inline t_float	ft_tan(t_float x)
{
// trigonometric formula
	return (ft_sin(x) / ft_cos(x));

// fast polynomial approximation for [-1,+1] and 1/x approximation for the rest
// score: 0.23	for [-40,+40]=> 200 tests
/*
	t_float		a;
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

	t_float result = x;
	t_float power = x * x * x;

	result += power * 0.33333333333;	power *= (x * x);
	result += power * 0.13333333333;	power *= (x * x);
	result += power * 0.09;
	return (result);
*/
}



t_float		ft_acos(t_float x)
{
// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
	if (IS_NAN(x) || ABS(x) > 1.)
		return (NAN);
	if (ABS(x) == 1.)
		return (INFINITY * SIGN(x));

	t_float result = HALF_PI;
	t_float power = x;
	result += power * -1.;				power *= (x * x);
	result += power * -0.0584;			power *= (x * x);
	result += power * -0.6852;			power *= (x * x);
	result += power * 1.16616;			power *= (x * x);
	result += power * -0.9933563268;
	return (result);

//	very fast cubic approximation
//	score: 11.53	for [-1,+1]-> 200 tests
/*
	return ((-0.8047926 * x * x - 0.766) * x + HALF_PI); // (-0.69813170079773212 * x * x - 0.87266462599716477)
*/
}



t_float		ft_asin(t_float x)
{
// fast polynomial approximation
// score: 2.55	for [-1,+1]=> 200 tests
	if (IS_NAN(x) || ABS(x) > 1.)
		return (NAN);
	if (ABS(x) == 1.)
		return (INFINITY * SIGN(x));

	t_float result = 0;
	t_float power = x;
	result += power * -1.;				power *= (x * x);
	result += power * -0.0584;			power *= (x * x);
	result += power * -0.6852;			power *= (x * x);
	result += power * 1.16616;			power *= (x * x);
	result += power * -0.9933563268;
	return (-result);

//	very fast cubic approximation
//	score: 11.53	for [-1,+1]-> 200 tests
/*
	return ((0.8047926 * x * x + 0.766) * x); // (-0.69813170079773212 * x * x - 0.87266462599716477)
*/
}



t_float		ft_atan(t_float x)
{
//	very fast sigmoid approximation
//	score: 0.77	for [-5,+5]-> 200 tests

	if (IS_NAN(x))
		return (NAN);
	else if (x == 0)
		return (0);

	t_float abs_x = ABS(x);
	t_float n = 1.54 - abs_x / (0.9 + abs_x);
	if (n < 0.65)
		n = 0.65;
	return ((HALF_PI * x) / (n + abs_x));


//	3 different curves, some discontinuity
//	score: 38.20	for [-5,+5]-> 200 tests
/*
	static const t_float result_1_0	= 0x1.921fb54442d18p-1;
	static const t_float result_2_5	= 0x1.30b6d796a4da7p0;
	t_float abs_x;
	t_float add = 0;

	abs_x = ABS(x);
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
*/

// score: 60.59	for [-5, 5]-> 200 tests
/*
	return (3. / (1 + ft_exp(-1.1 * x)) - 1.5);
*/
}

static t_s32	ft_float_get_exponent(t_float x)
{
	t_s64	result = 0;

	ft_memcpy((t_u8*)&result, &x, sizeof(t_float));
	return (((result & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS) - FLOAT_EXPONENT_BIAS);
}

t_float		ft_atan2(t_float y, t_float x)
{
	static const t_float pi_lo = 1.2246467991473531772E-16;

	if (IS_NAN(x) || IS_NAN(y))
		return (x + y);
	else if (y == 0.0)
		return ((x < 0 ? PI : 0) * SIGN(x));
	else if (x == 0.0)
		return (HALF_PI * SIGN(y));
	else if (IS_INFINITY(x))
	{
		if (IS_INFINITY(y))
			return ((x < 0 ? 3 * QUARTER_PI : QUARTER_PI) * SIGN(y));
		else
			return ((x < 0 ? PI : 0) * SIGN(y));
	}
	else if (IS_INFINITY(y))
	{
		return (HALF_PI * SIGN(y));
	}
	else if (x == 1.0)
		return (ft_atan(y));

	t_s32 exp_x = ft_float_get_exponent(x);
	t_s32 exp_y = ft_float_get_exponent(y);
	t_float result = ABS(y / x);
	if ((exp_y - exp_x) > 60)			/* |y / x| >  2^60 */
		result = HALF_PI + 0.5 * pi_lo;
	else if ((exp_y - exp_x) < -60)		/* |y| / x < -2^60 */
		result = 0.0;
	else
		result = ft_atan(result);

	if (x < 0)
		return ((PI - (result - pi_lo)) * SIGN(y));
	else
		return (y < 0 ? -result : result);
}



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



t_float		ft_tanh(t_float x)
{
//	fast sigmoid approximation
//	score: 0.84 for [-6,+6]-> 200 tests

	if (IS_NAN(x))
		return (NAN);
	else if (x == 0)
		return (0);

	t_float abs_x = ABS(x);
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
		return ((2 * x) / (1.6260705 + ABS(x)));
*/
}



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
		return (x / (1 + ABS(-0.22103915 * x)));
}



t_float		ft_atanh(t_float x)
{
//	approximation
//	score: 4.81	for [-1,+1]-> 200 tests

	if (IS_NAN(x) || ABS(x) > 1.)
		return (NAN);
	else if (x == 0)
		return (0);

	static const t_float p = 0.6232;
	if (x < -0.6)
		return (ft_ln(p * x + p) * 0.5);
	if (x > 0.6)
		return (-ft_ln(p * -x + p) * 0.5);

	t_float result = x / (1 - 0.418 * ABS(x));
	t_float power = x * x * x;
	result += -1.5 * power;		power *= (x * x);
	result +=  4.4 * power;		power *= (x * x);
	result += -2.4 * power;		power *= (x * x);
	result += -5.8 * power;
	return (result);

}
