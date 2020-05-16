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
#define LIBFT_COLOR_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Color_ARGB16_Get_A(color)						ft_color_argb16_get_a(color)
#define Color_ARGB16_Get_R(color)						ft_color_argb16_get_r(color)
#define Color_ARGB16_Get_G(color)						ft_color_argb16_get_g(color)
#define Color_ARGB16_Get_B(color)						ft_color_argb16_get_b(color)
#define Color_ARGB16_GetNearest(target, colors, n)		ft_color_argb16_get_nearest(target, colors, n)
#define Color_ARGB16_Set_A(color, a)					ft_color_argb16_set_a(color, a)
#define Color_ARGB16_Set_R(color, r)					ft_color_argb16_set_r(color, r)
#define Color_ARGB16_Set_G(color, g)					ft_color_argb16_set_g(color, g)
#define Color_ARGB16_Set_B(color, b)					ft_color_argb16_set_b(color, b)
#define Color_ARGB16_Set(a, r, g, b)					ft_color_argb16_set(a, r, g, b)

#define Color_ARGB32_Get_A(color)						ft_color_argb32_get_a(color)
#define Color_ARGB32_Get_R(color)						ft_color_argb32_get_r(color)
#define Color_ARGB32_Get_G(color)						ft_color_argb32_get_g(color)
#define Color_ARGB32_Get_B(color)						ft_color_argb32_get_b(color)
#define Color_ARGB32_GetNearest(target, colors, n)		ft_color_argb32_get_nearest(target, colors, n)
#define Color_ARGB32_Set_A(color, a)					ft_color_argb32_set_a(color, a)
#define Color_ARGB32_Set_R(color, r)					ft_color_argb32_set_r(color, r)
#define Color_ARGB32_Set_G(color, g)					ft_color_argb32_set_g(color, g)
#define Color_ARGB32_Set_B(color, b)					ft_color_argb32_set_b(color, b)
#define Color_ARGB32_Set(a, r, g, b)					ft_color_argb32_set(a, r, g, b)



/*
** ************************************************************************** *|
**                              ARGB 16bit Color                              *|
** ************************************************************************** *|
*/

/*
**	Color channel bitmasks
*/
# define COLOR_ARGB16_A	0b1000000000000000
# define COLOR_ARGB16_R	0b0111110000000000
# define COLOR_ARGB16_G	0b0000001111100000
# define COLOR_ARGB16_B	0b0000000000011111



/*
**	Gets the alpha channel value for the given 16-bit color (0 or 1)
*/
t_u8	ft_color_argb16_get_a(t_u16 color);
/*
**	Gets the red channel value for the given 16-bit color (0-31)
*/
t_u8	ft_color_argb16_get_r(t_u16 color);
/*
**	Gets the green channel value for the given 16-bit color (0-31)
*/
t_u8	ft_color_argb16_get_g(t_u16 color);
/*
**	Gets the blue channel value for the given 16-bit color (0-31)
*/
t_u8	ft_color_argb16_get_b(t_u16 color);

/*
**	Returns a pointer to the color within 'colors' which is the closest match
**	to the given 'target' color, searching through 'n' colors in the array.
*/
t_u16	*ft_color_argb16_get_nearest(t_u16 target, t_u16 *colors, size_t n);



/*
**	Returns the given 16-bit color, with the given alpha channel value (0 or 1)
*/
t_u16	ft_color_argb16_set_a(t_u16 color, t_u8 a);
/*
**	Returns the given 16-bit color, with the given red channel value (0-31)
*/
t_u16	ft_color_argb16_set_r(t_u16 color, t_u8 r);
/*
**	Returns the given 16-bit color, with the given green channel value (0-31)
*/
t_u16	ft_color_argb16_set_g(t_u16 color, t_u8 g);
/*
**	Returns the given 16-bit color, with the given blue channel value (0-31)
*/
t_u16	ft_color_argb16_set_b(t_u16 color, t_u8 b);

/*
**	Returns a 16-bit color from the given channel values
*/
t_u16	ft_color_argb16_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);



/*
**	Converts the given 16-bit color value to its 32-bit equivalent
*/
t_u32	ft_color_argb16_to_argb32(t_u16 color);



/*
** ************************************************************************** *|
**                              ARGB 32bit Color                              *|
** ************************************************************************** *|
*/

/*
**	Color channel bitmasks
*/
# define COLOR_ARGB32_A	0xFF000000
# define COLOR_ARGB32_R	0x00FF0000
# define COLOR_ARGB32_G	0x0000FF00
# define COLOR_ARGB32_B	0x000000FF



/*
**	Gets the alpha channel value for the given 32-bit color (0-255)
*/
t_u8	ft_color_argb32_get_a(t_u32 color);
/*
**	Gets the red channel value for the given 32-bit color (0-255)
*/
t_u8	ft_color_argb32_get_r(t_u32 color);
/*
**	Gets the green channel value for the given 32-bit color (0-255)
*/
t_u8	ft_color_argb32_get_g(t_u32 color);
/*
**	Gets the blue channel value for the given 32-bit color (0-255)
*/
t_u8	ft_color_argb32_get_b(t_u32 color);

/*
**	Returns a pointer to the color within 'colors' which is the closest match
**	to the given 'target' color, searching through 'n' colors in the array.
*/
t_u32	*ft_color_argb32_get_nearest(t_u32 target, t_u32 *colors, size_t n);



/*
**	Returns the given 32-bit color, with the given alpha channel value (0-255)
*/
t_u32	ft_color_argb32_set_a(t_u32 color, t_u8 a);
/*
**	Returns the given 32-bit color, with the given red channel value (0-255)
*/
t_u32	ft_color_argb32_set_r(t_u32 color, t_u8 r);
/*
**	Returns the given 32-bit color, with the given green channel value (0-255)
*/
t_u32	ft_color_argb32_set_g(t_u32 color, t_u8 g);
/*
**	Returns the given 32-bit color, with the given blue channel value (0-255)
*/
t_u32	ft_color_argb32_set_b(t_u32 color, t_u8 b);

/*
**	Returns a 32-bit color value from the given channel values
*/
t_u32	ft_color_argb32_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);



/*
**	Converts the given 32-bit color value to its 16-bit equivalent (rounding down values)
*/
t_u16	ft_color_argb32_to_argb16(t_u32 color);

#endif
