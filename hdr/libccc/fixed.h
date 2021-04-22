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

// TODO make fixed-point type have configurable denominator, not just bitwise point ?

//! The amount of bits dedicated to the fixed-point number type's fractional number part
#define FIXED_BITS_FRACTIONPART	LIBCONFIG_FIXED_BITS_FRACTIONPART
#define FIXED_MASK_FRACTIONPART	(((CONCAT(t_s,LIBCONFIG_BITS_FIXED))1 << FIXED_BITS_FRACTIONPART) - 1)
#define FIXED_MAX_FRACTIONPART	 ((CONCAT(t_s,LIBCONFIG_BITS_FIXED))1 << FIXED_BITS_FRACTIONPART)

//! The amount of bits dedicated to the fixed-point number type's integer number part
#define FIXED_BITS_INTEGERPART	LIBCONFIG_FIXED_BITS_INTEGERPART
#define FIXED_MASK_INTEGERPART	((((CONCAT(t_s,LIBCONFIG_BITS_FIXED))1 << FIXED_BITS_INTEGERPART) - 1) << FIXED_BITS_FRACTIONPART)
#define FIXED_MAX_INTEGERPART	  ((CONCAT(t_s,LIBCONFIG_BITS_FIXED))1 << FIXED_BITS_INTEGERPART)



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



//! The actual underlying type for the `t_fixed` configurable type
#define FIXED_T			CONCAT(t_q,LIBCONFIG_BITS_FIXED)
//! The actual underlying type for the `t_fixed` configurable type, in uppercase
#define FIXED_TYPE		CONCAT(Q,LIBCONFIG_BITS_FIXED)

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



/*!
**	This very small float is typically used to compare two fixed-point values.
**	Since fixed-point types have a configurable fractional portion, it can be useful
**	to have the Fixed_EqualsApprox() functions for approximate equality checks.
**	@see not to be confused with #FLOAT_EPSILON
*/
#define FIXED_APPROX	LIBCONFIG_FIXED_APPROX



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

#define FIXED_MAX	((t_fixed)SINT_MAX)	//!< The largest possible value that a configurable-size fixed-point can hold
#define FIXED_MIN	((t_fixed)SINT_MIN)	//!< The largest possible value that a configurable-size fixed-point can hold



/*
** ************************************************************************** *|
**                         Fixed-point number functions                       *|
** ************************************************************************** *|
*/



//! Create a new fixed-point value from its individual component parts
/*!
**	TODO document
**	@param	part_integer	the integer portion of the fixed-point number
**	@param	part_fraction	the fractional portion of the fixed-point number
**	@param	denominator		the denominator applied to this fixed-point number
**	@returns
*/
//!@{
#define				Fixed	CONCAT(FIXED_TYPE,)
#define c_fixed		Fixed 	//!< @alias{Fixed}

t_q16				Q16(t_s16 part_integer, t_u16 part_fraction, t_u16 denominator);
#define c_q16		Q16 	//!< @alias{Q16}

t_q32				Q32(t_s32 part_integer, t_u32 part_fraction, t_u32 denominator);
#define c_q32		Q32 	//!< @alias{Q32}

t_q64				Q64(t_s64 part_integer, t_u64 part_fraction, t_u64 denominator);
#define c_q64		Q64 	//!< @alias{Q64}
#ifdef __int128
t_q128				Q128(t_s128 part_integer, t_u128 part_fraction, t_u128 denominator);
#define c_q128		Q128 	//!< @alias{Q128}
#endif
//!@}



//! 
/*!
**	TODO document
*/
//!@{
#define					Fixed_FromInt	CONCAT(FIXED_TYPE,_FromInt)
#define c_itofixed		Fixed_FromInt 	//!< @alias{Fixed_FromInt}

t_q16					Q16_FromInt(t_s16 number);
#define c_itoq16		Q16_FromInt 	//!< @alias{Q16_FromInt}

t_q32					Q32_FromInt(t_s32 number);
#define c_itoq32		Q32_FromInt 	//!< @alias{Q32_FromInt}

t_q64					Q64_FromInt(t_s64 number);
#define c_itoq64		Q64_FromInt 	//!< @alias{Q64_FromInt}
#ifdef __int128
t_q128					Q128_FromInt(t_s128 number);
#define c_itoq128		Q128_FromInt 	//!< @alias{Q128_FromInt}
#endif
//!@}

//! 
/*!
**	TODO document
*/
//!@{
#define	 				Fixed_FromFloat	CONCAT(FIXED_TYPE,_FromFloat)
#define c_ftofixed		Fixed_FromFloat	//!< @alias{Fixed_FromFloat}

t_q16	 				Q16_FromFloat(t_f64 number);
#define c_ftoq16		Q16_FromFloat	//!< @alias{Q16_FromFloat}

t_q32	 				Q32_FromFloat(t_f64 number);
#define c_ftoq32		Q32_FromFloat	//!< @alias{Q32_FromFloat}

t_q64	 				Q64_FromFloat(t_f64 number);
#define c_ftoq64		Q64_FromFloat	//!< @alias{Q64_FromFloat}
#ifdef __int128
t_q128	 				Q128_FromFloat(t_f64 number);
#define c_ftoq128		Q128_FromFloat	//!< @alias{Q128_FromFloat}
#endif
//!@}



//! 
/*!
**	TODO document
*/
//!@{
#define							Fixed_IntegerPart	CONCAT(FIXED_TYPE,_IntegerPart)
#define c_fixed_integerpart		Fixed_IntegerPart	//!< @alias{Fixed_IntegerPart}

t_q16							Q16_IntegerPart(t_q16 number);
#define c_q16_integerpart		Q16_IntegerPart	//!< @alias{Q16_IntegerPart}

t_q32							Q32_IntegerPart(t_q32 number);
#define c_q32_integerpart		Q32_IntegerPart	//!< @alias{Q32_IntegerPart}

t_q64							Q64_IntegerPart(t_q64 number);
#define c_q64_integerpart		Q64_IntegerPart	//!< @alias{Q64_IntegerPart}

#ifdef __int128
t_q128							Q128_IntegerPart(t_q128 number);
#define c_q128_integerpart		Q128_IntegerPart	//!< @alias{Q128_IntegerPart}
#endif
//!@}

//! 
/*!
**	TODO document
*/
//!@{
#define							Fixed_FractionPart	CONCAT(FIXED_TYPE,_FractionPart)
#define c_fixed_fractionpart	Fixed_FractionPart	//!< @alias{Fixed_FractionPart}

t_q16							Q16_FractionPart(t_q16 number);
#define c_q16_fractionpart		Q16_FractionPart	//!< @alias{Q16_FractionPart}

t_q32							Q32_FractionPart(t_q32 number);
#define c_q32_fractionpart		Q32_FractionPart	//!< @alias{Q32_FractionPart}

t_q64							Q64_FractionPart(t_q64 number);
#define c_q64_fractionpart		Q64_FractionPart	//!< @alias{Q64_FractionPart}

#ifdef __int128
t_q128							Q128_FractionPart(t_q128 number);
#define c_q128_fractionpart		Q128_FractionPart	//!< @alias{Q128_FractionPart}
#endif
//!@}



//! Returns the nearest integer value to the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define					Fixed_Rounded	CONCAT(FIXED_TYPE,_Rounded)
#define c_fixed_round	Fixed_Rounded	//!< @alias{Fixed_Rounded}

t_q16					Q16_Rounded(t_q16 number);
#define c_q16_round		Q16_Rounded	//!< @alias{Q16_Rounded}

t_q32					Q32_Rounded(t_q32 number);
#define c_q32_round		Q32_Rounded	//!< @alias{Q32_Rounded}

t_q64					Q64_Rounded(t_q64 number);
#define c_q64_round		Q64_Rounded	//!< @alias{Q64_Rounded}

#ifdef __int128
t_q128					Q128_Rounded(t_q128 number);
#define c_q128_round	Q128_Rounded	//!< @alias{Q128_Rounded}

#endif
//!@}



/*
** ************************************************************************** *|
**                         Fixed-point basic operators                        *|
** ************************************************************************** *|
*/



//! Performs an addition between the 2 given floating-point values (operator: `+`)
//!@{
#define				Fixed_Add	CONCAT(FIXED_TYPE,_Add)
#define c_qadd		Fixed_Add	//! @alias{Fixed_Add}

t_q16				Q16_Add(t_q16 number1, t_q16 number2);
#define c_q16add	Q16_Add 	//! @alias{Q16_Add}

t_q32				Q32_Add(t_q32 number1, t_q32 number2);
#define c_q32add	Q32_Add 	//! @alias{Q32_Add}

t_q64				Q64_Add(t_q64 number1, t_q64 number2);
#define c_q64add	Q64_Add 	//! @alias{Q64_Add}

#ifdef __int128
t_q128				Q128_Add(t_q128 number1, t_q128 number2);
#define c_q128add	Q128_Add 	//! @alias{Q128_Add}
#endif
//!@}

//! Performs an addition between the 2 given floating-point values (operator: `-`)
//!@{
#define				Fixed_Sub	CONCAT(FIXED_TYPE,_Sub)
#define c_qsub		Fixed_Sub	//! @alias{Fixed_Sub}

t_q16				Q16_Sub(t_q16 number1, t_q16 number2);
#define c_q16sub	Q16_Sub 	//! @alias{Q16_Sub}

t_q32				Q32_Sub(t_q32 number1, t_q32 number2);
#define c_q32sub	Q32_Sub 	//! @alias{Q32_Sub}

t_q64				Q64_Sub(t_q64 number1, t_q64 number2);
#define c_q64sub	Q64_Sub 	//! @alias{Q64_Sub}

#ifdef __int128
t_q128				Q128_Sub(t_q128 number1, t_q128 number2);
#define c_q128sub	Q128_Sub 	//! @alias{Q128_Sub}
#endif
//!@}

//! Performs an addition between the 2 given floating-point values (operator: `*`)
//!@{
#define				Fixed_Mul	CONCAT(FIXED_TYPE,_Mul)
#define c_qmul		Fixed_Mul	//! @alias{Fixed_Mul}

t_q16				Q16_Mul(t_q16 number1, t_q16 number2);
#define c_q16mul	Q16_Mul 	//! @alias{Q16_Mul}

t_q32				Q32_Mul(t_q32 number1, t_q32 number2);
#define c_q32mul	Q32_Mul 	//! @alias{Q32_Mul}

t_q64				Q64_Mul(t_q64 number1, t_q64 number2);
#define c_q64mul	Q64_Mul 	//! @alias{Q64_Mul}

#ifdef __int128
t_q128				Q128_Mul(t_q128 number1, t_q128 number2);
#define c_q128mul	Q128_Mul 	//! @alias{Q128_Mul}
#endif
//!@}

//! Performs a division between the 2 given floating-point values (operator: `/`)
//!@{
#define				Fixed_Div	CONCAT(FIXED_TYPE,_Div)
#define c_qdiv		Fixed_Div	//! @alias{Fixed_Div}

t_q16				Q16_Div(t_q16 number1, t_q16 number2);
#define c_q16div	Q16_Div 	//! @alias{Q16_Div}

t_q32				Q32_Div(t_q32 number1, t_q32 number2);
#define c_q32div	Q32_Div 	//! @alias{Q32_Div}

t_q64				Q64_Div(t_q64 number1, t_q64 number2);
#define c_q64div	Q64_Div 	//! @alias{Q64_Div}

#ifdef __int128
t_q128				Q128_Div(t_q128 number1, t_q128 number2);
#define c_q128div	Q128_Div 	//! @alias{Q128_Div}
#endif
//!@}



/*
** ************************************************************************** *|
**                         Fixed-point logic operators                        *|
** ************************************************************************** *|
*/



//! Returns 1(TRUE) if the 2 given floating-point values are exactly equal (operator: `==`)
/*!
**	@param	number1	The first value to check for (exact) equality
**	@param	number2	The second value to check for (exact) equality
**	@returns 1(TRUE) if the 2 given floating-point values are exactly equal, 0(FALSE) otherwise.
*/
//!@{
#define					Fixed_Equals	CONCAT(FLOAT_TYPE,_Equals)
#define c_qequ			Fixed_Equals	//!< @alias{Fixed_Equals}

t_bool					Q32_Equals(t_q32 number1, t_q32 number2);
#define c_q32equ		Q32_Equals	//!< @alias{Q32_Equals}

t_bool					Q64_Equals(t_q64 number1, t_q64 number2);
#define c_q64equ		Q64_Equals	//!< @alias{Q64_Equals}

#ifdef	__float80
t_bool					Q80_Equals(t_q80 number1, t_q80 number2);
#define c_q80equ		Q80_Equals	//!< @alias{Q80_Equals}
#endif
#ifdef	__float128
t_bool					Q128_Equals(t_q128 number1, t_q128 number2);
#define c_q128equ		Q128_Equals	//!< @alias{Q128_Equals}
#endif
//!@}



//! Returns 1(TRUE) if the 2 given floating-point values are close enough to be considered equal (operator: `=~`, using FLOAT_APPROX)
/*!
**	@param	number1	The first value to check for (approximate) equality
**	@param	number2	The second value to check for (approximate) equality
**	@returns 1(TRUE) if the 2 given floating-point values are close enough to be considered equal
**		(using FLOAT_BIAS as a comparison margin), or 0(FALSE) otherwise.
*/
//!@{
#define					Fixed_EqualsApprox	CONCAT(FLOAT_TYPE,_EqualsApprox)
#define c_qequa			Fixed_EqualsApprox	//!< @alias{Fixed_EqualsApprox}

t_bool					Q32_EqualsApprox(t_q32 number1, t_q32 number2);
#define c_q32equa		Q32_EqualsApprox	//!< @alias{Q32_EqualsApprox}

t_bool					Q64_EqualsApprox(t_q64 number1, t_q64 number2);
#define c_q64equa		Q64_EqualsApprox	//!< @alias{Q64_EqualsApprox}

#ifdef	__float80
t_bool					Q80_EqualsApprox(t_q80 number1, t_q80 number2);
#define c_q80equa		Q80_EqualsApprox	//!< @alias{Q80_EqualsApprox}
#endif
#ifdef	__float128
t_bool					Q128_EqualsApprox(t_q128 number1, t_q128 number2);
#define c_q128equa		Q128_EqualsApprox	//!< @alias{Q128_EqualsApprox}
#endif
//!@}



// TODO Fixed_LessThan

// TODO Fixed_GreaterThan



/*
** ************************************************************************** *|
**                          Fixed-to-String Conversions                       *|
** ************************************************************************** *|
*/



//! Get the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns A newly allocated string, converted from the given `q`
*/
//!@{
#define					Fixed_ToString	CONCAT(FIXED_TYPE,_ToString)
#define c_qtostr		Fixed_ToString	//!<  @alias{Fixed_ToString}

_MALLOC()	char*		Q16_ToString(t_q16 number); // TODO implement
#define c_q16tostr		Q16_ToString	//!< @alias{Q16_ToString}

_MALLOC()	char*		Q32_ToString(t_q32 number); // TODO implement
#define c_q32tostr		Q32_ToString	//!< @alias{Q32_ToString}

_MALLOC()	char*		Q64_ToString(t_q64 number); // TODO implement
#define c_q64tostr		Q64_ToString	//!< @alias{Q64_ToString}

#ifdef	__int128
_MALLOC()	char*		Q128_ToString(t_q128 number); // TODO implement
#define c_q128tostr		Q128_ToString	//!< @alias{Q128_ToString}
#endif
//!@}



//! Get the string hexadecimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns A newly allocated string, converted from the given `q`
*/
//!@{
#define					Fixed_ToString_Hex	CONCAT(FIXED_TYPE,_ToString_Hex)
#define c_qtostrhex		Fixed_ToString_Hex	//!<  @alias{Fixed_ToString_Hex}

_MALLOC()	char*		Q16_ToString_Hex(t_q16 number); // TODO implement
#define c_q16tostrhex	Q16_ToString_Hex	//!< @alias{Q16_ToString_Hex}

_MALLOC()	char*		Q32_ToString_Hex(t_q32 number); // TODO implement
#define c_q32tostrhex	Q32_ToString_Hex	//!< @alias{Q32_ToString_Hex}

_MALLOC()	char*		Q64_ToString_Hex(t_q64 number); // TODO implement
#define c_q64tostrhex	Q64_ToString_Hex	//!< @alias{Q64_ToString_Hex}

#ifdef	__int128
_MALLOC()	char*		Q128_ToString_Hex(t_q128 number); // TODO implement
#define c_q128tostrhex	Q128_ToString_Hex	//!< @alias{Q128_ToString_Hex}
#endif
//!@}



//! Get the string binary representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns A newly allocated string, converted from the given `q`
*/
//!@{
#define					Fixed_ToString_Bin	CONCAT(FIXED_TYPE,_ToString_Bin)
#define c_qtostrbin		Fixed_ToString_Bin	//!<  @alias{Fixed_ToString_Bin}

_MALLOC()	char*		Q16_ToString_Bin(t_q16 number); // TODO implement
#define c_q16tostrbin	Q16_ToString_Bin	//!< @alias{Q16_ToString_Bin}

_MALLOC()	char*		Q32_ToString_Bin(t_q32 number); // TODO implement
#define c_q32tostrbin	Q32_ToString_Bin	//!< @alias{Q32_ToString_Bin}

_MALLOC()	char*		Q64_ToString_Bin(t_q64 number); // TODO implement
#define c_q64tostrbin	Q64_ToString_Bin	//!< @alias{Q64_ToString_Bin}

#ifdef	__int128
_MALLOC()	char*		Q128_ToString_Bin(t_q128 number); // TODO implement
#define c_q128tostrbin	Q128_ToString_Bin	//!< @alias{Q128_ToString_Bin}
#endif
//!@}



//! Get the custom-base representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@param	base	The numerical base to use to represent the given `number`
**	@returns A newly allocated string, converted from the given `q`
*/
//!@{
#define					Fixed_ToString_Base	CONCAT(FIXED_TYPE,_ToString_Base)
#define c_qtostrbase	Fixed_ToString_Base	//!<  @alias{Fixed_ToString_Base}

_MALLOC()	char*		Q16_ToString_Base(t_q16 number, char const* base); // TODO implement
#define c_q16tostrbase	Q16_ToString_Base	//!< @alias{Q16_ToString_Base}

_MALLOC()	char*		Q32_ToString_Base(t_q32 number, char const* base); // TODO implement
#define c_q32tostrbase	Q32_ToString_Base	//!< @alias{Q32_ToString_Base}

_MALLOC()	char*		Q64_ToString_Base(t_q64 number, char const* base); // TODO implement
#define c_q64tostrbase	Q64_ToString_Base	//!< @alias{Q64_ToString_Base}

#ifdef	__int128
_MALLOC()	char*		Q128_ToString_Base(t_q128 number, char const* base); // TODO implement
#define c_q128tostrbase	Q128_ToString_Base	//!< @alias{Q128_ToString_Base}
#endif
//!@}



/*
** ************************************************************************** *|
**                          String-to-Fixed Conversions                       *|
** ************************************************************************** *|
*/



//! Parses the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns A newly allocated string, converted from the given `q`,
**		or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString	CONCAT(FIXED_TYPE,_FromString)
#define c_strtoq		Fixed_FromString	//!<  @alias{Fixed_FromString}

t_q16					Q16_FromString(char const* str); // TODO implement
#define c_strtoq16		Q16_FromString //!< @alias{Q16_FromString}

t_q32					Q32_FromString(char const* str); // TODO implement
#define c_strtoq32		Q32_FromString //!< @alias{Q32_FromString}

t_q64					Q64_FromString(char const* str); // TODO implement
#define c_strtoq64		Q64_FromString //!< @alias{Q64_FromString}

#ifdef	__int128
t_q128					Q128_FromString(char const* str); // TODO implement
#define c_strtoq128		Q128_FromString //!< @alias{Q128_FromString}
#endif
//!@}



//! Parses the string hexadecimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns A newly allocated string, converted from the given `q`,
**		or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Hex	CONCAT(FIXED_TYPE,_FromString_Hex)
#define c_strhextoq		Fixed_FromString_Hex	//!<  @alias{Fixed_FromString_Hex}

t_q16					Q16_FromString_Hex(char const* str); // TODO implement
#define c_strhextoq16	Q16_FromString_Hex //!< @alias{Q16_FromString_Hex}

t_q32					Q32_FromString_Hex(char const* str); // TODO implement
#define c_strhextoq32	Q32_FromString_Hex //!< @alias{Q32_FromString_Hex}

t_q64					Q64_FromString_Hex(char const* str); // TODO implement
#define c_strhextoq64	Q64_FromString_Hex //!< @alias{Q64_FromString_Hex}

#ifdef	__int128
t_q128					Q128_FromString_Hex(char const* str); // TODO implement
#define c_strhextoq128	Q128_FromString_Hex //!< @alias{Q128_FromString_Hex}
#endif
//!@}



//! Parses the string binary representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns A newly allocated string, converted from the given `q`,
**		or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Bin	CONCAT(FIXED_TYPE,_FromString_Bin)
#define c_strbintoq		Fixed_FromString_Bin	//!<  @alias{Fixed_FromString_Bin}

t_q16					Q16_FromString_Bin(char const* str); // TODO implement
#define c_strbintoq16	Q16_FromString_Bin //!< @alias{Q16_FromString_Bin}

t_q32					Q32_FromString_Bin(char const* str); // TODO implement
#define c_strbintoq32	Q32_FromString_Bin //!< @alias{Q32_FromString_Bin}

t_q64					Q64_FromString_Bin(char const* str); // TODO implement
#define c_strbintoq64	Q64_FromString_Bin //!< @alias{Q64_FromString_Bin}

#ifdef	__int128
t_q128					Q128_FromString_Bin(char const* str); // TODO implement
#define c_strbintoq128	Q128_FromString_Bin //!< @alias{Q128_FromString_Bin}
#endif
//!@}



//! Parses the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@param	base	The numerical base used to represent the given `number`
**	@returns A newly allocated string, converted from the given `q`,
**		or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Base	CONCAT(FIXED_TYPE,_FromString_Base)
#define c_strbasetoq	Fixed_FromString_Base	//!<  @alias{Fixed_FromString_Base}

t_q16					Q16_FromString_Base(char const* str, char const* base); // TODO implement
#define c_strbasetoq16	Q16_FromString_Base //!< @alias{Q16_FromString_Base}

t_q32					Q32_FromString_Base(char const* str, char const* base); // TODO implement
#define c_strbasetoq32	Q32_FromString_Base //!< @alias{Q32_FromString_Base}

t_q64					Q64_FromString_Base(char const* str, char const* base); // TODO implement
#define c_strbasetoq64	Q64_FromString_Base //!< @alias{Q64_FromString_Base}

#ifdef	__int128
t_q128					Q128_FromString_Base(char const* str, char const* base); // TODO implement
#define c_strbasetoq128	Q128_FromString_Base //!< @alias{Q128_FromString_Base}
#endif
//!@}



/*! @} */
HEADER_END
#endif
