/*============================================================================*\
||                                            ______________________________  ||
||  libccc/fixed.h                           |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_FIXED_H
#define __LIBCCC_FIXED_H
/*!@group{libccc_fixed,13,libccc/fixed.h}
**
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
*/

/*============================================================================*\
||                                  Includes                                  ||
\*============================================================================*/

#include "libccc.h"
#include "libccc/int.h"

HEADER_CPP

#ifndef __LIBCCC_FIXED_T
#define __LIBCCC_FIXED_T

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

// TODO make fixed-point type have configurable denominator, not just bitwise point ?

//! The maximum value of the fixed-point number type's fractional number part
#define FIXED_MAX_FRACTIONPART	(LIBCONFIG_FIXED_DENOMINATOR - 1)

//! The amount of bits dedicated to the fixed-point number type's integer number part
#define FIXED_MAX_INTEGERPART	(CONCAT(CONCAT(S,LIBCONFIG_FIXED_BITS),_MAX) / LIBCONFIG_FIXED_DENOMINATOR)
#define FIXED_MIN_INTEGERPART	(CONCAT(CONCAT(S,LIBCONFIG_FIXED_BITS),_MIN) / LIBCONFIG_FIXED_DENOMINATOR)



#if LIBCONFIG_USE_STD_FIXEDPOINT



#if (!defined(__STDC__) || (__STDC_VERSION__ < __STDC_VERSION_C17__))
	#error "C ISO standard fixed-point types are not available for this C standard: "__STDC_VERSION__"L"
#endif

#ifndef __NOSTD__
	#include <stdfix.h>
#else
	#error "Cannot use standard fixed-point library, __NOSTD__ macro is defined"
#endif

//!@doc Primitive type: 16-bit signed fixed-point rational number (s4.7)
/*!
**	@nonstd
**
**	Fixed-point rational number type which has, at minimum:
**	- 4 bits dedicated to the integer part
**	- 7 bits dedicated to the fractional part
**	The largest possible value for this type is #Q16_MAX.
*/
//!@{
typedef _Sat short _Accum	t_q16;
TYPEDEF_ALIAS(t_q16,	FIXED_16,	PRIMITIVE)
//!@}

//!@doc Primitive type: 32-bit signed fixed-point rational numbers (s4.15)
/*!
**	@nonstd
**
**	Fixed-point rational number type which has, at minimum:
**	- 4 bits dedicated to the integer part
**	- 15 bits dedicated to the fractional part
**	The largest possible value for this type is #Q32_MAX.
*/
//!@{
typedef _Sat _Accum	t_q32;
TYPEDEF_ALIAS(t_q32,	FIXED_32,	PRIMITIVE)
//!@}

//!@doc Primitive type: 64-bit signed fixed-point rational numbers (s4.24)
/*!
**	@nonstd
**
**	Fixed-point rational number type which has, at minimum:
**	- 4 bits dedicated to the integer part
**	- 24 bits dedicated to the fractional part
**	The largest possible value for this type is #Q64_MAX.
*/
//!@{
typedef	_Sat long _Accum	t_q64;
TYPEDEF_ALIAS(t_q64,	FIXED_64,	PRIMITIVE)
//!@}

#if (LIBCONFIG_FIXED_BITS == 128)
	#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
#endif



#else

//!@doc Primitive type: 16-bit signed fixed-point rational number (configurable bit portions)
/*!
**	@nonstd
**
**	Fixed-point rational number type which is 16 bits in size.
**	Which amount is dedicated to the fraction/integer part is
**	determined by the value of #FIXED_BITS_FRACTIONPART.
**	All the other `#define`s depend on this one macro.
**	The largest possible value for this type is #Q16_MAX.
*/
//!@{
typedef s16_t	t_q16;
TYPEDEF_ALIAS(	t_q16,	FIXED_16,	PRIMITIVE)
//!@}

//!@doc Primitive type: 32-bit signed fixed-point rational number (configurable bit portions)
/*!
**	@nonstd
**
**	Fixed-point rational number type which is 32 bits in size.
**	Which amount is dedicated to the fraction/integer part is
**	determined by the value of #FIXED_BITS_FRACTIONPART.
**	All the other `#define`s depend on this one macro.
**	The largest possible value for this type is #Q32_MAX.
*/
//!@{
typedef s32_t	t_q32;
TYPEDEF_ALIAS(	t_q32,	FIXED_32,	PRIMITIVE)
//!@}

//!@doc Primitive type: 64-bit signed fixed-point rational number (configurable bit portions)
/*!
**	@nonstd
**
**	Fixed-point rational number type which is 64 bits in size.
**	Which amount is dedicated to the fraction/integer part is
**	determined by the value of #FIXED_BITS_FRACTIONPART.
**	All the other `#define`s depend on this one macro.
**	The largest possible value for this type is #Q64_MAX.
*/
//!@{
typedef	s64_t	t_q64;
TYPEDEF_ALIAS(	t_q64,	FIXED_64,	PRIMITIVE)
//!@}

#if LIBCONFIG_USE_INT128
//!@doc Primitive type: 128-bit signed fixed-point rational number (only certain platforms)
/*!
**	@nonstd
**
**	Fixed-point rational number type which is 128 bits in size.
**	Which amount is dedicated to the fraction/integer part is
**	determined by the value of #FIXED_BITS_FRACTIONPART.
**	All the other `#define`s depend on this one macro.
**	The largest possible value for this type is #Q128_MAX.
*/
//!@{
typedef s128_t	t_q128;
TYPEDEF_ALIAS(	t_q128,	FIXED_128,	PRIMITIVE)
//!@}

#elif (LIBCONFIG_FIXED_BITS == 128)
	#error "Cannot set default 't_fixed' to 128-bit size, unavailable on this platform"
#endif

#endif



//! The actual underlying type for the `t_fixed` configurable type
#define FIXED_T			CONCAT(t_q,LIBCONFIG_FIXED_BITS)
//! The actual underlying type for the `t_fixed` configurable type, in uppercase
#define FIXED_TYPE		CONCAT(Q,LIBCONFIG_FIXED_BITS)
//! the denominator/divisor for this fixed-point number type, @see #LIBCONFIG_FIXED_DENOMINATOR
#define FIXED_DENOMINATOR	LIBCONFIG_FIXED_DENOMINATOR


//!@doc The configurable-size fixed-point number primitive type.
/*!
**	@nonstd
**
**	Configurable-width fixed-point rational number type.
**	The size of this fixed-point type depends on the value of #LIBCONFIG_FIXED_BITS.
**	The portion dedicated to the fractional part depends on the value of #FIXED_BITS_FRACTIONPART.
**	All the other important `#define`s depend on this one macro (FIXED_BITS_FRACTIONPART).
**	This type can express a number between #FIXED_MIN and #FIXED_MAX.
*/
//!@{
typedef	FIXED_T	t_fixed;
TYPEDEF_ALIAS(t_fixed, FIXED_128, PRIMITIVE)
//!@}



#if(LIBCONFIG_FIXED_BITS != 16 && \
	LIBCONFIG_FIXED_BITS != 32 && \
	LIBCONFIG_FIXED_BITS != 64 && \
	LIBCONFIG_FIXED_BITS != 128)
	#error "LIBCONFIG_FIXED_BITS must be equal to one of: 16, 32, 64, 128"
#endif

#if (FIXED_DENOMINATOR == 0)
	#error "LIBCONFIG_FIXED_DENOMINATOR must never be 0 (cannot divide by zero)"
#endif



#undef FIXED_ERROR
#undef FIXED_MAX
#undef FIXED_MIN

#if (LIBCONFIG_FIXED_NAN == 0) && (LIBCONFIG_FIXED_INF == 0)

	#define Q16_MIN_INT	((t_q16)(Q16_MIN_VAL / FIXED_DENOMINATOR))
	#define Q16_MAX_INT	((t_q16)(Q16_MAX_VAL / FIXED_DENOMINATOR))
	#define Q16_MIN_VAL	Q16_MIN
	#define Q16_MAX_VAL	Q16_MAX
	#define Q16_MIN		((t_q16)0x8000) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_MAX		((t_q16)0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold

	#define Q32_MIN_INT	((t_q32)(Q32_MIN_VAL / FIXED_DENOMINATOR))
	#define Q32_MAX_INT	((t_q32)(Q32_MAX_VAL / FIXED_DENOMINATOR))
	#define Q32_MIN_VAL	Q32_MIN
	#define Q32_MAX_VAL	Q32_MAX
	#define Q32_MIN		((t_q32)0x80000000) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_MAX		((t_q32)0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold

	#define Q64_MIN_INT	((t_q64)(Q64_MIN_VAL / FIXED_DENOMINATOR))
	#define Q64_MAX_INT	((t_q64)(Q64_MAX_VAL / FIXED_DENOMINATOR))
	#define Q64_MIN_VAL	Q64_MIN
	#define Q64_MAX_VAL	Q64_MAX
	#define Q64_MIN		((t_q64)0x8000000000000000) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_MAX		((t_q64)0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold

	#if LIBCONFIG_USE_INT128
	#define Q128_MIN_INT	((t_q128)(Q128_MIN_VAL / FIXED_DENOMINATOR))
	#define Q128_MAX_INT	((t_q128)(Q128_MAX_VAL / FIXED_DENOMINATOR))
	#define Q128_MIN_VAL	Q128_MIN
	#define Q128_MAX_VAL	Q128_MAX
	#define Q128_MIN		((t_q128)(((t_q128)0x8000000000000000 << 64) | 0x0000000000000000)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_MAX		((t_q128)(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#endif

	#define FIXED_MIN_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_INT))
	#define FIXED_MAX_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_INT))
	#define FIXED_MIN_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_VAL))
	#define FIXED_MAX_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_VAL))
	#define FIXED_MIN		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN)) //!< The minimum possible value that a configurable-size fixed-point can represent
	#define FIXED_MAX		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX)) //!< The maximum possible value that a configurable-size fixed-point can represent

#elif (LIBCONFIG_SINT_NAN)

	#define Q16_MIN_INT	((t_q16)(Q16_MIN_VAL / FIXED_DENOMINATOR))
	#define Q16_MAX_INT	((t_q16)(Q16_MAX_VAL / FIXED_DENOMINATOR))
	#define Q16_MIN_VAL	Q16_MIN
	#define Q16_MAX_VAL	Q16_MAX
	#define Q16_MIN		((t_q16)-0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_MAX		((t_q16)+0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_NAN		((t_q16) 0x8000)

	#define Q32_MIN_INT	((t_q32)(Q32_MIN_VAL / FIXED_DENOMINATOR))
	#define Q32_MAX_INT	((t_q32)(Q32_MAX_VAL / FIXED_DENOMINATOR))
	#define Q32_MIN_VAL	Q32_MIN
	#define Q32_MAX_VAL	Q32_MAX
	#define Q32_MIN		((t_q32)-0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_MAX		((t_q32)+0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_NAN		((t_q32) 0x80000000)

	#define Q64_MIN_INT	((t_q64)(Q64_MIN_VAL / FIXED_DENOMINATOR))
	#define Q64_MAX_INT	((t_q64)(Q64_MAX_VAL / FIXED_DENOMINATOR))
	#define Q64_MIN_VAL	Q64_MIN
	#define Q64_MAX_VAL	Q64_MAX
	#define Q64_MIN		((t_q64)-0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_MAX		((t_q64)+0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_NAN		((t_q64) 0x8000000000000000)

	#if LIBCONFIG_USE_INT128
	#define Q128_MIN_INT	((t_q128)(Q128_MIN_VAL / FIXED_DENOMINATOR))
	#define Q128_MAX_INT	((t_q128)(Q128_MAX_VAL / FIXED_DENOMINATOR))
	#define Q128_MIN_VAL	Q128_MIN
	#define Q128_MAX_VAL	Q128_MAX
	#define Q128_MIN		((t_q128)-(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_MAX		((t_q128)+(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_NAN		((t_q128) (((t_q128)0x8000000000000000 << 64) | 0x0000000000000000))
	#endif

	#define FIXED_MIN_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_INT))
	#define FIXED_MAX_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_INT))
	#define FIXED_MIN_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_VAL))
	#define FIXED_MAX_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_VAL))
	#define FIXED_MIN		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN)) //!< The minimum possible value that a configurable-size fixed-point can represent
	#define FIXED_MAX		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX)) //!< The maximum possible value that a configurable-size fixed-point can represent
	#define FIXED_NAN		((t_fixed)((t_fixed)1 << (LIBCONFIG_FIXED_BITS - 1)))

#elif (LIBCONFIG_SINT_INF)

	#define Q16_MIN_INT	((t_q16)(Q16_MIN_VAL / FIXED_DENOMINATOR))
	#define Q16_MAX_INT	((t_q16)(Q16_MAX_VAL / FIXED_DENOMINATOR))
	#define Q16_MIN_VAL	Q16_MIN
	#define Q16_MAX_VAL	Q16_MAX
	#define Q16_MIN		((t_q16)-0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_MAX		((t_q16)+0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_INF		((t_q16) 0x8000)

	#define Q32_MIN_INT	((t_q32)(Q32_MIN_VAL / FIXED_DENOMINATOR))
	#define Q32_MAX_INT	((t_q32)(Q32_MAX_VAL / FIXED_DENOMINATOR))
	#define Q32_MIN_VAL	Q32_MIN
	#define Q32_MAX_VAL	Q32_MAX
	#define Q32_MIN		((t_q32)-0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_MAX		((t_q32)+0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_INF		((t_q32) 0x80000000)

	#define Q64_MIN_INT	((t_q64)(Q64_MIN_VAL / FIXED_DENOMINATOR))
	#define Q64_MAX_INT	((t_q64)(Q64_MAX_VAL / FIXED_DENOMINATOR))
	#define Q64_MIN_VAL	Q64_MIN
	#define Q64_MAX_VAL	Q64_MAX
	#define Q64_MIN		((t_q64)-0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_MAX		((t_q64)+0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_INF		((t_q64) 0x8000000000000000)

	#if LIBCONFIG_USE_INT128
	#define Q128_MIN_INT	((t_q128)(Q128_MIN_VAL / FIXED_DENOMINATOR))
	#define Q128_MAX_INT	((t_q128)(Q128_MAX_VAL / FIXED_DENOMINATOR))
	#define Q128_MIN_VAL	Q128_MIN
	#define Q128_MAX_VAL	Q128_MAX
	#define Q128_MIN		((t_q128)-(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_MAX		((t_q128)+(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_INF		((t_q128) (((t_q128)0x8000000000000000 << 64) | 0x0000000000000000))
	#endif

	#define FIXED_MIN_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_INT))
	#define FIXED_MAX_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_INT))
	#define FIXED_MIN_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_VAL))
	#define FIXED_MAX_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_VAL))
	#define FIXED_MIN		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN)) //!< The minimum possible value that a configurable-size fixed-point can represent
	#define FIXED_MAX		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX)) //!< The maximum possible value that a configurable-size fixed-point can represent
	#define FIXED_INF		((t_fixed)((t_fixed)1 << (LIBCONFIG_FIXED_BITS - 1)))

#else

	#define Q16_MIN_INT	((t_q16)(Q16_MIN_VAL / FIXED_DENOMINATOR))
	#define Q16_MAX_INT	((t_q16)(Q16_MAX_VAL / FIXED_DENOMINATOR))
	#define Q16_MIN_VAL	((t_q16)-0x7FFE)
	#define Q16_MAX_VAL	((t_q16)+0x7FFE)
	#define Q16_MIN		((t_q16)-0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_MAX		((t_q16)+0x7FFF) //!< The largest possible value that a 16-bit fixed-point can hold
	#define Q16_INF		((t_q16)+0x7FFF)
	#define Q16_NAN		((t_q16) 0x8000)

	#define Q32_MIN_INT	((t_q32)(Q32_MIN_VAL / FIXED_DENOMINATOR))
	#define Q32_MAX_INT	((t_q32)(Q32_MAX_VAL / FIXED_DENOMINATOR))
	#define Q32_MIN_VAL	((t_q32)-0x7FFFFFFE)
	#define Q32_MAX_VAL	((t_q32)+0x7FFFFFFE)
	#define Q32_MIN		((t_q32)-0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_MAX		((t_q32)+0x7FFFFFFF) //!< The largest possible value that a 32-bit fixed-point can hold
	#define Q32_INF		((t_q32)+0x7FFFFFFF)
	#define Q32_NAN		((t_q32) 0x80000000)

	#define Q64_MIN_INT	((t_q64)(Q64_MIN_VAL / FIXED_DENOMINATOR))
	#define Q64_MAX_INT	((t_q64)(Q64_MAX_VAL / FIXED_DENOMINATOR))
	#define Q64_MIN_VAL	((t_q64)-0x7FFFFFFFFFFFFFFE)
	#define Q64_MAX_VAL	((t_q64)+0x7FFFFFFFFFFFFFFE)
	#define Q64_MIN		((t_q64)-0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_MAX		((t_q64)+0x7FFFFFFFFFFFFFFF) //!< The largest possible value that a 64-bit fixed-point can hold
	#define Q64_INF		((t_q64)+0x7FFFFFFFFFFFFFFF)
	#define Q64_NAN		((t_q64) 0x8000000000000000)

	#if LIBCONFIG_USE_INT128
	#define Q128_MIN_INT	((t_q128)(Q128_MIN_VAL / FIXED_DENOMINATOR))
	#define Q128_MAX_INT	((t_q128)(Q128_MAX_VAL / FIXED_DENOMINATOR))
	#define Q128_MIN_VAL	((t_q128)-(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define Q128_MAX_VAL	((t_q128)+(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define Q128_MIN		((t_q128)-(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_MAX		((t_q128)+(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest possible value that a 128-bit fixed-point can hold
	#define Q128_INF		((t_q128)+(((t_q128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))
	#define Q128_NAN		((t_q128) (((t_q128)0x8000000000000000 << 64) | 0x0000000000000000))
	#endif

	#define FIXED_MIN_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_INT))
	#define FIXED_MAX_INT	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_INT))
	#define FIXED_MIN_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN_VAL))
	#define FIXED_MAX_VAL	((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX_VAL))
	#define FIXED_MIN		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MIN)) //!< The minimum possible value that a configurable-size fixed-point can represent
	#define FIXED_MAX		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX)) //!< The maximum possible value that a configurable-size fixed-point can represent
	#define FIXED_INF		((t_fixed)CONCAT(CONCAT(Q,LIBCONFIG_FIXED_BITS),_MAX))
	#define FIXED_NAN		((t_fixed)((t_fixed)1 << (LIBCONFIG_FIXED_BITS - 1)))

#endif

//!@doc Macros which define the default error value of integer types
//!@{
#if (LIBCONFIG_SINT_NAN)
	#define Q8_ERROR	Q8_NAN
	#define Q16_ERROR	Q16_NAN
	#define Q32_ERROR	Q32_NAN
	#define Q64_ERROR	Q64_NAN
	#if LIBCONFIG_USE_INT128
	#define Q128_ERROR	Q128_NAN
	#endif
	#define FIXED_ERROR	FIXED_NAN
#else
	#define Q8_ERROR	((t_q8)0)
	#define Q16_ERROR	((t_q16)0)
	#define Q32_ERROR	((t_q32)0)
	#define Q64_ERROR	((t_q64)0)
	#if LIBCONFIG_USE_INT128
	#define Q128_ERROR	((t_q128)0)
	#endif
	#define FIXED_ERROR	((t_fixed)0)
#endif
//!@}



#endif
#ifndef __LIBCCC_FIXED_F
#define __LIBCCC_FIXED_F

/*============================================================================*\
||                         Fixed-point number functions                       ||
\*============================================================================*/

//!@doc A smart constructor: calls the appropriate `Fixed_From*()` function from the given argument type
//!@{
#define DEFINEFUNC_Fixed(X, FUNCTYPE) \
	_Generic((X), \
		t_u16:	 FUNCTYPE##_FromUInt, \
		t_u32:	 FUNCTYPE##_FromUInt, \
		t_u64:	 FUNCTYPE##_FromUInt, \
		t_u128:	 FUNCTYPE##_FromUInt, \
		t_uint:  FUNCTYPE##_FromUInt, \
		t_s16:	 FUNCTYPE##_FromSInt, \
		t_s32:	 FUNCTYPE##_FromSInt, \
		t_s64:	 FUNCTYPE##_FromSInt, \
		t_s128:	 FUNCTYPE##_FromSInt, \
		t_sint:  FUNCTYPE##_FromSInt, \
		t_q16:	 FUNCTYPE##_FromFixed, \
		t_q32:	 FUNCTYPE##_FromFixed, \
		t_q64:	 FUNCTYPE##_FromFixed, \
		t_q128:	 FUNCTYPE##_FromFixed, \
		t_fixed: FUNCTYPE##_FromFixed, \
		t_f32:	 FUNCTYPE##_FromFloat, \
		t_f64:	 FUNCTYPE##_FromFloat, \
		t_f80:	 FUNCTYPE##_FromFloat, \
		t_f128:	 FUNCTYPE##_FromFloat, \
		t_float: FUNCTYPE##_FromFloat, \
	)(X)
#define Fixed(X)	DEFINEFUNC_Fixed(X, Fixed)
#define Q16(X)		DEFINEFUNC_Fixed(X, Q16)
#define Q32(X)		DEFINEFUNC_Fixed(X, Q32)
#define Q64(X)		DEFINEFUNC_Fixed(X, Q64)
#define Q128(X)		DEFINEFUNC_Fixed(X, Q128)
//!@}

//!@doc Returns the nearest fixed-point value to the given unsigned integer `number`
/*!
**	TODO document this
*/
//!@{
#define					Fixed_FromUInt	CONCAT(FIXED_TYPE,_FromUInt)
#define c_utoq			Fixed_FromUInt

t_q16					Q16_FromUInt(t_uint number);
#define c_utoq16		Q16_FromUInt

t_q32					Q32_FromUInt(t_uint number);
#define c_utoq32		Q32_FromUInt

t_q64					Q64_FromUInt(t_uint number);
#define c_utoq64		Q64_FromUInt
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromUInt(t_uint number);
#define c_utoq128		Q128_FromUInt
#endif
//!@}

//!@doc Returns the nearest fixed-point value to the given signed integer `number`
/*!
**	TODO document this
*/
//!@{
#define					Fixed_FromSInt	CONCAT(FIXED_TYPE,_FromSInt)
#define c_stoq			Fixed_FromSInt

t_q16					Q16_FromSInt(t_sint number);
#define c_stoq16		Q16_FromSInt

t_q32					Q32_FromSInt(t_sint number);
#define c_stoq32		Q32_FromSInt

t_q64					Q64_FromSInt(t_sint number);
#define c_stoq64		Q64_FromSInt
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromSInt(t_sint number);
#define c_stoq128		Q128_FromSInt
#endif
//!@}

//!@doc Returns the nearest fixed-point value to the given fixed-point `number`
/*!
**	TODO document this
*/
//!@{
#define					Fixed_FromFixed	CONCAT(FIXED_TYPE,_FromFixed)
#define c_qtoq			Fixed_FromFixed

t_q16					Q16_FromFixed(t_fixed number);
#define c_qtoq16		Q16_FromFixed

t_q32					Q32_FromFixed(t_fixed number);
#define c_qtoq32		Q32_FromFixed

t_q64					Q64_FromFixed(t_fixed number);
#define c_qtoq64		Q64_FromFixed
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromFixed(t_fixed number);
#define c_qtoq128		Q128_FromFixed
#endif
//!@}

//!@doc Returns the nearest fixed-point value to the given floating-point `number`
/*!
**	TODO document this
*/
//!@{
#define	 				Fixed_FromFloat	CONCAT(FIXED_TYPE,_FromFloat)
#define c_ftoq			Fixed_FromFloat

t_q16	 				Q16_FromFloat(t_float number);
#define c_ftoq16		Q16_FromFloat

t_q32	 				Q32_FromFloat(t_float number);
#define c_ftoq32		Q32_FromFloat

t_q64	 				Q64_FromFloat(t_float number);
#define c_ftoq64		Q64_FromFloat
#if LIBCONFIG_USE_INT128
t_q128	 				Q128_FromFloat(t_float number);
#define c_ftoq128		Q128_FromFloat
#endif
//!@}



//!@doc Get the nearest fixed-point value from the given fraction/rational number
/*!
**	TODO document
$$	@param	numerator		the numerator: number at the top of the fraction
**	@param	denominator		the denominator: number at the bottom of the fraction
**	@returns
*/
//!@{
#define					Fixed_From	CONCAT(FIXED_TYPE,_From)
#define c_toq			Fixed_From

t_q16					Q16_From(t_s16 part_fraction, t_s16 denominator);
#define c_toq16			Q16_From

t_q32					Q32_From(t_s32 part_fraction, t_s32 denominator);
#define c_toq32			Q32_From

t_q64					Q64_From(t_s64 part_fraction, t_s64 denominator);
#define c_toq64			Q64_From
#if LIBCONFIG_USE_INT128
t_q128					Q128_From(t_s128 part_fraction, t_s128 denominator);
#define c_toq128		Q128_From
#endif
//!@}

//!@doc Returns the integer portion of the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define							Fixed_IntegerPart	CONCAT(FIXED_TYPE,_IntegerPart)
#define c_fixed_integerpart		Fixed_IntegerPart

t_s16							Q16_IntegerPart(t_q16 number);
#define c_q16_integerpart		Q16_IntegerPart

t_s32							Q32_IntegerPart(t_q32 number);
#define c_q32_integerpart		Q32_IntegerPart

t_s64							Q64_IntegerPart(t_q64 number);
#define c_q64_integerpart		Q64_IntegerPart
#if LIBCONFIG_USE_INT128
t_s128							Q128_IntegerPart(t_q128 number);
#define c_q128_integerpart		Q128_IntegerPart
#endif
//!@}

//!@doc Returns the fractional portion of the given fixed-point `number`
/*!
**	TODO document
*/
//!@{
#define							Fixed_FractionPart	CONCAT(FIXED_TYPE,_FractionPart)
#define c_fixed_fractionpart	Fixed_FractionPart

t_s16							Q16_FractionPart(t_q16 number);
#define c_q16_fractionpart		Q16_FractionPart

t_s32							Q32_FractionPart(t_q32 number);
#define c_q32_fractionpart		Q32_FractionPart

t_s64							Q64_FractionPart(t_q64 number);
#define c_q64_fractionpart		Q64_FractionPart
#if LIBCONFIG_USE_INT128
t_s128							Q128_FractionPart(t_q128 number);
#define c_q128_fractionpart		Q128_FractionPart
#endif
//!@}



/*============================================================================*\
||                          Fixed-to-String Conversions                       ||
\*============================================================================*/



//!@doc Get the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString	CONCAT(FIXED_TYPE,_ToString)
#define c_qtostr		Fixed_ToString

_MALLOC()	t_char*		Q16_ToString(t_q16 number); // TODO implement
#define c_q16tostr		Q16_ToString

_MALLOC()	t_char*		Q32_ToString(t_q32 number); // TODO implement
#define c_q32tostr		Q32_ToString

_MALLOC()	t_char*		Q64_ToString(t_q64 number); // TODO implement
#define c_q64tostr		Q64_ToString
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		Q128_ToString(t_q128 number); // TODO implement
#define c_q128tostr		Q128_ToString
#endif
//!@}



//!@doc Get the string hexadecimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Hex	CONCAT(FIXED_TYPE,_ToString_Hex)
#define c_qtostrhex		Fixed_ToString_Hex

_MALLOC()	t_char*		Q16_ToString_Hex(t_q16 number); // TODO implement
#define c_q16tostrhex	Q16_ToString_Hex

_MALLOC()	t_char*		Q32_ToString_Hex(t_q32 number); // TODO implement
#define c_q32tostrhex	Q32_ToString_Hex

_MALLOC()	t_char*		Q64_ToString_Hex(t_q64 number); // TODO implement
#define c_q64tostrhex	Q64_ToString_Hex
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		Q128_ToString_Hex(t_q128 number); // TODO implement
#define c_q128tostrhex	Q128_ToString_Hex
#endif
//!@}



//!@doc Get the string octal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Oct	CONCAT(FIXED_TYPE,_ToString_Oct)
#define c_qtostroct		Fixed_ToString_Oct

_MALLOC()	t_char*		Q16_ToString_Oct(t_q16 number); // TODO implement
#define c_q16tostroct	Q16_ToString_Oct

_MALLOC()	t_char*		Q32_ToString_Oct(t_q32 number); // TODO implement
#define c_q32tostroct	Q32_ToString_Oct

_MALLOC()	t_char*		Q64_ToString_Oct(t_q64 number); // TODO implement
#define c_q64tostroct	Q64_ToString_Oct
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		Q128_ToString_Oct(t_q128 number); // TODO implement
#define c_q128tostroct	Q128_ToString_Oct
#endif
//!@}



//!@doc Get the string binary representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Bin	CONCAT(FIXED_TYPE,_ToString_Bin)
#define c_qtostrbin		Fixed_ToString_Bin

_MALLOC()	t_char*		Q16_ToString_Bin(t_q16 number); // TODO implement
#define c_q16tostrbin	Q16_ToString_Bin

_MALLOC()	t_char*		Q32_ToString_Bin(t_q32 number); // TODO implement
#define c_q32tostrbin	Q32_ToString_Bin

_MALLOC()	t_char*		Q64_ToString_Bin(t_q64 number); // TODO implement
#define c_q64tostrbin	Q64_ToString_Bin
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		Q128_ToString_Bin(t_q128 number); // TODO implement
#define c_q128tostrbin	Q128_ToString_Bin
#endif
//!@}



//!@doc Get the custom-base representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@param	base	The numerical base to use to represent the given `number`
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					Fixed_ToString_Base	CONCAT(FIXED_TYPE,_ToString_Base)
#define c_qtostrbase	Fixed_ToString_Base

_MALLOC()	t_char*		Q16_ToString_Base(t_q16 number, t_char const* base); // TODO implement
#define c_q16tostrbase	Q16_ToString_Base

_MALLOC()	t_char*		Q32_ToString_Base(t_q32 number, t_char const* base); // TODO implement
#define c_q32tostrbase	Q32_ToString_Base

_MALLOC()	t_char*		Q64_ToString_Base(t_q64 number, t_char const* base); // TODO implement
#define c_q64tostrbase	Q64_ToString_Base
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		Q128_ToString_Base(t_q128 number, t_char const* base); // TODO implement
#define c_q128tostrbase	Q128_ToString_Base
#endif
//!@}



/*============================================================================*\
||                          String-to-Fixed Conversions                       ||
\*============================================================================*/



// General parser functions



//!@doc Parse a fixed-point number from the given number string `str`
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Fixed_Parse	CONCAT(FIXED_TYPE,_Parse)
#define c_qparse		Fixed_Parse

t_size					Q16_Parse	(t_q16	*dest, t_char const* str, t_size n);
#define c_q16parse		Q16_Parse

t_size					Q32_Parse	(t_q32	*dest, t_char const* str, t_size n);
#define c_q32parse		Q32_Parse

t_size					Q64_Parse	(t_q64	*dest, t_char const* str, t_size n);
#define c_q64parse		Q64_Parse
#if LIBCONFIG_USE_INT128
t_size					Q128_Parse	(t_q128	*dest, t_char const* str, t_size n);
#define c_q128parse		Q128_Parse
#endif
//!@}

//!@doc Parses the string representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString	CONCAT(FIXED_TYPE,_FromString)
#define c_strtoq		Fixed_FromString

t_q16					Q16_FromString(t_char const* str); // TODO implement
#define c_strtoq16		Q16_FromString

t_q32					Q32_FromString(t_char const* str); // TODO implement
#define c_strtoq32		Q32_FromString

t_q64					Q64_FromString(t_char const* str); // TODO implement
#define c_strtoq64		Q64_FromString
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromString(t_char const* str); // TODO implement
#define c_strtoq128		Q128_FromString
#endif
//!@}



// Decimal parser functions



//!@doc Parse a fixed-point number from the given decimal number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be decimal number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Fixed_Parse_Dec	CONCAT(FIXED_TYPE,_Parse_Dec)
#define c_qparsedec		Fixed_Parse_Dec

t_size					Q16_Parse_Dec	(t_q16	*dest, t_char const* str, t_size n);
#define c_q16parsedec	Q16_Parse_Dec

t_size					Q32_Parse_Dec	(t_q32	*dest, t_char const* str, t_size n);
#define c_q32parsedec	Q32_Parse_Dec

t_size					Q64_Parse_Dec	(t_q64	*dest, t_char const* str, t_size n);
#define c_q64parsedec	Q64_Parse_Dec
#if LIBCONFIG_USE_INT128
t_size					Q128_Parse_Dec	(t_q128	*dest, t_char const* str, t_size n);
#define c_q128parsedec	Q128_Parse_Dec
#endif
//!@}

//!@doc Parses the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Dec	CONCAT(FIXED_TYPE,_FromString_Dec)
#define c_strdectoq		Fixed_FromString_Dec

t_q16					Q16_FromString_Dec(t_char const* str); // TODO implement
#define c_strdectoq16	Q16_FromString_Dec

t_q32					Q32_FromString_Dec(t_char const* str); // TODO implement
#define c_strdectoq32	Q32_FromString_Dec

t_q64					Q64_FromString_Dec(t_char const* str); // TODO implement
#define c_strdectoq64	Q64_FromString_Dec
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromString_Dec(t_char const* str); // TODO implement
#define c_strdectoq128	Q128_FromString_Dec
#endif
//!@}



// Hexadecimal parser functions



//!@doc Parse a fixed-point number from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 16) number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Fixed_Parse_Hex	CONCAT(FIXED_TYPE,_Parse_Hex)
#define c_qparsehex		Fixed_Parse_Hex

t_size					Q16_Parse_Hex	(t_q16	*dest, t_char const* str, t_size n);
#define c_q16parsehex	Q16_Parse_Hex

t_size					Q32_Parse_Hex	(t_q32	*dest, t_char const* str, t_size n);
#define c_q32parsehex	Q32_Parse_Hex

t_size					Q64_Parse_Hex	(t_q64	*dest, t_char const* str, t_size n);
#define c_q64parsehex	Q64_Parse_Hex
#if LIBCONFIG_USE_INT128
t_size					Q128_Parse_Hex	(t_q128	*dest, t_char const* str, t_size n);
#define c_q128parsehex	Q128_Parse_Hex
#endif
//!@}

//!@doc Parses the string hexadecimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Hex	CONCAT(FIXED_TYPE,_FromString_Hex)
#define c_strhextoq		Fixed_FromString_Hex

t_q16					Q16_FromString_Hex(t_char const* str); // TODO implement
#define c_strhextoq16	Q16_FromString_Hex

t_q32					Q32_FromString_Hex(t_char const* str); // TODO implement
#define c_strhextoq32	Q32_FromString_Hex

t_q64					Q64_FromString_Hex(t_char const* str); // TODO implement
#define c_strhextoq64	Q64_FromString_Hex
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromString_Hex(t_char const* str); // TODO implement
#define c_strhextoq128	Q128_FromString_Hex
#endif
//!@}



// Octal parser functions



//!@doc Parse a fixed-point number from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 8) number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Fixed_Parse_Oct	CONCAT(FIXED_TYPE,_Parse_Oct)
#define c_qparseoct		Fixed_Parse_Oct

t_size					Q16_Parse_Oct	(t_q16	*dest, t_char const* str, t_size n);
#define c_q16parseoct	Q16_Parse_Oct

t_size					Q32_Parse_Oct	(t_q32	*dest, t_char const* str, t_size n);
#define c_q32parseoct	Q32_Parse_Oct

t_size					Q64_Parse_Oct	(t_q64	*dest, t_char const* str, t_size n);
#define c_q64parseoct	Q64_Parse_Oct
#if LIBCONFIG_USE_INT128
t_size					Q128_Parse_Oct	(t_q128	*dest, t_char const* str, t_size n);
#define c_q128parseoct	Q128_Parse_Oct
#endif
//!@}

//!@doc Parses the string octal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Oct	CONCAT(FIXED_TYPE,_FromString_Oct)
#define c_strocttoq		Fixed_FromString_Oct

t_q16					Q16_FromString_Oct(t_char const* str); // TODO implement
#define c_strocttoq16	Q16_FromString_Oct

t_q32					Q32_FromString_Oct(t_char const* str); // TODO implement
#define c_strocttoq32	Q32_FromString_Oct

t_q64					Q64_FromString_Oct(t_char const* str); // TODO implement
#define c_strocttoq64	Q64_FromString_Oct
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromString_Oct(t_char const* str); // TODO implement
#define c_strocttoq128	Q128_FromString_Oct
#endif
//!@}



// Binary parser functions



//!@doc Parse a fixed-point number from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 2) number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Fixed_Parse_Bin	CONCAT(FIXED_TYPE,_Parse_Bin)
#define c_qparsebin		Fixed_Parse_Bin

t_size					Q16_Parse_Bin	(t_q16	*dest, t_char const* str, t_size n);
#define c_q16parsebin	Q16_Parse_Bin

t_size					Q32_Parse_Bin	(t_q32	*dest, t_char const* str, t_size n);
#define c_q32parsebin	Q32_Parse_Bin

t_size					Q64_Parse_Bin	(t_q64	*dest, t_char const* str, t_size n);
#define c_q64parsebin	Q64_Parse_Bin
#if LIBCONFIG_USE_INT128
t_size					Q128_Parse_Bin	(t_q128	*dest, t_char const* str, t_size n);
#define c_q128parsebin	Q128_Parse_Bin
#endif
//!@}

//!@doc Parses the string binary representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Bin	CONCAT(FIXED_TYPE,_FromString_Bin)
#define c_strbintoq		Fixed_FromString_Bin

t_q16					Q16_FromString_Bin(t_char const* str); // TODO implement
#define c_strbintoq16	Q16_FromString_Bin

t_q32					Q32_FromString_Bin(t_char const* str); // TODO implement
#define c_strbintoq32	Q32_FromString_Bin

t_q64					Q64_FromString_Bin(t_char const* str); // TODO implement
#define c_strbintoq64	Q64_FromString_Bin
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromString_Bin(t_char const* str); // TODO implement
#define c_strbintoq128	Q128_FromString_Bin
#endif
//!@}



// Custom-base parser functions



//!@doc Parse a fixed-point number from a custom-base number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be custom-base number string)
**	@param	n		The maximum amount of characters to parse (infinite if `0` is given)
**	@param	base	The custom numeric base to interpret, the char index being the digit.
**					The base string must have at least 2 chars, no sign chars, no duplicate chars.
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					Fixed_Parse_Base	CONCAT(FIXED_TYPE,_Parse_Base)
#define c_qparsebase	Fixed_Parse_Base

t_size					Q16_Parse_Base	(t_q16	*dest, t_char const* str, t_char const* base, t_size n);
#define c_q16parsebase	Q16_Parse_Base

t_size					Q32_Parse_Base	(t_q32	*dest, t_char const* str, t_char const* base, t_size n);
#define c_q32parsebase	Q32_Parse_Base

t_size					Q64_Parse_Base	(t_q64	*dest, t_char const* str, t_char const* base, t_size n);
#define c_q64parsebase	Q64_Parse_Base
#if LIBCONFIG_USE_INT128
t_size					Q128_Parse_Base	(t_q128	*dest, t_char const* str, t_char const* base, t_size n);
#define c_q128parsebase	Q128_Parse_Base
#endif
//!@}

//!@doc Parses the string decimal representation of a signed fixed-point number
/*!
**	@param	number	The number to convert to string
**	@param	base	The numerical base used to represent the given `number`
**	@returns
**	A newly allocated string, converted from the given `number`,
**	or `NULL` if there was a parsing error.
*/
//!@{
#define					Fixed_FromString_Base	CONCAT(FIXED_TYPE,_FromString_Base)
#define c_strbasetoq	Fixed_FromString_Base

t_q16					Q16_FromString_Base(t_char const* str, t_char const* base); // TODO implement
#define c_strbasetoq16	Q16_FromString_Base

t_q32					Q32_FromString_Base(t_char const* str, t_char const* base); // TODO implement
#define c_strbasetoq32	Q32_FromString_Base

t_q64					Q64_FromString_Base(t_char const* str, t_char const* base); // TODO implement
#define c_strbasetoq64	Q64_FromString_Base
#if LIBCONFIG_USE_INT128
t_q128					Q128_FromString_Base(t_char const* str, t_char const* base); // TODO implement
#define c_strbasetoq128	Q128_FromString_Base
#endif
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
