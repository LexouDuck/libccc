/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color/ft_color_argb16_set.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_color.h"



inline t_argb16	ft_color_argb16_set_a(t_argb16 color, t_u8 a)
{
	return ((color & ~COLOR_ARGB16_A) | (a << 15));
}

inline t_argb16	ft_color_argb16_set_r(t_argb16 color, t_u8 r)
{
	return ((color & ~COLOR_ARGB16_R) | (r << 10));
}

inline t_argb16	ft_color_argb16_set_g(t_argb16 color, t_u8 g)
{
	return ((color & ~COLOR_ARGB16_G) | (g << 5));
}

inline t_argb16	ft_color_argb16_set_b(t_argb16 color, t_u8 b)
{
	return ((color & ~COLOR_ARGB16_B) | (b));
}



inline t_argb16	ft_color_argb16_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_argb16)(((a ? 1 : 0) << 15)
		| ((r & COLOR_ARGB16_CHANNEL) << 10)
		| ((g & COLOR_ARGB16_CHANNEL) << 5)
		| ((b & COLOR_ARGB16_CHANNEL))));
}
