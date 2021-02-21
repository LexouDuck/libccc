/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/int.h                             |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_INT_H
#define __LIBCCC_INT_H
/*! @file libccc/int.h
**	@addtogroup libccc_int
**	@{
**	This header defines the integer number primitive types and functions.
**
**	@isostd{https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**	@isostd{https://en.cppreference.com/w/c/types/limits}
**
**	These are wrapper types for all the primitive integer types in a more concise
**	naming convention, to better reflect the amount of bits used by each type.
**	It is recommended to always use these types rather than the machine-specific
**	default C types (`char`, `short`, `int`, `long`, etc) - the following
**	`typedefs` are aliases over the more reliable integer types from `stdint.h`
**	They have the size that one would expect, no matter the platform/machine.
**
**	You can learn more about how the ISO standard defines integer types here:
**	https://en.wikipedia.org/wiki/C_data_types
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

/*
**	Included to use the following std types:
**	- uint8_t
**	- uint16_t
**	- uint32_t
**	- uint64_t
**	- int8_t
**	- int16_t
**	- int32_t
**	- int64_t
*/
#include <stdint.h>

#include "libccc_config.h"
#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#if LIBCONFIG_BITS_UINT != 8 && \
	LIBCONFIG_BITS_UINT != 16 && \
	LIBCONFIG_BITS_UINT != 32 && \
	LIBCONFIG_BITS_UINT != 64 && \
	LIBCONFIG_BITS_UINT != 128
	#error "LIBCONFIG_BITS_UINT must be equal to one of: 8, 16, 32, 64, 128"
#endif

#if LIBCONFIG_BITS_SINT != 8 && \
	LIBCONFIG_BITS_SINT != 16 && \
	LIBCONFIG_BITS_SINT != 32 && \
	LIBCONFIG_BITS_SINT != 64 && \
	LIBCONFIG_BITS_SINT != 128
	#error "LIBCONFIG_BITS_SINT must be equal to one of: 8, 16, 32, 64, 128"
#endif



#ifndef LIBCONFIG_INTEGER_TYPES
	#define STDINT(TYPE, BITS)	TYPE##BITS##_t
#else
	#define STDINT(TYPE, BITS)	TYPE##LIBCONFIG_INTEGER_TYPES##BITS##_t
#endif

typedef STDINT(uint, 8)	u8;
typedef u8		t_u8;	//!< Primitive type: 8-bit unsigned integer
TYPEDEF_ALIAS(	t_u8,	UINT_8,  PRIMITIVE)

typedef STDINT(uint,16)	u16;
typedef u16		t_u16;	//!< Primitive type: 16-bit unsigned integer
TYPEDEF_ALIAS(	t_u16,	UINT_16, PRIMITIVE)

typedef STDINT(uint,32)	u32;
typedef u32		t_u32;	//!< Primitive type: 32-bit unsigned integer
TYPEDEF_ALIAS(	t_u32,	UINT_32, PRIMITIVE)

typedef	STDINT(uint,64)	u64;
typedef	u64		t_u64;	//!< Primitive type: 64-bit unsigned integer
TYPEDEF_ALIAS(	t_u64,	UINT_64, PRIMITIVE)

#ifdef	__int128
typedef unsigned __int128	u128;
typedef u128	t_u128;	//!< Primitive type: 128-bit unsigned integer (only available on certain platforms)
TYPEDEF_ALIAS(	t_u128,	UINT_128,PRIMITIVE)
#elif (LIBCONFIG_BITS_UINT == 128)
	#error "Cannot set default unsigned int type to 128-bit, unavailable on this platform"
#endif

typedef STDINT(int,  8)	s8;
typedef s8		t_s8;	//!< Primitive type: 8-bit signed integer
TYPEDEF_ALIAS(	t_s8,	SINT_8,  PRIMITIVE)

typedef STDINT(int, 16)	s16;
typedef s16		t_s16;	//!< Primitive type: 16-bit signed integer
TYPEDEF_ALIAS(	t_s16,	SINT_16, PRIMITIVE)

typedef STDINT(int, 32)	s32;
typedef s32		t_s32;	//!< Primitive type: 32-bit signed integer
TYPEDEF_ALIAS(	t_s32,	SINT_32, PRIMITIVE)

typedef	STDINT(int, 64)	s64;
typedef	s64		t_s64;	//!< Primitive type: 64-bit signed integer
TYPEDEF_ALIAS(	t_s64,	SINT_64, PRIMITIVE)

#ifdef	__int128
typedef __int128		s128;
typedef s128	t_s128;	//!< Primitive type: 128-bit signed integer (only available on certain platforms)
TYPEDEF_ALIAS(	t_s128,	SINT_128,PRIMITIVE)
#elif (LIBCONFIG_BITS_SINT == 128)
	#error "Cannot set default signed int type to 128-bit, unavailable on this platform"
#endif



//! The configurable-size unsigned integer primitive type.
typedef LIBCONFIG_TYPE_UINT	t_uint;
TYPEDEF_ALIAS(				t_uint, UINT, PRIMITIVE)

//! The configurable-size signed integer primitive type.
typedef LIBCONFIG_TYPE_SINT	t_sint;
TYPEDEF_ALIAS(				t_sint, SINT, PRIMITIVE)

//! @}



#ifndef LIBCONFIG_INTEGER_TYPES

	#define U8_MAX	(255)						//!< The maximum value for  8-bit unsigned integers (0xFF)
	#define S8_MAX	(+127)						//!< The maximum value for  8-bit signed integers (0x7F)
	#define S8_MIN	(-128)						//!< The minimum value for  8-bit signed integers (0x80)

	#define U16_MAX	(65535)						//!< The maximum value for 16-bit unsigned integers (0xFFFF)
	#define S16_MAX	(+32767)					//!< The maximum value for 16-bit signed integers (0x7FFF)
	#define S16_MIN	(-32768)					//!< The minimum value for 16-bit signed integers (0x8000)

	#define U32_MAX	(4294967295)				//!< The maximum value for 32-bit unsigned integers (0xFFFFFFFF)
	#define S32_MAX	(+2147483647)				//!< The maximum value for 32-bit signed integers (0x7FFFFFFF)
	#define S32_MIN	(-2147483648)				//!< The minimum value for 32-bit signed integers (0x80000000)

	#define U64_MAX	(18446744073709551615llu)	//!< The maximum value for 64-bit unsigned integers (0xFFFFFFFFFFFFFFFF)
	#define S64_MAX	(+9223372036854775807ll)	//!< The maximum value for 64-bit signed integers (0x7FFFFFFFFFFFFFFF)
	#define S64_MIN	(-9223372036854775807ll)	//!< The minimum value for 64-bit signed integers (0x8000000000000000)

#else

	#define U8_MAX	((t_u8 )-1)						//!< The maximum value for at least size  8-bit, unsigned integer type
	#define S8_MAX	((t_s8)(U8_MAX  >> 1))			//!< The maximum value for at least size  8-bit, signed integer type
	#define S8_MIN	((t_s8)((U8_MAX  >> 1) + 1))	//!< The minimum value for at least size  8-bit, signed integer type

	#define U16_MAX	((t_u16)-1)						//!< The maximum value for at least size 16-bit, unsigned integer type
	#define S16_MAX	((t_s16)(U16_MAX >> 1))			//!< The maximum value for at least size 16-bit, signed integer type
	#define S16_MIN	((t_s16)((U16_MAX >> 1) + 1))	//!< The minimum value for at least size 16-bit, signed integer type

	#define U32_MAX	((t_u32)-1)						//!< The maximum value for at least size 32-bit, unsigned integer type
	#define S32_MAX	((t_s32)(U32_MAX >> 1))			//!< The maximum value for at least size 32-bit, signed integer type
	#define S32_MIN	((t_s32)((U32_MAX >> 1) + 1))	//!< The minimum value for at least size 32-bit, signed integer type

	#define U64_MAX	((t_u64)-1)						//!< The maximum value for at least size 64-bit, unsigned integer type
	#define S64_MAX	((t_s64)(U64_MAX >> 1))			//!< The maximum value for at least size 64-bit, signed integer type
	#define S64_MIN	((t_s64)((U64_MAX >> 1) + 1))	//!< The minimum value for at least size 64-bit, signed integer type

#endif

#ifdef __int128

	#define U128_MAX	(340282366920938463463374607431768211455llu) //!< The maximum value for 128-bit unsigned integers (0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)
	#define S128_MAX	(+170141183460469231731687303715884105727ll) //!< The maximum value for 128-bit signed integers (0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)
	#define S128_MIN	(−170141183460469231731687303715884105728ll) //!< The minimum value for 128-bit signed integers (0x80000000000000000000000000000000)

#endif

//#define UINT_MAX	(t_uint)CONCAT(CONCAT(U,LIBCONFIG_BITS_UINT),_MAX)
//#define SINT_MAX	(t_sint)CONCAT(CONCAT(S,LIBCONFIG_BITS_SINT),_MAX)
//#define SINT_MIN	(t_sint)CONCAT(CONCAT(S,LIBCONFIG_BITS_SINT),_MIN)



#define MAXDIGITS_8BIT	 ( 3)	//!< The amount of digits needed to represent an 8-bit integer in decimal (max: 255)
#define MAXDIGITS_16BIT	 ( 5)	//!< The amount of digits needed to represent a 16-bit integer in decimal (max: 65535)
#define MAXDIGITS_32BIT	 (10)	//!< The amount of digits needed to represent a 32-bit integer in decimal (max: 4294967295)
#define MAXDIGITS_64BIT	 (20)	//!< The amount of digits needed to represent a 64-bit integer in decimal (max: 18446744073709551615)
#define MAXDIGITS_128BIT (41)	//!< The amount of digits needed to represent a 128-bit integer in decimal (max: 340282366920938463463374607431768211455)



/*
** ************************************************************************** *|
**                             String Conversions                             *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of an 8-bit signed integer
_MALLOC()
char*					S8_ToString(t_s8 n);
#define c_s8_to_str		S8_ToString
//! Get the string decimal representation of a 16-bit signed integer
_MALLOC()
char*					S16_ToString(t_s16 n);
#define c_s16_to_str	S16_ToString
//! Get the string decimal representation of a 32-bit signed integer
_MALLOC()
char*					S32_ToString(t_s32 n);
#define c_s32_to_str	S32_ToString
//! Get the string decimal representation of a 64-bit signed integer
_MALLOC()
char*					S64_ToString(t_s64 n);
#define c_s64_to_str	S64_ToString

//! Get the string decimal representation of an 8-bit unsigned integer
_MALLOC()
char*					U8_ToString(t_u8 n);
#define c_u8_to_str		U8_ToString
//! Get the string decimal representation of a 16-bit unsigned integer
_MALLOC()
char*					U16_ToString(t_u16 n);
#define c_u16_to_str	U16_ToString
//! Get the string decimal representation of a 32-bit unsigned integer
_MALLOC()
char*					U32_ToString(t_u32 n);
#define c_u32_to_str	U32_ToString
//! Get the string decimal representation of a 64-bit unsigned integer
_MALLOC()
char*					U64_ToString(t_u64 n);
#define c_u64_to_str	U64_ToString



//! Parse an 8-bit signed integer from the given decimal number string
t_s8					S8_FromString(char const* str);
#define c_str_to_s8		S8_FromString
//! Parse a 16-bit signed integer from the given decimal number string
t_s16					S16_FromString(char const* str);
#define c_str_to_s16	S16_FromString
//! Parse a 32-bit signed integer from the given decimal number string
t_s32					S32_FromString(char const* str);
#define c_str_to_s32	S32_FromString
//! Parse a 64-bit signed integer from the given decimal number string
t_s64					S64_FromString(char const* str);
#define c_str_to_s64	S64_FromString

//! Parse an 8-bit unsigned integer from the given decimal number string
t_u8					U8_FromString(char const* str);
#define c_str_to_u8		U8_FromString
//! Parse a 16-bit unsigned integer from the given decimal number string
t_u16					U16_FromString(char const* str);
#define c_str_to_u16	U16_FromString
//! Parse a 32-bit unsigned integer from the given decimal number string
t_u32					U32_FromString(char const* str);
#define c_str_to_u32	U32_FromString
//! Parse a 64-bit unsigned integer from the given decimal number string
t_u64					U64_FromString(char const* str);
#define c_str_to_u64	U64_FromString



/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of an 8-bit unsigned integer
_MALLOC()
char*						U8_ToString_Hex(t_u8 n);
#define c_u8_to_strhex		U8_ToString_Hex
//! Get the string decimal representation of a 16-bit unsigned integer
_MALLOC()
char*						U16_ToString_Hex(t_u16 n);
#define c_u16_to_strhex		U16_ToString_Hex
//! Get the string decimal representation of a 32-bit unsigned integer
_MALLOC()
char*						U32_ToString_Hex(t_u32 n);
#define c_u32_to_strhex		U32_ToString_Hex
//! Get the string decimal representation of a 64-bit unsigned integer
_MALLOC()
char*						U64_ToString_Hex(t_u64 n);
#define c_u64_to_strhex		U64_ToString_Hex



//! Parse an 8-bit unsigned integer from the given haxedecimal number string
t_u8						U8_FromString_Hex(char const* str);
#define c_strhex_to_u8		U8_FromString_Hex
//! Parse a 16-bit unsigned integer from the given haxedecimal number string
t_u16						U16_FromString_Hex(char const* str);
#define c_strhex_to_u16		U16_FromString_Hex
//! Parse a 32-bit unsigned integer from the given haxedecimal number string
t_u32						U32_FromString_Hex(char const* str);
#define c_strhex_to_u32		U32_FromString_Hex
//! Parse a 64-bit unsigned integer from the given haxedecimal number string
t_u64						U64_FromString_Hex(char const* str);
#define c_strhex_to_u64		U64_FromString_Hex



/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

//! Get a string custom-base representation of an 8-bit signed integer
_MALLOC()
char*						S8_ToString_Base(t_s8 n, char const* base);
#define c_s8_to_strbase		S8_ToString_Base
//! Get a string custom-base representation of a 16-bit signed integer
_MALLOC()
char*						S16_ToString_Base(t_s16 n, char const* base);
#define c_s16_to_strbase	S16_ToString_Base
//! Get a string custom-base representation of a 32-bit signed integer
_MALLOC()
char*						S32_ToString_Base(t_s32 n, char const* base);
#define c_s32_to_strbase	S32_ToString_Base
//! Get a string custom-base representation of a 64-bit signed integer
_MALLOC()
char*						S64_ToString_Base(t_s64 n, char const* base);
#define c_s64_to_strbase	S64_ToString_Base

//! Get a string custom-base representation of an 8-bit unsigned integer
_MALLOC()
char*						U8_ToString_Base(t_u8 n, char const* base);
#define c_u8_to_strbase		U8_ToString_Base
//! Get a string custom-base representation of a 16-bit unsigned integer
_MALLOC()
char*						U16_ToString_Base(t_u16 n, char const* base);
#define c_u16_to_strbase	U16_ToString_Base
//! Get a string custom-base representation of a 32-bit unsigned integer
_MALLOC()
char*						U32_ToString_Base(t_u32 n, char const* base);
#define c_u32_to_strbase	U32_ToString_Base
//! Get a string custom-base representation of a 64-bit unsigned integer
_MALLOC()
char*						U64_ToString_Base(t_u64 n, char const* base);
#define c_u64_to_strbase	U64_ToString_Base



//! Parse an 8-bit signed integer from a custom-base number string
t_s8						S8_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s8		S8_FromString_Base
//! Parse a 16-bit signed integer from a custom-base number string
t_s16						S16_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s16	S16_FromString_Base
//! Parse a 32-bit signed integer from a custom-base number string
t_s32						S32_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s32	S32_FromString_Base
//! Parse a 64-bit signed integer from a custom-base number string
t_s64						S64_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s64	S64_FromString_Base

//! Parse an 8-bit unsigned integer from a custom-base number string
t_u8						U8_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u8		U8_FromString_Base
//! Parse a 16-bit unsigned integer from a custom-base number string
t_u16						U16_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u16	U16_FromString_Base
//! Parse a 32-bit unsigned integer from a custom-base number string
t_u32						U32_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u32	U32_FromString_Base
//! Parse a 64-bit unsigned integer from a custom-base number string
t_u64						U64_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u64	U64_FromString_Base



/*
** ************************************************************************** *|
**                       Variable-size primitive types                        *|
** ************************************************************************** *|
*/

//! A union storing an integer (signed or unsigned) of any common storage size
/*!
** These unions are used for certain difficult casting conditions.
** They are used in particular when casting an <stdarg.h> var_arg to the
** appropriate type in c_printf.
*/
typedef union		u_varint_
{
	t_s8			sc;
	t_s16			ss;
	t_s32			si;
	t_s64			sl;
	t_u8			uc;
	t_u16			us;
	t_u32			ui;
	t_u64			ul;
}					u_varint;



/*! @} */
HEADER_END
#endif
