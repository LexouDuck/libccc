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
/*!@group{libccc_math}
** @{
**	This header defines the common standard math functions and macro defines.
**
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math}
**	@isostd{C99,https://en.cppreference.com/w/c/numeric/tgmath}
**
**	@file
*/

// TODO add PCGD() and PPCM() functions

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/math/constants.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Computes to the absolute value of `X` (ie: gives the positive equivalent of `X`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/abs}
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fabs}
**
**	- Math: @f$ {|x|} @f$
*/
#ifndef ABS
#define ABS(X)		((X) < 0 ? -(X) : (X))
#endif

//! Computes to `+1`, `-1` (or `0` if `(X) == 0`) according to the sign of `X`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/signbit} (differs)
**
**	- Math: @f$ {\frac{x}{|x|}} @f$
*/
#ifndef SIGN
#define SIGN(X)		((X) == 0 ? 0 : ((X) < 0 ? -1 : +1))
#endif

//! Checks if a value is negative (works for unsigned types, without causing tautology warnings)
/*!
**	This macro is useful to check if a value is negative, but its type (signed or unsigned) is not known.
**	In particular, the `char` and `enum` native C types are of unknown/undefined signage,
**	so this macro is useful to check that a value is positive, no matter the platform/environment.
**
**	- Math: @f$ {x < 0} @f$
*/
#ifndef ISNEG
#define ISNEG(X)	(!((X) > 0) && ((X) != 0))
#endif



//!	Expands to the minimum value between `X` and `Y` (the smaller of the two)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmin}
*/
#ifndef MIN
#define MIN(X, Y)	((X) < (Y) ? (X) : (Y))
#endif

//! Expands to the maximum value between `X` and `Y` (the larger of the two)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmax}
*/
#ifndef MAX
#define MAX(X, Y)	((X) < (Y) ? (Y) : (X))
#endif

//! Expands to a sequence of `Y` repetitive multiplications of `X` (ie: a compile-time `pow()` function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmax}
**
**	@param	X	The number to exponentiate (can be a value of any numeric type)
**	@param	Y	The exponent (must be an integer literal, in the range `[0,16]`)
*/
#ifndef POW
#define POW(X, Y)		POW_##Y(X)

// TODO make more optimized with log2n method
#define POW_0(X)	(1)
#define POW_1(X)	(X)
#define POW_2(X)	(X * X)
#define POW_3(X)	(X * X * X)
#define POW_4(X)	(X * X * X * X)
#define POW_5(X)	(X * X * X * X * X)
#define POW_6(X)	(X * X * X * X * X * X)
#define POW_7(X)	(X * X * X * X * X * X * X)
#define POW_8(X)	(X * X * X * X * X * X * X * X)
#define POW_9(X)	(X * X * X * X * X * X * X * X * X)
#define POW_10(X)	(X * X * X * X * X * X * X * X * X * X)
#define POW_11(X)	(X * X * X * X * X * X * X * X * X * X * X)
#define POW_12(X)	(X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_13(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_14(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_15(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X * X * X)
#define POW_16(X)	(X * X * X * X * X * X * X * X * X * X * X * X * X * X * X * X)
#endif



#define MATH_DEFINE_FUNCTION(RETURN, BITS, NAME, CNAME, TYPE)	inline RETURN	 c_f##BITS##NAME(t_f##BITS x)				{ return (__builtin_##CNAME##TYPE(x)); }
#define MATH_DEFINE_REALFUNCTION(BITS, NAME, CNAME, TYPE)		inline t_f##BITS c_f##BITS##NAME(t_f##BITS x)				{ return (__builtin_##CNAME##TYPE(x)); }
#define MATH_DEFINE_REALOPERATOR(BITS, NAME, CNAME, TYPE)		inline t_f##BITS c_f##BITS##NAME(t_f##BITS x, t_f##BITS y)	{ return (__builtin_##CNAME##TYPE(x, y)); }

// TODO ascertain platform macros for sizeof(long double), and use them to conditionally defien wrappers for std libc math functions

#define MATH_DECL_FUNCTION(RETURN, NAME, CNAME)	\
	MATH_DEFINE_FUNCTION(RETURN, 32, NAME, CNAME,f)	\
	MATH_DEFINE_FUNCTION(RETURN, 64, NAME, CNAME,)	\
/*	MATH_DEFINE_FUNCTION(RETURN, 80, NAME, CNAME,l)	\*/
/*	MATH_DEFINE_FUNCTION(RETURN, 128,NAME, CNAME,q)	\*/

#define MATH_DECL_REALFUNCTION(NAME, CNAME)		\
	MATH_DEFINE_REALFUNCTION(32, NAME, CNAME,f)	\
	MATH_DEFINE_REALFUNCTION(64, NAME, CNAME,)	\
/*	MATH_DEFINE_REALFUNCTION(80, NAME, CNAME,l)	\*/
/*	MATH_DEFINE_REALFUNCTION(128,NAME, CNAME,q)	\*/

#define MATH_DECL_REALOPERATOR(NAME, CNAME)		\
	MATH_DEFINE_REALOPERATOR(32, NAME, CNAME,f)	\
	MATH_DEFINE_REALOPERATOR(64, NAME, CNAME,)	\
/*	MATH_DEFINE_REALOPERATOR(80, NAME, CNAME,l)	\*/
/*	MATH_DEFINE_REALOPERATOR(128,NAME, CNAME,q)	\*/



#define DEFINE_GENERIC_MATH_FUNCTION(FUNCTION, X) \
	_Generic((X),	\
		t_q16:	 Q16_##FUNCTION,	\
		t_q32:	 Q32_##FUNCTION,	\
		t_q64:	 Q64_##FUNCTION,	\
		t_q128:	 Q128_##FUNCTION,	\
		t_fixed: Fixed_##FUNCTION,	\
		t_f32:	 F32_##FUNCTION,	\
		t_f64:	 F64_##FUNCTION,	\
		t_f80:	 F80_##FUNCTION,	\
		t_f128:	 F128_##FUNCTION,	\
		t_float: Float_##FUNCTION,	\
	)(X)

#define DEFINE_GENERIC_MATH_OPERATOR(FUNCTION, X, Y) \
	_Generic((X),	\
		t_q16:	 Q16_##FUNCTION,	\
		t_q32:	 Q32_##FUNCTION,	\
		t_q64:	 Q64_##FUNCTION,	\
		t_q128:	 Q128_##FUNCTION,	\
		t_fixed: Fixed_##FUNCTION,	\
		t_f32:	 F32_##FUNCTION,	\
		t_f64:	 F64_##FUNCTION,	\
		t_f80:	 F80_##FUNCTION,	\
		t_f128:	 F128_##FUNCTION,	\
		t_float: Float_##FUNCTION,	\
	)(X, Y)



#ifndef __LIBCCC_NOFUNCTIONS__

/*
** ************************************************************************** *|
**                          Integer Rounding Operations                       *|
** ************************************************************************** *|
*/

//! Returns the value of `x`, rounded to the nearest integer
/*!
**	- Math: @f$ {round{x}} @f$ or @f$ {\lfloor{x}\rceil} @f$
*/
#define						Math_Round(X)		DEFINE_GENERIC_MATH_FUNCTION(Round, X)
#define c_round				Math_Round
#define Math_FloatRound		Math_Round

//! Returns the value of `x`, rounded to the superior integer
/*!
**	- Math: @f$ {floor{x}} @f$ or @f$ {\lfloor{x}\rfloor} @f$
*/
#define						Math_Floor(X)		DEFINE_GENERIC_MATH_FUNCTION(Floor, X)
#define c_floor				Math_Floor
#define Math_FloatFloor		Math_Floor

//! Returns the value of `x`, rounded to the inferior integer
/*!
**	- Math: @f$ {ceil{x}} @f$ or @f$ {\lceil{x}\rceil} @f$
*/
#define						Math_Ceiling(X)		DEFINE_GENERIC_MATH_FUNCTION(Ceiling, X)
#define c_ceil				Math_Ceiling
#define Math_FloatCeiling	Math_Ceiling

//! Returns the value of `x`, rounded towards 0
/*!
**	- Math: @f$ {trunc{x}} @f$
*/
#define						Math_Truncate(X)	DEFINE_GENERIC_MATH_FUNCTION(Truncate, X)
#define c_trunc				Math_Truncate
#define Math_FloatTrunc		Math_Truncate



/*
** ************************************************************************** *|
**                            Basic Math Operators                            *|
** ************************************************************************** *|
*/

//! Returns the absolute value of `x` (makes `x` positive)
/*!
**	- Math: @f$ {|x|} @f$
*/
#define						Math_Abs(X)		DEFINE_GENERIC_MATH_FUNCTION(Abs, X)
#define c_abs				Math_Abs
#define Math_AbsoluteValue	Math_Abs



//! Returns the addition result of `x` and `y`
/*!
**	- Math: @f$ {x + y} @f$
*/
#define						Math_Add(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Add, X, Y)
#define c_add				Math_Add

//! Returns the subtraction result of `x` by `y`
/*!
**	- Math: @f$ {x - y} @f$
*/
#define						Math_Sub(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Sub, X, Y)
#define c_sub				Math_Sub
#define Math_Subtract		Math_Sub

//! Returns the multiplication result of `x` and `y`
/*!
**	- Math: @f$ {x \times y} @f$
*/
#define						Math_Mul(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Mul, X, Y)
#define c_mul				Math_Mul
#define Math_Multiply		Math_Mul

//! Returns the quotient of euclidian division of `x` by `y`
/*!
**	- Math: @f$ {\frac{x}{y}} @f$
*/
#define						Math_Div(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Div, X, Y)
#define c_div				Math_Div
#define Math_Divide			Math_Div

/*
** ************************************************************************** *|
**                            Arithmetic Operations                           *|
** ************************************************************************** *|
*/

//! Returns the remainder of euclidian division of `x` by `y`
/*!
**	- Math: @f$ {x \mod y} @f$
*/
#define						Math_Mod(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Mod, X, Y)
#define c_mod				Math_Mod
#define Math_Modulo			Math_Mod

//! Returns the value of `x` to the power of `y`
/*!
**	- Math: @f$ {x^y} @f$
*/
#define						Math_Pow(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(Pow, X, Y)
#define c_pow				Math_Pow
#define Math_Power			Math_Pow

//! Returns the value of `x` to the power of `n` (integer)
/*!
**	- Math: @f$ {x^n} @f$
*/
#define						Math_IntPow(X, N);	DEFINE_GENERIC_MATH_OPERATOR(IntPow, X, N)
#define c_intpow			Math_IntPow
#define Math_IntPower		Math_IntPow



//! Returns the square root of `x` (inverse of power of 2)
/*!
**	- Math: @f$ {\sqrt{x}} @f$
*/
#define						Math_Root2(X)	DEFINE_GENERIC_MATH_FUNCTION(Root2, X)
#define c_sqrt				Math_Root2
#define Math_SqRt			Math_Root2
#define Math_SquareRoot		Math_Root2

//! Returns the cubic root of `x` (inverse of power of 3)
/*!
**	- Math: @f$ {\sqrt[3]{x}} @f$
*/
#define						Math_Root3(X)	DEFINE_GENERIC_MATH_FUNCTION(Root3, X)
#define c_cbrt				Math_Root3
#define Math_CbRt			Math_Root3
#define Math_CubeRoot		Math_Root3

//! Returns the power-n-ic root of `x` (inverse of power of `n`)
/*!
**	- Math: @f$ {\sqrt[n]{x}} @f$
*/
#define						Math_RootN(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(RootN, X, Y)
#define c_nrt				Math_RootN
#define Math_NRt			Math_RootN
#define Math_NRoot			Math_RootN

// TODO hypot: {\sqrt{x^2+y^2}}



/*
** ************************************************************************** *|
**                           Exponentiation Operations                        *|
** ************************************************************************** *|
*/

//! Returns the exponential function's value for `x`
/*!
**	- Math: @f$ {e^x} @f$
*/
#define							Math_Exp(X)		DEFINE_GENERIC_MATH_FUNCTION(Exp, X)
#define c_exp					Math_Exp
#define Math_Exponential		Math_Exp

//! Returns the natural logarithm of `x`
/*!
**	- Math: @f$ {\ln {x}} @f$
*/
#define							Math_Ln(X)		DEFINE_GENERIC_MATH_FUNCTION(Ln, X)
#define c_ln					Math_Ln
#define Math_NaturalLogarithm	Math_Ln

//! Returns the binary (base-2) logarithm of `x`
/*!
**	- Math: @f$ {\log_{2} {x}} @f$
*/
#define							Math_Log2(X)	DEFINE_GENERIC_MATH_FUNCTION(Log2, X)
#define c_lg					Math_Log2
#define c_log2					Math_Log2
#define Math_Logarithm_Base2	Math_Log2

//! Returns the decimal (base-10) logarithm of `x`
/*!
**	- Math: @f$ {\log_{10} {x}} @f$
*/
#define							Math_Log10(X)	DEFINE_GENERIC_MATH_FUNCTION(Log10, X)
#define c_log					Math_Log10
#define c_log10					Math_Log10
#define Math_Logarithm_Base10	Math_Log10

//! Returns the base-`n` logarithm of `x`
/*!
**	- Math: @f$ {\log_{n} {x}} @f$
*/
#define							Math_LogN(X, Y)	DEFINE_GENERIC_MATH_OPERATOR(LogN, X, Y)
#define c_logn					Math_LogN
#define Math_Logarithm_BaseN	Math_LogN



/*
** ************************************************************************** *|
**                           Trigonometric Operations                         *|
** ************************************************************************** *|
*/

//! Returns the cosine of `x` (horizontal trigonometry coordinate)
/*!
**	- Math: @f$ {\cos {x}} @f$
*/
#define						Math_Cos(X)		DEFINE_GENERIC_MATH_FUNCTION(Cos, X)
#define c_cos				Math_Cos
#define Math_Cosine			Math_Cos

//! Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	- Math: @f$ {\sin {x}} @f$
*/
#define						Math_Sin(X)		DEFINE_GENERIC_MATH_FUNCTION(Sin, X)
#define c_sin				Math_Sin
#define Math_Sine			Math_Sin

//! Returns the tangent of `x` (trigonometry tangent line)
/*!
**	- Math: @f$ {\tan {x}} @f$
*/
#define						Math_Tan(X)		DEFINE_GENERIC_MATH_FUNCTION(Tan, X)
#define c_tan				Math_Tan
#define Math_Tangent		Math_Tan

//! Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	- Math: @f$ {\cos^{-1} {x}} @f$
*/
#define						Math_ArcCos(X)		DEFINE_GENERIC_MATH_FUNCTION(ArcCos, X)
#define c_acos				Math_ArcCos
#define Math_Cos_1			Math_ArcCos
#define Math_InvCosine		Math_ArcCos

//! Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	- Math: @f$ {\sin^{-1} {x}} @f$
*/
#define						Math_ArcSin(X)		DEFINE_GENERIC_MATH_FUNCTION(ArcSin, X)
#define c_asin				Math_ArcSin
#define Math_Sin_1			Math_ArcSin
#define Math_InvSine		Math_ArcSin

//! Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	- Math: @f$ {\tan^{-1} {x}} @f$
*/
#define						Math_ArcTan(X)		DEFINE_GENERIC_MATH_FUNCTION(ArcTan, X)
#define c_atan				Math_ArcTan
#define Math_Tan_1			Math_ArcTan
#define Math_InvTangent		Math_ArcTan



//! Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	- Math: @f$ {\arctan(\frac{y}{x})} @f$, in the range @f$ {[-\pi;+\pi]} @f$
*/
#define							Math_ArcTan2(Y, X)	DEFINE_GENERIC_MATH_FUNCTION(ArcTan2, Y, X)
#define c_atan2					Math_ArcTan2
#define Math_ArcTan_YoverX		Math_ArcTan2
#define Math_ArcTangent2		Math_ArcTan2
#define Math_ArcTangent_YoverX	Math_ArcTan2



/*
** ************************************************************************** *|
**                           Hyperbolic Trigonometry                          *|
** ************************************************************************** *|
*/

//! Returns the hyperbolic cosine of `x`
/*!
**	- Math: @f$ {\cosh {x}} @f$
*/
#define								Math_CosH(X)	DEFINE_GENERIC_MATH_FUNCTION(CosH, X)
#define c_cosh						Math_CosH
#define Math_Cos_H					Math_CosH
#define Math_Cosine_Hyperbolic		Math_CosH

//! Returns the hyperbolic sine of `x`
/*!
**	- Math: @f$ {\sinh {x}} @f$
*/
#define								Math_SinH(X)	DEFINE_GENERIC_MATH_FUNCTION(SinH, X)
#define c_sinh						Math_SinH
#define Math_Sin_H					Math_SinH
#define Math_Sine_Hyperbolic		Math_SinH

//! Returns the hyperbolic tangent of `x`
/*!
**	- Math: @f$ {\tanh {x}} @f$
*/
#define								Math_TanH(X)	DEFINE_GENERIC_MATH_FUNCTION(TanH, X)
#define c_tanh						Math_TanH
#define Math_Tan_H					Math_TanH
#define Math_Tangent_Hyperbolic		Math_TanH

//! Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	- Math: @f$ {\cosh^{-1} {x}} @f$
*/
#define								Math_InvCosH(X)	DEFINE_GENERIC_MATH_FUNCTION(InvCosH, X)
#define c_acosh						Math_InvCosH
#define Math_Cos_1_H				Math_InvCosH
#define Math_InvCosine_Hyperbolic	Math_InvCosH

//! Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	- Math: @f$ {\sinh^{-1} {x}} @f$
*/
#define								Math_InvSinH(X)	DEFINE_GENERIC_MATH_FUNCTION(InvSinH, X)
#define c_asinh						Math_InvSinH
#define Math_Sin_1_H				Math_InvSinH
#define Math_InvSine_Hyperbolic		Math_InvSinH

//! Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	- Math: @f$ {\tanh^{-1} {x}} @f$
*/
#define								Math_InvTanH(X)	DEFINE_GENERIC_MATH_FUNCTION(InvTanH, X)
#define c_atanh						Math_InvTanH
#define Math_Tan_1_H				Math_InvTanH
#define Math_InvTangent_Hyperbolic	Math_InvTanH



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



#endif

/*! @} */
HEADER_END
#endif
