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
/*!@group{libccc_int}
** @{
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
**
**	@file
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
typedef STDINT(uint,16)	u16;
typedef STDINT(uint,32)	u32;
typedef	STDINT(uint,64)	u64;
#ifdef	__int128
typedef unsigned __int128	u128;
#endif
typedef STDINT(int,  8)	s8;
typedef STDINT(int, 16)	s16;
typedef STDINT(int, 32)	s32;
typedef	STDINT(int, 64)	s64;
#ifdef	__int128
typedef __int128		s128;
#endif



//! Primitive type: 8-bit unsigned integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width unsigned integer type which is 8 bits in size.
**	The possible range of values is between zero and #U8_MAX.
**
**	@see
**	- U8_ToString()
**	- U8_ToString_Bin()
**	- U8_ToString_Hex()
**	- U8_ToString_Base()
*/
typedef u8		t_u8;
TYPEDEF_ALIAS(	t_u8,	UINT_8,  PRIMITIVE)

//! Primitive type: 16-bit unsigned integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width unsigned integer type which is 16 bits in size.
**	The possible range of values is between zero and #U16_MAX.
**
**	@see
**	- U16_ToString()
**	- U16_ToString_Bin()
**	- U16_ToString_Hex()
**	- U16_ToString_Base()
*/
typedef u16		t_u16;
TYPEDEF_ALIAS(	t_u16,	UINT_16, PRIMITIVE)

//! Primitive type: 32-bit unsigned integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width unsigned integer type which is 32 bits in size.
**	The possible range of values is between zero and #U32_MAX.
**
**	@see
**	- U32_ToString()
**	- U32_ToString_Bin()
**	- U32_ToString_Hex()
**	- U32_ToString_Base()
*/
typedef u32		t_u32;
TYPEDEF_ALIAS(	t_u32,	UINT_32, PRIMITIVE)

//! Primitive type: 64-bit unsigned integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width unsigned integer type which is 64 bits in size.
**	The possible range of values is between zero and #U64_MAX.
**
**	@see
**	- U64_ToString()
**	- U64_ToString_Bin()
**	- U64_ToString_Hex()
**	- U64_ToString_Base()
*/
typedef	u64		t_u64;
TYPEDEF_ALIAS(	t_u64,	UINT_64, PRIMITIVE)

#ifdef	__int128
//! Primitive type: 128-bit unsigned integer (only available on certain platforms)
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width unsigned integer type which is 128 bits in size.
**	NB: This type does not exist on most common platforms/machines.
**	The possible range of values is between zero and #U128_MAX.
**
**	@see
**	- U128_ToString()
**	- U128_ToString_Bin()
**	- U128_ToString_Hex()
**	- U128_ToString_Base()
*/
typedef u128	t_u128;
TYPEDEF_ALIAS(	t_u128,	UINT_128,PRIMITIVE)
#elif (LIBCONFIG_BITS_UINT == 128)
	#error "Cannot set default unsigned int type to 128-bit, unavailable on this platform"
#endif



//! Primitive type: 8-bit signed integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width signed integer type which is 8 bits in size.
**	The possible range of values is between #S8_MIN and #S8_MAX.
**
**	@see
**	- S8_ToString()
**	- S8_ToString_Bin()
**	- S8_ToString_Hex()
**	- S8_ToString_Base()
*/
typedef s8		t_s8;
TYPEDEF_ALIAS(	t_s8,	SINT_8,  PRIMITIVE)

//! Primitive type: 16-bit signed integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width signed integer type which is 16 bits in size.
**	The possible range of values is between #S16_MIN and #S16_MAX.
**
**	@see
**	- S16_ToString()
**	- S16_ToString_Bin()
**	- S16_ToString_Hex()
**	- S16_ToString_Base()
*/
typedef s16		t_s16;
TYPEDEF_ALIAS(	t_s16,	SINT_16, PRIMITIVE)

//! Primitive type: 32-bit signed integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width signed integer type which is 32 bits in size.
**	The possible range of values is between #S32_MIN and #S32_MAX.
**
**	@see
**	- S32_ToString()
**	- S32_ToString_Bin()
**	- S32_ToString_Hex()
**	- S32_ToString_Base()
*/
typedef s32		t_s32;
TYPEDEF_ALIAS(	t_s32,	SINT_32, PRIMITIVE)

//! Primitive type: 64-bit signed integer
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width signed integer type which is 64 bits in size.
**	The possible range of values is between #S64_MIN and #S64_MAX.
**
**	@see
**	- S64_ToString()
**	- S64_ToString_Bin()
**	- S64_ToString_Hex()
**	- S64_ToString_Base()
*/
typedef	s64		t_s64;
TYPEDEF_ALIAS(	t_s64,	SINT_64, PRIMITIVE)

#ifdef	__int128
//! Primitive type: 128-bit signed integer (only available on certain platforms)
/*!
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**
**	Fixed-width signed integer type which is 128 bits in size.
**	NB: This type does not exist on most common platforms/machines.
**	The possible range of values is between #S128_MIN and #S128_MAX.
**
**	@see
**	- S128_ToString()
**	- S128_ToString_Bin()
**	- S128_ToString_Hex()
**	- S128_ToString_Base()
*/
typedef s128	t_s128;
TYPEDEF_ALIAS(	t_s128,	SINT_128,PRIMITIVE)
#elif (LIBCONFIG_BITS_SINT == 128)
	#error "Cannot set default signed int type to 128-bit, unavailable on this platform"
#endif



//! The configurable-size unsigned integer primitive type.
/*!
**	@isostd{https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**
**	The size of this integer type depends on the value of #LIBCONFIG_TYPE_UINT.
**	This is meant to be used as a "default integer type", a type where the
**	programmer doesn't need to worry about integer overflow behaviors being
**	platform-dependent (like they would if they used the C native `int` type).
*/
typedef LIBCONFIG_TYPE_UINT	t_uint;
TYPEDEF_ALIAS(				t_uint, UINT, PRIMITIVE)

//! The configurable-size signed integer primitive type.
/*!
**	@isostd{https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**
**	The size of this integer type depends on the value of #LIBCONFIG_TYPE_SINT.
**	This is meant to be used as a "default integer type", a type where the
**	programmer doesn't need to worry about integer overflow behaviors being
**	platform-dependent (like they would if they used the C native `int` type).
*/
typedef LIBCONFIG_TYPE_SINT	t_sint;
TYPEDEF_ALIAS(				t_sint, SINT, PRIMITIVE)



#ifndef LIBCONFIG_INTEGER_TYPES

	#define U8_MAX (0xFF)					//!< The largest possible value for any 8-bit unsigned integer	(255)
	#define S8_MAX (0x7F)					//!< The largest possible value for any 8-bit signed integer	(+127)
	#define S8_MIN (0x80)					//!< The minimum possible value for any 8-bit signed integer	(-128)

	#define U16_MAX (0xFFFF)				//!< The largest possible value for any 16-bit unsigned integer	(65535)
	#define S16_MAX (0x7FFF)				//!< The largest possible value for any 16-bit signed integer	(+32767)
	#define S16_MIN (0x8000)				//!< The minimum possible value for any 16-bit signed integer	(-32768)

	#define U32_MAX (0xFFFFFFFF)			//!< The largest possible value for any 32-bit unsigned integer	(4294967295)
	#define S32_MAX (0x7FFFFFFF)			//!< The largest possible value for any 32-bit signed integer	(+2147483647)
	#define S32_MIN (0x80000000)			//!< The minimum possible value for any 32-bit signed integer	(-2147483648)

	#define U64_MAX (0xFFFFFFFFFFFFFFFFllu)	//!< The largest possible value for any 64-bit unsigned integer	(18446744073709551615)
	#define S64_MAX (0x7FFFFFFFFFFFFFFFll)	//!< The largest possible value for any 64-bit signed integer	(+9223372036854775807)
	#define S64_MIN (0x8000000000000000ll)	//!< The minimum possible value for any 64-bit signed integer	(-9223372036854775807)

#else

	#define U8_MAX	((t_u8 )-1)						//!< The largest possible value for at least size  8-bit, unsigned integer type
	#define S8_MAX	((t_s8)(U8_MAX  >> 1))			//!< The largest possible value for at least size  8-bit, signed integer type
	#define S8_MIN	((t_s8)((U8_MAX  >> 1) + 1))	//!< The minimum possible value for at least size  8-bit, signed integer type

	#define U16_MAX	((t_u16)-1)						//!< The largest possible value for at least size 16-bit, unsigned integer type
	#define S16_MAX	((t_s16)(U16_MAX >> 1))			//!< The largest possible value for at least size 16-bit, signed integer type
	#define S16_MIN	((t_s16)((U16_MAX >> 1) + 1))	//!< The minimum possible value for at least size 16-bit, signed integer type

	#define U32_MAX	((t_u32)-1)						//!< The largest possible value for at least size 32-bit, unsigned integer type
	#define S32_MAX	((t_s32)(U32_MAX >> 1))			//!< The largest possible value for at least size 32-bit, signed integer type
	#define S32_MIN	((t_s32)((U32_MAX >> 1) + 1))	//!< The minimum possible value for at least size 32-bit, signed integer type

	#define U64_MAX	((t_u64)-1)						//!< The largest possible value for at least size 64-bit, unsigned integer type
	#define S64_MAX	((t_s64)(U64_MAX >> 1))			//!< The largest possible value for at least size 64-bit, signed integer type
	#define S64_MIN	((t_s64)((U64_MAX >> 1) + 1))	//!< The minimum possible value for at least size 64-bit, signed integer type

#endif

#ifdef __int128

	#define U128_MAX (0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFllu) //!< The largest possible value for a 128-bit unsigned integer	(340282366920938463463374607431768211455llu)
	#define S128_MAX (0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFll)  //!< The largest possible value for a 128-bit signed integer	(+170141183460469231731687303715884105727ll)
	#define S128_MIN (0x80000000000000000000000000000000ll)  //!< The minimum possible value for a 128-bit signed integer	(−170141183460469231731687303715884105728ll)

#endif

//#define UINT_MAX	(t_uint)CONCAT(CONCAT(U,LIBCONFIG_BITS_UINT),_MAX)
//#define SINT_MAX	(t_sint)CONCAT(CONCAT(S,LIBCONFIG_BITS_SINT),_MAX)
//#define SINT_MIN	(t_sint)CONCAT(CONCAT(S,LIBCONFIG_BITS_SINT),_MIN)



/*
** ************************************************************************** *|
**                        Integer-to-String Conversions                       *|
** ************************************************************************** *|
*/

//! Returns newly allocated string decimal representation of an 8-bit signed integer
_MALLOC()
char*					S8_ToString(t_s8 n);
#define c_s8_to_str		S8_ToString //!< @alias{S8_ToString}

//! Returns newly allocated string decimal representation of a 16-bit signed integer
_MALLOC()
char*					S16_ToString(t_s16 n);
#define c_s16_to_str	S16_ToString //!< @alias{S16_ToString}

//! Returns newly allocated string decimal representation of a 32-bit signed integer
_MALLOC()
char*					S32_ToString(t_s32 n);
#define c_s32_to_str	S32_ToString //!< @alias{S32_ToString}

//! Returns newly allocated string decimal representation of a 64-bit signed integer
_MALLOC()
char*					S64_ToString(t_s64 n);
#define c_s64_to_str	S64_ToString //!< @alias{S64_ToString}

//! Returns newly allocated string decimal representation of an 8-bit unsigned integer
_MALLOC()
char*					U8_ToString(t_u8 n);
#define c_u8_to_str		U8_ToString //!< @alias{U8_ToString}

//! Returns newly allocated string decimal representation of a 16-bit unsigned integer
_MALLOC()
char*					U16_ToString(t_u16 n);
#define c_u16_to_str	U16_ToString //!< @alias{U16_ToString}

//! Returns newly allocated string decimal representation of a 32-bit unsigned integer
_MALLOC()
char*					U32_ToString(t_u32 n);
#define c_u32_to_str	U32_ToString //!< @alias{U32_ToString}

//! Returns newly allocated string decimal representation of a 64-bit unsigned integer
_MALLOC()
char*					U64_ToString(t_u64 n);
#define c_u64_to_str	U64_ToString //!< @alias{U64_ToString}



//! Returns newly allocated string decimal representation of an 8-bit unsigned integer
_MALLOC()
char*						U8_ToString_Hex(t_u8 n);
#define c_u8_to_strhex		U8_ToString_Hex //!< @alias{U8_ToString_Hex}

//! Returns newly allocated string decimal representation of a 16-bit unsigned integer
_MALLOC()
char*						U16_ToString_Hex(t_u16 n);
#define c_u16_to_strhex		U16_ToString_Hex //!< @alias{U16_ToString_Hex}

//! Returns newly allocated string decimal representation of a 32-bit unsigned integer
_MALLOC()
char*						U32_ToString_Hex(t_u32 n);
#define c_u32_to_strhex		U32_ToString_Hex //!< @alias{U32_ToString_Hex}

//! Returns newly allocated string decimal representation of a 64-bit unsigned integer
_MALLOC()
char*						U64_ToString_Hex(t_u64 n);
#define c_u64_to_strhex		U64_ToString_Hex //!< @alias{U64_ToString_Hex}



//! Returns newly allocated string custom-base representation of an 8-bit signed integer
_MALLOC()
char*						S8_ToString_Base(t_s8 n, char const* base);
#define c_s8_to_strbase		S8_ToString_Base //!< @alias{S8_ToString_Base}

//! Returns newly allocated string custom-base representation of a 16-bit signed integer
_MALLOC()
char*						S16_ToString_Base(t_s16 n, char const* base);
#define c_s16_to_strbase	S16_ToString_Base //!< @alias{S16_ToString_Base}

//! Returns newly allocated string custom-base representation of a 32-bit signed integer
_MALLOC()
char*						S32_ToString_Base(t_s32 n, char const* base);
#define c_s32_to_strbase	S32_ToString_Base //!< @alias{S32_ToString_Base}

//! Returns newly allocated string custom-base representation of a 64-bit signed integer
_MALLOC()
char*						S64_ToString_Base(t_s64 n, char const* base);
#define c_s64_to_strbase	S64_ToString_Base //!< @alias{S64_ToString_Base}

//! Returns newly allocated string custom-base representation of an 8-bit unsigned integer
_MALLOC()
char*						U8_ToString_Base(t_u8 n, char const* base);
#define c_u8_to_strbase		U8_ToString_Base //!< @alias{U8_ToString_Base}

//! Returns newly allocated string custom-base representation of a 16-bit unsigned integer
_MALLOC()
char*						U16_ToString_Base(t_u16 n, char const* base);
#define c_u16_to_strbase	U16_ToString_Base //!< @alias{U16_ToString_Base}

//! Returns newly allocated string custom-base representation of a 32-bit unsigned integer
_MALLOC()
char*						U32_ToString_Base(t_u32 n, char const* base);
#define c_u32_to_strbase	U32_ToString_Base //!< @alias{U32_ToString_Base}

//! Returns newly allocated string custom-base representation of a 64-bit unsigned integer
_MALLOC()
char*						U64_ToString_Base(t_u64 n, char const* base);
#define c_u64_to_strbase	U64_ToString_Base //!< @alias{U64_ToString_Base}



/*
** ************************************************************************** *|
**                          String-to-int Conversions                         *|
** ************************************************************************** *|
*/

//! Parse an 8-bit signed integer from the given decimal number string
t_s8					S8_FromString(char const* str);
#define c_str_to_s8		S8_FromString //!< @alias{S8_FromString}

//! Parse a 16-bit signed integer from the given decimal number string
t_s16					S16_FromString(char const* str);
#define c_str_to_s16	S16_FromString //!< @alias{S16_FromString}

//! Parse a 32-bit signed integer from the given decimal number string
t_s32					S32_FromString(char const* str);
#define c_str_to_s32	S32_FromString //!< @alias{S32_FromString}

//! Parse a 64-bit signed integer from the given decimal number string
t_s64					S64_FromString(char const* str);
#define c_str_to_s64	S64_FromString //!< @alias{S64_FromString}

//! Parse an 8-bit unsigned integer from the given decimal number string
t_u8					U8_FromString(char const* str);
#define c_str_to_u8		U8_FromString //!< @alias{U8_FromString}

//! Parse a 16-bit unsigned integer from the given decimal number string
t_u16					U16_FromString(char const* str);
#define c_str_to_u16	U16_FromString //!< @alias{U16_FromString}

//! Parse a 32-bit unsigned integer from the given decimal number string
t_u32					U32_FromString(char const* str);
#define c_str_to_u32	U32_FromString //!< @alias{U32_FromString}

//! Parse a 64-bit unsigned integer from the given decimal number string
t_u64					U64_FromString(char const* str);
#define c_str_to_u64	U64_FromString //!< @alias{U64_FromString}



//! Parse an 8-bit unsigned integer from the given haxedecimal number string
t_u8						U8_FromString_Hex(char const* str);
#define c_strhex_to_u8		U8_FromString_Hex //!< @alias{U8_FromString_Hex}

//! Parse a 16-bit unsigned integer from the given haxedecimal number string
t_u16						U16_FromString_Hex(char const* str);
#define c_strhex_to_u16		U16_FromString_Hex //!< @alias{U16_FromString_Hex}

//! Parse a 32-bit unsigned integer from the given haxedecimal number string
t_u32						U32_FromString_Hex(char const* str);
#define c_strhex_to_u32		U32_FromString_Hex //!< @alias{U32_FromString_Hex}

//! Parse a 64-bit unsigned integer from the given haxedecimal number string
t_u64						U64_FromString_Hex(char const* str);
#define c_strhex_to_u64		U64_FromString_Hex //!< @alias{U64_FromString_Hex}



//! Parse an 8-bit signed integer from a custom-base number string
t_s8						S8_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s8		S8_FromString_Base //!< @alias{S8_FromString_Base}

//! Parse a 16-bit signed integer from a custom-base number string
t_s16						S16_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s16	S16_FromString_Base //!< @alias{S16_FromString_Base}

//! Parse a 32-bit signed integer from a custom-base number string
t_s32						S32_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s32	S32_FromString_Base //!< @alias{S32_FromString_Base}

//! Parse a 64-bit signed integer from a custom-base number string
t_s64						S64_FromString_Base(char const* str, char const* base);
#define c_strbase_to_s64	S64_FromString_Base //!< @alias{S64_FromString_Base}

//! Parse an 8-bit unsigned integer from a custom-base number string
t_u8						U8_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u8		U8_FromString_Base //!< @alias{U8_FromString_Base}

//! Parse a 16-bit unsigned integer from a custom-base number string
t_u16						U16_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u16	U16_FromString_Base //!< @alias{U16_FromString_Base}

//! Parse a 32-bit unsigned integer from a custom-base number string
t_u32						U32_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u32	U32_FromString_Base //!< @alias{U32_FromString_Base}

//! Parse a 64-bit unsigned integer from a custom-base number string
t_u64						U64_FromString_Base(char const* str, char const* base);
#define c_strbase_to_u64	U64_FromString_Base //!< @alias{U64_FromString_Base}



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
