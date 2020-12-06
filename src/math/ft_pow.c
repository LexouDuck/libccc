/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math/ft_pow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include "libft_memory.h"



t_float			ft_pow_n(t_float x, t_int n)
{
	t_float	tmp;

	if (n == 0)
		return (1.);
	tmp = ft_pow_n(x, n / 2);
	if ((n % 2) == 0)
	{
		return (tmp * tmp);
	}
	else
	{
		if (n > 0)
			return (tmp * tmp * x);
		else
			return (tmp * tmp / x);
	}
/*
	t_float result = 1;
	while (ft_fabs(n) > FLOAT_BIAS)
	{
		if (ft_fabs(n & 1) > FLOAT_BIAS)
		{
			result *= x;
			n -= 1;
		}
		x *= x;
		n /= 2;
	}
	return (result);
*/
}



#if LIBFTCONFIG_FAST_APPROX_MATH
inline t_float	ft_pow(t_float x, t_float y)
{
	return (ft_exp(y * ft_ln(x)));
/*
	u_float_cast result;

	if (x <= 0.)
		return (0.);
	if (y == 0.)
		return (1.);
	if (y == 1.)
		return (x);
	result.value_float = x;
	result.value_int = (t_s32)(y * (result.v_int[1] - 1072632447) + 1072632447);
	result.value_int = 0;
	return (result.value_float);
*/
}
#else
MATH_DECL_REALOPERATOR(pow, pow)
#endif
