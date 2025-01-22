/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/int.h                        |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_INT_H
#define __LIBCCC_MATH_INT_H
/*!@group{libccc_math_int,51,libccc/math/int.h}
**
**	This header defines the common standard math functions for integer numbers.
**
**	@nonstd
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/int.h"

HEADER_CPP

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/



//!@doc The type of function which takes one number and outputs one number
//!@{
typedef		t_uint	(*f_uint_function)	(t_uint x);
typedef		t_sint	(*f_sint_function)	(t_sint x);

typedef		t_u16	(*f_u16_function)	(t_u16  x);
typedef		t_s16	(*f_s16_function)	(t_s16  x);

typedef		t_u32	(*f_u32_function)	(t_u32  x);
typedef		t_s32	(*f_s32_function)	(t_s32  x);

typedef		t_u64	(*f_u64_function)	(t_u64  x);
typedef		t_s64	(*f_s64_function)	(t_s64  x);

#if LIBCONFIG_USE_INT128
typedef		t_u128	(*f_u128_function)	(t_u128 x);
typedef		t_s128	(*f_s128_function)	(t_s128 x);
#endif
//!@}

//!@doc The type of function which takes two numbers and outputs one number
//!@{
typedef		t_uint	(*f_uint_operator)	(t_uint x, t_uint y);
typedef		t_sint	(*f_sint_operator)	(t_sint x, t_sint y);

typedef		t_u16	(*f_u16_operator)	(t_u16  x, t_u16  y);
typedef		t_s16	(*f_s16_operator)	(t_s16  x, t_s16  y);

typedef		t_u32	(*f_u32_operator)	(t_u32  x, t_u32  y);
typedef		t_s32	(*f_s32_operator)	(t_s32  x, t_s32  y);

typedef		t_u64	(*f_u64_operator)	(t_u64  x, t_u64  y);
typedef		t_s64	(*f_s64_operator)	(t_s64  x, t_s64  y);

#if LIBCONFIG_USE_INT128
typedef		t_u128	(*f_u128_operator)	(t_u128 x, t_u128 y);
typedef		t_s128	(*f_s128_operator)	(t_s128 x, t_s128 y);
#endif
//!@}



/*============================================================================*\
||                          Basic Fundamental Operations                      ||
\*============================================================================*/

//!@doc Returns `x` as-is (only useful when dealing with function pointers).
/*!
**	@nonstd
*/
//!@{
#define						UInt_Id	CONCAT(UINT_TYPE,_Id)
#define c_uid				UInt_Id
#define UInt_Identity		UInt_Id

t_s8						U8_Id(t_s8 x);
#define c_u8id				U8_Id

t_s16						U16_Id(t_s16 x);
#define c_u16id				U16_Id

t_s32						U32_Id(t_s32 x);
#define c_u32id				U32_Id

t_s64						U64_Id(t_s64 x);
#define c_u64id				U64_Id

#if LIBCONFIG_USE_INT128
t_s128						U128_Id(t_s128 x);
#define c_u128id			U128_Id
#endif

#define						SInt_Id	CONCAT(SINT_TYPE,_Id)
#define c_sid				SInt_Id

t_s8						S8_Id(t_s8 x);
#define c_s8id				S8_Id

t_s16						S16_Id(t_s16 x);
#define c_s16id				S16_Id

t_s32						S32_Id(t_s32 x);
#define c_s32id				S32_Id

t_s64						S64_Id(t_s64 x);
#define c_s64id				S64_Id

#if LIBCONFIG_USE_INT128
t_s128						S128_Id(t_s128 x);
#define c_s128id			S128_Id
#endif
//!@}



//!@doc Returns the absolute value of `x` (makes `x` positive)
/*!
**	@nonstd
*/
//!@{
#define						UInt_Abs	CONCAT(UINT_TYPE,_Abs)
#define c_uabs				UInt_Abs
#define UInt_AbsoluteValue	UInt_Abs

t_u8						U8_Abs(t_u8 x);
#define c_u8abs				U8_Abs

t_u16						U16_Abs(t_u16 x);
#define c_u16abs			U16_Abs

t_u32						U32_Abs(t_u32 x);
#define c_u32abs			U32_Abs

t_u64						U64_Abs(t_u64 x);
#define c_u64abs			U64_Abs

#if LIBCONFIG_USE_INT128
t_u128						U128_Abs(t_u128 x);
#define c_u128abs			U128_Abs
#endif

#define						SInt_Abs	CONCAT(SINT_TYPE,_Abs)
#define c_sabs				SInt_Abs
#define SInt_AbsoluteValue	SInt_Abs

t_s8						S8_Abs(t_s8 x);
#define c_s8abs				S8_Abs

t_s16						S16_Abs(t_s16 x);
#define c_s16abs			S16_Abs

t_s32						S32_Abs(t_s32 x);
#define c_s32abs			S32_Abs

t_s64						S64_Abs(t_s64 x);
#define c_s64abs			S64_Abs

#if LIBCONFIG_USE_INT128
t_s128						S128_Abs(t_s128 x);
#define c_s128abs			S128_Abs
#endif
//!@}



//!@doc Returns the sign value value of `x` (either `-1`, `0`, or `+1`)
/*!
**	@nonstd
*/
//!@{
#define						UInt_Sgn	CONCAT(UINT_TYPE,_Sgn)
#define c_usgn				UInt_Sgn
#define UInt_Sign			UInt_Sgn
#define UInt_SignOf			UInt_Sgn

t_u8						U8_Sgn(t_u8 x);
#define c_u8sgn				U8_Sgn

t_u16						U16_Sgn(t_u16 x);
#define c_u16sgn			U16_Sgn

t_u32						U32_Sgn(t_u32 x);
#define c_u32sgn			U32_Sgn

t_u64						U64_Sgn(t_u64 x);
#define c_u64sgn			U64_Sgn

#if LIBCONFIG_USE_INT128
t_u128						U128_Sgn(t_u128 x);
#define c_u128sgn			U128_Sgn
#endif

#define						SInt_Sgn	CONCAT(SINT_TYPE,_Sgn)
#define c_ssgn				SInt_Sgn
#define SInt_Sign			SInt_Sgn
#define SInt_SignOf			SInt_Sgn

t_s8						S8_Sgn(t_s8 x);
#define c_s8sgn				S8_Sgn

t_s16						S16_Sgn(t_s16 x);
#define c_s16sgn			S16_Sgn

t_s32						S32_Sgn(t_s32 x);
#define c_s32sgn			S32_Sgn

t_s64						S64_Sgn(t_s64 x);
#define c_s64sgn			S64_Sgn

#if LIBCONFIG_USE_INT128
t_s128						S128_Sgn(t_s128 x);
#define c_s128sgn			S128_Sgn
#endif
//!@}



/*============================================================================*\
||                           Basic kind-check functions                       ||
\*============================================================================*/



//!@doc Returns `TRUE` if the given number is NAN (not a number) (only useful when #LIBCONFIG_UINT_NAN is active).
/*!
**	@nonstd
*/
//!@{
#define						UInt_IsNaN	CONCAT(UINT_TYPE,_IsNaN)
#define c_uisnan			UInt_IsNaN

t_bool						U8_IsNaN(t_u8 x);
#define c_u8isnan			U8_IsNaN

t_bool						U16_IsNaN(t_u16 x);
#define c_u16isnan			U16_IsNaN

t_bool						U32_IsNaN(t_u32 x);
#define c_u32isnan			U32_IsNaN

t_bool						U64_IsNaN(t_u64 x);
#define c_u64isnan			U64_IsNaN

#if LIBCONFIG_USE_INT128
t_bool						U128_IsNaN(t_u128 x);
#define c_u128isnan			U128_IsNaN
#endif

#define						SInt_IsNaN	CONCAT(SINT_TYPE,_IsNaN)
#define c_sisnan			SInt_IsNaN

t_bool						S8_IsNaN(t_s8 x);
#define c_s8isnan			S8_IsNaN

t_bool						S16_IsNaN(t_s16 x);
#define c_s16isnan			S16_IsNaN

t_bool						S32_IsNaN(t_s32 x);
#define c_s32isnan			S32_IsNaN

t_bool						S64_IsNaN(t_s64 x);
#define c_s64isnan			S64_IsNaN

#if LIBCONFIG_USE_INT128
t_bool						S128_IsNaN(t_s128 x);
#define c_s128isnan			S128_IsNaN
#endif
//!@}



//!@doc Returns `TRUE` if the given number is infinite (only useful when #LIBCONFIG_UINT_INF is active).
/*!
**	@nonstd
*/
//!@{
#define						UInt_IsInf	CONCAT(UINT_TYPE,_IsInf)
#define c_uisinf			UInt_IsInf

t_bool						U8_IsInf(t_u8 x);
#define c_u8isinf			U8_IsInf

t_bool						U16_IsInf(t_u16 x);
#define c_u16isinf			U16_IsInf

t_bool						U32_IsInf(t_u32 x);
#define c_u32isinf			U32_IsInf

t_bool						U64_IsInf(t_u64 x);
#define c_u64isinf			U64_IsInf

#if LIBCONFIG_USE_INT128
t_bool						U128_IsInf(t_u128 x);
#define c_u128isinf			U128_IsInf
#endif

#define						SInt_IsInf	CONCAT(SINT_TYPE,_IsInf)
#define c_sisinf			SInt_IsInf

t_bool						S8_IsInf(t_s8 x);
#define c_s8isinf			S8_IsInf

t_bool						S16_IsInf(t_s16 x);
#define c_s16isinf			S16_IsInf

t_bool						S32_IsInf(t_s32 x);
#define c_s32isinf			S32_IsInf

t_bool						S64_IsInf(t_s64 x);
#define c_s64isinf			S64_IsInf

#if LIBCONFIG_USE_INT128
t_bool						S128_IsInf(t_s128 x);
#define c_s128isinf			S128_IsInf
#endif
//!@}



//!@doc Returns `TRUE` if the given number is a prime number.
/*!
**	@nonstd
*/
//!@{
#define						UInt_IsPrime	CONCAT(UINT_TYPE,_IsPrime)
#define c_uisprime			UInt_IsPrime

t_bool						U8_IsPrime(t_u8 x);
#define c_u8isprime			U8_IsPrime

t_bool						U16_IsPrime(t_u16 x);
#define c_u16isprime		U16_IsPrime

t_bool						U32_IsPrime(t_u32 x);
#define c_u32isprime		U32_IsPrime

t_bool						U64_IsPrime(t_u64 x);
#define c_u64isprime		U64_IsPrime

#if LIBCONFIG_USE_INT128
t_bool						U128_IsPrime(t_u128 x);
#define c_u128isprime		U128_IsPrime
#endif

#define						SInt_IsPrime	CONCAT(SINT_TYPE,_IsPrime)
#define c_sisprime			SInt_IsPrime

t_bool						S8_IsPrime(t_s8 x);
#define c_s8isprime			S8_IsPrime

t_bool						S16_IsPrime(t_s16 x);
#define c_s16isprime		S16_IsPrime

t_bool						S32_IsPrime(t_s32 x);
#define c_s32isprime		S32_IsPrime

t_bool						S64_IsPrime(t_s64 x);
#define c_s64isprime		S64_IsPrime

#if LIBCONFIG_USE_INT128
t_bool						S128_IsPrime(t_s128 x);
#define c_s128isprime		S128_IsPrime
#endif
//!@}



// TODO: implement PrimeFactors() function



/*============================================================================*\
||                            Comparison operators                            ||
\*============================================================================*/

//!@doc Returns `TRUE` if the 2 given integer values are exactly equal (operator: `==`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (exact) equality
**	@param	y	The second value to check for (exact) equality
**	@returns
**	`TRUE` if the 2 given integer values are exactly equal,
**	otherwise `FALSE`.
*/
//!@{
#define					UInt_Equals	CONCAT(UINT_TYPE,_Equals)
#define c_uequ			UInt_Equals

t_bool					U8_Equals(t_u8 x, t_u8 y);
#define c_u8equ			U8_Equals

t_bool					U16_Equals(t_u16 x, t_u16 y);
#define c_u16equ		U16_Equals

t_bool					U32_Equals(t_u32 x, t_u32 y);
#define c_u32equ		U32_Equals

t_bool					U64_Equals(t_u64 x, t_u64 y);
#define c_u64equ		U64_Equals

#if LIBCONFIG_USE_INT128
t_bool					U128_Equals(t_u128 x, t_u128 y);
#define c_u128equ		U128_Equals
#endif
//!@}

//!@doc Returns `TRUE` if the 2 given integer values are exactly equal (operator: `==`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (exact) equality
**	@param	y	The second value to check for (exact) equality
**	@returns
**	`TRUE` if the 2 given integer values are exactly equal,
**	otherwise `FALSE`.
*/
//!@{
#define					SInt_Equals	CONCAT(SINT_TYPE,_Equals)
#define c_sequ			SInt_Equals

t_bool					S8_Equals(t_s8 x, t_s8 y);
#define c_s8equ			S8_Equals

t_bool					S16_Equals(t_s16 x, t_s16 y);
#define c_s16equ		S16_Equals

t_bool					S32_Equals(t_s32 x, t_s32 y);
#define c_s32equ		S32_Equals

t_bool					S64_Equals(t_s64 x, t_s64 y);
#define c_s64equ		S64_Equals

#if LIBCONFIG_USE_INT128
t_bool					S128_Equals(t_s128 x, t_s128 y);
#define c_s128equ		S128_Equals
#endif
//!@}



//!@doc Returns `TRUE` if the 2 given integer values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (approximate) equality
**	@param	y	The second value to check for (approximate) equality
**	@returns
**	`TRUE` if the 2 given integer values are close enough to be considered equal
**	(using #SINT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					UInt_EqualsApprox	CONCAT(UINT_TYPE,_EqualsApprox)
#define c_uequa			UInt_EqualsApprox

t_bool					U8_EqualsApprox(t_u8 x, t_u8 y, t_u8 approx);
#define c_u8equa		U8_EqualsApprox

t_bool					U16_EqualsApprox(t_u16 x, t_u16 y, t_u16 approx);
#define c_u16equa		U16_EqualsApprox

t_bool					U32_EqualsApprox(t_u32 x, t_u32 y, t_u32 approx);
#define c_u32equa		U32_EqualsApprox

t_bool					U64_EqualsApprox(t_u64 x, t_u64 y, t_u64 approx);
#define c_u64equa		U64_EqualsApprox

#if LIBCONFIG_USE_INT128
t_bool					U128_EqualsApprox(t_u128 x, t_u128 y, t_u128 approx);
#define c_u128equa		U128_EqualsApprox
#endif
//!@}

//!@doc Returns `TRUE` if the 2 given integer values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (approximate) equality
**	@param	y	The second value to check for (approximate) equality
**	@param	approx	The tolerance margin for the approximate equality check
**	@returns
**	`TRUE` if the 2 given integer values are close enough to be considered equal
**	(using #SINT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					SInt_EqualsApprox	CONCAT(SINT_TYPE,_EqualsApprox)
#define c_sequa			SInt_EqualsApprox

t_bool					S8_EqualsApprox(t_s8 x, t_s8 y, t_s8 approx);
#define c_s8equa		S8_EqualsApprox

t_bool					S16_EqualsApprox(t_s16 x, t_s16 y, t_s16 approx);
#define c_s16equa		S16_EqualsApprox

t_bool					S32_EqualsApprox(t_s32 x, t_s32 y, t_s32 approx);
#define c_s32equa		S32_EqualsApprox

t_bool					S64_EqualsApprox(t_s64 x, t_s64 y, t_s64 approx);
#define c_s64equa		S64_EqualsApprox

#if LIBCONFIG_USE_INT128
t_bool					S128_EqualsApprox(t_s128 x, t_s128 y, t_s128 approx);
#define c_s128equa		S128_EqualsApprox
#endif
//!@}



//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value (operator: `<`)
//!@{
#define					UInt_LessThan	CONCAT(UINT_TYPE,_LessThan)
#define c_ult			UInt_LessThan

t_bool					U8_LessThan(t_u8 x, t_u8 y);
#define c_u8lt			U8_LessThan

t_bool					U16_LessThan(t_u16 x, t_u16 y);
#define c_u16lt			U16_LessThan

t_bool					U32_LessThan(t_u32 x, t_u32 y);
#define c_u32lt			U32_LessThan

t_bool					U64_LessThan(t_u64 x, t_u64 y);
#define c_u64lt			U64_LessThan

#if LIBCONFIG_USE_INT128
t_bool					U128_LessThan(t_u128 x, t_u128 y);
#define c_u128lt		U128_LessThan
#endif


#define					SInt_LessThan	CONCAT(SINT_TYPE,_LessThan)
#define c_slt			SInt_LessThan

t_bool					S8_LessThan(t_s8 x, t_s8 y);
#define c_s8lt			S8_LessThan

t_bool					S16_LessThan(t_s16 x, t_s16 y);
#define c_s16lt			S16_LessThan

t_bool					S32_LessThan(t_s32 x, t_s32 y);
#define c_s32lt			S32_LessThan

t_bool					S64_LessThan(t_s64 x, t_s64 y);
#define c_s64lt			S64_LessThan

#if LIBCONFIG_USE_INT128
t_bool					S128_LessThan(t_s128 x, t_s128 y);
#define c_s128lt		S128_LessThan
#endif
//!@}



//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value or equal to it (operator: `<=`)
//!@{
#define					UInt_LessThanOrEqual	CONCAT(UINT_TYPE,_LessThanOrEqual)
#define c_ulte			UInt_LessThanOrEqual

t_bool					U8_LessThanOrEqual(t_u8 x, t_u8 y);
#define c_u8lte			U8_LessThanOrEqual

t_bool					U16_LessThanOrEqual(t_u16 x, t_u16 y);
#define c_u16lte		U16_LessThanOrEqual

t_bool					U32_LessThanOrEqual(t_u32 x, t_u32 y);
#define c_u32lte		U32_LessThanOrEqual

t_bool					U64_LessThanOrEqual(t_u64 x, t_u64 y);
#define c_u64lte		U64_LessThanOrEqual

#if LIBCONFIG_USE_INT128
t_bool					U128_LessThanOrEqual(t_u128 x, t_u128 y);
#define c_u128lte		U128_LessThanOrEqual
#endif

#define					SInt_LessThanOrEqual	CONCAT(SINT_TYPE,_LessThanOrEqual)
#define c_slte			SInt_LessThanOrEqual

t_bool					S8_LessThanOrEqual(t_s8 x, t_s8 y);
#define c_s8lte			S8_LessThanOrEqual

t_bool					S16_LessThanOrEqual(t_s16 x, t_s16 y);
#define c_s16lte		S16_LessThanOrEqual

t_bool					S32_LessThanOrEqual(t_s32 x, t_s32 y);
#define c_s32lte		S32_LessThanOrEqual

t_bool					S64_LessThanOrEqual(t_s64 x, t_s64 y);
#define c_s64lte		S64_LessThanOrEqual

#if LIBCONFIG_USE_INT128
t_bool					S128_LessThanOrEqual(t_s128 x, t_s128 y);
#define c_s128lte		S128_LessThanOrEqual
#endif
//!@}



//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value (operator: `>`)
//!@{
#define					UInt_GreaterThan	CONCAT(UINT_TYPE,_GreaterThan)
#define c_ugt			UInt_GreaterThan

t_bool					U8_GreaterThan(t_u8 x, t_u8 y);
#define c_u8gt			U8_GreaterThan

t_bool					U16_GreaterThan(t_u16 x, t_u16 y);
#define c_u16gt			U16_GreaterThan

t_bool					U32_GreaterThan(t_u32 x, t_u32 y);
#define c_u32gt			U32_GreaterThan

t_bool					U64_GreaterThan(t_u64 x, t_u64 y);
#define c_u64gt			U64_GreaterThan

#if LIBCONFIG_USE_INT128
t_bool					U128_GreaterThan(t_u128 x, t_u128 y);
#define c_u128gt		U128_GreaterThan
#endif

#define					SInt_GreaterThan	CONCAT(SINT_TYPE,_GreaterThan)
#define c_sgt			SInt_GreaterThan

t_bool					S8_GreaterThan(t_s8 x, t_s8 y);
#define c_s8gt			S8_GreaterThan

t_bool					S16_GreaterThan(t_s16 x, t_s16 y);
#define c_s16gt			S16_GreaterThan

t_bool					S32_GreaterThan(t_s32 x, t_s32 y);
#define c_s32gt			S32_GreaterThan

t_bool					S64_GreaterThan(t_s64 x, t_s64 y);
#define c_s64gt			S64_GreaterThan

#if LIBCONFIG_USE_INT128
t_bool					S128_GreaterThan(t_s128 x, t_s128 y);
#define c_s128gt		S128_GreaterThan
#endif
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value or equal to it (operator: `>=`)
//!@{
#define					UInt_GreaterThanOrEqual	CONCAT(UINT_TYPE,_GreaterThanOrEqual)
#define c_ugte			UInt_GreaterThanOrEqual

t_bool					U8_GreaterThanOrEqual(t_u8 x, t_u8 y);
#define c_u8gte			U8_GreaterThanOrEqual

t_bool					U16_GreaterThanOrEqual(t_u16 x, t_u16 y);
#define c_u16gte		U16_GreaterThanOrEqual

t_bool					U32_GreaterThanOrEqual(t_u32 x, t_u32 y);
#define c_u32gte		U32_GreaterThanOrEqual

t_bool					U64_GreaterThanOrEqual(t_u64 x, t_u64 y);
#define c_u64gte		U64_GreaterThanOrEqual

#if LIBCONFIG_USE_INT128
t_bool					U128_GreaterThanOrEqual(t_u128 x, t_u128 y);
#define c_u128gte		U128_GreaterThanOrEqual
#endif

#define					SInt_GreaterThanOrEqual	CONCAT(SINT_TYPE,_GreaterThanOrEqual)
#define c_sgte			SInt_GreaterThanOrEqual

t_bool					S8_GreaterThanOrEqual(t_s8 x, t_s8 y);
#define c_s8gte			S8_GreaterThanOrEqual

t_bool					S16_GreaterThanOrEqual(t_s16 x, t_s16 y);
#define c_s16gte		S16_GreaterThanOrEqual

t_bool					S32_GreaterThanOrEqual(t_s32 x, t_s32 y);
#define c_s32gte		S32_GreaterThanOrEqual

t_bool					S64_GreaterThanOrEqual(t_s64 x, t_s64 y);
#define c_s64gte		S64_GreaterThanOrEqual

#if LIBCONFIG_USE_INT128
t_bool					S128_GreaterThanOrEqual(t_s128 x, t_s128 y);
#define c_s128gte		S128_GreaterThanOrEqual
#endif
//!@}



//!@doc Returns the smaller of the two given numbers `x` and `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Min	CONCAT(UINT_TYPE,_Min)
#define c_umin			UInt_Min
#define UInt_Minimum	UInt_Min

t_u8					U8_Min(t_u8 x, t_u8 y);
#define c_u8min			U8_Min

t_u16					U16_Min(t_u16 x, t_u16 y);
#define c_u16min		U16_Min

t_u32					U32_Min(t_u32 x, t_u32 y);
#define c_u32min		U32_Min

t_u64					U64_Min(t_u64 x, t_u64 y);
#define c_u64min		U64_Min

#if LIBCONFIG_USE_INT128
t_u128					U128_Min(t_u128 x, t_u128 y);
#define c_u128min		U128_Min
#endif

#define					SInt_Min	CONCAT(SINT_TYPE,_Min)
#define c_smin			SInt_Min
#define SInt_Minimum	SInt_Min

t_s8					S8_Min(t_s8 x, t_s8 y);
#define c_s8min			S8_Min

t_s16					S16_Min(t_s16 x, t_s16 y);
#define c_s16min		S16_Min

t_s32					S32_Min(t_s32 x, t_s32 y);
#define c_s32min		S32_Min

t_s64					S64_Min(t_s64 x, t_s64 y);
#define c_s64min		S64_Min

#if LIBCONFIG_USE_INT128
t_s128					S128_Min(t_s128 x, t_s128 y);
#define c_s128min		S128_Min
#endif
//!@}



//!@doc Returns the larger of the two given numbers `x` and `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Max	CONCAT(UINT_TYPE,_Max)
#define c_umax			UInt_Max
#define UInt_Maximum	UInt_Max

t_u8					U8_Max(t_u8 x, t_u8 y);
#define c_u8max			U8_Max

t_u16					U16_Max(t_u16 x, t_u16 y);
#define c_u16max		U16_Max

t_u32					U32_Max(t_u32 x, t_u32 y);
#define c_u32max		U32_Max

t_u64					U64_Max(t_u64 x, t_u64 y);
#define c_u64max		U64_Max

#if LIBCONFIG_USE_INT128
t_u128					U128_Max(t_u128 x, t_u128 y);
#define c_u128max		U128_Max
#endif

#define					SInt_Max	CONCAT(SINT_TYPE,_Max)
#define c_smax			SInt_Max
#define SInt_Maximum	SInt_Max

t_s8					S8_Max(t_s8 x, t_s8 y);
#define c_s8max			S8_Max

t_s16					S16_Max(t_s16 x, t_s16 y);
#define c_s16max		S16_Max

t_s32					S32_Max(t_s32 x, t_s32 y);
#define c_s32max		S32_Max

t_s64					S64_Max(t_s64 x, t_s64 y);
#define c_s64max		S64_Max

#if LIBCONFIG_USE_INT128
t_s128					S128_Max(t_s128 x, t_s128 y);
#define c_s128max		S128_Max
#endif
//!@}



/*============================================================================*\
||                         Integer-based math operators                       ||
\*============================================================================*/



//!@doc Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				UInt_Add	CONCAT(UINT_TYPE,_Add)
#define c_uadd		UInt_Add

t_u8				U8_Add(t_u8 x, t_u8 y);
#define c_u8add		U8_Add

t_u16				U16_Add(t_u16 x, t_u16 y);
#define c_u16add	U16_Add

t_u32				U32_Add(t_u32 x, t_u32 y);
#define c_u32add	U32_Add

t_u64				U64_Add(t_u64 x, t_u64 y);
#define c_u64add	U64_Add

#if LIBCONFIG_USE_INT128
t_u128				U128_Add(t_u128 x, t_u128 y);
#define c_u128add	U128_Add
#endif

#define				SInt_Add	CONCAT(SINT_TYPE,_Add)
#define c_sadd		SInt_Add

t_s8				S8_Add(t_s8 x, t_s8 y);
#define c_s8add		S8_Add

t_s16				S16_Add(t_s16 x, t_s16 y);
#define c_s16add	S16_Add

t_s32				S32_Add(t_s32 x, t_s32 y);
#define c_s32add	S32_Add

t_s64				S64_Add(t_s64 x, t_s64 y);
#define c_s64add	S64_Add

#if LIBCONFIG_USE_INT128
t_s128				S128_Add(t_s128 x, t_s128 y);
#define c_s128add	S128_Add
#endif
//!@}



//!@doc Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define					UInt_Sub	CONCAT(UINT_TYPE,_Sub)
#define c_usub			UInt_Sub
#define UInt_Subtract	UInt_Sub

t_u8				U8_Sub(t_u8 x, t_u8 y);
#define c_u8sub		U8_Sub

t_u16				U16_Sub(t_u16 x, t_u16 y);
#define c_u16sub	U16_Sub

t_u32				U32_Sub(t_u32 x, t_u32 y);
#define c_u32sub	U32_Sub

t_u64				U64_Sub(t_u64 x, t_u64 y);
#define c_u64sub	U64_Sub

#if LIBCONFIG_USE_INT128
t_u128				U128_Sub(t_u128 x, t_u128 y);
#define c_u128sub	U128_Sub
#endif

#define					SInt_Sub	CONCAT(SINT_TYPE,_Sub)
#define c_ssub			SInt_Sub
#define SInt_Subtract	SInt_Sub

t_s8				S8_Sub(t_s8 x, t_s8 y);
#define c_s8sub		S8_Sub

t_s16				S16_Sub(t_s16 x, t_s16 y);
#define c_s16sub	S16_Sub

t_s32				S32_Sub(t_s32 x, t_s32 y);
#define c_s32sub	S32_Sub

t_s64				S64_Sub(t_s64 x, t_s64 y);
#define c_s64sub	S64_Sub

#if LIBCONFIG_USE_INT128
t_s128				S128_Sub(t_s128 x, t_s128 y);
#define c_s128sub	S128_Sub
#endif
//!@}



//!@doc Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define					UInt_Mul	CONCAT(UINT_TYPE,_Mul)
#define c_umul			UInt_Mul
#define UInt_Multiply	UInt_Mul

t_u8				U8_Mul(t_u8 x, t_u8 y);
#define c_u8mul		U8_Mul

t_u16				U16_Mul(t_u16 x, t_u16 y);
#define c_u16mul	U16_Mul

t_u32				U32_Mul(t_u32 x, t_u32 y);
#define c_u32mul	U32_Mul

t_u64				U64_Mul(t_u64 x, t_u64 y);
#define c_u64mul	U64_Mul

#if LIBCONFIG_USE_INT128
t_u128				U128_Mul(t_u128 x, t_u128 y);
#define c_u128mul	U128_Mul
#endif

#define					SInt_Mul	CONCAT(SINT_TYPE,_Mul)
#define c_smul			SInt_Mul
#define SInt_Multiply	SInt_Mul

t_s8				S8_Mul(t_s8 x, t_s8 y);
#define c_s8mul		S8_Mul

t_s16				S16_Mul(t_s16 x, t_s16 y);
#define c_s16mul	S16_Mul

t_s32				S32_Mul(t_s32 x, t_s32 y);
#define c_s32mul	S32_Mul

t_s64				S64_Mul(t_s64 x, t_s64 y);
#define c_s64mul	S64_Mul

#if LIBCONFIG_USE_INT128
t_s128				S128_Mul(t_s128 x, t_s128 y);
#define c_s128mul	S128_Mul
#endif
//!@}



//!@doc Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				UInt_Div	CONCAT(UINT_TYPE,_Div)
#define c_udiv		UInt_Div
#define UInt_Divide	UInt_Div

t_u8				U8_Div(t_u8 x, t_u8 y);
#define c_u8div		U8_Div

t_u16				U16_Div(t_u16 x, t_u16 y);
#define c_u16div	U16_Div

t_u32				U32_Div(t_u32 x, t_u32 y);
#define c_u32div	U32_Div

t_u64				U64_Div(t_u64 x, t_u64 y);
#define c_u64div	U64_Div

#if LIBCONFIG_USE_INT128
t_u128				U128_Div(t_u128 x, t_u128 y);
#define c_u128div	U128_Div
#endif

#define				SInt_Div	CONCAT(SINT_TYPE,_Div)
#define c_sdiv		SInt_Div
#define SInt_Divide	SInt_Div

t_s8				S8_Div(t_s8 x, t_s8 y);
#define c_s8div		S8_Div

t_s16				S16_Div(t_s16 x, t_s16 y);
#define c_s16div	S16_Div

t_s32				S32_Div(t_s32 x, t_s32 y);
#define c_s32div	S32_Div

t_s64				S64_Div(t_s64 x, t_s64 y);
#define c_s64div	S64_Div

#if LIBCONFIG_USE_INT128
t_s128				S128_Div(t_s128 x, t_s128 y);
#define c_s128div	S128_Div
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Mod	CONCAT(UINT_TYPE,_Mod)
#define c_umod			UInt_Mod
#define UInt_Modulo		UInt_Mod

t_u8					U8_Mod(t_u8 x, t_u8 y);
#define c_u8mod			U8_Mod

t_u16					U16_Mod(t_u16 x, t_u16 y);
#define c_u16mod		U16_Mod

t_u32					U32_Mod(t_u32 x, t_u32 y);
#define c_u32mod		U32_Mod

t_u64					U64_Mod(t_u64 x, t_u64 y);
#define c_u64mod		U64_Mod

#if LIBCONFIG_USE_INT128
t_u128					U128_Mod(t_u128 x, t_u128 y);
#define c_u128mod		U128_Mod
#endif

#define					SInt_Mod	CONCAT(SINT_TYPE,_Mod)
#define c_smod			SInt_Mod
#define SInt_Modulo		SInt_Mod

t_s8					S8_Mod(t_s8 x, t_s8 y);
#define c_s8mod			S8_Mod

t_s16					S16_Mod(t_s16 x, t_s16 y);
#define c_s16mod		S16_Mod

t_s32					S32_Mod(t_s32 x, t_s32 y);
#define c_s32mod		S32_Mod

t_s64					S64_Mod(t_s64 x, t_s64 y);
#define c_s64mod		S64_Mod

#if LIBCONFIG_USE_INT128
t_s128					S128_Mod(t_s128 x, t_s128 y);
#define c_s128mod		S128_Mod
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Rem	CONCAT(UINT_TYPE,_Rem)
#define c_urem			UInt_Rem
#define c_uremainder	UInt_Rem
#define UInt_Remainder	UInt_Rem

t_u8					U8_Rem(t_u8 x, t_u8 y);
#define c_u8rem			U8_Rem

t_u16					U16_Rem(t_u16 x, t_u16 y);
#define c_u16rem		U16_Rem

t_u32					U32_Rem(t_u32 x, t_u32 y);
#define c_u32rem		U32_Rem

t_u64					U64_Rem(t_u64 x, t_u64 y);
#define c_u64rem		U64_Rem

#if LIBCONFIG_USE_INT128
t_u128					U128_Rem(t_u128 x, t_u128 y);
#define c_u128rem		U128_Rem
#endif

#define					SInt_Rem	CONCAT(SINT_TYPE,_Rem)
#define c_srem			SInt_Rem
#define c_sremainder	SInt_Rem
#define SInt_Remainder	SInt_Rem

t_s8					S8_Rem(t_s8 x, t_s8 y);
#define c_s8rem			S8_Rem

t_s16					S16_Rem(t_s16 x, t_s16 y);
#define c_s16rem		S16_Rem

t_s32					S32_Rem(t_s32 x, t_s32 y);
#define c_s32rem		S32_Rem

t_s64					S64_Rem(t_s64 x, t_s64 y);
#define c_s64rem		S64_Rem

#if LIBCONFIG_USE_INT128
t_s128					S128_Rem(t_s128 x, t_s128 y);
#define c_s128rem		S128_Rem
#endif
//!@}



//!@doc Returns the value of `x` to the power of `y` (int)
/*!
**	@nonstd
*/
//!@{
#define					UInt_Pow	CONCAT(UINT_TYPE,_Pow)
#define c_upow			UInt_Pow
#define UInt_Power		UInt_Pow

t_u8					U8_Pow(t_u8 x, t_u8 y);
#define c_u8pow			U8_Pow

t_u16					U16_Pow(t_u16 x, t_u16 y);
#define c_u16pow		U16_Pow

t_u32					U32_Pow(t_u32 x, t_u32 y);
#define c_u32pow		U32_Pow

t_u64					U64_Pow(t_u64 x, t_u64 y);
#define c_u64pow		U64_Pow

#if LIBCONFIG_USE_INT128
t_u128					U128_Pow(t_u128 x, t_u128 y);
#define c_u128pow		U128_Pow
#endif

#define					SInt_Pow	CONCAT(SINT_TYPE,_Pow)
#define c_spow			SInt_Pow
#define SInt_Power		SInt_Pow

t_s8					S8_Pow(t_s8 x, t_s8 y);
#define c_s8pow			S8_Pow

t_s16					S16_Pow(t_s16 x, t_s16 y);
#define c_s16pow		S16_Pow

t_s32					S32_Pow(t_s32 x, t_s32 y);
#define c_s32pow		S32_Pow

t_s64					S64_Pow(t_s64 x, t_s64 y);
#define c_s64pow		S64_Pow

#if LIBCONFIG_USE_INT128
t_s128					S128_Pow(t_s128 x, t_s128 y);
#define c_s128pow		S128_Pow
#endif
//!@}





//!@doc Returns the nearest integer to the square root of `x` (truncated, ie: rounded down)
/*!
**	@nonstd
*/
//!@{
#define						UInt_Root2	CONCAT(UINT_TYPE,_Root2)
#define c_usqrt				UInt_Root2
#define c_uroot2			UInt_Root2
#define UInt_SqRt			UInt_Root2
#define UInt_SquareRoot		UInt_Root2

t_u8						U8_Root2(t_u8 x);
#define c_u8sqrt			U8_Root2
#define c_u8root2			U8_Root2

t_u16						U16_Root2(t_u16 x);
#define c_u16sqrt			U16_Root2
#define c_u16root2			U16_Root2

t_u32						U32_Root2(t_u32 x);
#define c_u32sqrt			U32_Root2
#define c_u32root2			U32_Root2

t_u64						U64_Root2(t_u64 x);
#define c_u64sqrt			U64_Root2
#define c_u64root2			U64_Root2

#if LIBCONFIG_USE_INT128
t_u128						U128_Root2(t_u128 x);
#define c_u128sqrt			U128_Root2
#define c_u128root2			U128_Root2
#endif

#define						SInt_Root2	CONCAT(SINT_TYPE,_Root2)
#define c_ssqrt				SInt_Root2
#define c_sroot2			SInt_Root2
#define SInt_SqRt			SInt_Root2
#define SInt_SquareRoot		SInt_Root2

t_s8						S8_Root2(t_s8 x);
#define c_s8sqrt			S8_Root2
#define c_s8root2			S8_Root2

t_s16						S16_Root2(t_s16 x);
#define c_s16sqrt			S16_Root2
#define c_s16root2			S16_Root2

t_s32						S32_Root2(t_s32 x);
#define c_s32sqrt			S32_Root2
#define c_s32root2			S32_Root2

t_s64						S64_Root2(t_s64 x);
#define c_s64sqrt			S64_Root2
#define c_s64root2			S64_Root2

#if LIBCONFIG_USE_INT128
t_s128						S128_Root2(t_s128 x);
#define c_s128sqrt			S128_Root2
#define c_s128root2			S128_Root2
#endif
//!@}



//!@doc Returns the greatest common divisor of `x` and `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_GCD	CONCAT(UINT_TYPE,_GCD)
#define c_ugcd			UInt_GCD
#define UInt_GreatestCommonDivisor	UInt_GCD

t_u8					U8_GCD(t_u8 x, t_u8 y);
#define c_u8gcd			U8_GCD

t_u16					U16_GCD(t_u16 x, t_u16 y);
#define c_u16gcd		U16_GCD

t_u32					U32_GCD(t_u32 x, t_u32 y);
#define c_u32gcd		U32_GCD

t_u64					U64_GCD(t_u64 x, t_u64 y);
#define c_u64gcd		U64_GCD

#if LIBCONFIG_USE_INT128
t_u128					U128_GCD(t_u128 x, t_u128 y);
#define c_u128gcd		U128_GCD
#endif

#define					SInt_GCD	CONCAT(SINT_TYPE,_GCD)
#define c_sgcd			SInt_GCD
#define SInt_GreatestCommonDivisor	SInt_GCD

t_s8					S8_GCD(t_s8 x, t_s8 y);
#define c_s8gcd			S8_GCD

t_s16					S16_GCD(t_s16 x, t_s16 y);
#define c_s16gcd		S16_GCD

t_s32					S32_GCD(t_s32 x, t_s32 y);
#define c_s32gcd		S32_GCD

t_s64					S64_GCD(t_s64 x, t_s64 y);
#define c_s64gcd		S64_GCD

#if LIBCONFIG_USE_INT128
t_s128					S128_GCD(t_s128 x, t_s128 y);
#define c_s128gcd		S128_GCD
#endif
//!@}



//!@doc Returns the least common multiple of `x` and `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_LCM	CONCAT(UINT_TYPE,_LCM)
#define c_ulcm			UInt_LCM
#define UInt_LeastCommonMultiple	UInt_LCM

t_u8					U8_LCM(t_u8 x, t_u8 y);
#define c_u8lcm			U8_LCM

t_u16					U16_LCM(t_u16 x, t_u16 y);
#define c_u16lcm		U16_LCM

t_u32					U32_LCM(t_u32 x, t_u32 y);
#define c_u32lcm		U32_LCM

t_u64					U64_LCM(t_u64 x, t_u64 y);
#define c_u64lcm		U64_LCM

#if LIBCONFIG_USE_INT128
t_u128					U128_LCM(t_u128 x, t_u128 y);
#define c_u128lcm		U128_LCM
#endif

#define					SInt_LCM	CONCAT(SINT_TYPE,_LCM)
#define c_slcm			SInt_LCM
#define SInt_LeastCommonMultiple	SInt_LCM

t_s8					S8_LCM(t_s8 x, t_s8 y);
#define c_s8lcm			S8_LCM

t_s16					S16_LCM(t_s16 x, t_s16 y);
#define c_s16lcm		S16_LCM

t_s32					S32_LCM(t_s32 x, t_s32 y);
#define c_s32lcm		S32_LCM

t_s64					S64_LCM(t_s64 x, t_s64 y);
#define c_s64lcm		S64_LCM

#if LIBCONFIG_USE_INT128
t_s128					S128_LCM(t_s128 x, t_s128 y);
#define c_s128lcm		S128_LCM
#endif
//!@}



/*! @endgroup */
HEADER_END
#endif
