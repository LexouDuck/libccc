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
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stdint.h>
#else
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

//! Check if this environment supports 128-bit integer types
//!@{
#ifdef __SIZEOF_INT128__
	#ifndef __int128
	#define __int128	__int128
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
	typedef unsigned __int128	_UInt128;
	typedef signed   __int128	_SInt128;
	#pragma GCC diagnostic pop
	#endif
#endif
//!@}

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
typedef _UInt128	u128;
#endif
typedef STDINT(int,  8)	s8;
typedef STDINT(int, 16)	s16;
typedef STDINT(int, 32)	s32;
typedef	STDINT(int, 64)	s64;
#ifdef	__int128
typedef _SInt128	s128;
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

//! Primitive type: 8-bit unsigned integer
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
typedef u8		t_u8;
TYPEDEF_ALIAS(	t_u8,	UINT_8,  PRIMITIVE)

//! Primitive type: 16-bit unsigned integer
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
typedef u16		t_u16;
TYPEDEF_ALIAS(	t_u16,	UINT_16, PRIMITIVE)

//! Primitive type: 32-bit unsigned integer
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
typedef u32		t_u32;
TYPEDEF_ALIAS(	t_u32,	UINT_32, PRIMITIVE)

//! Primitive type: 64-bit unsigned integer
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
typedef	u64		t_u64;
TYPEDEF_ALIAS(	t_u64,	UINT_64, PRIMITIVE)

#ifdef	__int128
//! Primitive type: 128-bit unsigned integer (only available on certain platforms)
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
typedef u128	t_u128;
TYPEDEF_ALIAS(	t_u128,	UINT_128,PRIMITIVE)
#elif (LIBCONFIG_BITS_UINT == 128)
	#error "Cannot set default unsigned int type to 128-bit, unavailable on this platform"
#endif



//! Primitive type: 8-bit signed integer
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
typedef s8		t_s8;
TYPEDEF_ALIAS(	t_s8,	SINT_8,  PRIMITIVE)

//! Primitive type: 16-bit signed integer
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
typedef s16		t_s16;
TYPEDEF_ALIAS(	t_s16,	SINT_16, PRIMITIVE)

//! Primitive type: 32-bit signed integer
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
typedef s32		t_s32;
TYPEDEF_ALIAS(	t_s32,	SINT_32, PRIMITIVE)

//! Primitive type: 64-bit signed integer
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
typedef	s64		t_s64;
TYPEDEF_ALIAS(	t_s64,	SINT_64, PRIMITIVE)

#ifdef	__int128
//! Primitive type: 128-bit signed integer (only available on certain platforms)
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
typedef s128	t_s128;
TYPEDEF_ALIAS(	t_s128,	SINT_128,PRIMITIVE)
#elif (LIBCONFIG_BITS_SINT == 128)
	#error "Cannot set default signed int type to 128-bit, unavailable on this platform"
#endif



//! The actual underlying type for the `t_uint` configurable type
#define UINT_T		CONCAT(t_u,LIBCONFIG_BITS_UINT)
//! The actual underlying type for the `t_uint` configurable type, in uppercase
#define UINT_TYPE	CONCAT(U,LIBCONFIG_BITS_UINT)

//! The configurable-size unsigned integer primitive type.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**
**	Configurable-width unsigned integer type.
**	The size of this integer type depends on the value of #LIBCONFIG_BITS_UINT.
**	This is meant to be used as a "default integer type", a type where the
**	programmer doesn't need to worry about integer overflow behaviors being
**	platform-dependent (like they would if they used the C native `int` type).
**	This type can express a number between `0` and #UINT_MAX
*/
typedef UINT_T	t_uint;
TYPEDEF_ALIAS(t_uint, UINT, PRIMITIVE)



//! The actual underlying type for the `t_sint` configurable type
#define SINT_T		CONCAT(t_s,LIBCONFIG_BITS_SINT)
//! The actual underlying type for the `t_sint` configurable type, in uppercase
#define SINT_TYPE	CONCAT(S,LIBCONFIG_BITS_SINT)

//! The configurable-size signed integer primitive type.
/*!
**	@isostd{C,https://en.cppreference.com/w/c/language/arithmetic_types#Integer_types}
**
**	Configurable-width signed integer type.
**	The size of this integer type depends on the value of #LIBCONFIG_BITS_SINT.
**	This is meant to be used as a "default integer type", a type where the
**	programmer doesn't need to worry about integer overflow behaviors being
**	platform-dependent (like they would if they used the C native `int` type).
**	This type can express a number between #SINT_MIN and #SINT_MAX.
*/
typedef SINT_T	t_sint;
TYPEDEF_ALIAS(t_sint, SINT, PRIMITIVE)



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

	#define U8_MAX ((t_u8)0xFF)					//!< The largest possible value for any 8-bit unsigned integer	(255)
	#define S8_MAX ((t_s8)0x7F)					//!< The largest possible value for any 8-bit signed integer	(+127)
	#define S8_MIN ((t_s8)0x80)					//!< The minimum possible value for any 8-bit signed integer	(-128)

	#define U16_MAX ((t_u16)0xFFFF)				//!< The largest possible value for any 16-bit unsigned integer	(65535)
	#define S16_MAX ((t_s16)0x7FFF)				//!< The largest possible value for any 16-bit signed integer	(+32767)
	#define S16_MIN ((t_s16)0x8000)				//!< The minimum possible value for any 16-bit signed integer	(-32768)

	#define U32_MAX ((t_u32)0xFFFFFFFF)			//!< The largest possible value for any 32-bit unsigned integer	(4294967295)
	#define S32_MAX ((t_s32)0x7FFFFFFF)			//!< The largest possible value for any 32-bit signed integer	(+2147483647)
	#define S32_MIN ((t_s32)0x80000000)			//!< The minimum possible value for any 32-bit signed integer	(-2147483648)

	#define U64_MAX ((t_u64)0xFFFFFFFFFFFFFFFF)	//!< The largest possible value for any 64-bit unsigned integer	(18446744073709551615)
	#define S64_MAX ((t_s64)0x7FFFFFFFFFFFFFFF)	//!< The largest possible value for any 64-bit signed integer	(+9223372036854775807)
	#define S64_MIN ((t_s64)0x8000000000000000)	//!< The minimum possible value for any 64-bit signed integer	(-9223372036854775807)

	#ifdef __int128
	#define U128_MAX (t_u128)(((t_u128)0xFFFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF) //!< The largest possible value for a 128-bit unsigned integer	(340282366920938463463374607431768211455llu)
	#define S128_MAX (t_s128)(((t_s128)0x7FFFFFFFFFFFFFFF << 64) | 0xFFFFFFFFFFFFFFFF)  //!< The largest possible value for a 128-bit signed integer	(+170141183460469231731687303715884105727ll)
	#define S128_MIN (t_s128)(((t_s128)0x8000000000000000 << 64) | 0x0000000000000000)  //!< The minimum possible value for a 128-bit signed integer	(−170141183460469231731687303715884105728ll)
	#endif

#else

	#define U8_MAX	((t_u8)-1)						//!< The largest possible value for at least size  8-bit, unsigned integer type
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

	#ifdef __int128
	#define U128_MAX ((t_u128)-1)					//!< The largest possible value for at least size 128-bit, unsigned integer type
	#define S128_MAX ((t_s128)(U128_MAX >> 1))		//!< The largest possible value for at least size 128-bit, signed integer type
	#define S128_MIN ((t_s128)((U128_MAX >> 1) + 1))//!< The minimum possible value for at least size 128-bit, signed integer type
	#endif
#endif



#undef	UINT_MAX
#define UINT_MAX	((t_uint)-1)					//!< The largest possible value for a configurable-size unsigned integer type
#define SINT_MAX	((t_sint)(UINT_MAX >> 1))		//!< The largest possible value for a configurable-size signed integer type
#define SINT_MIN	((t_sint)((UINT_MAX >> 1) + 1))	//!< The minimum possible value for a configurable-size signed integer type



#endif
#ifndef __LIBCCC_INT_F
#define __LIBCCC_INT_F

/*
** ************************************************************************** *|
**                           Integer number functions                         *|
** ************************************************************************** *|
*/

//! A smart constructor: calls the appropriate `Fixed_From*()` function from the given argument type
//!@{
#define DEFINEFUNC_Int(X, FUNCTYPE) \
	_Generic((X),	\
		t_s16:	 FUNCTYPE##_FromInt,	\
		t_s32:	 FUNCTYPE##_FromInt,	\
		t_s64:	 FUNCTYPE##_FromInt,	\
		t_s128:	 FUNCTYPE##_FromInt,	\
		t_sint:  FUNCTYPE##_FromInt,	\
		t_q16:	 FUNCTYPE##_FromFixed,	\
		t_q32:	 FUNCTYPE##_FromFixed,	\
		t_q64:	 FUNCTYPE##_FromFixed,	\
		t_q128:	 FUNCTYPE##_FromFixed,	\
		t_fixed: FUNCTYPE##_FromFixed,	\
		t_f32:	 FUNCTYPE##_FromFloat,	\
		t_f64:	 FUNCTYPE##_FromFloat,	\
		t_f80:	 FUNCTYPE##_FromFloat,	\
		t_f128:	 FUNCTYPE##_FromFloat,	\
		t_float: FUNCTYPE##_FromFloat,	\
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



// TODO Int_FromInt()
// TODO Int_FromFixed()
// TODO Int_FromFloat()



/*
** ************************************************************************** *|
**                        Integer-to-String Conversions                       *|
** ************************************************************************** *|
*/

// TODO Int_ToString() generic function

//! Get the string decimal (base 10) representation of an unsigned integer
/*!
**	@nonstd, `utoa()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString	CONCAT(UINT_TYPE,_ToString)
_MALLOC()	t_char*		U8_ToString(t_u8 number);
_MALLOC()	t_char*		U16_ToString(t_u16 number);
_MALLOC()	t_char*		U32_ToString(t_u32 number);
_MALLOC()	t_char*		U64_ToString(t_u64 number);
#ifdef __int128
_MALLOC()	t_char*		U128_ToString(t_u128 number); // TODO implement
#endif
#define c_utostr		UInt_ToString	//!< @alias{UInt_ToString}
#define c_u8tostr		U8_ToString 	//!< @alias{U8_ToString}
#define c_u16tostr		U16_ToString 	//!< @alias{U16_ToString}
#define c_u32tostr		U32_ToString 	//!< @alias{U32_ToString}
#define c_u64tostr		U64_ToString 	//!< @alias{U64_ToString}
#define c_u128tostr		U128_ToString 	//!< @alias{U128_ToString}
//!@}

//! Get the string decimal (base 10) representation of a signed integer
/*!
**	@nonstd, `itoa()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString	CONCAT(SINT_TYPE,_ToString)
_MALLOC()	t_char*		S8_ToString(t_s8 number);
_MALLOC()	t_char*		S16_ToString(t_s16 number);
_MALLOC()	t_char*		S32_ToString(t_s32 number);
_MALLOC()	t_char*		S64_ToString(t_s64 number);
#ifdef __int128
_MALLOC()	t_char*		S128_ToString(t_s128 number); // TODO implement
#endif
#define c_stostr		SInt_ToString	//!< @alias{SInt_ToString}
#define c_s8tostr		S8_ToString 	//!< @alias{S8_ToString}
#define c_s16tostr		S16_ToString 	//!< @alias{S16_ToString}
#define c_s32tostr		S32_ToString 	//!< @alias{S32_ToString}
#define c_s64tostr		S64_ToString 	//!< @alias{S64_ToString}
#define c_s128tostr		S128_ToString 	//!< @alias{S128_ToString}
//!@}



// TODO Int_ToString_Dec() function aliases ?



//! Get the string hexadecimal (base 16) representation of an unsigned integer
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
_MALLOC()	t_char*		U8_ToString_Hex(t_u8 number, t_bool prefix);
_MALLOC()	t_char*		U16_ToString_Hex(t_u16 number, t_bool prefix);
_MALLOC()	t_char*		U32_ToString_Hex(t_u32 number, t_bool prefix);
_MALLOC()	t_char*		U64_ToString_Hex(t_u64 number, t_bool prefix);
#ifdef __int128
_MALLOC()	t_char*		U128_ToString_Hex(t_u128 number, t_bool prefix); // TODO implement
#endif
#define c_utostrhex		UInt_ToString_Hex	//!< @alias{UInt_ToString_Hex}
#define c_u8tostrhex	U8_ToString_Hex 	//!< @alias{U8_ToString_Hex}
#define c_u16tostrhex	U16_ToString_Hex 	//!< @alias{U16_ToString_Hex}
#define c_u32tostrhex	U32_ToString_Hex 	//!< @alias{U32_ToString_Hex}
#define c_u64tostrhex	U64_ToString_Hex 	//!< @alias{U64_ToString_Hex}
#define c_u128tostrhex	U128_ToString_Hex 	//!< @alias{U128_ToString_Hex}
//!@}

//! Get the string hexadecimal (base 16) representation of a signed integer
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
_MALLOC()	t_char*		S8_ToString_Hex(t_s8 number, t_bool prefix);
_MALLOC()	t_char*		S16_ToString_Hex(t_s16 number, t_bool prefix);
_MALLOC()	t_char*		S32_ToString_Hex(t_s32 number, t_bool prefix);
_MALLOC()	t_char*		S64_ToString_Hex(t_s64 number, t_bool prefix);
#ifdef __int128
_MALLOC()	t_char*		S128_ToString_Hex(t_s128 number, t_bool prefix); // TODO implement
#endif
#define c_stostrhex		SInt_ToString_Hex	//!< @alias{SInt_ToString_Hex}
#define c_s8tostrhex	S8_ToString_Hex 	//!< @alias{S8_ToString_Hex}
#define c_s16tostrhex	S16_ToString_Hex 	//!< @alias{S16_ToString_Hex}
#define c_s32tostrhex	S32_ToString_Hex 	//!< @alias{S32_ToString_Hex}
#define c_s64tostrhex	S64_ToString_Hex 	//!< @alias{S64_ToString_Hex}
#define c_s128tostrhex	S128_ToString_Hex 	//!< @alias{S128_ToString_Hex}
//!@}



//! Get the string octal (base 8) representation of an unsigned integer
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
_MALLOC()	t_char*		U8_ToString_Oct(t_u8 number, t_bool prefix);
_MALLOC()	t_char*		U16_ToString_Oct(t_u16 number, t_bool prefix);
_MALLOC()	t_char*		U32_ToString_Oct(t_u32 number, t_bool prefix);
_MALLOC()	t_char*		U64_ToString_Oct(t_u64 number, t_bool prefix);
#ifdef __int128
_MALLOC()	t_char*		U128_ToString_Oct(t_u128 number, t_bool prefix); // TODO implement
#endif
#define c_utostroct		UInt_ToString_Oct	//!< @alias{UInt_ToString_Oct}
#define c_u8tostroct	U8_ToString_Oct 	//!< @alias{U8_ToString_Oct}
#define c_u16tostroct	U16_ToString_Oct 	//!< @alias{U16_ToString_Oct}
#define c_u32tostroct	U32_ToString_Oct 	//!< @alias{U32_ToString_Oct}
#define c_u64tostroct	U64_ToString_Oct 	//!< @alias{U64_ToString_Oct}
#define c_u128tostroct	U128_ToString_Oct 	//!< @alias{U128_ToString_Oct}
//!@}

//! Get the string octal (base 8) representation of a signed integer
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
_MALLOC()	t_char*		S8_ToString_Oct(t_s8 number, t_bool prefix);
_MALLOC()	t_char*		S16_ToString_Oct(t_s16 number, t_bool prefix);
_MALLOC()	t_char*		S32_ToString_Oct(t_s32 number, t_bool prefix);
_MALLOC()	t_char*		S64_ToString_Oct(t_s64 number, t_bool prefix);
#ifdef __int128
_MALLOC()	t_char*		S128_ToString_Oct(t_s128 number, t_bool prefix); // TODO implement
#endif
#define c_stostroct		SInt_ToString_Oct	//!< @alias{SInt_ToString_Oct}
#define c_s8tostroct	S8_ToString_Oct 	//!< @alias{S8_ToString_Oct}
#define c_s16tostroct	S16_ToString_Oct 	//!< @alias{S16_ToString_Oct}
#define c_s32tostroct	S32_ToString_Oct 	//!< @alias{S32_ToString_Oct}
#define c_s64tostroct	S64_ToString_Oct 	//!< @alias{S64_ToString_Oct}
#define c_s128tostroct	S128_ToString_Oct 	//!< @alias{S128_ToString_Oct}
//!@}



//! Get the string binary (base 2) representation of an unsigned integer
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
_MALLOC()	t_char*		U8_ToString_Bin(t_u8 number, t_bool prefix);
_MALLOC()	t_char*		U16_ToString_Bin(t_u16 number, t_bool prefix);
_MALLOC()	t_char*		U32_ToString_Bin(t_u32 number, t_bool prefix);
_MALLOC()	t_char*		U64_ToString_Bin(t_u64 number, t_bool prefix);
#ifdef __int128
_MALLOC()	t_char*		U128_ToString_Bin(t_u128 number, t_bool prefix); // TODO implement
#endif
#define c_utostrbin		UInt_ToString_Bin	//!< @alias{UInt_ToString_Bin}
#define c_u8tostrbin	U8_ToString_Bin 	//!< @alias{U8_ToString_Bin}
#define c_u16tostrbin	U16_ToString_Bin 	//!< @alias{U16_ToString_Bin}
#define c_u32tostrbin	U32_ToString_Bin 	//!< @alias{U32_ToString_Bin}
#define c_u64tostrbin	U64_ToString_Bin 	//!< @alias{U64_ToString_Bin}
#define c_u128tostrbin	U128_ToString_Bin 	//!< @alias{U128_ToString_Bin}
//!@}

//! Get the string binary (base 2) representation of a signed integer
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
_MALLOC()	t_char*		S8_ToString_Bin(t_s8 number, t_bool prefix);
_MALLOC()	t_char*		S16_ToString_Bin(t_s16 number, t_bool prefix);
_MALLOC()	t_char*		S32_ToString_Bin(t_s32 number, t_bool prefix);
_MALLOC()	t_char*		S64_ToString_Bin(t_s64 number, t_bool prefix);
#ifdef __int128
_MALLOC()	t_char*		S128_ToString_Bin(t_s128 number, t_bool prefix); // TODO implement
#endif
#define c_stostrbin		SInt_ToString_Bin	//!< @alias{SInt_ToString_Bin}
#define c_s8tostrbin	S8_ToString_Bin 	//!< @alias{S8_ToString_Bin}
#define c_s16tostrbin	S16_ToString_Bin 	//!< @alias{S16_ToString_Bin}
#define c_s32tostrbin	S32_ToString_Bin 	//!< @alias{S32_ToString_Bin}
#define c_s64tostrbin	S64_ToString_Bin 	//!< @alias{S64_ToString_Bin}
#define c_s128tostrbin	S128_ToString_Bin 	//!< @alias{S128_ToString_Bin}
//!@}



//! Get the string custom-base representation of an unsigned integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_ToString_Base	CONCAT(UINT_TYPE,_ToString_Base)
_MALLOC()	t_char*		U8_ToString_Base(t_u8 number, t_char const* base);
_MALLOC()	t_char*		U16_ToString_Base(t_u16 number, t_char const* base);
_MALLOC()	t_char*		U32_ToString_Base(t_u32 number, t_char const* base);
_MALLOC()	t_char*		U64_ToString_Base(t_u64 number, t_char const* base);
#ifdef __int128
_MALLOC()	t_char*		U128_ToString_Base(t_u128 number, t_char const* base); // TODO implement
#endif
#define c_utostrbase	UInt_ToString_Base	//!< @alias{UInt_ToString_Base}
#define c_u8tostrbase	U8_ToString_Base 	//!< @alias{U8_ToString_Base}
#define c_u16tostrbase	U16_ToString_Base 	//!< @alias{U16_ToString_Base}
#define c_u32tostrbase	U32_ToString_Base 	//!< @alias{U32_ToString_Base}
#define c_u64tostrbase	U64_ToString_Base 	//!< @alias{U64_ToString_Base}
#define c_u128tostrbase	U128_ToString_Base 	//!< @alias{U128_ToString_Base}
//!@}

//! Get the string custom-base representation of a signed integer
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_ToString_Base	CONCAT(SINT_TYPE,_ToString_Base)
_MALLOC()	t_char*		S8_ToString_Base(t_s8 number, t_char const* base);
_MALLOC()	t_char*		S16_ToString_Base(t_s16 number, t_char const* base);
_MALLOC()	t_char*		S32_ToString_Base(t_s32 number, t_char const* base);
_MALLOC()	t_char*		S64_ToString_Base(t_s64 number, t_char const* base);
#ifdef __int128
_MALLOC()	t_char*		S128_ToString_Base(t_s128 number, t_char const* base); // TODO implement
#endif
#define c_stostrbase	SInt_ToString_Base	//!< @alias{SInt_ToString_Base}
#define c_s8tostrbase	S8_ToString_Base	//!< @alias{S8_ToString_Base}
#define c_s16tostrbase	S16_ToString_Base	//!< @alias{S16_ToString_Base}
#define c_s32tostrbase	S32_ToString_Base	//!< @alias{S32_ToString_Base}
#define c_s64tostrbase	S64_ToString_Base	//!< @alias{S64_ToString_Base}
#define c_s128tostrbase	S128_ToString_Base 	//!< @alias{S128_ToString_Base}
//!@}



/*
** ************************************************************************** *|
**                          String-to-int Conversions                         *|
** ************************************************************************** *|
*/

//! Parse an unsigned integer from the given number string `str`
/*!
**	@nonstd, `atou()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_FromString	CONCAT(UINT_TYPE,_FromString)
t_u8					U8_FromString(t_char const* str);
t_u16					U16_FromString(t_char const* str);
t_u32					U32_FromString(t_char const* str);
t_u64					U64_FromString(t_char const* str);
#ifdef __int128
t_u128					U128_FromString(t_char const* str);
#endif
#define c_strtou		UInt_FromString	//!< @alias{UInt_FromString}
#define c_strtou8		U8_FromString	//!< @alias{U8_FromString}
#define c_strtou16		U16_FromString	//!< @alias{U16_FromString}
#define c_strtou32		U32_FromString	//!< @alias{U32_FromString}
#define c_strtou64		U64_FromString	//!< @alias{U64_FromString}
#define c_strtou128		U128_FromString	//!< @alias{U128_FromString}
//!@}

//! Parse a signed integer from the given number string `str`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/atoi}
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_FromString	CONCAT(SINT_TYPE,_FromString)
t_s8					S8_FromString(t_char const* str);
t_s16					S16_FromString(t_char const* str);
t_s32					S32_FromString(t_char const* str);
t_s64					S64_FromString(t_char const* str);
#ifdef __int128
t_s128					S128_FromString(t_char const* str);
#endif
#define c_strtos		SInt_FromString	//!< @alias{SInt_FromString}
#define c_strtos8		S8_FromString	//!< @alias{S8_FromString}
#define c_strtos16		S16_FromString	//!< @alias{S16_FromString}
#define c_strtos32		S32_FromString	//!< @alias{S32_FromString}
#define c_strtos64		S64_FromString	//!< @alias{S64_FromString}
#define c_strtos128		S128_FromString	//!< @alias{S128_FromString}
//!@}



//! Parse an unsigned integer from the given decimal number string
/*!
**	@nonstd, `atou()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_FromString_Dec	CONCAT(UINT_TYPE,_FromString_Dec)
t_u8					U8_FromString_Dec(t_char const* str);
t_u16					U16_FromString_Dec(t_char const* str);
t_u32					U32_FromString_Dec(t_char const* str);
t_u64					U64_FromString_Dec(t_char const* str);
#ifdef __int128
t_u128					U128_FromString_Dec(t_char const* str);
#endif
#define c_strdectou		UInt_FromString_Dec	//!< @alias{UInt_FromString_Dec}
#define c_strdectou8	U8_FromString_Dec	//!< @alias{U8_FromString_Dec}
#define c_strdectou16	U16_FromString_Dec	//!< @alias{U16_FromString_Dec}
#define c_strdectou32	U32_FromString_Dec	//!< @alias{U32_FromString_Dec}
#define c_strdectou64	U64_FromString_Dec	//!< @alias{U64_FromString_Dec}
#define c_strdectou128	U128_FromString_Dec	//!< @alias{U128_FromString_Dec}
//!@}

//! Parse a signed integer from the given decimal number string
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/atoi}
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_FromString_Dec	CONCAT(SINT_TYPE,_FromString_Dec)
t_s8					S8_FromString_Dec(t_char const* str);
t_s16					S16_FromString_Dec(t_char const* str);
t_s32					S32_FromString_Dec(t_char const* str);
t_s64					S64_FromString_Dec(t_char const* str);
#ifdef __int128
t_s128					S128_FromString_Dec(t_char const* str);
#endif
#define c_strdectos		SInt_FromString_Dec	//!< @alias{SInt_FromString_Dec}
#define c_strdectos8	S8_FromString_Dec	//!< @alias{S8_FromString_Dec}
#define c_strdectos16	S16_FromString_Dec	//!< @alias{S16_FromString_Dec}
#define c_strdectos32	S32_FromString_Dec	//!< @alias{S32_FromString_Dec}
#define c_strdectos64	S64_FromString_Dec	//!< @alias{S64_FromString_Dec}
#define c_strdectos128	S128_FromString_Dec	//!< @alias{S128_FromString_Dec}
//!@}



//! Parse an unsigned integer from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_FromString_Hex	CONCAT(UINT_TYPE,_FromString_Hex)
t_u8					U8_FromString_Hex(t_char const* str);
t_u16					U16_FromString_Hex(t_char const* str);
t_u32					U32_FromString_Hex(t_char const* str);
t_u64					U64_FromString_Hex(t_char const* str);
#ifdef __int128
t_u128					U128_FromString_Hex(t_char const* str);
#endif
#define c_strhextou		UInt_FromString_Hex	//!< @alias{UInt_FromString_Hex}
#define c_strhextou8	U8_FromString_Hex	//!< @alias{U8_FromString_Hex}
#define c_strhextou16	U16_FromString_Hex	//!< @alias{U16_FromString_Hex}
#define c_strhextou32	U32_FromString_Hex	//!< @alias{U32_FromString_Hex}
#define c_strhextou64	U64_FromString_Hex	//!< @alias{U64_FromString_Hex}
#define c_strhextou128	U128_FromString_Hex	//!< @alias{U128_FromString_Hex}
//!@}

//! Parse a signed integer from the given hexadecimal (base 16) number string
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_FromString_Hex	CONCAT(SINT_TYPE,_FromString_Hex)
t_s8					S8_FromString_Hex(t_char const* str);
t_s16					S16_FromString_Hex(t_char const* str);
t_s32					S32_FromString_Hex(t_char const* str);
t_s64					S64_FromString_Hex(t_char const* str);
#ifdef __int128
t_s128					S128_FromString_Hex(t_char const* str);
#endif
#define c_strhextos		SInt_FromString_Hex	//!< @alias{SInt_FromString_Hex}
#define c_strhextos8	S8_FromString_Hex	//!< @alias{S8_FromString_Hex}
#define c_strhextos16	S16_FromString_Hex	//!< @alias{S16_FromString_Hex}
#define c_strhextos32	S32_FromString_Hex	//!< @alias{S32_FromString_Hex}
#define c_strhextos64	S64_FromString_Hex	//!< @alias{S64_FromString_Hex}
#define c_strhextos128	S128_FromString_Hex	//!< @alias{S128_FromString_Hex}
//!@}



//! Parse an unsigned integer from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_FromString_Oct	CONCAT(UINT_TYPE,_FromString_Oct)
t_u8					U8_FromString_Oct(t_char const* str);
t_u16					U16_FromString_Oct(t_char const* str);
t_u32					U32_FromString_Oct(t_char const* str);
t_u64					U64_FromString_Oct(t_char const* str);
#ifdef __int128
t_u128					U128_FromString_Oct(t_char const* str);
#endif
#define c_strocttou		UInt_FromString_Oct	//!< @alias{UInt_FromString_Oct}
#define c_strocttou8	U8_FromString_Oct	//!< @alias{U8_FromString_Oct}
#define c_strocttou16	U16_FromString_Oct	//!< @alias{U16_FromString_Oct}
#define c_strocttou32	U32_FromString_Oct	//!< @alias{U32_FromString_Oct}
#define c_strocttou64	U64_FromString_Oct	//!< @alias{U64_FromString_Oct}
#define c_strocttou128	U128_FromString_Oct	//!< @alias{U128_FromString_Oct}
//!@}

//! Parse a signed integer from the given octal (base 8) number string
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_FromString_Oct	CONCAT(SINT_TYPE,_FromString_Oct)
t_s8					S8_FromString_Oct(t_char const* str);
t_s16					S16_FromString_Oct(t_char const* str);
t_s32					S32_FromString_Oct(t_char const* str);
t_s64					S64_FromString_Oct(t_char const* str);
#ifdef __int128
t_s128					S128_FromString_Oct(t_char const* str);
#endif
#define c_strocttos		SInt_FromString_Oct	//!< @alias{SInt_FromString_Oct}
#define c_strocttos8	S8_FromString_Oct	//!< @alias{S8_FromString_Oct}
#define c_strocttos16	S16_FromString_Oct	//!< @alias{S16_FromString_Oct}
#define c_strocttos32	S32_FromString_Oct	//!< @alias{S32_FromString_Oct}
#define c_strocttos64	S64_FromString_Oct	//!< @alias{S64_FromString_Oct}
#define c_strocttos128	S128_FromString_Oct	//!< @alias{S128_FromString_Oct}
//!@}



//! Parse an unsigned integer from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_FromString_Bin	CONCAT(UINT_TYPE,_FromString_Bin)
t_u8					U8_FromString_Bin(t_char const* str);
t_u16					U16_FromString_Bin(t_char const* str);
t_u32					U32_FromString_Bin(t_char const* str);
t_u64					U64_FromString_Bin(t_char const* str);
#ifdef __int128
t_u128					U128_FromString_Bin(t_char const* str);
#endif
#define c_strbintou		UInt_FromString_Bin	//!< @alias{UInt_FromString_Bin}
#define c_strbintou8	U8_FromString_Bin	//!< @alias{U8_FromString_Bin}
#define c_strbintou16	U16_FromString_Bin	//!< @alias{U16_FromString_Bin}
#define c_strbintou32	U32_FromString_Bin	//!< @alias{U32_FromString_Bin}
#define c_strbintou64	U64_FromString_Bin	//!< @alias{U64_FromString_Bin}
#define c_strbintou128	U128_FromString_Bin	//!< @alias{U128_FromString_Bin}
//!@}

//! Parse a signed integer from the given binary (base 2) number string
/*!
**	@nonstd
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_FromString_Bin	CONCAT(SINT_TYPE,_FromString_Bin)
t_s8					S8_FromString_Bin(t_char const* str);
t_s16					S16_FromString_Bin(t_char const* str);
t_s32					S32_FromString_Bin(t_char const* str);
t_s64					S64_FromString_Bin(t_char const* str);
#ifdef __int128
t_s128					S128_FromString_Bin(t_char const* str);
#endif
#define c_strbintos		SInt_FromString_Bin	//!< @alias{SInt_FromString_Bin}
#define c_strbintos8	S8_FromString_Bin	//!< @alias{S8_FromString_Bin}
#define c_strbintos16	S16_FromString_Bin	//!< @alias{S16_FromString_Bin}
#define c_strbintos32	S32_FromString_Bin	//!< @alias{S32_FromString_Bin}
#define c_strbintos64	S64_FromString_Bin	//!< @alias{S64_FromString_Bin}
#define c_strbintos128	S128_FromString_Bin	//!< @alias{S128_FromString_Bin}
//!@}



//! Parse an unsigned integer from a custom-base number string
/*!
**	@nonstd, `strtoul()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					UInt_FromString_Base	CONCAT(UINT_TYPE,_FromString_Base)
t_u8					U8_FromString_Base(t_char const* str, t_char const* base);
t_u16					U16_FromString_Base(t_char const* str, t_char const* base);
t_u32					U32_FromString_Base(t_char const* str, t_char const* base);
t_u64					U64_FromString_Base(t_char const* str, t_char const* base);
#ifdef __int128
t_u128					U128_FromString_Base(t_char const* str, t_char const* base);
#endif
#define c_strbasetou	UInt_FromString_Base//!< @alias{UInt_FromString_Base}
#define c_strbasetou8	U8_FromString_Base	//!< @alias{U8_FromString_Base}
#define c_strbasetou16	U16_FromString_Base	//!< @alias{U16_FromString_Base}
#define c_strbasetou32	U32_FromString_Base	//!< @alias{U32_FromString_Base}
#define c_strbasetou64	U64_FromString_Base	//!< @alias{U64_FromString_Base}
#define c_strbasetou128	U128_FromString_Base//!< @alias{U128_FromString_Base}
//!@}

//! Parse a signed integer from a custom-base number string
/*!
**	@nonstd, `strtol()`
**
**	@param	number	The number to convert to string
**	@returns
**	A newly allocated string, converted from the given `number`
*/
//!@{
#define					SInt_FromString_Base	CONCAT(SINT_TYPE,_FromString_Base)
t_s8					S8_FromString_Base(t_char const* str, t_char const* base);
t_s16					S16_FromString_Base(t_char const* str, t_char const* base);
t_s32					S32_FromString_Base(t_char const* str, t_char const* base);
t_s64					S64_FromString_Base(t_char const* str, t_char const* base);
#ifdef __int128
t_s128					S128_FromString_Base(t_char const* str, t_char const* base);
#endif
#define c_strbasetos	SInt_FromString_Base//!< @alias{SInt_FromString_Base}
#define c_strbasetos8	S8_FromString_Base	//!< @alias{S8_FromString_Base}
#define c_strbasetos16	S16_FromString_Base	//!< @alias{S16_FromString_Base}
#define c_strbasetos32	S32_FromString_Base	//!< @alias{S32_FromString_Base}
#define c_strbasetos64	S64_FromString_Base	//!< @alias{S64_FromString_Base}
#define c_strbasetos128	S128_FromString_Base//!< @alias{S128_FromString_Base}
//!@}



#endif

/*! @} */
HEADER_END
#endif
