/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/ft_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_math.h"
#include "../../libft_memory.h"



t_float		ft_exp(t_float x)
{
	t_float		result;
	t_float		result_prev;
	t_float		acc_x;
	t_float		acc_i;
	t_u32		i;

	if (x < 100.)
		return (0.);
	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	result_prev = 0.;
	while (ABS(result - result_prev) > FLOAT_BIAS)
	{
		result_prev = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
}



/*
** The following pair of functions return the natural logarithm of x.
** ln(x) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
**
** FLOAT_EXPONENT_ZERO is exponent bits except the MSB for exponent:
** this corresponds precisely to an exponent of zero when unbiased.
*/
static t_float	ft_ln_taylor_series(t_float x)
{
	t_float	result;
	t_float	result_previous;
	t_float	power;
	t_float	i;

	i = 2.;
	power = x;
	result = x;
	result_previous = NAN;
	while (ABS(power) > FLOAT_BIAS)
	{
		power *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (power / i);
		if (result == result_previous)
			break ;
		result_previous = result;
		++i;
	}
	return (result);
}

t_float			ft_ln(t_float x)
{
	static const t_float LN_3_2			= (t_float)0x1.9F323ECBF984Cp-2;
	static const t_float DIV_2_3		= (t_float)0x1.5555555555556p-1;
	t_float	result;
	t_u64	tmp = 0;	// a raw memory copy
	t_u64	norm = 0;	// the float x in x*2^n in raw memory
	t_s32	exp_b2;

	if (x < 0.)
		return (NAN);
	if (x == 0.)
		return (-INFINITY);
	if (x == 1.)
		return (0.);
	if (x == INFINITY)
		return (INFINITY);
	if (x < 1. || 2. <= x)
	{
		ft_memcpy(&tmp, &x, sizeof(t_float));
		norm = (tmp & FLOAT_MANTISSA_SIGNED) | FLOAT_EXPONENT_ZERO;
		ft_memcpy(&x, &norm, sizeof(t_float));
		result = ft_ln(x);
		exp_b2 = ((tmp << 1) >> (FLOAT_MANTISSA_BITS + 1)) - FLOAT_EXPONENT_BIAS;
		return (LN_2 * exp_b2 + result);
	}
	if (1.9 <= x && x < 2.)
		return (ft_ln(x * DIV_2_3) + LN_3_2);
	result = ft_ln_taylor_series(x - 1.);
	return (result);
}



inline t_float	ft_lg(t_float x)
{
	return (ft_ln(x) / LN_2);
}



inline t_float	ft_log(t_float x)
{
	return (ft_ln(x) / LN_10);
}



inline t_float	ft_logn(t_float x, t_float n)
{
	if (n == 2)
		return (ft_lg(x));
	else if (n == 10)
		return (ft_log(x));
	else
		return (ft_ln(x) / ft_ln(n));
}
