/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color/ft_color_argb32_set.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"



inline t_argb32	ft_color_argb32_set_a(t_argb32 color, t_u8 a)
{
	return ((color & ~COLOR_ARGB32_A) | (a << 24));
}

inline t_argb32	ft_color_argb32_set_r(t_argb32 color, t_u8 r)
{
	return ((color & ~COLOR_ARGB32_R) | (r << 16));
}

inline t_argb32	ft_color_argb32_set_g(t_argb32 color, t_u8 g)
{
	return ((color & ~COLOR_ARGB32_G) | (g << 8));
}

inline t_argb32	ft_color_argb32_set_b(t_argb32 color, t_u8 b)
{
	return ((color & ~COLOR_ARGB32_B) | (b));
}



inline t_argb32	ft_color_argb32_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb32)(((a & COLOR_ARGB32_CHANNEL) << 24)
		| ((r & COLOR_ARGB32_CHANNEL) << 16)
		| ((g & COLOR_ARGB32_CHANNEL) << 8)
		| ((b & COLOR_ARGB32_CHANNEL))));
}
