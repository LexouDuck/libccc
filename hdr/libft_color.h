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
/*! @file libft_color.h
**	This header defines all the functions/bitmasks for encoding colors in ints.
**	@addtogroup libft_color
**	@{
*/
// TODO add AHSL32 color typedef + conversion functions
// TODO add conversion functions for float-color structs

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This typedef represents an unsigned 16-bit number which stores an ARGB 1555 color
typedef t_u16	t_argb16;
//! The maximum possible value for one color channel of an ARGB16 color (0-31)
#define COLOR_ARGB16_CHANNEL	(31)

#define COLOR_ARGB16_A	(0x8000)	//!< 0b 10000000 00000000	bitmask for the 16-bit color's alpha channel (0 or 1)
#define COLOR_ARGB16_B	(0x7C00)	//!< 0b 01111100 00000000	bitmask for the 16-bit color's blue channel  (0-31)
#define COLOR_ARGB16_G	(0x03E0)	//!< 0b 00000011 11100000	bitmask for the 16-bit color's green channel (0-31)
#define COLOR_ARGB16_R	(0x001F)	//!< 0b 00000000 00011111	bitmask for the 16-bit color's red channel	 (0-31)



//! This typedef represents an unsigned 32-bit number which stores an ARGB 8888 color
typedef t_u32	t_argb32;
//! The maximum possible value for one color channel of an ARGB16 color (0-255)
#define COLOR_ARGB32_CHANNEL	(255)

#define COLOR_ARGB32_A	(0xFF000000)	// bitmask for the 32-bit color's alpha channel	(0-255)
#define COLOR_ARGB32_R	(0x00FF0000)	// bitmask for the 32-bit color's red channel	(0-255)
#define COLOR_ARGB32_G	(0x0000FF00)	// bitmask for the 32-bit color's green channel	(0-255)
#define COLOR_ARGB32_B	(0x000000FF)	// bitmask for the 32-bit color's blue channel	(0-255)



//! A struct to store color values with each channel (red,green,blue) as floats
typedef struct	s_rgb_
{
	t_float		r;			//! The red channel of this color
	t_float		g;			//! The green channel of this color
	t_float		b;			//! The blue channel of this color
}				s_rgb;

//! A struct to store color values with each channel (hue,sat,lum) as floats
typedef struct	s_hsl_
{
	t_float		h;			//! The hue value of this color
	t_float		s;			//! The saturation value of this color
	t_float		l;			//! The luminance/brightness value of this color
}				s_hsl;



//! A struct to store color values with each channel (alpha,red,green,blue) as floats
typedef struct		s_argb_
{
	t_float		a;			//! The alpha channel of this color (transparency)
	t_float		r;			//! The red channel of this color
	t_float		g;			//! The green channel of this color
	t_float		b;			//! The blue channel of this color
}					s_argb;

//! A struct to store color values with each channel (alpha,hue,sat,lum) as floats
typedef struct		s_ahsl_
{
	t_float		a;			//! The alpha channel of this color (transparency)
	t_float		h;			//! The hue value of this color
	t_float		s;			//! The saturation value of this color
	t_float		l;			//! The luminance/brightness value of this color
}					s_ahsl;



/*
** ************************************************************************** *|
**                              ARGB 16bit Color                              *|
** ************************************************************************** *|
*/

//! Gets the alpha channel value for the given 16-bit 'color'
t_u8							Color_ARGB16_Get_A(t_argb16 color);
#define ft_color_argb16_get_a	Color_ARGB16_Get_A
//! Gets the red channel value for the given 16-bit 'color'
t_u8							Color_ARGB16_Get_R(t_argb16 color);
#define ft_color_argb16_get_r	Color_ARGB16_Get_R
//! Gets the green channel value for the given 16-bit 'color'
t_u8							Color_ARGB16_Get_G(t_argb16 color);
#define ft_color_argb16_get_g	Color_ARGB16_Get_G
//! Gets the blue channel value for the given 16-bit 'color'
t_u8							Color_ARGB16_Get_B(t_argb16 color);
#define ft_color_argb16_get_b	Color_ARGB16_Get_B

//! Find the nearest color to the given 'target' color, from within the given arrays of 'colors'
/*!
**	@param	target	The desired color, for which the nearest will be returned
**	@param	colors	The array of different colors to check against
**	@param	n		The amount of colors to check in the 'colors' array
**	@return a pointer to the color within 'colors' which is the closest match
**			to the given 'target' color, searching through 'n' colors in the array.
*/
t_argb16*						Color_ARGB16_GetNearest(t_argb16 target, t_argb16* colors, t_size n);
#define ft_color_argb16_nearest	Color_ARGB16_GetNearest



//! Returns the given 16-bit 'color', with the 'a' channel value changed
t_argb16						Color_ARGB16_Set_A(t_argb16 color, t_u8 a);
#define ft_color_argb16_set_a	Color_ARGB16_Set_A
//! Returns the given 16-bit 'color', with the 'r' channel value changed
t_argb16						Color_ARGB16_Set_R(t_argb16 color, t_u8 r);
#define ft_color_argb16_set_r	Color_ARGB16_Set_R
//! Returns the given 16-bit 'color', with the 'g' channel value changed
t_argb16						Color_ARGB16_Set_G(t_argb16 color, t_u8 g);
#define ft_color_argb16_set_g	Color_ARGB16_Set_G
//! Returns the given 16-bit 'color', with the 'b' channel value changed
t_argb16						Color_ARGB16_Set_B(t_argb16 color, t_u8 b);
#define ft_color_argb16_set_b	Color_ARGB16_Set_B

//! Create a 16-bit color from the given channel values
/*!
**	This function creates a new uint color value from the four given
**	individual color channel values.
**
**	@param	a	The alpha channel value (0-1)
**	@param	r	The red channel value (0-31)
**	@param	g	The green channel value (0-31)
**	@param	b	The blue channel value (0-31)
**	@return the 16-bit color value from the given channel values
*/
t_argb16						Color_ARGB16_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);
#define ft_color_argb16_set		Color_ARGB16_Set

//! Converts the given 16-bit color value to its 32-bit equivalent
/*!
**	@param	color	The 16-bit color to convert
**	@return a 32-bit ARGB color by multiplying the color channel
**			values of the given 16-bit 'color' value.
*/
t_argb32							Color_ARGB16_To_ARGB32(t_argb16 color);
#define ft_color_argb16_to_argb32	Color_ARGB16_To_ARGB32



/*
** ************************************************************************** *|
**                              ARGB 32bit Color                              *|
** ************************************************************************** *|
*/

//! Gets the alpha channel value for the given 32-bit 'color'
t_u8							Color_ARGB32_Get_A(t_argb32 color);
#define ft_color_argb32_get_a	Color_ARGB32_Get_A
//! Gets the red channel value for the given 32-bit 'color'
t_u8							Color_ARGB32_Get_R(t_argb32 color);
#define ft_color_argb32_get_r	Color_ARGB32_Get_R
//! Gets the green channel value for the given 32-bit 'color'
t_u8							Color_ARGB32_Get_G(t_argb32 color);
#define ft_color_argb32_get_g	Color_ARGB32_Get_G
//! Gets the blue channel value for the given 32-bit 'color'
t_u8							Color_ARGB32_Get_B(t_argb32 color);
#define ft_color_argb32_get_b	Color_ARGB32_Get_B

//! Find the nearest color to the given 'target' color, from within the given arrays of 'colors'
/*!
**	@param	target	The desired color, for which the nearest will be returned
**	@param	colors	The array of different colors to check against
**	@param	n		The amount of colors to check in the 'colors' array
**	@return a pointer to the color within 'colors' which is the closest match
**			to the given 'target' color, searching through 'n' colors in the array.
*/
t_argb32*						Color_ARGB32_GetNearest(t_argb32 target, t_argb32* colors, t_size n);
#define ft_color_argb32_nearest	Color_ARGB32_GetNearest



//! Returns the given 32-bit 'color', with the 'a' channel value changed
t_argb32						Color_ARGB32_Set_A(t_argb32 color, t_u8 a);
#define ft_color_argb32_set_a	Color_ARGB32_Set_A
//! Returns the given 32-bit 'color', with the 'r' channel value changed
t_argb32						Color_ARGB32_Set_R(t_argb32 color, t_u8 r);
#define ft_color_argb32_set_r	Color_ARGB32_Set_R
//! Returns the given 32-bit 'color', with the 'g' channel value changed
t_argb32						Color_ARGB32_Set_G(t_argb32 color, t_u8 g);
#define ft_color_argb32_set_g	Color_ARGB32_Set_G
//! Returns the given 32-bit 'color', with the 'b' channel value changed
t_argb32						Color_ARGB32_Set_B(t_argb32 color, t_u8 b);
#define ft_color_argb32_set_b	Color_ARGB32_Set_B

//! Creates a 32-bit color value from the given channel values (alpha, red, green, blue)
/*!
**	This function creates a new 32-bit ARGB color value from
**	the given four individual color channel values.
**
**	@param	a	The alpha channel value (0-255)
**	@param	r	The red channel value (0-255)
**	@param	g	The green channel value (0-255)
**	@param	b	The blue channel value (0-255)
**	@return the 32-bit color value from the given channel values
*/
t_argb32						Color_ARGB32_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);
#define ft_color_argb32_set		Color_ARGB32_Set

//! Converts the given 32-bit color value to its 16-bit equivalent (rounding down)
/*!
**	@param	color	The 32-bit color to convert
**	@return a 16-bit ARGB color by dividing the color channel values of the
**			given 32-bit 'color' value (values are rounded down in the process).
*/
t_argb16							Color_ARGB32_To_ARGB16(t_argb32 color);
#define ft_color_argb32_to_argb16	Color_ARGB32_To_ARGB16



/*! @} */
HEADER_END
#endif
