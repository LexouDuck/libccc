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

	return (result[n]); //static so it shouldn't be called with any weird values
//	return (n >= 16) ? 0. : result[n];
}



t_float			ft_cos(t_float t)
{
	t_float		result;
	t_bool		sign; //True for negative
	t_float		t_p2;
	t_float		t_p4;
	t_float		t_p6;
	t_float		t_p8;

	sign = 0;
	if (t < 0.)
		t = -t;
	if (t > TAU)
		t = ft_fmod(t, TAU);
	if (t > PI)
		t = PI - (t - PI);
	if (t > HALF_PI)
	{
		t = HALF_PI - (t - HALF_PI);
		sign = -1;
	}

	t_p2 = t * t;
	t_p4 = t_p2 * t_p2;
	t_p6 = t_p2 * t_p4;
	t_p8 = t_p4 * t_p4;

	result = 1.;
	result -= t_p2 * 0.5;
	result += t_p4 * inv_factorial(4);
	result -= t_p6 * inv_factorial(6);
	result += t_p8 * inv_factorial(8);
	result -= t_p8 * t_p2 * inv_factorial(10);
	result += t_p8 * t_p4 * inv_factorial(12);
	result -= t_p8 * t_p6 * inv_factorial(14);

	return (sign ? -result : result);
}

t_float			ft_sin(t_float t)
{
	t_float		result;
	t_bool		sign; //True for negative
	t_float		t_p2;
	t_float		t_p3;
	t_float		t_p5;
	t_float		t_p7;
	t_float		t_p9;
	t_float		t_p11;
	t_float		t_p13;

	sign = 0;
	if (t < 0.)
	{
		t = -t;
		sign = !sign;
	}
	if (t > TAU)
		t = ft_fmod(t, TAU);
	if (t > PI)
	{
		t = PI - (t - PI);
		sign = !sign;
	}
	if (t > HALF_PI)
		t = HALF_PI - (t - HALF_PI);

	t_p2 = t * t;
	t_p3 = t * t_p2;
	t_p5 = t_p2 * t_p3;
	t_p7 = t_p2 * t_p5;
	t_p9 = t_p2 * t_p7;
	t_p11 = t_p2 * t_p9;
	t_p13 = t_p2 * t_p11;

	result = t;
	result -= t_p3 * inv_factorial(3);
	result += t_p5 * inv_factorial(5);
	result -= t_p7 * inv_factorial(7);
	result += t_p9 * inv_factorial(9);
	result -= t_p11 * inv_factorial(11);
	result += t_p13 * inv_factorial(13);
	result -= t_p13 * t_p2 * inv_factorial(15);

	return (sign ? -result : result);
}

// TODO implement homemade
#include <math.h>
t_float		ft_atan2(t_float x, t_float y)
{
/*
	t_float t = (t_float)y / (t_float)x;
	// approximate arctan2 voodoo magic
	t_float angle = 0.141499 * t - 0.343315;
	angle = angle * t - 0.016224;
	angle = angle * t + 1.003839;
	angle = angle * t - 0.000158;
*/
	return (atan2(x, y));
}
