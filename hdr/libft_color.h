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

#ifndef __LIBFT_COLOR_H
#define __LIBFT_COLOR_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Color_ARGB16_Get_A			ft_color_argb16_get_a
#define Color_ARGB16_Get_R			ft_color_argb16_get_r
#define Color_ARGB16_Get_G			ft_color_argb16_get_g
#define Color_ARGB16_Get_B			ft_color_argb16_get_b
#define Color_ARGB16_GetNearest		ft_color_argb16_get_nearest
#define Color_ARGB16_Set_A			ft_color_argb16_set_a
#define Color_ARGB16_Set_R			ft_color_argb16_set_r
#define Color_ARGB16_Set_G			ft_color_argb16_set_g
#define Color_ARGB16_Set_B			ft_color_argb16_set_b
#define Color_ARGB16_Set			ft_color_argb16_set

#define Color_ARGB32_Get_A			ft_color_argb32_get_a
#define Color_ARGB32_Get_R			ft_color_argb32_get_r
#define Color_ARGB32_Get_G			ft_color_argb32_get_g
#define Color_ARGB32_Get_B			ft_color_argb32_get_b
#define Color_ARGB32_GetNearest		ft_color_argb32_get_nearest
#define Color_ARGB32_Set_A			ft_color_argb32_set_a
#define Color_ARGB32_Set_R			ft_color_argb32_set_r
#define Color_ARGB32_Set_G			ft_color_argb32_set_g
#define Color_ARGB32_Set_B			ft_color_argb32_set_b
#define Color_ARGB32_Set			ft_color_argb32_set



/*
** ************************************************************************** *|
**                              ARGB 16bit Color                              *|
** ************************************************************************** *|
*/

/*
**	Color channel bitmasks
*/
# define COLOR_ARGB16_A	0x8000 // 0b 10000000 00000000	// alpha (0 or 1)
# define COLOR_ARGB16_B	0x7C00 // 0b 01111100 00000000	// blue  (0-31)
# define COLOR_ARGB16_G	0x03E0 // 0b 00000011 11100000	// green (0-31)
# define COLOR_ARGB16_R	0x001F // 0b 00000000 00011111	// red	 (0-31)



/*
**	Gets the channel values for the given 16-bit color
*/
t_u8	ft_color_argb16_get_a(t_u16 color);
t_u8	ft_color_argb16_get_r(t_u16 color);
t_u8	ft_color_argb16_get_g(t_u16 color);
t_u8	ft_color_argb16_get_b(t_u16 color);

/*
**	Returns a pointer to the color within 'colors' which is the closest match
**	to the given 'target' color, searching through 'n' colors in the array.
*/
t_u16	*ft_color_argb16_get_nearest(t_u16 target, t_u16 *colors, t_size n);



/*
**	Returns the given 16-bit 'color', with the given channel value changed
*/
t_u16	ft_color_argb16_set_a(t_u16 color, t_u8 a);
t_u16	ft_color_argb16_set_r(t_u16 color, t_u8 r);
t_u16	ft_color_argb16_set_g(t_u16 color, t_u8 g);
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
# define COLOR_ARGB32_A	0xFF000000	// alpha (0-255)
# define COLOR_ARGB32_R	0x00FF0000	// red	 (0-255)
# define COLOR_ARGB32_G	0x0000FF00	// green (0-255)
# define COLOR_ARGB32_B	0x000000FF	// blue	 (0-255)



/*
**	Gets the channel values for the given 32-bit color
*/
t_u8	ft_color_argb32_get_a(t_u32 color);
t_u8	ft_color_argb32_get_r(t_u32 color);
t_u8	ft_color_argb32_get_g(t_u32 color);
t_u8	ft_color_argb32_get_b(t_u32 color);

/*
**	Returns a pointer to the color within 'colors' which is the closest match
**	to the given 'target' color, searching through 'n' colors in the array.
*/
t_u32	*ft_color_argb32_get_nearest(t_u32 target, t_u32 *colors, t_size n);



/*
**	Returns the given 32-bit 'color', with the given channel value changed
*/
t_u32	ft_color_argb32_set_a(t_u32 color, t_u8 a);
t_u32	ft_color_argb32_set_r(t_u32 color, t_u8 r);
t_u32	ft_color_argb32_set_g(t_u32 color, t_u8 g);
t_u32	ft_color_argb32_set_b(t_u32 color, t_u8 b);

/*
**	Returns a 32-bit color value from the given channel values
*/
t_u32	ft_color_argb32_set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);



/*
**	Converts the given 32-bit color value to its 16-bit equivalent (rounding down values)
*/
t_u16	ft_color_argb32_to_argb16(t_u32 color);

HEADER_END
#endif
