/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_convert.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define MAXDIGIT_8BIT	3	//!< The amount of digits needed to represent an 8-bit number in decimal (255)
#define MAXDIGIT_16BIT	5	//!< The amount of digits needed to represent a 16-bit number in decimal (65535)
#define MAXDIGIT_32BIT	10	//!< The amount of digits needed to represent a 32-bit number in decimal (4294967295)
#define MAXDIGIT_64BIT	20	//!< The amount of digits needed to represent a 64-bit number in decimal (18446744073709551615)

#define FLOAT_THRESHOLD_HUGE	1e+10
#define FLOAT_THRESHOLD_TINY	1e-10



/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Convert_S8_To_String			ft_s8_to_str
#define Convert_S16_To_String			ft_s16_to_str
#define Convert_S32_To_String			ft_s32_to_str
#define Convert_S64_To_String			ft_s64_to_str
#define Convert_U8_To_String			ft_u8_to_str
#define Convert_U16_To_String			ft_u16_to_str
#define Convert_U32_To_String			ft_u32_to_str
#define Convert_U64_To_String			ft_u64_to_str

#define Convert_F32_To_String			ft_f32_to_str
#define Convert_F64_To_String			ft_f64_to_str
#define Convert_F32_To_String_P			ft_f32_to_str_p
#define Convert_F64_To_String_P			ft_f64_to_str_p

#define Convert_Bool_To_String			ft_bool_to_str
#define Convert_Size_To_String			ft_size_to_str

#define Convert_U8_To_HexString			ft_u8_to_hex
#define Convert_U16_To_HexString		ft_u16_to_hex
#define Convert_U32_To_HexString		ft_u32_to_hex
#define Convert_U64_To_HexString		ft_u64_to_hex

#define Convert_S8_To_BaseString		ft_s8_to_strbase
#define Convert_S16_To_BaseString		ft_s16_to_strbase
#define Convert_S32_To_BaseString		ft_s32_to_strbase
#define Convert_S64_To_BaseString		ft_s64_to_strbase
#define Convert_U8_To_BaseString		ft_u8_to_strbase
#define Convert_U16_To_BaseString		ft_u16_to_strbase
#define Convert_U32_To_BaseString		ft_u32_to_strbase
#define Convert_U64_To_BaseString		ft_u64_to_strbase

#define Convert_String_To_S8			ft_str_to_s8
#define Convert_String_To_S16			ft_str_to_s16
#define Convert_String_To_S32			ft_str_to_s32
#define Convert_String_To_S64			ft_str_to_s64
#define Convert_String_To_U8			ft_str_to_u8
#define Convert_String_To_U16			ft_str_to_u16
#define Convert_String_To_U32			ft_str_to_u32
#define Convert_String_To_U64			ft_str_to_u64
#define Convert_String_To_F32			ft_str_to_f32
#define Convert_String_To_F64			ft_str_to_f64
#define Convert_String_To_Bool			ft_str_to_bool
#define Convert_String_To_Size			ft_str_to_size

#define Convert_HexString_To_U8			ft_hex_to_u8
#define Convert_HexString_To_U16		ft_hex_to_u16
#define Convert_HexString_To_U32		ft_hex_to_u32
#define Convert_HexString_To_U64		ft_hex_to_u64

#define Convert_BaseString_To_S8		ft_strbase_to_s8
#define Convert_BaseString_To_S16		ft_strbase_to_s16
#define Convert_BaseString_To_S32		ft_strbase_to_s32
#define Convert_BaseString_To_S64		ft_strbase_to_s64
#define Convert_BaseString_To_U8		ft_strbase_to_u8
#define Convert_BaseString_To_U16		ft_strbase_to_u16
#define Convert_BaseString_To_U32		ft_strbase_to_u32
#define Convert_BaseString_To_U64		ft_strbase_to_u64



/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

char	*ft_s8_to_str(t_s8 n);		//!< Get the string decimal representation of an 8-bit signed integer
char	*ft_s16_to_str(t_s16 n);	//!< Get the string decimal representation of a 16-bit signed integer
char	*ft_s32_to_str(t_s32 n);	//!< Get the string decimal representation of a 32-bit signed integer
char	*ft_s64_to_str(t_s64 n);	//!< Get the string decimal representation of a 64-bit signed integer

char	*ft_u8_to_str(t_u8 n);		//!< Get the string decimal representation of an 8-bit unsigned integer
char	*ft_u16_to_str(t_u16 n);	//!< Get the string decimal representation of a 16-bit unsigned integer
char	*ft_u32_to_str(t_u32 n);	//!< Get the string decimal representation of a 32-bit unsigned integer
char	*ft_u64_to_str(t_u64 n);	//!< Get the string decimal representation of a 64-bit unsigned integer

t_s8	ft_str_to_s8(char const *str);	//!< Parse an 8-bit signed integer from the given decimal number string
t_s16	ft_str_to_s16(char const *str);	//!< Parse a 16-bit signed integer from the given decimal number string
t_s32	ft_str_to_s32(char const *str);	//!< Parse a 32-bit signed integer from the given decimal number string
t_s64	ft_str_to_s64(char const *str);	//!< Parse a 64-bit signed integer from the given decimal number string

t_u8	ft_str_to_u8(char const *str);	//!< Parse an 8-bit unsigned integer from the given decimal number string
t_u16	ft_str_to_u16(char const *str);	//!< Parse a 16-bit unsigned integer from the given decimal number string
t_u32	ft_str_to_u32(char const *str);	//!< Parse a 32-bit unsigned integer from the given decimal number string
t_u64	ft_str_to_u64(char const *str);	//!< Parse a 64-bit unsigned integer from the given decimal number string



/*
** ************************************************************************** *|
**                         Floating Point Conversions                         *|
** ************************************************************************** *|
*/

//! Returns TRUE if the given 'number' is NaN or +/- infinity
t_bool	ft_float_to_str_checkspecial(t_f32 number, char **result);

char	*ft_f32_to_str(t_f32 n);	//!< Get the string decimal representation of a 32-bit floating-point number
char	*ft_f64_to_str(t_f64 n);	//!< Get the string decimal representation of a 64-bit floating-point number

char	*ft_f32_to_str_p(t_f32 n, t_u8 precision);	//!< Get the string decimal representation of a 32-bit floating-point number, with 'precision' fractional digits
char	*ft_f64_to_str_p(t_f64 n, t_u8 precision);	//!< Get the string decimal representation of a 64-bit floating-point number, with 'precision' fractional digits

//! Returns ERROR(1) if the given 'str' contains any invalid characters for float parsing
int		ft_str_to_float_checkinvalid(char const *str, char **result_tmp);

t_f32	ft_str_to_f32(char const *str);	//!< Parse a 32-bit float from the given string (can be decimal/exponential/hexdecimal)
t_f64	ft_str_to_f64(char const *str);	//!< Parse a 64-bit double from the given string (can be decimal/exponential/hexdecimal)



/*
** ************************************************************************** *|
**                         Other Conversion Functions                         *|
** ************************************************************************** *|
*/

//! Get the string representation of a boolean value (TRUE or FALSE)
char	*ft_bool_to_str(t_bool value, t_bool uppercase);
//! Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
t_bool	ft_str_to_bool(char const *str);

//! Get the string decimal representation of a 64-bit unsigned integer
char	*ft_size_to_str(t_size value);
//! Parse a memory-size uint from the given string
t_size	ft_str_to_size(char const *str);



/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

char	*ft_u8_to_hex(t_u8 n);		//!< Get the string decimal representation of an 8-bit unsigned integer
char	*ft_u16_to_hex(t_u16 n);	//!< Get the string decimal representation of a 16-bit unsigned integer
char	*ft_u32_to_hex(t_u32 n);	//!< Get the string decimal representation of a 32-bit unsigned integer
char	*ft_u64_to_hex(t_u64 n);	//!< Get the string decimal representation of a 64-bit unsigned integer

t_u8	ft_hex_to_u8(char const *str);	//!< Parse an 8-bit unsigned integer from the given haxedecimal number string
t_u16	ft_hex_to_u16(char const *str);	//!< Parse a 16-bit unsigned integer from the given haxedecimal number string
t_u32	ft_hex_to_u32(char const *str);	//!< Parse a 32-bit unsigned integer from the given haxedecimal number string
t_u64	ft_hex_to_u64(char const *str);	//!< Parse a 64-bit unsigned integer from the given haxedecimal number string



/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

char	*ft_s8_to_strbase(t_s8 n, char const *base);	//!< Get a string custom-base representation of an 8-bit signed integer
char	*ft_s16_to_strbase(t_s16 n, char const *base);	//!< Get a string custom-base representation of a 16-bit signed integer
char	*ft_s32_to_strbase(t_s32 n, char const *base);	//!< Get a string custom-base representation of a 32-bit signed integer
char	*ft_s64_to_strbase(t_s64 n, char const *base);	//!< Get a string custom-base representation of a 64-bit signed integer

char	*ft_u8_to_strbase(t_u8 n, char const *base);	//!< Get a string custom-base representation of an 8-bit unsigned integer
char	*ft_u16_to_strbase(t_u16 n, char const *base);	//!< Get a string custom-base representation of a 16-bit unsigned integer
char	*ft_u32_to_strbase(t_u32 n, char const *base);	//!< Get a string custom-base representation of a 32-bit unsigned integer
char	*ft_u64_to_strbase(t_u64 n, char const *base);	//!< Get a string custom-base representation of a 64-bit unsigned integer

t_s8	ft_strbase_to_s8(char const *str, char const *base);	//!< Parse an 8-bit signed integer from a custom-base number string
t_s16	ft_strbase_to_s16(char const *str, char const *base);	//!< Parse a 16-bit signed integer from a custom-base number string
t_s32	ft_strbase_to_s32(char const *str, char const *base);	//!< Parse a 32-bit signed integer from a custom-base number string
t_s64	ft_strbase_to_s64(char const *str, char const *base);	//!< Parse a 64-bit signed integer from a custom-base number string

t_u8	ft_strbase_to_u8(char const *str, char const *base);	//!< Parse an 8-bit unsigned integer from a custom-base number string
t_u16	ft_strbase_to_u16(char const *str, char const *base);	//!< Parse a 16-bit unsigned integer from a custom-base number string
t_u32	ft_strbase_to_u32(char const *str, char const *base);	//!< Parse a 32-bit unsigned integer from a custom-base number string
t_u64	ft_strbase_to_u64(char const *str, char const *base);	//!< Parse a 64-bit unsigned integer from a custom-base number string



/*! @} */
HEADER_END
#endif
