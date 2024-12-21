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

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/int.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//!@doc Macros which store small threshold value for approximate equaity checks
/*!
**	@see
**	- UInt_EqualsApprox()
**	- SInt_EqualsApprox()
*/
//!@{
#define UINT_APPROX		1 // TODO remove ?
#define SINT_APPROX		1 // TODO remove ?
//!@}



//!@doc The type of function which takes one real number and outputs one real number
//!@{
typedef		t_uint	(*f_uint_function)	(t_uint a);
typedef		t_sint	(*f_sint_function)	(t_sint a);

typedef		t_u16	(*f_u16_function)	(t_u16 a);
typedef		t_s16	(*f_s16_function)	(t_s16 a);

typedef		t_u32	(*f_u32_function)	(t_u32 a);
typedef		t_s32	(*f_s32_function)	(t_s32 a);

typedef		t_u64	(*f_u64_function)	(t_u64 a);
typedef		t_s64	(*f_s64_function)	(t_s64 a);

#if LIBCONFIG_USE_INT128
typedef		t_u128	(*f_u128_function)	(t_u128 a);
typedef		t_s128	(*f_s128_function)	(t_s128 a);
#endif
//!@}

//!@doc The type of function which takes two real numbers and outputs one real number
//!@{
typedef		t_uint	(*f_uint_operator)	(t_uint a,	t_uint b);
typedef		t_sint	(*f_sint_operator)	(t_sint a,	t_sint b);

typedef		t_u16	(*f_u16_operator)	(t_u16 a,	t_u16 b);
typedef		t_s16	(*f_s16_operator)	(t_s16 a,	t_s16 b);

typedef		t_u32	(*f_u32_operator)	(t_u32 a,	t_u32 b);
typedef		t_s32	(*f_s32_operator)	(t_s32 a,	t_s32 b);

typedef		t_u64	(*f_u64_operator)	(t_u64 a,	t_u64 b);
typedef		t_s64	(*f_s64_operator)	(t_s64 a,	t_s64 b);

#if LIBCONFIG_USE_INT128
typedef		t_u128	(*f_u128_operator)	(t_u128 a,	t_u128 b);
typedef		t_s128	(*f_s128_operator)	(t_s128 a,	t_s128 b);
#endif
//!@}



/*
** ************************************************************************** *|
**                           Basic Arithmetic Operations                      *|
** ************************************************************************** *|
*/

//!@doc Returns the absolute value of `a` (makes `a` positive)
/*!
**	@nonstd
*/
//!@{
#define						SInt_Abs	CONCAT(SINT_TYPE,_Abs)
#define c_sabs				SInt_Abs
#define SInt_AbsoluteValue	SInt_Abs

t_s8						S8_Abs(t_s8 a);
#define c_s8abs				S8_Abs

t_s16						S16_Abs(t_s16 a);
#define c_s16abs			S16_Abs

t_s32						S32_Abs(t_s32 a);
#define c_s32abs			S32_Abs

t_s64						S64_Abs(t_s64 a);
#define c_s64abs			S64_Abs

#if LIBCONFIG_USE_INT128
t_s128						S128_Abs(t_s128 a);
#define c_s128abs			S128_Abs
#endif
//!@}

//!@doc Returns the sign value value of `x` (either `-1`, `0`, or `+1`)
/*!
**	@nonstd
*/
//!@{
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



// TODO: implement IsPrime() function

// TODO: implement PrimeFactors() function



/*
** ************************************************************************** *|
**                            Comparison operators                            *|
** ************************************************************************** *|
*/

//!@doc Returns `TRUE` if the 2 given integer values are exactly equal (operator: `==`)
/*!
**	@nonstd
**
**	@param	a	The first value to check for (exact) equality
**	@param	b	The second value to check for (exact) equality
**	@returns
**	`TRUE` if the 2 given integer values are exactly equal,
**	otherwise `FALSE`.
*/
//!@{
#define					UInt_Equals	CONCAT(UINT_TYPE,_Equals)
#define c_uequ			UInt_Equals

t_bool					U8_Equals(t_u8 a, t_u8 b);
#define c_u8equ			U8_Equals

t_bool					U16_Equals(t_u16 a, t_u16 b);
#define c_u16equ		U16_Equals

t_bool					U32_Equals(t_u32 a, t_u32 b);
#define c_u32equ		U32_Equals

t_bool					U64_Equals(t_u64 a, t_u64 b);
#define c_u64equ		U64_Equals

#if LIBCONFIG_USE_INT128
t_bool					U128_Equals(t_u128 a, t_u128 b);
#define c_u128equ		U128_Equals
#endif
//!@}

//!@doc Returns `TRUE` if the 2 given integer values are exactly equal (operator: `==`)
/*!
**	@nonstd
**
**	@param	a	The first value to check for (exact) equality
**	@param	b	The second value to check for (exact) equality
**	@returns
**	`TRUE` if the 2 given integer values are exactly equal,
**	otherwise `FALSE`.
*/
//!@{
#define					SInt_Equals	CONCAT(SINT_TYPE,_Equals)
#define c_sequ			SInt_Equals

t_bool					S8_Equals(t_s8 a, t_s8 b);
#define c_s8equ			S8_Equals

t_bool					S16_Equals(t_s16 a, t_s16 b);
#define c_s16equ		S16_Equals

t_bool					S32_Equals(t_s32 a, t_s32 b);
#define c_s32equ		S32_Equals

t_bool					S64_Equals(t_s64 a, t_s64 b);
#define c_s64equ		S64_Equals

#if LIBCONFIG_USE_INT128
t_bool					S128_Equals(t_s128 a, t_s128 b);
#define c_s128equ		S128_Equals
#endif
//!@}



//!@doc Returns `TRUE` if the 2 given integer values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	a	The first value to check for (approximate) equality
**	@param	b	The second value to check for (approximate) equality
**	@returns
**	`TRUE` if the 2 given integer values are close enough to be considered equal
**	(using #SINT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					UInt_EqualsApprox	CONCAT(UINT_TYPE,_EqualsApprox)
#define c_uequa			UInt_EqualsApprox

t_bool					U8_EqualsApprox(t_u8 a, t_u8 b);
#define c_u8equa		U8_EqualsApprox

t_bool					U16_EqualsApprox(t_u16 a, t_u16 b);
#define c_u16equa		U16_EqualsApprox

t_bool					U32_EqualsApprox(t_u32 a, t_u32 b);
#define c_u32equa		U32_EqualsApprox

t_bool					U64_EqualsApprox(t_u64 a, t_u64 b);
#define c_u64equa		U64_EqualsApprox

#if LIBCONFIG_USE_INT128
t_bool					U128_EqualsApprox(t_u128 a, t_u128 b);
#define c_u128equa		U128_EqualsApprox
#endif
//!@}

//!@doc Returns `TRUE` if the 2 given integer values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	a	The first value to check for (approximate) equality
**	@param	b	The second value to check for (approximate) equality
**	@returns
**	`TRUE` if the 2 given integer values are close enough to be considered equal
**	(using #SINT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					SInt_EqualsApprox	CONCAT(SINT_TYPE,_EqualsApprox)
#define c_sequa			SInt_EqualsApprox

t_bool					S8_EqualsApprox(t_s8 a, t_s8 b);
#define c_s8equa		S8_EqualsApprox

t_bool					S16_EqualsApprox(t_s16 a, t_s16 b);
#define c_s16equa		S16_EqualsApprox

t_bool					S32_EqualsApprox(t_s32 a, t_s32 b);
#define c_s32equa		S32_EqualsApprox

t_bool					S64_EqualsApprox(t_s64 a, t_s64 b);
#define c_s64equa		S64_EqualsApprox

#if LIBCONFIG_USE_INT128
t_bool					S128_EqualsApprox(t_s128 a, t_s128 b);
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
//!@}

//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value (operator: `<`)
//!@{
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
//!@}

//!@doc Returns `TRUE` if the left-hand value is lesser than the right-hand value or equal to it (operator: `<=`)
//!@{
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
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value (operator: `>`)
//!@{
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
//!@}

//!@doc Returns `TRUE` if the left-hand value is greater than the right-hand value or equal to it (operator: `>=`)
//!@{
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



/*
** ************************************************************************** *|
**                         UInt-point basic operators                        *|
** ************************************************************************** *|
*/



//!@doc Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				UInt_Add	CONCAT(UINT_TYPE,_Add)
#define c_uadd		UInt_Add

t_u8				U8_Add(t_u8 a, t_u8 b);
#define c_u8add		U8_Add

t_u16				U16_Add(t_u16 a, t_u16 b);
#define c_u16add	U16_Add

t_u32				U32_Add(t_u32 a, t_u32 b);
#define c_u32add	U32_Add

t_u64				U64_Add(t_u64 a, t_u64 b);
#define c_u64add	U64_Add

#if LIBCONFIG_USE_INT128
t_u128				U128_Add(t_u128 a, t_u128 b);
#define c_u128add	U128_Add
#endif
//!@}

//!@doc Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				SInt_Add	CONCAT(SINT_TYPE,_Add)
#define c_sadd		SInt_Add

t_s8				S8_Add(t_s8 a, t_s8 b);
#define c_s8add		S8_Add

t_s16				S16_Add(t_s16 a, t_s16 b);
#define c_s16add	S16_Add

t_s32				S32_Add(t_s32 a, t_s32 b);
#define c_s32add	S32_Add

t_s64				S64_Add(t_s64 a, t_s64 b);
#define c_s64add	S64_Add

#if LIBCONFIG_USE_INT128
t_s128				S128_Add(t_s128 a, t_s128 b);
#define c_s128add	S128_Add
#endif
//!@}



//!@doc Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define					UInt_Sub	CONCAT(UINT_TYPE,_Sub)
#define c_usub			UInt_Sub
#define UInt_Subtract	UInt_Sub

t_u8				U8_Sub(t_u8 a, t_u8 b);
#define c_u8sub		U8_Sub

t_u16				U16_Sub(t_u16 a, t_u16 b);
#define c_u16sub	U16_Sub

t_u32				U32_Sub(t_u32 a, t_u32 b);
#define c_u32sub	U32_Sub

t_u64				U64_Sub(t_u64 a, t_u64 b);
#define c_u64sub	U64_Sub

#if LIBCONFIG_USE_INT128
t_u128				U128_Sub(t_u128 a, t_u128 b);
#define c_u128sub	U128_Sub
#endif
//!@}

//!@doc Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define					SInt_Sub	CONCAT(SINT_TYPE,_Sub)
#define c_ssub			SInt_Sub
#define SInt_Subtract	SInt_Sub

t_s8				S8_Sub(t_s8 a, t_s8 b);
#define c_s8sub		S8_Sub

t_s16				S16_Sub(t_s16 a, t_s16 b);
#define c_s16sub	S16_Sub

t_s32				S32_Sub(t_s32 a, t_s32 b);
#define c_s32sub	S32_Sub

t_s64				S64_Sub(t_s64 a, t_s64 b);
#define c_s64sub	S64_Sub

#if LIBCONFIG_USE_INT128
t_s128				S128_Sub(t_s128 a, t_s128 b);
#define c_s128sub	S128_Sub
#endif
//!@}



//!@doc Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define					UInt_Mul	CONCAT(UINT_TYPE,_Mul)
#define c_umul			UInt_Mul
#define UInt_Multiply	UInt_Mul

t_u8				U8_Mul(t_u8 a, t_u8 b);
#define c_u8mul		U8_Mul

t_u16				U16_Mul(t_u16 a, t_u16 b);
#define c_u16mul	U16_Mul

t_u32				U32_Mul(t_u32 a, t_u32 b);
#define c_u32mul	U32_Mul

t_u64				U64_Mul(t_u64 a, t_u64 b);
#define c_u64mul	U64_Mul

#if LIBCONFIG_USE_INT128
t_u128				U128_Mul(t_u128 a, t_u128 b);
#define c_u128mul	U128_Mul
#endif
//!@}

//!@doc Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define					SInt_Mul	CONCAT(SINT_TYPE,_Mul)
#define c_smul			SInt_Mul
#define SInt_Multiply	SInt_Mul

t_s8				S8_Mul(t_s8 a, t_s8 b);
#define c_s8mul		S8_Mul

t_s16				S16_Mul(t_s16 a, t_s16 b);
#define c_s16mul	S16_Mul

t_s32				S32_Mul(t_s32 a, t_s32 b);
#define c_s32mul	S32_Mul

t_s64				S64_Mul(t_s64 a, t_s64 b);
#define c_s64mul	S64_Mul

#if LIBCONFIG_USE_INT128
t_s128				S128_Mul(t_s128 a, t_s128 b);
#define c_s128mul	S128_Mul
#endif
//!@}



//!@doc Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				UInt_Div	CONCAT(UINT_TYPE,_Div)
#define c_udiv		UInt_Div
#define UInt_Divide	UInt_Div

t_u8				U8_Div(t_u8 a, t_u8 b);
#define c_u8div		U8_Div

t_u16				U16_Div(t_u16 a, t_u16 b);
#define c_u16div	U16_Div

t_u32				U32_Div(t_u32 a, t_u32 b);
#define c_u32div	U32_Div

t_u64				U64_Div(t_u64 a, t_u64 b);
#define c_u64div	U64_Div

#if LIBCONFIG_USE_INT128
t_u128				U128_Div(t_u128 a, t_u128 b);
#define c_u128div	U128_Div
#endif
//!@}

//!@doc Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				SInt_Div	CONCAT(SINT_TYPE,_Div)
#define c_sdiv		SInt_Div
#define SInt_Divide	SInt_Div

t_s8				S8_Div(t_s8 a, t_s8 b);
#define c_s8div		S8_Div

t_s16				S16_Div(t_s16 a, t_s16 b);
#define c_s16div	S16_Div

t_s32				S32_Div(t_s32 a, t_s32 b);
#define c_s32div	S32_Div

t_s64				S64_Div(t_s64 a, t_s64 b);
#define c_s64div	S64_Div

#if LIBCONFIG_USE_INT128
t_s128				S128_Div(t_s128 a, t_s128 b);
#define c_s128div	S128_Div
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `a` by `b`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Mod	CONCAT(UINT_TYPE,_Mod)
#define c_umod			UInt_Mod
#define UInt_Modulo		UInt_Mod

t_u8					U8_Mod(t_u8 a, t_u8 b);
#define c_u8mod			U8_Mod

t_u16					U16_Mod(t_u16 a, t_u16 b);
#define c_u16mod		U16_Mod

t_u32					U32_Mod(t_u32 a, t_u32 b);
#define c_u32mod		U32_Mod

t_u64					U64_Mod(t_u64 a, t_u64 b);
#define c_u64mod		U64_Mod

#if LIBCONFIG_USE_INT128
t_u128					U128_Mod(t_u128 a, t_u128 b);
#define c_u128mod		U128_Mod
#endif
//!@}

//!@doc Returns the remainder of euclidian division of `a` by `b`
/*!
**	@nonstd
*/
//!@{
#define					SInt_Mod	CONCAT(SINT_TYPE,_Mod)
#define c_smod			SInt_Mod
#define SInt_Modulo		SInt_Mod

t_s8					S8_Mod(t_s8 a, t_s8 b);
#define c_s8mod			S8_Mod

t_s16					S16_Mod(t_s16 a, t_s16 b);
#define c_s16mod		S16_Mod

t_s32					S32_Mod(t_s32 a, t_s32 b);
#define c_s32mod		S32_Mod

t_s64					S64_Mod(t_s64 a, t_s64 b);
#define c_s64mod		S64_Mod

#if LIBCONFIG_USE_INT128
t_s128					S128_Mod(t_s128 a, t_s128 b);
#define c_s128mod		S128_Mod
#endif
//!@}



//!@doc Returns the remainder of euclidian division of `a` by `b`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Rem	CONCAT(UINT_TYPE,_Rem)
#define c_urem			UInt_Rem
#define c_uremainder	UInt_Rem
#define UInt_Remainder	UInt_Rem

t_u8					U8_Rem(t_u8 a, t_u8 b);
#define c_u8rem			U8_Rem

t_u16					U16_Rem(t_u16 a, t_u16 b);
#define c_u16rem		U16_Rem

t_u32					U32_Rem(t_u32 a, t_u32 b);
#define c_u32rem		U32_Rem

t_u64					U64_Rem(t_u64 a, t_u64 b);
#define c_u64rem		U64_Rem

#if LIBCONFIG_USE_INT128
t_u128					U128_Rem(t_u128 a, t_u128 b);
#define c_u128rem		U128_Rem
#endif
//!@}

//!@doc Returns the remainder of euclidian division of `a` by `b`
/*!
**	@nonstd
*/
//!@{
#define					SInt_Rem	CONCAT(SINT_TYPE,_Rem)
#define c_srem			SInt_Rem
#define c_sremainder	SInt_Rem
#define SInt_Remainder	SInt_Rem

t_s8					S8_Rem(t_s8 a, t_s8 b);
#define c_s8rem			S8_Rem

t_s16					S16_Rem(t_s16 a, t_s16 b);
#define c_s16rem		S16_Rem

t_s32					S32_Rem(t_s32 a, t_s32 b);
#define c_s32rem		S32_Rem

t_s64					S64_Rem(t_s64 a, t_s64 b);
#define c_s64rem		S64_Rem

#if LIBCONFIG_USE_INT128
t_s128					S128_Rem(t_s128 a, t_s128 b);
#define c_s128rem		S128_Rem
#endif
//!@}



/*
** ************************************************************************** *|
**                         Integer-based math operators                       *|
** ************************************************************************** *|
*/



//!@doc Returns the value of `a` to the power of `b` (int)
/*!
**	@nonstd
*/
//!@{
#define					UInt_Pow	CONCAT(UINT_TYPE,_Pow)
#define c_upow			UInt_Pow
#define UInt_Power		UInt_Pow

t_u8					U8_Pow(t_u8 a, t_u8 b);
#define c_u8pow			U8_Pow

t_u16					U16_Pow(t_u16 a, t_u16 b);
#define c_u16pow		U16_Pow

t_u32					U32_Pow(t_u32 a, t_u32 b);
#define c_u32pow		U32_Pow

t_u64					U64_Pow(t_u64 a, t_u64 b);
#define c_u64pow		U64_Pow

#if LIBCONFIG_USE_INT128
t_u128					U128_Pow(t_u128 a, t_u128 b);
#define c_u128pow		U128_Pow
#endif
//!@}

//!@doc Returns the value of `a` to the power of `b` (int)
/*!
**	@nonstd
*/
//!@{
#define					SInt_Pow	CONCAT(SINT_TYPE,_Pow)
#define c_spow			SInt_Pow
#define SInt_Power		SInt_Pow

t_s8					S8_Pow(t_s8 a, t_s8 b);
#define c_s8pow			S8_Pow

t_s16					S16_Pow(t_s16 a, t_s16 b);
#define c_s16pow		S16_Pow

t_s32					S32_Pow(t_s32 a, t_s32 b);
#define c_s32pow		S32_Pow

t_s64					S64_Pow(t_s64 a, t_s64 b);
#define c_s64pow		S64_Pow

#if LIBCONFIG_USE_INT128
t_s128					S128_Pow(t_s128 a, t_s128 b);
#define c_s128pow		S128_Pow
#endif
//!@}





//!@doc Returns the nearest integer to the square root of `a` (truncated, ie: rounded down)
/*!
**	@nonstd
*/
//!@{
#define						UInt_Root2	CONCAT(UINT_TYPE,_Root2)
#define c_usqrt				UInt_Root2
#define UInt_SqRt			UInt_Root2
#define UInt_SquareRoot		UInt_Root2

t_u8						U8_Root2(t_u8 a);
#define c_u8sqrt			U8_Root2

t_u16						U16_Root2(t_u16 a);
#define c_u16sqrt			U16_Root2

t_u32						U32_Root2(t_u32 a);
#define c_u32sqrt			U32_Root2

t_u64						U64_Root2(t_u64 a);
#define c_u64sqrt			U64_Root2

#if LIBCONFIG_USE_INT128
t_u128						U128_Root2(t_u128 a);
#define c_u128sqrt			U128_Root2
#endif
//!@}

//!@doc Returns the square root of `a` (inverse of power of 2)
/*!
**	@nonstd
*/
//!@{
#define						SInt_Root2	CONCAT(SINT_TYPE,_Root2)
#define c_ssqrt				SInt_Root2
#define SInt_SqRt			SInt_Root2
#define SInt_SquareRoot		SInt_Root2

t_s8						S8_Root2(t_s8 a);
#define c_s8sqrt			S8_Root2

t_s16						S16_Root2(t_s16 a);
#define c_s16sqrt			S16_Root2

t_s32						S32_Root2(t_s32 a);
#define c_s32sqrt			S32_Root2

t_s64						S64_Root2(t_s64 a);
#define c_s64sqrt			S64_Root2

#if LIBCONFIG_USE_INT128
t_s128						S128_Root2(t_s128 a);
#define c_s128sqrt			S128_Root2
#endif
//!@}



//!@doc Returns the greatest common divisor of `a` and `b`
/*!
**	@nonstd
*/
//!@{
#define					UInt_GCD	CONCAT(UINT_TYPE,_GCD)
#define c_ugcd			UInt_GCD
#define UInt_GreatestCommonDivisor	UInt_GCD

t_u8					U8_GCD(t_u8 a, t_u8 b);
#define c_u8gcd			U8_GCD

t_u16					U16_GCD(t_u16 a, t_u16 b);
#define c_u16gcd		U16_GCD

t_u32					U32_GCD(t_u32 a, t_u32 b);
#define c_u32gcd		U32_GCD

t_u64					U64_GCD(t_u64 a, t_u64 b);
#define c_u64gcd		U64_GCD

#if LIBCONFIG_USE_INT128
t_u128					U128_GCD(t_u128 a, t_u128 b);
#define c_u128gcd		U128_GCD
#endif
//!@}

//!@doc Returns the greatest common divisor of `a` and `b`
/*!
**	@nonstd
*/
//!@{
#define					SInt_GCD	CONCAT(SINT_TYPE,_GCD)
#define c_sgcd			SInt_GCD
#define SInt_GreatestCommonDivisor	SInt_GCD

t_s8					S8_GCD(t_s8 a, t_s8 b);
#define c_s8gcd			S8_GCD

t_s16					S16_GCD(t_s16 a, t_s16 b);
#define c_s16gcd		S16_GCD

t_s32					S32_GCD(t_s32 a, t_s32 b);
#define c_s32gcd		S32_GCD

t_s64					S64_GCD(t_s64 a, t_s64 b);
#define c_s64gcd		S64_GCD

#if LIBCONFIG_USE_INT128
t_s128					S128_GCD(t_s128 a, t_s128 b);
#define c_s128gcd		S128_GCD
#endif
//!@}



//!@doc Returns the least common multiple of `a` and `b`
/*!
**	@nonstd
*/
//!@{
#define					UInt_LCM	CONCAT(UINT_TYPE,_LCM)
#define c_ulcm			UInt_LCM
#define UInt_LeastCommonMultiple	UInt_LCM

t_u8					U8_LCM(t_u8 a, t_u8 b);
#define c_u8lcm			U8_LCM

t_u16					U16_LCM(t_u16 a, t_u16 b);
#define c_u16lcm		U16_LCM

t_u32					U32_LCM(t_u32 a, t_u32 b);
#define c_u32lcm		U32_LCM

t_u64					U64_LCM(t_u64 a, t_u64 b);
#define c_u64lcm		U64_LCM

#if LIBCONFIG_USE_INT128
t_u128					U128_LCM(t_u128 a, t_u128 b);
#define c_u128lcm		U128_LCM
#endif
//!@}

//!@doc Returns the least common multiple of `a` and `b`
/*!
**	@nonstd
*/
//!@{
#define					SInt_LCM	CONCAT(SINT_TYPE,_LCM)
#define c_slcm			SInt_LCM
#define SInt_LeastCommonMultiple	SInt_LCM

t_s8					S8_LCM(t_s8 a, t_s8 b);
#define c_s8lcm			S8_LCM

t_s16					S16_LCM(t_s16 a, t_s16 b);
#define c_s16lcm		S16_LCM

t_s32					S32_LCM(t_s32 a, t_s32 b);
#define c_s32lcm		S32_LCM

t_s64					S64_LCM(t_s64 a, t_s64 b);
#define c_s64lcm		S64_LCM

#if LIBCONFIG_USE_INT128
t_s128					S128_LCM(t_s128 a, t_s128 b);
#define c_s128lcm		S128_LCM
#endif
//!@}



/*! @endgroup */
HEADER_END
#endif
