/*============================================================================*/
/*                                            ______________________________  */
/*  libccc.h                                 |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_H
#define __LIBCCC_H
/*! @file libccc.h
**	This header defines all the primitive types and common macros to use.
**	@addtogroup libccc
**	@{
*/

// define 'extern C' header guards to prevent C++ compilers from doing symbol name mangling
#ifdef __cplusplus
	#ifndef HEADER_CPP
	#define HEADER_CPP	extern "C" {
	#endif
	#ifndef HEADER_END
	#define HEADER_END	}
	#endif
#else
	#ifndef HEADER_CPP
	#define HEADER_CPP	
	#endif
	#ifndef HEADER_END
	#define HEADER_END	
	#endif	
#endif

HEADER_CPP

/*
**	TODO reorganize the ./hdr/ header folder to have subfolders and better organized/more split-up files
**	TODO add a 't_char' and 't_utf8' type for strings
**	TODO add 's_tensor' type to algebra
**
**	incomplete:
**	TODO	libccc_list        + tests
**	TODO	libccc_stat        + tests
**	TODO	libccc_color       + tests
**	TODO	libccc_random      + tests
**	TODO	libccc_stringarray + tests
**	TODO	libccc_io          + tests
**	TODO	libccc_algebra     + tests
**	TODO	libccc_complex     + tests
**	TODO	libccc_time        + tests // system clock time functions
**	non-existent:
**	TODO	libccc_thread      + tests // POSIX-style pthread cross-platform interface
**	TODO	libccc_socket      + tests // network socket functions - send(), recv(), etc
**	TODO	libccc_network     + tests // utility functions for common network protocols: TCP/IP, UDP (maybe DELTA-T?)
**	TODO	libccc_object      + tests // extensible objects (json library)
**	TODO	libccc_fixedpoint  + tests // fixed-point number math library
**	TODO	libccc_compress    + tests // compression functions (RLE, LZ77, LZW, Huffman)
**	TODO	libccc_crypto      + tests // cryptography
**	TODO	libccc_regex       + tests // regular expressions
**	TODO	libccc_vlq         + tests // variable-length quantity (bigint)
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
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
/*
**	Included to use the following std types:
**	- size_t
**	- ptrdiff_t
*/
#include <stddef.h>



/*
** ************************************************************************** *|
**                            Library Configuration                           *|
** ************************************************************************** *|
*/

//! If 1, libccc functions handle NULL pointers args, otherwise they segfault.
/*!
**	This macro determines how NULL pointer arguments are to be handled
**	If 0, then libccc functions will always segfault when given NULL pointers.
**	If 1, then all NULL pointer accesses in libccc functions will be avoided, and
**		an appropriate return value (eg:NULL, 0, sometimes -1) will be returned.
*/
#define LIBCONFIG_HANDLE_NULLPOINTERS		1

//! If 1, libccc uses homemade approximate math functions, otherwise it's the builtin FPU calls.
/*!
**	This macro determines which math function implementations should be used.
**	If 1, the libccc fast approximate functions will be used (precision error margin: 0.0001)
**	If 0, the builtin FPU-call libc math functions will be used (eg: __builtin_powf(), etc)
*/
#define LIBCONFIG_FAST_APPROX_MATH			0



//! If 1, libccc uses exact bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
/*!
**	This macro determines which int types are used by default, as well as corresponding MAXINT
**	and MININT values.
**	INTTYPES_EXACT, if true, overrides both INTYPES_FAST and INTTYPES_LEAST being themselves true.
*/
#define LIBCONFIG_DEFAULT_INTTYPES_EXACT	1
//! If 1, libccc uses fast bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
/*!
**	This macro determines which int types are used by default, as well as corresponding MAXINT
**	and MININT values.
**	INTYPES_FAST is true, it overridden by INTTYPES_EXACT being true, and overrides INTTYPES_LEAST
**	being true.
*/
#define LIBCONFIG_DEFAULT_INTTYPES_FAST		0
//! If 1, libccc uses least bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
/*!
**	This macro determines which int types are used by default, as well as corresponding MAXINT
**	and MININT values.
**	INTTYPES_LEAST, if true, is overridden by both either INTYPES_EXACT or INTTYPES_FAST being true.
*/
#define LIBCONFIG_DEFAULT_INTTYPES_LEAST	0


/*!
**	This macro sets the default 't_uint' default unsigned integer type to use:
**	_UINT_8_	for 8-bit uint	[0, 255]
**	_UINT_16_	for 16-bit uint	[0, 65535]
**	_UINT_32_	for 32-bit uint	[0, 2147483647]
**	_UINT_64_	for 64-bit uint	[0, 18446744073709551615]
*/
#define _UINT_32_
/*!
**	This macro sets the default 't_int' default signed integer type to use:
**	_INT_8_		for 8-bit int	[-128, 127]
**	_INT_16_	for 16-bit int	[-32648, 32647]
**	_INT_32_	for 32-bit int	[-2147483648, 2147483647]
**	_INT_64_	for 64-bit int	[-9223372036854775808, +9223372036854775807]
*/
#define _INT_32_
/*!
**	The following macro sets what the 't_float' default floating-point type should be.
**	_FLOAT_32_	for 32-bit IEEE 754 standard precision floating-point number
**	_FLOAT_64_	for 64-bit IEEE 754 double-precision floating-point number
**	_FLOAT_80_	for 80-bit x86 extended-precision floating-point number (not available on clang; will default to 128)
**	_FLOAT_128_	for 128-bit IEEE 754 quadruple-precision floating-point number (GNU GCC 4.3 and up)
*/
#define _FLOAT_32_



/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

/*
**	Define the common NULL pointer macros.
*/
#ifdef	NULL
#undef	NULL
#endif	//! Represents a NULL (0-value) pointer, of type 'void'
#define NULL	(void*)(0)

#ifdef	TYPED_NULL
#undef	TYPED_NULL
#endif	//! Represents a NULL pointer, of the given 'TYPE'
#define TYPED_NULL(TYPE)	(TYPE*)(0)

/*
**	Define the common useful macros for writing some pseudo-boolean syntax.
*/
#ifdef	FALSE
#undef	FALSE
#endif	//! Represents a boolean false value (0)
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif	//! Represents a boolean true value  (1)
#define TRUE	(1)

/*
**	Define the common macros for return values used by several C functions.
*/
#ifdef	OK
#undef	OK
#endif	//! Represents a successful function return
#define OK		(0)

#ifdef	ERROR
#undef	ERROR
#endif	//! Represents a failure function return
#define ERROR	(1)

/*! @file libccc.h
**	NB: The following macros listed here exist on almost any platform/compiler:
**
**	Here is the list of all the predefined ANSI C macros
**	__cplusplus	Defined only when a C++ compiler is being used.
**	__OBJC__	Defined as 1 when the compiler is Objective-C.
**	__STDC__	Defined as 1 when the compiler complies with the ANSI standard.
**	__DATE__	String literal: The current date, in "MMM DD YYYY" format.
**	__TIME__	String literal: The current time, in "HH:MM:SS" format.
**	__FILE__	String literal: This contains the current source code filename.
**	__LINE__	Integer constant: the current source code line number.
**
**	There's also this very useful (non-macro) identifier, only defined in C99/C++:
**	__func__	String constant: The current function name.
**
**	Here are some of the many common GNU C macros (only present with GNU-compliant compilers):
**	__GNUC__			Integer constant (with value = GCC version), if the compiler is GNU-compliant.
**	__COUNTER__			Starts as 0, increments every time it is expanded - can be useful to generate names with token-paste '##' operator
**	__BASE_FILE__		String literal: the source entry point filename (the file which holds the 'main()' function)
**	__INCLUDE_LEVEL__	Integer constant: The current depth of nesting within '#include' directives.
**
**	      __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__	If TRUE, this machine stores integers in reverse byte ordering (least-to-most signficant)
**	      __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__	If TRUE, this machine stores integers in regular byte ordering (most-to-least signficant)
**	      __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__	If TRUE, this machine stores integers in strange byte ordering (word-reverse & byte-reverse)
**	__FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__	If TRUE, this machine stores multi-word floats in reverse ordering (least-to-most signficant)
**	__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__	If TRUE, this machine stores multi-word floats in regular ordering (most-to-least signficant)
*/



/*
** ************************************************************************** *|
**                   Useful cross-platform compiler macros                    *|
** ************************************************************************** *|
*/

// Check windows
#if (_WIN32 || _WIN64)
	#if (_WIN64)
		#define _IS_64BIT	(1)	//!< If this is a 64-bit platform, then this is defined with value (1)
	#else
		#define _IS_32BIT	(1)	//!< If this is a 32-bit platform, then this is defined with value (1)
	#endif
#endif
// Check GCC
#if (__GNUC__)
	#if (__x86_64__ || __ppc64__)
		#define _IS_64BIT	(1)	//!< If this is a 64-bit platform, then this is defined with value (1)
	#else
		#define _IS_32BIT	(1)	//!< If this is a 32-bit platform, then this is defined with value (1)
	#endif
#endif



#ifdef __GNUC__
	#ifdef __clang__
		#define __format_printf(POS_FORMAT, POS_VARARGS)	__attribute__ ((format(printf, POS_FORMAT, POS_VARARGS)))
		#define __format_strftime(POS_FORMAT)				__attribute__ ((format(strftime, POS_FORMAT, 0)))
	#else
		#ifdef __MINGW32__
			#define __format_printf(POS_FORMAT, POS_VARARGS)	__attribute__ ((format(gnu_printf, POS_FORMAT, POS_VARARGS)))
			#define __format_strftime(POS_FORMAT)				__attribute__ ((format(gnu_strftime, POS_FORMAT, 0)))
		#else
			#define __format_printf(POS_FORMAT, POS_VARARGS)	__attribute__ ((format(printf, POS_FORMAT, POS_VARARGS)))
			#define __format_strftime(POS_FORMAT)				__attribute__ ((format(strftime, POS_FORMAT, 0)))
		#endif
	#endif
#else
	#define __format_printf(POS_FORMAT, POS_VARARGS)	
	#define __format_strftime(POS_FORMAT)	
#endif



/*
** ************************************************************************** *|
**                      Shorthands for primitive types                        *|
** ************************************************************************** *|
*/

/*
**	Define wrapper types for all the primitive number types in a clear naming
**	convention, to better reflect the amount of bits used by each type.
**	It is recommended to always use these types rather than the machine-specific
**	default C types char,short,int,long - the following typedefs will always
**	have the size that one would expect, no matter the machine.
**	You can learn more about how the ISO standard defines integer types here:
**	https://en.wikipedia.org/wiki/C_data_types
*/


#if LIBCONFIG_DEFAULT_INTTYPES_EXACT || (!LIBCONFIG_DEFAULT_INTTYPES_EXACT && !LIBCONFIG_DEFAULT_INTTYPES_FAST && !LIBCONFIG_DEFAULT_INTTYPES_LEAST)

	//! The type for 8-bit unsigned integers
	typedef uint8_t		t_u8;
	//! The type for 16-bit unsigned integers
	typedef uint16_t	t_u16;
	//! The type for 32-bit unsigned integers
	typedef uint32_t	t_u32;
	//! The type for 64-bit unsigned integers
	typedef	uint64_t	t_u64;

	#define U8_MAX	(255)                  //!< The maximum value for  8-bit unsigned integers (0xFF)
	#define U16_MAX	(65535)                //!< The maximum value for 16-bit unsigned integers (0xFFFF)
	#define U32_MAX	(4294967295)           //!< The maximum value for 32-bit unsigned integers (0xFFFFFFFF)
	#define U64_MAX	(18446744073709551615) //!< The maximum value for 64-bit unsigned integers (0xFFFFFFFFFFFFFFFF)

	//! The type for 8-bit signed integers
	typedef int8_t		t_s8;
	//! The type for 16-bit signed integers
	typedef int16_t		t_s16;
	//! The type for 32-bit signed integers
	typedef int32_t		t_s32;
	//! The type for 64-bit signed integers
	typedef	int64_t		t_s64;

	#define S8_MAX	(127)                  //!< The maximum value for  8-bit signed integers (0x7F)
	#define S16_MAX	(32767)                //!< The maximum value for 16-bit signed integers (0x7FFF)
	#define S32_MAX	(2147483647)           //!< The maximum value for 32-bit signed integers (0x7FFFFFFF)
	#define S64_MAX	(9223372036854775807)  //!< The maximum value for 64-bit signed integers (0x7FFFFFFFFFFFFFFF)

	#define S8_MIN	(-128)                 //!< The maximum value for  8-bit signed integers (0x80)
	#define S16_MIN	(-32768)               //!< The maximum value for 16-bit signed integers (0x8000)
	#define S32_MIN	(-2147483648)          //!< The maximum value for 32-bit signed integers (0x80000000)
	#define S64_MIN	(-9223372036854775808) //!< The maximum value for 64-bit signed integers (0x8000000000000000)


#elif LIBCONFIG_DEFAULT_INTTYPES_FAST

	//! The type for 8-bit unsigned integers
	typedef uint_fast8_t	t_u8;
	//! The type for 16-bit unsigned integers
	typedef uint_fast16_t	t_u16;
	//! The type for 32-bit unsigned integers
	typedef uint_fast32_t	t_u32;
	//! The type for 64-bit unsigned integers
	typedef	uint_fast64_t	t_u64;

	#define U8_MAX	((t_u8 )-1) //!< The maximum value for fastest, at least size  8-bit, unsigned integer type
	#define U16_MAX	((t_u16)-1) //!< The maximum value for fastest, at least size 16-bit, unsigned integer type
	#define U32_MAX	((t_u32)-1) //!< The maximum value for fastest, at least size 32-bit, unsigned integer type
	#define U64_MAX	((t_u64)-1) //!< The maximum value for fastest, at least size 64-bit, unsigned integer type

	//! The type for 8-bit signed integers
	typedef int_fast8_t		t_s8;
	//! The type for 16-bit signed integers
	typedef int_fast16_t	t_s16;
	//! The type for 32-bit signed integers
	typedef int_fast32_t	t_s32;
	//! The type for 64-bit signed integers
	typedef	int_fast64_t	t_s64;

	#define S8_MAX	((t_s8) (U8_MAX  >> 1)) ////!< The maximum value for fastest, at least size  8-bit, signed integer type
	#define S16_MAX	((t_s16)(U16_MAX >> 1)) ////!< The maximum value for fastest, at least size 16-bit, signed integer type
	#define S32_MAX	((t_s32)(U32_MAX >> 1)) ////!< The maximum value for fastest, at least size 32-bit, signed integer type
	#define S64_MAX	((t_s64)(U64_MAX >> 1)) ////!< The maximum value for fastest, at least size 64-bit, signed integer type

	#define S8_MIN	((t_s8) ((U8_MAX  >> 1) + 1)) //!< The minimum value for fastest, at least size  8-bit, signed integer type
	#define S16_MIN	((t_s16)((U16_MAX >> 1) + 1)) //!< The minimum value for fastest, at least size 16-bit, signed integer type
	#define S32_MIN	((t_s32)((U32_MAX >> 1) + 1)) //!< The minimum value for fastest, at least size 32-bit, signed integer type
	#define S64_MIN	((t_s64)((U64_MAX >> 1) + 1)) //!< The minimum value for fastest, at least size 64-bit, signed integer type


#elif LIBCONFIG_DEFAULT_INTTYPES_LEAST

	//! The type for 8-bit unsigned integers
	typedef uint_least8_t	t_u8;
	//! The type for 16-bit unsigned integers
	typedef uint_least16_t	t_u16;
	//! The type for 32-bit unsigned integers
	typedef uint_least32_t	t_u32;
	//! The type for 64-bit unsigned integers
	typedef	uint_least64_t	t_u64;

	#define U8_MAX	((t_u8 )-1) //!< The maximum value for smallest, at least size  8-bit, unsigned integer type
	#define U16_MAX	((t_u16)-1) //!< The maximum value for smallest, at least size 16-bit, unsigned integer type
	#define U32_MAX	((t_u32)-1) //!< The maximum value for smallest, at least size 32-bit, unsigned integer type
	#define U64_MAX	((t_u64)-1) //!< The maximum value for smallest, at least size 64-bit, unsigned integer type

	//! The type for 8-bit signed integers
	typedef int_least8_t	t_s8;
	//! The type for 16-bit signed integers
	typedef int_least16_t	t_s16;
	//! The type for 32-bit signed integers
	typedef int_least32_t	t_s32;
	//! The type for 64-bit signed integers
	typedef	int_least64_t	t_s64;

	#define S8_MAX	((t_s8) (U8_MAX  >> 1)) ////!< The maximum value for smallest, at least size  8-bit, signed integer type
	#define S16_MAX	((t_s16)(U16_MAX >> 1)) ////!< The maximum value for smallest, at least size 16-bit, signed integer type
	#define S32_MAX	((t_s32)(U32_MAX >> 1)) ////!< The maximum value for smallest, at least size 32-bit, signed integer type
	#define S64_MAX	((t_s64)(U64_MAX >> 1)) ////!< The maximum value for smallest, at least size 64-bit, signed integer type

	#define S8_MIN	((t_s8) ((U8_MAX  >> 1) + 1)) //!< The minimum value for smallest, at least size  8-bit, signed integer type
	#define S16_MIN	((t_s16)((U16_MAX >> 1) + 1)) //!< The minimum value for smallest, at least size 16-bit, signed integer type
	#define S32_MIN	((t_s32)((U32_MAX >> 1) + 1)) //!< The minimum value for smallest, at least size 32-bit, signed integer type
	#define S64_MIN	((t_s64)((U64_MAX >> 1) + 1)) //!< The minimum value for smallest, at least size 64-bit, signed integer type


#endif



//! The type for 32-bit 'single precision' IEEE-754 floating-point numbers
typedef float		t_f32;
//! The type for 64-bit 'double precision' IEEE-754 floating-point numbers
typedef double		t_f64;

#ifdef	__float80
//! The type for 32-bit 'extended precision' IEEE-754 floating-point numbers
typedef __float80	t_f80;
#elif defined(_FLOAT_80_)
	#error "Cannot set default float to 80-bit extended-precision, unavailable on this platform"
#endif

#ifdef	__float128
//! The type for 32-bit 'quadruple precision' IEEE-754 floating-point numbers
typedef __float128	t_f128;
#elif defined(_FLOAT_128_)
	#error "Cannot set default float to 128-bit quadruple-precision, unavailable on this platform"
#endif


//! The primitive boolean type
/*!
**	Here, we use the native (from C99 onwards) '_Bool' type.
**	This type is useful because its value will always be 0 or 1, never more.
*/
typedef _Bool		t_bool;

//! The RAM memory size type
/*!
**	This typedef is here purely for nomenclature consistency
**	(all primitive typedefs are prefixed with 't_')
*/
typedef size_t		t_size;

//! The pointer difference substraction result type
/*!
**	This typedef is here purely for nomenclature consistency
**	(all primitive typedefs are prefixed with 't_')
*/
typedef ptrdiff_t	t_ptrdiff;



/*
**	Much care should be used with the default int/uint types:
**	This obviously depends on you knowing your compiler and platform/machine.
*/
#ifdef _UINT_8_
typedef t_u8		t_uint;
#endif
#ifdef _UINT_16_
typedef t_u16		t_uint;
#endif
#ifdef _UINT_32_
typedef t_u32		t_uint;
#endif
#ifdef _UINT_64_
typedef t_u64		t_uint;
#endif

#ifdef _INT_8_
typedef t_s8		t_int;
#endif
#ifdef _INT_16_
typedef t_s16		t_int;
#endif
#ifdef _INT_32_
typedef t_s32		t_int;
#endif
#ifdef _INT_64_
typedef t_s64		t_int;
#endif

#ifdef _FLOAT_32_
typedef t_f32		t_float;
#endif
#ifdef _FLOAT_64_
typedef t_f64		t_float;
#endif
#ifdef _FLOAT_80_
typedef t_f80		t_float;
#endif
#ifdef _FLOAT_128_
typedef t_f128		t_float;
#endif



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
