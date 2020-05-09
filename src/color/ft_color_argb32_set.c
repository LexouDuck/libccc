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



inline t_u32	ft_color_argb32_set_a(t_u32 color, t_u8 a)
{
	return ((color & ~COLOR_ARGB32_A) | (a << 24));
}

inline t_u32	ft_color_argb32_set_r(t_u32 color, t_u8 r)
{
	return ((color & ~COLOR_ARGB32_R) | (r << 16));
}

inline t_u32	ft_color_argb32_set_g(t_u32 color, t_u8 g)
{
	return ((color & ~COLOR_ARGB32_G) | (g << 8));
}

inline t_u32	ft_color_argb32_set_b(t_u32 color, t_u8 b)
{
	return ((color & ~COLOR_ARGB32_B) | b);
}

inline t_u32	ft_color_argb32_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b)
{
	return ((t_u32)((a << 24) | (r << 16) | (g << 8) | b));
}
