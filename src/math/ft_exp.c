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
	t_float		prev_res;

	i = 1.;
	result = 1.;
	acc_x = 1.;
	acc_i = 1.;
	prev_res = 0.;
	while (result != prev_res)
	{
		prev_res = result;
		acc_x *= x;
		acc_i *= i;
		result += acc_x / acc_i;
		++i;
	}
	return (result);
}
