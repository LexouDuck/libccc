/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/int.h                        |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_INT_H
#define __LIBCCC_MATH_INT_H
/*!@group{libccc_math_int}
** @{
**	This header defines the common standard math functions for integer numbers.
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

#include "libccc/int.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/



/*!
**	@see
**	- UInt_EqualsApprox()
**	- SInt_EqualsApprox()
*/
//!@{
#define UINT_APPROX		1 // TODO remove ?
#define SINT_APPROX		1 // TODO remove ?
//!@}



//! The type of function which takes one real number and outputs one real number
//!@{
typedef		t_uint	(*f_uint_function)	(t_uint x);
typedef		t_sint	(*f_sint_function)	(t_sint x);

typedef		t_u16	(*f_u16_function)	(t_u16 x);
typedef		t_s16	(*f_s16_function)	(t_s16 x);

typedef		t_u32	(*f_u32_function)	(t_u32 x);
typedef		t_s32	(*f_s32_function)	(t_s32 x);

typedef		t_u64	(*f_u64_function)	(t_u64 x);
typedef		t_s64	(*f_s64_function)	(t_s64 x);
#if LIBCONFIG_USE_128BIT
typedef		t_u128	(*f_u128_function)	(t_u128 x);
typedef		t_s128	(*f_s128_function)	(t_s128 x);
#endif
//!@}

//! The type of function which takes two real numbers and outputs one real number
//!@{
typedef		t_uint	(*f_uint_operator)	(t_uint x,	t_uint y);
typedef		t_sint	(*f_sint_operator)	(t_sint x,	t_sint y);

typedef		t_u16	(*f_u16_operator)	(t_u16 x,	t_u16 y);
typedef		t_s16	(*f_s16_operator)	(t_s16 x,	t_s16 y);

typedef		t_u32	(*f_u32_operator)	(t_u32 x,	t_u32 y);
typedef		t_s32	(*f_s32_operator)	(t_s32 x,	t_s32 y);

typedef		t_u64	(*f_u64_operator)	(t_u64 x,	t_u64 y);
typedef		t_s64	(*f_s64_operator)	(t_s64 x,	t_s64 y);
#if LIBCONFIG_USE_128BIT
typedef		t_u128	(*f_u128_operator)	(t_u128 x,	t_u128 y);
typedef		t_s128	(*f_s128_operator)	(t_s128 x,	t_s128 y);
#endif
//!@}



/*
** ************************************************************************** *|
**                            Arithmetic Operations                           *|
** ************************************************************************** *|
*/

//! Returns the absolute value of `x` (makes `x` positive)
/*!
**	@nonstd
*/
//!@{
#define				SInt_Abs	CONCAT(SINT_TYPE,_Abs)
t_s8				S8_Abs( t_s8  x);
t_s16				S16_Abs(t_s16 x);
t_s32				S32_Abs(t_s32 x);
t_s64				S64_Abs(t_s64 x);
#if LIBCONFIG_USE_128BIT
t_s128				S128_Abs(t_s128 x);
#endif
#define c_sabs		SInt_Abs 	//!< @alias{SInt_Abs}
#define c_s8abs		S8_Abs 	//!< @alias{S16_Abs}
#define c_s16abs	S16_Abs 	//!< @alias{S16_Abs}
#define c_s32abs	S32_Abs 	//!< @alias{S32_Abs}
#define c_s64abs	S64_Abs 	//!< @alias{S64_Abs}
#define c_s128abs	S128_Abs 	//!< @alias{S128_Abs}

#define SInt_AbsoluteValue	SInt_Abs
//!@}



/*
** ************************************************************************** *|
**                       Floating-point logic operators                       *|
** ************************************************************************** *|
*/

//! Returns `TRUE` if the 2 given integer values are exactly equal (operator: `==`)
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
#define					SInt_Equals	CONCAT(FLOAT_TYPE,_Equals)
t_bool					S8_Equals( t_s8  x, t_s8  y);
t_bool					S16_Equals(t_s16 x, t_s16 y);
t_bool					S32_Equals(t_s32 x, t_s32 y);
t_bool					S64_Equals(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_bool					S128_Equals(t_s128 x, t_s128 y);
#endif
#define c_sequ			SInt_Equals	//!< @alias{SInt_Equals}
#define c_s8equ			S8_Equals	//!< @alias{S8_Equals}
#define c_s16equ		S16_Equals	//!< @alias{S16_Equals}
#define c_s32equ		S32_Equals	//!< @alias{S32_Equals}
#define c_s64equ		S64_Equals	//!< @alias{S64_Equals}
#define c_s128equ		S128_Equals	//!< @alias{S128_Equals}
//!@}



//! Returns `TRUE` if the 2 given integer values are close to equal (operator: `~=`)
/*!
**	@nonstd
**
**	@param	x	The first value to check for (approximate) equality
**	@param	y	The second value to check for (approximate) equality
**	@returns
**	`TRUE` if the 2 given integer values are close enough to be considered equal
**	(using #FLOAT_APPROX as a comparison margin), otherwise `FALSE`.
*/
//!@{
#define					SInt_EqualsApprox	CONCAT(FLOAT_TYPE,_EqualsApprox)
t_bool					S8_EqualsApprox( t_s8  x, t_s8  y);
t_bool					S16_EqualsApprox(t_s16 x, t_s16 y);
t_bool					S32_EqualsApprox(t_s32 x, t_s32 y);
t_bool					S64_EqualsApprox(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_bool					S128_EqualsApprox(t_s128 x, t_s128 y);
#endif
#define c_sequa			SInt_EqualsApprox	//!< @alias{SInt_EqualsApprox}
#define c_s8equa		S8_EqualsApprox		//!< @alias{S8_EqualsApprox}
#define c_s16equa		S16_EqualsApprox	//!< @alias{S16_EqualsApprox}
#define c_s32equa		S32_EqualsApprox	//!< @alias{S32_EqualsApprox}
#define c_s64equa		S64_EqualsApprox	//!< @alias{S64_EqualsApprox}
#define c_s128equa		S128_EqualsApprox	//!< @alias{S128_EqualsApprox}
//!@}



// TODO SInt_LessThan

// TODO SInt_GreaterThan



/*
** ************************************************************************** *|
**                         UInt-point basic operators                        *|
** ************************************************************************** *|
*/



//! Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				UInt_Add	CONCAT(UINT_TYPE,_Add)
t_u8				U8_Add( t_u8  x, t_u8  y);
t_u16				U16_Add(t_u16 x, t_u16 y);
t_u32				U32_Add(t_u32 x, t_u32 y);
t_u64				U64_Add(t_u64 x, t_u64 y);
#if LIBCONFIG_USE_128BIT
t_u128				U128_Add(t_u128 x, t_u128 y);
#endif
#define c_uadd		UInt_Add	//!< @alias{UInt_Add}
#define c_u8add		U8_Add		//!< @alias{U8_Add}
#define c_u16add	U16_Add		//!< @alias{U16_Add}
#define c_u32add	U32_Add		//!< @alias{U32_Add}
#define c_u64add	U64_Add		//!< @alias{U64_Add}
#define c_u128add	U128_Add	//!< @alias{U128_Add}
//!@}

//! Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				SInt_Add	CONCAT(SINT_TYPE,_Add)
t_s8				S8_Add( t_s8  x, t_s8  y);
t_s16				S16_Add(t_s16 x, t_s16 y);
t_s32				S32_Add(t_s32 x, t_s32 y);
t_s64				S64_Add(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_s128				S128_Add(t_s128 x, t_s128 y);
#endif
#define c_sadd		SInt_Add	//!< @alias{SInt_Add}
#define c_s8add		S8_Add		//!< @alias{S8_Add}
#define c_s16add	S16_Add		//!< @alias{S16_Add}
#define c_s32add	S32_Add		//!< @alias{S32_Add}
#define c_s64add	S64_Add		//!< @alias{S64_Add}
#define c_s128add	S128_Add	//!< @alias{S128_Add}
//!@}





//! Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define				UInt_Sub	CONCAT(UINT_TYPE,_Sub)
t_u8				U8_Sub( t_u8  x, t_u8  y);
t_u16				U16_Sub(t_u16 x, t_u16 y);
t_u32				U32_Sub(t_u32 x, t_u32 y);
t_u64				U64_Sub(t_u64 x, t_u64 y);
#if LIBCONFIG_USE_128BIT
t_u128				U128_Sub(t_u128 x, t_u128 y);
#endif
#define c_usub		UInt_Sub	//!< @alias{UInt_Sub}
#define c_u8sub		U8_Sub		//!< @alias{U8_Sub}
#define c_u16sub	U16_Sub		//!< @alias{U16_Sub}
#define c_u32sub	U32_Sub		//!< @alias{U32_Sub}
#define c_u64sub	U64_Sub		//!< @alias{U64_Sub}
#define c_u128sub	U128_Sub	//!< @alias{U128_Sub}
//!@}

//! Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define				SInt_Sub	CONCAT(SINT_TYPE,_Sub)
t_s8				S8_Sub( t_s8  x, t_s8  y);
t_s16				S16_Sub(t_s16 x, t_s16 y);
t_s32				S32_Sub(t_s32 x, t_s32 y);
t_s64				S64_Sub(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_s128				S128_Sub(t_s128 x, t_s128 y);
#endif
#define c_ssub		SInt_Sub	//!< @alias{SInt_Sub}
#define c_s8sub		S8_Sub		//!< @alias{S8_Sub}
#define c_s16sub	S16_Sub		//!< @alias{S16_Sub}
#define c_s32sub	S32_Sub		//!< @alias{S32_Sub}
#define c_s64sub	S64_Sub		//!< @alias{S64_Sub}
#define c_s128sub	S128_Sub	//!< @alias{S128_Sub}
//!@}





//! Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define				UInt_Mul	CONCAT(UINT_TYPE,_Mul)
t_u8				U8_Mul( t_u8  x, t_u8  y);
t_u16				U16_Mul(t_u16 x, t_u16 y);
t_u32				U32_Mul(t_u32 x, t_u32 y);
t_u64				U64_Mul(t_u64 x, t_u64 y);
#if LIBCONFIG_USE_128BIT
t_u128				U128_Mul(t_u128 x, t_u128 y);
#endif
#define c_umul		UInt_Mul	//!< @alias{UInt_Mul}
#define c_u8mul		U8_Mul		//!< @alias{U8_Mul}
#define c_u16mul	U16_Mul		//!< @alias{U16_Mul}
#define c_u32mul	U32_Mul		//!< @alias{U32_Mul}
#define c_u64mul	U64_Mul		//!< @alias{U64_Mul}
#define c_u128mul	U128_Mul	//!< @alias{U128_Mul}
//!@}

//! Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define				SInt_Mul	CONCAT(SINT_TYPE,_Mul)
t_s8				S8_Mul( t_s8  x, t_s8  y);
t_s16				S16_Mul(t_s16 x, t_s16 y);
t_s32				S32_Mul(t_s32 x, t_s32 y);
t_s64				S64_Mul(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_s128				S128_Mul(t_s128 x, t_s128 y);
#endif
#define c_smul		SInt_Mul	//!< @alias{SInt_Mul}
#define c_s8mul		S8_Mul		//!< @alias{S8_Mul}
#define c_s16mul	S16_Mul		//!< @alias{S16_Mul}
#define c_s32mul	S32_Mul		//!< @alias{S32_Mul}
#define c_s64mul	S64_Mul		//!< @alias{S64_Mul}
#define c_s128mul	S128_Mul	//!< @alias{S128_Mul}
//!@}





//! Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				UInt_Div	CONCAT(UINT_TYPE,_Div)
t_u8				U8_Div( t_u8  x, t_u8  y);
t_u16				U16_Div(t_u16 x, t_u16 y);
t_u32				U32_Div(t_u32 x, t_u32 y);
t_u64				U64_Div(t_u64 x, t_u64 y);
#if LIBCONFIG_USE_128BIT
t_u128				U128_Div(t_u128 x, t_u128 y);
#endif
#define c_udiv		UInt_Div	//!< @alias{UInt_Div}
#define c_u8div		U8_Div		//!< @alias{U8_Div}
#define c_u16div	U16_Div		//!< @alias{U16_Div}
#define c_u32div	U32_Div		//!< @alias{U32_Div}
#define c_u64div	U64_Div		//!< @alias{U64_Div}
#define c_u128div	U128_Div	//!< @alias{U128_Div}
//!@}

//! Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				SInt_Div	CONCAT(SINT_TYPE,_Div)
t_s8				S8_Div( t_s8  x, t_s8  y);
t_s16				S16_Div(t_s16 x, t_s16 y);
t_s32				S32_Div(t_s32 x, t_s32 y);
t_s64				S64_Div(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_s128				S128_Div(t_s128 x, t_s128 y);
#endif
#define c_sdiv		SInt_Div	//!< @alias{SInt_Div}
#define c_s8div		S8_Div		//!< @alias{S8_Div}
#define c_s16div	S16_Div		//!< @alias{S16_Div}
#define c_s32div	S32_Div		//!< @alias{S32_Div}
#define c_s64div	S64_Div		//!< @alias{S64_Div}
#define c_s128div	S128_Div	//!< @alias{S128_Div}
//!@}





//! Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Mod	CONCAT(UINT_TYPE,_Mod)
t_u8					U8_Mod( t_u8  x, t_u8  y);
t_u16					U16_Mod(t_u16 x, t_u16 y);
t_u32					U32_Mod(t_u32 x, t_u32 y);
t_u64					U64_Mod(t_u64 x, t_u64 y);
#if LIBCONFIG_USE_128BIT
t_u128					U128_Mod(t_u128 x, t_u128 y);
#endif
#define c_umod			UInt_Mod
#define c_u8mod			U8_Mod
#define c_u16mod		U16_Mod
#define c_u32mod		U32_Mod
#define c_u64mod		U64_Mod
#define c_u128mod		U128_Mod

#define UInt_Modulo	UInt_Mod
//!@}

//! Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					SInt_Mod	CONCAT(SINT_TYPE,_Mod)
t_s8					S8_Mod( t_s8  x, t_s8  y);
t_s16					S16_Mod(t_s16 x, t_s16 y);
t_s32					S32_Mod(t_s32 x, t_s32 y);
t_s64					S64_Mod(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_s128					S128_Mod(t_s128 x, t_s128 y);
#endif
#define c_smod			SInt_Mod
#define c_s8mod			S8_Mod
#define c_s16mod		S16_Mod
#define c_s32mod		S32_Mod
#define c_s64mod		S64_Mod
#define c_s128mod		S128_Mod

#define SInt_Modulo	SInt_Mod
//!@}





/*
** ************************************************************************** *|
**                          UInt-point math operators                        *|
** ************************************************************************** *|
*/



//! Returns the value of `x` to the power of `y` (int)
/*!
**	@nonstd
*/
//!@{
#define					UInt_Pow	CONCAT(UINT_TYPE,_Pow)
t_u8					U8_Pow( t_u8  x, t_u8  y);
t_u16					U16_Pow(t_u16 x, t_u16 y);
t_u32					U32_Pow(t_u32 x, t_u32 y);
t_u64					U64_Pow(t_u64 x, t_u64 y);
#if LIBCONFIG_USE_128BIT
t_u128					U128_Pow(t_u128 x, t_u128 y);
#endif
#define c_upow			UInt_Pow
#define c_u8pow			U8_Pow
#define c_u16pow		U16_Pow
#define c_u32pow		U32_Pow
#define c_u64pow		U64_Pow
#define c_u128pow		U128_Pow

#define UInt_Power		UInt_Pow
//!@}

//! Returns the value of `x` to the power of `y` (int)
/*!
**	@nonstd
*/
//!@{
#define					SInt_Pow	CONCAT(SINT_TYPE,_Pow)
t_s8					S8_Pow( t_s8  x, t_s8  y);
t_s16					S16_Pow(t_s16 x, t_s16 y);
t_s32					S32_Pow(t_s32 x, t_s32 y);
t_s64					S64_Pow(t_s64 x, t_s64 y);
#if LIBCONFIG_USE_128BIT
t_s128					S128_Pow(t_s128 x, t_s128 y);
#endif
#define c_spow			SInt_Pow
#define c_s8pow			S8_Pow
#define c_s16pow		S16_Pow
#define c_s32pow		S32_Pow
#define c_s64pow		S64_Pow
#define c_s128pow		S128_Pow

#define SInt_Power		SInt_Pow
//!@}





//! Returns the square root of `x` (inverse of power of 2)
/*!
**	@nonstd
*/
//!@{
#define						UInt_Root2	CONCAT(UINT_TYPE,_Root2)
t_u8						U8_Root2( t_u8  x);
t_u16						U16_Root2(t_u16 x);
t_u32						U32_Root2(t_u32 x);
t_u64						U64_Root2(t_u64 x);
#if LIBCONFIG_USE_128BIT
t_u128						U128_Root2(t_u128 x);
#endif
#define c_usqrt				UInt_Root2
#define c_u8sqrt			U8_Root2
#define c_u16sqrt			U16_Root2
#define c_u32sqrt			U32_Root2
#define c_u64sqrt			U64_Root2
#define c_u128sqrt			U128_Root2

#define UInt_SqRt			UInt_Root2
#define UInt_SquareRoot		UInt_Root2
//!@}

//! Returns the square root of `x` (inverse of power of 2)
/*!
**	@nonstd
*/
//!@{
#define						SInt_Root2	CONCAT(SINT_TYPE,_Root2)
t_s8						S8_Root2( t_s8  x);
t_s16						S16_Root2(t_s16 x);
t_s32						S32_Root2(t_s32 x);
t_s64						S64_Root2(t_s64 x);
#if LIBCONFIG_USE_128BIT
t_s128						S128_Root2(t_s128 x);
#endif
#define c_ssqrt				SInt_Root2
#define c_s8sqrt			S8_Root2
#define c_s16sqrt			S16_Root2
#define c_s32sqrt			S32_Root2
#define c_s64sqrt			S64_Root2
#define c_s128sqrt			S128_Root2

#define SInt_SqRt			SInt_Root2
#define SInt_SquareRoot		SInt_Root2
//!@}



/*! @} */
HEADER_END
#endif
