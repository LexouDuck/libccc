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

#ifndef LIBFT_CONVERT_H
#define LIBFT_CONVERT_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Convert_S8_To_String(n)						ft_s8_to_str(n)
#define Convert_S16_To_String(n)					ft_s16_to_str(n)
#define Convert_S32_To_String(n)					ft_s32_to_str(n)
#define Convert_S64_To_String(n)					ft_s64_to_str(n)
#define Convert_U8_To_String(n)						ft_u8_to_str(n)
#define Convert_U16_To_String(n)					ft_u16_to_str(n)
#define Convert_U32_To_String(n)					ft_u32_to_str(n)
#define Convert_U64_To_String(n)					ft_u64_to_str(n)
#define Convert_F32_To_String(n, precision)			ft_f32_to_str(n, precision)
#define Convert_F64_To_String(n, precision)			ft_f64_to_str(n, precision)
#define Convert_Bool_To_String(value, uppercase)	ft_bool_to_str(value, uppercase)
#define Convert_Size_To_String(value)				ft_size_to_str(value)
#define Convert_U8_To_HexString(n)					ft_u8_to_hex(n)
#define Convert_U16_To_HexString(n)					ft_u16_to_hex(n)
#define Convert_U32_To_HexString(n)					ft_u32_to_hex(n)
#define Convert_U64_To_HexString(n)					ft_u64_to_hex(n)
#define Convert_S8_To_BaseString(n, base)			ft_s8_to_strbase(n, base)
#define Convert_S16_To_BaseString(n, base)			ft_s16_to_strbase(n, base)
#define Convert_S32_To_BaseString(n, base)			ft_s32_to_strbase(n, base)
#define Convert_S64_To_BaseString(n, base)			ft_s64_to_strbase(n, base)
#define Convert_U8_To_BaseString(n, base)			ft_u8_to_strbase(n, base)
#define Convert_U16_To_BaseString(n, base)			ft_u16_to_strbase(n, base)
#define Convert_U32_To_BaseString(n, base)			ft_u32_to_strbase(n, base)
#define Convert_U64_To_BaseString(n, base)			ft_u64_to_strbase(n, base)

#define Convert_String_To_S8(str)				ft_str_to_s8(str)
#define Convert_String_To_S16(str)				ft_str_to_s16(str)
#define Convert_String_To_S32(str)				ft_str_to_s32(str)
#define Convert_String_To_S64(str)				ft_str_to_s64(str)
#define Convert_String_To_U8(str)				ft_str_to_u8(str)
#define Convert_String_To_U16(str)				ft_str_to_u16(str)
#define Convert_String_To_U32(str)				ft_str_to_u32(str)
#define Convert_String_To_U64(str)				ft_str_to_u64(str)
#define Convert_String_To_F32(str)				ft_str_to_f32(str)
#define Convert_String_To_F64(str)				ft_str_to_f64(str)
#define Convert_String_To_Bool(str)				ft_str_to_bool(str)
#define Convert_String_To_Size(str)				ft_str_to_size(str)
#define Convert_HexString_To_U8(str)			ft_hex_to_u8(str)
#define Convert_HexString_To_U16(str)			ft_hex_to_u16(str)
#define Convert_HexString_To_U32(str)			ft_hex_to_u32(str)
#define Convert_HexString_To_U64(str)			ft_hex_to_u64(str)
#define Convert_BaseString_To_S8(str, base)		ft_strbase_to_s8(str, base)
#define Convert_BaseString_To_S16(str, base)	ft_strbase_to_s16(str, base)
#define Convert_BaseString_To_S32(str, base)	ft_strbase_to_s32(str, base)
#define Convert_BaseString_To_S64(str, base)	ft_strbase_to_s64(str, base)
#define Convert_BaseString_To_U8(str, base)		ft_strbase_to_u8(str, base)
#define Convert_BaseString_To_U16(str, base)	ft_strbase_to_u16(str, base)
#define Convert_BaseString_To_U32(str, base)	ft_strbase_to_u32(str, base)
#define Convert_BaseString_To_U64(str, base)	ft_strbase_to_u64(str, base)



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	Maximum amount of digits for decimal number respresentations
*/
#define MAXDIGIT_8BIT	3	// 255
#define MAXDIGIT_16BIT	5	// 65535
#define MAXDIGIT_32BIT	10	// 4294967295
#define MAXDIGIT_64BIT	20	// 18446744073709551615



/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

char	*ft_s8_to_str(t_s8 n);
char	*ft_s16_to_str(t_s16 n);
char	*ft_s32_to_str(t_s32 n);
char	*ft_s64_to_str(t_s64 n);

char	*ft_u8_to_str(t_u8 n);
char	*ft_u16_to_str(t_u16 n);
char	*ft_u32_to_str(t_u32 n);
char	*ft_u64_to_str(t_u64 n);

t_s8	ft_str_to_s8(char const *str);
t_s16	ft_str_to_s16(char const *str);
t_s32	ft_str_to_s32(char const *str);
t_s64	ft_str_to_s64(char const *str);

t_u8	ft_str_to_u8(char const *str);
t_u16	ft_str_to_u16(char const *str);
t_u32	ft_str_to_u32(char const *str);
t_u64	ft_str_to_u64(char const *str);



/*
** ************************************************************************** *|
**                         Floating Point Conversions                         *|
** ************************************************************************** *|
*/

# define FLOAT_THRESHOLD_HUGE	1e+10
# define FLOAT_THRESHOLD_TINY	1e-10



t_f32	ft_str_to_f32(char const *str);
t_f64	ft_str_to_f64(char const *str);

int		ft_str_to_float_checkinvalid(char const *str, char **result_tmp);

t_bool	ft_float_to_str_checkspecial(t_f32 number, char **result);

char	*ft_f32_to_str(t_f32 n, t_u8 precision);
char	*ft_f64_to_str(t_f64 n, t_u8 precision);



/*
** ************************************************************************** *|
**                         Other Conversion Functions                         *|
** ************************************************************************** *|
*/

char	*ft_bool_to_str(t_bool value, t_bool uppercase);
char	*ft_size_to_str(size_t value);

t_bool	ft_str_to_bool(char const *str);
size_t	ft_str_to_size(char const *str);



/*
** ************************************************************************** *|
**                      Hexadecimal Conversion Functions                      *|
** ************************************************************************** *|
*/

char	*ft_u8_to_hex(t_u8 n);
char	*ft_u16_to_hex(t_u16 n);
char	*ft_u32_to_hex(t_u32 n);
char	*ft_u64_to_hex(t_u64 n);

t_u8	ft_hex_to_u8(char const *str);
t_u16	ft_hex_to_u16(char const *str);
t_u32	ft_hex_to_u32(char const *str);
t_u64	ft_hex_to_u64(char const *str);



/*
** ************************************************************************** *|
**                          Base-Number Conversions                           *|
** ************************************************************************** *|
*/

char	*ft_s8_to_strbase(t_s8 n, char const *base);
char	*ft_s16_to_strbase(t_s16 n, char const *base);
char	*ft_s32_to_strbase(t_s32 n, char const *base);
char	*ft_s64_to_strbase(t_s64 n, char const *base);

char	*ft_u8_to_strbase(t_u8 n, char const *base);
char	*ft_u16_to_strbase(t_u16 n, char const *base);
char	*ft_u32_to_strbase(t_u32 n, char const *base);
char	*ft_u64_to_strbase(t_u64 n, char const *base);

t_s8	ft_strbase_to_s8(char const *str, char const *base);
t_s16	ft_strbase_to_s16(char const *str, char const *base);
t_s32	ft_strbase_to_s32(char const *str, char const *base);
t_s64	ft_strbase_to_s64(char const *str, char const *base);

t_u8	ft_strbase_to_u8(char const *str, char const *base);
t_u16	ft_strbase_to_u16(char const *str, char const *base);
t_u32	ft_strbase_to_u32(char const *str, char const *base);
t_u64	ft_strbase_to_u64(char const *str, char const *base);

#endif
