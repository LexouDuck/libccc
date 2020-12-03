/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_MATH_H
#define __LIBFT_MATH_H
/*! @file libft_math.h
**	This header defines the common standard math functions and macro defines.
**	@addtogroup libft_math
**	@{
*/
// TODO subdivide this into 2 modules: libft_math for classical real functions, and libft_vector for geometric functions
// TODO add other function macros for integral, distance, etc

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

#ifndef ABS			//! Expands to the absolute value of 'x'
#define ABS(x)		((x) < 0 ? -(x) : (x))
#endif

#ifndef SIGN		//! Expands to +1 or -1 according to the sign of 'x'
#define SIGN(x)		((x) < 0 ? -1 : +1)
#endif

#ifndef MIN			//!	Expands to the minimum value of 'x' and 'y'
#define MIN(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef MAX			//! Expands to the maximum value of 'x' and 'y'
#define MAX(x, y)	((x) < (y) ? (y) : (x))
#endif



#ifndef INFINITY		//! Define the floating-point infinity value: use -INFINITY for negative inf
#define INFINITY		(1. / 0.)
#endif
#ifndef IS_INFINITY		//! Checks if the given 'x' is either +INFINITY or -INFINITY
#define IS_INFINITY(x)	((x) == INFINITY || (x) == -INFINITY)
#endif

#ifndef NAN				//! Define the floating-point "not a number" value.
#define NAN				(0. / 0.)
#endif
#ifndef IS_NAN			//! Checks if the given 'x' has a "not a number" value.
#define IS_NAN(x)		((x) != (x))
#endif

/*!
**	This very small float is typically used to compare two float values.
**	Floating point equality checks aren't the most dependable kind of operation,
**	so it's often better to do (ABS(x - y) <= FLOAT_BIAS) to check for equality.
*/
#define FLOAT_BIAS		(1.0e-10)

//	TODO document this
#define SAMPLE_NB		1024



/*
**	Various relevant mathematical constants - these are used to speed up
**	our fast approximate versions of some fundamental algorithms and functions.
*/
#define QUARTER_PI		DIV_PI_4						//!< Alias for DIV_PI_4
#define HALF_PI			DIV_PI_2						//!< Alias for DIV_PI_2
#define DIV_PI_4		(t_float)0x1.921FB54442D18p-1	//!< Quarter of pi (PI / 4):		
#define DIV_PI_2		(t_float)0x1.921FB54442D18p+0	//!< Half of pi (PI / 2):			
#define PI				(t_float)0x1.921FB54442D18p+1	//!< A circle's periphery, pi:		3.141592653589793238462643383279502884197169399375105820974...
#define TAU 			(t_float)0x1.921FB54442D18p+2	//!< Double pi (PI * 2):			6.283185307179586476925286766559005768394338798750211641949...
#define INV_PI			(t_float)0x1.45F306DC9C883p-2	//!< Inverse of pi (1 / PI):		0.318309886183790671537767526745028724068919291480912897495...
#define INV_TAU			(t_float)0x1.45F306DC9C883p-3	//!< Inverse of tau (1 / (PI * 2)):	0.159154943091895335768883763372514362034459645740456448747...

#define E				(t_float)0x1.5BF0A8B145769p+1	//!< The exponential number, e:		2.718281828459045235360287471352662497757247093699959574966...
#define LN_2			(t_float)0x1.62E42FEFA39EFp-1	//!< The natural logarithm of 2:	0.693147180559945309417232121458176568075500134360255254120...
#define LN_10			(t_float)0x1.26BB1BBB55516p+1	//!< The natural logarithm of 10:	2.302585092994045684017991454684364207601101488628772976033...

#define SQRT_2			(t_float)0x1.6A09E667F3BCDp+0	//!< The square root of 2:	1.414213562373095048801688724209698078569671875376948073176...
#define INV_SQRT_2		(t_float)0x1.6A09E667F3BCDp-1	//!< The inverse square root of 2:	1 / SQRT_2
#define SQRT_3			(t_float)0x1.BB67AE8584CAAp+0	//!< The square root of 3:	1.732050807568877293527446341505872366942805253810380628055...
#define INV_SQRT_3		(t_float)0x1.279A74590331Cp-1	//!< The inverse square root of 3:	1 / SQRT_3
#define SQRT_5			(t_float)0x1.1E3779B97F4A7p+1	//!< The square root of 5:	2.236067977499789696409173668731276235440618359611525724270...
#define INV_SQRT_5		(t_float)0x1.C9F25C5BFEDD9p-2	//!< The inverse square root of 5:	1 / SQRT_5



/*
** ************************************************************************** *|
**                     Classical Real Number Operations                       *|
** ************************************************************************** *|
*/

//! Returns the base-2 exponent of 'x', as an integer
t_s32						Math_GetExp(t_float x);
#define ft_getexp			Math_GetExp
#define Math_GetExponent	Math_GetExp

//! Returns the absolute value of 'x' (makes 'x' positive)
t_float						Math_Abs(t_float x);
#define ft_fabs				Math_Abs
#define Math_AbsoluteValue	Math_Abs

//! Returns the division remainder of 'x' divided by 'y'
t_float						Math_Mod(t_float x, t_float y);
#define ft_fmod				Math_Mod
#define Math_Modulo			Math_Mod

//! Returns the value of 'x', rounded to the nearest integer
t_float						Math_Round(t_float x);
#define ft_round			Math_Round
#define Math_FloatRound		Math_Round

//! Returns the value of 'x', rounded towards 0
t_float						Math_Truncate(t_float x);
#define ft_trunc			Math_Truncate
#define Math_FloatTrunc		Math_Truncate

//! Returns the value of 'x', rounded to the superior integer
t_float						Math_Floor(t_float x);
#define ft_floor			Math_Floor
#define Math_FloatFloor		Math_Floor

//! Returns the value of 'x', rounded to the inferior integer
t_float						Math_Ceiling(t_float x);
#define ft_ceil				Math_Ceiling
#define Math_FloatCeiling	Math_Ceiling



//! Returns the value of 'x' to the power of 'y' (float)
t_float						Math_Pow(t_float x, t_float y);
#define ft_pow				Math_Pow
#define Math_Power			Math_Pow

//! Returns the value of 'x' to the power of 'n' (integer)
t_float						Math_Pow_N(t_float x, t_int n);
#define ft_pow_n			Math_Pow_N
#define Math_Power_N		Math_Pow_N

//! Returns the square root of 'x' (inverse of power of 2)
t_float						Math_SqRt(t_float x);
#define ft_sqrt				Math_SqRt
#define Math_SquareRoot		Math_SqRt

//! Returns the cubic root of 'x' (inverse of power of 3)
t_float						Math_CbRt(t_float x);
#define ft_cbrt				Math_CbRt
#define Math_CubicRoot		Math_CbRt

//! Returns the n-ic root of 'x' (inverse of power of 'n')
t_float						Math_NRt(t_float x, t_u8 n);
#define ft_nrt				Math_NRt
#define Math_NRoot			Math_NRt



//! Returns the exponential function's value for 'x'
t_float							Math_Exp(t_float x);
#define ft_exp					Math_Exp
#define Math_Exponential		Math_Exp

//! Returns the natural logarithm of 'x'
t_float							Math_Ln(t_float x);
#define ft_ln					Math_Ln
#define Math_NaturalLogarithm	Math_Ln

//! Returns the binary (base-2) logarithm of 'x'
t_float							Math_Log_2(t_float x);
#define ft_lg					Math_Log_2
#define Math_Logarithm_Base2	Math_Log_2

//! Returns the decimal (base-10) logarithm of 'x'
t_float							Math_Log_10(t_float x);
#define ft_log					Math_Log_10
#define Math_Logarithm_Base10	Math_Log_10

//! Returns the base-'n' logarithm of 'x'
t_float							Math_Log_N(t_float x, t_float n);
#define ft_logn					Math_Log_N
#define Math_Logarithm_BaseN	Math_Log_N




//! Returns the cosine of 'x' (horizontal trigonometry coordinate)
t_float								Math_Cos(t_float x);
#define ft_cos						Math_Cos
#define Math_Cosine					Math_Cos

//! Returns the sine of 'x' (vertical trigonometry coordinate)
t_float								Math_Sin(t_float x);
#define ft_sin						Math_Sin
#define Math_Sine					Math_Sin

//! Returns the tangent of 'x' (trigonometry tangent line)
t_float								Math_Tan(t_float x);
#define ft_tan						Math_Tan
#define Math_Tangent				Math_Tan

//! Returns the arc-cosine of 'x' (inverse of the cos function)
t_float								Math_ArcCos(t_float x);
#define ft_acos						Math_ArcCos
#define Math_InvCosine				Math_ArcCos

//! Returns the arc-sine of 'x' (inverse of the sin function)
t_float								Math_ArcSin(t_float x);
#define ft_asin						Math_ArcSin
#define Math_InvSine				Math_ArcSin

//! Returns the arc-tangent of 'x' (inverse of the tan function)
t_float								Math_ArcTan(t_float x);
#define ft_atan						Math_ArcTan
#define Math_InvTangent				Math_ArcTan



//! Returns the arc-tangent of ('y' / 'x'), used to find an angle
t_float								Math_ArcTan2(t_float y, t_float x);
#define ft_atan2					Math_ArcTan2
#define Math_ArcTangent_YoverX		Math_ArcTan2



//! Returns the hyperbolic cosine of 'x'
t_float								Math_CosH(t_float x);
#define ft_cosh						Math_CosH
#define Math_Cosine_Hyperbolic		Math_CosH

//! Returns the hyperbolic sine of 'x'
t_float								Math_SinH(t_float x);
#define ft_sinh						Math_SinH
#define Math_Sine_Hyperbolic		Math_SinH

//! Returns the hyperbolic tangent of 'x'
t_float								Math_TanH(t_float x);
#define ft_tanh						Math_TanH
#define Math_Tangent_Hyperbolic		Math_TanH

//! Returns the hyperbolic arc-cosine of 'x' (inverse of the cosh function)
t_float								Math_InvCosH(t_float x);
#define ft_acosh					Math_InvCosH
#define Math_InvCosine_Hyperbolic	Math_InvCosH

//! Returns the hyperbolic arc-sine of 'x' (inverse of the sinh function)
t_float								Math_InvSinH(t_float x);
#define ft_asinh					Math_InvSinH
#define Math_InvSine_Hyperbolic		Math_InvSinH

//! Returns the hyperbolic arc-tangent of 'x' (inverse of the tanh function)
t_float								Math_InvTanH(t_float x);
#define ft_atanh					Math_InvTanH
#define Math_InvTangent_Hyperbolic	Math_InvTanH



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



#if (LIBFTCONFIG_FAST_APPROX_MATH == 0)

	#ifdef _FLOAT_32_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##f(x, y)); }
	#endif

	#ifdef _FLOAT_64_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME(x, y)); }
	#endif

	#ifdef _FLOAT_80_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##l(x, y)); }
	#endif

	#ifdef _FLOAT_128_
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float ft_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##q(x, y)); }
	#endif

#endif

/*!
**	This union type is used in several math function implementations,
**	to manipulate float bits directly with bitwise operators.
*/
typedef union	u_float_cast_
{
	t_float		value_float;
#ifdef _FLOAT_32_
	t_s32		value_int;
#endif
#ifdef _FLOAT_64_
	t_s64		value_int;
#endif
#ifdef _FLOAT_80_
	t_s64[2]	value_int;
#endif
#ifdef _FLOAT_128_
	t_s64[2]	value_int;
#endif
}				u_float_cast;



/*
** ************************************************************************** *|
**                             Algebra & Calculus                             *|
** ************************************************************************** *|
*/

//! A simple struct for storing 2-dimensional values
typedef struct	s_vec2_
{
	t_float		x;			//! The X coordinate of this vector
	t_float		y;			//! The Y coordinate of this vector
}				s_vec2;

//! A struct to store complex/imaginary number values
typedef struct	s_complex_
{
	t_float		re;			//! The "real" part of this complex number
	t_float		im;			//! The "imaginary" part of this complex number
}				s_complex;

//! This union stores a 2-dimensional value which can be accessed in several ways
typedef	union	u_vec2_
{
	t_float		values[2];	//! An array, to access the 2 values from within brackets
	s_vec2		vect;		//! A vector, to access the 2 coordinates as `.x` and `.y`
	s_complex	cplx;		//! A complex number, to access the 2 parts as `.re` and `.im`
}				u_vec2;



//! A simple struct for storing 3-dimensional values
typedef struct	s_vec3_
{
	t_float		x;			//! The X coordinate of this vector
	t_float		y;			//! The Y coordinate of this vector
	t_float		z;			//! The Z coordinate of this vector
}				s_vec3;

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

//! This union stores a 3-dimensional value which can be accessed in several ways
typedef	union	u_vec3_
{
	t_float		values[3];	//! An array, to access the 3 values from within brackets
	s_vec3		vect;		//! A vector, to access the 3 coordinates as `.x`, `.y` and `.z`
	s_rgb		rgb;		//! An RGB color, to access the 3 channels as `.r`, `.g` and `.b`
	s_hsl		hsl;		//! An HSL color, to access the 3 channels as `.h`, `.s` and `.l`
}				u_vec3;



//! A simple struct for storing 4-dimensional values
typedef struct		s_vec4_
{
	t_float		x;			//! The X coordinate of this vector
	t_float		y;			//! The Y coordinate of this vector
	t_float		z;			//! The Z coordinate of this vector
	t_float		t;			//! The T coordinate of this vector
}					s_vec4;

//! A struct for storing quaternions
typedef struct		s_quaternion_
{
	t_float		s;			//! The S value of this quaternion
	t_float		i;			//! The I value of this quaternion
	t_float		j;			//! The J value of this quaternion
	t_float		k;			//! The K value of this quaternion
}					s_quaternion;

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

//! This union stores a 4-dimensional value which can be accessed in several ways
/*!
**	NB: Make sure to be coherent when using 4D vectors:
**	memory layout is in the order `xyz-t` for the 's_vec4' struct,
**	but the other union structs divid it like `s-ijk` and `a-rgb`
*/
typedef	union	u_vec4_
{
	t_float			values[4];	//! An array, to access the 4 values from within brackets
	s_vec4			vect;		//! A vector, to access the 4 coordinates as `.x`, `.y`, `.z`, and `.t`
	s_quaternion	quat;		//! A quaternion, to access the 4 values as `.i`, `.j`, `.k`, and `.s`
	s_argb			argb;		//! An RGB color, to access the 3 channels as `.r`, `.g` `.b`, and `.a`
	s_ahsl			ahsl;		//! An HSL color, to access the 3 channels as `.h`, `.s` `.l`, and `.a`
}				u_vec4;



typedef		t_float	(*f_scalar_func1)(t_float const v);
typedef		t_float	(*f_scalar_func2)(u_vec2 const v);
typedef		t_float	(*f_scalar_func3)(u_vec3 const v);
typedef		t_float	(*f_scalar_func4)(u_vec4 const v);

typedef		t_float	(*f_real_function)(t_float x);
typedef		t_float	(*f_real_operator)(t_float x, t_float y);



/*
** Note that for a coordinate box in the input space R^3, the volume
** computed by the integral is thus technically a 4-hypervolume (since you
** add a dimension because of the output space of dimension 1).
** The box is assumed to be composed of orthogonal edges (brick shaped),
** which is why only two vectors are necessary to define it.
*/

typedef struct		s_box1d_
{
	t_float		start;
	t_float		end;
}					s_box1d;

typedef struct		s_box2d_
{
	u_vec2	start;
	u_vec2	end;
}					s_box2d;

typedef struct		s_box3d_
{
	u_vec3	start;
	u_vec3	end;
}					s_box3d;

typedef struct		s_box4d_
{
	u_vec4	start;
	u_vec4	end;
}					s_box4d;

typedef s_box1d	s_interval;

//t_float	lin_integrate(sf, domain);
t_float		ft_integrate(f_real_function const f, s_interval const domain, t_float step);
t_float		ft_mc_integrate_1d(f_scalar_func1 const sf, s_box1d const domain);
t_float		ft_mc_integrate_2d(f_scalar_func2 const sf, s_box2d const domain);
t_float		ft_mc_integrate_3d(f_scalar_func3 const sf, s_box3d const domain);
t_float		ft_mc_integrate_4d(f_scalar_func4 const sf, s_box4d const domain);

t_f32		ft_distance_f32(t_f32 x, t_f32 y);
t_f64		ft_distance_f64(t_f64 x, t_f64 y);
t_u8		ft_distance_u8(t_u8 x, t_u8 y);
t_u16		ft_distance_u16(t_u16 x, t_u16 y);
t_u32		ft_distance_u32(t_u32 x, t_u32 y);
t_u64		ft_distance_u64(t_u64 x, t_u64 y);
t_s8		ft_distance_s8(t_s8 x, t_s8 y);
t_s16		ft_distance_s16(t_s16 x, t_s16 y);
t_s32		ft_distance_s32(t_s32 x, t_s32 y);
t_s64		ft_distance_s64(t_s64 x, t_s64 y);
t_float		ft_distance_float(t_float x, t_float y);
t_uint		ft_distance_uint(t_uint x, t_uint y);
t_int		ft_distance_int(t_int x, t_int y);
// TODO distance manh, eucl, inf for 2d, 3d and 4d



/*
** ************************************************************************** *|
**                            Float Type Definitions                          *|
** ************************************************************************** *|
*/

/*
**	IEEE 754 32-bit floating point "single" precision bitwise macros
*/
#define F32_SIGNED			0x80000000
#define F32_EXPONENT_BIAS	127
#define F32_EXPONENT		0x7F800000
#define F32_EXPONENT_ZERO	0x3F800000
#define F32_EXPONENT_BITS	8
#define F32_MANTISSA		0x007FFFFF
#define F32_MANTISSA_SIGNED	0x807FFFFF
#define F32_MANTISSA_BITS	23
#define F32_INIT_VALUE		0x1.p-23

/*
**	IEEE 754 64-bit floating point double-precision bitwise macros
*/
#define F64_SIGNED			0x8000000000000000
#define F64_EXPONENT_BIAS	1023
#define F64_EXPONENT		0x7FF0000000000000
#define F64_EXPONENT_ZERO	0x3FF0000000000000
#define F64_EXPONENT_BITS	11
#define F64_MANTISSA		0x000FFFFFFFFFFFFF
#define F64_MANTISSA_SIGNED	0x800FFFFFFFFFFFFF
#define F64_MANTISSA_BITS	52
#define F64_INIT_VALUE		0x1.p-52

/*
**	x86 80-bit floating point extended precision bitwise macros
*/
#define F80_SIGNED			0x80000000000000000000L
#define F80_EXPONENT_BIAS	16383
#define F80_EXPONENT		0x7FFF0000000000000000L
#define F80_EXPONENT_ZERO	0x3FFF0000000000000000L
#define F80_EXPONENT_BITS	15
#define F80_MANTISSA		0x0000FFFFFFFFFFFFFFFFL
#define F80_MANTISSA_SIGNED	0x8000FFFFFFFFFFFFFFFFL
#define F80_MANTISSA_BITS	64
#define F80_INIT_VALUE		0x1.p-64

/*
**	IEEE 754 128-bit floating point quadruple-precision bitwise macros
*/
#define F128_SIGNED				0x80000000000000000000000000000000L
#define F128_EXPONENT_BIAS		16383
#define F128_EXPONENT			0x7FFF0000000000000000000000000000L
#define F128_EXPONENT_ZERO		0x3FFF0000000000000000000000000000L
#define F128_EXPONENT_BITS		15
#define F128_MANTISSA			0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL
#define F128_MANTISSA_SIGNED	0x8000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL
#define F128_MANTISSA_BITS		112
#define F128_INIT_VALUE			0x1.p-112



/*
**	Depending on the 't_float' type (_FLOAT_32_ or _FLOAT_64_, etc) chosen,
**	the appropriate bitwise macros will be used by the math functions.
**	It is often better to only use one type of floating-point precision
**	for a given program, so the best way to do that is by using the 'FLOAT_'
**	macros defined below, rather than the 'F32_' or 'F64_' macros above.
*/

#ifdef _FLOAT_32_
	#define FLOAT_SIGNED			F32_SIGNED
	#define FLOAT_EXPONENT_BIAS		F32_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F32_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F32_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F32_EXPONENT_BITS
	#define FLOAT_MANTISSA			F32_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F32_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F32_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F32_INIT_VALUE
#endif

#ifdef _FLOAT_64_
	#define FLOAT_SIGNED			F64_SIGNED
	#define FLOAT_EXPONENT_BIAS		F64_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F64_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F64_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F64_EXPONENT_BITS
	#define FLOAT_MANTISSA			F64_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F64_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F64_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F64_INIT_VALUE
#endif

#ifdef _FLOAT_80_
	#define FLOAT_SIGNED			F80_SIGNED
	#define FLOAT_EXPONENT_BIAS		F80_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F80_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F80_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F80_EXPONENT_BITS
	#define FLOAT_MANTISSA			F80_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F80_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F80_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F80_INIT_VALUE
#endif

#ifdef _FLOAT_128_
	#define FLOAT_SIGNED			F128_SIGNED
	#define FLOAT_EXPONENT_BIAS		F128_EXPONENT_BIAS
	#define FLOAT_EXPONENT			F128_EXPONENT
	#define FLOAT_EXPONENT_ZERO		F128_EXPONENT_ZERO
	#define FLOAT_EXPONENT_BITS		F128_EXPONENT_BITS
	#define FLOAT_MANTISSA			F128_MANTISSA
	#define FLOAT_MANTISSA_SIGNED	F128_MANTISSA_SIGNED
	#define FLOAT_MANTISSA_BITS		F128_MANTISSA_BITS
	#define FLOAT_INIT_VALUE		F128_INIT_VALUE
#endif



/*! @} */
HEADER_END
#endif
