/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/float.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

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
**	NOTE: Not to be confused with #FLOAT_EPSILON - this "APPROX" value is configurable !
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
#define c_fabs				Float_Abs
#define Float_AbsoluteValue	Float_Abs

t_f32						F32_Abs(t_f32 x);
#define c_f32abs			F32_Abs

t_f64						F64_Abs(t_f64 x);
#define c_f64abs			F64_Abs

#ifdef __float80
t_f80						F80_Abs(t_f80 x);
#define c_f80abs			F80_Abs
#endif
#ifdef __float128
t_f128						F128_Abs(t_f128 x);
#define c_f128abs			F128_Abs
#endif
//!@}

//! Returns the value of `x`, rounded to the nearest integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/round}
*/
//!@{
#define						Float_Round	CONCAT(FLOAT_TYPE,_Round)
#define c_fround			Float_Round

t_f32						F32_Round(t_f32 x);
#define c_f32round			F32_Round

t_f64						F64_Round(t_f64 x);
#define c_f64round			F64_Round

#ifdef __float80
t_f80						F80_Round(t_f80 x);
#define c_f80round			F80_Round
#endif
#ifdef __float128
t_f128						F128_Round(t_f128 x);
#define c_f128round			F128_Round
#endif
//!@}

//! Returns the value of `x`, rounded towards 0
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/trunc}
*/
//!@{
#define						Float_Trunc	CONCAT(FLOAT_TYPE,_Trunc)
#define c_ftrunc			Float_Trunc
#define Float_Truncate		Float_Trunc

t_f32						F32_Trunc(t_f32 x);
#define c_f32trunc			F32_Trunc

t_f64						F64_Trunc(t_f64 x);
#define c_f64trunc			F64_Trunc

#ifdef __float80
t_f80						F80_Trunc(t_f80 x);
#define c_f80trunc			F80_Trunc
#endif
#ifdef __float128
t_f128						F128_Trunc(t_f128 x);
#define c_f128trunc			F128_Trunc
#endif

#define Float_Truncate		Float_Trunc
//!@}

//! Returns the value of `x`, rounded to the superior integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/floor}
*/
//!@{
#define						Float_Floor	CONCAT(FLOAT_TYPE,_Floor)
#define c_ffloor			Float_Floor

t_f32						F32_Floor(t_f32 x);
#define c_f32floor			F32_Floor

t_f64						F64_Floor(t_f64 x);
#define c_f64floor			F64_Floor

#ifdef __float80
t_f80						F80_Floor(t_f80 x);
#define c_f80floor			F80_Floor
#endif
#ifdef __float128
t_f128						F128_Floor(t_f128 x);
#define c_f128floor			F128_Floor
#endif
//!@}

//! Returns the value of `x`, rounded to the inferior integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/ceil}
*/
//!@{
#define						Float_Ceil	CONCAT(FLOAT_TYPE,_Ceil)
#define c_fceil				Float_Ceil
#define Float_Ceiling		Float_Ceil

t_f32						F32_Ceil(t_f32 x);
#define c_f32ceil			F32_Ceil

t_f64						F64_Ceil(t_f64 x);
#define c_f64ceil			F64_Ceil

#ifdef __float80
t_f80						F80_Ceil(t_f80 x);
#define c_f80ceil			F80_Ceil
#endif
#ifdef __float128
t_f128						F128_Ceil(t_f128 x);
#define c_f128ceil			F128_Ceil
#endif

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
#define c_fequ			Float_Equals

t_bool					F32_Equals(t_f32 x, t_f32 y);
#define c_f32equ		F32_Equals

t_bool					F64_Equals(t_f64 x, t_f64 y);
#define c_f64equ		F64_Equals

#ifdef	__float80
t_bool					F80_Equals(t_f80 x, t_f80 y);
#define c_f80equ		F80_Equals
#endif
#ifdef	__float128
t_bool					F128_Equals(t_f128 x, t_f128 y);
#define c_f128equ		F128_Equals
#endif
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
#define c_fequa			Float_EqualsApprox

t_bool					F32_EqualsApprox(t_f32 x, t_f32 y);
#define c_f32equa		F32_EqualsApprox

t_bool					F64_EqualsApprox(t_f64 x, t_f64 y);
#define c_f64equa		F64_EqualsApprox

#ifdef	__float80
t_bool					F80_EqualsApprox(t_f80 x, t_f80 y);
#define c_f80equa		F80_EqualsApprox
#endif
#ifdef	__float128
t_bool					F128_EqualsApprox(t_f128 x, t_f128 y);
#define c_f128equa		F128_EqualsApprox
#endif
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
#define c_fadd			Float_Add

t_f32					F32_Add(t_f32 x, t_f32 y);
#define c_f32add		F32_Add

t_f64					F64_Add(t_f64 x, t_f64 y);
#define c_f64add		F64_Add

#ifdef	__float80
t_f80					F80_Add(t_f80 x, t_f80 y);
#define c_f80add		F80_Add
#endif
#ifdef	__float128
t_f128					F128_Add(t_f128 x, t_f128 y);
#define c_f128add		F128_Add
#endif
//!@}



//! Performs a subtraction with the 2 given floating-point values (operator: `-`)
//!@{
#define					Float_Sub	CONCAT(FLOAT_TYPE,_Sub)
#define c_fsub			Float_Sub
#define Float_Subtract	Float_Sub

t_f32					F32_Sub(t_f32 x, t_f32 y);
#define c_f32sub		F32_Sub

t_f64					F64_Sub(t_f64 x, t_f64 y);
#define c_f64sub		F64_Sub

#ifdef	__float80
t_f80					F80_Sub(t_f80 x, t_f80 y);
#define c_f80sub		F80_Sub
#endif
#ifdef	__float128
t_f128					F128_Sub(t_f128 x, t_f128 y);
#define c_f128sub		F128_Sub
#endif
//!@}



//! Performs a multiplication with the 2 given floating-point values (operator: `*`)
//!@{
#define					Float_Mul	CONCAT(FLOAT_TYPE,_Mul)
#define c_fmul			Float_Mul
#define Float_Multiply	Float_Mul

t_f32					F32_Mul(t_f32 x, t_f32 y);
#define c_f32mul		F32_Mul

t_f64					F64_Mul(t_f64 x, t_f64 y);
#define c_f64mul		F64_Mul

#ifdef	__float80
t_f80					F80_Mul(t_f80 x, t_f80 y);
#define c_f80mul		F80_Mul
#endif
#ifdef	__float128
t_f128					F128_Mul(t_f128 x, t_f128 y);
#define c_f128mul		F128_Mul
#endif
//!@}



//! Performs a division with the 2 given floating-point values (operator: `/`)
//!@{
#define					Float_Div	CONCAT(FLOAT_TYPE,_Div)
#define c_fdiv			Float_Div
#define Float_Divide	Float_Div

t_f32					F32_Div(t_f32 x, t_f32 y);
#define c_f32div		F32_Div

t_f64					F64_Div(t_f64 x, t_f64 y);
#define c_f64div		F64_Div

#ifdef	__float80
t_f80					F80_Div(t_f80 x, t_f80 y);
#define c_f80div		F80_Div
#endif
#ifdef	__float128
t_f128					F128_Div(t_f128 x, t_f128 y);
#define c_f128div		F128_Div
#endif
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
#define c_fmod				Float_Mod
#define Float_Modulo		Float_Mod

t_f32						F32_Mod(t_f32 x, t_f32 y);
#define c_f32mod			F32_Mod

t_f64						F64_Mod(t_f64 x, t_f64 y);
#define c_f64mod			F64_Mod

#ifdef __float80
t_f80						F80_Mod(t_f80 x, t_f80 y);
#define c_f80mod			F80_Mod
#endif
#ifdef __float128
t_f128						F128_Mod(t_f128 x, t_f128 y);
#define c_f128mod			F128_Mod
#endif
//!@}



//! Returns the value of `x` to the power of `y` (float)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/pow}
*/
//!@{
#define						Float_Pow	CONCAT(FLOAT_TYPE,_Pow)
#define c_fpow				Float_Pow
#define Float_Power			Float_Pow

t_f32						F32_Pow(t_f32 x, t_f32 y);
#define c_f32pow			F32_Pow

t_f64						F64_Pow(t_f64 x, t_f64 y);
#define c_f64pow			F64_Pow

#ifdef __float80
t_f80						F80_Pow(t_f80 x, t_f80 y);
#define c_f80pow			F80_Pow
#endif
#ifdef __float128
t_f128						F128_Pow(t_f128 x, t_f128 y);
#define c_f128pow			F128_Pow
#endif
//!@}

//! Returns the value of `x` to the power of `n` (integer)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/pow}
*/
//!@{
#define						Float_IntPow	CONCAT(FLOAT_TYPE,_IntPow)
#define c_fintpow			Float_IntPow
#define Float_IntPower		Float_IntPow

t_f32						F32_IntPow(t_f32 x, t_sint n);
#define c_f32intpow			F32_IntPow

t_f64						F64_IntPow(t_f64 x, t_sint n);
#define c_f64intpow			F64_IntPow

#ifdef __float80
t_f80						F80_IntPow(t_f80 x, t_sint n);
#define c_f80intpow			F80_IntPow
#endif
#ifdef __float128
t_f128						F128_IntPow(t_f128 x, t_sint n);
#define c_f128intpow		F128_IntPow
#endif
//!@}



//! Returns the square root of `x` (inverse of power of 2)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sqrt}
*/
//!@{
#define						Float_Root2	CONCAT(FLOAT_TYPE,_Root2)
#define c_fsqrt				Float_Root2
#define Float_SqRt			Float_Root2
#define Float_SquareRoot	Float_Root2

t_f32						F32_Root2(t_f32 x);
#define c_f32sqrt			F32_Root2

t_f64						F64_Root2(t_f64 x);
#define c_f64sqrt			F64_Root2

#ifdef __float80
t_f80						F80_Root2(t_f80 x);
#define c_f80sqrt			F80_Root2
#endif
#ifdef __float128
t_f128						F128_Root2(t_f128 x);
#define c_f128sqrt			F128_Root2
#endif
//!@}

//! Returns the cubic root of `x` (inverse of power of 3)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cbrt}
*/
//!@{
#define						Float_Root3	CONCAT(FLOAT_TYPE,_Root3)
#define c_fcbrt				Float_Root3
#define Float_CbRt			Float_Root3
#define Float_CubeRoot		Float_Root3

t_f32						F32_Root3(t_f32 x);
#define c_f32cbrt			F32_Root3

t_f64						F64_Root3(t_f64 x);
#define c_f64cbrt			F64_Root3

#ifdef __float80
t_f80						F80_Root3(t_f80 x);
#define c_f80cbrt			F80_Root3
#endif
#ifdef __float128
t_f128						F128_Root3(t_f128 x);
#define c_f128cbrt			F128_Root3
#endif
//!@}

//! Returns the n-ic root of `x` (inverse of power of `n`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/nrt}
*/
//!@{
#define						Float_RootN	CONCAT(FLOAT_TYPE,_RootN)
#define c_fnrt				Float_RootN
#define Float_NRt			Float_RootN
#define Float_NRoot			Float_RootN

t_f32						F32_RootN(t_f32 x, t_u8 n);
#define c_f32nrt			F32_RootN

t_f64						F64_RootN(t_f64 x, t_u8 n);
#define c_f64nrt			F64_RootN

#ifdef __float80
t_f80						F80_RootN(t_f80 x, t_u8 n);
#define c_f80nrt			F80_RootN
#endif
#ifdef __float128
t_f128						F128_RootN(t_f128 x, t_u8 n);
#define c_f128nrt			F128_RootN
#endif
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
#define c_fexp					Float_Exp
#define Float_Exponential		Float_Exp

t_f32							F32_Exp(t_f32 x);
#define c_f32exp				F32_Exp

t_f64							F64_Exp(t_f64 x);
#define c_f64exp				F64_Exp

#ifdef __float80
t_f80							F80_Exp(t_f80 x);
#define c_f80exp				F80_Exp
#endif
#ifdef __float128
t_f128							F128_Exp(t_f128 x);
#define c_f128exp				F128_Exp
#endif
//!@}

//! Returns the natural logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log}
*/
//!@{
#define							Float_Ln	CONCAT(FLOAT_TYPE,_Ln)
#define c_fln					Float_Ln
#define Float_NaturalLogarithm	Float_Ln

t_f32							F32_Ln(t_f32 x);
#define c_f32ln					F32_Ln

t_f64							F64_Ln(t_f64 x);
#define c_f64ln					F64_Ln

#ifdef __float80
t_f80							F80_Ln(t_f80 x);
#define c_f80ln					F80_Ln
#endif
#ifdef __float128
t_f128							F128_Ln(t_f128 x);
#define c_f128ln				F128_Ln
#endif
//!@}

//! Returns the binary (base-2) logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log2}
*/
//!@{
#define							Float_Log2	CONCAT(FLOAT_TYPE,_Log2)
#define c_flg					Float_Log2
#define c_flog2					Float_Log2
#define Float_Logarithm_Base2	Float_Log2

t_f32							F32_Log2(t_f32 x);
#define c_f32lg					F32_Log2
#define c_f32log2				F32_Log2

t_f64							F64_Log2(t_f64 x);
#define c_f64lg					F64_Log2
#define c_f64log2				F64_Log2

#ifdef __float80
t_f80							F80_Log2(t_f80 x);
#define c_f80lg					F80_Log2
#define c_f80log2				F80_Log2
#endif
#ifdef __float128
t_f128							F128_Log2(t_f128 x);
#define c_f128lg				F128_Log2
#define c_f128log2				F128_Log2
#endif
//!@}

//! Returns the decimal (base-10) logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log10}
*/
//!@{
#define							Float_Log10	CONCAT(FLOAT_TYPE,_Log10)
#define c_flog					Float_Log10
#define c_flog10				Float_Log10
#define Float_Logarithm_Base10	Float_Log10

t_f32							F32_Log10(t_f32 x);
#define c_f32log				F32_Log10
#define c_f32log10				F32_Log10

t_f64							F64_Log10(t_f64 x);
#define c_f64log				F64_Log10
#define c_f64log10				F64_Log10

#ifdef __float80
t_f80							F80_Log10(t_f80 x);
#define c_f80log				F80_Log10
#define c_f80log10				F80_Log10
#endif
#ifdef __float128
t_f128							F128_Log10(t_f128 x);
#define c_f128log				F128_Log10
#define c_f128log10				F128_Log10
#endif
//!@}

//! Returns the base-`n` logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Float_LogN	CONCAT(FLOAT_TYPE,_LogN)
#define c_flogn					Float_LogN
#define Float_Logarithm_BaseN	Float_LogN

t_f32							F32_LogN(t_f32 x, t_f32 n);
#define c_f32logn				F32_LogN

t_f64							F64_LogN(t_f64 x, t_f64 n);
#define c_f64logn				F64_LogN

#ifdef __float80
t_f80							F80_LogN(t_f80 x, t_f80 n);
#define c_f80logn				F80_LogN
#endif
#ifdef __float128
t_f128							F128_LogN(t_f128 x, t_f128 n);
#define c_f128logn				F128_LogN
#endif
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
#define c_fcos				Float_Cos
#define Float_Cosine		Float_Cos

t_f32						F32_Cos(t_f32 x);
#define c_f32cos			F32_Cos

t_f64						F64_Cos(t_f64 x);
#define c_f64cos			F64_Cos

#ifdef __float80
t_f80						F80_Cos(t_f80 x);
#define c_f80cos			F80_Cos
#endif
#ifdef __float128
t_f128						F128_Cos(t_f128 x);
#define c_f128cos			F128_Cos
#endif
//!@}

//! Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sin}
*/
//!@{
#define						Float_Sin	CONCAT(FLOAT_TYPE,_Sin)
#define c_fsin				Float_Sin
#define Float_Sine			Float_Sin

t_f32						F32_Sin(t_f32 x);
#define c_f32sin			F32_Sin

t_f64						F64_Sin(t_f64 x);
#define c_f64sin			F64_Sin

#ifdef __float80
t_f80						F80_Sin(t_f80 x);
#define c_f80sin			F80_Sin
#endif
#ifdef __float128
t_f128						F128_Sin(t_f128 x);
#define c_f128sin			F128_Sin
#endif
//!@}

//! Returns the tangent of `x` (trigonometry tangent line)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tan}
*/
//!@{
#define						Float_Tan	CONCAT(FLOAT_TYPE,_Tan)
#define c_ftan				Float_Tan
#define Float_Tangent		Float_Tan

t_f32						F32_Tan(t_f32 x);
#define c_f32tan			F32_Tan

t_f64						F64_Tan(t_f64 x);
#define c_f64tan			F64_Tan

#ifdef __float80
t_f80						F80_Tan(t_f80 x);
#define c_f80tan			F80_Tan
#endif
#ifdef __float128
t_f128						F128_Tan(t_f128 x);
#define c_f128tan			F128_Tan
#endif
//!@}



//! Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/acos}
*/
//!@{
#define							Float_ArcCos	CONCAT(FLOAT_TYPE,_ArcCos)
#define c_facos					Float_ArcCos
#define Float_Cos_1				Float_ArcCos
#define Float_InvCosine			Float_ArcCos

t_f32							F32_ArcCos(t_f32 x);
#define c_f32acos				F32_ArcCos

t_f64							F64_ArcCos(t_f64 x);
#define c_f64acos				F64_ArcCos

#ifdef __float80
t_f80							F80_ArcCos(t_f80 x);
#define c_f80acos				F80_ArcCos
#endif
#ifdef __float128
t_f128							F128_ArcCos(t_f128 x);
#define c_f128acos				F128_ArcCos
#endif
//!@}

//! Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/asin}
*/
//!@{
#define							Float_ArcSin	CONCAT(FLOAT_TYPE,_ArcSin)
#define c_fasin					Float_ArcSin
#define Float_Sin_1				Float_ArcSin
#define Float_InvSine			Float_ArcSin

t_f32							F32_ArcSin(t_f32 x);
#define c_f32asin				F32_ArcSin

t_f64							F64_ArcSin(t_f64 x);
#define c_f64asin				F64_ArcSin

#ifdef __float80
t_f80							F80_ArcSin(t_f80 x);
#define c_f80asin				F80_ArcSin
#endif
#ifdef __float128
t_f128							F128_ArcSin(t_f128 x);
#define c_f128asin				F128_ArcSin
#endif
//!@}

//! Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atan}
*/
//!@{
#define							Float_ArcTan	CONCAT(FLOAT_TYPE,_ArcTan)
#define c_fatan					Float_ArcTan
#define Float_Tan_1				Float_ArcTan
#define Float_InvTangent		Float_ArcTan

t_f32							F32_ArcTan(t_f32 x);
#define c_f32atan				F32_ArcTan

t_f64							F64_ArcTan(t_f64 x);
#define c_f64atan				F64_ArcTan

#ifdef __float80
t_f80							F80_ArcTan(t_f80 x);
#define c_f80atan				F80_ArcTan
#endif
#ifdef __float128
t_f128							F128_ArcTan(t_f128 x);
#define c_f128atan				F128_ArcTan
#endif
//!@}



//! Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atan2}
*/
//!@{
#define								Float_ArcTan2	CONCAT(FLOAT_TYPE,_ArcTan2)
#define c_fatan2					Float_ArcTan2
#define Float_ArcTan_YoverX			Float_ArcTan2
#define Float_ArcTangent2			Float_ArcTan2
#define Float_ArcTangent_YoverX		Float_ArcTan2

t_f32								F32_ArcTan2(t_f32 y, t_f32 x);
#define c_f32atan2					F32_ArcTan2

t_f64								F64_ArcTan2(t_f64 y, t_f64 x);
#define c_f64atan2					F64_ArcTan2

#ifdef __float80
t_f80								F80_ArcTan2(t_f80 y, t_f80 x);
#define c_f80atan2					F80_ArcTan2
#endif
#ifdef __float128
t_f128								F128_ArcTan2(t_f128 y, t_f128 x);
#define c_f128atan2					F128_ArcTan2
#endif
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
#define c_fcosh						Float_CosH
#define Float_Cos_H					Float_CosH
#define Float_Cosine_Hyperbolic		Float_CosH

t_f32								F32_CosH(t_f32 x);
#define c_f32cosh					F32_CosH

t_f64								F64_CosH(t_f64 x);
#define c_f64cosh					F64_CosH

#ifdef __float80
t_f80								F80_CosH(t_f80 x);
#define c_f80cosh					F80_CosH
#endif
#ifdef __float128
t_f128								F128_CosH(t_f128 x);
#define c_f128cosh					F128_CosH
#endif
//!@}

//! Returns the hyperbolic sine of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sinh}
*/
//!@{
#define								Float_SinH	CONCAT(FLOAT_TYPE,_SinH)
#define c_fsinh						Float_SinH
#define Float_Sin_H					Float_SinH
#define Float_Sine_Hyperbolic		Float_SinH

t_f32								F32_SinH(t_f32 x);
#define c_f32sinh					F32_SinH

t_f64								F64_SinH(t_f64 x);
#define c_f64sinh					F64_SinH

#ifdef __float80
t_f80								F80_SinH(t_f80 x);
#define c_f80sinh					F80_SinH
#endif
#ifdef __float128
t_f128								F128_SinH(t_f128 x);
#define c_f128sinh					F128_SinH
#endif
//!@}

//! Returns the hyperbolic tangent of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tanh}
*/
//!@{
#define								Float_TanH	CONCAT(FLOAT_TYPE,_TanH)
#define c_ftanh						Float_TanH
#define Float_Tan_H					Float_TanH
#define Float_Tangent_Hyperbolic	Float_TanH

t_f32								F32_TanH(t_f32 x);
#define c_f32tanh					F32_TanH

t_f64								F64_TanH(t_f64 x);
#define c_f64tanh					F64_TanH

#ifdef __float80
t_f80								F80_TanH(t_f80 x);
#define c_f80tanh					F80_TanH
#endif
#ifdef __float128
t_f128								F128_TanH(t_f128 x);
#define c_f128tanh					F128_TanH
#endif
//!@}



//! Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/acosh}
*/
//!@{
#define								Float_InvCosH	CONCAT(FLOAT_TYPE,_InvCosH)
#define c_facosh					Float_InvCosH
#define Float_Cos_1_H				Float_InvCosH
#define Float_InvCosine_Hyperbolic	Float_InvCosH

t_f32								F32_InvCosH(t_f32 x);
#define c_f32acosh					F32_InvCosH

t_f64								F64_InvCosH(t_f64 x);
#define c_f64acosh					F64_InvCosH

#ifdef __float80
t_f80								F80_InvCosH(t_f80 x);
#define c_f80acosh					F80_InvCosH
#endif
#ifdef __float128
t_f128								F128_InvCosH(t_f128 x);
#define c_f128acosh					F128_InvCosH
#endif
//!@}

//! Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/asinh}
*/
//!@{
#define								Float_InvSinH	CONCAT(FLOAT_TYPE,_InvSinH)
#define c_fasinh					Float_InvSinH
#define Float_Sin_1_H				Float_InvSinH
#define Float_InvSine_Hyperbolic	Float_InvSinH

t_f32								F32_InvSinH(t_f32 x);
#define c_f32asinh					F32_InvSinH

t_f64								F64_InvSinH(t_f64 x);
#define c_f64asinh					F64_InvSinH

#ifdef __float80
t_f80								F80_InvSinH(t_f80 x);
#define c_f80asinh					F80_InvSinH
#endif
#ifdef __float128
t_f128								F128_InvSinH(t_f128 x);
#define c_f128asinh					F128_InvSinH
#endif
//!@}

//! Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atanh}
*/
//!@{
#define								Float_InvTanH	CONCAT(FLOAT_TYPE,_InvTanH)
#define c_fatanh					Float_InvTanH
#define Float_Tan_1_H				Float_InvTanH
#define Float_InvTangent_Hyperbolic	Float_InvTanH

t_f32								F32_InvTanH(t_f32 x);
#define c_f32atanh					F32_InvTanH

t_f64								F64_InvTanH(t_f64 x);
#define c_f64atanh					F64_InvTanH

#ifdef __float80
t_f80								F80_InvTanH(t_f80 x);
#define c_f80atanh					F80_InvTanH
#endif
#ifdef __float128
t_f128								F128_InvTanH(t_f128 x);
#define c_f128atanh					F128_InvTanH
#endif
//!@}



// TODO hypot ?
// TODO lgamma ?
// TODO tgamma ?



/*! @} */
HEADER_END
#endif
