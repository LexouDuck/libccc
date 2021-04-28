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
**	@addtogroup libccc_config
**	@{
**	This header defines all the primitive types and common macros to use.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                            Library Configuration                           *|
** ************************************************************************** *|
*/

//! Configures the typedef nomenclature style used by libccc
/*!
**	This macro sets the nomenclature style that libccc uses for typedefs. The value works like
**	both an enum and a bitflag simultaneously: you can see how this works at the bottom of this file.
**	NB: The style used throughout libccc's code is `(NAMINGSTYLE_SNAKECASE | NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX)`
**		You can set another style, it will actually generate a typedef alias above the existing typedef.
**		For example, having `(NAMINGSTYLE_SCREAMCASE)` will create a typedef for `t_bool` which is `BOOL`
**		Here, by default, the value is zero (no typedef aliases are generated).
*/
#define LIBCONFIG_NAMINGSTYLE_TYPES		(0)



//! If 1, libccc will define its functions as simple inline wrappers for STD C calls.
/*!
**	This macro determines if the compiler should prefer function implementations
**	from the platform's standard library, or the implementation from libccc.
**	- If 0, use libccc function implementations everywhere
**	- If 1, call stdlib implementations rather than libccc wherever possible
**	NB: Setting this to 1 can make your code run faster, but it may introduce
**		undefined behaviors depending on the platform (for edge-case arguments).
**		Also, it invalidates the LIBCONFIG_HANDLE_NULLPOINTERS setting:
**		NULL pointer handling is implementation-dependent for STD C functions.
*/
#define LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS	(0) // TODO implement this config flag



//! If 1, libccc uses its own fast-approximate math functions, otherwise it's the builtin FPU calls.
/*!
**	This macro determines which math function implementations should be used.
**	- If 1, the libccc fast approximate functions will be used (precision error margin: 0.0001)
**	- If 0, the builtin FPU-call libc math functions will be used (eg: __builtin_powf(), etc)
*/
#define LIBCONFIG_USE_FAST_APPROX_MATH		(0)



//! If 1, the `s_list` and `s_object` types in "libccc/monad" will be doubly-linked
/*!
**	This macro configures whether the `s_list` type is singly-linked or doubly-linked.
**	NB: This must be set BEFORE including the <libccc/monad/list.(c|h)> files
**	- If 0, `s_list` is singly-linked (that is, the struct only holds a `.next` pointer)
**	- If 1, `s_list` is doubly-linked (that is, the struct has both a `.prev` and `.next` pointer)
*/
#define LIBCONFIG_LIST_DOUBLYLINKED		(0)



//! Defines which type/bit size the `t_uint` default unsigned integer type will be
/*!
**	This macro sets the default `t_uint` default unsigned integer type to use.
**	There are 5 possible accepted values for this #define:
**	-	8	for 8-bit uint	[0, 255]
**	-	16	for 16-bit uint	[0, 65535]
**	-	32	for 32-bit uint	[0, 2147483647]
**	-	64	for 64-bit uint	[0, 18446744073709551615]
**	-	128	for 128-bit uint (not present on all platforms)
*/
#define LIBCONFIG_BITS_UINT		32

//! Defines which type/bit size the `t_sint` default signed integer type will be
/*!
**	This macro sets the default `t_sint` default signed integer type to use:
**	There are 5 possible accepted values for this #define:
**	-	8	for 8-bit int	[-128, 127]
**	-	16	for 16-bit int	[-32648, 32647]
**	-	32	for 32-bit int	[-2147483648, 2147483647]
**	-	64	for 64-bit int	[-9223372036854775808, +9223372036854775807]
**	-	128	for 128-bit int (not present on all platforms)
*/
#define LIBCONFIG_BITS_SINT		32

//! Defines which type/bit size the `t_fixed` default fixed-point number type will be
/*!
**	The following macro sets what the `t_fixed` default fixed-point type should be.
**	There are 4 possible accepted values for this #define:
**	-	16	for 16-bit fixed-point number
**	-	32	for 32-bit fixed-point number
**	-	64	for 64-bit fixed-point number
**	-	128	for 128-bit fixed-point number (not present on all platforms)
*/
#define LIBCONFIG_BITS_FIXED	32
//! @see #FIXED_APPROX and Fixed_EqualsApprox()
#define LIBCONFIG_FIXED_APPROX	(1.0e-10)
//! the amount of bits dedicated to the fraction part of the fixed-point types
#define LIBCONFIG_FIXED_BITS_FRACTIONPART(BITS)	(BITS / 4)
//! the amount of bits dedicated to the integer part of the fixed-point types
#define LIBCONFIG_FIXED_BITS_INTEGERPART(BITS)	(BITS - FIXED_BITS_FRACTIONPART)

//! Defines which type/bit size the `t_float` default floating-point number type will be
/*!
**	The following macro sets what the `t_float` default floating-point type should be.
**	There are 4 possible accepted values for this #define:
**	-	32	for 32-bit IEEE 754 single-precision floating-point number
**	-	64	for 64-bit IEEE 754 double-precision floating-point number
**	-	80	for 80-bit x86 extended-precision floating-point number (not present on all platforms)
**	-	128	for 128-bit IEEE 754 quadruple-precision floating-point number (not present on all platforms)
*/
#define LIBCONFIG_BITS_FLOAT	32
//! @see #FLOAT_APPROX and Float_EqualsApprox()
#define LIBCONFIG_FLOAT_APPROX	(1.0e-10)



//! If 1, libccc uses exact bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
/*!
**	This macro configures which stdint.h integer types are used by default,
**	as well as setting the corresponding appropriate `[INT]_MAX` and `[INT]_MIN` values.
**	There are 3 possible values for this #define:
**	-	(undefined)	EXACT: This is the default - uses the 'exact size' integer types (int8_t, etc)
**	-				This is the recommended option as it ensures consistent overflow behavior on ints.
**	-				Unfortunately, certain platforms do not have these types, so the others can also be of use.
**	-	_least		LEAST: Uses the smallest available integer type with at least `n` bits (`int_least8_t`, etc)
**	-	_fast		FAST: Uses the fastest available integer type with at least `n` bits (`int_fast8_t`, etc)
*/
//#define LIBCONFIG_INTEGER_TYPES _least // uncomment this line to use LEAST int types
//#define LIBCONFIG_INTEGER_TYPES _fast  // uncomment this line to use FAST int types



//! If 1, libccc will make the `t_complex` types use the STDC _Complex type
/*!
**	TODO implement & document this
*/
#define LIBCONFIG_USE_STD_COMPLEX		0



//! If 1, libccc will make the fixed point types 't_g*' and `t_fixed` use the STDC `_Sat, _Fract, _Accum` types
/*!
**	It is recommended to keep this set to 0, as the STD C fixed-point types are not yet standard
**	(ie: `_Accum`, `_Fract`, and `_Sat` are not present on all platforms, only GCC implements them).
**	Furthermore, the libccc fixed-point type may not be as fast as a STD C implementation which
**	may leverage the platform's full capacities, but it does offer the signficant advantage of
**	being entirely configurable, regarding what portion of the fixed-point number type
**	is dedicated to the integer part and the fraction part.
*/
#define LIBCONFIG_USE_STD_FIXEDPOINT	0



//! These macros allow you to configure how libccc handles parameter validation.
/*!
**	The "plural-named" macros should only ever have a value of `0` or `1`,
**	they are used to activate or deactivate parameter validation at will.
**	The "single-named" macro functions determine how the arguments are to be
**	checked, validated, and handled. These macro functions are the important part,
**	where you may customize the logic (to implement custom exception handling for example).
*/
//!@{

//! TODO configurable allocation failure error handling
//! TODO configurable IO error handling
//! TODO configurable parse error handling

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_NULLPOINTERS	(1)
#define LIBCONFIG_HANDLE_NULLPOINTER(RESULT, PTR) \
	if ((PTR) == NULL)	return RESULT;

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_INVALIDENUMS	(1) // TODO check everywhere where this should be used, and use it
#define LIBCONFIG_HANDLE_INVALIDENUM(RESULT, ENUM, MIN, MAX) \
	if ((ENUM) < (MIN) || (ENUM) > (MAX))	return RESULT;

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_INDEX2SMALLS	(1) // TODO check everywhere where this should be used, and use it
#define LIBCONFIG_HANDLE_INDEX2SMALL(RESULT, INDEX, MIN) \
	if ((INDEX) < (MIN))	return RESULT;

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_INDEX2LARGES	(1) // TODO check everywhere where this should be used, and use it
#define LIBCONFIG_HANDLE_INDEX2LARGE(RESULT, INDEX, MAX) \
	if ((INDEX) >= (MAX))	return RESULT;

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_LENGTH2SMALLS	(1) // TODO check everywhere where this should be used, and use it
#define LIBCONFIG_HANDLE_LENGTH2SMALL(RESULT, LENGTH, MIN) \
	if ((LENGTH) < (MIN))	return RESULT;

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_LENGTH2LARGES	(1) // TODO check everywhere where this should be used, and use it
#define LIBCONFIG_HANDLE_LENGTH2LARGE(RESULT, LENGTH, MAX) \
	if ((LENGTH) > (MAX))	return RESULT;

//! Set value to `(0)` or comment out this `#define` to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_PARSINGERRORS	(1) // TODO check everywhere where this should be used, and use it
#define LIBCONFIG_HANDLE_PARSINGERROR(RESULT, FORMAT, ...) \
	{											\
		IO_Output_Format(FORMAT, ##__VA_ARGS__);\
		return RESULT;							\
	}											\
//!@}



// if the `(1)` macros are notdefined, or have value zero, deactivate this handler macro functions

#if !( \
defined(LIBCONFIG_HANDLE_LENGTH2LARGES) && \
		LIBCONFIG_HANDLE_LENGTH2LARGES)
#undef  LIBCONFIG_HANDLE_LENGTH2LARGE
#define LIBCONFIG_HANDLE_LENGTH2LARGE(ARG, RESULT, MAX)
#endif

#if !( \
defined(LIBCONFIG_HANDLE_NULLPOINTERS) && \
		LIBCONFIG_HANDLE_NULLPOINTERS)
#undef  LIBCONFIG_HANDLE_NULLPOINTER
#define LIBCONFIG_HANDLE_NULLPOINTER(ARG, RESULT)
#endif

#if !( \
defined(LIBCONFIG_HANDLE_INVALIDENUMS) && \
		LIBCONFIG_HANDLE_INVALIDENUMS)
#undef  LIBCONFIG_HANDLE_INVALIDENUM
#define LIBCONFIG_HANDLE_INVALIDENUM(ARG, RESULT, MIN, MAX)
#endif

#if !( \
defined(LIBCONFIG_HANDLE_INDEX2SMALLS) && \
		LIBCONFIG_HANDLE_INDEX2SMALLS)
#undef  LIBCONFIG_HANDLE_INDEX2SMALL
#define LIBCONFIG_HANDLE_INDEX2SMALL(ARG, RESULT, MIN)
#endif

#if !( \
defined(LIBCONFIG_HANDLE_INDEX2LARGES) && \
		LIBCONFIG_HANDLE_INDEX2LARGES)
#undef  LIBCONFIG_HANDLE_INDEX2LARGE
#define LIBCONFIG_HANDLE_INDEX2LARGE(ARG, RESULT, MAX)
#endif

#if !( \
defined(LIBCONFIG_HANDLE_LENGTH2SMALLS) && \
		LIBCONFIG_HANDLE_LENGTH2SMALLS)
#undef  LIBCONFIG_HANDLE_LENGTH2SMALL
#define LIBCONFIG_HANDLE_LENGTH2SMALL(ARG, RESULT, MIN)
#endif

#if !( \
defined(LIBCONFIG_HANDLE_LENGTH2LARGES) && \
		LIBCONFIG_HANDLE_LENGTH2LARGES)
#undef  LIBCONFIG_HANDLE_LENGTH2LARGE
#define LIBCONFIG_HANDLE_LENGTH2LARGE(ARG, RESULT, MAX)
#endif



/*! @} */
HEADER_END
#endif
