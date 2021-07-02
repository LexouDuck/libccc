/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/float.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_FLOAT_H
#define __LIBCCC_MATH_FLOAT_H
/*!@group{libccc_math_float}
** @{
**	This header defines the common standard math functions for floating-point numbers.
**
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math}
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/



/*!
**	This very small float is typically used to compare two floating-point values.
**	Floating point equality checks aren't the most dependable kind of operation,
**	so it's often better to do `(ABS(x - y) <= FLOAT_APPROX)` to check for equality.
**	You can use the Float_EqualsApprox() functions for this purpose.
**	@see not to be confused with #FLOAT_EPSILON
*/
#define FLOAT_APPROX	LIBCONFIG_FLOAT_APPROX



//! The type of function which takes one real number and outputs one real number
//!@{
typedef		t_float	(*f_float_function)	(t_float x);
typedef		t_f32	(*f_f32_function)	(t_f32 x);
typedef		t_f64	(*f_f64_function)	(t_f64 x);
#ifdef __float80
typedef		t_f80	(*f_f80_function)	(t_f80 x);
#endif
#ifdef __float128
typedef		t_f128	(*f_f128_function)	(t_f128 x);
#endif
//!@}

//! The type of function which takes two real numbers and outputs one real number
//!@{
typedef		t_float	(*f_float_operator)	(t_float x, t_float y);
typedef		t_f32	(*f_f32_operator)	(t_f32 x,	t_f32 y);
typedef		t_f64	(*f_f64_operator)	(t_f64 x,	t_f64 y);
#ifdef __float80
typedef		t_f80	(*f_f80_operator)	(t_f80 x,	t_f80 y);
#endif
#ifdef __float128
typedef		t_f128	(*f_f128_operator)	(t_f128 x,	t_f128 y);
#endif
//!@}



/*
** ************************************************************************** *|
**                            Arithmetic Operations                           *|
** ************************************************************************** *|
*/

//! Returns the absolute value of `x` (makes `x` positive)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fabs}
*/
//!@{
#define						Float_Abs	CONCAT(FLOAT_TYPE,_Abs)
t_f32						F32_Abs(t_f32 x);
t_f64						F64_Abs(t_f64 x);
#ifdef __float80
t_f80						F80_Abs(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Abs(t_f128 x);
#endif
#define c_fabs				Float_Abs
#define c_f32abs			F32_Abs
#define c_f64abs			F64_Abs
#define c_f80abs			F80_Abs
#define c_f128abs			F128_Abs
//!@}

//! Returns the value of `x`, rounded to the nearest integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/round}
*/
//!@{
#define						Float_Round	CONCAT(FLOAT_TYPE,_Round)
t_f32						F32_Round(t_f32 x);
t_f64						F64_Round(t_f64 x);
#ifdef __float80
t_f80						F80_Round(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Round(t_f128 x);
#endif
#define c_fround			Float_Round
#define c_f32round			F32_Round
#define c_f64round			F64_Round
#define c_f80round			F80_Round
#define c_f128round			F128_Round
//!@}

//! Returns the value of `x`, rounded towards 0
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/trunc}
*/
//!@{
#define						Float_Trunc	CONCAT(FLOAT_TYPE,_Trunc)
t_f32						F32_Trunc(t_f32 x);
t_f64						F64_Trunc(t_f64 x);
#ifdef __float80
t_f80						F80_Trunc(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Trunc(t_f128 x);
#endif
#define c_ftrunc			Float_Trunc
#define c_f32trunc			F32_Trunc
#define c_f64trunc			F64_Trunc
#define c_f80trunc			F80_Trunc
#define c_f128trunc			F128_Trunc

#define Float_Truncate		Float_Trunc
//!@}

//! Returns the value of `x`, rounded to the superior integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/floor}
*/
//!@{
#define						Float_Floor	CONCAT(FLOAT_TYPE,_Floor)
t_f32						F32_Floor(t_f32 x);
t_f64						F64_Floor(t_f64 x);
#ifdef __float80
t_f80						F80_Floor(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Floor(t_f128 x);
#endif
#define c_ffloor			Float_Floor
#define c_f32floor			F32_Floor
#define c_f64floor			F64_Floor
#define c_f80floor			F80_Floor
#define c_f128floor			F128_Floor
//!@}

//! Returns the value of `x`, rounded to the inferior integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/ceil}
*/
//!@{
#define						Float_Ceil	CONCAT(FLOAT_TYPE,_Ceil)
t_f32						F32_Ceil(t_f32 x);
t_f64						F64_Ceil(t_f64 x);
#ifdef __float80
t_f80						F80_Ceil(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Ceil(t_f128 x);
#endif
#define c_fceil				Float_Ceil
#define c_f32ceil			F32_Ceil
#define c_f64ceil			F64_Ceil
#define c_f80ceil			F80_Ceil
#define c_f128ceil			F128_Ceil

#define Float_Ceiling		Float_Ceil
//!@}



/*
** ************************************************************************** *|
**                       Floating-point logic operators                       *|
** ************************************************************************** *|
*/

//! Returns `TRUE` if the 2 given floating-point values are exactly equal (operator: `==`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (exact) equality
**	@param	y	The second value to check for (exact) equality
**	@returns
**	`TRUE` if the 2 given floating-point values are exactly equal,
**	otherwise `FALSE`.
*/
//!@{
#define					Float_Equals	CONCAT(FLOAT_TYPE,_Equals)
t_bool					F32_Equals(t_f32 x, t_f32 y);
t_bool					F64_Equals(t_f64 x, t_f64 y);
#ifdef	__float80
t_bool					F80_Equals(t_f80 x, t_f80 y);
#endif
#ifdef	__float128
t_bool					F128_Equals(t_f128 x, t_f128 y);
#endif
#define c_fequ			Float_Equals//!< @alias{Float_Equals}
#define c_f32equ		F32_Equals	//!< @alias{F32_Equals}
#define c_f64equ		F64_Equals	//!< @alias{F64_Equals}
#define c_f80equ		F80_Equals	//!< @alias{F80_Equals}
#define c_f128equ		F128_Equals	//!< @alias{F128_Equals}
//!@}



//! Returns `TRUE` if the 2 given floating-point values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (approximate) equality
**	@param	y	The second value to check for (approximate) equality
**	@returns
**	`TRUE` if the 2 given floating-point values are close enough to be considered equal
**	(using #FLOAT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					Float_EqualsApprox	CONCAT(FLOAT_TYPE,_EqualsApprox)
t_bool					F32_EqualsApprox(t_f32 x, t_f32 y);
t_bool					F64_EqualsApprox(t_f64 x, t_f64 y);
#ifdef	__float80
t_bool					F80_EqualsApprox(t_f80 x, t_f80 y);
#endif
#ifdef	__float128
t_bool					F128_EqualsApprox(t_f128 x, t_f128 y);
#endif
#define c_fequa			Float_EqualsApprox	//!< @alias{Float_EqualsApprox}
#define c_f32equa		F32_EqualsApprox	//!< @alias{F32_EqualsApprox}
#define c_f64equa		F64_EqualsApprox	//!< @alias{F64_EqualsApprox}
#define c_f80equa		F80_EqualsApprox	//!< @alias{F80_EqualsApprox}
#define c_f128equa		F128_EqualsApprox	//!< @alias{F128_EqualsApprox}
//!@}



// TODO Float_LessThan

// TODO Float_GreaterThan



/*
** ************************************************************************** *|
**                       Floating-point basic operators                       *|
** ************************************************************************** *|
*/



//! Performs an addition with the 2 given floating-point values (operator: `+`)
//!@{
#define					Float_Add	CONCAT(FLOAT_TYPE,_Add)
t_f32					F32_Add(t_f32 x, t_f32 y);
t_f64					F64_Add(t_f64 x, t_f64 y);
#ifdef	__float80
t_f80					F80_Add(t_f80 x, t_f80 y);
#endif
#ifdef	__float128
t_f128					F128_Add(t_f128 x, t_f128 y);
#endif
#define c_fadd			Float_Add	//!< @alias{Float_Add}
#define c_f32add		F32_Add 	//!< @alias{F32_Add}
#define c_f64add		F64_Add 	//!< @alias{F64_Add}
#define c_f80add		F80_Add 	//!< @alias{F80_Add}
#define c_f128add		F128_Add	//!< @alias{F128_Add}
//!@}



//! Performs a subtraction with the 2 given floating-point values (operator: `-`)
//!@{
#define					Float_Sub	CONCAT(FLOAT_TYPE,_Sub)
t_f32					F32_Sub(t_f32 x, t_f32 y);
t_f64					F64_Sub(t_f64 x, t_f64 y);
#ifdef	__float80
t_f80					F80_Sub(t_f80 x, t_f80 y);
#endif
#ifdef	__float128
t_f128					F128_Sub(t_f128 x, t_f128 y);
#endif
#define c_fsub			Float_Sub	//!< @alias{Float_Sub}
#define c_f32sub		F32_Sub 	//!< @alias{F32_Sub}
#define c_f64sub		F64_Sub 	//!< @alias{F64_Sub}
#define c_f80sub		F80_Sub 	//!< @alias{F80_Sub}
#define c_f128sub		F128_Sub	//!< @alias{F128_Sub}
//!@}



//! Performs a multiplication with the 2 given floating-point values (operator: `*`)
//!@{
#define					Float_Mul	CONCAT(FLOAT_TYPE,_Mul)
t_f32					F32_Mul(t_f32 x, t_f32 y);
t_f64					F64_Mul(t_f64 x, t_f64 y);
#ifdef	__float80
t_f80					F80_Mul(t_f80 x, t_f80 y);
#endif
#ifdef	__float128
t_f128					F128_Mul(t_f128 x, t_f128 y);
#endif
#define c_fmul			Float_Mul	//!< @alias{Float_Mul}
#define c_f32mul		F32_Mul 	//!< @alias{F32_Mul}
#define c_f64mul		F64_Mul 	//!< @alias{F64_Mul}
#define c_f80mul		F80_Mul 	//!< @alias{F80_Mul}
#define c_f128mul		F128_Mul	//!< @alias{F128_Mul}
//!@}



//! Performs a division with the 2 given floating-point values (operator: `/`)
//!@{
#define					Float_Div	CONCAT(FLOAT_TYPE,_Div)
t_f32					F32_Div(t_f32 x, t_f32 y);
t_f64					F64_Div(t_f64 x, t_f64 y);
#ifdef	__float80
t_f80					F80_Div(t_f80 x, t_f80 y);
#endif
#ifdef	__float128
t_f128					F128_Div(t_f128 x, t_f128 y);
#endif
#define c_fdiv			Float_Div	//!< @alias{Float_Div}
#define c_f32div		F32_Div 	//!< @alias{F32_Div}
#define c_f64div		F64_Div 	//!< @alias{F64_Div}
#define c_f80div		F80_Div 	//!< @alias{F80_Div}
#define c_f128div		F128_Div	//!< @alias{F128_Div}
//!@}



/*
** ************************************************************************** *|
**                        Floating-point math operators                       *|
** ************************************************************************** *|
*/



//! Returns the remainder of euclidian division of `x` by `y`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmod}
*/
//!@{
#define						Float_Mod	CONCAT(FLOAT_TYPE,_Mod)
t_f32						F32_Mod(t_f32 x, t_f32 y);
t_f64						F64_Mod(t_f64 x, t_f64 y);
#ifdef __float80
t_f80						F80_Mod(t_f80 x, t_f80 y);
#endif
#ifdef __float128
t_f128						F128_Mod(t_f128 x, t_f128 y);
#endif
#define c_fmod				Float_Mod
#define c_f32mod			F32_Mod
#define c_f64mod			F64_Mod
#define c_f80mod			F80_Mod
#define c_f128mod			F128_Mod

#define Float_Modulo		Float_Mod
//!@}



//! Returns the value of `x` to the power of `y` (float)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/pow}
*/
//!@{
#define						Float_Pow	CONCAT(FLOAT_TYPE,_Pow)
t_f32						F32_Pow(t_f32 x, t_f32 y);
t_f64						F64_Pow(t_f64 x, t_f64 y);
#ifdef __float80
t_f80						F80_Pow(t_f80 x, t_f80 y);
#endif
#ifdef __float128
t_f128						F128_Pow(t_f128 x, t_f128 y);
#endif
#define c_fpow				Float_Pow
#define c_f32pow			F32_Pow
#define c_f64pow			F64_Pow
#define c_f80pow			F80_Pow
#define c_f128pow			F128_Pow

#define Float_Power			Float_Pow
//!@}

//! Returns the value of `x` to the power of `n` (integer)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/pow}
*/
//!@{
#define						Float_IntPow	CONCAT(FLOAT_TYPE,_IntPow)
t_f32						F32_IntPow(t_f32 x, t_sint n);
t_f64						F64_IntPow(t_f64 x, t_sint n);
#ifdef __float80
t_f80						F80_IntPow(t_f80 x, t_sint n);
#endif
#ifdef __float128
t_f128						F128_IntPow(t_f128 x, t_sint n);
#endif
#define c_fintpow			Float_IntPow
#define c_f32intpow			F32_IntPow
#define c_f64intpow			F64_IntPow
#define c_f80intpow			F80_IntPow
#define c_f128intpow		F128_IntPow

#define Float_IntPower		Float_IntPow
//!@}



//! Returns the square root of `x` (inverse of power of 2)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sqrt}
*/
//!@{
#define						Float_Root2	CONCAT(FLOAT_TYPE,_Root2)
t_f32						F32_Root2(t_f32 x);
t_f64						F64_Root2(t_f64 x);
#ifdef __float80
t_f80						F80_Root2(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Root2(t_f128 x);
#endif
#define c_fsqrt				Float_Root2
#define c_f32sqrt			F32_Root2
#define c_f64sqrt			F64_Root2
#define c_f80sqrt			F80_Root2
#define c_f128sqrt			F128_Root2

#define Float_SqRt			Float_Root2
#define Float_SquareRoot	Float_Root2
//!@}

//! Returns the cubic root of `x` (inverse of power of 3)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cbrt}
*/
//!@{
#define						Float_Root3	CONCAT(FLOAT_TYPE,_Root3)
t_f32						F32_Root3(t_f32 x);
t_f64						F64_Root3(t_f64 x);
#ifdef __float80
t_f80						F80_Root3(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Root3(t_f128 x);
#endif
#define c_fcbrt				Float_Root3
#define c_f32cbrt			F32_Root3
#define c_f64cbrt			F64_Root3
#define c_f80cbrt			F80_Root3
#define c_f128cbrt			F128_Root3

#define Float_CbRt			Float_Root3
#define Float_CubeRoot		Float_Root3
//!@}

//! Returns the n-ic root of `x` (inverse of power of `n`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/nrt}
*/
//!@{
#define						Float_RootN	CONCAT(FLOAT_TYPE,_RootN)
t_f32						F32_RootN(t_f32 x, t_u8 n);
t_f64						F64_RootN(t_f64 x, t_u8 n);
#ifdef __float80
t_f80						F80_RootN(t_f80 x, t_u8 n);
#endif
#ifdef __float128
t_f128						F128_RootN(t_f128 x, t_u8 n);
#endif
#define c_fnrt				Float_RootN
#define c_f32nrt			F32_RootN
#define c_f64nrt			F64_RootN
#define c_f80nrt			F80_RootN
#define c_f128nrt			F128_RootN

#define Float_NRt			Float_RootN
#define Float_NRoot			Float_RootN
//!@}

// TODO hypot: {\sqrt{x^2+y^2}}



/*
** ************************************************************************** *|
**                           Exponentiation Operations                        *|
** ************************************************************************** *|
*/



//! Returns the exponential function's value for `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/exp}
*/
//!@{
#define							Float_Exp	CONCAT(FLOAT_TYPE,_Exp)
t_f32							F32_Exp(t_f32 x);
t_f64							F64_Exp(t_f64 x);
#ifdef __float80
t_f80							F80_Exp(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_Exp(t_f128 x);
#endif
#define c_fexp					Float_Exp
#define c_f32exp				F32_Exp
#define c_f64exp				F64_Exp
#define c_f80exp				F80_Exp
#define c_f128exp				F128_Exp

#define Float_Exponential		Float_Exp
//!@}

//! Returns the natural logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log}
*/
//!@{
#define							Float_Ln	CONCAT(FLOAT_TYPE,_Ln)
t_f32							F32_Ln(t_f32 x);
t_f64							F64_Ln(t_f64 x);
#ifdef __float80
t_f80							F80_Ln(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_Ln(t_f128 x);
#endif
#define c_fln					Float_Ln
#define c_f32ln					F32_Ln
#define c_f64ln					F64_Ln
#define c_f80ln					F80_Ln
#define c_f128ln				F128_Ln

#define Float_NaturalLogarithm	Float_Ln
//!@}

//! Returns the binary (base-2) logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log2}
*/
//!@{
#define							Float_Log2	CONCAT(FLOAT_TYPE,_Log2)
t_f32							F32_Log2(t_f32 x);
t_f64							F64_Log2(t_f64 x);
#ifdef __float80
t_f80							F80_Log2(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_Log2(t_f128 x);
#endif
#define c_flg					Float_Log2
#define c_f32lg					F32_Log2
#define c_f64lg					F64_Log2
#define c_f80lg					F80_Log2
#define c_f128lg				F128_Log2

#define c_flog2					Float_Log2

#define Float_Logarithm_Base2	Float_Log2
//!@}

//! Returns the decimal (base-10) logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log10}
*/
//!@{
#define							Float_Log10	CONCAT(FLOAT_TYPE,_Log10)
t_f32							F32_Log10(t_f32 x);
t_f64							F64_Log10(t_f64 x);
#ifdef __float80
t_f80							F80_Log10(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_Log10(t_f128 x);
#endif
#define c_flog					Float_Log10
#define c_f32log				F32_Log10
#define c_f64log				F64_Log10
#define c_f80log				F80_Log10
#define c_f128log				F128_Log10

#define c_flog10				Float_Log10

#define Float_Logarithm_Base10	Float_Log10
//!@}

//! Returns the base-`n` logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Float_LogN	CONCAT(FLOAT_TYPE,_LogN)
t_f32							F32_LogN(t_f32 x, t_f32 n);
t_f64							F64_LogN(t_f64 x, t_f64 n);
#ifdef __float80
t_f80							F80_LogN(t_f80 x, t_f80 n);
#endif
#ifdef __float128
t_f128							F128_LogN(t_f128 x, t_f128 n);
#endif
#define c_flogn					Float_LogN
#define c_f32logn				F32_LogN
#define c_f64logn				F64_LogN
#define c_f80logn				F80_LogN
#define c_f128logn				F128_LogN

#define Float_Logarithm_BaseN	Float_LogN
//!@}



/*
** ************************************************************************** *|
**                           Trigonometric Operations                         *|
** ************************************************************************** *|
*/



//! Returns the cosine of `x` (horizontal trigonometry coordinate)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cos}
*/
//!@{
#define						Float_Cos	CONCAT(FLOAT_TYPE,_Cos)
t_f32						F32_Cos(t_f32 x);
t_f64						F64_Cos(t_f64 x);
#ifdef __float80
t_f80						F80_Cos(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Cos(t_f128 x);
#endif
#define c_fcos				Float_Cos
#define c_f32cos			F32_Cos
#define c_f64cos			F64_Cos
#define c_f80cos			F80_Cos
#define c_f128cos			F128_Cos

#define Float_Cosine		Float_Cos
//!@}

//! Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sin}
*/
//!@{
#define						Float_Sin	CONCAT(FLOAT_TYPE,_Sin)
t_f32						F32_Sin(t_f32 x);
t_f64						F64_Sin(t_f64 x);
#ifdef __float80
t_f80						F80_Sin(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Sin(t_f128 x);
#endif
#define c_fsin				Float_Sin
#define c_f32sin			F32_Sin
#define c_f64sin			F64_Sin
#define c_f80sin			F80_Sin
#define c_f128sin			F128_Sin

#define Float_Sine			Float_Sin
//!@}

//! Returns the tangent of `x` (trigonometry tangent line)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tan}
*/
//!@{
#define						Float_Tan	CONCAT(FLOAT_TYPE,_Tan)
t_f32						F32_Tan(t_f32 x);
t_f64						F64_Tan(t_f64 x);
#ifdef __float80
t_f80						F80_Tan(t_f80 x);
#endif
#ifdef __float128
t_f128						F128_Tan(t_f128 x);
#endif
#define c_ftan				Float_Tan
#define c_f32tan			F32_Tan
#define c_f64tan			F64_Tan
#define c_f80tan			F80_Tan
#define c_f128tan			F128_Tan

#define Float_Tangent		Float_Tan
//!@}



//! Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/acos}
*/
//!@{
#define							Float_ArcCos	CONCAT(FLOAT_TYPE,_ArcCos)
t_f32							F32_ArcCos(t_f32 x);
t_f64							F64_ArcCos(t_f64 x);
#ifdef __float80
t_f80							F80_ArcCos(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_ArcCos(t_f128 x);
#endif
#define c_facos					Float_ArcCos
#define c_f32acos				F32_ArcCos
#define c_f64acos				F64_ArcCos
#define c_f80acos				F80_ArcCos
#define c_f128acos				F128_ArcCos

#define Float_Cos_1				Float_ArcCos
#define Float_InvCosine			Float_ArcCos
//!@}

//! Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/asin}
*/
//!@{
#define							Float_ArcSin	CONCAT(FLOAT_TYPE,_ArcSin)
t_f32							F32_ArcSin(t_f32 x);
t_f64							F64_ArcSin(t_f64 x);
#ifdef __float80
t_f80							F80_ArcSin(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_ArcSin(t_f128 x);
#endif
#define c_fasin					Float_ArcSin
#define c_f32asin				F32_ArcSin
#define c_f64asin				F64_ArcSin
#define c_f80asin				F80_ArcSin
#define c_f128asin				F128_ArcSin

#define Float_Sin_1				Float_ArcSin
#define Float_InvSine			Float_ArcSin
//!@}

//! Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atan}
*/
//!@{
#define							Float_ArcTan	CONCAT(FLOAT_TYPE,_ArcTan)
t_f32							F32_ArcTan(t_f32 x);
t_f64							F64_ArcTan(t_f64 x);
#ifdef __float80
t_f80							F80_ArcTan(t_f80 x);
#endif
#ifdef __float128
t_f128							F128_ArcTan(t_f128 x);
#endif
#define c_fatan					Float_ArcTan
#define c_f32atan				F32_ArcTan
#define c_f64atan				F64_ArcTan
#define c_f80atan				F80_ArcTan
#define c_f128atan				F128_ArcTan

#define Float_Tan_1				Float_ArcTan
#define Float_InvTangent		Float_ArcTan
//!@}



//! Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atan2}
*/
//!@{
#define								Float_ArcTan2	CONCAT(FLOAT_TYPE,_ArcTan2)
t_f32								F32_ArcTan2(t_f32 y, t_f32 x);
t_f64								F64_ArcTan2(t_f64 y, t_f64 x);
#ifdef __float80
t_f80								F80_ArcTan2(t_f80 y, t_f80 x);
#endif
#ifdef __float128
t_f128								F128_ArcTan2(t_f128 y, t_f128 x);
#endif
#define c_fatan2					Float_ArcTan2
#define c_f32atan2					F32_ArcTan2
#define c_f64atan2					F64_ArcTan2
#define c_f80atan2					F80_ArcTan2
#define c_f128atan2					F128_ArcTan2

#define Float_ArcTan_YoverX			Float_ArcTan2
#define Float_ArcTangent2			Float_ArcTan2
#define Float_ArcTangent_YoverX		Float_ArcTan2
//!@}



/*
** ************************************************************************** *|
**                           Hyperbolic Trigonometry                          *|
** ************************************************************************** *|
*/

//! Returns the hyperbolic cosine of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cosh}
*/
//!@{
#define								Float_CosH	CONCAT(FLOAT_TYPE,_CosH)
t_f32								F32_CosH(t_f32 x);
t_f64								F64_CosH(t_f64 x);
#ifdef __float80
t_f80								F80_CosH(t_f80 x);
#endif
#ifdef __float128
t_f128								F128_CosH(t_f128 x);
#endif
#define c_fcosh						Float_CosH
#define c_f32cosh					F32_CosH
#define c_f64cosh					F64_CosH
#define c_f80cosh					F80_CosH
#define c_f128cosh					F128_CosH

#define Float_Cos_H					Float_CosH
#define Float_Cosine_Hyperbolic		Float_CosH
//!@}

//! Returns the hyperbolic sine of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sinh}
*/
//!@{
#define								Float_SinH	CONCAT(FLOAT_TYPE,_SinH)
t_f32								F32_SinH(t_f32 x);
t_f64								F64_SinH(t_f64 x);
#ifdef __float80
t_f80								F80_SinH(t_f80 x);
#endif
#ifdef __float128
t_f128								F128_SinH(t_f128 x);
#endif
#define c_fsinh						Float_SinH
#define c_f32sinh					F32_SinH
#define c_f64sinh					F64_SinH
#define c_f80sinh					F80_SinH
#define c_f128sinh					F128_SinH

#define Float_Sin_H					Float_SinH
#define Float_Sine_Hyperbolic		Float_SinH
//!@}

//! Returns the hyperbolic tangent of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tanh}
*/
//!@{
#define								Float_TanH	CONCAT(FLOAT_TYPE,_TanH)
t_f32								F32_TanH(t_f32 x);
t_f64								F64_TanH(t_f64 x);
#ifdef __float80
t_f80								F80_TanH(t_f80 x);
#endif
#ifdef __float128
t_f128								F128_TanH(t_f128 x);
#endif
#define c_ftanh						Float_TanH
#define c_f32tanh					F32_TanH
#define c_f64tanh					F64_TanH
#define c_f80tanh					F80_TanH
#define c_f128tanh					F128_TanH

#define Float_Tan_H					Float_TanH
#define Float_Tangent_Hyperbolic	Float_TanH
//!@}



//! Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/acosh}
*/
//!@{
#define								Float_InvCosH	CONCAT(FLOAT_TYPE,_InvCosH)
t_f32								F32_InvCosH(t_f32 x);
t_f64								F64_InvCosH(t_f64 x);
#ifdef __float80
t_f80								F80_InvCosH(t_f80 x);
#endif
#ifdef __float128
t_f128								F128_InvCosH(t_f128 x);
#endif
#define c_facosh					Float_InvCosH
#define c_f32acosh					F32_InvCosH
#define c_f64acosh					F64_InvCosH
#define c_f80acosh					F80_InvCosH
#define c_f128acosh					F128_InvCosH

#define Float_Cos_1_H				Float_InvCosH
#define Float_InvCosine_Hyperbolic	Float_InvCosH
//!@}

//! Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/asinh}
*/
//!@{
#define								Float_InvSinH	CONCAT(FLOAT_TYPE,_InvSinH)
t_f32								F32_InvSinH(t_f32 x);
t_f64								F64_InvSinH(t_f64 x);
#ifdef __float80
t_f80								F80_InvSinH(t_f80 x);
#endif
#ifdef __float128
t_f128								F128_InvSinH(t_f128 x);
#endif
#define c_fasinh					Float_InvSinH
#define c_f32asinh					F32_InvSinH
#define c_f64asinh					F64_InvSinH
#define c_f80asinh					F80_InvSinH
#define c_f128asinh					F128_InvSinH

#define Float_Sin_1_H				Float_InvSinH
#define Float_InvSine_Hyperbolic	Float_InvSinH
//!@}

//! Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atanh}
*/
//!@{
#define								Float_InvTanH	CONCAT(FLOAT_TYPE,_InvTanH)
t_f32								F32_InvTanH(t_f32 x);
t_f64								F64_InvTanH(t_f64 x);
#ifdef __float80
t_f80								F80_InvTanH(t_f80 x);
#endif
#ifdef __float128
t_f128								F128_InvTanH(t_f128 x);
#endif
#define c_fatanh					Float_InvTanH
#define c_f32atanh					F32_InvTanH
#define c_f64atanh					F64_InvTanH
#define c_f80atanh					F80_InvTanH
#define c_f128atanh					F128_InvTanH

#define Float_Tan_1_H				Float_InvTanH
#define Float_InvTangent_Hyperbolic	Float_InvTanH
//!@}



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



/*! @} */
HEADER_END
#endif
