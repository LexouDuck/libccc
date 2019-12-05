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
	t_float		i;
	t_float		acc_i;
	t_float		acc_x;
	t_float		result;
	t_float		result_prev;

	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	result_prev = 0.;
	while (abs(result - result_prev) > FLOAT_BIAS)
	{
		result_prev = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
}
