/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_color.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COLOR_H
# define LIBFT_COLOR_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                  Macros                                    *|
** ************************************************************************** *|
*/

/*
**	#define FT_Color_ARGB16_Get_A(color)					_
**		ft_color_argb32_get_a(color)
**	#define FT_Color_ARGB16_Get_R(color)					_
**		ft_color_argb32_get_r(color)
**	#define FT_Color_ARGB16_Get_G(color)					_
**		ft_color_argb32_get_g(color)
**	#define FT_Color_ARGB16_Get_B(color)					_
**		ft_color_argb32_get_b(color)
**	#define FT_Color_ARGB16_GetNearest(target, colors, n)	_
**		ft_color_argb32_get_nearest(target, colors, n)
**	#define FT_Color_ARGB16_Set_A(color, a)					_
**		ft_color_argb32_set_a(color, a)
**	#define FT_Color_ARGB16_Set_R(color, r)					_
**		ft_color_argb32_set_r(color, r)
**	#define FT_Color_ARGB16_Set_G(color, g)					_
**		ft_color_argb32_set_g(color, g)
**	#define FT_Color_ARGB16_Set_B(color, b)					_
**		ft_color_argb32_set_b(color, b)
**	#define FT_Color_ARGB16_Set(a, r, g, b)					_
**		ft_color_argb32_set(a, r, g, b)
**
**	#define FT_Color_ARGB32_Get_A(color)					_
**		ft_color_argb32_get_a(color)
**	#define FT_Color_ARGB32_Get_R(color)					_
**		ft_color_argb32_get_r(color)
**	#define FT_Color_ARGB32_Get_G(color)					_
**		ft_color_argb32_get_g(color)
**	#define FT_Color_ARGB32_Get_B(color)					_
**		ft_color_argb32_get_b(color)
**	#define FT_Color_ARGB32_GetNearest(target, colors, n)	_
**		ft_color_argb32_get_nearest(target, colors, n)
**	#define FT_Color_ARGB32_Set_A(color, a)					_
**		ft_color_argb32_set_a(color, a)
**	#define FT_Color_ARGB32_Set_R(color, r)					_
**		ft_color_argb32_set_r(color, r)
**	#define FT_Color_ARGB32_Set_G(color, g)					_
**		ft_color_argb32_set_g(color, g)
**	#define FT_Color_ARGB32_Set_B(color, b)					_
**		ft_color_argb32_set_b(color, b)
**	#define FT_Color_ARGB32_Set(a, r, g, b)					_
**		ft_color_argb32_set(a, r, g, b)
*/

/*
** ************************************************************************** *|
**                              ARGB 16bit Color                              *|
** ************************************************************************** *|
*/

# define COLOR_ARGB16_A	0b1000000000000000
# define COLOR_ARGB16_R	0b0111110000000000
# define COLOR_ARGB16_G	0b0000001111100000
# define COLOR_ARGB16_B	0b0000000000011111

t_u8	ft_color_argb16_get_a(t_u16 color);
t_u8	ft_color_argb16_get_r(t_u16 color);
t_u8	ft_color_argb16_get_g(t_u16 color);
t_u8	ft_color_argb16_get_b(t_u16 color);
/*
**	Returns a pointer to the color within 'colors' which is the closest match
**	to the given 'target' color, searching through 'n' colors.
*/
t_u16	*ft_color_argb16_get_nearest(t_u16 target, t_u16 *colors, size_t n);

t_u16	ft_color_argb16_set_a(t_u16 color, t_u8 a);
t_u16	ft_color_argb16_set_r(t_u16 color, t_u8 r);
t_u16	ft_color_argb16_set_g(t_u16 color, t_u8 g);
t_u16	ft_color_argb16_set_b(t_u16 color, t_u8 b);
t_u16	ft_color_argb16_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);

t_u32	ft_color_argb16_to_argb32(t_u16 color);

/*
** ************************************************************************** *|
**                              ARGB 32bit Color                              *|
** ************************************************************************** *|
*/

# define COLOR_ARGB32_A	0xFF000000
# define COLOR_ARGB32_R	0x00FF0000
# define COLOR_ARGB32_G	0x0000FF00
# define COLOR_ARGB32_B	0x000000FF

t_u8	ft_color_argb32_get_a(t_u32 color);
t_u8	ft_color_argb32_get_r(t_u32 color);
t_u8	ft_color_argb32_get_g(t_u32 color);
t_u8	ft_color_argb32_get_b(t_u32 color);
/*
**	Returns a pointer to the color within 'colors' which is the closest match
**	to the given 'target' color, searching through 'n' colors.
*/
t_u32	*ft_color_argb32_get_nearest(t_u32 target, t_u32 *colors, size_t n);

t_u32	ft_color_argb32_set_a(t_u32 color, t_u8 a);
t_u32	ft_color_argb32_set_r(t_u32 color, t_u8 r);
t_u32	ft_color_argb32_set_g(t_u32 color, t_u8 g);
t_u32	ft_color_argb32_set_b(t_u32 color, t_u8 b);
t_u32	ft_color_argb32_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);

t_u16	ft_color_argb32_to_argb16(t_u32 color);

#endif
