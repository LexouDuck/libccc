/*============================================================================*\
||                                            ______________________________  ||
||  libccc/image/color.h                           |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_IMAGE_COLOR_H
#define __LIBCCC_IMAGE_COLOR_H
/*!@group{libccc_image_color,20,libccc/image/color.h}
**
**	This header defines all the functions/bitmasks for encoding colors in ints.
*/

// TODO add AHSL32 color typedef + conversion functions
// TODO add conversion functions for float-color structs

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_IMAGE_COLOR_T
#define __LIBCCC_IMAGE_COLOR_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//!@doc This type represents an unsigned 16-bit number which stores an ARGB 1555 color
//!@{
typedef u16_t	t_argb16;
TYPEDEF_ALIAS(	t_argb16, COLOR_ARGB16, PRIMITIVE)
//!@}
#define COLOR_ARGB16_NULL	(t_argb16)(0)

//!@doc Bitmask macros for the 16-bit ARGB color encoding type
//!@{
#define COLOR_ARGB16_CHANNEL	(0x1F)	//!< The maximum possible value for one color channel of an ARGB16 color `[0, 31]`

#define COLOR_ARGB16_R_BITINDEX	( 0)	//!< The bit index for the 16-bit color's red channel   `[0, 31]`
#define COLOR_ARGB16_G_BITINDEX	( 5)	//!< The bit index for the 16-bit color's green channel `[0, 31]`
#define COLOR_ARGB16_B_BITINDEX	(10)	//!< The bit index for the 16-bit color's blue channel  `[0, 31]`
#define COLOR_ARGB16_A_BITINDEX	(15)	//!< The bit index for the 16-bit color's alpha channel `(0 or 1)`

#define COLOR_ARGB16_R	(COLOR_ARGB16_CHANNEL << COLOR_ARGB16_R_BITINDEX)	//!< `0b0000000000011111` or `0x001F` - bitmask for the 16-bit color's red channel   `[0, 31]`
#define COLOR_ARGB16_G	(COLOR_ARGB16_CHANNEL << COLOR_ARGB16_G_BITINDEX)	//!< `0b0000001111100000` or `0x03E0` - bitmask for the 16-bit color's green channel `[0, 31]`
#define COLOR_ARGB16_B	(COLOR_ARGB16_CHANNEL << COLOR_ARGB16_B_BITINDEX)	//!< `0b0111110000000000` or `0x7C00` - bitmask for the 16-bit color's blue channel  `[0, 31]`
#define COLOR_ARGB16_A					(0x01 << COLOR_ARGB16_A_BITINDEX)	//!< `0b1000000000000000` or `0x8000` - bitmask for the 16-bit color's alpha channel `(0 or 1)`
//!@}



//!@doc This type represents an unsigned 32-bit number which stores an ARGB 8888 color
//!@{
typedef u32_t	t_argb32;
TYPEDEF_ALIAS(	t_argb32, COLOR_ARGB32, PRIMITIVE)
//!@}
#define COLOR_ARGB32_NULL	(t_argb32)(0)

//!@doc Bitmask macros for the 32-bit color encoding type
//!@{
#define COLOR_ARGB32_CHANNEL	(0xFF)	//!< The maximum possible value for one color channel of an ARGB16 color `[0, 255]`

#define COLOR_ARGB32_A_BITINDEX	(24)	//!< The bit index for the 32-bit color's alpha channel `[0, 255]`
#define COLOR_ARGB32_R_BITINDEX	(16)	//!< The bit index for the 32-bit color's red channel   `[0, 255]`
#define COLOR_ARGB32_G_BITINDEX	( 8)	//!< The bit index for the 32-bit color's green channel `[0, 255]`
#define COLOR_ARGB32_B_BITINDEX	( 0)	//!< The bit index for the 32-bit color's blue channel  `[0, 255]`

#define COLOR_ARGB32_A	(COLOR_ARGB32_CHANNEL << COLOR_ARGB32_A_BITINDEX)	//!< `0xFF000000` - bitmask for the 32-bit color's alpha channel `[0, 255]`
#define COLOR_ARGB32_R	(COLOR_ARGB32_CHANNEL << COLOR_ARGB32_R_BITINDEX)	//!< `0x00FF0000` - bitmask for the 32-bit color's red channel   `[0, 255]`
#define COLOR_ARGB32_G	(COLOR_ARGB32_CHANNEL << COLOR_ARGB32_G_BITINDEX)	//!< `0x0000FF00` - bitmask for the 32-bit color's green channel `[0, 255]`
#define COLOR_ARGB32_B	(COLOR_ARGB32_CHANNEL << COLOR_ARGB32_B_BITINDEX)	//!< `0x000000FF` - bitmask for the 32-bit color's blue channel  `[0, 255]`
//!@}



//!@doc A struct to store color values with each channel (alpha,red,green,blue) as floating-point values in the interval [0,1]
//!@{
typedef struct argb
{
	t_float		a;		//!< The alpha channel of this color `[0, 1]` (transparency)
	t_float		r;		//!< The red channel of this color   `[0, 1]`
	t_float		g;		//!< The green channel of this color `[0, 1]`
	t_float		b;		//!< The blue channel of this color  `[0, 1]`
}				s_argb;
TYPEDEF_ALIAS(	s_argb, COLOR_ARGB, STRUCT)
//!@}
//! The null default value for the #s_argb struct (all fields set to zero)
#define COLOR_ARGB_NULL	{ .a=0, .r=0, .g=0, .b=0 }



//!@doc A struct to store color values with each channel (alpha,hue,sat,lum) as floating-point values in the interval [0,1]
//!@{
typedef struct ahsl
{
	t_float		a;		//!< The alpha channel (transparency) of this color             `[0,1]`
	t_float		hue;	//!< The hue/value of this color (its angle on the color wheel) `[0, PI*2]`
	t_float		sat;	//!< The saturation value of this color (distance from center)  `[0, 1]`
	t_float		lum;	//!< The luminance/brightness value of this color (whiteness)   `[0, 1]`
}				s_ahsl;
TYPEDEF_ALIAS(	s_ahsl, COLOR_AHSL, STRUCT)
//!@}
//! The null default value for the #s_ahsl struct (all fields set to zero)
#define COLOR_AHSL_NULL	{ .a=0, .hue=0, .sat=0, .lum=0 }



#endif
#ifndef __LIBCCC_IMAGE_COLOR_F
#define __LIBCCC_IMAGE_COLOR_F

/*============================================================================*\
||                              ARGB 16bit Color                              ||
\*============================================================================*/

//!@doc Functions to get a color channel value for the given #t_argb16 color integer
//!@{
//! Gets the alpha channel value for the given 16-bit `color`
t_u8							Color_ARGB16_Get_A(t_argb16 color);
#define c_argb16geta			Color_ARGB16_Get_A
#define Color_ARGB16_Get_Alpha	Color_ARGB16_Get_A
//! Gets the red channel value for the given 16-bit `color`
t_u8							Color_ARGB16_Get_R(t_argb16 color);
#define c_argb16getr			Color_ARGB16_Get_R
#define Color_ARGB16_Get_Red	Color_ARGB16_Get_R
//! Gets the green channel value for the given 16-bit `color`
t_u8							Color_ARGB16_Get_G(t_argb16 color);
#define c_argb16getg			Color_ARGB16_Get_G
#define Color_ARGB16_Get_Green	Color_ARGB16_Get_G
//! Gets the blue channel value for the given 16-bit `color`
t_u8							Color_ARGB16_Get_B(t_argb16 color);
#define c_argb16getb			Color_ARGB16_Get_B
#define Color_ARGB16_Get_Blue	Color_ARGB16_Get_B
//!@}



//!@doc Create a 16-bit color from the given channel values
/*!
**	This function creates a new uint color value from the four given
**	individual color channel values.
**
**	@param	a	The alpha channel value (constrained to interval `[0, 1]`)
**	@param	r	The red channel value   (constrained to interval `[0, 31]`)
**	@param	g	The green channel value (constrained to interval `[0, 31]`)
**	@param	b	The blue channel value  (constrained to interval `[0, 31]`)
**	@returns
**	The 16-bit color value from the given channel values
*/
//!@{
t_argb16					Color_ARGB16_Set(t_bool a, t_u8 r, t_u8 g, t_u8 b);
#define c_argb16set			Color_ARGB16_Set
//!@}

//!@doc Functions to set a color channel value for the given #t_argb16 color integer
//!@{
//! Returns the given 16-bit `color`, with the `a` alpha channel value changed
t_argb16						Color_ARGB16_Set_A(t_argb16 color, t_bool a);
#define c_argb16seta			Color_ARGB16_Set_A
#define Color_ARGB16_Set_Alpha	Color_ARGB16_Set_A
//! Returns the given 16-bit `color`, with the `r` red channel value changed
t_argb16						Color_ARGB16_Set_R(t_argb16 color, t_u8 r);
#define c_argb16setr			Color_ARGB16_Set_R
#define Color_ARGB16_Set_Red	Color_ARGB16_Set_R
//! Returns the given 16-bit `color`, with the `g` green channel value changed
t_argb16						Color_ARGB16_Set_G(t_argb16 color, t_u8 g);
#define c_argb16setg			Color_ARGB16_Set_G
#define Color_ARGB16_Set_Green	Color_ARGB16_Set_G
//! Returns the given 16-bit `color`, with the `b` blue channel value changed
t_argb16						Color_ARGB16_Set_B(t_argb16 color, t_u8 b);
#define c_argb16setb			Color_ARGB16_Set_B
#define Color_ARGB16_Set_Blue	Color_ARGB16_Set_B
//!@}



//!@doc Converts the given 16-bit color value to its 32-bit equivalent
/*!
**	@param	color	The 16-bit color to convert
**	@returns
**	A 32-bit ARGB color integer created by multiplying the color channel
**	values of the given 16-bit `color` value.
*/
//!@{
t_argb32					Color_ARGB16_To_ARGB32(t_argb16 color);
#define c_argb16toargb32	Color_ARGB16_To_ARGB32
//!@}

//!@doc Converts the given 16-bit color value to its floating-point color equivalent
/*!
**	@param	color	The 16-bit color to convert
**	@returns
**	A floating-point ARGB color vector created by multiplying the color channel
**	values of the given 16-bit `color` value.
*/
//!@{
s_argb						Color_ARGB16_To_ARGB(t_argb16 color);
#define c_argb16toargb		Color_ARGB16_To_ARGB
//!@}



//!@doc Returns a value indicating the amount of visual difference between the two given colors
/*!
**	learn more: https://en.wikipedia.org/wiki/Color_difference
**
**	@returns
**	A human-perception-weighted euclidian squared distance between the two given colors
**	The greater the value, the more perceptually different these 2 colors are.
*/
//!@{
t_u16						Color_ARGB16_Difference(t_argb16 c1, t_argb16 c2);
#define c_argb16diff		Color_ARGB16_Difference
//!@}

//!@doc Find the nearest color to the given `target` color, from within the given arrays of `colors`
/*!
**	@param	target	The desired color, for which the nearest will be returned
**	@param	colors	The array of different colors to check against
**	@param	n		The amount of colors to check in the `colors` array
**	@returns
**	A pointer to the color within `colors` which is the closest match
**	to the given `target` color, searching through `n` colors in the array.
*/
//!@{
t_argb16 const*				Color_ARGB16_GetNearest(t_argb16 target, t_argb16 const* colors, t_size n);
#define c_argb16nearest		Color_ARGB16_GetNearest
//!@}



/*============================================================================*\
||                              ARGB 32bit Color                              ||
\*============================================================================*/

//!@doc Functions to get a color channel value for the given #t_argb32 color integer
//!@{
//! Gets the alpha channel value for the given 32-bit `color`
t_u8							Color_ARGB32_Get_A(t_argb32 color);
#define c_argb32geta			Color_ARGB32_Get_A
#define Color_ARGB32_Get_Alpha	Color_ARGB32_Get_A
//! Gets the red channel value for the given 32-bit `color`
t_u8							Color_ARGB32_Get_R(t_argb32 color);
#define c_argb32getr			Color_ARGB32_Get_R
#define Color_ARGB32_Get_Red	Color_ARGB32_Get_R
//! Gets the green channel value for the given 32-bit `color`
t_u8							Color_ARGB32_Get_G(t_argb32 color);
#define c_argb32getg			Color_ARGB32_Get_G
#define Color_ARGB32_Get_Green	Color_ARGB32_Get_G
//! Gets the blue channel value for the given 32-bit `color`
t_u8							Color_ARGB32_Get_B(t_argb32 color);
#define c_argb32getb			Color_ARGB32_Get_B
#define Color_ARGB32_Get_Blue	Color_ARGB32_Get_B
//!@}



//!@doc Creates a 32-bit color value from the given channel values (alpha, red, green, blue)
/*!
**	This function creates a new 32-bit ARGB color value from
**	the four given color channel 1-byte values.
**
**	@param	a	The alpha channel value (constrained to interval `[0, 255]`)
**	@param	r	The red channel value   (constrained to interval `[0, 255]`)
**	@param	g	The green channel value (constrained to interval `[0, 255]`)
**	@param	b	The blue channel value  (constrained to interval `[0, 255]`)
**	@returns
**	The 32-bit color value assembled from the given channel values
*/
//!@{
t_argb32					Color_ARGB32_Set(t_u8 a, t_u8 r, t_u8 g, t_u8 b);
#define c_argb32set			Color_ARGB32_Set
//!@}

//!@doc Functions to set a color channel value for the given #t_argb32 color integer
//!@{
//! Returns the given 32-bit `color`, with the `a` alpha channel value changed
t_argb32						Color_ARGB32_Set_A(t_argb32 color, t_u8 a);
#define c_argb32seta			Color_ARGB32_Set_A
#define Color_ARGB32_Set_Alpha	Color_ARGB32_Set_A
//! Returns the given 32-bit `color`, with the `r` red channel value changed
t_argb32						Color_ARGB32_Set_R(t_argb32 color, t_u8 r);
#define c_argb32setr			Color_ARGB32_Set_R
#define Color_ARGB32_Set_Red	Color_ARGB32_Set_R
//! Returns the given 32-bit `color`, with the `g` green channel value changed
t_argb32						Color_ARGB32_Set_G(t_argb32 color, t_u8 g);
#define c_argb32setg			Color_ARGB32_Set_G
#define Color_ARGB32_Set_Green	Color_ARGB32_Set_G
//! Returns the given 32-bit `color`, with the `b` blue channel value changed
t_argb32						Color_ARGB32_Set_B(t_argb32 color, t_u8 b);
#define c_argb32setb			Color_ARGB32_Set_B
#define Color_ARGB32_Set_Blue	Color_ARGB32_Set_B
//!@}



//!@doc Converts the given 32-bit color value to its 16-bit equivalent (rounding down)
/*!
**	@param	color	The 32-bit color to convert
**	@returns
**	A 16-bit ARGB color integer, created by dividing the color channel values of the
**	given 32-bit `color` value (values are rounded down in the process).
*/
//!@{
t_argb16					Color_ARGB32_To_ARGB16(t_argb32 color);
#define c_argb32toargb16	Color_ARGB32_To_ARGB16
//!@}

//!@doc Converts the given 16-bit color value to its floating-point color equivalent
/*!
**	@param	color	The 32-bit color to convert
**	@returns
**	A floating-point ARGB color vector, created by dividing the color channel values of the
**	given 32-bit `color` value (values are rounded down in the process).
*/
//!@{
s_argb						Color_ARGB32_To_ARGB(t_argb32 color);
#define c_argb32toargb		Color_ARGB32_To_ARGB
//!@}



//!@doc Returns a value indicating the amount of visual difference between the two given colors
/*!
**	https://en.wikipedia.org/wiki/Color_difference
**
**	@returns
**	A human-perception-weighted euclidian squared distance between the two given colors
**	The greater the value, the more perceptually different these 2 colors are.
*/
//!@{
t_u32						Color_ARGB32_Difference(t_argb32 c1, t_argb32 c2);
#define c_argb32diff		Color_ARGB32_Difference
//!@}

//!@doc Find the nearest color to the given `target` color, from within the given arrays of `colors`
/*!
**	@param	target	The desired color, for which the nearest will be returned
**	@param	colors	The array of different colors to check against
**	@param	n		The amount of colors to check in the `colors` array
**	@returns
**	A pointer to the color within `colors` which is the closest match
**	to the given `target` color, searching through `n` colors in the array.
*/
//!@{
t_argb32 const*				Color_ARGB32_GetNearest(t_argb32 target, t_argb32 const* colors, t_size n);
#define c_argb32nearest		Color_ARGB32_GetNearest
//!@}



/*============================================================================*\
||                              ARGB Float Color                              ||
\*============================================================================*/

//!@doc Creates a float color struct from the given channel values (alpha, red, green, blue)
/*!
**	This function creates a new floating-point color struct from
**	the given four individual color channel values (constains them between 0 and 1)
**
**	@param	a	The alpha channel value (constrained to interval `[0.0, 1.0]`)
**	@param	r	The red channel value   (constrained to interval `[0.0, 1.0]`)
**	@param	g	The green channel value (constrained to interval `[0.0, 1.0]`)
**	@param	b	The blue channel value  (constrained to interval `[0.0, 1.0]`)
**	@returns
**	The floating-point color struct from the given channel values
*/
//!@{
s_argb							Color_ARGB_Set(t_float a, t_float r, t_float g, t_float b);
#define c_argbset				Color_ARGB_Set
//!@}

//!@doc Functions to set a color channel value for the given #s_argb color vector
//!@{
//! Sets the given `a` alpha channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_ARGB_Set_A(s_argb* color, t_float a);
#define c_argbseta				Color_ARGB_Set_A
#define Color_ARGB_Set_Alpha	Color_ARGB_Set_A
//! Sets the given `r` red channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_ARGB_Set_R(s_argb* color, t_float r);
#define c_argbsetr				Color_ARGB_Set_R
#define Color_ARGB_Set_Red		Color_ARGB_Set_R
//! Sets the given `g` green channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_ARGB_Set_G(s_argb* color, t_float g);
#define c_argbsetg				Color_ARGB_Set_G
#define Color_ARGB_Set_Green	Color_ARGB_Set_G
//! Sets the given `b` blue channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_ARGB_Set_B(s_argb* color, t_float b);
#define c_argbsetb				Color_ARGB_Set_B
#define Color_ARGB_Set_Blue		Color_ARGB_Set_B
//!@}



//!@doc Converts the given floating-point color struct value to its 16-bit equivalent
/*!
**	@param	color	The floating-point color struct to convert
**	@returns
**	A 16-bit ARGB color by dividing the color channel values of the
**	given 32-bit `color` value (values are rounded down in the process).
*/
//!@{
t_argb16						Color_ARGB_To_ARGB16(s_argb const* color);
#define c_argbtoargb16			Color_ARGB_To_ARGB16
//!@}

//!@doc Converts the given floating-point color struct value to its 32-bit equivalent
/*!
**	@param	color	The floating-point color struct to convert
**	@returns
**	A 16-bit ARGB color by dividing the color channel values of the
**	given 32-bit `color` value (values are rounded down in the process).
*/
//!@{
t_argb32						Color_ARGB_To_ARGB32(s_argb const* color);
#define c_argbtoargb32			Color_ARGB_To_ARGB32
//!@}

//!@doc Converts the given floating-point color struct value to hue/sat/lum color format
/*!
**	@param	color	The floating-point color struct to convert
**	@returns
**	The equivalent to the given `color`, in hue/sat/lum format
*/
//!@{
s_ahsl							Color_ARGB_To_AHSL(s_argb const* color);
#define c_argbtoahsl			Color_ARGB_To_AHSL
//!@}



//!@doc Find the nearest color to the given `target` color from within the given arrays of `colors`
/*!
**	@param	target	The desired color, for which the nearest will be returned
**	@param	colors	The array of different colors to check against
**	@param	n		The amount of colors to check in the `colors` array
**	@returns
**	A pointer to the color within `colors` which is the closest match
**	to the given `target` color, searching through `n` colors in the array.
*/
//!@{
s_argb const*					Color_ARGB_GetNearest(s_argb target, s_argb const* colors, t_size n);
#define c_argbnearest			Color_ARGB_GetNearest
//!@}



/*============================================================================*\
||                              ARGB Float Color                              ||
\*============================================================================*/

//!@doc Creates a float color struct from the given channel values (alpha, hue, sat, lum)
/*!
**	This function creates a new floating-point color struct from
**	the given four individual color channel values (constains them)
**
**	@param	a	The alpha channel value        (constrained to interval `[0, 1]`)
**	@param	hue	The color hue/value            (constrained to interval `[0, PI*2]`)
**	@param	sat	The color saturation           (constrained to interval `[0, 1]`)
**	@param	lum	The color luminance/brightness (constrained to interval `[0, 1]`)
**	@returns
**	The floating-point color struct from the given channel values
*/
//!@{
s_ahsl							Color_AHSL_Set(t_float a, t_float hue, t_float sat, t_float lum);
#define c_ahslset				Color_AHSL_Set
//!@}

//!@doc Functions to set a color channel value for the given #s_ahsl color integer
//!@{
//! Sets the given `a` channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_AHSL_Set_A(s_ahsl* color, t_float a);
#define c_ahslseta				Color_AHSL_Set_A
#define Color_AHSL_Set_Alpha	Color_AHSL_Set_A
//! Sets the given `r` channel value in the given struct `color` (constraining it between 0 and #TAU, ie: `PI * 2`)
void							Color_AHSL_Set_H(s_ahsl* color, t_float hue);
#define c_ahslseth				Color_AHSL_Set_H
#define Color_AHSL_Set_Hue		Color_AHSL_Set_H
//! Sets the given `g` channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_AHSL_Set_S(s_ahsl* color, t_float sat);
#define c_ahslsets				Color_AHSL_Set_S
#define Color_AHSL_Set_Sat		Color_AHSL_Set_S
//! Sets the given `b` channel value in the given struct `color` (constraining it between 0 and 1)
void							Color_AHSL_Set_L(s_ahsl* color, t_float lum);
#define c_ahslsetl				Color_AHSL_Set_L
#define Color_AHSL_Set_Lum		Color_AHSL_Set_L
//!@}



//!@doc Converts the given floating-point color struct value to hue/sat/lum color format
/*!
**	@param	color	The floating-point color struct to convert
**	@returns
**	The equivalent to the given `color`, in hue/sat/lum format
*/
//!@{
s_argb							Color_AHSL_To_ARGB(s_ahsl const* color);
#define c_ahsltoargb			Color_AHSL_To_ARGB
//!@}



//!@doc Find the nearest color to the given `target` color from within the given arrays of `colors`
/*!
**	@param	target	The desired color, for which the nearest will be returned
**	@param	colors	The array of different colors to check against
**	@param	n		The amount of colors to check in the `colors` array
**	@returns
**	A pointer to the color within `colors` which is the closest match
**	to the given `target` color, searching through `n` colors in the array.
*/
//!@{
s_ahsl const*					Color_AHSL_GetNearest(s_ahsl target, s_ahsl const* colors, t_size n);
#define c_ahslnearest			Color_AHSL_GetNearest
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
