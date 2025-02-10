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
/*!@group{libccc_math_float,53,libccc/math/float.h}
**
**	This header defines the common standard math functions for floating-point numbers.
**
**	@isostd{C,https://en.cppreference.com/w/c/numeric/math}
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/float.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/



//!@doc The type of function which takes one real number and outputs one real number
//!@{
#if LIBCONFIG_USE_FLOAT16
typedef	t_f16	(*f_f16_function)	(t_f16   x);
#endif
typedef	t_f32	(*f_f32_function)	(t_f32   x);

typedef	t_f64	(*f_f64_function)	(t_f64   x);
#if LIBCONFIG_USE_FLOAT80
typedef	t_f80	(*f_f80_function)	(t_f80   x);
#endif
#if LIBCONFIG_USE_FLOAT128
typedef	t_f128	(*f_f128_function)	(t_f128  x);
#endif
typedef	t_float	(*f_float_function)	(t_float x);
//!@}

//!@doc The type of function which takes two real numbers and outputs one real number
//!@{
#if LIBCONFIG_USE_FLOAT16
typedef	t_f16	(*f_f16_operator)	(t_f16   x, t_f16   y);
#endif
typedef	t_f32	(*f_f32_operator)	(t_f32   x, t_f32   y);

typedef	t_f64	(*f_f64_operator)	(t_f64   x, t_f64   y);
#if LIBCONFIG_USE_FLOAT80
typedef	t_f80	(*f_f80_operator)	(t_f80   x, t_f80   y);
#endif
#if LIBCONFIG_USE_FLOAT128
typedef	t_f128	(*f_f128_operator)	(t_f128  x, t_f128  y);
#endif
typedef	t_float	(*f_float_operator)	(t_float x, t_float y);
//!@}

//!@doc The type of function which relates two numbers to each other
//!@{
#if LIBCONFIG_USE_FLOAT16
typedef	t_bool	(*f_f16_relation)	(t_f16   x, t_f16   y);
#endif
typedef	t_bool	(*f_f32_relation)	(t_f32   x, t_f32   y);

typedef	t_bool	(*f_f64_relation)	(t_f64   x, t_f64   y);
#if LIBCONFIG_USE_FLOAT80
typedef	t_bool	(*f_f80_relation)	(t_f80   x, t_f80   y);
#endif
#if LIBCONFIG_USE_FLOAT128
typedef	t_bool	(*f_f128_relation)	(t_f128  x, t_f128  y);
#endif
typedef	t_bool	(*f_float_relation)	(t_float x, t_float y);
//!@}



/*============================================================================*\
||                           Basic Arithmetic Operations                      ||
\*============================================================================*/

//!@doc Returns the absolute value of `x` (makes `x` positive)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fabs}
*/
//!@{
#define						Float_Abs	CONCAT(FLOAT_TYPE,_Abs)
#define c_fabs				Float_Abs
#define Float_AbsoluteValue	Float_Abs

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Abs(t_f16 x);
#define c_f16abs			F16_Abs
#endif
t_f32						F32_Abs(t_f32 x);
#define c_f32abs			F32_Abs

t_f64						F64_Abs(t_f64 x);
#define c_f64abs			F64_Abs

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Abs(t_f80 x);
#define c_f80abs			F80_Abs
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Abs(t_f128 x);
#define c_f128abs			F128_Abs
#endif
//!@}

//!@doc Returns the sign value value of `x` (either `-1`, `0`, or `+1`)
/*!
**	@isostd{C11,https://en.cppreference.com/w/c/numeric/math/signbit}
*/
//!@{
#define						Float_Sgn	CONCAT(FLOAT_TYPE,_Sgn)
#define c_fsgn				Float_Sgn
#define Float_Sign			Float_Sgn
#define Float_SignOf		Float_Sgn

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Sgn(t_f16 x);
#define c_f16sgn			F16_Sgn
#endif
t_f32						F32_Sgn(t_f32 x);
#define c_f32sgn			F32_Sgn

t_f64						F64_Sgn(t_f64 x);
#define c_f64sgn			F64_Sgn

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Sgn(t_f80 x);
#define c_f80sgn			F80_Sgn
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Sgn(t_f128 x);
#define c_f128sgn			F128_Sgn
#endif
//!@}



/*============================================================================*\
||                           Basic kind-check functions                       ||
\*============================================================================*/



//!@doc Returns `TRUE` if the given number is NAN (not a number).
/*!
**	@nonstd
*/
//!@{
#define						Float_IsNaN	CONCAT(FLOAT_TYPE,_IsNaN)
#define c_fisnan			Float_IsNaN

#if LIBCONFIG_USE_FLOAT16
t_bool						F16_IsNaN(t_f16 a);
#define c_f16isnan			F16_IsNaN
#endif
t_bool						F32_IsNaN(t_f32 a);
#define c_f32isnan			F32_IsNaN

t_bool						F64_IsNaN(t_f64 a);
#define c_f64isnan			F64_IsNaN

#if LIBCONFIG_USE_FLOAT80
t_bool						F80_IsNaN(t_f80 a);
#define c_f80isnan			F80_IsNaN
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool						F128_IsNaN(t_f128 a);
#define c_f128isnan			F128_IsNaN
#endif
//!@}



//!@doc Returns `TRUE` if the given number is infinite.
/*!
**	@nonstd
*/
//!@{
#define						Float_IsInf	CONCAT(FLOAT_TYPE,_IsInf)
#define c_fisinf			Float_IsInf

#if LIBCONFIG_USE_FLOAT16
t_bool						F16_IsInf(t_f16 a);
#define c_f16isinf			F16_IsInf
#endif
t_bool						F32_IsInf(t_f32 a);
#define c_f32isinf			F32_IsInf

t_bool						F64_IsInf(t_f64 a);
#define c_f64isinf			F64_IsInf

#if LIBCONFIG_USE_FLOAT80
t_bool						F80_IsInf(t_f80 a);
#define c_f80isinf			F80_IsInf
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool						F128_IsInf(t_f128 a);
#define c_f128isinf			F128_IsInf
#endif
//!@}



//!@doc Returns `TRUE` if the given number is a prime number.
/*!
**	@nonstd
*/
//!@{
#define						Float_IsPrime	CONCAT(FLOAT_TYPE,_IsPrime)
#define c_fisprime			Float_IsPrime

#if LIBCONFIG_USE_FLOAT16
t_bool						F16_IsPrime(t_f16 a);
#define c_f16isprime		F16_IsPrime
#endif
t_bool						F32_IsPrime(t_f32 a);
#define c_f32isprime		F32_IsPrime

t_bool						F64_IsPrime(t_f64 a);
#define c_f64isprime		F64_IsPrime

#if LIBCONFIG_USE_FLOAT80
t_bool						F80_IsPrime(t_f80 a);
#define c_f80isprime		F80_IsPrime
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool						F128_IsPrime(t_f128 a);
#define c_f128isprime		F128_IsPrime
#endif
//!@}



/*============================================================================*\
||                          Integer Rounding Operations                       ||
\*============================================================================*/

//!@doc Returns the value of `x`, rounded to the nearest integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/round}
*/
//!@{
#define						Float_Round	CONCAT(FLOAT_TYPE,_Round)
#define c_fround			Float_Round

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Round(t_f16 x);
#define c_f16round			F16_Round
#endif
t_f32						F32_Round(t_f32 x);
#define c_f32round			F32_Round

t_f64						F64_Round(t_f64 x);
#define c_f64round			F64_Round

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Round(t_f80 x);
#define c_f80round			F80_Round
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Round(t_f128 x);
#define c_f128round			F128_Round
#endif
//!@}

//!@doc Returns the value of `x`, rounded towards 0
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/trunc}
*/
//!@{
#define						Float_Trunc	CONCAT(FLOAT_TYPE,_Trunc)
#define c_ftrunc			Float_Trunc
#define Float_Truncate		Float_Trunc

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Trunc(t_f16 x);
#define c_f16trunc			F16_Trunc
#endif
t_f32						F32_Trunc(t_f32 x);
#define c_f32trunc			F32_Trunc

t_f64						F64_Trunc(t_f64 x);
#define c_f64trunc			F64_Trunc

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Trunc(t_f80 x);
#define c_f80trunc			F80_Trunc
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Trunc(t_f128 x);
#define c_f128trunc			F128_Trunc
#endif
//!@}

//!@doc Returns the value of `x`, rounded to the superior integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/floor}
*/
//!@{
#define						Float_Floor	CONCAT(FLOAT_TYPE,_Floor)
#define c_ffloor			Float_Floor

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Floor(t_f16 x);
#define c_f16floor			F16_Floor
#endif
t_f32						F32_Floor(t_f32 x);
#define c_f32floor			F32_Floor

t_f64						F64_Floor(t_f64 x);
#define c_f64floor			F64_Floor

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Floor(t_f80 x);
#define c_f80floor			F80_Floor
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Floor(t_f128 x);
#define c_f128floor			F128_Floor
#endif
//!@}

//!@doc Returns the value of `x`, rounded to the inferior integer
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/ceil}
*/
//!@{
#define						Float_Ceil	CONCAT(FLOAT_TYPE,_Ceil)
#define c_fceil				Float_Ceil
#define Float_Ceiling		Float_Ceil

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Ceil(t_f16 x);
#define c_f16ceil			F16_Ceil
#endif
t_f32						F32_Ceil(t_f32 x);
#define c_f32ceil			F32_Ceil

t_f64						F64_Ceil(t_f64 x);
#define c_f64ceil			F64_Ceil

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Ceil(t_f80 x);
#define c_f80ceil			F80_Ceil
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Ceil(t_f128 x);
#define c_f128ceil			F128_Ceil
#endif
//!@}



/*============================================================================*\
||                            Comparison operators                            ||
\*============================================================================*/

//!@doc Returns `TRUE` if the 2 given floating-point values are exactly equal (operator: `==`)
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

#if LIBCONFIG_USE_FLOAT16
t_bool					F16_Equals(t_f16 x, t_f16 y);
#define c_f16equ		F16_Equals
#endif
t_bool					F32_Equals(t_f32 x, t_f32 y);
#define c_f32equ		F32_Equals

t_bool					F64_Equals(t_f64 x, t_f64 y);
#define c_f64equ		F64_Equals

#if LIBCONFIG_USE_FLOAT80
t_bool					F80_Equals(t_f80 x, t_f80 y);
#define c_f80equ		F80_Equals
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool					F128_Equals(t_f128 x, t_f128 y);
#define c_f128equ		F128_Equals
#endif
//!@}

//!@doc Returns `TRUE` if the 2 given floating-point values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (approximate) equality
**	@param	y	The second value to check for (approximate) equality
**	@param	approx	The tolerance margin for the approximate equality check
**	@returns
**	`TRUE` if the 2 given floating-point values are close enough to be considered equal
**	(using #FLOAT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					Float_EqualsApprox	CONCAT(FLOAT_TYPE,_EqualsApprox)
#define c_fequa			Float_EqualsApprox

#if LIBCONFIG_USE_FLOAT16
t_bool					F16_EqualsApprox(t_f16 x, t_f16 y, t_f16 approx);
#define c_f16equa		F16_EqualsApprox
#endif
t_bool					F32_EqualsApprox(t_f32 x, t_f32 y, t_f32 approx);
#define c_f32equa		F32_EqualsApprox

t_bool					F64_EqualsApprox(t_f64 x, t_f64 y, t_f64 approx);
#define c_f64equa		F64_EqualsApprox

#if LIBCONFIG_USE_FLOAT80
t_bool					F80_EqualsApprox(t_f80 x, t_f80 y, t_f80 approx);
#define c_f80equa		F80_EqualsApprox
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool					F128_EqualsApprox(t_f128 x, t_f128 y, t_f128 approx);
#define c_f128equa		F128_EqualsApprox
#endif
//!@}



//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value (operator: `<`)
//!@{
#define					Float_LessThan	CONCAT(FLOAT_TYPE,_LessThan)
#define c_flt			Float_LessThan

#if LIBCONFIG_USE_FLOAT16
t_bool					F16_LessThan(t_f16 x, t_f16 y);
#define c_f16lt			F16_LessThan
#endif
t_bool					F32_LessThan(t_f32 x, t_f32 y);
#define c_f32lt			F32_LessThan

t_bool					F64_LessThan(t_f64 x, t_f64 y);
#define c_f64lt			F64_LessThan

#if LIBCONFIG_USE_FLOAT80
t_bool					F80_LessThan(t_f80 x, t_f80 y);
#define c_f80lt			F80_LessThan
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool					F128_LessThan(t_f128 x, t_f128 y);
#define c_f128lt		F128_LessThan
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value or equal to it (operator: `<=`)
//!@{
#define					Float_LessThanOrEqual	CONCAT(FLOAT_TYPE,_LessThanOrEqual)
#define c_flte			Float_LessThanOrEqual

#if LIBCONFIG_USE_FLOAT16
t_bool					F16_LessThanOrEqual(t_f16 x, t_f16 y);
#define c_f16lte		F16_LessThanOrEqual
#endif
t_bool					F32_LessThanOrEqual(t_f32 x, t_f32 y);
#define c_f32lte		F32_LessThanOrEqual

t_bool					F64_LessThanOrEqual(t_f64 x, t_f64 y);
#define c_f64lte		F64_LessThanOrEqual

#if LIBCONFIG_USE_FLOAT80
t_bool					F80_LessThanOrEqual(t_f80 x, t_f80 y);
#define c_f80lte		F80_LessThanOrEqual
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool					F128_LessThanOrEqual(t_f128 x, t_f128 y);
#define c_f128lte		F128_LessThanOrEqual
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value (operator: `>`)
//!@{
#define					Float_GreaterThan	CONCAT(FLOAT_TYPE,_GreaterThan)
#define c_fgt			Float_GreaterThan

#if LIBCONFIG_USE_FLOAT16
t_bool					F16_GreaterThan(t_f16 x, t_f16 y);
#define c_f16gt			F16_GreaterThan
#endif
t_bool					F32_GreaterThan(t_f32 x, t_f32 y);
#define c_f32gt			F32_GreaterThan

t_bool					F64_GreaterThan(t_f64 x, t_f64 y);
#define c_f64gt			F64_GreaterThan

#if LIBCONFIG_USE_FLOAT80
t_bool					F80_GreaterThan(t_f80 x, t_f80 y);
#define c_f80gt			F80_GreaterThan
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool					F128_GreaterThan(t_f128 x, t_f128 y);
#define c_f128gt		F128_GreaterThan
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value or equal to it (operator: `>=`)
//!@{
#define					Float_GreaterThanOrEqual	CONCAT(FLOAT_TYPE,_GreaterThanOrEqual)
#define c_fgte			Float_GreaterThanOrEqual

#if LIBCONFIG_USE_FLOAT16
t_bool					F16_GreaterThanOrEqual(t_f16 x, t_f16 y);
#define c_f16gte		F16_GreaterThanOrEqual
#endif
t_bool					F32_GreaterThanOrEqual(t_f32 x, t_f32 y);
#define c_f32gte		F32_GreaterThanOrEqual

t_bool					F64_GreaterThanOrEqual(t_f64 x, t_f64 y);
#define c_f64gte		F64_GreaterThanOrEqual

#if LIBCONFIG_USE_FLOAT80
t_bool					F80_GreaterThanOrEqual(t_f80 x, t_f80 y);
#define c_f80gte		F80_GreaterThanOrEqual
#endif
#if LIBCONFIG_USE_FLOAT128
t_bool					F128_GreaterThanOrEqual(t_f128 x, t_f128 y);
#define c_f128gte		F128_GreaterThanOrEqual
#endif
//!@}



//!@doc Returns the smaller of the two given numbers `x` and `y`
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/numeric/math/fmin}
*/
//!@{
#define					Float_Min	CONCAT(FLOAT_TYPE,_Min)
#define c_fmin			Float_Min
#define Float_Minimum	Float_Min

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_Min(t_f16 x, t_f16 y);
#define c_f16min		F16_Min
#endif
t_f32					F32_Min(t_f32 x, t_f32 y);
#define c_f32min		F32_Min

t_f64					F64_Min(t_f64 x, t_f64 y);
#define c_f64min		F64_Min

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_Min(t_f80 x, t_f80 y);
#define c_f80min		F80_Min
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_Min(t_f128 x, t_f128 y);
#define c_f128min		F128_Min
#endif
//!@}

//!@doc Returns the larger of the two given numbers `x` and `y`
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/numeric/math/fmax}
*/
//!@{
#define					Float_Max	CONCAT(FLOAT_TYPE,_Max)
#define c_fmax			Float_Max
#define Float_Maximum	Float_Max

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_Max(t_f16 x, t_f16 y);
#define c_f16max		F16_Max
#endif
t_f32					F32_Max(t_f32 x, t_f32 y);
#define c_f32max		F32_Max

t_f64					F64_Max(t_f64 x, t_f64 y);
#define c_f64max		F64_Max

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_Max(t_f80 x, t_f80 y);
#define c_f80max		F80_Max
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_Max(t_f128 x, t_f128 y);
#define c_f128max		F128_Max
#endif
//!@}



/*============================================================================*\
||                            Arithmetic operators                            ||
\*============================================================================*/



//!@doc Performs an addition with the 2 given floating-point values (operator: `+`)
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/numeric/math/fadd}
*/
//!@{
#define					Float_Add	CONCAT(FLOAT_TYPE,_Add)
#define c_fadd			Float_Add
#define Float_Addition	Float_Add

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_Add(t_f16 x, t_f16 y);
#define c_f16add		F16_Add
#endif
t_f32					F32_Add(t_f32 x, t_f32 y);
#define c_f32add		F32_Add

t_f64					F64_Add(t_f64 x, t_f64 y);
#define c_f64add		F64_Add

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_Add(t_f80 x, t_f80 y);
#define c_f80add		F80_Add
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_Add(t_f128 x, t_f128 y);
#define c_f128add		F128_Add
#endif
//!@}



//!@doc Performs a subtraction with the 2 given floating-point values (operator: `-`)
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/numeric/math/fsub}
*/
//!@{
#define					Float_Sub	CONCAT(FLOAT_TYPE,_Sub)
#define c_fsub			Float_Sub
#define Float_Subtract	Float_Sub
#define Float_Subtraction	Float_Sub

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_Sub(t_f16 x, t_f16 y);
#define c_f16sub		F16_Sub
#endif
t_f32					F32_Sub(t_f32 x, t_f32 y);
#define c_f32sub		F32_Sub

t_f64					F64_Sub(t_f64 x, t_f64 y);
#define c_f64sub		F64_Sub

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_Sub(t_f80 x, t_f80 y);
#define c_f80sub		F80_Sub
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_Sub(t_f128 x, t_f128 y);
#define c_f128sub		F128_Sub
#endif
//!@}



//!@doc Performs a multiplication with the 2 given floating-point values (operator: `*`)
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/numeric/math/fmul}
*/
//!@{
#define					Float_Mul	CONCAT(FLOAT_TYPE,_Mul)
#define c_fmul			Float_Mul
#define Float_Multiply	Float_Mul
#define Float_Multiplication	Float_Mul

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_Mul(t_f16 x, t_f16 y);
#define c_f16mul		F16_Mul
#endif
t_f32					F32_Mul(t_f32 x, t_f32 y);
#define c_f32mul		F32_Mul

t_f64					F64_Mul(t_f64 x, t_f64 y);
#define c_f64mul		F64_Mul

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_Mul(t_f80 x, t_f80 y);
#define c_f80mul		F80_Mul
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_Mul(t_f128 x, t_f128 y);
#define c_f128mul		F128_Mul
#endif
//!@}



//!@doc Performs a division with the 2 given floating-point values (operator: `/`)
/*!
**	@isostd{C23,https://en.cppreference.com/w/c/numeric/math/fdiv}
*/
//!@{
#define					Float_Div	CONCAT(FLOAT_TYPE,_Div)
#define c_fdiv			Float_Div
#define Float_Divide	Float_Div
#define Float_Division	Float_Div

#if LIBCONFIG_USE_FLOAT16
t_f16					F16_Div(t_f16 x, t_f16 y);
#define c_f16div		F16_Div
#endif
t_f32					F32_Div(t_f32 x, t_f32 y);
#define c_f32div		F32_Div

t_f64					F64_Div(t_f64 x, t_f64 y);
#define c_f64div		F64_Div

#if LIBCONFIG_USE_FLOAT80
t_f80					F80_Div(t_f80 x, t_f80 y);
#define c_f80div		F80_Div
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128					F128_Div(t_f128 x, t_f128 y);
#define c_f128div		F128_Div
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/fmod}
*/
//!@{
#define						Float_Mod	CONCAT(FLOAT_TYPE,_Mod)
#define c_fmod				Float_Mod
#define Float_Modulo		Float_Mod

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Mod(t_f16 x, t_f16 y);
#define c_f16mod			F16_Mod
#endif
t_f32						F32_Mod(t_f32 x, t_f32 y);
#define c_f32mod			F32_Mod

t_f64						F64_Mod(t_f64 x, t_f64 y);
#define c_f64mod			F64_Mod

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Mod(t_f80 x, t_f80 y);
#define c_f80mod			F80_Mod
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Mod(t_f128 x, t_f128 y);
#define c_f128mod			F128_Mod
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/remainder}
*/
//!@{
#define						Float_Rem	CONCAT(FLOAT_TYPE,_Rem)
#define c_frem				Float_Rem
#define c_fremainder		Float_Rem
#define Float_Remainder		Float_Rem

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Rem(t_f16 x, t_f16 y);
#define c_f16rem			F16_Rem
#define c_f16remainder		F16_Rem
#define F16_Remainder		F16_Rem
#endif
t_f32						F32_Rem(t_f32 x, t_f32 y);
#define c_f32rem			F32_Rem
#define c_f32remainder		F32_Rem
#define F32_Remainder		F32_Rem

t_f64						F64_Rem(t_f64 x, t_f64 y);
#define c_f64rem			F64_Rem
#define c_f64remainder		F64_Rem
#define F64_Remainder		F64_Rem

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Rem(t_f80 x, t_f80 y);
#define c_f80rem			F80_Rem
#define c_f80remainder		F80_Rem
#define F80_Remainder		F80_Rem
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Rem(t_f128 x, t_f128 y);
#define c_f128rem			F128_Rem
#define c_f128remainder		F128_Rem
#define F128_Remainder		F128_Rem
#endif
//!@}



//!@doc Returns the remainder and quotient of euclidian division of `x` by `y`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/remquo}
*/
//!@{
#define							Float_RemQuo	CONCAT(FLOAT_TYPE,_RemQuo)
#define c_fremquo				Float_RemQuo
#define Float_RemainderQuotient	Float_RemQuo

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_RemQuo(t_f16 x, t_f16 y, t_sint* quotient);
#define c_f16remquo			F16_RemQuo
#endif
t_f32						F32_RemQuo(t_f32 x, t_f32 y, t_sint* quotient);
#define c_f32remquo			F32_RemQuo

t_f64						F64_RemQuo(t_f64 x, t_f64 y, t_sint* quotient);
#define c_f64remquo			F64_RemQuo

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_RemQuo(t_f80 x, t_f80 y, t_sint* quotient);
#define c_f80remquo			F80_RemQuo
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_RemQuo(t_f128 x, t_f128 y, t_sint* quotient);
#define c_f128remquo		F128_RemQuo
#endif
//!@}



/*============================================================================*\
||                        Floating-point math operators                       ||
\*============================================================================*/



//!@doc Returns the value of `x` to the power of `y` (float)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/pow}
*/
//!@{
#define						Float_Pow	CONCAT(FLOAT_TYPE,_Pow)
#define c_fpow				Float_Pow
#define Float_Power			Float_Pow

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Pow(t_f16 x, t_f16 y);
#define c_f16pow			F16_Pow
#endif
t_f32						F32_Pow(t_f32 x, t_f32 y);
#define c_f32pow			F32_Pow

t_f64						F64_Pow(t_f64 x, t_f64 y);
#define c_f64pow			F64_Pow

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Pow(t_f80 x, t_f80 y);
#define c_f80pow			F80_Pow
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Pow(t_f128 x, t_f128 y);
#define c_f128pow			F128_Pow
#endif
//!@}



//!@doc Returns the square root of `x` (inverse of power of 2)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sqrt}
*/
//!@{
#define						Float_Root2	CONCAT(FLOAT_TYPE,_Root2)
#define c_fsqrt				Float_Root2
#define c_froot2			Float_Root2
#define Float_SqRt			Float_Root2
#define Float_SquareRoot	Float_Root2

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Root2(t_f16 x);
#define c_f16sqrt			F16_Root2
#define c_f16root2			F16_Root2
#endif
t_f32						F32_Root2(t_f32 x);
#define c_f32sqrt			F32_Root2
#define c_f32root2			F32_Root2

t_f64						F64_Root2(t_f64 x);
#define c_f64sqrt			F64_Root2
#define c_f64root2			F64_Root2

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Root2(t_f80 x);
#define c_f80sqrt			F80_Root2
#define c_f80root2			F80_Root2
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Root2(t_f128 x);
#define c_f128sqrt			F128_Root2
#define c_f128root2			F128_Root2
#endif
//!@}

//!@doc Returns the cubic root of `x` (inverse of power of 3)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cbrt}
*/
//!@{
#define						Float_Root3	CONCAT(FLOAT_TYPE,_Root3)
#define c_fcbrt				Float_Root3
#define c_froot3			Float_Root3
#define Float_CbRt			Float_Root3
#define Float_CubeRoot		Float_Root3

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Root3(t_f16 x);
#define c_f16cbrt			F16_Root3
#define c_f16root3			F16_Root3
#endif
t_f32						F32_Root3(t_f32 x);
#define c_f32cbrt			F32_Root3
#define c_f32root3			F32_Root3

t_f64						F64_Root3(t_f64 x);
#define c_f64cbrt			F64_Root3
#define c_f64root3			F64_Root3

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Root3(t_f80 x);
#define c_f80cbrt			F80_Root3
#define c_f80root3			F80_Root3
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Root3(t_f128 x);
#define c_f128cbrt			F128_Root3
#define c_f128root3			F128_Root3
#endif
//!@}

//!@doc Returns the n-ic root of `x` (inverse of power of `n`)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/nrt}
*/
//!@{
#define						Float_RootN	CONCAT(FLOAT_TYPE,_RootN)
#define c_fnrt				Float_RootN
#define c_frootn			Float_RootN
#define Float_NRt			Float_RootN
#define Float_NRoot			Float_RootN

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_RootN(t_f16 x, t_u8 n);
#define c_f16nrt			F16_RootN
#define c_f16rootn			F16_RootN
#endif
t_f32						F32_RootN(t_f32 x, t_u8 n);
#define c_f32nrt			F32_RootN
#define c_f32rootn			F32_RootN

t_f64						F64_RootN(t_f64 x, t_u8 n);
#define c_f64nrt			F64_RootN
#define c_f64rootn			F64_RootN

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_RootN(t_f80 x, t_u8 n);
#define c_f80nrt			F80_RootN
#define c_f80rootn			F80_RootN
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_RootN(t_f128 x, t_u8 n);
#define c_f128nrt			F128_RootN
#define c_f128rootn			F128_RootN
#endif
//!@}



//!@doc Computes the square root of the sum of the squares of `x` and `y`, without undue overflow or underflow at intermediate stages of the computation.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/hypot}
**
**	- Math: @f$ {\sqrt{x^2+y^2}} @f$
*/
//!@{
#define						Float_Hypotenuse	CONCAT(FLOAT_TYPE,_Hypotenuse)
#define c_fhypot			Float_Hypotenuse
#define Float_Hypot			Float_Hypotenuse

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Hypotenuse(t_f16 x, t_f16 y);
#define c_f16hypot			F16_Hypotenuse
#endif
t_f32						F32_Hypotenuse(t_f32 x, t_f32 y);
#define c_f32hypot			F32_Hypotenuse

t_f64						F64_Hypotenuse(t_f64 x, t_f64 y);
#define c_f64hypot			F64_Hypotenuse

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Hypotenuse(t_f80 x, t_f80 y);
#define c_f80hypot			F80_Hypotenuse
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Hypotenuse(t_f128 x, t_f128 y);
#define c_f128hypot			F128_Hypotenuse
#endif
//!@}



/*============================================================================*\
||                           Exponentiation Operations                        ||
\*============================================================================*/



//!@doc Returns the exponential function's value for `x`, i.e. `e^x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/exp}
*/
//!@{
#define							Float_Exp	CONCAT(FLOAT_TYPE,_Exp)
#define c_fexp					Float_Exp
#define Float_Exponential		Float_Exp

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Exp(t_f16 x);
#define c_f16exp				F16_Exp
#endif
t_f32							F32_Exp(t_f32 x);
#define c_f32exp				F32_Exp

t_f64							F64_Exp(t_f64 x);
#define c_f64exp				F64_Exp

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Exp(t_f80 x);
#define c_f80exp				F80_Exp
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Exp(t_f128 x);
#define c_f128exp				F128_Exp
#endif
//!@}

//!@doc Returns the value of `2^x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/exp2}
*/
//!@{
#define							Float_Exp2	CONCAT(FLOAT_TYPE,_Exp2)
#define c_fexp2					Float_Exp2
#define c_fpow2					Float_Exp2
#define Float_Pow2				Float_Exp2

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Exp2(t_f16 x);
#define c_f16exp2				F16_Exp2
#define c_f16pow2				F16_Exp2
#endif
t_f32							F32_Exp2(t_f32 x);
#define c_f32exp2				F32_Exp2
#define c_f32pow2				F32_Exp2

t_f64							F64_Exp2(t_f64 x);
#define c_f64exp2				F64_Exp2
#define c_f64pow2				F32_Exp2

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Exp2(t_f80 x);
#define c_f80exp2				F80_Exp2
#define c_f80pow2				F80_Exp2
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Exp2(t_f128 x);
#define c_f128exp2				F128_Exp2
#define c_f128pow2				F128_Exp2
#endif
//!@}

//!@doc Returns the value of `10^x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/exp10}
*/
//!@{
#define							Float_Exp10	CONCAT(FLOAT_TYPE,_Exp10)
#define c_fexp10				Float_Exp10
#define c_fpow10				Float_Exp10
#define Float_Pow10				Float_Exp10

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Exp10(t_f16 x);
#define c_f16exp10				F16_Exp10
#define c_f16pow10				F16_Exp10
#endif
t_f32							F32_Exp10(t_f32 x);
#define c_f32exp10				F32_Exp10
#define c_f32pow10				F32_Exp10

t_f64							F64_Exp10(t_f64 x);
#define c_f64exp10				F64_Exp10
#define c_f64pow10				F32_Exp10

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Exp10(t_f80 x);
#define c_f80exp10				F80_Exp10
#define c_f80pow10				F80_Exp10
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Exp10(t_f128 x);
#define c_f128exp10				F128_Exp10
#define c_f128pow10				F128_Exp10
#endif
//!@}



//!@doc Returns the natural logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log}
*/
//!@{
#define							Float_Log	CONCAT(FLOAT_TYPE,_Ln)
#define c_flog					Float_Log
#define c_fln					Float_Log
#define Float_Ln				Float_Log
#define Float_NaturalLog		Float_Log
#define Float_NaturalLogarithm	Float_Log

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Log(t_f16 x);
#define c_f16log				F16_Log
#define c_f16ln					F16_Log
#define F16_Ln					F16_Log
#endif
t_f32							F32_Log(t_f32 x);
#define c_f32log				F32_Log
#define c_f32ln					F32_Log
#define F32_Ln					F32_Log

t_f64							F64_Log(t_f64 x);
#define c_f64log				F64_Log
#define c_f64ln					F64_Log
#define F64_Ln					F64_Log

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Log(t_f80 x);
#define c_f80log				F80_Log
#define c_f80ln					F80_Log
#define F80_Ln					F80_Log
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Log(t_f128 x);
#define c_f128log				F128_Log
#define c_f128ln				F128_Log
#define F128_Ln					F128_Log
#endif
//!@}

//!@doc Returns the binary (base-2) logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log2}
*/
//!@{
#define							Float_Log2	CONCAT(FLOAT_TYPE,_Log2)
#define c_flg					Float_Log2
#define c_flog2					Float_Log2
#define Float_Base2Log			Float_Log2
#define Float_Logarithm_Base2	Float_Log2

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Log2(t_f16 x);
#define c_f16lg					F16_Log2
#define c_f16log2				F16_Log2
#endif
t_f32							F32_Log2(t_f32 x);
#define c_f32lg					F32_Log2
#define c_f32log2				F32_Log2

t_f64							F64_Log2(t_f64 x);
#define c_f64lg					F64_Log2
#define c_f64log2				F64_Log2

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Log2(t_f80 x);
#define c_f80lg					F80_Log2
#define c_f80log2				F80_Log2
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Log2(t_f128 x);
#define c_f128lg				F128_Log2
#define c_f128log2				F128_Log2
#endif
//!@}

//!@doc Returns the decimal (base-10) logarithm of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/log10}
*/
//!@{
#define							Float_Log10	CONCAT(FLOAT_TYPE,_Log10)
#define c_flog10				Float_Log10
#define Float_Base10Log			Float_Log10
#define Float_Logarithm_Base10	Float_Log10

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Log10(t_f16 x);
#define c_f16log10				F16_Log10
#endif
t_f32							F32_Log10(t_f32 x);
#define c_f32log10				F32_Log10

t_f64							F64_Log10(t_f64 x);
#define c_f64log10				F64_Log10

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Log10(t_f80 x);
#define c_f80log10				F80_Log10
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Log10(t_f128 x);
#define c_f128log10				F128_Log10
#endif
//!@}

//!@doc Returns the base-`n` logarithm of `x`
/*!
**	@nonstd
*/
//!@{
#define							Float_LogN	CONCAT(FLOAT_TYPE,_LogN)
#define c_flogn					Float_LogN
#define Float_BaseNLog			Float_LogN
#define Float_Logarithm_BaseN	Float_LogN

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_LogN(t_f16 x, t_f16 n);
#define c_f16logn				F16_LogN
#define c_flognl				F16_LogN
#endif
t_f32							F32_LogN(t_f32 x, t_f32 n);
#define c_f32logn				F32_LogN
#define c_flognf				F32_LogN

t_f64							F64_LogN(t_f64 x, t_f64 n);
#define c_f64logn				F64_LogN
#define c_flognd				F64_LogN

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_LogN(t_f80 x, t_f80 n);
#define c_f80logn				F80_LogN
#define c_flognl				F80_LogN
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_LogN(t_f128 x, t_f128 n);
#define c_f128logn				F128_LogN
#define c_flognl				F128_LogN
#endif
//!@}



//!@doc Returns the error function value `erf(x)` for `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/erf}
**
**	- Math: @f$ {erf(z) = \frac{2}{\sqrt{\pi}} \(\int_{0}^{z} e^{-t^2} \,dt\)} @f$
*/
//!@{
#define							Float_Erf	CONCAT(FLOAT_TYPE,_Erf)
#define c_ferf					Float_Erf
#define Float_ErrorFunction		Float_Erf

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Erf(t_f16 x);
#define c_f16erf				F16_Erf
#define c_erfl					F16_Erf
#endif
t_f32							F32_Erf(t_f32 x);
#define c_f32erf				F32_Erf
#define c_erff					F32_Erf

t_f64							F64_Erf(t_f64 x);
#define c_f64erf				F64_Erf
#define c_erfd					F64_Erf

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Erf(t_f80 x);
#define c_f80erf				F80_Erf
#define c_erfl					F80_Erf
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Erf(t_f128 x);
#define c_f128erf				F128_Erf
#define c_erfl					F128_Erf
#endif
//!@}

//!@doc Returns the complementary error function value `erf(x)` for the given `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/erfc}
**
**	- Math: @f$ {1 - erf(z) = 1 - ( \frac{2}{\sqrt{\pi}} \(\int_{0}^{z} e^{-t^2} \,dt\) )} @f$
*/
//!@{
#define							Float_ErfC	CONCAT(FLOAT_TYPE,_ErfC)
#define c_ferfc					Float_ErfC
#define Float_ErrorFunctionComplement	Float_ErfC

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_ErfC(t_f16 x);
#define c_f16erfc				F16_ErfC
#define c_erfcl					F16_ErfC
#endif
t_f32							F32_ErfC(t_f32 x);
#define c_f32erfc				F32_ErfC
#define c_erfcf					F32_ErfC

t_f64							F64_ErfC(t_f64 x);
#define c_f64erfc				F64_ErfC
#define c_erfcd					F64_ErfC

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_ErfC(t_f80 x);
#define c_f80erfc				F80_ErfC
#define c_erfcl					F80_ErfC
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_ErfC(t_f128 x);
#define c_f128erfc				F128_ErfC
#define c_erfcl					F128_ErfC
#endif
//!@}



//!@doc Returns the gamma function value `Γ(x)` for the given `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tgamma}
**
**	- Math: @f$ {\Gamma(x) = \int_{0}^{\infty} t^{x-1}e^{-t} \,dt} @f$
*/
//!@{
#define							Float_Gamma	CONCAT(FLOAT_TYPE,_Gamma)
#define c_fgamma				Float_Gamma
#define c_ftgamma				Float_Gamma

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_Gamma(t_f16 x);
#define c_f16gamma				F16_Gamma
#define c_gammal				F16_Gamma
#define c_tgammal				F16_Gamma
#endif
t_f32							F32_Gamma(t_f32 x);
#define c_f32gamma				F32_Gamma
#define c_gammaf				F32_Gamma
#define c_tgammaf				F32_Gamma

t_f64							F64_Gamma(t_f64 x);
#define c_f64gamma				F64_Gamma
#define c_gammad				F64_Gamma
#define c_tgammad				F64_Gamma

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_Gamma(t_f80 x);
#define c_f80gamma				F80_Gamma
#define c_gammal				F80_Gamma
#define c_tgammal				F80_Gamma
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_Gamma(t_f128 x);
#define c_f128gamma				F128_Gamma
#define c_gammal				F128_Gamma
#define c_tgammal				F128_Gamma
#endif
//!@}

//!@doc Returns the natural logarithm of the absolute value of the gamma function value `ln(|Γ(x)|)` for the given `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/lgamma}
**
**	- Math: @f$ {\log_{e} | \Gamma(x) | = \log_{e} | \int_{0}^{\infty} t^{x-1}e^{-t} \,dt |} @f$
*/
//!@{
#define							Float_LnGamma	CONCAT(FLOAT_TYPE,_LnGamma)
#define c_flngamma				Float_LnGamma
#define c_flgamma				Float_LnGamma

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_LnGamma(t_f16 x);
#define c_f16lngamma			F16_LnGamma
#define c_lgammal				F16_LnGamma
#endif
t_f32							F32_LnGamma(t_f32 x);
#define c_f32lngamma			F32_LnGamma
#define c_lgammaf				F32_LnGamma

t_f64							F64_LnGamma(t_f64 x);
#define c_f64lngamma			F64_LnGamma
#define c_lgammad				F64_LnGamma

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_LnGamma(t_f80 x);
#define c_f80lngamma			F80_LnGamma
#define c_lgammal				F80_LnGamma
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_LnGamma(t_f128 x);
#define c_f128lngamma			F128_LnGamma
#define c_lgammal				F128_LnGamma
#endif
//!@}



/*============================================================================*\
||                           Trigonometric Operations                         ||
\*============================================================================*/



//!@doc Returns the sine of `x` (vertical trigonometry coordinate)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sin}
*/
//!@{
#define						Float_Sin	CONCAT(FLOAT_TYPE,_Sin)
#define c_fsin				Float_Sin
#define Float_Sine			Float_Sin

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Sin(t_f16 x);
#define c_f16sin			F16_Sin
#define c_sinl				F16_Sin
#endif
t_f32						F32_Sin(t_f32 x);
#define c_f32sin			F32_Sin
#define c_sinf				F32_Sin

t_f64						F64_Sin(t_f64 x);
#define c_f64sin			F64_Sin
#define c_sind				F64_Sin

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Sin(t_f80 x);
#define c_f80sin			F80_Sin
#define c_sinl				F80_Sin
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Sin(t_f128 x);
#define c_f128sin			F128_Sin
#define c_sinl				F128_Sin
#endif
//!@}

//!@doc Returns the cosine of `x` (horizontal trigonometry coordinate)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cos}
*/
//!@{
#define						Float_Cos	CONCAT(FLOAT_TYPE,_Cos)
#define c_fcos				Float_Cos
#define Float_Cosine		Float_Cos

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Cos(t_f16 x);
#define c_f16cos			F16_Cos
#define c_cosl				F16_Cos
#endif
t_f32						F32_Cos(t_f32 x);
#define c_f32cos			F32_Cos
#define c_cosf				F32_Cos

t_f64						F64_Cos(t_f64 x);
#define c_f64cos			F64_Cos
#define c_cosd				F64_Cos

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Cos(t_f80 x);
#define c_f80cos			F80_Cos
#define c_cosl				F80_Cos
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Cos(t_f128 x);
#define c_f128cos			F128_Cos
#define c_cosl				F128_Cos
#endif
//!@}

//!@doc Returns the tangent of `x` (trigonometry tangent line)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tan}
*/
//!@{
#define						Float_Tan	CONCAT(FLOAT_TYPE,_Tan)
#define c_ftan				Float_Tan
#define Float_Tangent		Float_Tan

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_Tan(t_f16 x);
#define c_f16tan			F16_Tan
#define c_tanl				F16_Tan
#endif
t_f32						F32_Tan(t_f32 x);
#define c_f32tan			F32_Tan
#define c_tanf				F32_Tan

t_f64						F64_Tan(t_f64 x);
#define c_f64tan			F64_Tan
#define c_tand				F64_Tan

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_Tan(t_f80 x);
#define c_f80tan			F80_Tan
#define c_tanl				F80_Tan
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_Tan(t_f128 x);
#define c_f128tan			F128_Tan
#define c_tanl				F128_Tan
#endif
//!@}



//!@doc Returns the arc-sine of `x` (inverse of the sin function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/asin}
*/
//!@{
#define						Float_ArcSin	CONCAT(FLOAT_TYPE,_ArcSin)
#define c_fasin				Float_ArcSin
#define Float_Sin_1			Float_ArcSin
#define Float_ArcSine		Float_ArcSin
#define Float_InvSine		Float_ArcSin

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_ArcSin(t_f16 x);
#define c_f16asin			F16_ArcSin
#define c_asinl				F16_ArcSin
#endif
t_f32						F32_ArcSin(t_f32 x);
#define c_f32asin			F32_ArcSin
#define c_asinf				F32_ArcSin

t_f64						F64_ArcSin(t_f64 x);
#define c_f64asin			F64_ArcSin
#define c_asind				F64_ArcSin

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_ArcSin(t_f80 x);
#define c_f80asin			F80_ArcSin
#define c_asinl				F80_ArcSin
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_ArcSin(t_f128 x);
#define c_f128asin			F128_ArcSin
#define c_asinl				F128_ArcSin
#endif
//!@}

//!@doc Returns the arc-cosine of `x` (inverse of the cos function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/acos}
*/
//!@{
#define						Float_ArcCos	CONCAT(FLOAT_TYPE,_ArcCos)
#define c_facos				Float_ArcCos
#define Float_Cos_1			Float_ArcCos
#define Float_ArcCosine		Float_ArcCos
#define Float_InvCosine		Float_ArcCos

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_ArcCos(t_f16 x);
#define c_f16acos			F16_ArcCos
#define c_acosl				F16_ArcCos
#endif
t_f32						F32_ArcCos(t_f32 x);
#define c_f32acos			F32_ArcCos
#define c_acosf				F32_ArcCos

t_f64						F64_ArcCos(t_f64 x);
#define c_f64acos			F64_ArcCos
#define c_acosd				F64_ArcCos

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_ArcCos(t_f80 x);
#define c_f80acos			F80_ArcCos
#define c_acosl				F80_ArcCos
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_ArcCos(t_f128 x);
#define c_f128acos			F128_ArcCos
#define c_acosl				F128_ArcCos
#endif
//!@}

//!@doc Returns the arc-tangent of `x` (inverse of the tan function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atan}
*/
//!@{
#define						Float_ArcTan	CONCAT(FLOAT_TYPE,_ArcTan)
#define c_fatan				Float_ArcTan
#define Float_Tan_1			Float_ArcTan
#define Float_ArcTangent	Float_ArcTan
#define Float_InvTangent	Float_ArcTan

#if LIBCONFIG_USE_FLOAT16
t_f16						F16_ArcTan(t_f16 x);
#define c_f16atan			F16_ArcTan
#define c_atanl				F16_ArcTan
#endif
t_f32						F32_ArcTan(t_f32 x);
#define c_f32atan			F32_ArcTan
#define c_atanf				F32_ArcTan

t_f64						F64_ArcTan(t_f64 x);
#define c_f64atan			F64_ArcTan
#define c_atand				F64_ArcTan

#if LIBCONFIG_USE_FLOAT80
t_f80						F80_ArcTan(t_f80 x);
#define c_f80atan			F80_ArcTan
#define c_atanl				F80_ArcTan
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128						F128_ArcTan(t_f128 x);
#define c_f128atan			F128_ArcTan
#define c_atanl				F128_ArcTan
#endif
//!@}



//!@doc Returns the arc-tangent of (`y` / `x`), used to find an angle from coordinates
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atan2}
*/
//!@{
#define							Float_ArcTan2	CONCAT(FLOAT_TYPE,_ArcTan2)
#define c_fatan2				Float_ArcTan2
#define Float_ArcTan_YoverX		Float_ArcTan2
#define Float_ArcTangent2		Float_ArcTan2
#define Float_ArcTangent_YoverX	Float_ArcTan2
#define Float_InvTan_YoverX		Float_ArcTan2
#define Float_InvTangent2		Float_ArcTan2
#define Float_InvTangent_YoverX	Float_ArcTan2

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_ArcTan2(t_f16 y, t_f16 x);
#define c_f16atan2				F16_ArcTan2
#define c_atan2l				F16_ArcTan2
#endif
t_f32							F32_ArcTan2(t_f32 y, t_f32 x);
#define c_f32atan2				F32_ArcTan2
#define c_atan2f				F32_ArcTan2

t_f64							F64_ArcTan2(t_f64 y, t_f64 x);
#define c_f64atan2				F64_ArcTan2
#define c_atan2d				F64_ArcTan2

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_ArcTan2(t_f80 y, t_f80 x);
#define c_f80atan2				F80_ArcTan2
#define c_atan2l				F80_ArcTan2
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_ArcTan2(t_f128 y, t_f128 x);
#define c_f128atan2				F128_ArcTan2
#define c_atan2l				F128_ArcTan2
#endif
//!@}



/*============================================================================*\
||                           Hyperbolic Trigonometry                          ||
\*============================================================================*/

//!@doc Returns the hyperbolic sine of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/sinh}
*/
//!@{
#define							Float_SinH	CONCAT(FLOAT_TYPE,_SinH)
#define c_fsinh					Float_SinH
#define Float_Sin_H				Float_SinH
#define Float_Sine_Hyperbolic	Float_SinH

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_SinH(t_f16 x);
#define c_f16sinh				F16_SinH
#define c_sinhl					F16_SinH
#endif
t_f32							F32_SinH(t_f32 x);
#define c_f32sinh				F32_SinH
#define c_sinhf					F32_SinH

t_f64							F64_SinH(t_f64 x);
#define c_f64sinh				F64_SinH
#define c_sinhd					F64_SinH

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_SinH(t_f80 x);
#define c_f80sinh				F80_SinH
#define c_sinhl					F80_SinH
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_SinH(t_f128 x);
#define c_f128sinh				F128_SinH
#define c_sinhl					F128_SinH
#endif
//!@}

//!@doc Returns the hyperbolic cosine of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/cosh}
*/
//!@{
#define							Float_CosH	CONCAT(FLOAT_TYPE,_CosH)
#define c_fcosh					Float_CosH
#define Float_Cos_H				Float_CosH
#define Float_Cosine_Hyperbolic	Float_CosH

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_CosH(t_f16 x);
#define c_f16cosh				F16_CosH
#define c_coshl					F16_CosH
#endif
t_f32							F32_CosH(t_f32 x);
#define c_f32cosh				F32_CosH
#define c_coshf					F32_CosH

t_f64							F64_CosH(t_f64 x);
#define c_f64cosh				F64_CosH
#define c_coshd					F64_CosH

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_CosH(t_f80 x);
#define c_f80cosh				F80_CosH
#define c_coshl					F80_CosH
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_CosH(t_f128 x);
#define c_f128cosh				F128_CosH
#define c_coshl					F128_CosH
#endif
//!@}

//!@doc Returns the hyperbolic tangent of `x`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/tanh}
*/
//!@{
#define								Float_TanH	CONCAT(FLOAT_TYPE,_TanH)
#define c_ftanh						Float_TanH
#define Float_Tan_H					Float_TanH
#define Float_Tangent_Hyperbolic	Float_TanH

#if LIBCONFIG_USE_FLOAT16
t_f16							F16_TanH(t_f16 x);
#define c_f16tanh				F16_TanH
#define c_tanhl					F16_TanH
#endif
t_f32							F32_TanH(t_f32 x);
#define c_f32tanh				F32_TanH
#define c_tanhf					F32_TanH

t_f64							F64_TanH(t_f64 x);
#define c_f64tanh				F64_TanH
#define c_tanhd					F64_TanH

#if LIBCONFIG_USE_FLOAT80
t_f80							F80_TanH(t_f80 x);
#define c_f80tanh				F80_TanH
#define c_tanhl					F80_TanH
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128							F128_TanH(t_f128 x);
#define c_f128tanh				F128_TanH
#define c_tanhl					F128_TanH
#endif
//!@}



//!@doc Returns the hyperbolic arc-sine of `x` (inverse of the sinh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/asinh}
*/
//!@{
#define								Float_InvSinH	CONCAT(FLOAT_TYPE,_InvSinH)
#define c_fasinh					Float_InvSinH
#define Float_Sin_1_H				Float_InvSinH
#define Float_InvSine_Hyperbolic	Float_InvSinH

#if LIBCONFIG_USE_FLOAT16
t_f16								F16_InvSinH(t_f16 x);
#define c_f16asinh					F16_InvSinH
#define c_asinhl					F16_InvSinH
#endif
t_f32								F32_InvSinH(t_f32 x);
#define c_f32asinh					F32_InvSinH
#define c_asinhf					F32_InvSinH

t_f64								F64_InvSinH(t_f64 x);
#define c_f64asinh					F64_InvSinH
#define c_asinhd					F64_InvSinH

#if LIBCONFIG_USE_FLOAT80
t_f80								F80_InvSinH(t_f80 x);
#define c_f80asinh					F80_InvSinH
#define c_asinhl					F80_InvSinH
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128								F128_InvSinH(t_f128 x);
#define c_f128asinh					F128_InvSinH
#define c_asinhl					F128_InvSinH
#endif
//!@}

//!@doc Returns the hyperbolic arc-cosine of `x` (inverse of the cosh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/acosh}
*/
//!@{
#define								Float_InvCosH	CONCAT(FLOAT_TYPE,_InvCosH)
#define c_facosh					Float_InvCosH
#define Float_Cos_1_H				Float_InvCosH
#define Float_InvCosine_Hyperbolic	Float_InvCosH

#if LIBCONFIG_USE_FLOAT16
t_f16								F16_InvCosH(t_f16 x);
#define c_f16acosh					F16_InvCosH
#define c_acoshl					F16_InvCosH
#endif
t_f32								F32_InvCosH(t_f32 x);
#define c_f32acosh					F32_InvCosH
#define c_acoshf					F32_InvCosH

t_f64								F64_InvCosH(t_f64 x);
#define c_f64acosh					F64_InvCosH
#define c_acoshd					F64_InvCosH

#if LIBCONFIG_USE_FLOAT80
t_f80								F80_InvCosH(t_f80 x);
#define c_f80acosh					F80_InvCosH
#define c_acoshl					F80_InvCosH
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128								F128_InvCosH(t_f128 x);
#define c_f128acosh					F128_InvCosH
#define c_acoshl					F128_InvCosH
#endif
//!@}

//!@doc Returns the hyperbolic arc-tangent of `x` (inverse of the tanh function)
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/numeric/math/atanh}
*/
//!@{
#define								Float_InvTanH	CONCAT(FLOAT_TYPE,_InvTanH)
#define c_fatanh					Float_InvTanH
#define Float_Tan_1_H				Float_InvTanH
#define Float_InvTangent_Hyperbolic	Float_InvTanH

#if LIBCONFIG_USE_FLOAT16
t_f16								F16_InvTanH(t_f16 x);
#define c_f16atanh					F16_InvTanH
#define c_atanhl					F16_InvTanH
#endif
t_f32								F32_InvTanH(t_f32 x);
#define c_f32atanh					F32_InvTanH
#define c_atanhf					F32_InvTanH

t_f64								F64_InvTanH(t_f64 x);
#define c_f64atanh					F64_InvTanH
#define c_atanhd					F64_InvTanH

#if LIBCONFIG_USE_FLOAT80
t_f80								F80_InvTanH(t_f80 x);
#define c_f80atanh					F80_InvTanH
#define c_atanhl					F80_InvTanH
#endif
#if LIBCONFIG_USE_FLOAT128
t_f128								F128_InvTanH(t_f128 x);
#define c_f128atanh					F128_InvTanH
#define c_atanhl					F128_InvTanH
#endif
//!@}



/*============================================================================*\
||                           Other private utilities                          ||
\*============================================================================*/

#if !LIBCONFIG_USE_STD_MATH

#ifdef __GNUC__
#define predict_true(x) __builtin_expect(!!(x), 1)
#define predict_false(x) __builtin_expect(x, 0)
#else
#define predict_true(x) (x)
#define predict_false(x) (x)
#endif
/* Support non-nearest rounding mode.  */
#define WANT_ROUNDING	1
/* Support signaling NaNs.  */
#define WANT_SNAN	0
/* apply SNaN config */
#if WANT_SNAN
#error "SNaN is unsupported"
#else
#define issignalingf_inline(x) 0
#define issignaling_inline(x) 0
#endif



#define GET_F16_WORD(word,d)	do { union { t_f16 f; t_u16 i; } __u;  __u.f = (d);  (word) = __u.i;                          } while (0)
#define GET_F32_WORD(word,d)	do { union { t_f32 f; t_u32 i; } __u;  __u.f = (d);  (word) = __u.i;                          } while (0)
#define GET_F64_WORD_HI(hi,d)	do { union { t_f64 f; t_u64 i; } __u;  __u.f = (d);  (hi) = __u.i >> 32;                      } while (0)
#define GET_F64_WORD_LO(lo,d)	do { union { t_f64 f; t_u64 i; } __u;  __u.f = (d);                      (lo) = (t_u32)__u.i; } while (0)
#define GET_F64_WORDS(hi,lo,d)	do { union { t_f64 f; t_u64 i; } __u;  __u.f = (d);  (hi) = __u.i >> 32; (lo) = (t_u32)__u.i; } while (0)

#define SET_F16_WORD(d,word)	do { union { t_f16 f; t_u16 i; } __u;  __u.i = (word);                                                             (d) = __u.f; } while (0)
#define SET_F32_WORD(d,word)	do { union { t_f32 f; t_u32 i; } __u;  __u.i = (word);                                                             (d) = __u.f; } while (0)
#define SET_F64_WORD_HI(d,hi)	do { union { t_f64 f; t_u64 i; } __u;  __u.f = (d);  __u.i &= 0xFFFFFFFF;             __u.i |= (t_u64)(hi) << 32;  (d) = __u.f; } while (0)
#define SET_F64_WORD_LO(d,lo)	do { union { t_f64 f; t_u64 i; } __u;  __u.f = (d);  __u.i &= 0xFFFFFFFF00000000ull;  __u.i |= (t_u32)(lo);        (d) = __u.f; } while (0)
#define SET_F64_WORDS(d,hi,lo)	do { union { t_f64 f; t_u64 i; } __u;  __u.i = ((t_u64)(hi)<<32) | (t_u32)(lo);                                    (d) = __u.f; } while (0)



float	__math_oflowf	(float x);
double	__math_oflow	(double x);

float	__math_uflowf	(float x);
double	__math_uflow	(double x);

float	__math_xflowf	(uint32_t sign, float y);
double	__math_xflow	(uint32_t sign, double y);

float	__math_divzerof (uint32_t sign);
double	__math_divzero  (uint32_t sign);

float		__math_invalidf	(float x);
double		__math_invalid	(double x);
long double	__math_invalidl	(long double x);



#if LIBCONFIG_USE_FLOAT80
union ldshape
{
	long double	f;
	struct { t_u64 mant; t_u16 se; }	i;
};
#elif LIBCONFIG_USE_FLOAT128
union ldshape
{
	long double	f;
	struct { t_u64 low; t_u32 mid; t_u16 top; t_u16 se; }	i;
	struct { t_u64 lo; t_u64 hi; }	i2;
};
#endif


/*
if x in [1,2): i = (int)(64*x);
if x in [2,4): i = (int)(32*x-64);
	__rsqrt_tab[i]*2^-16 is estimating 1/sqrt(x) with small relative error:
	|__rsqrt_tab[i]*0x1p-16*sqrt(x) - 1| < -0x1.fdp-9 < 2^-8
*/
extern const uint16_t __rsqrt_tab[128];

#define EXP_USE_TOINT_NARROW	0

t_sint	__rem_pi2_large(t_f64 *x, t_f64 *y, t_sint e0, t_sint nx, t_sint prec);
t_f32	__expo2_f32(t_f32 x, t_f32 sign);
t_f64	__expo2_f64(t_f64 x, t_f64 sign);



#if LIBCONFIG_USE_FLOAT16
#define TABLEBITS_EXP_F16	7
#define N_EXP_F16	(1 << TABLEBITS_EXP_F16)
struct data_exp_f16
{
	t_f16	ln2hi;
	t_f16	ln2lo;
	t_f16	log2e;
	t_f16	exp_poly_p[3];
	t_f16	exp_poly_q[4];
	t_f64	redux;
	t_f64	poly[7];
	t_f64	table[2*N_EXP_F16];
};
extern const	struct data_exp_f16	__data_exp_f16;

struct data_log_f16
{
	t_f16	P[7];
	t_f16	Q[6];
	t_f16	R[4];
	t_f16	S[4];
	t_f16	C1;
	t_f16	C2;
	t_f16	SQRTH;
};
extern const	struct data_log_f16	__data_log_f16;

t_f16	__sin_f16(t_f16 x, t_f16 y, int iy);
t_f16	__cos_f16(t_f16 x, t_f16 y);
t_f16	__tan_f16(t_f16 x, t_f16 y, t_bool odd);
t_sint	__rem_pi2_f16(t_f16 x, t_f16*  y);
t_f16	__polynomial_f16(t_f16 x, t_f16 const* coefficients, int n);
t_f16	__root2pN_f16(t_sint n);
t_f16	__inv_factorial_f16(t_uint n);
t_f16	__invtrig_polynomial_f16(t_f16 z);
#endif



#define TABLEBITS_EXP_F32	5
#define N_EXP_F32	(1 << TABLEBITS_EXP_F32)
struct data_exp_f32
{
	t_f64	shift;
	t_f64	shift_scaled;
	t_f64	invln2_scaled;
	t_f64	poly[3];
	t_f64	poly_scaled[3];
	t_u64	table[N_EXP_F32];
};
extern const	struct data_exp_f32	__data_exp_f32;

#define TABLEBITS_LOG_F32	4
#define N_LOG_F32	(1 << TABLEBITS_LOG_F32)
struct data_log_f32
{
	t_f64	ln2;
	t_f64	poly[3]; /* First order coefficient is 1.  */
	struct { t_f64 invc; t_f64 logc; }	table[N_LOG_F32];
};
extern const	struct data_log_f32 __data_log_f32;

t_f32	__sin_f32(t_f64 x);
t_f32	__cos_f32(t_f64 x);
t_f32	__tan_f32(t_f64 x, t_bool odd);
t_sint	__rem_pi2_f32(t_f32 x, t_f64*  y);
t_f32	__polynomial_f32(t_f32 x, t_f32 const* coefficients, int n);
t_f32	__root2pN_f32(t_sint n);
t_f32	__inv_factorial_f32(t_uint n);
t_f32	__invtrig_polynomial_f32(t_f32 z);



#define TABLEBITS_EXP_F64	7
#define N_EXP_F64	(1 << TABLEBITS_EXP_F64)
struct data_exp_f64
{
	t_f64	shift;
	t_f64	invln2N;
	t_f64	negln2hiN;
	t_f64	negln2loN;
	t_f64	poly[4]; /* Last four coefficients. */
	t_f64	exp_shift;
	t_f64	exp_poly[5];
	t_u64	table[2*N_EXP_F64];
};
extern const	struct data_exp_f64	__data_exp_f64;

#define TABLEBITS_LOG_F64	7
#define N_LOG_F64	(1 << TABLEBITS_LOG_F64)
struct data_log_f64
{
	t_f64	ln2hi;
	t_f64	ln2lo;
	t_f64	poly[6 - 1]; /* First coefficient is 1.  */
	t_f64	poly1[12 - 1];
	struct { t_f64 invc; t_f64 logc; } table[N_LOG_F64];
#if !__FP_FAST_FMA
	struct { t_f64 chi; t_f64 clo; } table2[N_LOG_F64];
#endif
};
extern const struct data_log_f64 __data_log_f64;

t_f64	__sin_f64(t_f64 x, t_f64 y, int iy);
t_f64	__cos_f64(t_f64 x, t_f64 y);
t_f64	__tan_f64(t_f64 x, t_f64 y, t_bool odd);
t_sint	__rem_pi2_f64(t_f64 x, t_f64*  y);
t_f64	__polynomial_f64(t_f64 x, t_f64 const* coefficients, int n);
t_f64	__root2pN_f64(t_sint n);
t_f64	__inv_factorial_f64(t_uint n);
t_f64	__invtrig_polynomial_f64(t_f64 z);



#if LIBCONFIG_USE_FLOAT80
#define TABLEBITS_EXP_F80	7
#define N_EXP_F80	(1 << TABLEBITS_EXP_F80)
struct data_exp_f80
{
	t_f80	ln2hi;
	t_f80	ln2lo;
	t_f80	log2e;
	t_f80	exp_poly_p[3];
	t_f80	exp_poly_q[4];
	t_f64	redux;
	t_f64	poly[7];
	t_f64	table[2*N_EXP_F80];
};
extern const	struct data_exp_f80	__data_exp_f80;

struct data_log_f80
{
	t_f80	P[7];
	t_f80	Q[6];
	t_f80	R[4];
	t_f80	S[4];
	t_f80	C1;
	t_f80	C2;
	t_f80	SQRTH;
};
extern const	struct data_log_f80	__data_log_f80;

t_f80	__sin_f80(t_f80 x, t_f80 y, int iy);
t_f80	__cos_f80(t_f80 x, t_f80 y);
t_f80	__tan_f80(t_f80 x, t_f80 y, t_bool odd);
t_sint	__rem_pi2_f80(t_f80 x, t_f80*  y);
t_f80	__polynomial_f80(t_f80 x, t_f80 const* coefficients, int n);
t_f80	__root2pN_f80(t_sint n);
t_f80	__inv_factorial_f80(t_uint n);
t_f80	__invtrig_polynomial_f80(t_f80 z);
#endif



#if LIBCONFIG_USE_FLOAT128
#define TABLEBITS_EXP_F128	7
#define N_EXP_F128	(1 << TABLEBITS_EXP_F128)
struct data_exp_f128
{
	t_f128	ln2hi;
	t_f128	ln2lo;
	t_f128	log2e;
	t_f128	exp_poly_p[3];
	t_f128	exp_poly_q[4];
	t_f64	redux;
	t_f128	poly[11];
	t_f128	table[N_EXP_F128];
	t_f32	eps[N_EXP_F128];
};
extern const	struct data_exp_f128	__data_exp_f128;

struct data_log_f128
{
	t_f128	P[7];
	t_f128	Q[6];
	t_f128	R[4];
	t_f128	S[4];
	t_f128	C1;
	t_f128	C2;
	t_f128	SQRTH;
};
extern const	struct data_log_f128	__data_log_f128;

t_f128	__sin_f128(t_f128 x, t_f128 y, int iy);
t_f128	__cos_f128(t_f128 x, t_f128 y);
t_f128	__tan_f128(t_f128 x, t_f128 y, t_bool odd);
t_sint	__rem_pi2_f128(t_f128 x, t_f128* y);
t_f128	__polynomial_f128(t_f128 x, t_f128 const* coefficients, int n);
t_f128	__root2pN_f128(t_sint n);
t_f128	__inv_factorial_f128(t_uint n);
t_f128	__invtrig_polynomial_f128(t_f128 z);
#endif



#endif



/*! @endgroup */
HEADER_END
#endif
