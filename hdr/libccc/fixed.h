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
**	This header defines the fixed-point number primitive types and functions.
**	@addtogroup libccc/fixed
**	@{
*/

/*
** ************************************************************************** *|
**                                  Includes                                  *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_define.h"

#include "libccc/int.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define Q16_MAX	(t_q16)(~0)
#define Q16_MIN	(t_q16)(~0)

#define Q32_MAX	(t_q32)(~0)
#define Q32_MIN	(t_q32)(~0)

#define Q64_MAX	(t_q64)(~0)
#define Q64_MIN	(t_q64)(~0)

#ifdef __int128
	#define Q128_MAX	(t_q128)(~0)
	#define Q128_MIN	(t_q128)(~0)
#endif



#if LIBCONFIG_BITS_FIXED != 16 && \
	LIBCONFIG_BITS_FIXED != 32 && \
	LIBCONFIG_BITS_FIXED != 64 && \
	LIBCONFIG_BITS_FIXED != 128
	#error "LIBCONFIG_BITS_FIXED must be equal to one of: 16, 32, 64, 128"
#endif

#if LIBCONFIG_BITS_FIXED_INTEGERPART > LIBCONFIG_BITS_FIXED
	#error "LIBCONFIG_BITS_FIXED_INTEGERPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if LIBCONFIG_BITS_FIXED_FRACTIONPART > LIBCONFIG_BITS_FIXED
	#error "LIBCONFIG_BITS_FIXED_FRACTIONPART must be inferior or equal to LIBCONFIG_BITS_FIXED"
#endif

#if LIBCONFIG_BITS_FIXED_INTEGERPART + LIBCONFIG_BITS_FIXED_FRACTIONPART > LIBCONFIG_BITS_FIXED
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



/*
** ************************************************************************** *|
**                         Basic fixed-point operations                       *|
** ************************************************************************** *|
*/

#define Fixed(I, F)			(Fixed_FromInt(I) | Fixed_FractionPart(Math_Mod((F), 1)))
#define Fixed_FromInt(I)	((t_fixed)(I) << LIBCONFIG_BITS_FIXED_FRACTIONPART)
#define Fixed_FromFloat(I)	(((t_fixed)(I) << LIBCONFIG_BITS_FIXED_FRACTIONPART) | Fixed_FractionPart(Math_Mod((I), 1)))

#define Fixed_IntegerPart(Q)	((Q) >> LIBCONFIG_BITS_FIXED_FRACTIONPART)
#define Fixed_FractionPart(Q)	((t_fixed)(Q) & (((t_fixed)1 << LIBCONFIG_BITS_FIXED_FRACTIONPART) - 1))
#define Fixed_Rounded(Q)		((t_fixed)((Q) * (((t_fixed)1 << LIBCONFIG_BITS_FIXED_FRACTIONPART) + ((Q) >= 0 ? 0.5 : -0.5))))

#define Fixed_Add(A, B)	((A) + (B))
#define Fixed_Sub(A, B)	((A) - (B))
#define Fixed_Mul(A, B)	((t_fixed)(((t_fixed)(A) * (t_fixed)(B)) >> LIBCONFIG_BITS_FIXED_FRACTIONPART))
#define Fixed_Div(A, B)	((t_fixed)(((t_fixed)(A) << LIBCONFIG_BITS_FIXED_FRACTIONPART) / (t_fixed)(B)))




/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
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
