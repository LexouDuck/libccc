/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color/ft_color_argb16_to.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"



t_u32	ft_color_argb16_to_argb32(t_u16 color)
{
	static const t_float	factor = (float)COLOR_ARGB32_CHANNEL / (float)COLOR_ARGB16_CHANNEL;
	t_u32					result;

	result = (color & COLOR_ARGB16_A) ? COLOR_ARGB32_A : 0;
	result |= (t_u32)(ft_color_argb16_get_r(color) * factor);
	result |= (t_u32)(ft_color_argb16_get_g(color) * factor);
	result |= (t_u32)(ft_color_argb16_get_b(color) * factor);
	return (result);
}
