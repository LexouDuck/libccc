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
/*!@group{libccc_config,3,libccc_config.h}
**
**	This header defines all the configuration macros which alter how libccc works.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc_define.h"
#include "libccc_errors.h"

HEADER_CPP

/*============================================================================*\
||                            Library Configuration                           ||
\*============================================================================*/

//!@doc Configures the nomenclature style used by libccc for `typedef` statements.
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



//!@doc Defines which type/bit size the `t_uint` default unsigned integer type will be.
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
#define LIBCONFIG_UINT_BITS	64
#endif
#if (LIBCONFIG_UINT_BITS != 8) && \
	(LIBCONFIG_UINT_BITS != 16) && \
	(LIBCONFIG_UINT_BITS != 32) && \
	(LIBCONFIG_UINT_BITS != 64) && \
	(LIBCONFIG_UINT_BITS != 128)
#error "Invalid value selected for LIBCONFIG_UINT_BITS, must be one of: 8, 16, 32, 64, 128"
#endif
//!@}

//!@doc Sets which unsigned integer value ought to be used for error returns
/*!
**	This macro sets what value is returned when a function which returns an unsigned int has an error
**	NOTE: The value for the macro #UINT_ERROR depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	Will return `0`: this is how the C standard library works, though it can lead to confusions.
**	- `1`	Will use the largest representable unsigned int value for the bitsize in question.
**	  NOTE: When using this option, the #UINT_MAX macros will be different !
**			For example, `U8_MAX` will become `254`, rather than the usual `255`
*/
//!@{
#ifndef LIBCONFIG_UINT_NAN
#define LIBCONFIG_UINT_NAN	0
#endif
#if (LIBCONFIG_UINT_NAN != 0) && (LIBCONFIG_UINT_NAN != 1)
#error "Invalid value selected for LIBCONFIG_UINT_NAN, must be either 0 or 1"
#endif
//!@}

//!@doc Sets whether unsigned integer types should have an infinity value
/*!
**	This macro sets the behavior of uint functions when some calculation exceeds the representable integer values.
**	NOTE: The value for the macro #UINT_INFINITY depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	No infinity, overflow-behavior: this is how integer types usually work in most any programming language
**	- `1`	The largest representable unsigned integer value is used as an absorbant saturation-behavior INFINITY value
**	  NOTE: When using this option, the #UINT_MAX macros will be different !
**			For example, `U8_MAX` will become `254`, rather than the usual `255`
*/
//!@{
#ifndef LIBCONFIG_UINT_INF
#define LIBCONFIG_UINT_INF	0
#endif
#if (LIBCONFIG_UINT_INF != 0) && (LIBCONFIG_UINT_INF != 1)
#error "Invalid value selected for LIBCONFIG_UINT_INF, must be either 0 or 1"
#endif
//!@}



//!@doc Defines which type/bit size the `t_sint` default signed integer type will be
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
#define LIBCONFIG_SINT_BITS	64
#endif
#if (LIBCONFIG_SINT_BITS != 8) && \
	(LIBCONFIG_SINT_BITS != 16) && \
	(LIBCONFIG_SINT_BITS != 32) && \
	(LIBCONFIG_SINT_BITS != 64) && \
	(LIBCONFIG_SINT_BITS != 128)
#error "Invalid value selected for LIBCONFIG_SINT_BITS, must be one of: 8, 16, 32, 64, 128"
#endif
//!@}

//!@doc The signed integer value which is used for error returns
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
#ifndef LIBCONFIG_SINT_NAN
#define LIBCONFIG_SINT_NAN	0
#endif
#if (LIBCONFIG_SINT_NAN != 0) && (LIBCONFIG_SINT_NAN != 1)
#error "Invalid value selected for LIBCONFIG_SINT_NAN, must be either 0 or 1"
#endif
//!@}

//!@doc Sets whether signed integer types should have an infinity value
/*!
**	This macro sets the behavior of uint functions when some calculation exceeds the representable integer values.
**	NOTE: The value for the macro #SINT_INFINITY depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	No infinity, overflow-behavior: this is how integer types usually work in most any programming language
**	- `1`	The largest representable signed integer value is used as an absorbant saturation-behavior INFINITY value
**	  NOTE: When using this option, the #SINT_MAX macros will be different !
**			For example, `U8_MAX` will become `254`, rather than the usual `255`
*/
//!@{
#ifndef LIBCONFIG_SINT_INF
#define LIBCONFIG_SINT_INF	0
#endif
#if (LIBCONFIG_SINT_INF != 0) && (LIBCONFIG_SINT_INF != 1)
#error "Invalid value selected for LIBCONFIG_SINT_INF, must be either 0 or 1"
#endif
//!@}



//!@doc If 1, libccc uses exact bit length for t_s8, t_s16, t_s32, t_s64, t_u8, t_u16, t_u32, and t_u64
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
#if defined(__DOXYGEN__)
#define LIBCONFIG_INTEGER_TYPES	
#else
//#define LIBCONFIG_INTEGER_TYPES _least //!< uncomment this line to use LEAST int types
//#define LIBCONFIG_INTEGER_TYPES _fast  //!< uncomment this line to use FAST int types
#endif
//!@}



//!@doc Defines which type/bit size the `t_fixed` default fixed-point number type will be
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
#if (LIBCONFIG_FIXED_BITS != 16) && \
	(LIBCONFIG_FIXED_BITS != 32) && \
	(LIBCONFIG_FIXED_BITS != 64) && \
	(LIBCONFIG_FIXED_BITS != 128)
#error "Invalid value selected for LIBCONFIG_FIXED_BITS, must be one of: 16, 32, 64, 128"
#endif
//!@}
//!@doc The fixed-point value which is used for error returns
/*!
**	This macro sets what value is returned when a function which returns a fixed-point number has an error
**	NOTE: The value for the macro #FIXED_ERROR depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	Will return `0`: this mimics how the C standard library works (even though there is no fixed-point type in stdlib)
**	- `1`	Will use the smallest representable fixed-point value for the bitsize in question
**		NB: When using this option, the #FIXED_MIN macros will be different !
**			For example, `Q16_MIN` will become `-0x7FFF`, rather than the usual `-0x8000`
*/
//!@{
#ifndef LIBCONFIG_FIXED_NAN
#define LIBCONFIG_FIXED_NAN	1
#endif
#if (LIBCONFIG_FIXED_NAN != 0) && (LIBCONFIG_FIXED_NAN != 1)
#error "Invalid value selected for LIBCONFIG_FIXED_NAN, must be either 0 or 1"
#endif
//!@}

//!@doc Sets whether fixed-point types should have an infinity value
/*!
**	This macro sets the behavior of uint functions when some calculation exceeds the representable integer values.
**	NOTE: The value for the macro #FIXED_INFINITY depends on this setting
**	There are 2 possible values for this setting:
**	- `0`	No infinity, overflow-behavior: this is how integer types usually work in most any programming language
**	- `1`	The largest representable fixed-point value is used as an absorbant saturation-behavior INFINITY value
**	  NOTE: When using this option, the #FIXED_MAX macros will be different !
**			For example, `U8_MAX` will become `254`, rather than the usual `255`
*/
//!@{
#ifndef LIBCONFIG_FIXED_INF
#define LIBCONFIG_FIXED_INF	1
#endif
#if (LIBCONFIG_FIXED_INF != 0) && (LIBCONFIG_FIXED_INF != 1)
#error "Invalid value selected for LIBCONFIG_FIXED_INF, must be either 0 or 1"
#endif
//!@}

//!@doc The amount of subdivisions dedicated to the fraction part of the fixed-point types
/*!
**	This can be any signed integer value which is representable.
**	TODO make this more configurable, i.e. set each bitsize type individually ?
*/
//!@{
#ifndef LIBCONFIG_Q8_DENOMINATOR
#define LIBCONFIG_Q8_DENOMINATOR	4
#endif
#ifndef LIBCONFIG_Q16_DENOMINATOR
#define LIBCONFIG_Q16_DENOMINATOR	16
#endif
#ifndef LIBCONFIG_Q32_DENOMINATOR
#define LIBCONFIG_Q32_DENOMINATOR	256
#endif
#ifndef LIBCONFIG_Q64_DENOMINATOR
#define LIBCONFIG_Q64_DENOMINATOR	65536
#endif
#ifndef LIBCONFIG_Q128_DENOMINATOR
#define LIBCONFIG_Q128_DENOMINATOR	4294967296
#endif
//!@}



//!@doc Defines which type/bit size the `t_float` default floating-point number type will be
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
#if (LIBCONFIG_FLOAT_BITS != 32) && \
	(LIBCONFIG_FLOAT_BITS != 64) && \
	(LIBCONFIG_FLOAT_BITS != 80) && \
	(LIBCONFIG_FLOAT_BITS != 128)
#error "Invalid value selected for LIBCONFIG_FLOAT_BITS, must be one of: 32, 64, 80, 128"
#endif
//!@}
//!@doc The floating-point value which is used for error returns
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
#if (LIBCONFIG_FLOAT_ERROR != 0) && (LIBCONFIG_FLOAT_ERROR != 1)
#error "Invalid value selected for LIBCONFIG_FLOAT_ERROR, must be either 0 or 1"
#endif
//!@}



//!@doc Defines which type the `t_rand` default random state type will be
/*!
**	This macro sets the default `t_rand` RNG type and methods to use.
**	With the default settings, `t_rand` resolves to `t_prng`, and its functions work accordingly
**	(ie: the `Random_UInt()` function is really an alias for the `PRNG_UInt()` function)
**
**	There are 2 possible accepted values for these:
**
**	| `LIBCONFIG_RANDOM_TYPE` | Config description                           |
**	|-------------------------|----------------------------------------------|
**	| `t_prng`                | for simple pseudo-random number algorithm    |
**	| `t_csprng`              | for cryptographically-secure RNG (OS native) |
*/
//!@{
#ifndef LIBCONFIG_RANDOM_TYPE
#define LIBCONFIG_RANDOM_TYPE	t_prng
#endif
#ifndef LIBCONFIG_RANDOM_NAME
#define LIBCONFIG_RANDOM_NAME	PRNG
#endif
#if 0
#if !defined(LIBCONFIG_RANDOM_TYPE) || !defined(LIBCONFIG_RANDOM_NAME)
#error "The configuration macros LIBCONFIG_RANDOM_TYPE LIBCONFIG_RANDOM_NAME have not been defined properly"
#elif (STREQU(STRING(LIBCONFIG_RANDOM_TYPE), "t_prng", 6)
	#undef  LIBCONFIG_RANDOM_NAME
	#define LIBCONFIG_RANDOM_NAME	PRNG
#elif (STREQU(STRING(LIBCONFIG_RANDOM_TYPE), "t_csprng", 8)
	#undef  LIBCONFIG_RANDOM_NAME
	#define LIBCONFIG_RANDOM_NAME	CSPRNG
#else
#error "Invalid value(s) selected for LIBCONFIG_RANDOM_TYPE and/or LIBCONFIG_RANDOM_NAME"
#endif
#endif
//!@}



//!@doc Whether the `s_list` linked-list types in "libccc/generic/" will be doubly-linked
/*!
**	This macro configures whether the `s_list` type is singly-linked or doubly-linked.
**	NOTE: This must be set BEFORE including the `<libccc/generic/list.(c|h)>` header files
**	- If `0`, `s_list` is singly-linked (that is, the struct only holds a `.next` pointer)
**	- If `1`, `s_list` is doubly-linked (that is, the struct has both a `.prev` and `.next` pointer)
*/
//!@{
#ifndef LIBCONFIG_LIST_DOUBLYLINKED
#define LIBCONFIG_LIST_DOUBLYLINKED	0
#endif
#if (LIBCONFIG_LIST_DOUBLYLINKED != 0) && (LIBCONFIG_LIST_DOUBLYLINKED != 1)
#error "Invalid value selected for LIBCONFIG_LIST_DOUBLYLINKED, must be either 0 or 1"
#endif
//!@}
// TODO make it so doubly-linked lists have the first item's `->prev` point to the last element



//!@doc Whether libccc will define/expose utility functions for 128-bit integer types
/*!
**	By default, this setting will be enabled if the `__int128` macro is defined.
**	Since 128-bit integers are not supported by the standard, they are not
**	consistently accessible/usable/similar across all (or even most) platforms.
**	If you wish to make use of 128-bit integers regardless, then set this value to `1`.
**	Enabling this configuration setting will expose several types (and functions):
**	- `t_u128`: unsigned integer type
**	- `t_s128`: signed integer type
**	- `t_q128`: fixed-point fraction type
*/
//!@{
#ifndef LIBCONFIG_USE_INT128
#define LIBCONFIG_USE_INT128	_HAS_INT128
#endif
#if !defined(__int128) && LIBCONFIG_USE_INT128
#error "Current platform does not support native 128-bit integer type: please set LIBCONFIG_USE_INT128 to 0"
#endif
//!@}

//!@doc Whether libccc will define/expose utility functions for extended-precision floating-point types
/*!
**	By default, this setting will be enabled if the `__float80`/`__float128` macro is defined.
**	Since 80/96/128-bit floating-point numbers are only partly supported by the standard,
**	(as `long double`) they are not consistently accessible/usable/similar across all platforms.
**	If you wish to make use of extended floats regardless, then set this value to `1`.
**	Enabling this configuration setting will expose several types (and functions):
**	- `t_f80`: extended-precision floating-point type
**	- `t_f128`: quadruple-precision floating-point type
*/
//!@{
#ifndef LIBCONFIG_USE_FLOAT16
#define LIBCONFIG_USE_FLOAT16	0 //_HAS_FLOAT16
#endif
#if !defined(__float16) && LIBCONFIG_USE_FLOAT16
#error "Current platform does not support native 16-bit float type: please set LIBCONFIG_USE_FLOAT16 to 0"
#endif

#ifndef LIBCONFIG_USE_FLOAT80
#define LIBCONFIG_USE_FLOAT80	0 //_HAS_FLOAT80
#endif
#if !defined(__float80) && LIBCONFIG_USE_FLOAT80
#error "Current platform does not support native 80-bit float type: please set LIBCONFIG_USE_FLOAT80 to 0"
#endif

#ifndef LIBCONFIG_USE_FLOAT128
#define LIBCONFIG_USE_FLOAT128	0 //_HAS_FLOAT128
#endif
#if !defined(__float128) && LIBCONFIG_USE_FLOAT128
#error "Current platform does not support native 128-bit float type: please set LIBCONFIG_USE_FLOAT128 to 0"
#endif
//!@}



//!@doc Whether or not libccc should use the builtin math calls or its own math functions (most of which are from OpenBSD).
/*!
**	This macro determines which math function implementations should be used.
**	- If `0`, the libccc implementations functions will be used (usually slightly slower than the builtins)
**	- If `1`, the builtin FPU-call libc math functions will be used (eg: `__builtin_powf()`, etc)
**		This is the recommended option, and is on by default (since the standard math functions
**		are typically well-implemented for the given platform: they're both precise, and fast)
*/
//!@{
#ifndef LIBCONFIG_USE_STD_MATH
#define LIBCONFIG_USE_STD_MATH	0
#endif
#if (LIBCONFIG_USE_STD_MATH != 0) && (LIBCONFIG_USE_STD_MATH != 1)
#error "Invalid value selected for LIBCONFIG_USE_STD_MATH, must be either 0 or 1"
#endif
//!@}

//!@doc Whether or not libccc should use the very approximate fast math function implementations (this is not recommended, because the functions havent been tested enough, and their error margin is quite large).
//!@{
#ifndef LIBCONFIG_USE_CCC_MATH
#define LIBCONFIG_USE_CCC_MATH	0
#endif
#if (LIBCONFIG_USE_CCC_MATH != 0) && (LIBCONFIG_USE_CCC_MATH != 1)
#error "Invalid value selected for LIBCONFIG_USE_CCC_MATH, must be either 0 or 1"
#endif
//!@}



//!@doc Whether libccc will make the `t_complex` types use the STD C99 `_Complex`/`_Imaginary` types
/*!
**	TODO implement & document this
*/
//!@{
#ifndef LIBCONFIG_USE_STD_COMPLEX
#define LIBCONFIG_USE_STD_COMPLEX	0
#endif
#if (LIBCONFIG_USE_STD_COMPLEX != 0) && (LIBCONFIG_USE_STD_COMPLEX != 1)
#error "Invalid value selected for LIBCONFIG_USE_STD_COMPLEX, must be either 0 or 1"
#endif
//!@}



//!@doc Whether libccc will make the fixed point types `t_g*` and `t_fixed` use the STD ext `_Sat`/`_Fract`/`_Accum` types
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
#if (LIBCONFIG_USE_STD_FIXEDPOINT != 0) && (LIBCONFIG_USE_STD_FIXEDPOINT != 1)
#error "Invalid value selected for LIBCONFIG_USE_STD_FIXEDPOINT, must be either 0 or 1"
#endif
//!@}



//!@doc Whether or not libccc will define its functions as simple inline wrappers for STD C calls, wherever possible.
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
#define LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS	0
#endif
#if (LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS != 0) && (LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS != 1)
#error "Invalid value selected for LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS, must be either 0 or 1"
#endif
//!@}



//!@doc if `__NOSTD__` flag is active, force-disable all the `LIBCONFIG_USE_STD_*` macros
//!@{
#ifdef	__NOSTD__

#undef	LIBCONFIG_USE_CCC_MATH
#define	LIBCONFIG_USE_CCC_MATH	0

#undef	LIBCONFIG_USE_STD_MATH
#define	LIBCONFIG_USE_STD_MATH	0

#undef	LIBCONFIG_USE_STD_COMPLEX
#define	LIBCONFIG_USE_STD_COMPLEX	0

#undef	LIBCONFIG_USE_STD_FIXEDPOINT
#define	LIBCONFIG_USE_STD_FIXEDPOINT	0

#undef	LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#define	LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS	0

#endif
//!@}



/*! @endgroup */
HEADER_END
#endif
