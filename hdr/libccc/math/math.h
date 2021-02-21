/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/math.h                       |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_H
#define __LIBCCC_MATH_H
/*! @file libccc/math/math.h
**	@addtogroup libccc_math_math
**	@{
**	This header defines the common standard math functions and macro defines.
**
**	@isostd{https://en.cppreference.com/w/c/numeric/math}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Expands to the absolute value of 'x' (ie: gives the positive equivalent of 'x')
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/abs}
**	@isostd{https://en.cppreference.com/w/c/numeric/math/fabs}
**
**	- Math: @f$ {|x|} @f$
*/
#ifndef ABS
#define ABS(x)		((x) < 0 ? -(x) : (x))
#endif

//! Expands to +1 or -1 according to the sign of 'x' (NB: if 'x' is zero, gives +1)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/signbit} (differs)
**
**	- Math: @f$ {\frac{x}{|x|}} @f$
*/
#ifndef SIGN
#define SIGN(x)		((x) < 0 ? -1 : +1)
#endif



//!	Expands to the minimum value between 'x' and 'y' (the smaller of the two)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/fmin}
*/
#ifndef MIN
#define MIN(x, y)	((x) < (y) ? (x) : (y))
#endif

//! Expands to the maximum value between 'x' and 'y' (the larger of the two)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/fmax}
*/
#ifndef MAX
#define MAX(x, y)	((x) < (y) ? (y) : (x))
#endif



/*
**	Various relevant mathematical constants - these are used to speed up
**	our fast-approximate versions of some fundamental algorithms and functions.
*/

//! Alias for #DIV_PI_4
#define QUARTER_PI	DIV_PI_4
//! Alias for #DIV_PI_2
#define HALF_PI		DIV_PI_2

//! Mathematical constant: Quarter of pi (`PI / 4`)
/*!
**	- Math: @f$ {\frac{\pi}{4}} @f$
**	- Decimal: TODO
**	- Hexadecimal: `0x1.921FB54442D18p-1`
*/
#define DIV_PI_4		(t_float)(0x1.921FB54442D18p-1)

//! Mathematical constant: Half of pi (`PI / 2`)
/*!
**	- Math: @f$ {\frac{\pi}{2}} @f$
**	- Decimal: TODO
**	- Hexadecimal: `0x1.921FB54442D18p+0`
*/
#define DIV_PI_2		(t_float)(0x1.921FB54442D18p+0)

//! Mathematical constant: circle periphery from diameter, pi (`TAU / 2`)
/*!
**	- Math: @f$ {\pi} @f$
**	- Decimal: `3.141592653589793238462643383279502884197169399375105820974...`
**	- Hexadecimal: `0x1.921FB54442D18p+1`
*/
#define PI				(t_float)(0x1.921FB54442D18p+1)

//! Mathematical constant: circle periphery from radius, tau (`2 * PI`)
/*!
**	- Math: @f$ {2\pi} @f$
**	- Decimal: `6.283185307179586476925286766559005768394338798750211641949...`
**	- Hexadecimal: `0x1.921FB54442D18p+2`
*/
#define TAU 			(t_float)(0x1.921FB54442D18p+2)

//! Mathematical constant: Inverse of pi (`1 / pi`)
/*!
**	- Math: @f$ {\frac{1}{\pi}} @f$
**	- Decimal: `0.318309886183790671537767526745028724068919291480912897495...`
**	- Hexadecimal: `0x1.45F306DC9C883p-2`
*/
#define INV_PI			(t_float)(0x1.45F306DC9C883p-2)

//! Mathematical constant: Inverse of tau (`1 / tau`)
/*!
**	- Math: @f$ {\frac{1}{2\pi}} @f$
**	- Decimal: `0.159154943091895335768883763372514362034459645740456448747...`
**	- Hexadecimal: `0x1.45F306DC9C883p-3`
*/
#define INV_TAU			(t_float)(0x1.45F306DC9C883p-3)



//! Mathematical constant: The exponential number, e (`exp(1)`)
/*!
**	- Math: @f$ {e} @f$
**	- Decimal: `2.718281828459045235360287471352662497757247093699959574966...`
**	- Hexadecimal: `0x1.5BF0A8B145769p+1`
*/
#define E				(t_float)(0x1.5BF0A8B145769p+1)

//! Mathematical constant: The natural logarithm of 2 (`ln(2)`)
/*!
**	- Math: @f$ {\ln {2}} @f$
**	- Decimal: `0.693147180559945309417232121458176568075500134360255254120...`
**	- Hexadecimal: `0x1.62E42FEFA39EFp-1`
*/
#define LN_2			(t_float)(0x1.62E42FEFA39EFp-1)

//! Mathematical constant: The natural logarithm of 10 (`ln(10)`)
/*!
**	- Math: @f$ {\ln {10}} @f$
**	- Decimal: `2.302585092994045684017991454684364207601101488628772976033...`
**	- Hexadecimal: `0x1.26BB1BBB55516p+1`
*/
#define LN_10			(t_float)(0x1.26BB1BBB55516p+1)



//! Mathematical constant: The square root of 2 (`sqrt(2)`)
/*!
**	- Math: @f$ {\sqrt{2}} @f$
**	- Decimal: `1.414213562373095048801688724209698078569671875376948073176...`
**	- Hexadecimal: `0x1.6A09E667F3BCDp+0`
*/
#define SQRT_2			(t_float)(0x1.6A09E667F3BCDp+0)

//! Mathematical constant: The inverse square root of 2 (`1 / sqrt(2)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{2}}} @f$
**	- Decimal: TODO
**	- Hexadecimal: `0x1.6A09E667F3BCDp-1`
*/
#define INV_SQRT_2		(t_float)(0x1.6A09E667F3BCDp-1)

//! Mathematical constant: The square root of 3 (`sqrt(3)`)
/*!
**	- Math: @f$ {\sqrt{3}} @f$
**	- Decimal: `1.732050807568877293527446341505872366942805253810380628055...`
**	- Hexadecimal: `0x1.BB67AE8584CAAp+0`
*/
#define SQRT_3			(t_float)(0x1.BB67AE8584CAAp+0)

//! Mathematical constant: The inverse square root of 3 (`1 / sqrt(3)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{3}}} @f$
**	- Decimal: TODO
**	- Hexadecimal: `0x1.279A74590331Cp-1`
*/
#define INV_SQRT_3		(t_float)(0x1.279A74590331Cp-1)

//! Mathematical constant: The square root of 5 (`sqrt(5)`)
/*!
**	- Math: @f$ {\sqrt{5}} @f$
**	- Decimal: `2.236067977499789696409173668731276235440618359611525724270...`
**	- Hexadecimal: `0x1.1E3779B97F4A7p+1`
*/
#define SQRT_5			(t_float)(0x1.1E3779B97F4A7p+1)

//! Mathematical constant: The inverse square root of 5 (`1 / sqrt(5)`)
/*!
**	- Math: @f$ {\frac{1}{\sqrt{5}}} @f$
**	- Decimal: TODO
**	- Hexadecimal: `0x1.C9F25C5BFEDD9p-2`
*/
#define INV_SQRT_5		(t_float)(0x1.C9F25C5BFEDD9p-2)



//! The type of function which takes one real number and outputs one real number
typedef		t_float	(*f_real_function)(t_float x);

//! The type of function which takes two real numbers and outputs one real number
typedef		t_float	(*f_real_operator)(t_float x, t_float y);



/*
** ************************************************************************** *|
**                     Classical Real Number Operations                       *|
** ************************************************************************** *|
*/

//! Returns the base-2 exponent of 'x', as an integer
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/ilogb}
*/
t_s32						Math_GetExp(t_float x);
#define c_getexp			Math_GetExp
#define Math_GetExponent	Math_GetExp

// TODO logb, ie: Math_GetExp_Float ?

//! Returns the absolute value of 'x' (makes 'x' positive)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/abs}
**	@isostd{https://en.cppreference.com/w/c/numeric/math/fabs}
**
**	- Math: @f$ {|x|} @f$
*/
t_float						Math_Abs(t_float x);
#define c_fabs				Math_Abs
#define Math_AbsoluteValue	Math_Abs

//! Returns the remainder of euclidian division of 'x' by 'y'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/fmod}
*/
t_float						Math_Mod(t_float x, t_float y);
#define c_fmod				Math_Mod
#define Math_Modulo			Math_Mod

//! Returns the value of 'x', rounded to the nearest integer
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/round}
*/
t_float						Math_Round(t_float x);
#define c_round				Math_Round
#define Math_FloatRound		Math_Round

//! Returns the value of 'x', rounded towards 0
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/trunc}
*/
t_float						Math_Truncate(t_float x);
#define c_trunc				Math_Truncate
#define Math_FloatTrunc		Math_Truncate

//! Returns the value of 'x', rounded to the superior integer
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/floor}
*/
t_float						Math_Floor(t_float x);
#define c_floor				Math_Floor
#define Math_FloatFloor		Math_Floor

//! Returns the value of 'x', rounded to the inferior integer
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/ceil}
*/
t_float						Math_Ceiling(t_float x);
#define c_ceil				Math_Ceiling
#define Math_FloatCeiling	Math_Ceiling



//! Returns the value of 'x' to the power of 'y' (float)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/pow}
**
**	- Math: @f$ {x^y} @f$
*/
t_float						Math_Pow(t_float x, t_float y);
#define c_pow				Math_Pow
#define Math_Power			Math_Pow

//! Returns the value of 'x' to the power of 'n' (integer)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/pow}
**
**	- Math: @f$ {x^n} @f$
*/
t_float						Math_Pow_N(t_float x, t_sint n);
#define c_pow_n				Math_Pow_N
#define Math_Power_N		Math_Pow_N

//! Returns the square root of 'x' (inverse of power of 2)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/sqrt}
**
**	- Math: @f$ {\sqrt {x}} @f$
*/
t_float						Math_SqRt(t_float x);
#define c_sqrt				Math_SqRt
#define Math_SquareRoot		Math_SqRt

//! Returns the cubic root of 'x' (inverse of power of 3)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/cbrt}
**
**	- Math: @f$ {\sqrt[3] {x}} @f$
*/
t_float						Math_CbRt(t_float x);
#define c_cbrt				Math_CbRt
#define Math_CubicRoot		Math_CbRt

//! Returns the n-ic root of 'x' (inverse of power of 'n')
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/nrt}
**
**	- Math: @f$ {\sqrt[n] {x}} @f$
*/
t_float						Math_NRt(t_float x, t_u8 n);
#define c_nrt				Math_NRt
#define Math_NRoot			Math_NRt

// TODO hypot: {\sqrt{x^2+y^2}}



//! Returns the exponential function's value for 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/exp}
**
**	- Math: @f$ {e^x} @f$
*/
t_float							Math_Exp(t_float x);
#define c_exp					Math_Exp
#define Math_Exponential		Math_Exp

//! Returns the natural logarithm of 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/log}
**
**	- Math: @f$ {\ln {x}} @f$
*/
t_float							Math_Ln(t_float x);
#define c_ln					Math_Ln
#define Math_NaturalLogarithm	Math_Ln

//! Returns the binary (base-2) logarithm of 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/log2}
**
**	- Math: @f$ {\log_{2} {x}} @f$
*/
t_float							Math_Log_2(t_float x);
#define c_lg					Math_Log_2
#define Math_Logarithm_Base2	Math_Log_2

//! Returns the decimal (base-10) logarithm of 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/log10}
**
**	- Math: @f$ {\log_{10} {x}} @f$
*/
t_float							Math_Log_10(t_float x);
#define c_log					Math_Log_10
#define Math_Logarithm_Base10	Math_Log_10

//! Returns the base-'n' logarithm of 'x'
/*!
**	@nonstd
**
**	- Math: @f$ {\log_{n} {x}} @f$
*/
t_float							Math_Log_N(t_float x, t_float n);
#define c_logn					Math_Log_N
#define Math_Logarithm_BaseN	Math_Log_N




//! Returns the cosine of 'x' (horizontal trigonometry coordinate)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/cos}
**
**	- Math: @f$ {\cos {x}} @f$
*/
t_float								Math_Cos(t_float x);
#define c_cos						Math_Cos
#define Math_Cosine					Math_Cos

//! Returns the sine of 'x' (vertical trigonometry coordinate)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/sin}
**
**	- Math: @f$ {\sin {x}} @f$
*/
t_float								Math_Sin(t_float x);
#define c_sin						Math_Sin
#define Math_Sine					Math_Sin

//! Returns the tangent of 'x' (trigonometry tangent line)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/tan}
**
**	- Math: @f$ {\tan {x}} @f$
*/
t_float								Math_Tan(t_float x);
#define c_tan						Math_Tan
#define Math_Tangent				Math_Tan

//! Returns the arc-cosine of 'x' (inverse of the cos function)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/acos}
**
**	- Math: @f$ {\cos^{-1} {x}} @f$
*/
t_float								Math_ArcCos(t_float x);
#define c_acos						Math_ArcCos
#define Math_Cos_1					Math_ArcCos
#define Math_InvCosine				Math_ArcCos

//! Returns the arc-sine of 'x' (inverse of the sin function)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/asin}
**
**	- Math: @f$ {\sin^{-1} {x}} @f$
*/
t_float								Math_ArcSin(t_float x);
#define c_asin						Math_ArcSin
#define Math_Sin_1					Math_ArcSin
#define Math_InvSine				Math_ArcSin

//! Returns the arc-tangent of 'x' (inverse of the tan function)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/atan}
**
**	- Math: @f$ {\tan^{-1} {x}} @f$
*/
t_float								Math_ArcTan(t_float x);
#define c_atan						Math_ArcTan
#define Math_Tan_1					Math_ArcTan
#define Math_InvTangent				Math_ArcTan



//! Returns the arc-tangent of ('y' / 'x'), used to find an angle from coordinates
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/atan2}
**
**	- Math: @f$ {\arctan(\frac{y}{x})} @f$, in the range @f$ {[-\pi;+\pi]} @f$
*/
t_float								Math_ArcTan2(t_float y, t_float x);
#define c_atan2						Math_ArcTan2
#define Math_ArcTangent2			Math_ArcTan2
#define Math_ArcTangent_YoverX		Math_ArcTan2



//! Returns the hyperbolic cosine of 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/cosh}
**
**	- Math: @f$ {\cosh {x}} @f$
*/
t_float								Math_CosH(t_float x);
#define c_cosh						Math_CosH
#define Math_Cos_H					Math_CosH
#define Math_Cosine_Hyperbolic		Math_CosH

//! Returns the hyperbolic sine of 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/sinh}
**
**	- Math: @f$ {\sinh {x}} @f$
*/
t_float								Math_SinH(t_float x);
#define c_sinh						Math_SinH
#define Math_Sin_H					Math_SinH
#define Math_Sine_Hyperbolic		Math_SinH

//! Returns the hyperbolic tangent of 'x'
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/tanh}
**
**	- Math: @f$ {\tanh {x}} @f$
*/
t_float								Math_TanH(t_float x);
#define c_tanh						Math_TanH
#define Math_Tan_H					Math_TanH
#define Math_Tangent_Hyperbolic		Math_TanH

//! Returns the hyperbolic arc-cosine of 'x' (inverse of the cosh function)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/acosh}
**
**	- Math: @f$ {\cosh^{-1} {x}} @f$
*/
t_float								Math_InvCosH(t_float x);
#define c_acosh						Math_InvCosH
#define Math_Cos_1_H				Math_InvCosH
#define Math_InvCosine_Hyperbolic	Math_InvCosH

//! Returns the hyperbolic arc-sine of 'x' (inverse of the sinh function)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/asinh}
**
**	- Math: @f$ {\sinh^{-1} {x}} @f$
*/
t_float								Math_InvSinH(t_float x);
#define c_asinh						Math_InvSinH
#define Math_Sin_1_H				Math_InvSinH
#define Math_InvSine_Hyperbolic		Math_InvSinH

//! Returns the hyperbolic arc-tangent of 'x' (inverse of the tanh function)
/*!
**	@isostd{https://en.cppreference.com/w/c/numeric/math/atanh}
**
**	- Math: @f$ {\tanh^{-1} {x}} @f$
*/
t_float								Math_InvTanH(t_float x);
#define c_atanh						Math_InvTanH
#define Math_Tan_1_H				Math_InvTanH
#define Math_InvTangent_Hyperbolic	Math_InvTanH



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



#if (LIBCONFIG_USE_FAST_APPROX_MATH == 0)

	#if LIBCONFIG_BITS_FLOAT == 32
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##f(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##f(x, y)); }
	#endif

	#if LIBCONFIG_BITS_FLOAT == 64
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME(x, y)); }
	#endif

	#if LIBCONFIG_BITS_FLOAT == 80
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##l(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##l(x, y)); }
	#endif

	#if LIBCONFIG_BITS_FLOAT == 128
		#define MATH_DECL_FUNCTION(RETURN, FT_NAME, NAME)	inline RETURN c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALFUNCTION(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x)				{ return (__builtin_##NAME##q(x)); }
		#define MATH_DECL_REALOPERATOR(FT_NAME, NAME)		inline t_float c_##FT_NAME(t_float x, t_float y)	{ return (__builtin_##NAME##q(x, y)); }
	#endif

#endif



/*! @} */
HEADER_END
#endif
