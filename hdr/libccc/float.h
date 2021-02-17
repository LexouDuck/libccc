/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/float.h                           |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_FLOAT_H
#define __LIBCCC_FLOAT_H
/*! @file libccc/float.h
**	This header defines the floating-point number primitive types and functions.
**	@defgroup libccc_float
**	@grouporder{3}
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
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

#if LIBCONFIG_BITS_FLOAT != 32 && \
	LIBCONFIG_BITS_FLOAT != 64 && \
	LIBCONFIG_BITS_FLOAT != 80 && \
	LIBCONFIG_BITS_FLOAT != 128
	#error "LIBCONFIG_BITS_UINT must be equal to one of: 32, 64, 80, 128"
#endif



//! The type for 32-bit 'single precision' IEEE-754 floating-point numbers
typedef float		t_f32;
TYPEDEF_ALIAS(		t_f32,	FLOAT_32,	PRIMITIVE)

//! The type for 64-bit 'double precision' IEEE-754 floating-point numbers
typedef double		t_f64;
TYPEDEF_ALIAS(		t_f64,	FLOAT_64,	PRIMITIVE)

#ifdef	__float80
typedef __float80	t_f80;	//!< The type for 32-bit 'extended precision' IEEE-754 floating-point numbers (only certain platforms)
TYPEDEF_ALIAS(		t_f80,	FLOAT_80,	PRIMITIVE)
#elif LIBCONFIG_BITS_FLOAT == 80
	#error "Cannot set default float to 80-bit extended-precision, unavailable on this platform"
#endif

#ifdef	__float128
typedef __float128	t_f128;	//!< The type for 32-bit 'quadruple precision' IEEE-754 floating-point numbers (only certain platforms)
TYPEDEF_ALIAS(		t_f128,	FLOAT_128,	PRIMITIVE)
#elif LIBCONFIG_BITS_FLOAT == 128
	#error "Cannot set default float to 128-bit quadruple-precision, unavailable on this platform"
#endif



//! The configurable-size floating-point number primitive type.
typedef LIBCONFIG_TYPE_FLOAT	t_float;
TYPEDEF_ALIAS(					t_float, FLOAT, PRIMITIVE)



#ifndef INFINITY		//! Define the floating-point infinity value: use -INFINITY for negative inf
#define INFINITY		(1. / 0.)
#endif
#ifndef IS_INFINITY		//! Checks if the given 'x' is either +INFINITY or -INFINITY
#define IS_INFINITY(X)	((X) == INFINITY || (X) == -INFINITY)
#endif
#ifndef INF
#define INF				INFINITY
#endif
#ifndef IS_INF
#define IS_INF(X)		IS_INFINITY(X)
#endif

#ifndef NAN				//! Define the floating-point "not a number" value.
#define NAN				(0. / 0.)
#endif
#ifndef IS_NAN			//! Checks if the given 'x' has a "not a number" value.
#define IS_NAN(X)		((X) != (X))
#endif



/*!
**	This very small float is typically used to compare two float values.
**	Floating point equality checks aren't the most dependable kind of operation,
**	so it's often better to do (ABS(x - y) <= FLOAT_BIAS) to check for equality.
*/
#define FLOAT_BIAS		(1.0e-10)

//	TODO document this
#define SAMPLE_NB		(1024)



//! If (value >= FLOAT_THRESHOLD_HUGE), Float_ToString() functions print in scientific notation
#define FLOAT_THRESHOLD_HUGE	(1e+9)
//! If (value <= FLOAT_THRESHOLD_TINY), Float_ToString() functions print in scientific notation
#define FLOAT_THRESHOLD_TINY	(1e-9)



/*
**	IEEE 754 32-bit floating point "single" precision bitwise macros
*/
#define F32_SIGNED			(0x80000000)	//!< A 32-bit floating-point number's sign bit (bitmask)
#define F32_EXPONENT_BIAS	(127)			//!< A 32-bit floating-point number's exponent bias offset
#define F32_EXPONENT		(0x7F800000)	//!< A 32-bit floating-point number's exponent bit region (bitmask)
#define F32_EXPONENT_ZERO	(0x3F800000)	//!< A 32-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F32_EXPONENT_BITS	(8)				//!< A 32-bit floating-point number's amount of bits dedicated to the exponent
#define F32_MANTISSA		(0x007FFFFF)	//!< A 32-bit floating-point number's mantissa bit region (bitmask)
#define F32_MANTISSA_SIGNED	(0x807FFFFF)	//!< A 32-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F32_MANTISSA_BITS	(23)			//!< A 32-bit floating-point number's amount of bits dedicated to the mantissa
#define F32_INIT_VALUE		(0x1.p-23)		//!< A 32-bit floating-point number's value if all bits are zero

/*
**	IEEE 754 64-bit floating point double-precision bitwise macros
*/
#define F64_SIGNED			(0x8000000000000000)	//!< A 64-bit floating-point number's sign bit (bitmask)
#define F64_EXPONENT_BIAS	(1023)					//!< A 64-bit floating-point number's exponent bias offset
#define F64_EXPONENT		(0x7FF0000000000000)	//!< A 64-bit floating-point number's exponent bit region (bitmask)
#define F64_EXPONENT_ZERO	(0x3FF0000000000000)	//!< A 64-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F64_EXPONENT_BITS	(11)					//!< A 64-bit floating-point number's amount of bits dedicated to the exponent
#define F64_MANTISSA		(0x000FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa bit region (bitmask)
#define F64_MANTISSA_SIGNED	(0x800FFFFFFFFFFFFF)	//!< A 64-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F64_MANTISSA_BITS	(52)					//!< A 64-bit floating-point number's amount of bits dedicated to the mantissa
#define F64_INIT_VALUE		(0x1.p-52)				//!< A 64-bit floating-point number's value if all bits are zero

/*
**	x86 80-bit floating point extended precision bitwise macros
*/
#define F80_SIGNED			(0x80000000000000000000L)	//!< A 80-bit floating-point number's sign bit (bitmask)
#define F80_EXPONENT_BIAS	(16383)						//!< A 80-bit floating-point number's exponent bias offset
#define F80_EXPONENT		(0x7FFF0000000000000000L)	//!< A 80-bit floating-point number's exponent bit region (bitmask)
#define F80_EXPONENT_ZERO	(0x3FFF0000000000000000L)	//!< A 80-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F80_EXPONENT_BITS	(15)						//!< A 80-bit floating-point number's amount of bits dedicated to the exponent
#define F80_MANTISSA		(0x0000FFFFFFFFFFFFFFFFL)	//!< A 80-bit floating-point number's mantissa bit region (bitmask)
#define F80_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFL)	//!< A 80-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F80_MANTISSA_BITS	(64)						//!< A 80-bit floating-point number's amount of bits dedicated to the mantissa
#define F80_INIT_VALUE		(0x1.p-64)					//!< A 80-bit floating-point number's value if all bits are zero

/*
**	IEEE 754 128-bit floating point quadruple-precision bitwise macros
*/
#define F128_SIGNED				(0x80000000000000000000000000000000L)	//!< A 128-bit floating-point number's sign bit (bitmask)
#define F128_EXPONENT_BIAS		(16383)									//!< A 128-bit floating-point number's exponent bias offset
#define F128_EXPONENT			(0x7FFF0000000000000000000000000000L)	//!< A 128-bit floating-point number's exponent bit region (bitmask)
#define F128_EXPONENT_ZERO		(0x3FFF0000000000000000000000000000L)	//!< A 128-bit floating-point number's 0-exponent value, accounting for bias (bitmask)
#define F128_EXPONENT_BITS		(15)									//!< A 128-bit floating-point number's amount of bits dedicated to the exponent
#define F128_MANTISSA			(0x0000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL)	//!< A 128-bit floating-point number's mantissa bit region (bitmask)
#define F128_MANTISSA_SIGNED	(0x8000FFFFFFFFFFFFFFFFFFFFFFFFFFFFL)	//!< A 128-bit floating-point number's mantissa and sign bit regions (bitmask)
#define F128_MANTISSA_BITS		(112)									//!< A 128-bit floating-point number's amount of bits dedicated to the mantissa
#define F128_INIT_VALUE			(0x1.p-112)								//!< A 128-bit floating-point number's value if all bits are zero



/*
**	Depending on the 't_float' type (_FLOAT_32_ or _FLOAT_64_, etc) chosen,
**	the appropriate bitwise macros will be used by the math functions.
**	It is often better to only use one type of floating-point precision
**	for a given program, so the best way to do that is by using the 'FLOAT_'
**	macros defined below, rather than the 'F32_' or 'F64_' macros above.
*/

#define FLOAT_SIGNED			CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_SIGNED)
#define FLOAT_EXPONENT_BIAS		CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_EXPONENT_BIAS)
#define FLOAT_EXPONENT			CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_EXPONENT)
#define FLOAT_EXPONENT_ZERO		CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_EXPONENT_ZERO)
#define FLOAT_EXPONENT_BITS		CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_EXPONENT_BITS)
#define FLOAT_MANTISSA			CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_MANTISSA)
#define FLOAT_MANTISSA_SIGNED	CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_MANTISSA_SIGNED)
#define FLOAT_MANTISSA_BITS		CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_MANTISSA_BITS)
#define FLOAT_INIT_VALUE		CONCAT(CONCAT(F,LIBCONFIG_BITS_FLOAT),_INIT_VALUE)



/*!
**	This union type is used in several math function implementations,
**	to manipulate float bits directly with bitwise operators.
*/
typedef union	u_float_cast_
{
	t_float		value_float;
#if LIBCONFIG_BITS_FLOAT == 32
	t_s32
#elif LIBCONFIG_BITS_FLOAT == 64
	t_s64
#else
	t_s64[2]
#endif
	value_int;
}				u_float_cast;



/*
** ************************************************************************** *|
**                         Float-to-String Conversions                        *|
** ************************************************************************** *|
*/

//! Get the shortest string representation of the given 32-bit floating-point number (dec or exp), with 'precision' fractional digits
_MALLOC()
char*						F32_ToString(t_f32 n, t_u8 precision);
#define c_f32_to_str		F32_ToString

//! Get the shortest string representation of the given 64-bit floating-point number (dec or exp), with 'precision' fractional digits
_MALLOC()
char*						F64_ToString(t_f64 n, t_u8 precision);
#define c_f64_to_str		F64_ToString

#ifdef	__float80
//! Get the shortest string representation of the given 80-bit floating-point number (dec or exp), with 'precision' fractional digits
_MALLOC()
char*						F80_ToString(t_f80 n, t_u8 precision);
#define c_f80_to_str		F80_ToString
#endif
#ifdef	__float128
//! Get the shortest string representation of the given 128-bit floating-point number (dec or exp), with 'precision' fractional digits
_MALLOC()
char*						F128_ToString(t_f128 n, t_u8 precision);
#define c_f128_to_str		F128_ToString
#endif

//! Get the shortest string representation of the given floating-point number (dec or exp), with 'precision' fractional digits
_MALLOC()
char*							Float_ToString(t_float n, t_u8 precision);
#define c_float_to_str			Float_ToString



//! Get the string scientific notation of a 32-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F32_ToString_Exp(t_f32 n, t_u8 precision);
#define c_f32_to_strexp				F32_ToString_Exp
#define c_f32_to_strsci				F32_ToString_Exp
#define F32_ToString_Exponential	F32_ToString_Exp
#define F32_ToString_Sci			F32_ToString_Exp
#define F32_ToString_Scientific		F32_ToString_Exp

//! Get the string scientific notation of a 64-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F64_ToString_Exp(t_f64 n, t_u8 precision);
#define c_f64_to_strexp				F64_ToString_Exp
#define c_f64_to_strsci				F64_ToString_Exp
#define F64_ToString_Exponential	F64_ToString_Exp
#define F64_ToString_Sci			F64_ToString_Exp
#define F64_ToString_Scientific		F64_ToString_Exp

#ifdef	__float80
//! Get the string scientific notation of a 80-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F80_ToString_Exp(t_f80 n, t_u8 precision);
#define c_f80_to_strexp				F80_ToString_Exp
#define c_f80_to_strsci				F80_ToString_Exp
#define F80_ToString_Exponential	F80_ToString_Exp
#define F80_ToString_Sci			F80_ToString_Exp
#define F80_ToString_Scientific		F80_ToString_Exp
#endif
#ifdef	__float128
//! Get the string scientific notation of a 128-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F128_ToString_Exp(t_f128 n, t_u8 precision);
#define c_f128_to_strexp			F128_ToString_Exp
#define c_f128_to_strsci			F128_ToString_Exp
#define F128_ToString_Exponential	F128_ToString_Exp
#define F128_ToString_Sci			F128_ToString_Exp
#define F128_ToString_Scientific	F128_ToString_Exp
#endif

//! Get the string scientific notation of a floating-point number, with 'precision' fractional digits
_MALLOC()
char*									Float_ToString_Exp(t_float n, t_u8 precision);
#define c_float_to_strexp				Float_ToString_Exp
#define c_float_to_strsci				Float_ToString_Exp
#define Float_ToString_Exponential		Float_ToString_Exp
#define Float_ToString_Sci				Float_ToString_Exp
#define Float_ToString_Scientific		Float_ToString_Exp



//! Get the string decimal representation of a 32-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F32_ToString_Dec(t_f32 n, t_u8 precision);
#define c_f32_to_strdec				F32_ToString_Dec
#define F32_ToString_Decimal		F32_ToString_Dec

//! Get the string decimal representation of a 64-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F64_ToString_Dec(t_f64 n, t_u8 precision);
#define c_f64_to_strdec				F64_ToString_Dec
#define F64_ToString_Decimal		F64_ToString_Dec

#ifdef	__float80
//! Get the string decimal representation of a 80-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F80_ToString_Dec(t_f80 n, t_u8 precision);
#define c_f80_to_strdec				F80_ToString_Dec
#define F80_ToString_Decimal		F80_ToString_Dec
#endif
#ifdef	__float128
//! Get the string decimal representation of a 128-bit floating-point number, with 'precision' fractional digits
_MALLOC()
char*								F128_ToString_Dec(t_f128 n, t_u8 precision);
#define c_f128_to_strdec			F128_ToString_Dec
#define F128_ToString_Decimal		F128_ToString_Dec
#endif

//! Get the string decimal representation of a floating-point number, with 'precision' fractional digits
_MALLOC()
char*									Float_ToString_Dec(t_float n, t_u8 precision);
#define c_float_to_strdec				Float_ToString_Dec
#define Float_ToString_Decimal			Float_ToString_Dec



//! Get the string hexadecimal representation of a 32-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F32_ToString_Hex(t_f32 n, t_u8 precision);
#define c_f32_to_strhex				F32_ToString_Hex
#define F32_ToString_Hexadecimal	F32_ToString_Hex

//! Get the string hexadecimal representation of a 64-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F64_ToString_Hex(t_f64 n, t_u8 precision);
#define c_f64_to_strhex				F64_ToString_Hex
#define F64_ToString_Hexadecimal	F64_ToString_Hex

#ifdef	__float80
//! Get the string hexadecimal representation of a 80-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F80_ToString_Hex(t_f80 n, t_u8 precision);
#define c_f80_to_strhex				F80_ToString_Hex
#define F80_ToString_Hexadecimal	F80_ToString_Hex
#endif
#ifdef	__float128
//! Get the string hexadecimal representation of a 128-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F128_ToString_Hex(t_f128 n, t_u8 precision);
#define c_f128_to_strhex			F128_ToString_Hex
#define F128_ToString_Hexadecimal	F128_ToString_Hex
#endif

//! Get the string hexadecimal representation of a floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*									Float_ToString_Hex(t_float n, t_u8 precision);
#define c_float_to_strhex				Float_ToString_Hex
#define Float_ToString_Hexadecimal		Float_ToString_Hex



//! Get the string binary representation of a 32-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F32_ToString_Bin(t_f32 n, t_u8 precision);
#define c_f32_to_strbin				F32_ToString_Bin
#define F32_ToString_Binary			F32_ToString_Bin

//! Get the string binary representation of a 64-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F64_ToString_Bin(t_f64 n, t_u8 precision);
#define c_f64_to_strbin				F64_ToString_Bin
#define F64_ToString_Binary			F64_ToString_Bin

#ifdef	__float80
//! Get the string binary representation of a 80-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F80_ToString_Bin(t_f80 n, t_u8 precision);
#define c_f80_to_strbin				F80_ToString_Bin
#define F80_ToString_Binary			F80_ToString_Bin
#endif
#ifdef	__float128
//! Get the string binary representation of a 128-bit floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*								F128_ToString_Bin(t_f128 n, t_u8 precision);
#define c_f128_to_strbin			F128_ToString_Bin
#define F128_ToString_Binary		F128_ToString_Bin
#endif

//! Get the string binary representation of a floating-point number, with 'precision' fractional digits (if 0, max precision)
_MALLOC()
char*									Float_ToString_Bin(t_float n, t_u8 precision);
#define c_float_to_strbin				Float_ToString_Bin
#define Float_ToString_Binary			Float_ToString_Bin



/*
** ************************************************************************** *|
**                         String-to-Float Conversions                        *|
** ************************************************************************** *|
*/

//! Parse a 32-bit floating-point number from the given string (can be decimal/exponential/hexdecimal)
t_f32					F32_FromString(char const* str);
#define c_str_to_f32	F32_FromString

//! Parse a 64-bit floating-point number from the given string (can be decimal/exponential/hexdecimal)
t_f64					F64_FromString(char const* str);
#define c_str_to_f64	F64_FromString

#ifdef	__float80
//! Parse a 80-bit floating-point number from the given string (can be decimal/exponential/hexdecimal)
t_f80					F80_FromString(char const* str);
#define c_str_to_f80	F80_FromString
#endif
#ifdef	__float128
//! Parse a 128-bit floating-point number from the given string (can be decimal/exponential/hexdecimal)
t_f128					F128_FromString(char const* str);
#define c_str_to_f128	F128_FromString
#endif

//! Parse a floating-point number from the given string (can be decimal/exponential/hexdecimal)
t_float						Float_FromString(char const* str);
#define c_str_to_float		Float_FromString



//! Parse the scientific notation of a 32-bit floating-point number
t_f32								F32_FromString_Exp(char const* str);
#define c_strexp_to_f32				F32_FromString_Exp
#define c_strsci_to_f32				F32_FromString_Exp
#define F32_FromString_Exponential	F32_FromString_Exp
#define F32_FromString_Sci			F32_FromString_Exp
#define F32_FromString_Scientific	F32_FromString_Exp

//! Parse the scientific notation of a 64-bit floating-point number
t_f64								F64_FromString_Exp(char const* str);
#define c_strexp_to_f64				F64_FromString_Exp
#define c_strsci_to_f64				F64_FromString_Exp
#define F64_FromString_Exponential	F64_FromString_Exp
#define F64_FromString_Sci			F64_FromString_Exp
#define F64_FromString_Scientific	F64_FromString_Exp

#ifdef	__float80
//! Parse the scientific notation of a 80-bit floating-point number
t_f80								F80_FromString_Exp(char const* str);
#define c_strexp_to_f80				F80_FromString_Exp
#define c_strsci_to_f80				F80_FromString_Exp
#define F80_FromString_Exponential	F80_FromString_Exp
#define F80_FromString_Sci			F80_FromString_Exp
#define F80_FromString_Scientific	F80_FromString_Exp
#endif
#ifdef	__float128
//! Parse the scientific notation of a 128-bit floating-point number
t_f128								F128FromoString_Exp(char const* str);
#define c_strexp_to_f128			F128FromoString_Exp
#define c_strsci_to_f128			F128FromoString_Exp
#define F128_FromString_Exponential	F128FromoString_Exp
#define F128_FromString_Sci			F128FromoString_Exp
#define F128_FromString_Scientific	F128FromoString_Exp
#endif

//! Parse the scientific notation of a floating-point number
t_float									Float_FromString_Exp(char const* str);
#define c_strexp_to_float				Float_FromString_Exp
#define c_strsci_to_float				Float_FromString_Exp
#define Float_FromString_Exponential	Float_FromString_Exp
#define Float_FromString_Sci			Float_FromString_Exp
#define Float_FromString_Scientific		Float_FromString_Exp



//! Parse the decimal representation of a 32-bit floating-point number
t_f32								F32_FromString_Dec(char const* str);
#define c_strdec_to_f32				F32_FromString_Dec
#define F32_FromString_Decimal		F32_FromString_Dec

//! Parse the decimal representation of a 64-bit floating-point number
t_f64								F64_FromString_Dec(char const* str);
#define c_strdec_to_f64				F64_FromString_Dec
#define F64_FromString_Decimal		F64_FromString_Dec

#ifdef	__float80
//! Parse the decimal representation of a 80-bit floating-point number
t_f80								F80_FromString_Dec(char const* str);
#define c_strdec_to_f80				F80_FromString_Dec
#define F80_FromString_Decimal		F80_FromString_Dec
#endif
#ifdef	__float128
//! Parse the decimal representation of a 128-bit floating-point number
t_f128								F128_FromString_Dec(char const* str);
#define c_strdec_to_f128			F128_FromString_Dec
#define F128_FromString_Decimal		F128_FromString_Dec
#endif

//! Parse the decimal representation of a floating-point number
t_float									Float_FromString_Dec(char const* str);
#define c_strdec_to_float				Float_FromString_Dec
#define Float_FromString_Decimal		Float_FromString_Dec



//! Parse the hexadecimal representation of a 32-bit floating-point number
t_f32								F32_FromString_Hex(char const* str);
#define c_strhex_to_f32				F32_FromString_Hex
#define F32_FromString_Hexadecimal	F32_FromString_Hex

//! Parse the hexadecimal representation of a 64-bit floating-point number
t_f64								F64_FromString_Hex(char const* str);
#define c_strhex_to_f64				F64_FromString_Hex
#define F64_FromString_Hexadecimal	F64_FromString_Hex

#ifdef	__float80
//! Parse the hexadecimal representation of a 80-bit floating-point number
t_f80								F80_FromString_Hex(char const* str);
#define c_strhex_to_f80				F80_FromString_Hex
#define F80_FromString_Hexadecimal	F80_FromString_Hex
#endif
#ifdef	__float128
//! Parse the hexadecimal representation of a 128-bit floating-point number
t_f128								F128_FromString_Hex(char const* str);
#define c_strhex_to_f128			F128_FromString_Hex
#define F128_FromString_Hexadecimal	F128_FromString_Hex
#endif

//! Parse the hexadecimal representation of a floating-point number
t_float									Float_FromString_Hex(char const* str);
#define c_strhex_to_float				Float_FromString_Hex
#define Float_FromString_Hexadecimal	Float_FromString_Hex



//! Parse the binary representation of a 32-bit floating-point number
t_f32								F32_FromString_Bin(char const* str);
#define c_strbin_to_f32				F32_FromString_Bin
#define F32_FromString_Binary		F32_FromString_Bin

//! Parse the binary representation of a 64-bit floating-point number
t_f64								F64_FromString_Bin(char const* str);
#define c_strbin_to_f64				F64_FromString_Bin
#define F64_FromString_Binary		F64_FromString_Bin

#ifdef	__float80
//! Parse the binary representation of a 80-bit floating-point number
t_f80								F80_FromString_Bin(char const* str);
#define c_strbin_to_f80				F80_FromString_Bin
#define F80_FromString_Binary		F80_FromString_Bin
#endif
#ifdef	__float128
//! Parse the binary representation of a 128-bit floating-point number
t_f128								F128_FromString_Bin(char const* str);
#define c_strbin_to_f128			F128_FromString_Bin
#define F128_FromString_Binary		F128_FromString_Bin
#endif

//! Parse the binary representation of a floating-point number
t_float									Float_FromString_Bin(char const* str);
#define c_strbin_to_float				Float_FromString_Bin
#define Float_FromString_Binary			Float_FromString_Bin



/*
** ************************************************************************** *|
**                       Variable-size primitive types                        *|
** ************************************************************************** *|
*/

//! A union storing a floating-point number of any common size/precision
/*!
** These unions are used for certain difficult casting conditions.
** They are used in particular when casting an <stdarg.h> var_arg to the
** appropriate type in c_printf.
*/
typedef union		u_varfloat_
{
	t_f32			f;
	t_f64			d;
#ifdef	__float80
	t_f80			e;
#endif
#ifdef	__float128
	t_f128			q;
#endif
}					u_varfloat;



/*! @} */
HEADER_END
#endif
