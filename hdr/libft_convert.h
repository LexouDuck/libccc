/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_convert.h                         |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBFT_CONVERT_H
#define __LIBFT_CONVERT_H
/*! @file libft_convert.h
**	This header defines all the functions for converting with primitive types.
**	@addtogroup libft_convert
**	@{
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define MAXDIGIT_8BIT	( 3)	//!< The amount of digits needed to represent an 8-bit number in decimal (255)
#define MAXDIGIT_16BIT	( 5)	//!< The amount of digits needed to represent a 16-bit number in decimal (65535)
#define MAXDIGIT_32BIT	(10)	//!< The amount of digits needed to represent a 32-bit number in decimal (4294967295)
#define MAXDIGIT_64BIT	(20)	//!< The amount of digits needed to represent a 64-bit number in decimal (18446744073709551615)

#define FLOAT_THRESHOLD_HUGE	(1e+10)
#define FLOAT_THRESHOLD_TINY	(1e-10)



/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of an 8-bit signed integer
char*					Convert_S8_To_String(t_s8 n);
#define ft_s8_to_str	Convert_S8_To_String
//! Get the string decimal representation of a 16-bit signed integer
char*					Convert_S16_To_String(t_s16 n);
#define ft_s16_to_str	Convert_S16_To_String
//! Get the string decimal representation of a 32-bit signed integer
char*					Convert_S32_To_String(t_s32 n);
#define ft_s32_to_str	Convert_S32_To_String
//! Get the string decimal representation of a 64-bit signed integer
char*					Convert_S64_To_String(t_s64 n);
#define ft_s64_to_str	Convert_S64_To_String

//! Get the string decimal representation of an 8-bit unsigned integer
char*					Convert_U8_To_String(t_u8 n);
#define ft_u8_to_str	Convert_U8_To_String
//! Get the string decimal representation of a 16-bit unsigned integer
char*					Convert_U16_To_String(t_u16 n);
#define ft_u16_to_str	Convert_U16_To_String
//! Get the string decimal representation of a 32-bit unsigned integer
char*					Convert_U32_To_String(t_u32 n);
#define ft_u32_to_str	Convert_U32_To_String
//! Get the string decimal representation of a 64-bit unsigned integer
char*					Convert_U64_To_String(t_u64 n);
#define ft_u64_to_str	Convert_U64_To_String



//! Parse an 8-bit signed integer from the given decimal number string
t_s8					Convert_String_To_S8(char const* str);
#define ft_str_to_s8	Convert_String_To_S8
//! Parse a 16-bit signed integer from the given decimal number string
t_s16					Convert_String_To_S16(char const* str);
#define ft_str_to_s16	Convert_String_To_S16
//! Parse a 32-bit signed integer from the given decimal number string
t_s32					Convert_String_To_S32(char const* str);
#define ft_str_to_s32	Convert_String_To_S32
//! Parse a 64-bit signed integer from the given decimal number string
t_s64					Convert_String_To_S64(char const* str);
#define ft_str_to_s64	Convert_String_To_S64

//! Parse an 8-bit unsigned integer from the given decimal number string
t_u8					Convert_String_To_U8(char const* str);
#define ft_str_to_u8	Convert_String_To_U8
//! Parse a 16-bit unsigned integer from the given decimal number string
t_u16					Convert_String_To_U16(char const* str);
#define ft_str_to_u16	Convert_String_To_U16
//! Parse a 32-bit unsigned integer from the given decimal number string
t_u32					Convert_String_To_U32(char const* str);
#define ft_str_to_u32	Convert_String_To_U32
//! Parse a 64-bit unsigned integer from the given decimal number string
t_u64					Convert_String_To_U64(char const* str);
#define ft_str_to_u64	Convert_String_To_U64



/*
** ************************************************************************** *|
**                         Floating Point Conversions                         *|
** ************************************************************************** *|
*/

//! Returns TRUE if the given 'number' is NaN or +/- infinity
t_bool									Convert_F_To_String_CheckSpecial(t_f32 number, char* *a_result);
#define ft_float_to_str_checkspecial	Convert_F_To_String_CheckSpecial

//! Get the string decimal representation of a 32-bit floating-point number
char*						Convert_F32_To_String(t_f32 n);
#define ft_f32_to_str		Convert_F32_To_String
//! Get the string hexadecimal representation of a 32-bit floating-point number
char*						Convert_F32_To_HexString(t_f32 n);
#define ft_f32_to_hexstr	Convert_F32_To_HexString
//! Get the string decimal representation of a 32-bit floating-point number, with 'precision' fractional digits
char*						Convert_F32_To_String_P(t_f32 n, t_u8 precision);
#define ft_f32_to_str_p		Convert_F32_To_String_P

//! Get the string decimal representation of a 64-bit floating-point number
char*						Convert_F64_To_String(t_f64 n);
#define ft_f64_to_str		Convert_F64_To_String
//! Get the string hexadecimal representation of a 64-bit floating-point number
char*						Convert_F64_To_HexString(t_f64 n);
#define ft_f64_to_hexstr	Convert_F64_To_HexString
//! Get the string decimal representation of a 64-bit floating-point number, with 'precision' fractional digits
char*						Convert_F64_To_String_P(t_f64 n, t_u8 precision);
#define ft_f64_to_str_p		Convert_F64_To_String_P



//! Returns ERROR(1) if the given 'str' contains any invalid characters for float parsing
int										Convert_String_To_F_CheckInvalid(char const* str, char* *a_result);
#define ft_str_to_float_checkinvalid	Convert_String_To_F_CheckInvalid

//! Parse a 32-bit float from the given string (can be decimal/exponential/hexdecimal)
t_f32					Convert_String_To_F32(char const* str);
#define ft_str_to_f32	Convert_String_To_F32
//! Parse a 64-bit double from the given string (can be decimal/exponential/hexdecimal)
t_f64					Convert_String_To_F64(char const* str);
#define ft_str_to_f64	Convert_String_To_F64



/*
** ************************************************************************** *|
**                         Other Conversion Functions                         *|
** ************************************************************************** *|
*/

//! Get the string representation of a boolean value (TRUE or FALSE)
char*					Convert_Bool_To_String(t_bool value, t_bool uppercase);
#define ft_bool_to_str	Convert_Bool_To_String
//! Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
t_bool					Convert_String_To_Bool(char const* str);
#define ft_str_to_bool	Convert_String_To_Bool



//! Get the string decimal representation of a 64-bit unsigned integer
char*					Convert_Size_To_String(t_size value);
#define ft_size_to_str	Convert_Size_To_String
//! Parse a memory-size uint from the given string
t_size					Convert_String_To_Size(char const* str);
#define ft_str_to_size	Convert_String_To_Size

//! Get the string decimal human-readable representation of a 64-bit unsigned integer, with bytes units (KB,MB,GB,etc)
char*							Convert_Size_To_String_Readable(t_size value);
#define ft_size_to_str_readable	Convert_Size_To_String_Readable



/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of an 8-bit unsigned integer
char*					Convert_U8_To_HexString(t_u8 n);
#define ft_u8_to_hex	Convert_U8_To_HexString
//! Get the string decimal representation of a 16-bit unsigned integer
char*					Convert_U16_To_HexString(t_u16 n);
#define ft_u16_to_hex	Convert_U16_To_HexString
//! Get the string decimal representation of a 32-bit unsigned integer
char*					Convert_U32_To_HexString(t_u32 n);
#define ft_u32_to_hex	Convert_U32_To_HexString
//! Get the string decimal representation of a 64-bit unsigned integer
char*					Convert_U64_To_HexString(t_u64 n);
#define ft_u64_to_hex	Convert_U64_To_HexString



//! Parse an 8-bit unsigned integer from the given haxedecimal number string
t_u8					Convert_HexString_To_U8(char const* str);
#define ft_hex_to_u8	Convert_HexString_To_U8
//! Parse a 16-bit unsigned integer from the given haxedecimal number string
t_u16					Convert_HexString_To_U16(char const* str);
#define ft_hex_to_u16	Convert_HexString_To_U16
//! Parse a 32-bit unsigned integer from the given haxedecimal number string
t_u32					Convert_HexString_To_U32(char const* str);
#define ft_hex_to_u32	Convert_HexString_To_U32
//! Parse a 64-bit unsigned integer from the given haxedecimal number string
t_u64					Convert_HexString_To_U64(char const* str);
#define ft_hex_to_u64	Convert_HexString_To_U64



/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

//! Get a string custom-base representation of an 8-bit signed integer
char*						Convert_S8_To_BaseString(t_s8 n, char const* base);
#define ft_s8_to_strbase	Convert_S8_To_BaseString
//! Get a string custom-base representation of a 16-bit signed integer
char*						Convert_S16_To_BaseString(t_s16 n, char const* base);
#define ft_s16_to_strbase	Convert_S16_To_BaseString
//! Get a string custom-base representation of a 32-bit signed integer
char*						Convert_S32_To_BaseString(t_s32 n, char const* base);
#define ft_s32_to_strbase	Convert_S32_To_BaseString
//! Get a string custom-base representation of a 64-bit signed integer
char*						Convert_S64_To_BaseString(t_s64 n, char const* base);
#define ft_s64_to_strbase	Convert_S64_To_BaseString

//! Get a string custom-base representation of an 8-bit unsigned integer
char*						Convert_U8_To_BaseString(t_u8 n, char const* base);
#define ft_u8_to_strbase	Convert_U8_To_BaseString
//! Get a string custom-base representation of a 16-bit unsigned integer
char*						Convert_U16_To_BaseString(t_u16 n, char const* base);
#define ft_u16_to_strbase	Convert_U16_To_BaseString
//! Get a string custom-base representation of a 32-bit unsigned integer
char*						Convert_U32_To_BaseString(t_u32 n, char const* base);
#define ft_u32_to_strbase	Convert_U32_To_BaseString
//! Get a string custom-base representation of a 64-bit unsigned integer
char*						Convert_U64_To_BaseString(t_u64 n, char const* base);
#define ft_u64_to_strbase	Convert_U64_To_BaseString



//! Parse an 8-bit signed integer from a custom-base number string
t_s8						Convert_BaseString_To_S8(char const* str, char const* base);
#define ft_strbase_to_s8	Convert_BaseString_To_S8
//! Parse a 16-bit signed integer from a custom-base number string
t_s16						Convert_BaseString_To_S16(char const* str, char const* base);
#define ft_strbase_to_s16	Convert_BaseString_To_S16
//! Parse a 32-bit signed integer from a custom-base number string
t_s32						Convert_BaseString_To_S32(char const* str, char const* base);
#define ft_strbase_to_s32	Convert_BaseString_To_S32
//! Parse a 64-bit signed integer from a custom-base number string
t_s64						Convert_BaseString_To_S64(char const* str, char const* base);
#define ft_strbase_to_s64	Convert_BaseString_To_S64

//! Parse an 8-bit unsigned integer from a custom-base number string
t_u8						Convert_BaseString_To_U8(char const* str, char const* base);
#define ft_strbase_to_u8	Convert_BaseString_To_U8
//! Parse a 16-bit unsigned integer from a custom-base number string
t_u16						Convert_BaseString_To_U16(char const* str, char const* base);
#define ft_strbase_to_u16	Convert_BaseString_To_U16
//! Parse a 32-bit unsigned integer from a custom-base number string
t_u32						Convert_BaseString_To_U32(char const* str, char const* base);
#define ft_strbase_to_u32	Convert_BaseString_To_U32
//! Parse a 64-bit unsigned integer from a custom-base number string
t_u64						Convert_BaseString_To_U64(char const* str, char const* base);
#define ft_strbase_to_u64	Convert_BaseString_To_U64



/*! @} */
HEADER_END
#endif
