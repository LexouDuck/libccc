/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_config.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_CONFIG_H
#define __LIBCCC_CONFIG_H
/*! @file libccc_config.h
**	This header defines all the primitive types and common macros to use.
**	@addtogroup libccc_config
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
//#define LIBCONFIG_INTEGER_TYPES _least // uncomment this line to use LEAST int types
//#define LIBCONFIG_INTEGER_TYPES _fast  // uncomment this line to use FAST int types



//! Defines which type/bit size the 't_uint' unsigned integer type will be
/*!
**	This macro sets the default 't_uint' default unsigned integer type to use.
**	There are 3 possible values for this #define:
**	8	for 8-bit uint	[0, 255]
**	16	for 16-bit uint	[0, 65535]
**	32	for 32-bit uint	[0, 2147483647]
**	64	for 64-bit uint	[0, 18446744073709551615]
*/
#define LIBCONFIG_BITS_UINT		32
#define LIBCONFIG_TYPE_UINT		t_u32

//! Defines which type/bit size the 't_int' signed integer type will be
/*!
**	This macro sets the default 't_int' default signed integer type to use:
**	8	for 8-bit int	[-128, 127]
**	16	for 16-bit int	[-32648, 32647]
**	32	for 32-bit int	[-2147483648, 2147483647]
**	64	for 64-bit int	[-9223372036854775808, +9223372036854775807]
*/
#define LIBCONFIG_BITS_INT		32
#define LIBCONFIG_TYPE_INT		t_s32

//! Defines which type/bit size the 't_fixed' fixed-point number type will be
/*!
**	The following macro sets what the 't_fixed' default fixed-point type should be.
*/
#define LIBCONFIG_BITS_FIXED	32
#define LIBCONFIG_TYPE_FIXED	t_g32
#define LIBCONFIG_BITS_FIXED_DECIMALPART	(LIBCONFIG_BITS_FIXED / 4)
#define LIBCONFIG_BITS_FIXED_INTEGERPART	(LIBCONFIG_BITS_FIXED - LIBCONFIG_BITS_FIXED_DECIMALPART)

//! Defines which type/bit size the 't_float' floating-point number type will be
/*!
**	The following macro sets what the 't_float' default floating-point type should be.
**	32	for 32-bit IEEE 754 standard precision floating-point number
**	64	for 64-bit IEEE 754 double-precision floating-point number
**	80	for 80-bit x86 extended-precision floating-point number (not available on clang; will default to 128)
**	128	for 128-bit IEEE 754 quadruple-precision floating-point number (GNU GCC 4.3 and up)
*/
#define LIBCONFIG_BITS_FLOAT	32
#define LIBCONFIG_TYPE_FLOAT	t_f32



/*! @} */
HEADER_END
#endif
