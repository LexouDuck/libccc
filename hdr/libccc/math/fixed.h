/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/fixed.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_FIXED_H
#define __LIBCCC_MATH_FIXED_H
/*!@group{libccc_math_fixed}
** @{
**	This header defines the common standard math functions and macro defines.
**
**	@nonstd
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/fixed.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/



//! The type of function which takes one real number and outputs one real number
typedef		t_fixed	(*f_fixed_function)	(t_fixed x);
typedef		t_q16	(*f_q16_function)	(t_q16 x);
typedef		t_q32	(*f_q32_function)	(t_q32 x);
typedef		t_q64	(*f_q64_function)	(t_q64 x);
typedef		t_q128	(*f_q128_function)	(t_q128 x);

//! The type of function which takes two real numbers and outputs one real number
typedef		t_fixed	(*f_fixed_operator)	(t_fixed x,	t_fixed y);
typedef		t_q16	(*f_q16_operator)	(t_q16 x,	t_q16 y);
typedef		t_q32	(*f_q32_operator)	(t_q32 x,	t_q32 y);
typedef		t_q64	(*f_q64_operator)	(t_q64 x,	t_q64 y);
typedef		t_q128	(*f_q128_operator)	(t_q128 x,	t_q128 y);



/*
** ************************************************************************** *|
**                            Arithmetic Operations                           *|
** ************************************************************************** *|
*/

//! Returns the absolute value of `x` (makes `x` positive)
/*!
**	@nonstd
**
**	- Math: @f$ {|x|} @f$
*/
//!@{
#define						Fixed_Abs	CONCAT(FIXED_TYPE,_Abs)
t_q16						Q16_Abs(t_q16 x);
t_q32						Q32_Abs(t_q32 x);
t_q64						Q64_Abs(t_q64 x);
#ifdef __int128
t_q128						Q128_Abs(t_q128 x);
#endif
#define c_qabs				Fixed_Abs 	//!< @alias{Fixed_Abs}
#define c_q16abs			Q16_Abs 	//!< @alias{Q16_Abs}
#define c_q32abs			Q32_Abs 	//!< @alias{Q32_Abs}
#define c_q64abs			Q64_Abs 	//!< @alias{Q64_Abs}
#define c_q128abs			Q128_Abs 	//!< @alias{Q128_Abs}

#define Fixed_AbsoluteValue	Fixed_Abs
//!@}

//! Returns the value of `x`, rounded to the nearest integer
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Round	CONCAT(FIXED_TYPE,_Round)
t_q16					Q16_Round(t_q16 x);
t_q32					Q32_Round(t_q32 x);
t_q64					Q64_Round(t_q64 x);
#ifdef __int128
t_q128					Q128_Round(t_q128 x);
#endif
#define c_qround		Fixed_Round //!< @alias{Fixed_Round}
#define c_q16round		Q16_Round 	//!< @alias{Q16_Round}
#define c_q32round		Q32_Round 	//!< @alias{Q32_Round}
#define c_q64round		Q64_Round 	//!< @alias{Q64_Round}
#define c_q128round		Q128_Round 	//!< @alias{Q128_Round}
//!@}

//! Returns the value of `x`, rounded towards 0
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Truncate	CONCAT(FIXED_TYPE,_Truncate)
t_q16					Q16_Truncate(t_q16 x);
t_q32					Q32_Truncate(t_q32 x);
t_q64					Q64_Truncate(t_q64 x);
#ifdef __int128
t_q128					Q128_Truncate(t_q128 x);
#endif
#define c_qtrunc		Fixed_Truncate 	//!< @alias{Fixed_Truncate}
#define c_q16trunc		Q16_Truncate 	//!< @alias{Q16_Truncate}
#define c_q32trunc		Q32_Truncate 	//!< @alias{Q32_Truncate}
#define c_q64trunc		Q64_Truncate 	//!< @alias{Q64_Truncate}
#define c_q128trunc		Q128_Truncate 	//!< @alias{Q128_Truncate}

#define Fixed_Trunc		Fixed_Truncate
//!@}

//! Returns the value of `x`, rounded to the superior integer
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Floor	CONCAT(FIXED_TYPE,_Floor)
t_q16					Q16_Floor(t_q16 x);
t_q32					Q32_Floor(t_q32 x);
t_q64					Q64_Floor(t_q64 x);
#ifdef __int128
t_q128					Q128_Floor(t_q128 x);
#endif
#define c_qfloor		Fixed_Floor
#define c_q16floor		Q16_Floor
#define c_q32floor		Q32_Floor
#define c_q64floor		Q64_Floor
#define c_q128floor		Q128_Floor
//!@}

//! Returns the value of `x`, rounded to the inferior integer
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Ceiling	CONCAT(FIXED_TYPE,_Ceiling)
t_q16					Q16_Ceiling(t_q16 x);
t_q32					Q32_Ceiling(t_q32 x);
t_q64					Q64_Ceiling(t_q64 x);
#ifdef __int128
t_q128					Q128_Ceiling(t_q128 x);
#endif
#define c_qceil			Fixed_Ceiling
#define c_q16ceil		Q16_Ceiling
#define c_q32ceil		Q32_Ceiling
#define c_q64ceil		Q64_Ceiling
#define c_q128ceil		Q128_Ceiling

#define Fixed_Ceil		Fixed_Ceiling
//!@}



/*
** ************************************************************************** *|
**                         Fixed-point basic operators                        *|
** ************************************************************************** *|
*/



//! Performs an addition between the 2 given floating-point values (operator: `+`)
//!@{
#define				Fixed_Add	CONCAT(FIXED_TYPE,_Add)
t_q16				Q16_Add(t_q16 x, t_q16 y);
t_q32				Q32_Add(t_q32 x, t_q32 y);
t_q64				Q64_Add(t_q64 x, t_q64 y);
#ifdef __int128
t_q128				Q128_Add(t_q128 x, t_q128 y);
#endif
#define c_qadd		Fixed_Add	//!< @alias{Fixed_Add}
#define c_q16add	Q16_Add 	//!< @alias{Q16_Add}
#define c_q32add	Q32_Add 	//!< @alias{Q32_Add}
#define c_q64add	Q64_Add 	//!< @alias{Q64_Add}
#define c_q128add	Q128_Add 	//!< @alias{Q128_Add}
//!@}



//! Performs an addition between the 2 given floating-point values (operator: `-`)
//!@{
#define				Fixed_Sub	CONCAT(FIXED_TYPE,_Sub)
t_q16				Q16_Sub(t_q16 x, t_q16 y);
t_q32				Q32_Sub(t_q32 x, t_q32 y);
t_q64				Q64_Sub(t_q64 x, t_q64 y);
#ifdef __int128
t_q128				Q128_Sub(t_q128 x, t_q128 y);
#endif
#define c_qsub		Fixed_Sub	//!< @alias{Fixed_Sub}
#define c_q16sub	Q16_Sub 	//!< @alias{Q16_Sub}
#define c_q32sub	Q32_Sub 	//!< @alias{Q32_Sub}
#define c_q64sub	Q64_Sub 	//!< @alias{Q64_Sub}
#define c_q128sub	Q128_Sub 	//!< @alias{Q128_Sub}
//!@}



//! Performs an addition between the 2 given floating-point values (operator: `*`)
//!@{
#define				Fixed_Mul	CONCAT(FIXED_TYPE,_Mul)
t_q16				Q16_Mul(t_q16 x, t_q16 y);
t_q32				Q32_Mul(t_q32 x, t_q32 y);
t_q64				Q64_Mul(t_q64 x, t_q64 y);
#ifdef __int128
t_q128				Q128_Mul(t_q128 x, t_q128 y);
#endif
#define c_qmul		Fixed_Mul	//!< @alias{Fixed_Mul}
#define c_q16mul	Q16_Mul 	//!< @alias{Q16_Mul}
#define c_q32mul	Q32_Mul 	//!< @alias{Q32_Mul}
#define c_q64mul	Q64_Mul 	//!< @alias{Q64_Mul}
#define c_q128mul	Q128_Mul 	//!< @alias{Q128_Mul}
//!@}



//! Performs a division between the 2 given floating-point values (operator: `/`)
//!@{
#define				Fixed_Div	CONCAT(FIXED_TYPE,_Div)
t_q16				Q16_Div(t_q16 x, t_q16 y);
t_q32				Q32_Div(t_q32 x, t_q32 y);
t_q64				Q64_Div(t_q64 x, t_q64 y);
#ifdef __int128
t_q128				Q128_Div(t_q128 x, t_q128 y);
#endif
#define c_qdiv		Fixed_Div	//!< @alias{Fixed_Div}
#define c_q16div	Q16_Div 	//!< @alias{Q16_Div}
#define c_q32div	Q32_Div 	//!< @alias{Q32_Div}
#define c_q64div	Q64_Div 	//!< @alias{Q64_Div}
#define c_q128div	Q128_Div 	//!< @alias{Q128_Div}
//!@}



//! Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Mod	CONCAT(FIXED_TYPE,_Mod)
t_q16					Q16_Mod(t_q16 x, t_q16 y);
t_q32					Q32_Mod(t_q32 x, t_q32 y);
t_q64					Q64_Mod(t_q64 x, t_q64 y);
#ifdef __int128
t_q128					Q128_Mod(t_q128 x, t_q128 y);
#endif
#define c_qmod			Fixed_Mod
#define c_q16mod		Q16_Mod
#define c_q32mod		Q32_Mod
#define c_q64mod		Q64_Mod
#define c_q128mod		Q128_Mod

#define Fixed_Modulo	Fixed_Mod
//!@}



/*
** ************************************************************************** *|
**                          Fixed-point math operators                        *|
** ************************************************************************** *|
*/



//! Returns the value of `x` to the power of `y` (fixed)
/*!
**	@nonstd
**
**	- Math: @f$ {x^y} @f$
*/
//!@{
#define					Fixed_Pow	CONCAT(FIXED_TYPE,_Pow)
t_q16					Q16_Pow(t_q16 x, t_q16 y);
t_q32					Q32_Pow(t_q32 x, t_q32 y);
t_q64					Q64_Pow(t_q64 x, t_q64 y);
#ifdef __int128
t_q128					Q128_Pow(t_q128 x, t_q128 y);
#endif
#define c_qpow			Fixed_Pow
#define c_q16pow		Q16_Pow
#define c_q32pow		Q32_Pow
#define c_q64pow		Q64_Pow
#define c_q128pow		Q128_Pow

#define Fixed_Power		Fixed_Pow
//!@}

//! Returns the value of `x` to the power of `n` (integer)
/*!
**	@nonstd
**
**	- Math: @f$ {x^n} @f$
*/
//!@{
#define					Fixed_IntPow	CONCAT(FIXED_TYPE,_IntPow)
t_q16					Q16_IntPow(t_q16 x, t_sint n);
t_q32					Q32_IntPow(t_q32 x, t_sint n);
t_q64					Q64_IntPow(t_q64 x, t_sint n);
#ifdef __int128
t_q128					Q128_IntPow(t_q128 x, t_sint n);
#endif
#define c_qintpow		Fixed_IntPow
#define c_q16intpow		Q16_IntPow
#define c_q32intpow		Q32_IntPow
#define c_q64intpow		Q64_IntPow
#define c_q128intpow	Q128_IntPow

#define Fixed_IntPower	Fixed_IntPow
//!@}



//! Returns the square root of `x` (inverse of power of 2)
/*!
**	@nonstd
**
**	- Math: @f$ {\sqrt {x}} @f$
*/
//!@{
#define						Fixed_Root2	CONCAT(FIXED_TYPE,_Root2)
t_q16						Q16_Root2(t_q16 x);
t_q32						Q32_Root2(t_q32 x);
t_q64						Q64_Root2(t_q64 x);
#ifdef __int128
t_q128						Q128_Root2(t_q128 x);
#endif
#define c_qsqrt				Fixed_Root2
#define c_q16sqrt			Q16_Root2
#define c_q32sqrt			Q32_Root2
#define c_q64sqrt			Q64_Root2
#define c_q128sqrt			Q128_Root2

#define Fixed_SqRt			Fixed_Root2
#define Fixed_SquareRoot	Fixed_Root2
//!@}

//! Returns the cubic root of `x` (inverse of power of 3)
/*!
**	@nonstd
**
**	- Math: @f$ {\sqrt[3] {x}} @f$
*/
//!@{
#define						Fixed_Root3	CONCAT(FIXED_TYPE,_Root3)
t_q16						Q16_Root3(t_q16 x);
t_q32						Q32_Root3(t_q32 x);
t_q64						Q64_Root3(t_q64 x);
#ifdef __int128
t_q128						Q128_Root3(t_q128 x);
#endif
#define c_qcbrt				Fixed_Root3
#define c_q16cbrt			Q16_Root3
#define c_q32cbrt			Q32_Root3
#define c_q64cbrt			Q64_Root3
#define c_q128cbrt			Q128_Root3

#define Fixed_CbRt			Fixed_Root3
#define Fixed_CubeRoot		Fixed_Root3
//!@}

//! Returns the n-ic root of `x` (inverse of power of `n`)
/*!
**	@nonstd
**
**	- Math: @f$ {\sqrt[n] {x}} @f$
*/
//!@{
#define						Fixed_RootN	CONCAT(FIXED_TYPE,_RootN)
t_q16						Q16_RootN(t_q16 x, t_u8 n);
t_q32						Q32_RootN(t_q32 x, t_u8 n);
t_q64						Q64_RootN(t_q64 x, t_u8 n);
#ifdef __int128
t_q128						Q128_RootN(t_q128 x, t_u8 n);
#endif
#define c_qnrt				Fixed_RootN
#define c_q16nrt			Q16_RootN
#define c_q32nrt			Q32_RootN
#define c_q64nrt			Q64_RootN
#define c_q128nrt			Q128_RootN

#define Fixed_NRt			Fixed_RootN
#define Fixed_NRoot			Fixed_RootN
//!@}

// TODO hypot: {\sqrt{x^2+y^2}}



/*
** ************************************************************************** *|
**                           Exponentiation Operations                        *|
** ************************************************************************** *|
*/



//! Returns the exponential function's value for `x`
/*!
**	@nonstd
**
**	- Math: @f$ {e^x} @f$
*/
//!@{
#define							Fixed_Exp	CONCAT(FIXED_TYPE,_Exp)
t_q16							Q16_Exp(t_q16 x);
t_q32							Q32_Exp(t_q32 x);
t_q64							Q64_Exp(t_q64 x);
#ifdef __int128
t_q128							Q128_Exp(t_q128 x);
#endif
#define c_qexp					Fixed_Exp
#define c_q16exp				Q16_Exp
#define c_q32exp				Q32_Exp
#define c_q64exp				Q64_Exp
#define c_q128exp				Q128_Exp

#define Fixed_Exponential		Fixed_Exp
//!@}



//! Returns the natural logarithm of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\ln {x}} @f$
*/
//!@{
#define							Fixed_Ln	CONCAT(FIXED_TYPE,_Ln)
t_q16							Q16_Ln(t_q16 x);
t_q32							Q32_Ln(t_q32 x);
t_q64							Q64_Ln(t_q64 x);
#ifdef __int128
t_q128							Q128_Ln(t_q128 x);
#endif
#define c_qln					Fixed_Ln
#define c_q16ln					Q16_Ln
#define c_q32ln					Q32_Ln
#define c_q64ln					Q64_Ln
#define c_q128ln				Q128_Ln

#define Fixed_NaturalLogarithm	Fixed_Ln
//!@}

//! Returns the binary (base-2) logarithm of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\log_{2} {x}} @f$
*/
//!@{
#define							Fixed_Log2	CONCAT(FIXED_TYPE,_Log2)
t_q16							Q16_Log2(t_q16 x);
t_q32							Q32_Log2(t_q32 x);
t_q64							Q64_Log2(t_q64 x);
#ifdef __int128
t_q128							Q128_Log2(t_q128 x);
#endif
#define c_qlg					Fixed_Log2
#define c_q16lg					Q16_Log2
#define c_q32lg					Q32_Log2
#define c_q64lg					Q64_Log2
#define c_q128lg				Q128_Log2

#define c_qlog2					Fixed_Log2
#define c_q16log2				Q16_Log2
#define c_q32log2				Q32_Log2
#define c_q64log2				Q64_Log2
#define c_q128log2				Q128_Log2

#define Fixed_Logarithm_Base2	Fixed_Log2
//!@}

//! Returns the decimal (base-10) logarithm of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\log_{10} {x}} @f$
*/
//!@{
#define							Fixed_Log10	CONCAT(FIXED_TYPE,_Log10)
t_q16							Q16_Log10(t_q16 x);
t_q32							Q32_Log10(t_q32 x);
t_q64							Q64_Log10(t_q64 x);
#ifdef __int128
t_q128							Q128_Log10(t_q128 x);
#endif
#define c_qlog					Fixed_Log10
#define c_q16log				Q16_Log10
#define c_q32log				Q32_Log10
#define c_q64log				Q64_Log10
#define c_q128log				Q128_Log10

#define c_qlog10				Fixed_Log10
#define c_q16log10				Q16_Log10
#define c_q32log10				Q32_Log10
#define c_q64log10				Q64_Log10
#define c_q128log10				Q128_Log10

#define Fixed_Logarithm_Base10	Fixed_Log10
//!@}

//! Returns the base-`n` logarithm of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\log_{n} {x}} @f$
*/
//!@{
#define							Fixed_LogN	CONCAT(FIXED_TYPE,_LogN)
t_q16							Q16_LogN(t_q16 x, t_q16 y);
t_q32							Q32_LogN(t_q32 x, t_q32 y);
t_q64							Q64_LogN(t_q64 x, t_q64 y);
#ifdef __int128
t_q128							Q128_LogN(t_q128 x, t_q128 y);
#endif
#define c_qlogn					Fixed_LogN
#define c_q16logn				Q16_LogN
#define c_q32logn				Q32_LogN
#define c_q64logn				Q64_LogN
#define c_q128logn				Q128_LogN

#define Fixed_Logarithm_BaseN	Fixed_LogN
//!@}



/*
** ************************************************************************** *|
**                           Trigonometric Operations                         *|
** ************************************************************************** *|
*/



//! Returns the cosine of `x` (horizontal trigonometry coordinate)
/*!
**	@nonstd
**
**	- Math: @f$ {\cos {x}} @f$
*/
//!@{
#define							Fixed_Cos	CONCAT(FIXED_TYPE,_Cos)
t_q16							Q16_Cos(t_q16 x);
t_q32							Q32_Cos(t_q32 x);
t_q64							Q64_Cos(t_q64 x);
#ifdef __int128
t_q128							Q128_Cos(t_q128 x);
#endif
#define c_qcos					Fixed_Cos
#define c_q16cos				Q16_Cos
#define c_q32cos				Q32_Cos
#define c_q64cos				Q64_Cos
#define c_q128cos				Q128_Cos

#define Fixed_Cosine			Fixed_Cos
//!@}

//! Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	@nonstd
**
**	- Math: @f$ {\sin {x}} @f$
*/
//!@{
#define							Fixed_Sin	CONCAT(FIXED_TYPE,_Sin)
t_q16							Q16_Sin(t_q16 x);
t_q32							Q32_Sin(t_q32 x);
t_q64							Q64_Sin(t_q64 x);
#ifdef __int128
t_q128							Q128_Sin(t_q128 x);
#endif
#define c_qsin					Fixed_Sin
#define c_q16sin				Q16_Sin
#define c_q32sin				Q32_Sin
#define c_q64sin				Q64_Sin
#define c_q128sin				Q128_Sin

#define Fixed_Sine				Fixed_Sin
//!@}

//! Returns the tangent of `x` (trigonometry tangent line)
/*!
**	@nonstd
**
**	- Math: @f$ {\tan {x}} @f$
*/
//!@{
#define							Fixed_Tan	CONCAT(FIXED_TYPE,_Tan)
t_q16							Q16_Tan(t_q16 x);
t_q32							Q32_Tan(t_q32 x);
t_q64							Q64_Tan(t_q64 x);
#ifdef __int128
t_q128							Q128_Tan(t_q128 x);
#endif
#define c_qtan					Fixed_Tan
#define c_q16tan				Q16_Tan
#define c_q32tan				Q32_Tan
#define c_q64tan				Q64_Tan
#define c_q128tan				Q128_Tan

#define Fixed_Tangent			Fixed_Tan
//!@}



//! Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	@nonstd
**
**	- Math: @f$ {\cos^{-1} {x}} @f$
*/
//!@{
#define							Fixed_ArcCos	CONCAT(FIXED_TYPE,_ArcCos)
t_q16							Q16_ArcCos(t_q16 x);
t_q32							Q32_ArcCos(t_q32 x);
t_q64							Q64_ArcCos(t_q64 x);
#ifdef __int128
t_q128							Q128_ArcCos(t_q128 x);
#endif
#define c_qacos					Fixed_ArcCos
#define c_q16acos				Q16_ArcCos
#define c_q32acos				Q32_ArcCos
#define c_q64acos				Q64_ArcCos
#define c_q128acos				Q128_ArcCos

#define Fixed_Cos_1				Fixed_ArcCos
#define Fixed_InvCosine			Fixed_ArcCos
//!@}

//! Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	@nonstd
**
**	- Math: @f$ {\sin^{-1} {x}} @f$
*/
//!@{
#define							Fixed_ArcSin	CONCAT(FIXED_TYPE,_ArcSin)
t_q16							Q16_ArcSin(t_q16 x);
t_q32							Q32_ArcSin(t_q32 x);
t_q64							Q64_ArcSin(t_q64 x);
#ifdef __int128
t_q128							Q128_ArcSin(t_q128 x);
#endif
#define c_qasin					Fixed_ArcSin
#define c_q16asin				Q16_ArcSin
#define c_q32asin				Q32_ArcSin
#define c_q64asin				Q64_ArcSin
#define c_q128asin				Q128_ArcSin

#define Fixed_Sin_1				Fixed_ArcSin
#define Fixed_InvSine			Fixed_ArcSin
//!@}

//! Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	@nonstd
**
**	- Math: @f$ {\tan^{-1} {x}} @f$
*/
//!@{
#define							Fixed_ArcTan	CONCAT(FIXED_TYPE,_ArcTan)
t_q16							Q16_ArcTan(t_q16 x);
t_q32							Q32_ArcTan(t_q32 x);
t_q64							Q64_ArcTan(t_q64 x);
#ifdef __int128
t_q128							Q128_ArcTan(t_q128 x);
#endif
#define c_qatan					Fixed_ArcTan
#define c_q16atan				Q16_ArcTan
#define c_q32atan				Q32_ArcTan
#define c_q64atan				Q64_ArcTan
#define c_q128atan				Q128_ArcTan

#define Fixed_Tan_1				Fixed_ArcTan
#define Fixed_InvTangent		Fixed_ArcTan
//!@}



//! Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	@nonstd
**
**	- Math: @f$ {\arctan(\frac{y}{x})} @f$, in the range @f$ {[-\pi;+\pi]} @f$
*/
//!@{
#define								Fixed_ArcTan2	CONCAT(FIXED_TYPE,_ArcTan2)
t_q16								Q16_(t_q16 x, t_q16 y);
t_q32								Q32_(t_q32 x, t_q32 y);
t_q64								Q64_(t_q64 x, t_q64 y);
#ifdef __int128
t_q128								Q128_(t_q128 x, t_q128 y);
#endif
#define c_qatan2					Fixed_ArcTan2
#define c_q16atan2					Q16_ArcTan2
#define c_q32atan2					Q32_ArcTan2
#define c_q64atan2					Q64_ArcTan2
#define c_q128atan2					Q128_ArcTan2

#define Fixed_ArcTan_YoverX			Fixed_ArcTan2
#define Fixed_ArcTangent2			Fixed_ArcTan2
#define Fixed_ArcTangent_YoverX		Fixed_ArcTan2
//!@}



//! Returns the hyperbolic cosine of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\cosh {x}} @f$
*/
//!@{
#define								Fixed_CosH	CONCAT(FIXED_TYPE,_CosH)
t_q16								Q16_CosH(t_q16 x);
t_q32								Q32_CosH(t_q32 x);
t_q64								Q64_CosH(t_q64 x);
#ifdef __int128
t_q128								Q128_CosH(t_q128 x);
#endif
#define c_qcosh						Fixed_CosH
#define c_q16cosh					Q16_CosH
#define c_q32cosh					Q32_CosH
#define c_q64cosh					Q64_CosH
#define c_q128cosh					Q128_CosH

#define Fixed_Cos_H					Fixed_CosH
#define Fixed_Cosine_Hyperbolic		Fixed_CosH
//!@}

//! Returns the hyperbolic sine of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\sinh {x}} @f$
*/
//!@{
#define								Fixed_SinH	CONCAT(FIXED_TYPE,_SinH)
t_q16								Q16_SinH(t_q16 x);
t_q32								Q32_SinH(t_q32 x);
t_q64								Q64_SinH(t_q64 x);
#ifdef __int128
t_q128								Q128_SinH(t_q128 x);
#endif
#define c_qsinh						Fixed_SinH
#define c_q16sinh					Q16_SinH
#define c_q32sinh					Q32_SinH
#define c_q64sinh					Q64_SinH
#define c_q128sinh					Q128_SinH

#define Fixed_Sin_H					Fixed_SinH
#define Fixed_Sine_Hyperbolic		Fixed_SinH
//!@}

//! Returns the hyperbolic tangent of `x`
/*!
**	@nonstd
**
**	- Math: @f$ {\tanh {x}} @f$
*/
//!@{
#define								Fixed_TanH	CONCAT(FIXED_TYPE,_TanH)
t_q16								Q16_TanH(t_q16 x);
t_q32								Q32_TanH(t_q32 x);
t_q64								Q64_TanH(t_q64 x);
#ifdef __int128
t_q128								Q128_TanH(t_q128 x);
#endif
#define c_qtanh						Fixed_TanH
#define c_q16tanh					Q16_TanH
#define c_q32tanh					Q32_TanH
#define c_q64tanh					Q64_TanH
#define c_q128tanh					Q128_TanH

#define Fixed_Tan_H					Fixed_TanH
#define Fixed_Tangent_Hyperbolic	Fixed_TanH
//!@}



//! Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	@nonstd
**
**	- Math: @f$ {\cosh^{-1} {x}} @f$
*/
//!@{
#define								Fixed_InvCosH	CONCAT(FIXED_TYPE,_InvCosH)
t_q16								Q16_InvCosH(t_q16 x);
t_q32								Q32_InvCosH(t_q32 x);
t_q64								Q64_InvCosH(t_q64 x);
#ifdef __int128
t_q128								Q128_InvCosH(t_q128 x);
#endif
#define c_qacosh					Fixed_InvCosH
#define c_q16acosh					Q16_InvCosH
#define c_q32acosh					Q32_InvCosH
#define c_q64acosh					Q64_InvCosH
#define c_q128acosh					Q128_InvCosH

#define Fixed_Cos_1_H				Fixed_InvCosH
#define Fixed_InvCosine_Hyperbolic	Fixed_InvCosH
//!@}

//! Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	@nonstd
**
**	- Math: @f$ {\sinh^{-1} {x}} @f$
*/
//!@{
#define								Fixed_InvSinH	CONCAT(FIXED_TYPE,_InvSinH)
t_q16								Q16_InvSinH(t_q16 x);
t_q32								Q32_InvSinH(t_q32 x);
t_q64								Q64_InvSinH(t_q64 x);
#ifdef __int128
t_q128								Q128_InvSinH(t_q128 x);
#endif
#define c_qasinh					Fixed_InvSinH
#define c_q16asinh					Q16_InvSinH
#define c_q32asinh					Q32_InvSinH
#define c_q64asinh					Q64_InvSinH
#define c_q128asinh					Q128_InvSinH

#define Fixed_Sin_1_H				Fixed_InvSinH
#define Fixed_InvSine_Hyperbolic	Fixed_InvSinH
//!@}

//! Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	@nonstd
**
**	- Math: @f$ {\tanh^{-1} {x}} @f$
*/
//!@{
#define								Fixed_InvTanH	CONCAT(FIXED_TYPE,_InvTanH)
t_q16								Q16_InvTanH(t_q16 x);
t_q32								Q32_InvTanH(t_q32 x);
t_q64								Q64_InvTanH(t_q64 x);
#ifdef __int128
t_q128								Q128_InvTanH(t_q128 x);
#endif
#define c_qatanh					Fixed_InvTanH
#define c_q16atanh					Q16_InvTanH
#define c_q32atanh					Q32_InvTanH
#define c_q64atanh					Q64_InvTanH
#define c_q128atanh					Q128_InvTanH

#define Fixed_Tan_1_H				Fixed_InvTanH
#define Fixed_InvTangent_Hyperbolic	Fixed_InvTanH
//!@}



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



/*! @} */
HEADER_END
#endif
