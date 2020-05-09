/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color/ft_color_argb32_to.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"

t_u16	ft_color_argb32_to_argb16(t_u32 color)
{
	t_u32					result;

	result = (color & COLOR_ARGB32_A) ? COLOR_ARGB16_A : 0;
	result |= (ft_color_argb16_get_r(color) >> 3) << 10;
	result |= (ft_color_argb16_get_g(color) >> 3) << 5;
	result |= (ft_color_argb16_get_b(color) >> 3) << 0;
	return (result);
}
