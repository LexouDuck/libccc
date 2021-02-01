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
**	This header defines the integer number primitive types and functions.
**	@addtogroup libccc/int
**	@{
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
	LIBCONFIG_BITS_UINT != 64
	#error "LIBCONFIG_BITS_UINT must be equal to one of: 8, 16, 32, 64"
#endif

#if LIBCONFIG_BITS_INT != 8 && \
	LIBCONFIG_BITS_INT != 16 && \
	LIBCONFIG_BITS_INT != 32 && \
	LIBCONFIG_BITS_INT != 64
	#error "LIBCONFIG_BITS_INT must be equal to one of: 8, 16, 32, 64"
#endif



#ifndef LIBCONFIG_INTEGER_TYPES

	#define STDINT(TYPE, BITS)	TYPE##BITS##_t

	#define U8_MAX	(255)                  //!< The maximum value for  8-bit unsigned integers (0xFF)
	#define U16_MAX	(65535)                //!< The maximum value for 16-bit unsigned integers (0xFFFF)
	#define U32_MAX	(4294967295)           //!< The maximum value for 32-bit unsigned integers (0xFFFFFFFF)
	#define U64_MAX	(18446744073709551615) //!< The maximum value for 64-bit unsigned integers (0xFFFFFFFFFFFFFFFF)

	#define S8_MAX	(127)                  //!< The maximum value for  8-bit signed integers (0x7F)
	#define S16_MAX	(32767)                //!< The maximum value for 16-bit signed integers (0x7FFF)
	#define S32_MAX	(2147483647)           //!< The maximum value for 32-bit signed integers (0x7FFFFFFF)
	#define S64_MAX	(9223372036854775807)  //!< The maximum value for 64-bit signed integers (0x7FFFFFFFFFFFFFFF)

	#define S8_MIN	(-128)                 //!< The minimum value for  8-bit signed integers (0x80)
	#define S16_MIN	(-32768)               //!< The minimum value for 16-bit signed integers (0x8000)
	#define S32_MIN	(-2147483648)          //!< The minimum value for 32-bit signed integers (0x80000000)
	#define S64_MIN	(-9223372036854775808) //!< The minimum value for 64-bit signed integers (0x8000000000000000)

#else

	#define STDINT(TYPE, BITS)	TYPE##LIBCONFIG_INTEGER_TYPES##BITS##_t

	#define U8_MAX	((t_u8 )-1) //!< The maximum value for at least size  8-bit, unsigned integer type
	#define U16_MAX	((t_u16)-1) //!< The maximum value for at least size 16-bit, unsigned integer type
	#define U32_MAX	((t_u32)-1) //!< The maximum value for at least size 32-bit, unsigned integer type
	#define U64_MAX	((t_u64)-1) //!< The maximum value for at least size 64-bit, unsigned integer type

	#define S8_MAX	((t_s8) (U8_MAX  >> 1)) ////!< The maximum value for at least size  8-bit, signed integer type
	#define S16_MAX	((t_s16)(U16_MAX >> 1)) ////!< The maximum value for at least size 16-bit, signed integer type
	#define S32_MAX	((t_s32)(U32_MAX >> 1)) ////!< The maximum value for at least size 32-bit, signed integer type
	#define S64_MAX	((t_s64)(U64_MAX >> 1)) ////!< The maximum value for at least size 64-bit, signed integer type

	#define S8_MIN	((t_s8) ((U8_MAX  >> 1) + 1)) //!< The minimum value for at least size  8-bit, signed integer type
	#define S16_MIN	((t_s16)((U16_MAX >> 1) + 1)) //!< The minimum value for at least size 16-bit, signed integer type
	#define S32_MIN	((t_s32)((U32_MAX >> 1) + 1)) //!< The minimum value for at least size 32-bit, signed integer type
	#define S64_MIN	((t_s64)((U64_MAX >> 1) + 1)) //!< The minimum value for at least size 64-bit, signed integer type

#endif

/*
**	Define wrapper types for all the primitive number types in a clear naming
**	convention, to better reflect the amount of bits used by each type.
**	It is recommended to always use these types rather than the machine-specific
**	default C types char,short,int,long - the following typedefs will always
**	have the size that one would expect, no matter the machine.
**	You can learn more about how the ISO standard defines integer types here:
**	https://en.wikipedia.org/wiki/C_data_types
*/

typedef STDINT(uint,  8)	t_u8;	//!< The type for 8-bit unsigned integers
typedef STDINT(uint, 16)	t_u16;	//!< The type for 16-bit unsigned integers
typedef STDINT(uint, 32)	t_u32;	//!< The type for 32-bit unsigned integers
typedef	STDINT(uint, 64)	t_u64;	//!< The type for 64-bit unsigned integers

typedef STDINT( int,  8)	t_s8;	//!< The type for 8-bit signed integers
typedef STDINT( int, 16)	t_s16;	//!< The type for 16-bit signed integers
typedef STDINT( int, 32)	t_s32;	//!< The type for 32-bit signed integers
typedef	STDINT( int, 64)	t_s64;	//!< The type for 64-bit signed integers

#ifdef	__int128
typedef unsigned __int128	t_u128;	//!< The type for 128-bit unsigned integers (only certain platforms)
typedef __int128			t_s128;	//!< The type for 128-bit signed integers (only certain platforms)
#endif



//! The configurable-size unsigned integer primitive type.
typedef LIBCONFIG_TYPE_UINT		t_uint;

//! The configurable-size signed integer primitive type.
typedef LIBCONFIG_TYPE_INT		t_int;



#define MAXDIGIT_8BIT	( 3)	//!< The amount of digits needed to represent an 8-bit integer in decimal (max: 255)
#define MAXDIGIT_16BIT	( 5)	//!< The amount of digits needed to represent a 16-bit integer in decimal (max: 65535)
#define MAXDIGIT_32BIT	(10)	//!< The amount of digits needed to represent a 32-bit integer in decimal (max: 4294967295)
#define MAXDIGIT_64BIT	(20)	//!< The amount of digits needed to represent a 64-bit integer in decimal (max: 18446744073709551615)



/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of an 8-bit signed integer
_MALLOC
char*					Convert_S8_To_String(t_s8 n);
#define c_s8_to_str		Convert_S8_To_String
//! Get the string decimal representation of a 16-bit signed integer
_MALLOC
char*					Convert_S16_To_String(t_s16 n);
#define c_s16_to_str	Convert_S16_To_String
//! Get the string decimal representation of a 32-bit signed integer
_MALLOC
char*					Convert_S32_To_String(t_s32 n);
#define c_s32_to_str	Convert_S32_To_String
//! Get the string decimal representation of a 64-bit signed integer
_MALLOC
char*					Convert_S64_To_String(t_s64 n);
#define c_s64_to_str	Convert_S64_To_String

//! Get the string decimal representation of an 8-bit unsigned integer
_MALLOC
char*					Convert_U8_To_String(t_u8 n);
#define c_u8_to_str		Convert_U8_To_String
//! Get the string decimal representation of a 16-bit unsigned integer
_MALLOC
char*					Convert_U16_To_String(t_u16 n);
#define c_u16_to_str	Convert_U16_To_String
//! Get the string decimal representation of a 32-bit unsigned integer
_MALLOC
char*					Convert_U32_To_String(t_u32 n);
#define c_u32_to_str	Convert_U32_To_String
//! Get the string decimal representation of a 64-bit unsigned integer
_MALLOC
char*					Convert_U64_To_String(t_u64 n);
#define c_u64_to_str	Convert_U64_To_String



//! Parse an 8-bit signed integer from the given decimal number string
t_s8					Convert_String_To_S8(char const* str);
#define c_str_to_s8		Convert_String_To_S8
//! Parse a 16-bit signed integer from the given decimal number string
t_s16					Convert_String_To_S16(char const* str);
#define c_str_to_s16	Convert_String_To_S16
//! Parse a 32-bit signed integer from the given decimal number string
t_s32					Convert_String_To_S32(char const* str);
#define c_str_to_s32	Convert_String_To_S32
//! Parse a 64-bit signed integer from the given decimal number string
t_s64					Convert_String_To_S64(char const* str);
#define c_str_to_s64	Convert_String_To_S64

//! Parse an 8-bit unsigned integer from the given decimal number string
t_u8					Convert_String_To_U8(char const* str);
#define c_str_to_u8		Convert_String_To_U8
//! Parse a 16-bit unsigned integer from the given decimal number string
t_u16					Convert_String_To_U16(char const* str);
#define c_str_to_u16	Convert_String_To_U16
//! Parse a 32-bit unsigned integer from the given decimal number string
t_u32					Convert_String_To_U32(char const* str);
#define c_str_to_u32	Convert_String_To_U32
//! Parse a 64-bit unsigned integer from the given decimal number string
t_u64					Convert_String_To_U64(char const* str);
#define c_str_to_u64	Convert_String_To_U64



/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of an 8-bit unsigned integer
_MALLOC
char*						Convert_U8_To_HexString(t_u8 n);
#define c_u8_to_strhex		Convert_U8_To_HexString
//! Get the string decimal representation of a 16-bit unsigned integer
_MALLOC
char*						Convert_U16_To_HexString(t_u16 n);
#define c_u16_to_strhex		Convert_U16_To_HexString
//! Get the string decimal representation of a 32-bit unsigned integer
_MALLOC
char*						Convert_U32_To_HexString(t_u32 n);
#define c_u32_to_strhex		Convert_U32_To_HexString
//! Get the string decimal representation of a 64-bit unsigned integer
_MALLOC
char*						Convert_U64_To_HexString(t_u64 n);
#define c_u64_to_strhex		Convert_U64_To_HexString



//! Parse an 8-bit unsigned integer from the given haxedecimal number string
t_u8						Convert_HexString_To_U8(char const* str);
#define c_strhex_to_u8		Convert_HexString_To_U8
//! Parse a 16-bit unsigned integer from the given haxedecimal number string
t_u16						Convert_HexString_To_U16(char const* str);
#define c_strhex_to_u16		Convert_HexString_To_U16
//! Parse a 32-bit unsigned integer from the given haxedecimal number string
t_u32						Convert_HexString_To_U32(char const* str);
#define c_strhex_to_u32		Convert_HexString_To_U32
//! Parse a 64-bit unsigned integer from the given haxedecimal number string
t_u64						Convert_HexString_To_U64(char const* str);
#define c_strhex_to_u64		Convert_HexString_To_U64



/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

//! Get a string custom-base representation of an 8-bit signed integer
_MALLOC
char*						Convert_S8_To_BaseString(t_s8 n, char const* base);
#define c_s8_to_strbase		Convert_S8_To_BaseString
//! Get a string custom-base representation of a 16-bit signed integer
_MALLOC
char*						Convert_S16_To_BaseString(t_s16 n, char const* base);
#define c_s16_to_strbase	Convert_S16_To_BaseString
//! Get a string custom-base representation of a 32-bit signed integer
_MALLOC
char*						Convert_S32_To_BaseString(t_s32 n, char const* base);
#define c_s32_to_strbase	Convert_S32_To_BaseString
//! Get a string custom-base representation of a 64-bit signed integer
_MALLOC
char*						Convert_S64_To_BaseString(t_s64 n, char const* base);
#define c_s64_to_strbase	Convert_S64_To_BaseString

//! Get a string custom-base representation of an 8-bit unsigned integer
_MALLOC
char*						Convert_U8_To_BaseString(t_u8 n, char const* base);
#define c_u8_to_strbase		Convert_U8_To_BaseString
//! Get a string custom-base representation of a 16-bit unsigned integer
_MALLOC
char*						Convert_U16_To_BaseString(t_u16 n, char const* base);
#define c_u16_to_strbase	Convert_U16_To_BaseString
//! Get a string custom-base representation of a 32-bit unsigned integer
_MALLOC
char*						Convert_U32_To_BaseString(t_u32 n, char const* base);
#define c_u32_to_strbase	Convert_U32_To_BaseString
//! Get a string custom-base representation of a 64-bit unsigned integer
_MALLOC
char*						Convert_U64_To_BaseString(t_u64 n, char const* base);
#define c_u64_to_strbase	Convert_U64_To_BaseString



//! Parse an 8-bit signed integer from a custom-base number string
t_s8						Convert_BaseString_To_S8(char const* str, char const* base);
#define c_strbase_to_s8		Convert_BaseString_To_S8
//! Parse a 16-bit signed integer from a custom-base number string
t_s16						Convert_BaseString_To_S16(char const* str, char const* base);
#define c_strbase_to_s16	Convert_BaseString_To_S16
//! Parse a 32-bit signed integer from a custom-base number string
t_s32						Convert_BaseString_To_S32(char const* str, char const* base);
#define c_strbase_to_s32	Convert_BaseString_To_S32
//! Parse a 64-bit signed integer from a custom-base number string
t_s64						Convert_BaseString_To_S64(char const* str, char const* base);
#define c_strbase_to_s64	Convert_BaseString_To_S64

//! Parse an 8-bit unsigned integer from a custom-base number string
t_u8						Convert_BaseString_To_U8(char const* str, char const* base);
#define c_strbase_to_u8		Convert_BaseString_To_U8
//! Parse a 16-bit unsigned integer from a custom-base number string
t_u16						Convert_BaseString_To_U16(char const* str, char const* base);
#define c_strbase_to_u16	Convert_BaseString_To_U16
//! Parse a 32-bit unsigned integer from a custom-base number string
t_u32						Convert_BaseString_To_U32(char const* str, char const* base);
#define c_strbase_to_u32	Convert_BaseString_To_U32
//! Parse a 64-bit unsigned integer from a custom-base number string
t_u64						Convert_BaseString_To_U64(char const* str, char const* base);
#define c_strbase_to_u64	Convert_BaseString_To_U64



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
