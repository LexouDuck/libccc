/*============================================================================*\
||                                            ______________________________  ||
||  libccc/int.h                             |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_INT_H
#define __LIBCCC_INT_H
/*!@group{libccc_int,12,libccc/int.h}
**
**	This header defines the integer number primitive types and functions.
**
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
**	@isostd{C,https://en.cppreference.com/w/c/types/limits}
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

#ifndef __NOSTD__
	#include <stdint.h>
#else
// TODO: better logic than just using 'long' here, with the __DATAMODEL__ macro ?
	typedef unsigned char		uint8_t;
	typedef unsigned short		uint16_t;
	typedef unsigned long		uint32_t;
	typedef unsigned long long	uint64_t;
	typedef signed char			int8_t;
	typedef signed short		int16_t;
	typedef signed long			int32_t;
	typedef signed long long	int64_t;

	typedef uint8_t		uint_least8_t;
	typedef uint16_t	uint_least16_t;
	typedef uint32_t	uint_least32_t;
	typedef uint64_t	uint_least64_t;
	typedef int8_t		int_least8_t;
	typedef int16_t		int_least16_t;
	typedef int32_t		int_least32_t;
	typedef int64_t		int_least64_t;

	typedef uint8_t		uint_fast8_t;
	typedef uint16_t	uint_fast16_t;
	typedef uint32_t	uint_fast32_t;
	typedef uint64_t	uint_fast64_t;
	typedef int8_t		int_fast8_t;
	typedef int16_t		int_fast16_t;
	typedef int32_t		int_fast32_t;
	typedef int64_t		int_fast64_t;
#endif

#ifndef LIBCONFIG_INTEGER_TYPES
	#define STDINT(TYPE, BITS)	TYPE##BITS##_t
#else
	#define STDINT(TYPE, BITS)	TYPE##LIBCONFIG_INTEGER_TYPES##BITS##_t
#endif
typedef STDINT(uint, 8)	u8_t;
typedef STDINT(uint,16)	u16_t;
typedef STDINT(uint,32)	u32_t;
typedef	STDINT(uint,64)	u64_t;
#if LIBCONFIG_USE_INT128
typedef _UInt128	u128_t;
#endif
typedef STDINT(int,  8)	s8_t;
typedef STDINT(int, 16)	s16_t;
typedef STDINT(int, 32)	s32_t;
typedef	STDINT(int, 64)	s64_t;
#if LIBCONFIG_USE_INT128
typedef _SInt128	s128_t;
#endif

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_INT_T
#define __LIBCCC_INT_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//!@doc Primitive type: 8-bit unsigned integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef u8_t	t_u8;
TYPEDEF_ALIAS(	t_u8,	UINT_8,  PRIMITIVE)
//!@}

//!@doc Primitive type: 16-bit unsigned integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef u16_t	t_u16;
TYPEDEF_ALIAS(	t_u16,	UINT_16, PRIMITIVE)
//!@}

//!@doc Primitive type: 32-bit unsigned integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef u32_t	t_u32;
TYPEDEF_ALIAS(	t_u32,	UINT_32, PRIMITIVE)
//!@}

//!@doc Primitive type: 64-bit unsigned integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef	u64_t	t_u64;
TYPEDEF_ALIAS(	t_u64,	UINT_64, PRIMITIVE)
//!@}

#if LIBCONFIG_USE_INT128
//!@doc Primitive type: 128-bit unsigned integer (only available on certain platforms)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef u128_t	t_u128;
TYPEDEF_ALIAS(	t_u128,	UINT_128,PRIMITIVE)
//!@}
#elif (LIBCONFIG_UINT_BITS == 128)
#error "Cannot set default unsigned int type to 128-bit, unavailable on this platform"
#endif



//!@doc Primitive type: 8-bit signed integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef s8_t	t_s8;
TYPEDEF_ALIAS(	t_s8,	SINT_8,  PRIMITIVE)
//!@}

//!@doc Primitive type: 16-bit signed integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef s16_t	t_s16;
TYPEDEF_ALIAS(	t_s16,	SINT_16, PRIMITIVE)
//!@}

//!@doc Primitive type: 32-bit signed integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef s32_t	t_s32;
TYPEDEF_ALIAS(	t_s32,	SINT_32, PRIMITIVE)
//!@}

//!@doc Primitive type: 64-bit signed integer
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef	s64_t	t_s64;
TYPEDEF_ALIAS(	t_s64,	SINT_64, PRIMITIVE)
//!@}

#if LIBCONFIG_USE_INT128
//!@doc Primitive type: 128-bit signed integer (only available on certain platforms)
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
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
//!@{
typedef s128_t	t_s128;
TYPEDEF_ALIAS(	t_s128,	SINT_128,PRIMITIVE)
//!@}
#elif (LIBCONFIG_SINT_BITS == 128)
#error "Cannot set default signed int type to 128-bit, unavailable on this platform"
#endif



//!@doc The configurable-size unsigned integer primitive type.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**
**	Configurable-width unsigned integer type.
**	The size of this integer type depends on the value of #LIBCONFIG_UINT_BITS.
**	This is meant to be used as a "default integer type", a type where the
**	programmer doesn't need to worry about integer overflow behaviors being
**	platform-dependent (like they would if they used the C native `int` type).
**	This type can express a number between `0` and #UINT_MAX
*/
//!@{

//! The actual underlying type for the `t_uint` configurable type
#define UINT_T		CONCAT(t_u,LIBCONFIG_UINT_BITS)
//! The actual underlying type for the `t_uint` configurable type, in uppercase
#define UINT_TYPE	CONCAT(U,LIBCONFIG_UINT_BITS)

typedef UINT_T	t_uint;
TYPEDEF_ALIAS(t_uint, UINT, PRIMITIVE)
//!@}



//!@doc The configurable-size signed integer primitive type.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**
**	Configurable-width signed integer type.
**	The size of this integer type depends on the value of #LIBCONFIG_SINT_BITS.
**	This is meant to be used as a "default integer type", a type where the
**	programmer doesn't need to worry about integer overflow behaviors being
**	platform-dependent (like they would if they used the C native `int` type).
**	This type can express a number between #SINT_MIN and #SINT_MAX.
*/
//!@{

//! The actual underlying type for the `t_sint` configurable type
#define SINT_T		CONCAT(t_s,LIBCONFIG_SINT_BITS)
//! The actual underlying type for the `t_sint` configurable type, in uppercase
#define SINT_TYPE	CONCAT(S,LIBCONFIG_SINT_BITS)

typedef SINT_T	t_sint;
TYPEDEF_ALIAS(t_sint, SINT, PRIMITIVE)
//!@}



#if LIBCONFIG_UINT_BITS != 8 && \
	LIBCONFIG_UINT_BITS != 16 && \
	LIBCONFIG_UINT_BITS != 32 && \
	LIBCONFIG_UINT_BITS != 64 && \
	LIBCONFIG_UINT_BITS != 128
	#error "LIBCONFIG_UINT_BITS must be equal to one of: 8, 16, 32, 64, 128"
#endif

#if LIBCONFIG_SINT_BITS != 8 && \
	LIBCONFIG_SINT_BITS != 16 && \
	LIBCONFIG_SINT_BITS != 32 && \
	LIBCONFIG_SINT_BITS != 64 && \
	LIBCONFIG_SINT_BITS != 128
	#error "LIBCONFIG_SINT_BITS must be equal to one of: 8, 16, 32, 64, 128"
#endif


/*
#ifdef LIBCONFIG_INTEGER_TYPES

	#define U8_MAX	((t_u8)-1)						//!< The largest representable value for at least size  8-bit, unsigned integer type
	#define S8_MAX	((t_s8)(U8_MAX  >> 1))			//!< The largest representable value for at least size  8-bit, signed integer type
	#define S8_MIN	((t_s8)((U8_MAX  >> 1) + 1))	//!< The minimum representable value for at least size  8-bit, signed integer type

	#define U16_MAX	((t_u16)-1)						//!< The largest representable value for at least size 16-bit, unsigned integer type
	#define S16_MAX	((t_s16)(U16_MAX >> 1))			//!< The largest representable value for at least size 16-bit, signed integer type
	#define S16_MIN	((t_s16)((U16_MAX >> 1) + 1))	//!< The minimum representable value for at least size 16-bit, signed integer type

	#define U32_MAX	((t_u32)-1)						//!< The largest representable value for at least size 32-bit, unsigned integer type
	#define S32_MAX	((t_s32)(U32_MAX >> 1))			//!< The largest representable value for at least size 32-bit, signed integer type
	#define S32_MIN	((t_s32)((U32_MAX >> 1) + 1))	//!< The minimum representable value for at least size 32-bit, signed integer type

	#define U64_MAX	((t_u64)-1)						//!< The largest representable value for at least size 64-bit, unsigned integer type
	#define S64_MAX	((t_s64)(U64_MAX >> 1))			//!< The largest representable value for at least size 64-bit, signed integer type
	#define S64_MIN	((t_s64)((U64_MAX >> 1) + 1))	//!< The minimum representable value for at least size 64-bit, signed integer type

	#if LIBCONFIG_USE_INT128
	#define U128_MAX ((t_u128)-1)					//!< The largest representable value for at least size 128-bit, unsigned integer type
	#define S128_MAX ((t_s128)(U128_MAX >> 1))		//!< The largest representable value for at least size 128-bit, signed integer type
	#define S128_MIN ((t_s128)((U128_MAX >> 1) + 1))//!< The minimum representable value for at least size 128-bit, signed integer type
	#endif
#else
#endif
*/

//!@doc Macros which define upper/lower bounds of integer types, and special values
//!@{
#undef UINT_ERROR
#undef UINT_MAX

#undef SINT_ERROR
#undef SINT_MAX
#undef SINT_MIN

#if (LIBCONFIG_UINT_NAN == 0) && (LIBCONFIG_UINT_INF == 0)

	#define U8_MIN		((t_u8)0x00)	//!< The minimum representable value for a 8-bit unsigned integer (0)
	#define U8_MAX		((t_u8)0xFF)	//!< The largest representable value for a 8-bit unsigned integer (255)

	#define U16_MIN		((t_u16)0x0000)	//!< The minimum representable value for a 16-bit unsigned integer (0)
	#define U16_MAX		((t_u16)0xFFFF)	//!< The largest representable value for a 16-bit unsigned integer (65535)

	#define U32_MIN		((t_u32)0x00000000)	//!< The minimum representable value for a 32-bit unsigned integer (0)
	#define U32_MAX		((t_u32)0xFFFFFFFF)	//!< The largest representable value for a 32-bit unsigned integer (4294967295)

	#define U64_MIN		((t_u64)0x0000000000000000)	//!< The minimum representable value for a 64-bit unsigned integer (0)
	#define U64_MAX		((t_u64)0xFFFFFFFFFFFFFFFF)	//!< The largest representable value for a 64-bit unsigned integer (18446744073709551615)

	#if LIBCONFIG_USE_INT128
	#define U128_MIN	((t_u128)0) //!< The minimum representable value for a 128-bit unsigned integer (0)
	#define U128_MAX	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)) //!< The largest representable value for a 128-bit unsigned integer (340282366920938463463374607431768211455)
	#endif

	#define UINT_MIN	((t_uint) 0)	//!< The minimum representable value for a configurable-size unsigned integer type (0)
	#define UINT_MAX	((t_uint)-1)	//!< The largest representable value for a configurable-size unsigned integer type

#elif (LIBCONFIG_UINT_NAN)

	#define U8_MIN		((t_u8)0x00)	//!< The minimum representable value for a 8-bit unsigned integer (0)
	#define U8_MAX		((t_u8)0xFE)	//!< The largest representable value for a 8-bit unsigned integer (254)
	#define U8_NAN		((t_u8)0xFF)

	#define U16_MIN		((t_u16)0x0000)	//!< The minimum representable value for a 16-bit unsigned integer (0)
	#define U16_MAX		((t_u16)0xFFFE)	//!< The largest representable value for a 16-bit unsigned integer (65534)
	#define U16_NAN		((t_u16)0xFFFF)

	#define U32_MIN		((t_u32)0x00000000)	//!< The minimum representable value for a 32-bit unsigned integer (0)
	#define U32_MAX		((t_u32)0xFFFFFFFE)	//!< The largest representable value for a 32-bit unsigned integer (4294967294)
	#define U32_NAN		((t_u32)0xFFFFFFFF)

	#define U64_MIN		((t_u64)0x0000000000000000)	//!< The minimum representable value for a 64-bit unsigned integer (0)
	#define U64_MAX		((t_u64)0xFFFFFFFFFFFFFFFE)	//!< The largest representable value for a 64-bit unsigned integer (18446744073709551614)
	#define U64_NAN		((t_u64)0xFFFFFFFFFFFFFFFF)

	#if LIBCONFIG_USE_INT128
	#define U128_MIN	((t_u128)0) //!< The minimum representable value for a 128-bit unsigned integer (0)
	#define U128_MAX	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE)) //!< The largest representable value for a 128-bit unsigned integer (340282366920938463463374607431768211454)
	#define U128_NAN	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))
	#endif

	#define UINT_MIN	((t_uint) 0)	//!< The minimum representable value for a configurable-size unsigned integer type (0)
	#define UINT_MAX	((t_uint)-2)	//!< The largest representable value for a configurable-size unsigned integer type
	#define UINT_NAN	((t_uint)-1)

#elif (LIBCONFIG_UINT_INF)

	#define U8_MIN		((t_u8)0x00)	//!< The minimum representable value for a 8-bit unsigned integer (0)
	#define U8_MAX		((t_u8)0xFE)	//!< The largest representable value for a 8-bit unsigned integer (254)
	#define U8_INF		((t_u8)0xFF)

	#define U16_MIN		((t_u16)0x0000)	//!< The minimum representable value for a 16-bit unsigned integer (0)
	#define U16_MAX		((t_u16)0xFFFE)	//!< The largest representable value for a 16-bit unsigned integer (65534)
	#define U16_INF		((t_u16)0xFFFF)

	#define U32_MIN		((t_u32)0x00000000)	//!< The minimum representable value for a 32-bit unsigned integer (0)
	#define U32_MAX		((t_u32)0xFFFFFFFE)	//!< The largest representable value for a 32-bit unsigned integer (4294967294)
	#define U32_INF		((t_u32)0xFFFFFFFF)

	#define U64_MIN		((t_u64)0x0000000000000000)	//!< The minimum representable value for a 64-bit unsigned integer (0)
	#define U64_MAX		((t_u64)0xFFFFFFFFFFFFFFFE)	//!< The largest representable value for a 64-bit unsigned integer (18446744073709551614)
	#define U64_INF		((t_u64)0xFFFFFFFFFFFFFFFF)

	#if LIBCONFIG_USE_INT128
	#define U128_MIN	((t_u128)0) //!< The minimum representable value for a 128-bit unsigned integer (0)
	#define U128_MAX	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE)) //!< The largest representable value for a 128-bit unsigned integer (340282366920938463463374607431768211454)
	#define U128_INF	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))
	#endif

	#define UINT_MIN	((t_uint) 0)	//!< The minimum representable value for a configurable-size unsigned integer type (0)
	#define UINT_MAX	((t_uint)-2)	//!< The largest representable value for a configurable-size unsigned integer type
	#define UINT_INF	((t_uint)-1)

#else

	#define U8_MIN		((t_u8)0x00)	//!< The minimum representable value for a 8-bit unsigned integer (0)
	#define U8_MAX		((t_u8)0xFD)	//!< The largest representable value for a 8-bit unsigned integer (254)
	#define U8_INF		((t_u8)0xFE)
	#define U8_NAN		((t_u8)0xFF)

	#define U16_MIN		((t_u16)0x0000)	//!< The minimum representable value for a 16-bit unsigned integer (0)
	#define U16_MAX		((t_u16)0xFFFD)	//!< The largest representable value for a 16-bit unsigned integer (65534)
	#define U16_INF		((t_u16)0xFFFE)
	#define U16_NAN		((t_u16)0xFFFF)

	#define U32_MIN		((t_u32)0x00000000)	//!< The minimum representable value for a 32-bit unsigned integer (0)
	#define U32_MAX		((t_u32)0xFFFFFFFD)	//!< The largest representable value for a 32-bit unsigned integer (4294967294)
	#define U32_INF		((t_u32)0xFFFFFFFE)
	#define U32_NAN		((t_u32)0xFFFFFFFF)

	#define U64_MIN		((t_u64)0x0000000000000000)	//!< The minimum representable value for a 64-bit unsigned integer (0)
	#define U64_MAX		((t_u64)0xFFFFFFFFFFFFFFFD)	//!< The largest representable value for a 64-bit unsigned integer (18446744073709551614)
	#define U64_INF		((t_u64)0xFFFFFFFFFFFFFFFE)
	#define U64_NAN		((t_u64)0xFFFFFFFFFFFFFFFF)

	#if LIBCONFIG_USE_INT128
	#define U128_MIN	((t_u128)0) //!< The minimum representable value for a 128-bit unsigned integer (0)
	#define U128_MAX	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFD)) //!< The largest representable value for a 128-bit unsigned integer (340282366920938463463374607431768211454)
	#define U128_INF	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define U128_NAN	((t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))
	#endif

	#define UINT_MIN	((t_uint) 0)	//!< The minimum representable value for a configurable-size unsigned integer type (0)
	#define UINT_MAX	((t_uint)-3)	//!< The largest representable value for a configurable-size unsigned integer type
	#define UINT_INF	((t_uint)-2)
	#define UINT_NAN	((t_uint)-1)

#endif



#if (LIBCONFIG_SINT_NAN == 0) && (LIBCONFIG_SINT_INF == 0)

	#define S8_MIN_VAL	S8_MIN
	#define S8_MAX_VAL	S8_MAX
	#define S8_MIN		((t_s8)0x80)	//!< The minimum representable value for a 8-bit signed integer (-128)
	#define S8_MAX		((t_s8)0x7F)	//!< The largest representable value for a 8-bit signed integer (+127)

	#define S16_MIN_VAL	S16_MIN
	#define S16_MAX_VAL	S16_MAX
	#define S16_MIN		((t_s16)0x8000)	//!< The minimum representable value for a 16-bit signed integer (-32768)
	#define S16_MAX		((t_s16)0x7FFF)	//!< The largest representable value for a 16-bit signed integer (+32767)

	#define S32_MIN_VAL	S32_MIN
	#define S32_MAX_VAL	S32_MAX
	#define S32_MIN		((t_s32)0x80000000)	//!< The minimum representable value for a 32-bit signed integer (-2147483648)
	#define S32_MAX		((t_s32)0x7FFFFFFF)	//!< The largest representable value for a 32-bit signed integer (+2147483647)

	#define S64_MIN_VAL	S64_MIN
	#define S64_MAX_VAL	S64_MAX
	#define S64_MIN		((t_s64)0x8000000000000000)	//!< The minimum representable value for a 64-bit signed integer (-9223372036854775808)
	#define S64_MAX		((t_s64)0x7FFFFFFFFFFFFFFF)	//!< The largest representable value for a 64-bit signed integer (+9223372036854775807)

	#if LIBCONFIG_USE_INT128
	#define S128_MIN_VAL	S128_MIN
	#define S128_MAX_VAL	S128_MAX
	#define S128_MIN		((t_s128)(((t_s128)0x8000000000000000 << 64) | 0x0000000000000000))	//!< The minimum representable value for a 128-bit signed integer	(−170141183460469231731687303715884105728)
	#define S128_MAX		((t_s128)(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The largest representable value for a 128-bit signed integer	(+170141183460469231731687303715884105727)
	#endif

	#define SINT_MIN_VAL	SINT_MIN
	#define SINT_MAX_VAL	SINT_MAX
	#define SINT_MIN		((t_sint)((t_uint)1 << (LIBCONFIG_UINT_BITS - 1)))	//!< The minimum representable value for a configurable-size signed integer type
	#define SINT_MAX		((t_sint)((~(t_uint)0) >> 1))	//!< The largest representable value for a configurable-size signed integer type

#elif (LIBCONFIG_SINT_NAN)

	#define S8_MIN_VAL	S8_MIN
	#define S8_MAX_VAL	S8_MAX
	#define S8_MIN		((t_s8)-0x7F)	//!< The minimum representable value for a 8-bit signed integer (-127)
	#define S8_MAX		((t_s8)+0x7F)	//!< The largest representable value for a 8-bit signed integer (+127)
	#define S8_NAN		((t_s8) 0x80)

	#define S16_MIN_VAL	S16_MIN
	#define S16_MAX_VAL	S16_MAX
	#define S16_MIN		((t_s16)-0x7FFF)	//!< The minimum representable value for a 16-bit signed integer (-32767)
	#define S16_MAX		((t_s16)+0x7FFF)	//!< The largest representable value for a 16-bit signed integer (+32767)
	#define S16_NAN		((t_s16) 0x8000)

	#define S32_MIN_VAL	S32_MIN
	#define S32_MAX_VAL	S32_MAX
	#define S32_MIN		((t_s32)-0x7FFFFFFF)	//!< The minimum representable value for a 32-bit signed integer (-2147483647)
	#define S32_MAX		((t_s32)+0x7FFFFFFF)	//!< The largest representable value for a 32-bit signed integer (+2147483647)
	#define S32_NAN		((t_s32) 0x80000000)

	#define S64_MIN_VAL	S64_MIN
	#define S64_MAX_VAL	S64_MAX
	#define S64_MIN		((t_s64)-0x7FFFFFFFFFFFFFFF)	//!< The minimum representable value for a 64-bit signed integer (-9223372036854775807)
	#define S64_MAX		((t_s64)+0x7FFFFFFFFFFFFFFF)	//!< The largest representable value for a 64-bit signed integer (+9223372036854775807)
	#define S64_NAN		((t_s64) 0x8000000000000000)

	#if LIBCONFIG_USE_INT128
	#define S128_MIN_VAL	S128_MIN
	#define S128_MAX_VAL	S128_MAX
	#define S128_MIN		((t_s128)-(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The minimum representable value for a 128-bit signed integer	(−170141183460469231731687303715884105728)
	#define S128_MAX		((t_s128)+(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The largest representable value for a 128-bit signed integer	(+170141183460469231731687303715884105727)
	#define S128_NAN		((t_s128) (((t_s128)0x8000000000000000 << 64) | 0x0000000000000000))
	#endif

	#define SINT_MIN_VAL	SINT_MIN
	#define SINT_MAX_VAL	SINT_MAX
	#define SINT_MIN		((t_sint)-((~(t_uint)0) >> 1))	//!< The minimum representable value for a configurable-size signed integer type
	#define SINT_MAX		((t_sint)+((~(t_uint)0) >> 1))	//!< The largest representable value for a configurable-size signed integer type
	#define SINT_NAN		((t_sint)((t_uint)1 << (LIBCONFIG_UINT_BITS - 1)))

#elif (LIBCONFIG_SINT_INF)

	#define S8_MIN_VAL	((t_s8)-0x7E)
	#define S8_MAX_VAL	((t_s8)+0x7E)
	#define S8_MIN		((t_s8)-0x7F)	//!< The minimum representable value for a 8-bit signed integer (-127)
	#define S8_MAX		((t_s8)+0x7F)	//!< The largest representable value for a 8-bit signed integer (+127)
	#define S8_INF		((t_s8) 0x80)

	#define S16_MIN_VAL	((t_s16)-0x7FFE)
	#define S16_MAX_VAL	((t_s16)+0x7FFE)
	#define S16_MIN		((t_s16)-0x7FFF)	//!< The minimum representable value for a 16-bit signed integer (-32767)
	#define S16_MAX		((t_s16)+0x7FFF)	//!< The largest representable value for a 16-bit signed integer (+32767)
	#define S16_INF		((t_s16) 0x8000)

	#define S32_MIN_VAL	((t_s32)-0x7FFFFFFE)
	#define S32_MAX_VAL	((t_s32)+0x7FFFFFFE)
	#define S32_MIN		((t_s32)-0x7FFFFFFF)	//!< The minimum representable value for a 32-bit signed integer (-2147483647)
	#define S32_MAX		((t_s32)+0x7FFFFFFF)	//!< The largest representable value for a 32-bit signed integer (+2147483647)
	#define S32_INF		((t_s32) 0x80000000)

	#define S64_MIN_VAL	((t_s64)-0x7FFFFFFFFFFFFFFE)
	#define S64_MAX_VAL	((t_s64)+0x7FFFFFFFFFFFFFFE)
	#define S64_MIN		((t_s64)-0x7FFFFFFFFFFFFFFF)	//!< The minimum representable value for a 64-bit signed integer (-9223372036854775807)
	#define S64_MAX		((t_s64)+0x7FFFFFFFFFFFFFFF)	//!< The largest representable value for a 64-bit signed integer (+9223372036854775807)
	#define S64_INF		((t_s64) 0x8000000000000000)

	#if LIBCONFIG_USE_INT128
	#define S128_MIN_VAL	((t_s128)-(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define S128_MAX_VAL	((t_s128)+(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define S128_MIN		((t_s128)-(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The minimum representable value for a 128-bit signed integer	(−170141183460469231731687303715884105728)
	#define S128_MAX		((t_s128)+(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The largest representable value for a 128-bit signed integer	(+170141183460469231731687303715884105727)
	#define S128_INF		((t_s128) (((t_s128)0x8000000000000000 << 64) | 0x0000000000000000))
	#endif

	#define SINT_MIN_VAL	((t_sint)-(((~(t_uint)0) << 1) >> 1))
	#define SINT_MAX_VAL	((t_sint)+(((~(t_uint)0) << 1) >> 1))
	#define SINT_MIN		((t_sint)-((~(t_uint)0) >> 1))	//!< The minimum representable value for a configurable-size signed integer type
	#define SINT_MAX		((t_sint)+((~(t_uint)0) >> 1))	//!< The largest representable value for a configurable-size signed integer type
	#define SINT_INF		((t_sint)((t_uint)1 << (LIBCONFIG_UINT_BITS - 1)))

#else

	#define S8_MIN_VAL	((t_s8)-0x7E)
	#define S8_MAX_VAL	((t_s8)+0x7E)
	#define S8_MIN		((t_s8)-0x7F)	//!< The minimum representable value for a 8-bit signed integer (-127)
	#define S8_MAX		((t_s8)+0x7F)	//!< The largest representable value for a 8-bit signed integer (+127)
	#define S8_INF		((t_s8)+0x7F)
	#define S8_NAN		((t_s8) 0x80)

	#define S16_MIN_VAL	((t_s16)-0x7FFE)
	#define S16_MAX_VAL	((t_s16)+0x7FFE)
	#define S16_MIN		((t_s16)-0x7FFF)	//!< The minimum representable value for a 16-bit signed integer (-32767)
	#define S16_MAX		((t_s16)+0x7FFF)	//!< The largest representable value for a 16-bit signed integer (+32767)
	#define S16_INF		((t_s16)+0x7FFF)
	#define S16_NAN		((t_s16) 0x8000)

	#define S32_MIN_VAL	((t_s32)-0x7FFFFFFE)
	#define S32_MAX_VAL	((t_s32)+0x7FFFFFFE)
	#define S32_MIN		((t_s32)-0x7FFFFFFF)	//!< The minimum representable value for a 32-bit signed integer (-2147483647)
	#define S32_MAX		((t_s32)+0x7FFFFFFF)	//!< The largest representable value for a 32-bit signed integer (+2147483647)
	#define S32_INF		((t_s32)+0x7FFFFFFF)
	#define S32_NAN		((t_s32) 0x80000000)

	#define S64_MIN_VAL	((t_s64)-0x7FFFFFFFFFFFFFFE)
	#define S64_MAX_VAL	((t_s64)+0x7FFFFFFFFFFFFFFE)
	#define S64_MIN		((t_s64)-0x7FFFFFFFFFFFFFFF)	//!< The minimum representable value for a 64-bit signed integer (-9223372036854775807)
	#define S64_MAX		((t_s64)+0x7FFFFFFFFFFFFFFF)	//!< The largest representable value for a 64-bit signed integer (+9223372036854775807)
	#define S64_INF		((t_s64)+0x7FFFFFFFFFFFFFFF)
	#define S64_NAN		((t_s64) 0x8000000000000000)

	#if LIBCONFIG_USE_INT128
	#define S128_MIN_VAL	((t_s128)-(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define S128_MAX_VAL	((t_s128)+(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFE))
	#define S128_MIN		((t_s128)-(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The minimum representable value for a 128-bit signed integer	(−170141183460469231731687303715884105728)
	#define S128_MAX		((t_s128)+(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))	//!< The largest representable value for a 128-bit signed integer	(+170141183460469231731687303715884105727)
	#define S128_INF		((t_s128)+(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF))
	#define S128_NAN		((t_s128) (((t_s128)0x8000000000000000 << 64) | 0x0000000000000000))
	#endif

	#define SINT_MIN_VAL	((t_sint)-(((~(t_uint)0) << 1) >> 1))
	#define SINT_MAX_VAL	((t_sint)+(((~(t_uint)0) << 1) >> 1))
	#define SINT_MIN		((t_sint)-((~(t_uint)0) >> 1))	//!< The minimum representable value for a configurable-size signed integer type
	#define SINT_MAX		((t_sint)+((~(t_uint)0) >> 1))	//!< The largest representable value for a configurable-size signed integer type
	#define SINT_INF		((t_sint)+((~(t_uint)0) >> 1))
	#define SINT_NAN		((t_sint)((t_uint)1 << (LIBCONFIG_UINT_BITS - 1)))

#endif
//!@}

//!@doc Macros which define the default error value of integer types
//!@{
#if (LIBCONFIG_UINT_NAN)
	#define U8_ERROR	U8_NAN
	#define U16_ERROR	U16_NAN
	#define U32_ERROR	U32_NAN
	#define U64_ERROR	U64_NAN
	#if LIBCONFIG_USE_INT128
	#define U128_ERROR	U128_NAN
	#endif
	#define UINT_ERROR	UINT_NAN
#else
	#define U8_ERROR	((t_u8)0)
	#define U16_ERROR	((t_u16)0)
	#define U32_ERROR	((t_u32)0)
	#define U64_ERROR	((t_u64)0)
	#if LIBCONFIG_USE_INT128
	#define U128_ERROR	((t_u128)0)
	#endif
	#define UINT_ERROR	((t_uint)0)
#endif

#if (LIBCONFIG_SINT_NAN)
	#define S8_ERROR	S8_NAN
	#define S16_ERROR	S16_NAN
	#define S32_ERROR	S32_NAN
	#define S64_ERROR	S64_NAN
	#if LIBCONFIG_USE_INT128
	#define S128_ERROR	S128_NAN
	#endif
	#define SINT_ERROR	SINT_NAN
#else
	#define S8_ERROR	((t_s8)0)
	#define S16_ERROR	((t_s16)0)
	#define S32_ERROR	((t_s32)0)
	#define S64_ERROR	((t_s64)0)
	#if LIBCONFIG_USE_INT128
	#define S128_ERROR	((t_s128)0)
	#endif
	#define SINT_ERROR	((t_sint)0)
#endif
//!@}



#endif
#ifndef __LIBCCC_INT_F
#define __LIBCCC_INT_F

/*
** ************************************************************************** *|
**                         Integer conversion functions                       *|
** ************************************************************************** *|
*/

//!@doc A smart constructor: calls the appropriate `Fixed_From*()` function from the given argument type
//!@{
#define DEFINEFUNC_Int(X, FUNCTYPE) \
	_Generic((X), \
		t_s16:	 FUNCTYPE##_FromInt, \
		t_s32:	 FUNCTYPE##_FromInt, \
		t_s64:	 FUNCTYPE##_FromInt, \
		t_s128:	 FUNCTYPE##_FromInt, \
		t_sint:  FUNCTYPE##_FromInt, \
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

#define Int(X)		DEFINEFUNC_Int(X, Int)
#define S16(X)		DEFINEFUNC_Int(X, S16)
#define S32(X)		DEFINEFUNC_Int(X, S32)
#define S64(X)		DEFINEFUNC_Int(X, S64)
#define S128(X)		DEFINEFUNC_Int(X, S128)

#define c_int(X)	Int(X)
#define c_s16(X)	S16(X)
#define c_s32(X)	S32(X)
#define c_s64(X)	S64(X)
#define c_s128(X)	S128(X)
//!@}



//!@doc Cast the given value to an integer of the specified size
/*!
**	TODO document
*/
//!@{
#define					SInt_FromInt	CONCAT(SINT_TYPE,_FromInt)
#define c_stos			SInt_FromInt

t_s8					S8_FromInt(t_sint number);
#define c_stos8			S8_FromInt

t_s16					S16_FromInt(t_sint number);
#define c_stos16		S16_FromInt

t_s32					S32_FromInt(t_sint number);
#define c_stos32		S32_FromInt

t_s64					S64_FromInt(t_sint number);
#define c_stos64		S64_FromInt
#if LIBCONFIG_USE_INT128
t_s128					S128_FromInt(t_sint number);
#define c_stos128		S128_FromInt
#endif
//!@}

//!@doc Converts the given fixed-point value to the nearest representable integer
/*!
**	TODO document
*/
//!@{
#define					SInt_FromFixed	CONCAT(SINT_TYPE,_FromFixed)
#define c_qtos			SInt_FromFixed

t_s8					S8_FromFixed(t_fixed number);
#define c_qtos8			S8_FromFixed

t_s16					S16_FromFixed(t_fixed number);
#define c_qtos16		S16_FromFixed

t_s32					S32_FromFixed(t_fixed number);
#define c_qtos32		S32_FromFixed

t_s64					S64_FromFixed(t_fixed number);
#define c_qtos64		S64_FromFixed
#if LIBCONFIG_USE_INT128
t_s128					S128_FromFixed(t_fixed number);
#define c_qtos128		S128_FromFixed
#endif
//!@}

//!@doc Converts the given floating-point value to the nearest representable integer
/*!
**	TODO document
*/
//!@{
#define					SInt_FromFloat	CONCAT(SINT_TYPE,_FromFloat)
#define c_ftos			SInt_FromFloat

t_s8					S8_FromFloat(t_float number);
#define c_ftos8			S8_FromFloat

t_s16					S16_FromFloat(t_float number);
#define c_ftos16		S16_FromFloat

t_s32					S32_FromFloat(t_float number);
#define c_ftos32		S32_FromFloat

t_s64					S64_FromFloat(t_float number);
#define c_ftos64		S64_FromFloat
#if LIBCONFIG_USE_INT128
t_s128					S128_FromFloat(t_float number);
#define c_ftos128		S128_FromFloat
#endif
//!@}



/*
** ************************************************************************** *|
**                        Integer-to-String Conversions                       *|
** ************************************************************************** *|
*/

// TODO Int_ToString() generic function



// General printer functions



//!@doc Get the string decimal (base 10) representation of an unsigned integer
/*!
**	@nonstd, `utoa()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString	CONCAT(UINT_TYPE,_ToString)
#define c_utostr		UInt_ToString

_MALLOC()	t_char*		U8_ToString	(t_u8  number);
#define c_u8tostr		U8_ToString

_MALLOC()	t_char*		U16_ToString(t_u16 number);
#define c_u16tostr		U16_ToString

_MALLOC()	t_char*		U32_ToString(t_u32 number);
#define c_u32tostr		U32_ToString

_MALLOC()	t_char*		U64_ToString(t_u64 number);
#define c_u64tostr		U64_ToString
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		U128_ToString(t_u128 number); // TODO implement
#define c_u128tostr		U128_ToString
#endif
//!@}

//!@doc Get the string decimal (base 10) representation of a signed integer
/*!
**	@nonstd, `itoa()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString	CONCAT(SINT_TYPE,_ToString)
#define c_stostr		SInt_ToString

_MALLOC()	t_char*		S8_ToString	(t_s8  number);
#define c_s8tostr		S8_ToString

_MALLOC()	t_char*		S16_ToString(t_s16 number);
#define c_s16tostr		S16_ToString

_MALLOC()	t_char*		S32_ToString(t_s32 number);
#define c_s32tostr		S32_ToString

_MALLOC()	t_char*		S64_ToString(t_s64 number);
#define c_s64tostr		S64_ToString
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		S128_ToString(t_s128 number); // TODO implement
#define c_s128tostr		S128_ToString
#endif
//!@}



// Decimal printer functions



//!@doc Get the string decimal (base 10) representation of an unsigned integer
/*!
**	@nonstd, `utoa()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString_Dec	CONCAT(UINT_TYPE,_ToString_Dec)
#define c_utostrdec		UInt_ToString_Dec

_MALLOC()	t_char*		U8_ToString_Dec	(t_u8  number);
#define c_u8tostrdec	U8_ToString_Dec

_MALLOC()	t_char*		U16_ToString_Dec(t_u16 number);
#define c_u16tostrdec	U16_ToString_Dec

_MALLOC()	t_char*		U32_ToString_Dec(t_u32 number);
#define c_u32tostrdec	U32_ToString_Dec

_MALLOC()	t_char*		U64_ToString_Dec(t_u64 number);
#define c_u64tostrdec	U64_ToString_Dec
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		U128_ToString_Dec(t_u128 number);
#define c_u128tostrdec	U128_ToString_Dec
#endif
//!@}

//!@doc Get the string decimal (base 10) representation of a signed integer
/*!
**	@nonstd, `itoa()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString_Dec	CONCAT(SINT_TYPE,_ToString_Dec)
#define c_stostrdec		SInt_ToString_Dec

_MALLOC()	t_char*		S8_ToString_Dec	(t_s8  number);
#define c_s8tostrdec	S8_ToString_Dec

_MALLOC()	t_char*		S16_ToString_Dec(t_s16 number);
#define c_s16tostrdec	S16_ToString_Dec

_MALLOC()	t_char*		S32_ToString_Dec(t_s32 number);
#define c_s32tostrdec	S32_ToString_Dec

_MALLOC()	t_char*		S64_ToString_Dec(t_s64 number);
#define c_s64tostrdec	S64_ToString_Dec
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		S128_ToString_Dec(t_s128 number);
#define c_s128tostrdec	S128_ToString_Dec
#endif
//!@}



// Hexadecimal printer functions



//!@doc Get the string hexadecimal (base 16) representation of an unsigned integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@param	prefix	If `TRUE`, the output string will have a `0x` hexadecimal number literal prefix
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString_Hex	CONCAT(UINT_TYPE,_ToString_Hex)
#define c_utostrhex		UInt_ToString_Hex

_MALLOC()	t_char*		U8_ToString_Hex	(t_u8  number, t_bool prefix);
#define c_u8tostrhex	U8_ToString_Hex

_MALLOC()	t_char*		U16_ToString_Hex(t_u16 number, t_bool prefix);
#define c_u16tostrhex	U16_ToString_Hex

_MALLOC()	t_char*		U32_ToString_Hex(t_u32 number, t_bool prefix);
#define c_u32tostrhex	U32_ToString_Hex

_MALLOC()	t_char*		U64_ToString_Hex(t_u64 number, t_bool prefix);
#define c_u64tostrhex	U64_ToString_Hex
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		U128_ToString_Hex(t_u128 number, t_bool prefix); // TODO implement
#define c_u128tostrhex	U128_ToString_Hex
#endif
//!@}

//!@doc Get the string hexadecimal (base 16) representation of a signed integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@param	prefix	If `TRUE`, the output string will have a `0x` hexadecimal number literal prefix
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString_Hex	CONCAT(SINT_TYPE,_ToString)
#define c_stostrhex		SInt_ToString_Hex

_MALLOC()	t_char*		S8_ToString_Hex	(t_s8  number, t_bool prefix);
#define c_s8tostrhex	S8_ToString_Hex

_MALLOC()	t_char*		S16_ToString_Hex(t_s16 number, t_bool prefix);
#define c_s16tostrhex	S16_ToString_Hex

_MALLOC()	t_char*		S32_ToString_Hex(t_s32 number, t_bool prefix);
#define c_s32tostrhex	S32_ToString_Hex

_MALLOC()	t_char*		S64_ToString_Hex(t_s64 number, t_bool prefix);
#define c_s64tostrhex	S64_ToString_Hex
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		S128_ToString_Hex(t_s128 number, t_bool prefix); // TODO implement
#define c_s128tostrhex	S128_ToString_Hex
#endif
//!@}



// Octal printer functions



//!@doc Get the string octal (base 8) representation of an unsigned integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@param	prefix	If `TRUE`, the output string will have a `0o` octal number literal prefix
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString_Oct	CONCAT(UINT_TYPE,_ToString_Oct)
#define c_utostroct		UInt_ToString_Oct

_MALLOC()	t_char*		U8_ToString_Oct	(t_u8  number, t_bool prefix);
#define c_u8tostroct	U8_ToString_Oct

_MALLOC()	t_char*		U16_ToString_Oct(t_u16 number, t_bool prefix);
#define c_u16tostroct	U16_ToString_Oct

_MALLOC()	t_char*		U32_ToString_Oct(t_u32 number, t_bool prefix);
#define c_u32tostroct	U32_ToString_Oct

_MALLOC()	t_char*		U64_ToString_Oct(t_u64 number, t_bool prefix);
#define c_u64tostroct	U64_ToString_Oct
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		U128_ToString_Oct(t_u128 number, t_bool prefix); // TODO implement
#define c_u128tostroct	U128_ToString_Oct
#endif
//!@}

//!@doc Get the string octal (base 8) representation of a signed integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@param	prefix	If `TRUE`, the output string will have a `0o` octal number literal prefix
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString_Oct	CONCAT(SINT_TYPE,_ToString)
#define c_stostroct		SInt_ToString_Oct

_MALLOC()	t_char*		S8_ToString_Oct	(t_s8  number, t_bool prefix);
#define c_s8tostroct	S8_ToString_Oct

_MALLOC()	t_char*		S16_ToString_Oct(t_s16 number, t_bool prefix);
#define c_s16tostroct	S16_ToString_Oct

_MALLOC()	t_char*		S32_ToString_Oct(t_s32 number, t_bool prefix);
#define c_s32tostroct	S32_ToString_Oct

_MALLOC()	t_char*		S64_ToString_Oct(t_s64 number, t_bool prefix);
#define c_s64tostroct	S64_ToString_Oct
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		S128_ToString_Oct(t_s128 number, t_bool prefix); // TODO implement
#define c_s128tostroct	S128_ToString_Oct
#endif
//!@}



// Binary printer functions



//!@doc Get the string binary (base 2) representation of an unsigned integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@param	prefix	If `TRUE`, the output string will have a `0b` binary number literal prefix
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString_Bin	CONCAT(UINT_TYPE,_ToString_Hex)
#define c_utostrbin		UInt_ToString_Bin

_MALLOC()	t_char*		U8_ToString_Bin	(t_u8  number, t_bool prefix);
#define c_u8tostrbin	U8_ToString_Bin

_MALLOC()	t_char*		U16_ToString_Bin(t_u16 number, t_bool prefix);
#define c_u16tostrbin	U16_ToString_Bin

_MALLOC()	t_char*		U32_ToString_Bin(t_u32 number, t_bool prefix);
#define c_u32tostrbin	U32_ToString_Bin

_MALLOC()	t_char*		U64_ToString_Bin(t_u64 number, t_bool prefix);
#define c_u64tostrbin	U64_ToString_Bin
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		U128_ToString_Bin(t_u128 number, t_bool prefix); // TODO implement
#define c_u128tostrbin	U128_ToString_Bin
#endif
//!@}

//!@doc Get the string binary (base 2) representation of a signed integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@param	prefix	If `TRUE`, the output string will have a `0b` binary number literal prefix
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString_Bin	CONCAT(SINT_TYPE,_ToString)
#define c_stostrbin		SInt_ToString_Bin

_MALLOC()	t_char*		S8_ToString_Bin	(t_s8  number, t_bool prefix);
#define c_s8tostrbin	S8_ToString_Bin

_MALLOC()	t_char*		S16_ToString_Bin(t_s16 number, t_bool prefix);
#define c_s16tostrbin	S16_ToString_Bin

_MALLOC()	t_char*		S32_ToString_Bin(t_s32 number, t_bool prefix);
#define c_s32tostrbin	S32_ToString_Bin

_MALLOC()	t_char*		S64_ToString_Bin(t_s64 number, t_bool prefix);
#define c_s64tostrbin	S64_ToString_Bin
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		S128_ToString_Bin(t_s128 number, t_bool prefix); // TODO implement
#define c_s128tostrbin	S128_ToString_Bin
#endif
//!@}



// Custom-base printer functions



//!@doc Get the string custom-base representation of an unsigned integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString_Base	CONCAT(UINT_TYPE,_ToString_Base)
#define c_utostrbase	UInt_ToString_Base

_MALLOC()	t_char*		U8_ToString_Base	(t_u8  number, t_char const* base);
#define c_u8tostrbase	U8_ToString_Base

_MALLOC()	t_char*		U16_ToString_Base	(t_u16 number, t_char const* base);
#define c_u16tostrbase	U16_ToString_Base

_MALLOC()	t_char*		U32_ToString_Base	(t_u32 number, t_char const* base);
#define c_u32tostrbase	U32_ToString_Base

_MALLOC()	t_char*		U64_ToString_Base	(t_u64 number, t_char const* base);
#define c_u64tostrbase	U64_ToString_Base
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		U128_ToString_Base	(t_u128 number, t_char const* base); // TODO implement
#define c_u128tostrbase	U128_ToString_Base
#endif
//!@}

//!@doc Get the string custom-base representation of a signed integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString_Base	CONCAT(SINT_TYPE,_ToString_Base)
#define c_stostrbase	SInt_ToString_Base

_MALLOC()	t_char*		S8_ToString_Base	(t_s8  number, t_char const* base);
#define c_s8tostrbase	S8_ToString_Base

_MALLOC()	t_char*		S16_ToString_Base	(t_s16 number, t_char const* base);
#define c_s16tostrbase	S16_ToString_Base

_MALLOC()	t_char*		S32_ToString_Base	(t_s32 number, t_char const* base);
#define c_s32tostrbase	S32_ToString_Base

_MALLOC()	t_char*		S64_ToString_Base	(t_s64 number, t_char const* base);
#define c_s64tostrbase	S64_ToString_Base
#if LIBCONFIG_USE_INT128
_MALLOC()	t_char*		S128_ToString_Base	(t_s128 number, t_char const* base); // TODO implement
#define c_s128tostrbase	S128_ToString_Base
#endif
//!@}



/*
** ************************************************************************** *|
**                          String-to-int Conversions                         *|
** ************************************************************************** *|
*/



// General parser functions



//!@doc Parse an unsigned integer from the given number string `str`
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					UInt_Parse	CONCAT(UINT_TYPE,_Parse)
#define c_uparse		UInt_Parse

t_size					U8_Parse	(t_u8	*dest, t_char const* str, t_size n);
#define c_u8parse		U8_Parse

t_size					U16_Parse	(t_u16	*dest, t_char const* str, t_size n);
#define c_u16parse		U16_Parse

t_size					U32_Parse	(t_u32	*dest, t_char const* str, t_size n);
#define c_u32parse		U32_Parse

t_size					U64_Parse	(t_u64	*dest, t_char const* str, t_size n);
#define c_u64parse		U64_Parse
#if LIBCONFIG_USE_INT128
t_size					U128_Parse	(t_u128	*dest, t_char const* str, t_size n);
#define c_u128parse		U128_Parse
#endif
//!@}

//!@doc Parse an unsigned integer from the given number string `str`
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					UInt_FromString	CONCAT(UINT_TYPE,_FromString)
#define c_strtou		UInt_FromString

t_u8					U8_FromString(t_char const* str);
#define c_strtou8		U8_FromString

t_u16					U16_FromString(t_char const* str);
#define c_strtou16		U16_FromString

t_u32					U32_FromString(t_char const* str);
#define c_strtou32		U32_FromString

t_u64					U64_FromString(t_char const* str);
#define c_strtou64		U64_FromString
#if LIBCONFIG_USE_INT128
t_u128					U128_FromString(t_char const* str);
#define c_strtou128		U128_FromString
#endif
//!@}

//!@doc Parse a signed integer from the given number string `str`
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					SInt_Parse	CONCAT(SINT_TYPE,_Parse)
#define c_sparse		SInt_Parse

t_size					S8_Parse	(t_s8	*dest, t_char const* str, t_size n);
#define c_s8parse		S8_Parse

t_size					S16_Parse	(t_s16	*dest, t_char const* str, t_size n);
#define c_s16parse		S16_Parse

t_size					S32_Parse	(t_s32	*dest, t_char const* str, t_size n);
#define c_s32parse		S32_Parse

t_size					S64_Parse	(t_s64	*dest, t_char const* str, t_size n);
#define c_s64parse		S64_Parse
#if LIBCONFIG_USE_INT128
t_size					S128_Parse	(t_s128	*dest, t_char const* str, t_size n);
#define c_s128parse		S128_Parse
#endif
//!@}

//!@doc Parse a signed integer from the given number string `str`
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					SInt_FromString	CONCAT(SINT_TYPE,_FromString)
#define c_strtos		SInt_FromString

t_s8					S8_FromString(t_char const* str);
#define c_strtos8		S8_FromString

t_s16					S16_FromString(t_char const* str);
#define c_strtos16		S16_FromString

t_s32					S32_FromString(t_char const* str);
#define c_strtos32		S32_FromString

t_s64					S64_FromString(t_char const* str);
#define c_strtos64		S64_FromString
#if LIBCONFIG_USE_INT128
t_s128					S128_FromString(t_char const* str);
#define c_strtos128		S128_FromString
#endif
//!@}



// Decimal parser functions



//!@doc Parse an unsigned integer from the given decimal number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be decimal number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					UInt_Parse_Dec	CONCAT(UINT_TYPE,_Parse_Dec)
#define c_uparsedec		UInt_Parse_Dec

t_size					U8_Parse_Dec	(t_u8	*dest, t_char const* str, t_size n);
#define c_u8parsedec	U8_Parse_Dec

t_size					U16_Parse_Dec	(t_u16	*dest, t_char const* str, t_size n);
#define c_u16parsedec	U16_Parse_Dec

t_size					U32_Parse_Dec	(t_u32	*dest, t_char const* str, t_size n);
#define c_u32parsedec	U32_Parse_Dec

t_size					U64_Parse_Dec	(t_u64	*dest, t_char const* str, t_size n);
#define c_u64parsedec	U64_Parse_Dec
#if LIBCONFIG_USE_INT128
t_size					U128_Parse_Dec	(t_u128	*dest, t_char const* str, t_size n);
#define c_u128parsedec	U128_Parse_Dec
#endif
//!@}

//!@doc Parse an unsigned integer from the given decimal number string
/*!
**	@nonstd, `atou()`
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					UInt_FromString_Dec	CONCAT(UINT_TYPE,_FromString_Dec)
#define c_strdectou		UInt_FromString_Dec

t_u8					U8_FromString_Dec(t_char const* str);
#define c_strdectou8	U8_FromString_Dec

t_u16					U16_FromString_Dec(t_char const* str);
#define c_strdectou16	U16_FromString_Dec

t_u32					U32_FromString_Dec(t_char const* str);
#define c_strdectou32	U32_FromString_Dec

t_u64					U64_FromString_Dec(t_char const* str);
#define c_strdectou64	U64_FromString_Dec
#if LIBCONFIG_USE_INT128
t_u128					U128_FromString_Dec(t_char const* str);
#define c_strdectou128	U128_FromString_Dec
#endif
//!@}

//!@doc Parse a signed integer from the given decimal number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be decimal number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					SInt_Parse_Dec	CONCAT(SINT_TYPE,_Parse_Dec)
#define c_sparsedec		SInt_Parse_Dec

t_size					S8_Parse_Dec	(t_s8	*dest, t_char const* str, t_size n);
#define c_s8parsedec	S8_Parse_Dec

t_size					S16_Parse_Dec	(t_s16	*dest, t_char const* str, t_size n);
#define c_s16parsedec	S16_Parse_Dec

t_size					S32_Parse_Dec	(t_s32	*dest, t_char const* str, t_size n);
#define c_s32parsedec	S32_Parse_Dec

t_size					S64_Parse_Dec	(t_s64	*dest, t_char const* str, t_size n);
#define c_s64parsedec	S64_Parse_Dec
#if LIBCONFIG_USE_INT128
t_size					S128_Parse_Dec	(t_s128	*dest, t_char const* str, t_size n);
#define c_s128parsedec	S128_Parse_Dec
#endif
//!@}

//!@doc Parse a signed integer from the given decimal number string
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/atoi}
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					SInt_FromString_Dec	CONCAT(SINT_TYPE,_FromString_Dec)
#define c_strdectos		SInt_FromString_Dec

t_s8					S8_FromString_Dec(t_char const* str);
#define c_strdectos8	S8_FromString_Dec

t_s16					S16_FromString_Dec(t_char const* str);
#define c_strdectos16	S16_FromString_Dec

t_s32					S32_FromString_Dec(t_char const* str);
#define c_strdectos32	S32_FromString_Dec

t_s64					S64_FromString_Dec(t_char const* str);
#define c_strdectos64	S64_FromString_Dec
#if LIBCONFIG_USE_INT128
t_s128					S128_FromString_Dec(t_char const* str);
#define c_strdectos128	S128_FromString_Dec
#endif
//!@}



// Hexadecimal parser functions



//!@doc Parse an unsigned integer from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 16) number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					UInt_Parse_Hex	CONCAT(UINT_TYPE,_Parse_Hex)
#define c_uparsehex		UInt_Parse_Hex

t_size					U8_Parse_Hex	(t_u8	*dest, t_char const* str, t_size n);
#define c_u8parsehex	U8_Parse_Hex

t_size					U16_Parse_Hex	(t_u16	*dest, t_char const* str, t_size n);
#define c_u16parsehex	U16_Parse_Hex

t_size					U32_Parse_Hex	(t_u32	*dest, t_char const* str, t_size n);
#define c_u32parsehex	U32_Parse_Hex

t_size					U64_Parse_Hex	(t_u64	*dest, t_char const* str, t_size n);
#define c_u64parsehex	U64_Parse_Hex
#if LIBCONFIG_USE_INT128
t_size					U128_Parse_Hex	(t_u128	*dest, t_char const* str, t_size n);
#define c_u128parsehex	U128_Parse_Hex
#endif
//!@}

//!@doc Parse an unsigned integer from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					UInt_FromString_Hex	CONCAT(UINT_TYPE,_FromString_Hex)
#define c_strhextou		UInt_FromString_Hex

t_u8					U8_FromString_Hex(t_char const* str);
#define c_strhextou8	U8_FromString_Hex

t_u16					U16_FromString_Hex(t_char const* str);
#define c_strhextou16	U16_FromString_Hex

t_u32					U32_FromString_Hex(t_char const* str);
#define c_strhextou32	U32_FromString_Hex

t_u64					U64_FromString_Hex(t_char const* str);
#define c_strhextou64	U64_FromString_Hex
#if LIBCONFIG_USE_INT128
t_u128					U128_FromString_Hex(t_char const* str);
#define c_strhextou128	U128_FromString_Hex
#endif
//!@}

//!@doc Parse a signed integer from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 16) number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					SInt_Parse_Hex	CONCAT(SINT_TYPE,_Parse_Hex)
#define c_sparsehex		SInt_Parse_Hex

t_size					S8_Parse_Hex	(t_s8	*dest, t_char const* str, t_size n);
#define c_s8parsehex	S8_Parse_Hex

t_size					S16_Parse_Hex	(t_s16	*dest, t_char const* str, t_size n);
#define c_s16parsehex	S16_Parse_Hex

t_size					S32_Parse_Hex	(t_s32	*dest, t_char const* str, t_size n);
#define c_s32parsehex	S32_Parse_Hex

t_size					S64_Parse_Hex	(t_s64	*dest, t_char const* str, t_size n);
#define c_s64parsehex	S64_Parse_Hex
#if LIBCONFIG_USE_INT128
t_size					S128_Parse_Hex	(t_s128	*dest, t_char const* str, t_size n);
#define c_s128parsehex	S128_Parse_Hex
#endif
//!@}

//!@doc Parse a signed integer from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					SInt_FromString_Hex	CONCAT(SINT_TYPE,_FromString_Hex)
#define c_strhextos		SInt_FromString_Hex

t_s8					S8_FromString_Hex(t_char const* str);
#define c_strhextos8	S8_FromString_Hex

t_s16					S16_FromString_Hex(t_char const* str);
#define c_strhextos16	S16_FromString_Hex

t_s32					S32_FromString_Hex(t_char const* str);
#define c_strhextos32	S32_FromString_Hex

t_s64					S64_FromString_Hex(t_char const* str);
#define c_strhextos64	S64_FromString_Hex
#if LIBCONFIG_USE_INT128
t_s128					S128_FromString_Hex(t_char const* str);
#define c_strhextos128	S128_FromString_Hex
#endif
//!@}



// Octal parser functions



//!@doc Parse an unsigned integer from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 8) number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					UInt_Parse_Oct	CONCAT(UINT_TYPE,_Parse_Oct)
#define c_uparseoct		UInt_Parse_Oct

t_size					U8_Parse_Oct	(t_u8	*dest, t_char const* str, t_size n);
#define c_u8parseoct	U8_Parse_Oct

t_size					U16_Parse_Oct	(t_u16	*dest, t_char const* str, t_size n);
#define c_u16parseoct	U16_Parse_Oct

t_size					U32_Parse_Oct	(t_u32	*dest, t_char const* str, t_size n);
#define c_u32parseoct	U32_Parse_Oct

t_size					U64_Parse_Oct	(t_u64	*dest, t_char const* str, t_size n);
#define c_u64parseoct	U64_Parse_Oct
#if LIBCONFIG_USE_INT128
t_size					U128_Parse_Oct	(t_u128	*dest, t_char const* str, t_size n);
#define c_u128parseoct	U128_Parse_Oct
#endif
//!@}

//!@doc Parse an unsigned integer from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					UInt_FromString_Oct	CONCAT(UINT_TYPE,_FromString_Oct)
#define c_strocttou		UInt_FromString_Oct

t_u8					U8_FromString_Oct(t_char const* str);
#define c_strocttou8	U8_FromString_Oct

t_u16					U16_FromString_Oct(t_char const* str);
#define c_strocttou16	U16_FromString_Oct

t_u32					U32_FromString_Oct(t_char const* str);
#define c_strocttou32	U32_FromString_Oct

t_u64					U64_FromString_Oct(t_char const* str);
#define c_strocttou64	U64_FromString_Oct
#if LIBCONFIG_USE_INT128
t_u128					U128_FromString_Oct(t_char const* str);
#define c_strocttou128	U128_FromString_Oct
#endif
//!@}

//!@doc Parse a signed integer from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 8) number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					SInt_Parse_Oct	CONCAT(SINT_TYPE,_Parse_Oct)
#define c_sparseoct		SInt_Parse_Oct

t_size					S8_Parse_Oct	(t_s8	*dest, t_char const* str, t_size n);
#define c_s8parseoct	S8_Parse_Oct

t_size					S16_Parse_Oct	(t_s16	*dest, t_char const* str, t_size n);
#define c_s16parseoct	S16_Parse_Oct

t_size					S32_Parse_Oct	(t_s32	*dest, t_char const* str, t_size n);
#define c_s32parseoct	S32_Parse_Oct

t_size					S64_Parse_Oct	(t_s64	*dest, t_char const* str, t_size n);
#define c_s64parseoct	S64_Parse_Oct
#if LIBCONFIG_USE_INT128
t_size					S128_Parse_Oct	(t_s128	*dest, t_char const* str, t_size n);
#define c_s128parseoct	S128_Parse_Oct
#endif
//!@}

//!@doc Parse a signed integer from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					SInt_FromString_Oct	CONCAT(SINT_TYPE,_FromString_Oct)
#define c_strocttos		SInt_FromString_Oct

t_s8					S8_FromString_Oct(t_char const* str);
#define c_strocttos8	S8_FromString_Oct

t_s16					S16_FromString_Oct(t_char const* str);
#define c_strocttos16	S16_FromString_Oct

t_s32					S32_FromString_Oct(t_char const* str);
#define c_strocttos32	S32_FromString_Oct

t_s64					S64_FromString_Oct(t_char const* str);
#define c_strocttos64	S64_FromString_Oct
#if LIBCONFIG_USE_INT128
t_s128					S128_FromString_Oct(t_char const* str);
#define c_strocttos128	S128_FromString_Oct
#endif
//!@}



// Binary parser functions



//!@doc Parse an unsigned integer from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 2) number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					UInt_Parse_Bin	CONCAT(UINT_TYPE,_Parse_Bin)
#define c_uparsebin		UInt_Parse_Bin

t_size					U8_Parse_Bin	(t_u8	*dest, t_char const* str, t_size n);
#define c_u8parsebin	U8_Parse_Bin

t_size					U16_Parse_Bin	(t_u16	*dest, t_char const* str, t_size n);
#define c_u16parsebin	U16_Parse_Bin

t_size					U32_Parse_Bin	(t_u32	*dest, t_char const* str, t_size n);
#define c_u32parsebin	U32_Parse_Bin

t_size					U64_Parse_Bin	(t_u64	*dest, t_char const* str, t_size n);
#define c_u64parsebin	U64_Parse_Bin
#if LIBCONFIG_USE_INT128
t_size					U128_Parse_Bin	(t_u128	*dest, t_char const* str, t_size n);
#define c_u128parsebin	U128_Parse_Bin
#endif
//!@}

//!@doc Parse an unsigned integer from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					UInt_FromString_Bin	CONCAT(UINT_TYPE,_FromString_Bin)
#define c_strbintou		UInt_FromString_Bin

t_u8					U8_FromString_Bin(t_char const* str);
#define c_strbintou8	U8_FromString_Bin

t_u16					U16_FromString_Bin(t_char const* str);
#define c_strbintou16	U16_FromString_Bin

t_u32					U32_FromString_Bin(t_char const* str);
#define c_strbintou32	U32_FromString_Bin

t_u64					U64_FromString_Bin(t_char const* str);
#define c_strbintou64	U64_FromString_Bin
#if LIBCONFIG_USE_INT128
t_u128					U128_FromString_Bin(t_char const* str);
#define c_strbintou128	U128_FromString_Bin
#endif
//!@}

//!@doc Parse a signed integer from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be base 2) number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					SInt_Parse_Bin	CONCAT(SINT_TYPE,_Parse_Bin)
#define c_sparsebin		SInt_Parse_Bin

t_size					S8_Parse_Bin	(t_s8	*dest, t_char const* str, t_size n);
#define c_s8parsebin	S8_Parse_Bin

t_size					S16_Parse_Bin	(t_s16	*dest, t_char const* str, t_size n);
#define c_s16parsebin	S16_Parse_Bin

t_size					S32_Parse_Bin	(t_s32	*dest, t_char const* str, t_size n);
#define c_s32parsebin	S32_Parse_Bin

t_size					S64_Parse_Bin	(t_s64	*dest, t_char const* str, t_size n);
#define c_s64parsebin	S64_Parse_Bin
#if LIBCONFIG_USE_INT128
t_size					S128_Parse_Bin	(t_s128	*dest, t_char const* str, t_size n);
#define c_s128parsebin	S128_Parse_Bin
#endif
//!@}

//!@doc Parse a signed integer from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	str		The numeric string to parse
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					SInt_FromString_Bin	CONCAT(SINT_TYPE,_FromString_Bin)
#define c_strbintos		SInt_FromString_Bin

t_s8					S8_FromString_Bin(t_char const* str);
#define c_strbintos8	S8_FromString_Bin

t_s16					S16_FromString_Bin(t_char const* str);
#define c_strbintos16	S16_FromString_Bin

t_s32					S32_FromString_Bin(t_char const* str);
#define c_strbintos32	S32_FromString_Bin

t_s64					S64_FromString_Bin(t_char const* str);
#define c_strbintos64	S64_FromString_Bin
#if LIBCONFIG_USE_INT128
t_s128					S128_FromString_Bin(t_char const* str);
#define c_strbintos128	S128_FromString_Bin
#endif
//!@}



// Custom-base parser functions



//!@doc Parse an unsigned integer from a custom-base number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be custom-base number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@param	base	The custom numeric base to interpret, the char index being the digit.
**					The base string must have at least 2 chars, no sign chars, no duplicate chars.
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					UInt_Parse_Base	CONCAT(UINT_TYPE,_Parse_Base)
#define c_uparsebase	UInt_Parse_Base

t_size					U8_Parse_Base	(t_u8	*dest, t_char const* str, t_char const* base, t_size n);
#define c_u8parsebase	U8_Parse_Base

t_size					U16_Parse_Base	(t_u16	*dest, t_char const* str, t_char const* base, t_size n);
#define c_u16parsebase	U16_Parse_Base

t_size					U32_Parse_Base	(t_u32	*dest, t_char const* str, t_char const* base, t_size n);
#define c_u32parsebase	U32_Parse_Base

t_size					U64_Parse_Base	(t_u64	*dest, t_char const* str, t_char const* base, t_size n);
#define c_u64parsebase	U64_Parse_Base
#if LIBCONFIG_USE_INT128
t_size					U128_Parse_Base	(t_u128	*dest, t_char const* str, t_char const* base, t_size n);
#define c_u128parsebase	U128_Parse_Base
#endif
//!@}

//!@doc Parse an unsigned integer from a custom-base number string
/*!
**	@nonstd, `strtoul()`
**
**	@param	str		The numeric string to parse
**	@param	base	The custom numeric base to interpret, the char index being the digit.
**					The base string must have at least 2 chars, no sign chars, no duplicate chars.
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					UInt_FromString_Base	CONCAT(UINT_TYPE,_FromString_Base)
#define c_strbasetou	UInt_FromString_Base

t_u8					U8_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetou8	U8_FromString_Base

t_u16					U16_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetou16	U16_FromString_Base

t_u32					U32_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetou32	U32_FromString_Base

t_u64					U64_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetou64	U64_FromString_Base
#if LIBCONFIG_USE_INT128
t_u128					U128_FromString_Base(t_char const* str, t_char const* base);
#define c_strbasetou128	U128_FromString_Base
#endif
//!@}

//!@doc Parse a signed integer from a custom-base number string
/*!
**	@nonstd
**
**	@param	dest	The resulting number, parse from the given `str`
**	@param	str		The numeric string to parse (must be custom-base number string)
**	@param	n		The maximum amount of character to parse (infinite if `0` is given)
**	@param	base	The custom numeric base to interpret, the char index being the digit.
**					The base string must have at least 2 chars, no sign chars, no duplicate chars.
**	@returns
**	The amount of characters parsed from the given `str`
*/
//!@{
#define					SInt_Parse_Base	CONCAT(SINT_TYPE,_Parse_Base)
#define c_sparsebase	SInt_Parse_Base

t_size					S8_Parse_Base	(t_s8	*dest, t_char const* str, t_char const* base, t_size n);
#define c_s8parsebase	S8_Parse_Base

t_size					S16_Parse_Base	(t_s16	*dest, t_char const* str, t_char const* base, t_size n);
#define c_s16parsebase	S16_Parse_Base

t_size					S32_Parse_Base	(t_s32	*dest, t_char const* str, t_char const* base, t_size n);
#define c_s32parsebase	S32_Parse_Base

t_size					S64_Parse_Base	(t_s64	*dest, t_char const* str, t_char const* base, t_size n);
#define c_s64parsebase	S64_Parse_Base
#if LIBCONFIG_USE_INT128
t_size					S128_Parse_Base	(t_s128	*dest, t_char const* str, t_char const* base, t_size n);
#define c_s128parsebase	S128_Parse_Base
#endif
//!@}

//!@doc Parse a signed integer from a custom-base number string
/*!
**	@nonstd, `strtol()`
**
**	@param	str		The numeric string to parse
**	@param	base	The custom numeric base to interpret, the char index being the digit.
**					The base string must have at least 2 chars, no sign chars, no duplicate chars.
**	@returns
**	The resulting number, parse from the given `str`
*/
//!@{
#define					SInt_FromString_Base	CONCAT(SINT_TYPE,_FromString_Base)
#define c_strbasetos	SInt_FromString_Base

t_s8					S8_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetos8	S8_FromString_Base

t_s16					S16_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetos16	S16_FromString_Base

t_s32					S32_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetos32	S32_FromString_Base

t_s64					S64_FromString_Base	(t_char const* str, t_char const* base);
#define c_strbasetos64	S64_FromString_Base
#if LIBCONFIG_USE_INT128
t_s128					S128_FromString_Base(t_char const* str, t_char const* base);
#define c_strbasetos128	S128_FromString_Base
#endif
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
