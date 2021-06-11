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
#ifdef __int128
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
#ifdef __int128
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
t_s16				S16_Abs(t_s16 x);
t_s32				S32_Abs(t_s32 x);
t_s64				S64_Abs(t_s64 x);
#ifdef __int128
t_s128				S128_Abs(t_s128 x);
#endif
#define c_sabs		SInt_Abs 	//!< @alias{SInt_Abs}
#define c_s16abs	S16_Abs 	//!< @alias{S16_Abs}
#define c_s32abs	S32_Abs 	//!< @alias{S32_Abs}
#define c_s64abs	S64_Abs 	//!< @alias{S64_Abs}
#define c_s128abs	S128_Abs 	//!< @alias{S128_Abs}

#define SInt_AbsoluteValue	SInt_Abs
//!@}



/*
** ************************************************************************** *|
**                         UInt-point basic operators                        *|
** ************************************************************************** *|
*/



//! Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				UInt_Add	CONCAT(UINT_TYPE,_Add)
t_u16				U16_Add(t_u16 x, t_u16 y);
t_u32				U32_Add(t_u32 x, t_u32 y);
t_u64				U64_Add(t_u64 x, t_u64 y);
#ifdef __int128
t_u128				U128_Add(t_u128 x, t_u128 y);
#endif
#define c_uadd		UInt_Add	//!< @alias{UInt_Add}
#define c_u16add	U16_Add 	//!< @alias{U16_Add}
#define c_u32add	U32_Add 	//!< @alias{U32_Add}
#define c_u64add	U64_Add 	//!< @alias{U64_Add}
#define c_u128add	U128_Add 	//!< @alias{U128_Add}
//!@}

//! Performs an addition between the 2 given integer values (operator: `+`)
//!@{
#define				SInt_Add	CONCAT(SINT_TYPE,_Add)
t_s16				S16_Add(t_s16 x, t_s16 y);
t_s32				S32_Add(t_s32 x, t_s32 y);
t_s64				S64_Add(t_s64 x, t_s64 y);
#ifdef __int128
t_s128				S128_Add(t_s128 x, t_s128 y);
#endif
#define c_sadd		SInt_Add	//!< @alias{SInt_Add}
#define c_s16add	S16_Add 	//!< @alias{S16_Add}
#define c_s32add	S32_Add 	//!< @alias{S32_Add}
#define c_s64add	S64_Add 	//!< @alias{S64_Add}
#define c_s128add	S128_Add 	//!< @alias{S128_Add}
//!@}





//! Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define				UInt_Sub	CONCAT(UINT_TYPE,_Sub)
t_u16				U16_Sub(t_u16 x, t_u16 y);
t_u32				U32_Sub(t_u32 x, t_u32 y);
t_u64				U64_Sub(t_u64 x, t_u64 y);
#ifdef __int128
t_u128				U128_Sub(t_u128 x, t_u128 y);
#endif
#define c_usub		UInt_Sub	//!< @alias{UInt_Sub}
#define c_u16sub	U16_Sub 	//!< @alias{U16_Sub}
#define c_u32sub	U32_Sub 	//!< @alias{U32_Sub}
#define c_u64sub	U64_Sub 	//!< @alias{U64_Sub}
#define c_u128sub	U128_Sub 	//!< @alias{U128_Sub}
//!@}

//! Performs an addition between the 2 given integer values (operator: `-`)
//!@{
#define				SInt_Sub	CONCAT(SINT_TYPE,_Sub)
t_s16				S16_Sub(t_s16 x, t_s16 y);
t_s32				S32_Sub(t_s32 x, t_s32 y);
t_s64				S64_Sub(t_s64 x, t_s64 y);
#ifdef __int128
t_s128				S128_Sub(t_s128 x, t_s128 y);
#endif
#define c_ssub		SInt_Sub	//!< @alias{SInt_Sub}
#define c_s16sub	S16_Sub 	//!< @alias{S16_Sub}
#define c_s32sub	S32_Sub 	//!< @alias{S32_Sub}
#define c_s64sub	S64_Sub 	//!< @alias{S64_Sub}
#define c_s128sub	S128_Sub 	//!< @alias{S128_Sub}
//!@}





//! Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define				UInt_Mul	CONCAT(UINT_TYPE,_Mul)
t_u16				U16_Mul(t_u16 x, t_u16 y);
t_u32				U32_Mul(t_u32 x, t_u32 y);
t_u64				U64_Mul(t_u64 x, t_u64 y);
#ifdef __int128
t_u128				U128_Mul(t_u128 x, t_u128 y);
#endif
#define c_umul		UInt_Mul	//!< @alias{UInt_Mul}
#define c_u16mul	U16_Mul 	//!< @alias{U16_Mul}
#define c_u32mul	U32_Mul 	//!< @alias{U32_Mul}
#define c_u64mul	U64_Mul 	//!< @alias{U64_Mul}
#define c_u128mul	U128_Mul 	//!< @alias{U128_Mul}
//!@}

//! Performs an addition between the 2 given integer values (operator: `*`)
//!@{
#define				SInt_Mul	CONCAT(SINT_TYPE,_Mul)
t_s16				S16_Mul(t_s16 x, t_s16 y);
t_s32				S32_Mul(t_s32 x, t_s32 y);
t_s64				S64_Mul(t_s64 x, t_s64 y);
#ifdef __int128
t_s128				S128_Mul(t_s128 x, t_s128 y);
#endif
#define c_smul		SInt_Mul	//!< @alias{SInt_Mul}
#define c_s16mul	S16_Mul 	//!< @alias{S16_Mul}
#define c_s32mul	S32_Mul 	//!< @alias{S32_Mul}
#define c_s64mul	S64_Mul 	//!< @alias{S64_Mul}
#define c_s128mul	S128_Mul 	//!< @alias{S128_Mul}
//!@}





//! Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				UInt_Div	CONCAT(UINT_TYPE,_Div)
t_u16				U16_Div(t_u16 x, t_u16 y);
t_u32				U32_Div(t_u32 x, t_u32 y);
t_u64				U64_Div(t_u64 x, t_u64 y);
#ifdef __int128
t_u128				U128_Div(t_u128 x, t_u128 y);
#endif
#define c_udiv		UInt_Div	//!< @alias{UInt_Div}
#define c_u16div	U16_Div 	//!< @alias{U16_Div}
#define c_u32div	U32_Div 	//!< @alias{U32_Div}
#define c_u64div	U64_Div 	//!< @alias{U64_Div}
#define c_u128div	U128_Div 	//!< @alias{U128_Div}
//!@}

//! Performs a division between the 2 given integer values (operator: `/`)
//!@{
#define				SInt_Div	CONCAT(SINT_TYPE,_Div)
t_s16				S16_Div(t_s16 x, t_s16 y);
t_s32				S32_Div(t_s32 x, t_s32 y);
t_s64				S64_Div(t_s64 x, t_s64 y);
#ifdef __int128
t_s128				S128_Div(t_s128 x, t_s128 y);
#endif
#define c_sdiv		SInt_Div	//!< @alias{SInt_Div}
#define c_s16div	S16_Div 	//!< @alias{S16_Div}
#define c_s32div	S32_Div 	//!< @alias{S32_Div}
#define c_s64div	S64_Div 	//!< @alias{S64_Div}
#define c_s128div	S128_Div 	//!< @alias{S128_Div}
//!@}





//! Returns the remainder of euclidian division of `x` by `y`
/*!
**	@nonstd
*/
//!@{
#define					UInt_Mod	CONCAT(UINT_TYPE,_Mod)
t_u16					U16_Mod(t_u16 x, t_u16 y);
t_u32					U32_Mod(t_u32 x, t_u32 y);
t_u64					U64_Mod(t_u64 x, t_u64 y);
#ifdef __int128
t_u128					U128_Mod(t_u128 x, t_u128 y);
#endif
#define c_umod			UInt_Mod
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
t_s16					S16_Mod(t_s16 x, t_s16 y);
t_s32					S32_Mod(t_s32 x, t_s32 y);
t_s64					S64_Mod(t_s64 x, t_s64 y);
#ifdef __int128
t_s128					S128_Mod(t_s128 x, t_s128 y);
#endif
#define c_smod			SInt_Mod
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
t_u16					U16_Pow(t_u16 x, t_u16 y);
t_u32					U32_Pow(t_u32 x, t_u32 y);
t_u64					U64_Pow(t_u64 x, t_u64 y);
#ifdef __int128
t_u128					U128_Pow(t_u128 x, t_u128 y);
#endif
#define c_upow			UInt_Pow
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
t_s16					S16_Pow(t_s16 x, t_s16 y);
t_s32					S32_Pow(t_s32 x, t_s32 y);
t_s64					S64_Pow(t_s64 x, t_s64 y);
#ifdef __int128
t_s128					S128_Pow(t_s128 x, t_s128 y);
#endif
#define c_spow			SInt_Pow
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
t_u16						U16_Root2(t_u16 x);
t_u32						U32_Root2(t_u32 x);
t_u64						U64_Root2(t_u64 x);
#ifdef __int128
t_u128						U128_Root2(t_u128 x);
#endif
#define c_usqrt				UInt_Root2
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
t_s16						S16_Root2(t_s16 x);
t_s32						S32_Root2(t_s32 x);
t_s64						S64_Root2(t_s64 x);
#ifdef __int128
t_s128						S128_Root2(t_s128 x);
#endif
#define c_ssqrt				SInt_Root2
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
