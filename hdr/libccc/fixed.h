/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/fixed.h                           |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_FIXED_H
#define __LIBCCC_FIXED_H
/*! @file libccc/fixed.h
**	@addtogroup libccc_fixed
**	@{
**	This header defines the fixed-point number primitive types and functions.
*/

/*
** ************************************************************************** *|
**                                  Includes                                  *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/int.h"
#include "libccc/float.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! The amount of bits dedicated to the fixed-point number type's fractional number part
#define FIXED_BITS_FRACTIONPART	(LIBCONFIG_BITS_FIXED / 4)
#define FIXED_MASK_FRACTIONPART	(((t_s64)1 << FIXED_BITS_FRACTIONPART) - 1)
#define FIXED_MAX_FRACTIONPART	 ((t_s64)1 << FIXED_BITS_FRACTIONPART)

//! The amount of bits dedicated to the fixed-point number type's integer number part
#define FIXED_BITS_INTEGERPART	(LIBCONFIG_BITS_FIXED - FIXED_BITS_FRACTIONPART)
#define FIXED_MASK_INTEGERPART	((((t_s64)1 << FIXED_BITS_INTEGERPART) - 1) << FIXED_BITS_FRACTIONPART)
#define FIXED_MAX_INTEGERPART	  ((t_s64)1 << FIXED_BITS_INTEGERPART)



#if LIBCONFIG_BITS_FIXED != 16 && \
	LIBCONFIG_BITS_FIXED != 32 && \
	LIBCONFIG_BITS_FIXED != 64 && \
	LIBCONFIG_BITS_FIXED != 128
	#error "LIBCONFIG_BITS_FIXED must be equal to one of: 16, 32, 64, 128"
#endif

#if (FIXED_BITS_INTEGERPART > LIBCONFIG_BITS_FIXED)
	#error "FIXED_BITS_INTEGERPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if (FIXED_BITS_FRACTIONPART > LIBCONFIG_BITS_FIXED)
	#error "FIXED_BITS_FRACTIONPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if (FIXED_BITS_INTEGERPART + FIXED_BITS_FRACTIONPART > LIBCONFIG_BITS_FIXED)
	#error "The sum of both _INTEGERPART and _DECIMALPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif



#if LIBCONFIG_USE_STD_FIXEDPOINT
	#include <stdfix.h>
	//!< The type for 16-bit signed fixed-point rational numbers (s4.7)
	typedef _Sat short _Accum		t_q16;
	TYPEDEF_ALIAS(					t_q16,	FIXED_16,	PRIMITIVE)
	//!< The type for 32-bit signed fixed-point rational numbers (s4.15)
	typedef _Sat _Accum				t_q32;
	TYPEDEF_ALIAS(					t_q32,	FIXED_32,	PRIMITIVE)
	//!< The type for 64-bit signed fixed-point rational numbers (s4.24)
	typedef	_Sat long _Accum		t_q64;
	TYPEDEF_ALIAS(					t_q64,	FIXED_64,	PRIMITIVE)
	#ifdef	__int128
	//!< The type for 128-bit signed fixed-point rational numbers (only certain platforms)
	typedef _Sat long long _Accum	t_q128;
	TYPEDEF_ALIAS(					t_q128,	FIXED_128,	PRIMITIVE)
	#elif LIBCONFIG_BITS_FIXED == 128
		#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
	#endif

#else
	//!< The type for 16-bit signed fixed-point rational numbers (configurable)
	typedef t_s16		t_q16;
	TYPEDEF_ALIAS(		t_q16,	FIXED_16,	PRIMITIVE)
	//!< The type for 32-bit signed fixed-point rational numbers (configurable)
	typedef t_s32		t_q32;
	TYPEDEF_ALIAS(		t_q32,	FIXED_32,	PRIMITIVE)
	//!< The type for 64-bit signed fixed-point rational numbers (configurable)
	typedef	t_s64		t_q64;
	TYPEDEF_ALIAS(		t_q64,	FIXED_64,	PRIMITIVE)
	#ifdef	__int128
	//!< The type for 128-bit signed fixed-point rational numbers (only certain platforms)
	typedef __int128	t_q128;
	TYPEDEF_ALIAS(		t_q128,	FIXED_128,	PRIMITIVE)
	#elif LIBCONFIG_BITS_FIXED == 128
		#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
	#endif

#endif

//! The configurable-size fixed-point number primitive type.
typedef	LIBCONFIG_TYPE_FIXED	t_fixed;
TYPEDEF_ALIAS(					t_fixed, FIXED_128, PRIMITIVE)



#define Q16_MAX	(t_q16)S16_MAX
#define Q16_MIN	(t_q16)S16_MIN

#define Q32_MAX	(t_q32)S32_MAX
#define Q32_MIN	(t_q32)S32_MIN

#define Q64_MAX	(t_q64)S64_MAX
#define Q64_MIN	(t_q64)S64_MIN

#ifdef __int128
#define Q128_MAX	(t_q128)S128_MAX
#define Q128_MIN	(t_q128)S128_MIN
#endif

//#define FIXED_MAX	(t_fixed)CONCAT(CONCAT(S,LIBCONFIG_BITS_FIXED),_MAX)
//#define FIXED_MIN	(t_fixed)CONCAT(CONCAT(S,LIBCONFIG_BITS_FIXED),_MIN)



/*
** ************************************************************************** *|
**                         Basic fixed-point operations                       *|
** ************************************************************************** *|
*/

t_fixed	 Fixed	(t_fixed part_integer,	t_u64	part_fraction,	t_u64	denominator);
t_q16	 Q16	(t_s64 part_integer,	t_u64	part_fraction,	t_u64	denominator);
t_q32	 Q32	(t_s64 part_integer,	t_u64	part_fraction,	t_u64	denominator);
t_q64	 Q64	(t_s64 part_integer,	t_u64	part_fraction,	t_u64	denominator);
#ifdef __int128
t_q128	 Q128	(t_s64 part_integer,	t_u64	part_fraction,	t_u64	denominator);
#endif

t_fixed	 Fixed_FromInt	(t_fixed number);
t_q16	 Q16_FromInt	(t_s16 number);
t_q32	 Q32_FromInt	(t_s32 number);
t_q64	 Q64_FromInt	(t_s64 number);
#ifdef __int128
t_q128	 Q128_FromInt	(t_s128 number);
#endif

t_fixed	 Fixed_FromFloat(t_fixed number);
t_q16	 Q16_FromFloat	(t_f64 number);
t_q32	 Q32_FromFloat	(t_f64 number);
t_q64	 Q64_FromFloat	(t_f64 number);
#ifdef __int128
t_q128	 Q128_FromFloat	(t_f64 number);
#endif



t_fixed	 Fixed_IntegerPart	(t_fixed number);
t_q16	 Q16_IntegerPart	(t_q16 number);
t_q32	 Q32_IntegerPart	(t_q32 number);
t_q64	 Q64_IntegerPart	(t_q64 number);
#ifdef __int128
t_q128	 Q128_IntegerPart	(t_q128 number);
#endif

t_fixed	 Fixed_FractionPart	(t_fixed number);
t_q16	 Q16_FractionPart	(t_q16 number);
t_q32	 Q32_FractionPart	(t_q32 number);
t_q64	 Q64_FractionPart	(t_q64 number);
#ifdef __int128
t_q128	 Q128_FractionPart	(t_q128 number);
#endif

t_fixed	 Fixed_Rounded	(t_fixed number);
t_q16	 Q16_Rounded	(t_q16 number);
t_q32	 Q32_Rounded	(t_q32 number);
t_q64	 Q64_Rounded	(t_q64 number);
#ifdef __int128
t_q128	 Q128_Rounded	(t_q128 number);
#endif



t_fixed	 Fixed_Add	(t_fixed	q1, t_fixed	q2);
t_q16	 Q16_Add	(t_q16	q1, t_q16	q2);
t_q32	 Q32_Add	(t_q32	q1, t_q32	q2);
t_q64	 Q64_Add	(t_q64	q1, t_q64	q2);
#ifdef __int128
t_q128	 Q128_Add	(t_q128	q1, t_q128	q2);
#endif

t_fixed	 Fixed_Sub	(t_fixed	q1, t_fixed	q2);
t_q16	 Q16_Sub	(t_q16	q1, t_q16	q2);
t_q32	 Q32_Sub	(t_q32	q1, t_q32	q2);
t_q64	 Q64_Sub	(t_q64	q1, t_q64	q2);
#ifdef __int128
t_q128	 Q128_Sub	(t_q128	q1, t_q128	q2);
#endif

t_fixed	 Fixed_Mul	(t_fixed	q1, t_fixed	q2);
t_q16	 Q16_Mul	(t_q16	q1, t_q16	q2);
t_q32	 Q32_Mul	(t_q32	q1, t_q32	q2);
t_q64	 Q64_Mul	(t_q64	q1, t_q64	q2);
#ifdef __int128
t_q128	 Q128_Mul	(t_q128	q1, t_q128	q2);
#endif

t_fixed	 Fixed_Div	(t_fixed	q1, t_fixed	q2);
t_q16	 Q16_Div	(t_q16	q1, t_q16	q2);
t_q32	 Q32_Div	(t_q32	q1, t_q32	q2);
t_q64	 Q64_Div	(t_q64	q1, t_q64	q2);
#ifdef __int128
t_q128	 Q128_Div	(t_q128	q1, t_q128	q2);
#endif



/*
** ************************************************************************** *|
**                             String Conversions                             *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of a 16-bit signed fixed-point number
_MALLOC()
char*					Q16_ToString(t_q16 n);	// TODO
#define c_q16_to_str	Q16_ToString

//! Get the string decimal representation of a 32-bit signed fixed-point number
_MALLOC()
char*					Q32_ToString(t_q32 n);	// TODO
#define c_q32_to_str	Q32_ToString

//! Get the string decimal representation of a 64-bit signed fixed-point number
_MALLOC()
char*					Q64_ToString(t_q64 n);	// TODO
#define c_q64_to_str	Q64_ToString

#ifdef	__int128
//! Get the string decimal representation of a 128-bit signed fixed-point number
_MALLOC()
char*					Q128_ToString(t_q128 n);	// TODO
#define c_q128_to_str	Q128_ToString
#endif



//! Get the string decimal representation of a 16-bit signed fixed-point number
_MALLOC()
char*						Q16_ToString_Hex(t_q16 n);	// TODO
#define c_q16_to_strhex		Q16_ToString_Hex

//! Get the string decimal representation of a 32-bit signed fixed-point number
_MALLOC()
char*						Q32_ToString_Hex(t_q32 n);	// TODO
#define c_q32_to_strhex		Q32_ToString_Hex

//! Get the string decimal representation of a 64-bit signed fixed-point number
_MALLOC()
char*						Q64_ToString_Hex(t_q64 n);	// TODO
#define c_q64_to_strhex		Q64_ToString_Hex

#ifdef	__int128
//! Get the string decimal representation of a 128-bit signed fixed-point number
_MALLOC()
char*						Q128_ToString_Hex(t_q128 n);	// TODO
#define c_q128_to_strhex	Q128_ToString_Hex
#endif



//! Get the custom-base representation of a 16-bit signed fixed-point number
_MALLOC()
char*						Q16_ToString_Base(t_q16 n);	// TODO
#define c_q16_to_strbase	Q16_ToString_Base

//! Get the custom-base representation of a 32-bit signed fixed-point number
_MALLOC()
char*						Q32_ToString_Base(t_q32 n);	// TODO
#define c_q32_to_strbase	Q32_ToString_Base

//! Get the custom-base representation of a 64-bit signed fixed-point number
_MALLOC()
char*						Q64_ToString_Base(t_q64 n);	// TODO
#define c_q64_to_strbase	Q64_ToString_Base

#ifdef	__int128
//! Get the string decimal representation of a 128-bit signed fixed-point number
_MALLOC()
char*						Q128_ToString_Base(t_q128 n);	// TODO
#define c_q128_to_strbase	Q128_ToString_Base
#endif



//! Parses the string decimal representation of a 16-bit signed fixed-point number
t_q16					Q16_FromString(char const* str);
#define c_str_to_q16	Q16_FromString

//! Parses the string decimal representation of a 32-bit signed fixed-point number
t_q32					Q32_FromString(char const* str);
#define c_str_to_q32	Q32_FromString

//! Parses the string decimal representation of a 64-bit signed fixed-point number
t_q64					Q64_FromString(char const* str);
#define c_str_to_q64	Q64_FromString

#ifdef	__int128
//! Parses the string decimal representation of a 128-bit signed fixed-point number
t_q128					Q128_FromString(char const* str);
#define c_str_to_q128	Q128_FromString
#endif



/*! @} */
HEADER_END
#endif
