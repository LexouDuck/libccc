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
/*!@group{libccc_fixed}
** @{
**	This header defines the fixed-point number primitive types and functions.
**
**	There has been a draft proposal to include fixed-point number types and
**	all the relevant operators to the C standard, but it has not gone through.
**	You can read it here: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n968.pdf
**
**	This means that despite being older than the IEEE-754 floating-point standard,
**	fixed-point number types are not yet defined in the C ISO standard,
**	and the compilers that do implement some fixed-point type vary greatly
**	in how they do it.
**
**	As such, it is not really recommended to use the "standard" fixed-point types,
**	but you can nevertheless use them with the #LIBCONFIG_USE_STD_FIXEDPOINT setting.
**
**	NB: The `typedef`s here are "saturated" number types, what this means is
**		that operations will not make the value overflow like they would with
**		a typical `int` type. Instead, the fixed-point value is constrained
**		to the largest and smallest possible values that it can hold (ie:
**		the macros #Q16_MIN & #Q16_MAX, #Q32_MIN & #Q32_MAX, #Q64_MIN & #Q64_MAX,
**		and #FIXED_MIN & #FIXED_MAX).
**
**	It also worth noting another difference with integers, the minimum possible value
**	here is reserved to represent a NAN-like value, which is the result of 0-division.
**	So, instead of having the negative value range be 1 greater than the positive range,
**	The `0x800000...` value is set aside to represent NAN/not a number.
**
**	Finally there's the question of choosing a denominator value for the
**	fixed-point number type. There are several advantages that come with choosing a
**	denominator number which is a power of 2: many operations can be optimized, and
**	there is a clear separation of the two parts of the number, in terms of bits.
**	On the other hand, it can be useful to choose whichever arbitrary denominator
**	one wishes (for instance, having 100 fractions, to represent currency cents).
**	For this reason, the literal notation that is chosen to represent fixed-point
**	numbers is the following: `123.(456/789)`
**	It should appear obvious that the first part is the integer, and after the decimal
**	point, inside the parentheses, the first number is the fractional part, and the
**	last number is the denominator chosen.
**	For another example: $42.75 would be `42.(75/100)`
**	This notation was chosen because it allows any kind of configuration for a
**	fixed-point number to be represented in an inter-compatible "lossless" fashion.
**
**	@file
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

// TODO make fixed-point type have configurable denominator, not just bitwise point

//! The amount of bits dedicated to the fixed-point number type's fractional number part
#define FIXED_BITS_FRACTIONPART	(LIBCONFIG_BITS_FIXED / 4)
#define FIXED_MASK_FRACTIONPART	(((t_s64)1 << FIXED_BITS_FRACTIONPART) - 1)
#define FIXED_MAX_FRACTIONPART	 ((t_s64)1 << FIXED_BITS_FRACTIONPART)

//! The amount of bits dedicated to the fixed-point number type's integer number part
#define FIXED_BITS_INTEGERPART	(LIBCONFIG_BITS_FIXED - FIXED_BITS_FRACTIONPART)
#define FIXED_MASK_INTEGERPART	((((t_s64)1 << FIXED_BITS_INTEGERPART) - 1) << FIXED_BITS_FRACTIONPART)
#define FIXED_MAX_INTEGERPART	  ((t_s64)1 << FIXED_BITS_INTEGERPART)



#if LIBCONFIG_USE_STD_FIXEDPOINT
	#include <stdfix.h>

	//! Primitive type: 16-bit signed fixed-point rational number (s4.7)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which has, at minimum:
	**	- 4 bits dedicated to the integer part
	**	- 7 bits dedicated to the fractional part
	**	The largest possible value for this type is #Q16_MAX.
	*/
	typedef _Sat short _Accum		t_q16;
	TYPEDEF_ALIAS(					t_q16,	FIXED_16,	PRIMITIVE)

	//! Primitive type: 32-bit signed fixed-point rational numbers(s4.15)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which has, at minimum:
	**	- 4 bits dedicated to the integer part
	**	- 15 bits dedicated to the fractional part
	**	The largest possible value for this type is #Q32_MAX.
	*/
	typedef _Sat _Accum				t_q32;
	TYPEDEF_ALIAS(					t_q32,	FIXED_32,	PRIMITIVE)

	//! Primitive type: 64-bit signed fixed-point rational numbers(s4.24)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which has, at minimum:
	**	- 4 bits dedicated to the integer part
	**	- 24 bits dedicated to the fractional part
	**	The largest possible value for this type is #Q64_MAX.
	*/
	typedef	_Sat long _Accum		t_q64;
	TYPEDEF_ALIAS(					t_q64,	FIXED_64,	PRIMITIVE)

	#if (LIBCONFIG_BITS_FIXED == 128)
		#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
	#endif

#else

	//! Primitive type: 16-bit signed fixed-point rational number (configurable bit portions)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which is 16 bits in size.
	**	Which amount is dedicated to the fraction/integer part is
	**	determined by the value of #FIXED_BITS_FRACTIONPART.
	**	All the other `#define`s depend on this one macro.
	**	The largest possible value for this type is #Q16_MAX.
	*/
	typedef t_s16		t_q16;
	TYPEDEF_ALIAS(		t_q16,	FIXED_16,	PRIMITIVE)

	//! Primitive type: 32-bit signed fixed-point rational number (configurable bit portions)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which is 32 bits in size.
	**	Which amount is dedicated to the fraction/integer part is
	**	determined by the value of #FIXED_BITS_FRACTIONPART.
	**	All the other `#define`s depend on this one macro.
	**	The largest possible value for this type is #Q32_MAX.
	*/
	typedef t_s32		t_q32;
	TYPEDEF_ALIAS(		t_q32,	FIXED_32,	PRIMITIVE)

	//! Primitive type: 64-bit signed fixed-point rational number (configurable bit portions)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which is 64 bits in size.
	**	Which amount is dedicated to the fraction/integer part is
	**	determined by the value of #FIXED_BITS_FRACTIONPART.
	**	All the other `#define`s depend on this one macro.
	**	The largest possible value for this type is #Q64_MAX.
	*/
	typedef	t_s64		t_q64;
	TYPEDEF_ALIAS(		t_q64,	FIXED_64,	PRIMITIVE)

	#ifdef	__int128
	//! Primitive type: 128-bit signed fixed-point rational number (only certain platforms)
	/*!
	**	@nonstd
	**
	**	Fixed-point rational number type which is 128 bits in size.
	**	Which amount is dedicated to the fraction/integer part is
	**	determined by the value of #FIXED_BITS_FRACTIONPART.
	**	All the other `#define`s depend on this one macro.
	**	The largest possible value for this type is #Q128_MAX.
	*/
	typedef __int128	t_q128;
	TYPEDEF_ALIAS(		t_q128,	FIXED_128,	PRIMITIVE)
	#elif (LIBCONFIG_BITS_FIXED == 128)
		#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
	#endif

#endif



//! The configurable-size fixed-point number primitive type.
/*!
**	@nonstd
**
**	Configurable-width fixed-point rational number type.
**	The size of this fixed-point type depends on the value of #LIBCONFIG_BITS_FIXED.
**	The portion dedicated to the fractional part depends on the value of #FIXED_BITS_FRACTIONPART.
**	All the other important `#define`s depend on this one macro (FIXED_BITS_FRACTIONPART).
**	This type can express a number between #FIXED_MIN and #FIXED_MAX.
*/
typedef	CONCAT(t_q,LIBCONFIG_BITS_FIXED)	t_fixed;
TYPEDEF_ALIAS(t_fixed, FIXED_128, PRIMITIVE)

//! The actual underlying type for the `t_fixed` configurable type, in uppercase
#define FIXED_TYPE		CONCAT(Q,LIBCONFIG_BITS_FIXED)



#if(LIBCONFIG_BITS_FIXED != 16 && \
	LIBCONFIG_BITS_FIXED != 32 && \
	LIBCONFIG_BITS_FIXED != 64 && \
	LIBCONFIG_BITS_FIXED != 128)
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



#define Q16_MAX		((t_q16)S16_MAX)	//!< The largest possible value that a 16-bit fixed-point can hold
#define Q16_MIN		((t_q16)S16_MIN)	//!< The largest possible value that a 16-bit fixed-point can hold

#define Q32_MAX		((t_q32)S32_MAX)	//!< The largest possible value that a 32-bit fixed-point can hold
#define Q32_MIN		((t_q32)S32_MIN)	//!< The largest possible value that a 32-bit fixed-point can hold

#define Q64_MAX		((t_q64)S64_MAX)	//!< The largest possible value that a 64-bit fixed-point can hold
#define Q64_MIN		((t_q64)S64_MIN)	//!< The largest possible value that a 64-bit fixed-point can hold

#ifdef __int128
#define Q128_MAX	((t_q128)S128_MAX)	//!< The largest possible value that a 128-bit fixed-point can hold
#define Q128_MIN	((t_q128)S128_MIN)	//!< The largest possible value that a 128-bit fixed-point can hold
#endif

#define FIXED_MAX	((t_fixed)SINT_MAX)
#define FIXED_MIN	((t_fixed)SINT_MIN)



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
**                          Fixed-to-String Conversions                       *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of a 16-bit signed fixed-point number
_MALLOC()
char*					Q16_ToString(t_q16 n);	// TODO
#define c_q16_to_str	Q16_ToString //!< @alias{Q16_ToString}

//! Get the string decimal representation of a 32-bit signed fixed-point number
_MALLOC()
char*					Q32_ToString(t_q32 n);	// TODO
#define c_q32_to_str	Q32_ToString //!< @alias{Q32_ToString}

//! Get the string decimal representation of a 64-bit signed fixed-point number
_MALLOC()
char*					Q64_ToString(t_q64 n);	// TODO
#define c_q64_to_str	Q64_ToString //!< @alias{Q64_ToString}

#ifdef	__int128
//! Get the string decimal representation of a 128-bit signed fixed-point number
_MALLOC()
char*					Q128_ToString(t_q128 n);	// TODO
#define c_q128_to_str	Q128_ToString //!< @alias{Q128_ToString}
#endif



//! Get the string decimal representation of a 16-bit signed fixed-point number
_MALLOC()
char*						Q16_ToString_Hex(t_q16 n);	// TODO
#define c_q16_to_strhex		Q16_ToString_Hex //!< @alias{Q16_ToString_Hex}

//! Get the string decimal representation of a 32-bit signed fixed-point number
_MALLOC()
char*						Q32_ToString_Hex(t_q32 n);	// TODO
#define c_q32_to_strhex		Q32_ToString_Hex //!< @alias{Q32_ToString_Hex}

//! Get the string decimal representation of a 64-bit signed fixed-point number
_MALLOC()
char*						Q64_ToString_Hex(t_q64 n);	// TODO
#define c_q64_to_strhex		Q64_ToString_Hex //!< @alias{Q64_ToString_Hex}

#ifdef	__int128
//! Get the string decimal representation of a 128-bit signed fixed-point number
_MALLOC()
char*						Q128_ToString_Hex(t_q128 n);	// TODO
#define c_q128_to_strhex	Q128_ToString_Hex //!< @alias{Q128_ToString_Hex}
#endif



//! Get the custom-base representation of a 16-bit signed fixed-point number
_MALLOC()
char*						Q16_ToString_Base(t_q16 n);	// TODO
#define c_q16_to_strbase	Q16_ToString_Base //!< @alias{Q16_ToString_Base}

//! Get the custom-base representation of a 32-bit signed fixed-point number
_MALLOC()
char*						Q32_ToString_Base(t_q32 n);	// TODO
#define c_q32_to_strbase	Q32_ToString_Base //!< @alias{Q32_ToString_Base}

//! Get the custom-base representation of a 64-bit signed fixed-point number
_MALLOC()
char*						Q64_ToString_Base(t_q64 n);	// TODO
#define c_q64_to_strbase	Q64_ToString_Base //!< @alias{Q64_ToString_Base}

#ifdef	__int128
//! Get the string decimal representation of a 128-bit signed fixed-point number
_MALLOC()
char*						Q128_ToString_Base(t_q128 n);	// TODO
#define c_q128_to_strbase	Q128_ToString_Base //!< @alias{Q128_ToString_Base}
#endif



/*
** ************************************************************************** *|
**                          String-to-Fixed Conversions                       *|
** ************************************************************************** *|
*/

//! Parses the string decimal representation of a 16-bit signed fixed-point number
t_q16					Q16_FromString(char const* str);
#define c_str_to_q16	Q16_FromString //!< @alias{Q16_FromString}

//! Parses the string decimal representation of a 32-bit signed fixed-point number
t_q32					Q32_FromString(char const* str);
#define c_str_to_q32	Q32_FromString //!< @alias{Q32_FromString}

//! Parses the string decimal representation of a 64-bit signed fixed-point number
t_q64					Q64_FromString(char const* str);
#define c_str_to_q64	Q64_FromString //!< @alias{Q64_FromString}

#ifdef	__int128
//! Parses the string decimal representation of a 128-bit signed fixed-point number
t_q128					Q128_FromString(char const* str);
#define c_str_to_q128	Q128_FromString //!< @alias{Q128_FromString}
#endif



/*! @} */
HEADER_END
#endif
