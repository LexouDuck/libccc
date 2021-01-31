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

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc/int.h"
#include "libccc/float.h"
//#include "libccc/fixed.h" TODO
#include "libccc/bool.h"
#include "libccc/pointer.h"
//#include "libccc/memory.h"
//#include "libccc/string.h"

HEADER_CPP

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
**	This macro configures which stdint.h integer types are used by default,
**	as well as setting the corresponding appropriate [INT]_MAX and [INT]_MIN values.
**	There are 3 possible values for this #define:
**	(undefined)	EXACT: This is the default - uses the 'exact size' integer types (int8_t, etc)
**				This is the recommended option as it ensures consistent overflow behavior on ints.
**				Unfortunately, certain platforms do not have these types, so the others can also be of use.
**	_least		LEAST: Uses the smallest available integer type with at least 'n' bits (int_least8_t, etc)
**	_fast		FAST: Uses the fastest available integer type with at least 'n' bits (int_fast8_t, etc)
*/
//#define LIBCONFIG_INTEGER_TYPES	_least	// uncomment this line to use LEAST int types
//#define LIBCONFIG_INTEGER_TYPES	_fast	// uncomment this line to use FAST int types



//! Defines which type/bit size the 't_uint' type will be
/*!
**	This macro sets the default 't_uint' default unsigned integer type to use.
**	There are 3 possible values for this #define:
**	8	for 8-bit uint	[0, 255]
**	16	for 16-bit uint	[0, 65535]
**	32	for 32-bit uint	[0, 2147483647]
**	64	for 64-bit uint	[0, 18446744073709551615]
*/
#define LIBCONFIG_BITSIZE_UINT	32

//! Defines which type/bit size the 't_int' type will be
/*!
**	This macro sets the default 't_int' default signed integer type to use:
**	8	for 8-bit int	[-128, 127]
**	16	for 16-bit int	[-32648, 32647]
**	32	for 32-bit int	[-2147483648, 2147483647]
**	64	for 64-bit int	[-9223372036854775808, +9223372036854775807]
*/
#define LIBCONFIG_BITSIZE_INT	32

//! Defines which type/bit size the 't_float' type will be
/*!
**	The following macro sets what the 't_float' default floating-point type should be.
**	32	for 32-bit IEEE 754 standard precision floating-point number
**	64	for 64-bit IEEE 754 double-precision floating-point number
**	80	for 80-bit x86 extended-precision floating-point number (not available on clang; will default to 128)
**	128	for 128-bit IEEE 754 quadruple-precision floating-point number (GNU GCC 4.3 and up)
*/
#define LIBCONFIG_BITSIZE_FLOAT	32



/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

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



//! A 'foreach' keyword macro, to use with any iterable types, rather than an index-based 'for' loop
/*
**	Currently, the types that work with this 'foreach' keyword are: s_array, s_list, s_dict
**	Here are some more details on how to use this macro:
**	- s_array:	
*/
#define foreach(VARIABLE_TYPE, VARIABLE, ITERABLE_TYPE, ITERABLE) \
	foreach_##ITERABLE_TYPE##_init(VARIABLE_TYPE, VARIABLE, ITERABLE)			\
	foreach_##ITERABLE_TYPE##_exit(VARIABLE_TYPE, VARIABLE, ITERABLE)			\
	for(foreach_##ITERABLE_TYPE##_loop_init(VARIABLE_TYPE, VARIABLE, ITERABLE);	\
		foreach_##ITERABLE_TYPE##_loop_exit(VARIABLE_TYPE, VARIABLE, ITERABLE);	\
		foreach_##ITERABLE_TYPE##_loop_incr(VARIABLE_TYPE, VARIABLE, ITERABLE))	\



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



/*! @} */
HEADER_END
#endif
