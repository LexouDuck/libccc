/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/fixed.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_FIXED_H
#define __LIBCCC_MATH_FIXED_H
/*!@group{libccc_math_fixed,52,libccc/math/fixed.h}
**
**	This header defines the common standard math functions for fixed-point numbers.
**
**	@nonstd
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/fixed.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/



//!@doc The type of function which takes one number and outputs one number
//!@{
typedef	t_q8	(*f_q8_function)	(t_q8    x);
typedef	t_q16	(*f_q16_function)	(t_q16   x);
typedef	t_q32	(*f_q32_function)	(t_q32   x);
typedef	t_q64	(*f_q64_function)	(t_q64   x);
#if LIBCONFIG_USE_INT128
typedef	t_q128	(*f_q128_function)	(t_q128  x);
#endif
typedef	t_fixed	(*f_fixed_function)	(t_fixed x);
//!@}

//!@doc The type of function which takes two numbers and outputs one number
//!@{
typedef	t_q8	(*f_q8_operator)	(t_q8    x, t_q8    y);
typedef	t_q16	(*f_q16_operator)	(t_q16   x, t_q16   y);
typedef	t_q32	(*f_q32_operator)	(t_q32   x, t_q32   y);
typedef	t_q64	(*f_q64_operator)	(t_q64   x, t_q64   y);
#if LIBCONFIG_USE_INT128
typedef	t_q128	(*f_q128_operator)	(t_q128  x, t_q128  y);
#endif
typedef	t_fixed	(*f_fixed_operator)	(t_fixed x,	t_fixed y);
//!@}

//!@doc The type of function which relates two numbers to each other
//!@{
typedef	t_bool	(*f_q8_relation)	(t_q8    x, t_q8    y);
typedef	t_bool	(*f_q16_relation)	(t_q16   x, t_q16   y);
typedef	t_bool	(*f_q32_relation)	(t_q32   x, t_q32   y);
typedef	t_bool	(*f_q64_relation)	(t_q64   x, t_q64   y);
#if LIBCONFIG_USE_INT128
typedef	t_bool	(*f_q128_relation)	(t_q128  x, t_q128  y);
#endif
typedef	t_bool	(*f_fixed_relation)	(t_fixed x,	t_fixed y);
//!@}



/*============================================================================*\
||                           Basic Arithmetic Operations                      ||
\*============================================================================*/

//!@doc Returns the absolute value of `x` (makes `x` positive)
/*!
**	@nonstd
*/
//!@{
#define						Fixed_Abs	CONCAT(FIXED_TYPE,_Abs)
#define c_qabs				Fixed_Abs
#define Fixed_AbsoluteValue	Fixed_Abs

t_q8						Q8_Abs(t_q8 x);
#define c_q8abs				Q8_Abs

t_q16						Q16_Abs(t_q16 x);
#define c_q16abs			Q16_Abs

t_q32						Q32_Abs(t_q32 x);
#define c_q32abs			Q32_Abs

t_q64						Q64_Abs(t_q64 x);
#define c_q64abs			Q64_Abs

#if LIBCONFIG_USE_INT128
t_q128						Q128_Abs(t_q128 x);
#define c_q128abs			Q128_Abs
#endif
//!@}

//!@doc Returns the sign value value of `x` (either `-1`, `0`, or `+1`)
/*!
**	@isostd{C11,https://en.cppreference.com/w/c/numeric/math/signbit}
*/
//!@{
#define						Fixed_Sgn	CONCAT(FIXED_TYPE,_Sgn)
#define c_qsgn				Fixed_Sgn
#define Fixed_Sign			Fixed_Sgn
#define Fixed_SignOf		Fixed_Sgn

t_q8						Q8_Sgn(t_q8 x);
#define c_q8sgn				Q8_Sgn

t_q16						Q16_Sgn(t_q16 x);
#define c_q16sgn			Q16_Sgn

t_q32						Q32_Sgn(t_q32 x);
#define c_q32sgn			Q32_Sgn

t_q64						Q64_Sgn(t_q64 x);
#define c_q64sgn			Q64_Sgn

#if LIBCONFIG_USE_INT128
t_q128						Q128_Sgn(t_q128 x);
#define c_q128sgn			Q128_Sgn
#endif
//!@}



/*============================================================================*\
||                           Basic kind-check functions                       ||
\*============================================================================*/



//!@doc Returns `TRUE` if the given number is NAN (not a number) (only useful when #LIBCONFIG_FIXED_NAN is active).
/*!
**	@nonstd
*/
//!@{
#define						Fixed_IsNaN	CONCAT(FIXED_TYPE,_IsNaN)
#define c_qisnan			Fixed_IsNaN

t_bool						Q8_IsNaN(t_q8 a);
#define c_q8isnan			Q8_IsNaN

t_bool						Q16_IsNaN(t_q16 a);
#define c_q16isnan			Q16_IsNaN

t_bool						Q32_IsNaN(t_q32 a);
#define c_q32isnan			Q32_IsNaN

t_bool						Q64_IsNaN(t_q64 a);
#define c_q64isnan			Q64_IsNaN

#if LIBCONFIG_USE_INT128
t_bool						Q128_IsNaN(t_q128 a);
#define c_q128isnan			Q128_IsNaN
#endif
//!@}



//!@doc Returns `TRUE` if the given number is infinite (only useful when #LIBCONFIG_FIXED_INF is active).
/*!
**	@nonstd
*/
//!@{
#define						Fixed_IsInf	CONCAT(FIXED_TYPE,_IsInf)
#define c_qisinf			Fixed_IsInf

t_bool						Q8_IsInf(t_q8 a);
#define c_q8isinf			Q8_IsInf

t_bool						Q16_IsInf(t_q16 a);
#define c_q16isinf			Q16_IsInf

t_bool						Q32_IsInf(t_q32 a);
#define c_q32isinf			Q32_IsInf

t_bool						Q64_IsInf(t_q64 a);
#define c_q64isinf			Q64_IsInf

#if LIBCONFIG_USE_INT128
t_bool						Q128_IsInf(t_q128 a);
#define c_q128isinf			Q128_IsInf
#endif
//!@}



//!@doc Returns `TRUE` if the given number is a prime number.
/*!
**	@nonstd
*/
//!@{
#define						Fixed_IsPrime	CONCAT(FIXED_TYPE,_IsPrime)
#define c_qisprime			Fixed_IsPrime

t_bool						Q8_IsPrime(t_q8 a);
#define c_q8isprime			Q8_IsPrime

t_bool						Q16_IsPrime(t_q16 a);
#define c_q16isprime		Q16_IsPrime

t_bool						Q32_IsPrime(t_q32 a);
#define c_q32isprime		Q32_IsPrime

t_bool						Q64_IsPrime(t_q64 a);
#define c_q64isprime		Q64_IsPrime

#if LIBCONFIG_USE_INT128
t_bool						Q128_IsPrime(t_q128 a);
#define c_q128isprime		Q128_IsPrime
#endif
//!@}



/*============================================================================*\
||                            Fixed-point Functions                           ||
\*============================================================================*/

//!@doc Returns the value of `x`, rounded to the nearest integer
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Round	CONCAT(FIXED_TYPE,_Round)
#define c_qround		Fixed_Round

t_q8					Q8_Round(t_q8 x);
#define c_q8round		Q8_Round

t_q16					Q16_Round(t_q16 x);
#define c_q16round		Q16_Round

t_q32					Q32_Round(t_q32 x);
#define c_q32round		Q32_Round

t_q64					Q64_Round(t_q64 x);
#define c_q64round		Q64_Round

#if LIBCONFIG_USE_INT128
t_q128					Q128_Round(t_q128 x);
#define c_q128round		Q128_Round
#endif
//!@}

//!@doc Returns the value of `x`, rounded towards 0
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Trunc	CONCAT(FIXED_TYPE,_Trunc)
#define c_qtrunc		Fixed_Trunc
#define Fixed_Truncate	Fixed_Trunc

t_q8					Q8_Trunc(t_q8 x);
#define c_q8trunc		Q8_Trunc

t_q16					Q16_Trunc(t_q16 x);
#define c_q16trunc		Q16_Trunc

t_q32					Q32_Trunc(t_q32 x);
#define c_q32trunc		Q32_Trunc

t_q64					Q64_Trunc(t_q64 x);
#define c_q64trunc		Q64_Trunc

#if LIBCONFIG_USE_INT128
t_q128					Q128_Trunc(t_q128 x);
#define c_q128trunc		Q128_Trunc
#endif
//!@}

//!@doc Returns the value of `x`, rounded to the superior integer
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Floor	CONCAT(FIXED_TYPE,_Floor)
#define c_qfloor		Fixed_Floor

t_q8					Q8_Floor(t_q8 x);
#define c_q8floor		Q8_Floor

t_q16					Q16_Floor(t_q16 x);
#define c_q16floor		Q16_Floor

t_q32					Q32_Floor(t_q32 x);
#define c_q32floor		Q32_Floor

t_q64					Q64_Floor(t_q64 x);
#define c_q64floor		Q64_Floor

#if LIBCONFIG_USE_INT128
t_q128					Q128_Floor(t_q128 x);
#define c_q128floor		Q128_Floor
#endif
//!@}

//!@doc Returns the value of `x`, rounded to the inferior integer
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Ceil	CONCAT(FIXED_TYPE,_Ceil)
#define c_qceil			Fixed_Ceil
#define Fixed_Ceiling	Fixed_Ceil

t_q8					Q8_Ceil(t_q8 x);
#define c_q8ceil		Q8_Ceil

t_q16					Q16_Ceil(t_q16 x);
#define c_q16ceil		Q16_Ceil

t_q32					Q32_Ceil(t_q32 x);
#define c_q32ceil		Q32_Ceil

t_q64					Q64_Ceil(t_q64 x);
#define c_q64ceil		Q64_Ceil

#if LIBCONFIG_USE_INT128
t_q128					Q128_Ceil(t_q128 x);
#define c_q128ceil		Q128_Ceil
#endif
//!@}



/*============================================================================*\
||                            Comparison operators                            ||
\*============================================================================*/

//!@doc Returns `TRUE` if the 2 given fixed-point values are exactly equal (operator: `==`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (exact) equality
**	@param	y	The second value to check for (exact) equality
**	@returns
**	`TRUE` if the 2 given fixed-point values are exactly equal,
**	otherwise `FALSE`.
*/
//!@{
#define					Fixed_Equals	CONCAT(FIXED_TYPE,_Equals)
#define c_qequ			Fixed_Equals

t_bool					Q8_Equals(t_q8 x, t_q8 y);
#define c_q8equ			Q8_Equals

t_bool					Q16_Equals(t_q16 x, t_q16 y);
#define c_q16equ		Q16_Equals

t_bool					Q32_Equals(t_q32 x, t_q32 y);
#define c_q32equ		Q32_Equals

t_bool					Q64_Equals(t_q64 x, t_q64 y);
#define c_q64equ		Q64_Equals

#if LIBCONFIG_USE_INT128
t_bool					Q128_Equals(t_q128 x, t_q128 y);
#define c_q128equ		Q128_Equals
#endif
//!@}

//!@doc Returns `TRUE` if the 2 given fixed-point values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (approximate) equality
**	@param	y	The second value to check for (approximate) equality
**	@param	approx	The tolerance margin for the approximate equality check
**	@returns
**	`TRUE` if the 2 given fixed-point values are close enough to be considered equal
**	(using #FIXED_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					Fixed_EqualsApprox	CONCAT(FIXED_TYPE,_EqualsApprox)
#define c_qequa			Fixed_EqualsApprox

t_bool					Q8_EqualsApprox(t_q8 x, t_q8 y, t_q8 approx);
#define c_q8equa		Q8_EqualsApprox

t_bool					Q16_EqualsApprox(t_q16 x, t_q16 y, t_q16 approx);
#define c_q16equa		Q16_EqualsApprox

t_bool					Q32_EqualsApprox(t_q32 x, t_q32 y, t_q32 approx);
#define c_q32equa		Q32_EqualsApprox

t_bool					Q64_EqualsApprox(t_q64 x, t_q64 y, t_q64 approx);
#define c_q64equa		Q64_EqualsApprox

#if LIBCONFIG_USE_INT128
t_bool					Q128_EqualsApprox(t_q128 x, t_q128 y, t_q128 approx);
#define c_q128equa		Q128_EqualsApprox
#endif
//!@}



//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value (operator: `<`)
//!@{
#define					Fixed_LessThan	CONCAT(FIXED_TYPE,_LessThan)
#define c_qlt			Fixed_LessThan

t_bool					Q8_LessThan(t_q8 x, t_q8 y);
#define c_q8lt			Q8_LessThan

t_bool					Q16_LessThan(t_q16 x, t_q16 y);
#define c_q16lt			Q16_LessThan

t_bool					Q32_LessThan(t_q32 x, t_q32 y);
#define c_q32lt			Q32_LessThan

t_bool					Q64_LessThan(t_q64 x, t_q64 y);
#define c_q64lt			Q64_LessThan

#if LIBCONFIG_USE_INT128
t_bool					Q128_LessThan(t_q128 x, t_q128 y);
#define c_q128lt		Q128_LessThan
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value or equal to it (operator: `<=`)
//!@{
#define					Fixed_LessThanOrEqual	CONCAT(FIXED_TYPE,_LessThanOrEqual)
#define c_qlte			Fixed_LessThanOrEqual

t_bool					Q8_LessThanOrEqual(t_q8 x, t_q8 y);
#define c_q8lte			Q8_LessThanOrEqual

t_bool					Q16_LessThanOrEqual(t_q16 x, t_q16 y);
#define c_q16lte		Q16_LessThanOrEqual

t_bool					Q32_LessThanOrEqual(t_q32 x, t_q32 y);
#define c_q32lte		Q32_LessThanOrEqual

t_bool					Q64_LessThanOrEqual(t_q64 x, t_q64 y);
#define c_q64lte		Q64_LessThanOrEqual

#if LIBCONFIG_USE_INT128
t_bool					Q128_LessThanOrEqual(t_q128 x, t_q128 y);
#define c_q128lte		Q128_LessThanOrEqual
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value (operator: `>`)
//!@{
#define					Fixed_GreaterThan	CONCAT(FIXED_TYPE,_GreaterThan)
#define c_qgt			Fixed_GreaterThan

t_bool					Q8_GreaterThan(t_q8 x, t_q8 y);
#define c_q8gt			Q8_GreaterThan

t_bool					Q16_GreaterThan(t_q16 x, t_q16 y);
#define c_q16gt			Q16_GreaterThan

t_bool					Q32_GreaterThan(t_q32 x, t_q32 y);
#define c_q32gt			Q32_GreaterThan

t_bool					Q64_GreaterThan(t_q64 x, t_q64 y);
#define c_q64gt			Q64_GreaterThan

#if LIBCONFIG_USE_INT128
t_bool					Q128_GreaterThan(t_q128 x, t_q128 y);
#define c_q128gt		Q128_GreaterThan
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value or equal to it (operator: `>=`)
//!@{
#define					Fixed_GreaterThanOrEqual	CONCAT(FIXED_TYPE,_GreaterThanOrEqual)
#define c_qgte			Fixed_GreaterThanOrEqual

t_bool					Q8_GreaterThanOrEqual(t_q8 x, t_q8 y);
#define c_q8gte			Q8_GreaterThanOrEqual

t_bool					Q16_GreaterThanOrEqual(t_q16 x, t_q16 y);
#define c_q16gte		Q16_GreaterThanOrEqual

t_bool					Q32_GreaterThanOrEqual(t_q32 x, t_q32 y);
#define c_q32gte		Q32_GreaterThanOrEqual

t_bool					Q64_GreaterThanOrEqual(t_q64 x, t_q64 y);
#define c_q64gte		Q64_GreaterThanOrEqual

#if LIBCONFIG_USE_INT128
t_bool					Q128_GreaterThanOrEqual(t_q128 x, t_q128 y);
#define c_q128gte		Q128_GreaterThanOrEqual
#endif
//!@}



//!@doc Returns the smaller of the two given numbers `x` and `y`
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Min	CONCAT(QINT_TYPE,_Min)
#define c_qmin			Fixed_Min
#define Fixed_Minimum	Fixed_Min

t_q8					Q8_Min(t_q8 x, t_q8 y);
#define c_q8min			Q8_Min

t_q16					Q16_Min(t_q16 x, t_q16 y);
#define c_q16min		Q16_Min

t_q32					Q32_Min(t_q32 x, t_q32 y);
#define c_q32min		Q32_Min

t_q64					Q64_Min(t_q64 x, t_q64 y);
#define c_q64min		Q64_Min

#if LIBCONFIG_USE_INT128
t_q128					Q128_Min(t_q128 x, t_q128 y);
#define c_q128min		Q128_Min
#endif
//!@}

//!@doc Returns the larger of the two given numbers `x` and `y`
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Max	CONCAT(QINT_TYPE,_Max)
#define c_qmax			Fixed_Max
#define Fixed_Maximum	Fixed_Max

t_q8					Q8_Max(t_q8 x, t_q8 y);
#define c_q8max			Q8_Max

t_q16					Q16_Max(t_q16 x, t_q16 y);
#define c_q16max		Q16_Max

t_q32					Q32_Max(t_q32 x, t_q32 y);
#define c_q32max		Q32_Max

t_q64					Q64_Max(t_q64 x, t_q64 y);
#define c_q64max		Q64_Max

#if LIBCONFIG_USE_INT128
t_q128					Q128_Max(t_q128 x, t_q128 y);
#define c_q128max		Q128_Max
#endif
//!@}



/*============================================================================*\
||                          Fixed-point math operators                        ||
\*============================================================================*/



//!@doc Performs an addition between the 2 given fixed-point values (operator: `+`)
//!@{
#define					Fixed_Add	CONCAT(FIXED_TYPE,_Add)
#define c_qadd			Fixed_Add

t_q8					Q8_Add(t_q8 x, t_q8 y);
#define c_q8add			Q8_Add

t_q16					Q16_Add(t_q16 x, t_q16 y);
#define c_q16add		Q16_Add

t_q32					Q32_Add(t_q32 x, t_q32 y);
#define c_q32add		Q32_Add

t_q64					Q64_Add(t_q64 x, t_q64 y);
#define c_q64add		Q64_Add

#if LIBCONFIG_USE_INT128
t_q128					Q128_Add(t_q128 x, t_q128 y);
#define c_q128add		Q128_Add
#endif
//!@}



//!@doc Performs an addition between the 2 given fixed-point values (operator: `-`)
//!@{
#define					Fixed_Sub	CONCAT(FIXED_TYPE,_Sub)
#define c_qsub			Fixed_Sub
#define Fixed_Subtract	Fixed_Sub

t_q8					Q8_Sub(t_q8 x, t_q8 y);
#define c_q8sub			Q8_Sub

t_q16					Q16_Sub(t_q16 x, t_q16 y);
#define c_q16sub		Q16_Sub

t_q32					Q32_Sub(t_q32 x, t_q32 y);
#define c_q32sub		Q32_Sub

t_q64					Q64_Sub(t_q64 x, t_q64 y);
#define c_q64sub		Q64_Sub

#if LIBCONFIG_USE_INT128
t_q128					Q128_Sub(t_q128 x, t_q128 y);
#define c_q128sub		Q128_Sub
#endif
//!@}



//!@doc Performs an addition between the 2 given fixed-point values (operator: `*`)
//!@{
#define					Fixed_Mul	CONCAT(FIXED_TYPE,_Mul)
#define c_qmul			Fixed_Mul
#define Fixed_Multiply	Fixed_Mul

t_q8					Q8_Mul(t_q8 x, t_q8 y);
#define c_q8mul			Q8_Mul

t_q16					Q16_Mul(t_q16 x, t_q16 y);
#define c_q16mul		Q16_Mul

t_q32					Q32_Mul(t_q32 x, t_q32 y);
#define c_q32mul		Q32_Mul

t_q64					Q64_Mul(t_q64 x, t_q64 y);
#define c_q64mul		Q64_Mul

#if LIBCONFIG_USE_INT128
t_q128					Q128_Mul(t_q128 x, t_q128 y);
#define c_q128mul		Q128_Mul
#endif
//!@}



//!@doc Performs a division between the 2 given fixed-point values (operator: `/`)
//!@{
#define					Fixed_Div	CONCAT(FIXED_TYPE,_Div)
#define c_qdiv			Fixed_Div
#define Fixed_Divide	Fixed_Div

t_q8					Q8_Div(t_q8 x, t_q8 y);
#define c_q8div			Q8_Div

t_q16					Q16_Div(t_q16 x, t_q16 y);
#define c_q16div		Q16_Div

t_q32					Q32_Div(t_q32 x, t_q32 y);
#define c_q32div		Q32_Div

t_q64					Q64_Div(t_q64 x, t_q64 y);
#define c_q64div		Q64_Div

#if LIBCONFIG_USE_INT128
t_q128					Q128_Div(t_q128 x, t_q128 y);
#define c_q128div		Q128_Div
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Mod	CONCAT(FIXED_TYPE,_Mod)
#define c_qmod			Fixed_Mod
#define Fixed_Modulo	Fixed_Mod

t_q8					Q8_Mod(t_q8 x, t_q8 y);
#define c_q8mod			Q8_Mod

t_q16					Q16_Mod(t_q16 x, t_q16 y);
#define c_q16mod		Q16_Mod

t_q32					Q32_Mod(t_q32 x, t_q32 y);
#define c_q32mod		Q32_Mod

t_q64					Q64_Mod(t_q64 x, t_q64 y);
#define c_q64mod		Q64_Mod

#if LIBCONFIG_USE_INT128
t_q128					Q128_Mod(t_q128 x, t_q128 y);
#define c_q128mod		Q128_Mod
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Rem	CONCAT(FIXED_TYPE,_Rem)
#define c_qrem			Fixed_Rem
#define Fixed_Remainder	Fixed_Rem

t_q8					Q8_Rem(t_q8 x, t_q8 y);
#define c_q8rem			Q8_Rem

t_q16					Q16_Rem(t_q16 x, t_q16 y);
#define c_q16rem		Q16_Rem

t_q32					Q32_Rem(t_q32 x, t_q32 y);
#define c_q32rem		Q32_Rem

t_q64					Q64_Rem(t_q64 x, t_q64 y);
#define c_q64rem		Q64_Rem

#if LIBCONFIG_USE_INT128
t_q128					Q128_Rem(t_q128 x, t_q128 y);
#define c_q128rem		Q128_Rem
#endif
//!@}



//!@doc Returns the value of `x` to the power of `y` (fixed)
/*!
**	@nonstd
*/
//!@{
#define					Fixed_Pow	CONCAT(FIXED_TYPE,_Pow)
#define c_qpow			Fixed_Pow
#define Fixed_Power		Fixed_Pow

t_q8					Q8_Pow(t_q8 x, t_q8 y);
#define c_q8pow			Q8_Pow

t_q16					Q16_Pow(t_q16 x, t_q16 y);
#define c_q16pow		Q16_Pow

t_q32					Q32_Pow(t_q32 x, t_q32 y);
#define c_q32pow		Q32_Pow

t_q64					Q64_Pow(t_q64 x, t_q64 y);
#define c_q64pow		Q64_Pow

#if LIBCONFIG_USE_INT128
t_q128					Q128_Pow(t_q128 x, t_q128 y);
#define c_q128pow		Q128_Pow
#endif
//!@}



//!@doc Returns the square root of `x` (inverse of power of 2)
/*!
**	@nonstd
*/
//!@{
#define						Fixed_Root2	CONCAT(FIXED_TYPE,_Root2)
#define c_qsqrt				Fixed_Root2
#define c_qroot2			Fixed_Root2
#define Fixed_SqRt			Fixed_Root2
#define Fixed_SquareRoot	Fixed_Root2

t_q8						Q8_Root2(t_q8 x);
#define c_q8sqrt			Q8_Root2
#define c_q8root2			Q8_Root2

t_q16						Q16_Root2(t_q16 x);
#define c_q16sqrt			Q16_Root2
#define c_q16root2			Q16_Root2

t_q32						Q32_Root2(t_q32 x);
#define c_q32sqrt			Q32_Root2
#define c_q32root2			Q32_Root2

t_q64						Q64_Root2(t_q64 x);
#define c_q64sqrt			Q64_Root2
#define c_q64root2			Q64_Root2

#if LIBCONFIG_USE_INT128
t_q128						Q128_Root2(t_q128 x);
#define c_q128sqrt			Q128_Root2
#define c_q128root2			Q128_Root2
#endif
//!@}

//!@doc Returns the cubic root of `x` (inverse of power of 3)
/*!
**	@nonstd
*/
//!@{
#define						Fixed_Root3	CONCAT(FIXED_TYPE,_Root3)
#define c_qcbrt				Fixed_Root3
#define c_qroot3			Fixed_Root3
#define Fixed_CbRt			Fixed_Root3
#define Fixed_CubeRoot		Fixed_Root3

t_q8						Q8_Root3(t_q8 x);
#define c_q8cbrt			Q8_Root3
#define c_q8root3			Q8_Root3

t_q16						Q16_Root3(t_q16 x);
#define c_q16cbrt			Q16_Root3
#define c_q16root3			Q16_Root3

t_q32						Q32_Root3(t_q32 x);
#define c_q32cbrt			Q32_Root3
#define c_q32root3			Q32_Root3

t_q64						Q64_Root3(t_q64 x);
#define c_q64cbrt			Q64_Root3
#define c_q64root3			Q64_Root3

#if LIBCONFIG_USE_INT128
t_q128						Q128_Root3(t_q128 x);
#define c_q128cbrt			Q128_Root3
#define c_q128root3			Q128_Root3
#endif
//!@}

//!@doc Returns the n-ic root of `x` (inverse of power of `n`)
/*!
**	@nonstd
*/
//!@{
#define						Fixed_RootN	CONCAT(FIXED_TYPE,_RootN)
#define c_qnrt				Fixed_RootN
#define c_qrootn			Fixed_RootN
#define Fixed_NRt			Fixed_RootN
#define Fixed_NRoot			Fixed_RootN

t_q8						Q8_RootN(t_q8 x, t_u8 n);
#define c_q8nrt				Q8_RootN
#define c_q8rootn			Q8_RootN

t_q16						Q16_RootN(t_q16 x, t_u8 n);
#define c_q16nrt			Q16_RootN
#define c_q16rootn			Q16_RootN

t_q32						Q32_RootN(t_q32 x, t_u8 n);
#define c_q32nrt			Q32_RootN
#define c_q32rootn			Q32_RootN

t_q64						Q64_RootN(t_q64 x, t_u8 n);
#define c_q64nrt			Q64_RootN
#define c_q64rootn			Q64_RootN

#if LIBCONFIG_USE_INT128
t_q128						Q128_RootN(t_q128 x, t_u8 n);
#define c_q128nrt			Q128_RootN
#define c_q128rootn			Q128_RootN
#endif
//!@}



//!@doc Computes the square root of the sum of the squares of `x` and `y`, without undue overflow or underflow at intermediate stages of the computation.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/hypot}
**
**	- Math: @f$ {\sqrt{x^2+y^2}} @f$
*/
//!@{
#define						Fixed_Hypotenuse	CONCAT(FIXED_TYPE,_Hypotenuse)
#define c_qhypot			Fixed_Hypotenuse
#define Fixed_Hypot			Fixed_Hypotenuse

t_q8						Q8_Hypotenuse(t_q8 x, t_q8 y);
#define c_q8hypot			Q8_Hypotenuse

t_q16						Q16_Hypotenuse(t_q16 x, t_q16 y);
#define c_q16hypot			Q16_Hypotenuse

t_q32						Q32_Hypotenuse(t_q32 x, t_q32 y);
#define c_q32hypot			Q32_Hypotenuse

t_q64						Q64_Hypotenuse(t_q64 x, t_q64 y);
#define c_q64hypot			Q64_Hypotenuse

#if LIBCONFIG_USE_FLOAT128
t_q128						Q128_Hypotenuse(t_q128 x, t_q128 y);
#define c_q128hypot			Q128_Hypotenuse
#endif
//!@}



/*============================================================================*\
||                           Exponentiation Operations                        ||
\*============================================================================*/



//!@doc Returns the exponential function's value for `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Exp	CONCAT(FIXED_TYPE,_Exp)
#define c_qexp					Fixed_Exp
#define Fixed_Exponential		Fixed_Exp

t_q8							Q8_Exp(t_q8 x);
#define c_q8exp					Q8_Exp

t_q16							Q16_Exp(t_q16 x);
#define c_q16exp				Q16_Exp

t_q32							Q32_Exp(t_q32 x);
#define c_q32exp				Q32_Exp

t_q64							Q64_Exp(t_q64 x);
#define c_q64exp				Q64_Exp

#if LIBCONFIG_USE_INT128
t_q128							Q128_Exp(t_q128 x);
#define c_q128exp				Q128_Exp
#endif
//!@}

//!@doc Returns the exponential function's value for `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Exp2	CONCAT(FIXED_TYPE,_Exp2)
#define c_qexp2					Fixed_Exp2
#define c_qpow2					Fixed_Exp2
#define Fixed_Pow2				Fixed_Exp2

t_q8							Q8_Exp2(t_q8 x);
#define c_q8exp2				Q8_Exp2
#define c_q8pow2				Q8_Exp2

t_q16							Q16_Exp2(t_q16 x);
#define c_q16exp2				Q16_Exp2
#define c_q16pow2				Q16_Exp2

t_q32							Q32_Exp2(t_q32 x);
#define c_q32exp2				Q32_Exp2
#define c_q32pow2				Q32_Exp2

t_q64							Q64_Exp2(t_q64 x);
#define c_q64exp2				Q64_Exp2
#define c_q64pow2				Q64_Exp2

#if LIBCONFIG_USE_INT128
t_q128							Q128_Exp2(t_q128 x);
#define c_q128exp2				Q128_Exp2
#define c_q128pow2				Q128_Exp2
#endif
//!@}

//!@doc Returns the ex ponential function's value for `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Exp10	CONCAT(FIXED_TYPE,_Exp10)
#define c_qexp10				Fixed_Exp10
#define c_qpow10				Fixed_Exp10
#define Fixed_Pow10				Fixed_Exp10

t_q8							Q8_Exp10(t_q8 x);
#define c_q8exp10				Q8_Exp10
#define c_q8pow10				Q8_Exp10

t_q16							Q16_Exp10(t_q16 x);
#define c_q16exp10				Q16_Exp10
#define c_q16pow10				Q16_Exp10

t_q32							Q32_Exp10(t_q32 x);
#define c_q32exp10				Q32_Exp10
#define c_q32pow10				Q32_Exp10

t_q64							Q64_Exp10(t_q64 x);
#define c_q64exp10				Q64_Exp10
#define c_q64pow10				Q64_Exp10

#if LIBCONFIG_USE_INT128
t_q128							Q128_Exp10(t_q128 x);
#define c_q128exp10				Q128_Exp10
#define c_q128pow10				Q128_Exp10
#endif
//!@}



//!@doc Returns the natural logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Ln	CONCAT(FIXED_TYPE,_Ln)
#define c_qln					Fixed_Ln
#define Fixed_NaturalLogarithm	Fixed_Ln

t_q8							Q8_Ln(t_q8 x);
#define c_q8ln					Q8_Ln

t_q16							Q16_Ln(t_q16 x);
#define c_q16ln					Q16_Ln

t_q32							Q32_Ln(t_q32 x);
#define c_q32ln					Q32_Ln

t_q64							Q64_Ln(t_q64 x);
#define c_q64ln					Q64_Ln

#if LIBCONFIG_USE_INT128
t_q128							Q128_Ln(t_q128 x);
#define c_q128ln				Q128_Ln
#endif
//!@}

//!@doc Returns the binary (base-2) logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Log2	CONCAT(FIXED_TYPE,_Log2)
#define c_qlg					Fixed_Log2
#define c_qlog2					Fixed_Log2
#define Fixed_Logarithm_Base2	Fixed_Log2

t_q8							Q8_Log2(t_q8 x);
#define c_q8lg					Q8_Log2
#define c_q8log2				Q8_Log2

t_q16							Q16_Log2(t_q16 x);
#define c_q16lg					Q16_Log2
#define c_q16log2				Q16_Log2

t_q32							Q32_Log2(t_q32 x);
#define c_q32lg					Q32_Log2
#define c_q32log2				Q32_Log2

t_q64							Q64_Log2(t_q64 x);
#define c_q64lg					Q64_Log2
#define c_q64log2				Q64_Log2


#if LIBCONFIG_USE_INT128
t_q128							Q128_Log2(t_q128 x);
#define c_q128lg				Q128_Log2
#define c_q128log2				Q128_Log2
#endif
//!@}

//!@doc Returns the decimal (base-10) logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Log10	CONCAT(FIXED_TYPE,_Log10)
#define c_qlog					Fixed_Log10
#define c_qlog10				Fixed_Log10
#define Fixed_Logarithm_Base10	Fixed_Log10

t_q8							Q8_Log10(t_q8 x);
#define c_q8log					Q8_Log10
#define c_q8log10				Q8_Log10

t_q16							Q16_Log10(t_q16 x);
#define c_q16log				Q16_Log10
#define c_q16log10				Q16_Log10

t_q32							Q32_Log10(t_q32 x);
#define c_q32log				Q32_Log10
#define c_q32log10				Q32_Log10

t_q64							Q64_Log10(t_q64 x);
#define c_q64log				Q64_Log10
#define c_q64log10				Q64_Log10

#if LIBCONFIG_USE_INT128
t_q128							Q128_Log10(t_q128 x);
#define c_q128log				Q128_Log10
#define c_q128log10				Q128_Log10
#endif
//!@}

//!@doc Returns the base-`n` logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Fixed_LogN	CONCAT(FIXED_TYPE,_LogN)
#define c_qlogn					Fixed_LogN
#define Fixed_Logarithm_BaseN	Fixed_LogN

t_q8							Q8_LogN(t_q8 x, t_q8 y);
#define c_q8logn				Q8_LogN

t_q16							Q16_LogN(t_q16 x, t_q16 y);
#define c_q16logn				Q16_LogN

t_q32							Q32_LogN(t_q32 x, t_q32 y);
#define c_q32logn				Q32_LogN

t_q64							Q64_LogN(t_q64 x, t_q64 y);
#define c_q64logn				Q64_LogN

#if LIBCONFIG_USE_INT128
t_q128							Q128_LogN(t_q128 x, t_q128 y);
#define c_q128logn				Q128_LogN
#endif
//!@}



/*============================================================================*\
||                           Trigonometric Operations                         ||
\*============================================================================*/



//!@doc Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Sin	CONCAT(FIXED_TYPE,_Sin)
#define c_qsin					Fixed_Sin
#define Fixed_Sine				Fixed_Sin

t_q8							Q8_Sin(t_q8 x);
#define c_q8sin					Q8_Sin

t_q16							Q16_Sin(t_q16 x);
#define c_q16sin				Q16_Sin

t_q32							Q32_Sin(t_q32 x);
#define c_q32sin				Q32_Sin

t_q64							Q64_Sin(t_q64 x);
#define c_q64sin				Q64_Sin

#if LIBCONFIG_USE_INT128
t_q128							Q128_Sin(t_q128 x);
#define c_q128sin				Q128_Sin
#endif
//!@}

//!@doc Returns the cosine of `x` (horizontal trigonometry coordinate)
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Cos	CONCAT(FIXED_TYPE,_Cos)
#define c_qcos					Fixed_Cos
#define Fixed_Cosine			Fixed_Cos

t_q8							Q8_Cos(t_q8 x);
#define c_q8cos					Q8_Cos

t_q16							Q16_Cos(t_q16 x);
#define c_q16cos				Q16_Cos

t_q32							Q32_Cos(t_q32 x);
#define c_q32cos				Q32_Cos

t_q64							Q64_Cos(t_q64 x);
#define c_q64cos				Q64_Cos

#if LIBCONFIG_USE_INT128
t_q128							Q128_Cos(t_q128 x);
#define c_q128cos				Q128_Cos
#endif
//!@}

//!@doc Returns the tangent of `x` (trigonometry tangent line)
/*!
**	@nonstd
*/
//!@{
#define							Fixed_Tan	CONCAT(FIXED_TYPE,_Tan)
#define c_qtan					Fixed_Tan
#define Fixed_Tangent			Fixed_Tan

t_q8							Q8_Tan(t_q8 x);
#define c_q8tan					Q8_Tan

t_q16							Q16_Tan(t_q16 x);
#define c_q16tan				Q16_Tan

t_q32							Q32_Tan(t_q32 x);
#define c_q32tan				Q32_Tan

t_q64							Q64_Tan(t_q64 x);
#define c_q64tan				Q64_Tan

#if LIBCONFIG_USE_INT128
t_q128							Q128_Tan(t_q128 x);
#define c_q128tan				Q128_Tan
#endif
//!@}



//!@doc Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	@nonstd
*/
//!@{
#define							Fixed_ArcSin	CONCAT(FIXED_TYPE,_ArcSin)
#define c_qasin					Fixed_ArcSin
#define Fixed_Sin_1				Fixed_ArcSin
#define Fixed_InvSine			Fixed_ArcSin

t_q8							Q8_ArcSin(t_q8 x);
#define c_q8asin				Q8_ArcSin

t_q16							Q16_ArcSin(t_q16 x);
#define c_q16asin				Q16_ArcSin

t_q32							Q32_ArcSin(t_q32 x);
#define c_q32asin				Q32_ArcSin

t_q64							Q64_ArcSin(t_q64 x);
#define c_q64asin				Q64_ArcSin

#if LIBCONFIG_USE_INT128
t_q128							Q128_ArcSin(t_q128 x);
#define c_q128asin				Q128_ArcSin
#endif
//!@}

//!@doc Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	@nonstd
*/
//!@{
#define							Fixed_ArcCos	CONCAT(FIXED_TYPE,_ArcCos)
#define c_qacos					Fixed_ArcCos
#define Fixed_Cos_1				Fixed_ArcCos
#define Fixed_InvCosine			Fixed_ArcCos

t_q8							Q8_ArcCos(t_q8 x);
#define c_q8acos				Q8_ArcCos

t_q16							Q16_ArcCos(t_q16 x);
#define c_q16acos				Q16_ArcCos

t_q32							Q32_ArcCos(t_q32 x);
#define c_q32acos				Q32_ArcCos

t_q64							Q64_ArcCos(t_q64 x);
#define c_q64acos				Q64_ArcCos

#if LIBCONFIG_USE_INT128
t_q128							Q128_ArcCos(t_q128 x);
#define c_q128acos				Q128_ArcCos
#endif
//!@}

//!@doc Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	@nonstd
*/
//!@{
#define							Fixed_ArcTan	CONCAT(FIXED_TYPE,_ArcTan)
#define c_qatan					Fixed_ArcTan
#define Fixed_Tan_1				Fixed_ArcTan
#define Fixed_InvTangent		Fixed_ArcTan

t_q8							Q8_ArcTan(t_q8 x);
#define c_q8atan				Q8_ArcTan

t_q16							Q16_ArcTan(t_q16 x);
#define c_q16atan				Q16_ArcTan

t_q32							Q32_ArcTan(t_q32 x);
#define c_q32atan				Q32_ArcTan

t_q64							Q64_ArcTan(t_q64 x);
#define c_q64atan				Q64_ArcTan

#if LIBCONFIG_USE_INT128
t_q128							Q128_ArcTan(t_q128 x);
#define c_q128atan				Q128_ArcTan
#endif
//!@}



//!@doc Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	@nonstd
*/
//!@{
#define								Fixed_ArcTan2	CONCAT(FIXED_TYPE,_ArcTan2)
#define c_qatan2					Fixed_ArcTan2
#define Fixed_ArcTan_YoverX			Fixed_ArcTan2
#define Fixed_ArcTangent2			Fixed_ArcTan2
#define Fixed_ArcTangent_YoverX		Fixed_ArcTan2

t_q8								Q8_ArcTan2(t_q8 x, t_q8 y);
#define c_q8atan2					Q8_ArcTan2

t_q16								Q16_ArcTan2(t_q16 x, t_q16 y);
#define c_q16atan2					Q16_ArcTan2

t_q32								Q32_ArcTan2(t_q32 x, t_q32 y);
#define c_q32atan2					Q32_ArcTan2

t_q64								Q64_ArcTan2(t_q64 x, t_q64 y);
#define c_q64atan2					Q64_ArcTan2

#if LIBCONFIG_USE_INT128
t_q128								Q128_ArcTan2(t_q128 x, t_q128 y);
#define c_q128atan2					Q128_ArcTan2
#endif
//!@}



//!@doc Returns the hyperbolic sine of `x`
/*!
**	@nonstd
*/
//!@{
#define								Fixed_SinH	CONCAT(FIXED_TYPE,_SinH)
#define c_qsinh						Fixed_SinH
#define Fixed_Sin_H					Fixed_SinH
#define Fixed_Sine_Hyperbolic		Fixed_SinH

t_q8								Q8_SinH(t_q8 x);
#define c_q8sinh					Q8_SinH

t_q16								Q16_SinH(t_q16 x);
#define c_q16sinh					Q16_SinH

t_q32								Q32_SinH(t_q32 x);
#define c_q32sinh					Q32_SinH

t_q64								Q64_SinH(t_q64 x);
#define c_q64sinh					Q64_SinH

#if LIBCONFIG_USE_INT128
t_q128								Q128_SinH(t_q128 x);
#define c_q128sinh					Q128_SinH
#endif
//!@}

//!@doc Returns the hyperbolic cosine of `x`
/*!
**	@nonstd
*/
//!@{
#define								Fixed_CosH	CONCAT(FIXED_TYPE,_CosH)
#define c_qcosh						Fixed_CosH
#define Fixed_Cos_H					Fixed_CosH
#define Fixed_Cosine_Hyperbolic		Fixed_CosH

t_q8								Q8_CosH(t_q8 x);
#define c_q8cosh					Q8_CosH

t_q16								Q16_CosH(t_q16 x);
#define c_q16cosh					Q16_CosH

t_q32								Q32_CosH(t_q32 x);
#define c_q32cosh					Q32_CosH

t_q64								Q64_CosH(t_q64 x);
#define c_q64cosh					Q64_CosH

#if LIBCONFIG_USE_INT128
t_q128								Q128_CosH(t_q128 x);
#define c_q128cosh					Q128_CosH
#endif
//!@}

//!@doc Returns the hyperbolic tangent of `x`
/*!
**	@nonstd
*/
//!@{
#define								Fixed_TanH	CONCAT(FIXED_TYPE,_TanH)
#define c_qtanh						Fixed_TanH
#define Fixed_Tan_H					Fixed_TanH
#define Fixed_Tangent_Hyperbolic	Fixed_TanH

t_q8								Q8_TanH(t_q8 x);
#define c_q8tanh					Q8_TanH

t_q16								Q16_TanH(t_q16 x);
#define c_q16tanh					Q16_TanH

t_q32								Q32_TanH(t_q32 x);
#define c_q32tanh					Q32_TanH

t_q64								Q64_TanH(t_q64 x);
#define c_q64tanh					Q64_TanH

#if LIBCONFIG_USE_INT128
t_q128								Q128_TanH(t_q128 x);
#define c_q128tanh					Q128_TanH
#endif
//!@}



//!@doc Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	@nonstd
*/
//!@{
#define								Fixed_InvSinH	CONCAT(FIXED_TYPE,_InvSinH)
#define c_qasinh					Fixed_InvSinH
#define Fixed_Sin_1_H				Fixed_InvSinH
#define Fixed_InvSine_Hyperbolic	Fixed_InvSinH

t_q8								Q8_InvSinH(t_q8 x);
#define c_q8asinh					Q8_InvSinH

t_q16								Q16_InvSinH(t_q16 x);
#define c_q16asinh					Q16_InvSinH

t_q32								Q32_InvSinH(t_q32 x);
#define c_q32asinh					Q32_InvSinH

t_q64								Q64_InvSinH(t_q64 x);
#define c_q64asinh					Q64_InvSinH

#if LIBCONFIG_USE_INT128
t_q128								Q128_InvSinH(t_q128 x);
#define c_q128asinh					Q128_InvSinH
#endif
//!@}

//!@doc Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	@nonstd
*/
//!@{
#define								Fixed_InvCosH	CONCAT(FIXED_TYPE,_InvCosH)
#define c_qacosh					Fixed_InvCosH
#define Fixed_Cos_1_H				Fixed_InvCosH
#define Fixed_InvCosine_Hyperbolic	Fixed_InvCosH

t_q8								Q8_InvCosH(t_q8 x);
#define c_q8acosh					Q8_InvCosH

t_q16								Q16_InvCosH(t_q16 x);
#define c_q16acosh					Q16_InvCosH

t_q32								Q32_InvCosH(t_q32 x);
#define c_q32acosh					Q32_InvCosH

t_q64								Q64_InvCosH(t_q64 x);
#define c_q64acosh					Q64_InvCosH

#if LIBCONFIG_USE_INT128
t_q128								Q128_InvCosH(t_q128 x);
#define c_q128acosh					Q128_InvCosH
#endif
//!@}

//!@doc Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	@nonstd
*/
//!@{
#define								Fixed_InvTanH	CONCAT(FIXED_TYPE,_InvTanH)
#define c_qatanh					Fixed_InvTanH
#define Fixed_Tan_1_H				Fixed_InvTanH
#define Fixed_InvTangent_Hyperbolic	Fixed_InvTanH

t_q8								Q8_InvTanH(t_q8 x);
#define c_q8atanh					Q8_InvTanH

t_q16								Q16_InvTanH(t_q16 x);
#define c_q16atanh					Q16_InvTanH

t_q32								Q32_InvTanH(t_q32 x);
#define c_q32atanh					Q32_InvTanH

t_q64								Q64_InvTanH(t_q64 x);
#define c_q64atanh					Q64_InvTanH

#if LIBCONFIG_USE_INT128
t_q128								Q128_InvTanH(t_q128 x);
#define c_q128atanh					Q128_InvTanH
#endif
//!@}



/*! @endgroup */
HEADER_END
#endif
