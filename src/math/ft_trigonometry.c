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

#include "../../libft_math.h"
#include "../../libft_memory.h"



static t_float	inv_factorial(t_u32 n)
{
	static t_float	result[16] =
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



// TODO remove and implement homemade
#include <math.h>
t_float		ft_atan(t_float x)
{
	t_float add = 0;

	if (abs(x) > 2.)
		x *= 1.2;
	else if (abs(x) > 1.)
		add = (0.02 * x);
	else
	{
		x *= 0.8;
		add = (0.07 * x);
	}
	return ((HALF_PI * x) / (1. + abs(x)) + add);
//	return (atan(x));							// precise
//	return (3. / (1 + ft_exp(-1.1 * x)) - 1.5);	// bad
}

#define FLOAT_SIZE	sizeof(t_float)
static t_u64	ft_float_to_uint(t_float x)
{
	t_u8	bytes[FLOAT_SIZE];
	t_u64	result = 0;

	FT_MemoryCopy(bytes, &x, FLOAT_SIZE);
	for (t_u8 i = 0; i < FLOAT_SIZE; ++i)
	{
		result <<= 8;
		result |= bytes[i];
	}
	return (result);
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
		return (atan(y));

	t_s32 exp_x = (ft_float_to_uint(x) & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS;
	t_s32 exp_y = (ft_float_to_uint(y) & FLOAT_EXPONENT) >> FLOAT_MANTISSA_BITS;
	t_float result = ABS(y / x);
	if ((exp_y - exp_x) > 60)			/* |y / x| >  2^60 */
		result = HALF_PI + 0.5 * pi_lo;
	else if ((exp_y - exp_x) < -60)		/* |y| / x < -2^60 */
		result = 0.0;
	else
		result = ft_atan(0.98 * result);

	if (x < 0)
		return ((PI - (result - pi_lo)) * SIGN(y));
	else
		return (y < 0 ? -result : result);
}
