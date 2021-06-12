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
**		to the largest and smallest possible values that it can hold, ie:
**		- #Q16_MIN & #Q16_MAX
**		- #Q32_MIN & #Q32_MAX
**		- #Q64_MIN & #Q64_MAX
**		- #Q128_MIN & #Q128_MAX
**		- #FIXED_MIN & #FIXED_MAX
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

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_FIXED_T
#define __LIBCCC_FIXED_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

// TODO make fixed-point type have configurable denominator, not just bitwise point ?

//! The maximum value of the fixed-point number type's fractional number part
#define FIXED_MAX_FRACTIONPART	(LIBCONFIG_FIXED_DENOMINATOR - 1)

//! The amount of bits dedicated to the fixed-point number type's integer number part
#define FIXED_MAX_INTEGERPART	(CONCAT(CONCAT(S,LIBCONFIG_BITS_FIXED),_MAX) / LIBCONFIG_FIXED_DENOMINATOR)
#define FIXED_MIN_INTEGERPART	(CONCAT(CONCAT(S,LIBCONFIG_BITS_FIXED),_MIN) / LIBCONFIG_FIXED_DENOMINATOR)



#if LIBCONFIG_USE_STD_FIXEDPOINT

	#if (!defined(__STDC__) || (__STDC_VERSION__ < __STDC_VERSION_C17__))
		#error "C ISO standard fixed-point types are not available for this C standard: "__STDC_VERSION__"L"
	#endif

	#ifndef __NOSTD__
		#include <stdfix.h>
	#else
		#error "Cannot use standard fixed-point library, __NOSTD__ macro is defined"
	#endif

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
	typedef s16		t_q16;
	TYPEDEF_ALIAS(	t_q16,	FIXED_16,	PRIMITIVE)

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
	typedef s32		t_q32;
	TYPEDEF_ALIAS(	t_q32,	FIXED_32,	PRIMITIVE)

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
	typedef	s64		t_q64;
	TYPEDEF_ALIAS(	t_q64,	FIXED_64,	PRIMITIVE)

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
	typedef s128	t_q128;
	TYPEDEF_ALIAS(	t_q128,	FIXED_128,	PRIMITIVE)
	#elif (LIBCONFIG_BITS_FIXED == 128)
		#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
	#endif

#endif



//! The actual underlying type for the `t_fixed` configurable type
#define FIXED_T			CONCAT(t_q,LIBCONFIG_BITS_FIXED)
//! The actual underlying type for the `t_fixed` configurable type, in uppercase
#define FIXED_TYPE		CONCAT(Q,LIBCONFIG_BITS_FIXED)
//! the denominator/divisor for this fixed-point number type, @see #LIBCONFIG_FIXED_DENOMINATOR
#define FIXED_DENOMINATOR	LIBCONFIG_FIXED_DENOMINATOR


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
typedef	FIXED_T	t_fixed;
TYPEDEF_ALIAS(t_fixed, FIXED_128, PRIMITIVE)



#if(LIBCONFIG_BITS_FIXED != 16 && \
	LIBCONFIG_BITS_FIXED != 32 && \
	LIBCONFIG_BITS_FIXED != 64 && \
	LIBCONFIG_BITS_FIXED != 128)
	#error "LIBCONFIG_BITS_FIXED must be equal to one of: 16, 32, 64, 128"
#endif

#if (FIXED_DENOMINATOR == 0)
	#error "LIBCONFIG_FIXED_DENOMINATOR must never be 0 (cannot divide by zero)"
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

#define FIXED_MAX	((t_fixed)SINT_MAX)	//!< The largest possible value that a configurable-size fixed-point can hold
#define FIXED_MIN	((t_fixed)SINT_MIN)	//!< The largest possible value that a configurable-size fixed-point can hold



#endif
#ifndef __LIBCCC_FIXED_F
#define __LIBCCC_FIXED_F

/*
** ************************************************************************** *|
**                         Fixed-point number functions                       *|
** ************************************************************************** *|
*/

//! A smart constructor: calls the appropriate `Fixed_From*()` function from the given argument type
//!@{
#define DEFINEFUNC_Fixed(X, FUNCTYPE) \
	_Generic((X),	\
		t_s16:	 FUNCTYPE##_FromInt,	\
		t_s32:	 FUNCTYPE##_FromInt,	\
		t_s64:	 FUNCTYPE##_FromInt,	\
		t_s128:	 FUNCTYPE##_FromInt,	\
		t_sint:  FUNCTYPE##_FromInt,	\
		t_q16:	 FUNCTYPE##_FromFixed,	\
		t_q32:	 FUNCTYPE##_FromFixed,	\
		t_q64:	 FUNCTYPE##_FromFixed,	\
		t_q128:	 FUNCTYPE##_FromFixed,	\
		t_fixed: FUNCTYPE##_FromFixed,	\
		t_f32:	 FUNCTYPE##_FromFloat,	\
		t_f64:	 FUNCTYPE##_FromFloat,	\
		t_f80:	 FUNCTYPE##_FromFloat,	\
		t_f128:	 FUNCTYPE##_FromFloat,	\
		t_float: FUNCTYPE##_FromFloat,	\
	)(X)
#define Fixed(X)	DEFINEFUNC_Fixed(X, Fixed)
#define Q16(X)		DEFINEFUNC_Fixed(X, Q16)
#define Q32(X)		DEFINEFUNC_Fixed(X, Q32)
#define Q64(X)		DEFINEFUNC_Fixed(X, Q64)
#define Q128(X)		DEFINEFUNC_Fixed(X, Q128)
//!@}

//! Returns the nearest fixed-point value to the given integer `number`
/*!
**	TODO document
*/
//!@{
#define					Fixed_FromInt	CONCAT(FIXED_TYPE,_FromInt)
t_q16					Q16_FromInt(t_sint number);
t_q32					Q32_FromInt(t_sint number);
t_q64					Q64_FromInt(t_sint number);
#ifdef __int128
t_q128					Q128_FromInt(t_sint number);
#endif
#define c_itofixed		Fixed_FromInt 	//!< @alias{Fixed_FromInt}
#define c_itoq16		Q16_FromInt 	//!< @alias{Q16_FromInt}
#define c_itoq32		Q32_FromInt 	//!< @alias{Q32_FromInt}
#define c_itoq64		Q64_FromInt 	//!< @alias{Q64_FromInt}
#define c_itoq128		Q128_FromInt 	//!< @alias{Q128_FromInt}
//!@}

//! Returns the nearest fixed-point value to the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define					Fixed_FromFixed	CONCAT(FIXED_TYPE,_FromFixed)
t_q16					Q16_FromFixed(t_fixed number);
t_q32					Q32_FromFixed(t_fixed number);
t_q64					Q64_FromFixed(t_fixed number);
#ifdef __int128
t_q128					Q128_FromFixed(t_fixed number);
#endif
#define c_qtofixed		Fixed_FromFixed	//!< @alias{Fixed_FromFixed}
#define c_qtoq16		Q16_FromFixed	//!< @alias{Q16_FromFixed}
#define c_qtoq32		Q32_FromFixed	//!< @alias{Q32_FromFixed}
#define c_qtoq64		Q64_FromFixed	//!< @alias{Q64_FromFixed}
#define c_qtoq128		Q128_FromFixed	//!< @alias{Q128_FromFixed}
//!@}

//! Returns the nearest fixed-point value to the given floating-point `number`
/*!
**	TODO document
*/
//!@{
#define	 				Fixed_FromFloat	CONCAT(FIXED_TYPE,_FromFloat)
t_q16	 				Q16_FromFloat(t_float number);
t_q32	 				Q32_FromFloat(t_float number);
t_q64	 				Q64_FromFloat(t_float number);
#ifdef __int128
t_q128	 				Q128_FromFloat(t_float number);
#endif
#define c_ftofixed		Fixed_FromFloat	//!< @alias{Fixed_FromFloat}
#define c_ftoq16		Q16_FromFloat	//!< @alias{Q16_FromFloat}
#define c_ftoq32		Q32_FromFloat	//!< @alias{Q32_FromFloat}
#define c_ftoq64		Q64_FromFloat	//!< @alias{Q64_FromFloat}
#define c_ftoq128		Q128_FromFloat	//!< @alias{Q128_FromFloat}
//!@}



//! Get the nearest fixed-point value from the given fraction/rational number
/*!
**	TODO document
$$	@param	numerator		the numerator: number at the top of the fraction
**	@param	denominator		the denominator: number at the bottom of the fraction
**	@returns
*/
//!@{
#define					Fixed_From	CONCAT(FIXED_TYPE,_From)
t_q16					Q16_From(t_s16 part_fraction, t_s16 denominator);
t_q32					Q32_From(t_s32 part_fraction, t_s32 denominator);
t_q64					Q64_From(t_s64 part_fraction, t_s64 denominator);
#ifdef __int128
t_q128					Q128_From(t_s128 part_fraction, t_s128 denominator);
#endif
#define c_tofixed		Fixed_From	//!< @alias{Fixed_From}
#define c_toq16			Q16_From	//!< @alias{Q16_From}
#define c_toq32			Q32_From	//!< @alias{Q32_From}
#define c_toq64			Q64_From	//!< @alias{Q64_From}
#define c_toq128		Q128_From	//!< @alias{Q128_From}
//!@}

//! Returns the integer portion of the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define							Fixed_IntegerPart	CONCAT(FIXED_TYPE,_IntegerPart)
t_s16							Q16_IntegerPart(t_q16 number);
t_s32							Q32_IntegerPart(t_q32 number);
t_s64							Q64_IntegerPart(t_q64 number);
#ifdef __int128
t_s128							Q128_IntegerPart(t_q128 number);
#endif
#define c_fixed_integerpart		Fixed_IntegerPart 	//!< @alias{Fixed_IntegerPart}
#define c_q16_integerpart		Q16_IntegerPart 	//!< @alias{Q16_IntegerPart}
#define c_q32_integerpart		Q32_IntegerPart 	//!< @alias{Q32_IntegerPart}
#define c_q64_integerpart		Q64_IntegerPart 	//!< @alias{Q64_IntegerPart}
#define c_q128_integerpart		Q128_IntegerPart 	//!< @alias{Q128_IntegerPart}
//!@}

//! Returns the fractional portion of the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define							Fixed_FractionPart	CONCAT(FIXED_TYPE,_FractionPart)
t_s16							Q16_FractionPart(t_q16 number);
t_s32							Q32_FractionPart(t_q32 number);
t_s64							Q64_FractionPart(t_q64 number);
#ifdef __int128
t_s128							Q128_FractionPart(t_q128 number);
#endif
#define c_fixed_fractionpart	Fixed_FractionPart	//!< @alias{Fixed_FractionPart}
#define c_q16_fractionpart		Q16_FractionPart	//!< @alias{Q16_FractionPart}
#define c_q32_fractionpart		Q32_FractionPart	//!< @alias{Q32_FractionPart}
#define c_q64_fractionpart		Q64_FractionPart	//!< @alias{Q64_FractionPart}
#define c_q128_fractionpart		Q128_FractionPart	//!< @alias{Q128_FractionPart}
//!@}



/*
** ************************************************************************** *|
**                          Fixed-to-String Conversions                       *|
** ************************************************************************** *|
*/



//! Get the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString	CONCAT(FIXED_TYPE,_ToString)
_MALLOC()	t_char*		Q16_ToString(t_q16 number); // TODO implement
_MALLOC()	t_char*		Q32_ToString(t_q32 number); // TODO implement
_MALLOC()	t_char*		Q64_ToString(t_q64 number); // TODO implement
#ifdef	__int128
_MALLOC()	t_char*		Q128_ToString(t_q128 number); // TODO implement
#endif
#define c_qtostr		Fixed_ToString	//!< @alias{Fixed_ToString}
#define c_q16tostr		Q16_ToString	//!< @alias{Q16_ToString}
#define c_q32tostr		Q32_ToString	//!< @alias{Q32_ToString}
#define c_q64tostr		Q64_ToString	//!< @alias{Q64_ToString}
#define c_q128tostr		Q128_ToString	//!< @alias{Q128_ToString}
//!@}



//! Get the string hexadecimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Hex	CONCAT(FIXED_TYPE,_ToString_Hex)
_MALLOC()	t_char*		Q16_ToString_Hex(t_q16 number); // TODO implement
_MALLOC()	t_char*		Q32_ToString_Hex(t_q32 number); // TODO implement
_MALLOC()	t_char*		Q64_ToString_Hex(t_q64 number); // TODO implement
#ifdef	__int128
_MALLOC()	t_char*		Q128_ToString_Hex(t_q128 number); // TODO implement
#endif
#define c_qtostrhex		Fixed_ToString_Hex	//!< @alias{Fixed_ToString_Hex}
#define c_q16tostrhex	Q16_ToString_Hex	//!< @alias{Q16_ToString_Hex}
#define c_q32tostrhex	Q32_ToString_Hex	//!< @alias{Q32_ToString_Hex}
#define c_q64tostrhex	Q64_ToString_Hex	//!< @alias{Q64_ToString_Hex}
#define c_q128tostrhex	Q128_ToString_Hex	//!< @alias{Q128_ToString_Hex}
//!@}



//! Get the string octal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Oct	CONCAT(FIXED_TYPE,_ToString_Oct)
_MALLOC()	t_char*		Q16_ToString_Oct(t_q16 number); // TODO implement
_MALLOC()	t_char*		Q32_ToString_Oct(t_q32 number); // TODO implement
_MALLOC()	t_char*		Q64_ToString_Oct(t_q64 number); // TODO implement
#ifdef	__int128
_MALLOC()	t_char*		Q128_ToString_Oct(t_q128 number); // TODO implement
#endif
#define c_qtostroct		Fixed_ToString_Oct	//!< @alias{Fixed_ToString_Oct}
#define c_q16tostroct	Q16_ToString_Oct	//!< @alias{Q16_ToString_Oct}
#define c_q32tostroct	Q32_ToString_Oct	//!< @alias{Q32_ToString_Oct}
#define c_q64tostroct	Q64_ToString_Oct	//!< @alias{Q64_ToString_Oct}
#define c_q128tostroct	Q128_ToString_Oct	//!< @alias{Q128_ToString_Oct}
//!@}



//! Get the string binary representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Bin	CONCAT(FIXED_TYPE,_ToString_Bin)
_MALLOC()	t_char*		Q16_ToString_Bin(t_q16 number); // TODO implement
_MALLOC()	t_char*		Q32_ToString_Bin(t_q32 number); // TODO implement
_MALLOC()	t_char*		Q64_ToString_Bin(t_q64 number); // TODO implement
#ifdef	__int128
_MALLOC()	t_char*		Q128_ToString_Bin(t_q128 number); // TODO implement
#endif
#define c_qtostrbin		Fixed_ToString_Bin	//!< @alias{Fixed_ToString_Bin}
#define c_q16tostrbin	Q16_ToString_Bin	//!< @alias{Q16_ToString_Bin}
#define c_q32tostrbin	Q32_ToString_Bin	//!< @alias{Q32_ToString_Bin}
#define c_q64tostrbin	Q64_ToString_Bin	//!< @alias{Q64_ToString_Bin}
#define c_q128tostrbin	Q128_ToString_Bin	//!< @alias{Q128_ToString_Bin}
//!@}



//! Get the custom-base representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@param	base	The numerical base to use to represent the given `number`
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Base	CONCAT(FIXED_TYPE,_ToString_Base)
_MALLOC()	t_char*		Q16_ToString_Base(t_q16 number, t_char const* base); // TODO implement
_MALLOC()	t_char*		Q32_ToString_Base(t_q32 number, t_char const* base); // TODO implement
_MALLOC()	t_char*		Q64_ToString_Base(t_q64 number, t_char const* base); // TODO implement
#ifdef	__int128
_MALLOC()	t_char*		Q128_ToString_Base(t_q128 number, t_char const* base); // TODO implement
#endif
#define c_qtostrbase	Fixed_ToString_Base	//!< @alias{Fixed_ToString_Base}
#define c_q16tostrbase	Q16_ToString_Base	//!< @alias{Q16_ToString_Base}
#define c_q32tostrbase	Q32_ToString_Base	//!< @alias{Q32_ToString_Base}
#define c_q64tostrbase	Q64_ToString_Base	//!< @alias{Q64_ToString_Base}
#define c_q128tostrbase	Q128_ToString_Base	//!< @alias{Q128_ToString_Base}
//!@}



/*
** ************************************************************************** *|
**                          String-to-Fixed Conversions                       *|
** ************************************************************************** *|
*/



//! Parses the string representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString	CONCAT(FIXED_TYPE,_FromString)
t_q16					Q16_FromString(t_char const* str); // TODO implement
t_q32					Q32_FromString(t_char const* str); // TODO implement
t_q64					Q64_FromString(t_char const* str); // TODO implement
#ifdef	__int128
t_q128					Q128_FromString(t_char const* str); // TODO implement
#endif
#define c_strtoq		Fixed_FromString//!< @alias{Fixed_FromString}
#define c_strtoq16		Q16_FromString	//!< @alias{Q16_FromString}
#define c_strtoq32		Q32_FromString	//!< @alias{Q32_FromString}
#define c_strtoq64		Q64_FromString	//!< @alias{Q64_FromString}
#define c_strtoq128		Q128_FromString	//!< @alias{Q128_FromString}
//!@}



//! Parses the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Dec	CONCAT(FIXED_TYPE,_FromString)
t_q16					Q16_FromString_Dec(t_char const* str); // TODO implement
t_q32					Q32_FromString_Dec(t_char const* str); // TODO implement
t_q64					Q64_FromString_Dec(t_char const* str); // TODO implement
#ifdef	__int128
t_q128					Q128_FromString_Dec(t_char const* str); // TODO implement
#endif
#define c_strdectoq		Fixed_FromString_Dec//!< @alias{Fixed_FromString_Dec}
#define c_strdectoq16	Q16_FromString_Dec	//!< @alias{Q16_FromString_Dec}
#define c_strdectoq32	Q32_FromString_Dec	//!< @alias{Q32_FromString_Dec}
#define c_strdectoq64	Q64_FromString_Dec	//!< @alias{Q64_FromString_Dec}
#define c_strdectoq128	Q128_FromString_Dec	//!< @alias{Q128_FromString_Dec}
//!@}



//! Parses the string hexadecimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Hex	CONCAT(FIXED_TYPE,_FromString_Hex)
t_q16					Q16_FromString_Hex(t_char const* str); // TODO implement
t_q32					Q32_FromString_Hex(t_char const* str); // TODO implement
t_q64					Q64_FromString_Hex(t_char const* str); // TODO implement
#ifdef	__int128
t_q128					Q128_FromString_Hex(t_char const* str); // TODO implement
#endif
#define c_strhextoq		Fixed_FromString_Hex//!< @alias{Fixed_FromString_Hex}
#define c_strhextoq16	Q16_FromString_Hex	//!< @alias{Q16_FromString_Hex}
#define c_strhextoq32	Q32_FromString_Hex	//!< @alias{Q32_FromString_Hex}
#define c_strhextoq64	Q64_FromString_Hex	//!< @alias{Q64_FromString_Hex}
#define c_strhextoq128	Q128_FromString_Hex	//!< @alias{Q128_FromString_Hex}
//!@}



//! Parses the string octal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Oct	CONCAT(FIXED_TYPE,_FromString_Oct)
t_q16					Q16_FromString_Oct(t_char const* str); // TODO implement
t_q32					Q32_FromString_Oct(t_char const* str); // TODO implement
t_q64					Q64_FromString_Oct(t_char const* str); // TODO implement
#ifdef	__int128
t_q128					Q128_FromString_Oct(t_char const* str); // TODO implement
#endif
#define c_strocttoq		Fixed_FromString_Oct//!< @alias{Fixed_FromString_Oct}
#define c_strocttoq16	Q16_FromString_Oct	//!< @alias{Q16_FromString_Oct}
#define c_strocttoq32	Q32_FromString_Oct	//!< @alias{Q32_FromString_Oct}
#define c_strocttoq64	Q64_FromString_Oct	//!< @alias{Q64_FromString_Oct}
#define c_strocttoq128	Q128_FromString_Oct	//!< @alias{Q128_FromString_Oct}
//!@}



//! Parses the string binary representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Bin	CONCAT(FIXED_TYPE,_FromString_Bin)
t_q16					Q16_FromString_Bin(t_char const* str); // TODO implement
t_q32					Q32_FromString_Bin(t_char const* str); // TODO implement
t_q64					Q64_FromString_Bin(t_char const* str); // TODO implement
#ifdef	__int128
t_q128					Q128_FromString_Bin(t_char const* str); // TODO implement
#endif
#define c_strbintoq		Fixed_FromString_Bin//!< @alias{Fixed_FromString_Bin}
#define c_strbintoq16	Q16_FromString_Bin	//!< @alias{Q16_FromString_Bin}
#define c_strbintoq32	Q32_FromString_Bin	//!< @alias{Q32_FromString_Bin}
#define c_strbintoq64	Q64_FromString_Bin	//!< @alias{Q64_FromString_Bin}
#define c_strbintoq128	Q128_FromString_Bin	//!< @alias{Q128_FromString_Bin}
//!@}



//! Parses the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@param	base	The numerical base used to represent the given `number`
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Base	CONCAT(FIXED_TYPE,_FromString_Base)
t_q16					Q16_FromString_Base(t_char const* str, t_char const* base); // TODO implement
t_q32					Q32_FromString_Base(t_char const* str, t_char const* base); // TODO implement
t_q64					Q64_FromString_Base(t_char const* str, t_char const* base); // TODO implement
#ifdef	__int128
t_q128					Q128_FromString_Base(t_char const* str, t_char const* base); // TODO implement
#endif
#define c_strbasetoq	Fixed_FromString_Base 	//!< @alias{Fixed_FromString_Base}
#define c_strbasetoq16	Q16_FromString_Base 	//!< @alias{Q16_FromString_Base}
#define c_strbasetoq32	Q32_FromString_Base 	//!< @alias{Q32_FromString_Base}
#define c_strbasetoq64	Q64_FromString_Base 	//!< @alias{Q64_FromString_Base}
#define c_strbasetoq128	Q128_FromString_Base 	//!< @alias{Q128_FromString_Base}
//!@}



#endif

/*! @} */
HEADER_END
#endif
