/*============================================================================*\
||                                            ______________________________  ||
||  libccc_config.h                          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_CONFIG_H
#define __LIBCCC_CONFIG_H
/*! @file libccc_config.h
**	@addtogroup libccc_config
**	@{
**	This header defines all the configuration macros which alter how libccc works.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_define.h"
#include "libccc_errors.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                            Library Configuration                           *|
** ************************************************************************** *|
*/

//! Configures the nomenclature style used by libccc for `typedef` statements.
/*!
**	This macro sets the nomenclature style that libccc uses for `typedef`s.
**	The value works like both an enum and a bitflag simultaneously:
**	you can learn more about how this by looking at "libccc_naming.h".
**
**	The style used throughout libccc's code is `(NAMINGSTYLE_SNAKECASE | NAMINGSTYLE_FLAG_HUNGARIAN_PREFIX)`
**	You can set another style, it will actually generate a typedef alias above the existing typedef.
**	For example, having `(NAMINGSTYLE_SCREAMCASE)` will create a typedef for `t_bool` which is `BOOL`
**	Here, by default, the value is zero (no typedef aliases are generated).
*/
//!@{
#ifndef LIBCONFIG_NAMINGSTYLE_TYPES
#define LIBCONFIG_NAMINGSTYLE_TYPES	0
#endif
//!@}



//! The file to include in source files which use `HANDLE_ERROR()`
//!@{
#ifndef LIBCONFIG_ERROR_INCLUDE
#define LIBCONFIG_ERROR_INCLUDE	"libccc/error.h"
#endif
//!@}

//! The action to take when there is an integer overflow (by default, let it continue)
//!@{
#ifndef LIBCONFIG_ERROR_HANDLEOVERFLOW
#define LIBCONFIG_ERROR_HANDLEOVERFLOW(VALUE) \
//	return (VALUE);
#endif
#ifndef LIBCONFIG_ERROR_PARSEROVERFLOW
#define LIBCONFIG_ERROR_PARSEROVERFLOW(VALUE) \
//	if (dest)	*dest = VALUE;	return (i);
#endif

// TODO implement configurable overflow-case return values with this macro
#define LIBCONFIG_ERROR_OVERFLOW(TYPE, VALUE) \
	CONCAT(TYPE,_ERROR)	//!< configurable error value
//	(VALUE)				//!< saturated type
//!@}



//! Defines which type/bit size the `t_uint` default unsigned integer type will be.
/*!
**	This macro sets the default `t_uint` default unsigned integer type to use.
**	There are 5 possible accepted values for this #define:
**	- `8`	for 8-bit uint	[0, 255]
**	- `16`	for 16-bit uint	[0, 65535]
**	- `32`	for 32-bit uint	[0, 2147483647]
**	- `64`	for 64-bit uint	[0, 18446744073709551615]
**	- `128`	for 128-bit uint (not present on all platforms)
*/
//!@{
#ifndef LIBCONFIG_UINT_BITS
#define LIBCONFIG_UINT_BITS		32
#endif
//!@}
//! The unsigned integer value which is used for error returns
/*!
**	This macro sets what value is returned when a function which returns an unsigned int has an error
**	NOTE: The value for the macro #UINT_ERROR depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	Will return `0`: this is how the C standard library works, though it can lead to confusions.
**	- `1`	Will use the largest representable unsigned int value for the bitsize in question.
**		NB: When using this option, the #UINT_MAX macros will be different !
**			For example, `U8_MAX` will become `254`, rather than the usual `255`
*/
//!@{
#ifndef LIBCONFIG_UINT_ERROR
#define LIBCONFIG_UINT_ERROR	0
#endif
//!@}



//! Defines which type/bit size the `t_sint` default signed integer type will be
/*!
**	This macro sets the default `t_sint` default signed integer type to use:
**	There are 5 possible accepted values for this #define:
**	- `8`	for 8-bit int	[-128, 127]
**	- `16`	for 16-bit int	[-32648, 32647]
**	- `32`	for 32-bit int	[-2147483648, 2147483647]
**	- `64`	for 64-bit int	[-9223372036854775808, +9223372036854775807]
**	- `128`	for 128-bit int (not present on all platforms)
*/
//!@{
#ifndef LIBCONFIG_SINT_BITS
#define LIBCONFIG_SINT_BITS		32
#endif
//!@}
//! The signed integer value which is used for error returns
/*!
**	This macro sets what value is returned when a function which returns an unsigned int has an error
**	NOTE: The value for the macro #SINT_ERROR depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	Will return `0`: this is how the C standard library works, though it can lead to confusions.
**	- `1`	Will use the smallest representable signed int value for the bitsize in question.
**		NB: When using this option, the #SINT_MIN macros will be different !
**			For example, `S8_MIN` will become `-127`, rather than the usual `-128`
*/
//!@{
#ifndef LIBCONFIG_SINT_ERROR
#define LIBCONFIG_SINT_ERROR	0
#endif
//!@}



//! If 1, libccc uses exact bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
/*!
**	This macro configures which `<stdint.h>` integer types are used by default,
**	as well as setting the corresponding appropriate `[INT]_MAX` and `[INT]_MIN` values.
**	There are 3 possible values for this #define:
**	- (undefined)	EXACT: This is the default - uses the 'exact size' integer types (int8_t, etc)
**					This is the recommended option, as it ensures consistent overflow behavior on ints.
**					Unfortunately, certain platforms do not have these types, so the others can also be of use.
**	- `_least`	LEAST: Uses the smallest available integer type with at least `n` bits (`int_least8_t`, etc)
**	- `_fast`	FAST: Uses the fastest available integer type with at least `n` bits (`int_fast8_t`, etc)
*/
//!@{
//#define LIBCONFIG_INTEGER_TYPES _least //!< uncomment this line to use LEAST int types
//#define LIBCONFIG_INTEGER_TYPES _fast  //!< uncomment this line to use FAST int types
//!@}



//! Defines which type/bit size the `t_fixed` default fixed-point number type will be
/*!
**	This macro sets what the `t_fixed` default fixed-point type should be.
**	There are 4 possible accepted values for this #define:
**	- `16`	for 16-bit fixed-point number
**	- `32`	for 32-bit fixed-point number
**	- `64`	for 64-bit fixed-point number
**	- `128`	for 128-bit fixed-point number (not present on all platforms)
*/
//!@{
#ifndef LIBCONFIG_FIXED_BITS
#define LIBCONFIG_FIXED_BITS	64
#endif
//!@}
//! The fixed-point value which is used for error returns
/*!
**	This macro sets what value is returned when a function which returns a fixed-point number has an error
**	NOTE: The value for the macro #FIXED_ERROR depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	Will return `0`: this mimics how the C standard library works (even though there is no std fixed-point type in stdlib)
**	- `1`	Will use the smallest representable fixed-point value for the bitsize in question
**		NB: When using this option, the #FIXED_MIN macros will be different !
**			For example, `Q16_MIN` will become `-0x7FFF`, rather than the usual `-0x8000`
*/
//!@{
#ifndef LIBCONFIG_FIXED_ERROR
#define LIBCONFIG_FIXED_ERROR	1
#endif
//!@}
//! @see #FIXED_APPROX and Fixed_EqualsApprox()
//!@{
#ifndef LIBCONFIG_FIXED_APPROX
#define LIBCONFIG_FIXED_APPROX	((t_fixed)(LIBCONFIG_FIXED_DENOMINATOR / 2))
#endif
//!@}
//! The amount of subdivisions dedicated to the fraction part of the fixed-point types
/*!
**	This can be any signed integer value which is representable.
**	TODO make this more configurable, ie: set each bitsize type individually ?
*/
//!@{
#ifndef LIBCONFIG_FIXED_DENOMINATOR
#define LIBCONFIG_FIXED_DENOMINATOR	(256)
#endif
//!@}



//! Defines which type/bit size the `t_float` default floating-point number type will be
/*!
**	This macro sets what the `t_float` default floating-point type should be.
**	There are 4 possible accepted values for this #define:
**	- `32`	for 32-bit IEEE 754 single-precision floating-point number
**	- `64`	for 64-bit IEEE 754 double-precision floating-point number
**	- `80`	for 80-bit x86 extended-precision floating-point number (not present on all platforms)
**	- `128`	for 128-bit IEEE 754 quadruple-precision floating-point number (not present on all platforms)
*/
//!@{
#ifndef LIBCONFIG_FLOAT_BITS
#define LIBCONFIG_FLOAT_BITS	64
#endif
//!@}
//! The floating-point value which is used for error returns
/*!
**	This macro sets what value is returned when a function which returns a floating-point number has an error
**	NOTE: The value for the macro #FIXED_ERROR depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	Will return `0`: this is how the C standard library works (except for math functions, eg: `sqrt(-1)` returns `nan`)
**	- `1`	Will use the not-a-number float value for error returns for any float-return function.
*/
//!@{
#ifndef LIBCONFIG_FLOAT_ERROR
#define LIBCONFIG_FLOAT_ERROR	1
#endif
//!@}
//! @see #FLOAT_APPROX and Float_EqualsApprox()
//!@{
#ifndef LIBCONFIG_FLOAT_APPROX
#define LIBCONFIG_FLOAT_APPROX	(1.0e-10)
#endif
//!@}



//! Defines which type the `t_char` default text character type will be
/*!
**	This macro sets the default `t_char` text string character type and methods to use.
**	With the default settings, `t_char` resolves to `t_ascii`, and its functions work accordingly
**	(ie: the `Char_ToUpper()` function is really an alias for the `ASCII_IsUpper()` function)
**	There are 2 possible accepted values for these:
**		|`TYPE_CHAR`|`NAME_CHAR`|__________________________________________
**	-	| `t_ascii` | `ASCII`   | for simple 8-bit ASCII character strings
**	-	| `t_utf32` | `UTF32`   | for unicode 32-bit wide character strings
*/
//!@{
#ifndef LIBCONFIG_CHAR_TYPE
#define LIBCONFIG_CHAR_TYPE		t_ascii
#endif
#ifndef LIBCONFIG_CHAR_NAME
#define LIBCONFIG_CHAR_NAME		ASCII
#endif
//!@}



//! Defines which type the `t_rand` default random state type will be
/*!
**	This macro sets the default `t_rand` RNG type and methods to use.
**	With the default settings, `t_rand` resolves to `t_prng`, and its functions work accordingly
**	(ie: the `Random_UInt()` function is really an alias for the `PRNG_UInt()` function)
**	There are 2 possible accepted values for these:
**		|`TYPE_RANDOM`|`NAME_RANDOM`|__________________________________________
**	-	| `t_prng`    | `PRNG`      | for simple pseudo-random number algorithm
**	-	| `t_csprng`  | `CSPRNG`    | for cryptographically-secure RNG (OS native)
*/
//!@{
#ifndef LIBCONFIG_RANDOM_TYPE
#define LIBCONFIG_RANDOM_TYPE	t_prng
#endif
#ifndef LIBCONFIG_RANDOM_NAME
#define LIBCONFIG_RANDOM_NAME	PRNG
#endif
//!@}



//! Whether the `s_list` linked-list types in "libccc/monad/" will be doubly-linked
/*!
**	This macro configures whether the `s_list` type is singly-linked or doubly-linked.
**	NOTE: This must be set BEFORE including the `<libccc/monad/list.(c|h)>` header files
**	- If `0`, `s_list` is singly-linked (that is, the struct only holds a `.next` pointer)
**	- If `1`, `s_list` is doubly-linked (that is, the struct has both a `.prev` and `.next` pointer)
*/
//!@{
#ifndef LIBCONFIG_LIST_DOUBLYLINKED
#define LIBCONFIG_LIST_DOUBLYLINKED		0
#endif
//!@}
// TODO make it so doubly-linked lists have the first item's `->prev` point to the last element



//! Whether libccc will define/expose utility functions for 128-bit integer types
/*!
**	By default, this setting will be enabled if the `__int128` macro is defined.
**	Since 128-bit integers are not supported by the standard, they are not
**	consistently accessible/usable/similar across all (or even most) platforms.
**	If you wish to make use of 128-bit types regardless, then set this value to `1`.
**	Enabling this configuration setting will expose several types (and functions):
**	- `t_u128`: unsigned integer type
**	- `t_s128`: signed integer type
**	- `t_q128`: fixed-point fraction type
*/
//!@{
#ifndef LIBCONFIG_USE_INT128
#define LIBCONFIG_USE_INT128	0 // _HAS_INT128
#endif
//!@}



//! Whether or not libccc will define its functions as simple inline wrappers for STD C calls, wherever possible.
/*!
**	This macro determines if the compiler should prefer function implementations
**	from the platform's standard library, or the implementation from libccc.
**	- If `0`, use libccc function implementations everywhere
**	- If `1`, call stdlib implementations rather than libccc wherever possible
**
**	NOTE: Setting this to 1 can make your code run faster, but it may introduce
**		undefined behaviors depending on the platform (for edge-case arguments).
**		Also, it invalidates the error-handling settings (`DEFAULT_HANDLER`, etc):
**		Argument handling is implementation-dependent for STD C functions.
*/
//!@{
#ifndef LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#define LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS		0
#endif
//!@}



//! Whether or not libccc uses its own fast-approximate math functions or the builtin math calls.
/*!
**	This macro determines which math function implementations should be used.
**	- If `0`, the libccc fast approximate functions will be used (precision error margin is `10^-4`)
**	- If `1`, the builtin FPU-call libc math functions will be used (eg: `__builtin_powf()`, etc)
**		This is the recommended option, and is on by default (since the standard math functions
**		are typically well-implemented for the given platform: they're both precise, and fast)
*/
//!@{
#ifndef LIBCONFIG_USE_STD_MATH
#define LIBCONFIG_USE_STD_MATH			1
#endif
//!@}



//! Whether libccc will make the `t_complex` types use the STD C99 `_Complex`/`_Imaginary` types
/*!
**	TODO implement & document this
*/
//!@{
#ifndef LIBCONFIG_USE_STD_COMPLEX
#define LIBCONFIG_USE_STD_COMPLEX		0
#endif
//!@}



//! Whether libccc will make the fixed point types `t_g*` and `t_fixed` use the STD ext `_Sat`/`_Fract`/`_Accum` types
/*!
**	It is recommended to keep this set to `0`, as the STD C fixed-point types are not yet standard
**	(ie: `_Accum`, `_Fract`, and `_Sat` are not present on all platforms, only GCC implements them).
**	Furthermore, the libccc fixed-point type may not be as fast as a STD C implementation which
**	may leverage the platform's full capacities, but it does offer the signficant advantage of
**	being entirely configurable, regarding what portion of the fixed-point number type
**	is dedicated to the integer part and the fraction part.
*/
//!@{
#ifndef LIBCONFIG_USE_STD_FIXEDPOINT
#define LIBCONFIG_USE_STD_FIXEDPOINT	0
#endif
//!@}



//! if `__NOSTD__` flag is active, force-disable all the `LIBCONFIG_USE_STD_*` macros
//!@{
#ifdef	__NOSTD__

#undef	LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#define	LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS	0
/*
#undef	LIBCONFIG_USE_STD_MATH
#define	LIBCONFIG_USE_STD_MATH			0
*/
#undef	LIBCONFIG_USE_STD_COMPLEX
#define	LIBCONFIG_USE_STD_COMPLEX		0

#undef	LIBCONFIG_USE_STD_FIXEDPOINT
#define	LIBCONFIG_USE_STD_FIXEDPOINT	0

#endif
//!@}



/*! @} */
HEADER_END
#endif
