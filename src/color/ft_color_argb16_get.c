/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color/ft_color_argb16_get.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"



inline t_u8		ft_color_argb16_get_a(t_u16 color)
{
	return ((t_u8)(color >> 15));
}

inline t_u8		ft_color_argb16_get_r(t_u16 color)
{
	return ((t_u8)(0x1F & (color >> 10)));
}

inline t_u8		ft_color_argb16_get_g(t_u16 color)
{
	return ((t_u8)(0x1F & (color >> 5)));
}

inline t_u8		ft_color_argb16_get_b(t_u16 color)
{
	return ((t_u8)(0x1F & color));
}

t_u16			*ft_color_argb16_get_nearest(
	t_u16 target,
	t_u16 *colors,
	size_t n)
{
	t_s8	r;
	t_s8	g;
	t_s8	b;
	t_u16	min;
	t_u16	*result;

#if HANDLE_NULLPOINTERS
	if (colors == NULL)
		return (NULL);
#endif
	min = 0xFFFF;
	result = NULL;
	while (n--)
	{
		r = ft_color_argb16_get_r(target) - ft_color_argb16_get_r(colors[n]);
		g = ft_color_argb16_get_g(target) - ft_color_argb16_get_g(colors[n]);
		b = ft_color_argb16_get_b(target) - ft_color_argb16_get_b(colors[n]);
		r = (r < 0) ? -r : r;
		g = (g < 0) ? -g : g;
		b = (b < 0) ? -b : b;
		if ((t_u16)(r + g + b) < min)
		{
			min = (r + g + b);
			result = (colors + n);
		}
	}
	return (result);
}
