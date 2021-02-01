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
**	@addtogroup libccc/float
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



typedef float	t_f32;	//!< The type for 32-bit 'single precision' IEEE-754 floating-point numbers
typedef double	t_f64;	//!< The type for 64-bit 'double precision' IEEE-754 floating-point numbers

#ifdef	__float80
typedef __float80	t_f80;	//!< The type for 32-bit 'extended precision' IEEE-754 floating-point numbers (only certain platforms)
#elif LIBCONFIG_BITS_FLOAT == 80
	#error "Cannot set default float to 80-bit extended-precision, unavailable on this platform"
#endif

#ifdef	__float128
typedef __float128	t_f128;	//!< The type for 32-bit 'quadruple precision' IEEE-754 floating-point numbers (only certain platforms)
#elif LIBCONFIG_BITS_FLOAT == 128
	#error "Cannot set default float to 128-bit quadruple-precision, unavailable on this platform"
#endif



//! The configurable-size floating-point number primitive type.
typedef LIBCONFIG_TYPE_FLOAT	t_float;



/*!
**	This very small float is typically used to compare two float values.
**	Floating point equality checks aren't the most dependable kind of operation,
**	so it's often better to do (ABS(x - y) <= FLOAT_BIAS) to check for equality.
*/
#define FLOAT_BIAS		(1.0e-10)

//	TODO document this
#define SAMPLE_NB		(1024)



#define FLOAT_THRESHOLD_HUGE	(1e+10)	//!< TODO document this
#define FLOAT_THRESHOLD_TINY	(1e-10)	//!< TODO document this



#ifndef INFINITY		//! Define the floating-point infinity value: use -INFINITY for negative inf
#define INFINITY		(1. / 0.)
#endif
#ifndef IS_INFINITY		//! Checks if the given 'x' is either +INFINITY or -INFINITY
#define IS_INFINITY(x)	((x) == INFINITY || (x) == -INFINITY)
#endif

#ifndef NAN				//! Define the floating-point "not a number" value.
#define NAN				(0. / 0.)
#endif
#ifndef IS_NAN			//! Checks if the given 'x' has a "not a number" value.
#define IS_NAN(x)		((x) != (x))
#endif



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

#define FLOAT_SIGNED			F##LIBCONFIG_BITS_FLOAT##_SIGNED
#define FLOAT_EXPONENT_BIAS		F##LIBCONFIG_BITS_FLOAT##_EXPONENT_BIAS
#define FLOAT_EXPONENT			F##LIBCONFIG_BITS_FLOAT##_EXPONENT
#define FLOAT_EXPONENT_ZERO		F##LIBCONFIG_BITS_FLOAT##_EXPONENT_ZERO
#define FLOAT_EXPONENT_BITS		F##LIBCONFIG_BITS_FLOAT##_EXPONENT_BITS
#define FLOAT_MANTISSA			F##LIBCONFIG_BITS_FLOAT##_MANTISSA
#define FLOAT_MANTISSA_SIGNED	F##LIBCONFIG_BITS_FLOAT##_MANTISSA_SIGNED
#define FLOAT_MANTISSA_BITS		F##LIBCONFIG_BITS_FLOAT##_MANTISSA_BITS
#define FLOAT_INIT_VALUE		F##LIBCONFIG_BITS_FLOAT##_INIT_VALUE




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
**                         Floating Point Conversions                         *|
** ************************************************************************** *|
*/

//! Returns 1 if the given 'number' is either NaN, or +/- infinity
int									Convert_Float_To_String_CheckSpecial(t_f32 number, char* *a_result);
#define c_float_to_str_checkspecial	Convert_Float_To_String_CheckSpecial

//! Get the string decimal representation of a 32-bit floating-point number
/*
*/
_MALLOC
char*						Convert_F32_To_String(t_f32 n);
#define c_f32_to_str		Convert_F32_To_String
//! Get the string hexadecimal representation of a 32-bit floating-point number
/*
*/
_MALLOC
char*						Convert_F32_To_HexString(t_f32 n);
#define c_f32_to_strhex		Convert_F32_To_HexString
//! Get the string decimal representation of a 32-bit floating-point number, with 'precision' fractional digits
/*!
**	NB: This function has some approximation/error margin (beyond the
**	seventh decimal digit; the exact amount of imprecision depends on the input)
*/
_MALLOC
char*						Convert_F32_To_String_P(t_f32 n, t_u8 precision);
#define c_f32_to_str_p		Convert_F32_To_String_P

//! Get the string decimal representation of a 64-bit floating-point number
/*
*/
_MALLOC
char*						Convert_F64_To_String(t_f64 n);
#define c_f64_to_str		Convert_F64_To_String
//! Get the string hexadecimal representation of a 64-bit floating-point number
/*
*/
_MALLOC
char*						Convert_F64_To_HexString(t_f64 n);
#define c_f64_to_strhex		Convert_F64_To_HexString
//! Get the string decimal representation of a 64-bit floating-point number, with 'precision' fractional digits
/*!
**	Has some approximation/error margin (beyond the seventh decimal digit;
**	the exact amount of imprecision depends on the input)
*/
_MALLOC
char*						Convert_F64_To_String_P(t_f64 n, t_u8 precision);
#define c_f64_to_str_p		Convert_F64_To_String_P



//! Returns 1(ERROR) if the given 'str' contains any invalid characters for float parsing
int										Convert_String_To_Float_CheckInvalid(char const* str, char* *a_result);
#define c_str_to_float_checkinvalid		Convert_String_To_Float_CheckInvalid

//! Parse a 32-bit float from the given string (can be decimal/exponential/hexdecimal)
t_f32					Convert_String_To_F32(char const* str);
#define c_str_to_f32	Convert_String_To_F32
//! Parse a 64-bit double from the given string (can be decimal/exponential/hexdecimal)
t_f64					Convert_String_To_F64(char const* str);
#define c_str_to_f64	Convert_String_To_F64



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
	t_f64			lf;
}					u_varfloat;



/*! @} */
HEADER_END
#endif
