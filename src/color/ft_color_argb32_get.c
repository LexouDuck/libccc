/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color/ft_color_argb32_get.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"



inline t_u8		ft_color_argb32_get_a(t_u32 color)
{
	return ((t_u8)(0xFF & (color >> 24)));
}

inline t_u8		ft_color_argb32_get_r(t_u32 color)
{
	return ((t_u8)(0xFF & (color >> 16)));
}

inline t_u8		ft_color_argb32_get_g(t_u32 color)
{
	return ((t_u8)(0xFF & (color >> 8)));
}

inline t_u8		ft_color_argb32_get_b(t_u32 color)
{
	return ((t_u8)(0xFF & color));
}

t_u32			*ft_color_argb32_get_nearest(
	t_u32 target,
	t_u32 *colors,
	t_size n)
{
	t_s16	r;
	t_s16	g;
	t_s16	b;
	t_u32	min;
	t_u32	*result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min = 0xFFFFFFFF;
	result = NULL;
	while (n--)
	{
		r = ft_color_argb32_get_r(target) - ft_color_argb32_get_r(colors[n]);
		g = ft_color_argb32_get_g(target) - ft_color_argb32_get_g(colors[n]);
		b = ft_color_argb32_get_b(target) - ft_color_argb32_get_b(colors[n]);
		r = (r < 0) ? -r : r;
		g = (g < 0) ? -g : g;
		b = (b < 0) ? -b : b;
		if ((t_u32)(r + g + b) < min)
		{
			min = (r + g + b);
			result = (colors + n);
		}
	}
	return (result);
}
