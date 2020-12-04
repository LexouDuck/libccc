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



inline t_u8		ft_color_argb32_get_a(t_argb32 color)
{
	return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> 24)));
}

inline t_u8		ft_color_argb32_get_r(t_argb32 color)
{
	return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> 16)));
}

inline t_u8		ft_color_argb32_get_g(t_argb32 color)
{
	return ((t_u8)(COLOR_ARGB32_CHANNEL & (color >> 8)));
}

inline t_u8		ft_color_argb32_get_b(t_argb32 color)
{
	return ((t_u8)(COLOR_ARGB32_CHANNEL & color));
}

t_argb32*		ft_color_argb32_get_nearest(
	t_argb32 target,
	t_argb32* colors,
	t_size n)
{
	t_s16 r;
	t_s16 g;
	t_s16 b;
	t_s16 min_diff;
	t_argb32* result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min_diff = S16_MAX;
	result = NULL;
	while (n--)
	{
		r = ft_color_argb32_get_r(target) - ft_color_argb32_get_r(colors[n]);
		g = ft_color_argb32_get_g(target) - ft_color_argb32_get_g(colors[n]);
		b = ft_color_argb32_get_b(target) - ft_color_argb32_get_b(colors[n]);
		r = (r < 0) ? -r : r;
		g = (g < 0) ? -g : g;
		b = (b < 0) ? -b : b;
		if ((r + g + b) < min_diff)
		{
			min_diff = (r + g + b);
			result = (colors + n);
		}
	}
	return (result);
}
