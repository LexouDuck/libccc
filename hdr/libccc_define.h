/*============================================================================*\
||                                            ______________________________  ||
||  libccc_define.h                          |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_DEFINE_H
#define __LIBCCC_DEFINE_H
/*!@group{libccc_define,2,libccc_define.h}
**
**	This header defines all the common macros used to extend the C language.
**
**	Important read - regarding identifiers, storage duration, alignment:
**	@isostd{C,https://en.cppreference.com/w/c/language/object}
**
**	Interesting read, little known fact about C syntax and code text encodings.
**	@isostd{C,https://en.cppreference.com/w/c/language/operator_alternative}
**
**	------
**
**	@note The following macros listed here exist as predefined builtins on almost any platform/compiler:
**
**	Here is the list of all the standard predefined ANSI C macros:
**
**	| Macro name          | Description
**	|---------------------|--------------
**	| `__cplusplus`       | Defined only when a C++ compiler is being used.
**	| `__OBJC__`          | Defined as 1 when the compiler is Objective-C.
**	| `__DATE__`          | String literal: The current date, in "MMM DD YYYY" format.
**	| `__TIME__`          | String literal: The current time, in "HH:MM:SS" format.
**	| `__FILE__`          | String literal: This contains the current source code filename.
**	| `__LINE__`          | Integer constant: the current source code line number.
**	| `__STDC__`          | Defined as 1 when the compiler complies with the ISO C standard.
**	| `__STDC_VERSION__`  | Defined as a `long` literal value, in the format `YYYYMMl`, eg: 199901l means the C99 standard
**
**	There's also this very useful (non-macro) identifier, only defined in C99/C++:
**
**	| Macro name          | Description
**	|---------------------|--------------
**	| `__func__`          | String constant: The current function name.
**
**	Also, here are some of the many common GNU C macros (only present with GNU-compliant compilers):
**
**	| Macro name          | Description
**	|---------------------|--------------
**	| `__GNUC__`          | Integer constant (with value = GCC version), if the compiler is GNU-compliant.
**	| `__COUNTER__`       | Starts as 0, increments every time it is expanded - can be useful to generate names with token-paste '##' operator
**	| `__BASE_FILE__`     | String literal: the source entry point filename (the file which holds the 'main()' function)
**	| `__INCLUDE_LEVEL__` | Integer constant: The current depth of nesting within `#include` directives.
**
**	There is also the `__BYTE_ORDER__` and `__FLOAT_WORD_ORDER__`, which describe the storage endianness of native numeric types.
**
**	| Macro name and value                              | Description
**	|---------------------------------------------------|--------------
**	|       `__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__` | If `TRUE`, this machine stores integers in reverse byte ordering (least-to-most signficant)
**	|       `__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__`    | If `TRUE`, this machine stores integers in regular byte ordering (most-to-least signficant)
**	|       `__BYTE_ORDER__ == __ORDER_PDP_ENDIAN__`    | If `TRUE`, this machine stores integers in strange byte ordering (word-reverse + byte-reverse)
**	| `__FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__` | If `TRUE`, this machine stores multi-word floats in reverse ordering (least-to-most signficant)
**	| `__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__`    | If `TRUE`, this machine stores multi-word floats in regular ordering (most-to-least signficant)
**
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

//!@doc Convenience macro: C++ header code guards
/*!
**	This macro is a more succinct way to write the typical `extern "C" {...}`
**	C++ header guards - mostly to prevent C++ compilers from doing symbol name mangling.
*/
//!@{
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
//!@}

HEADER_CPP



/*
** ************************************************************************** *|
**                   Useful cross-platform compiler macros                    *|
** ************************************************************************** *|
*/

//!@doc Convienence macros, use these to check for different C standards in preprocessor `#if` statements.
//!@{
#define __STDC_VERSION_ANSI__	0l	//!< NOTE: when only ANSI/C89/C90 support is present, `__STDC_VERSION__` will not be defined !
#define __STDC_VERSION_C95__	199409l
#define __STDC_VERSION_C99__	199901l
#define __STDC_VERSION_C11__	201112l
#define __STDC_VERSION_C17__	201710l
#define __STDC_VERSION_C23__	202311L
//!@}



//!@doc Convienence macros, use these to check for different POSIX standards in preprocessor `#if` statements.
//!@{
#define __POSIX_VERSION_1990__	1		//!< The 1990 edition of the POSIX.1  standard (IEEE Standard 1003.1-1990)
#define __POSIX_VERSION_1992__	2		//!< The 1992 edition of the POSIX.2  standard (IEEE Standard 1003.2-1992)
#define __POSIX_VERSION_1993__	199309l	//!< The 1993 edition of the POSIX.1b standard (IEEE Standard 1003.1b-1993)
#define __POSIX_VERSION_1995__	199506l	//!< The 1995 edition of the POSIX.1c standard (IEEE Standard 1003.1c-1995)
#define __POSIX_VERSION_2001__	200112l	//!< The 2001 edition of the POSIX    standard (IEEE Standard 1003.1-2001)
#define __POSIX_VERSION_2008__	200809l	//!< The 2008 edition of the POSIX    standard (IEEE Standard 1003.1-2008)
//!@}



//!@doc Platform-defined macro to check if the current environment is windows
//!@{
#if (defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER))
#ifndef __WINDOWS__
#define __WINDOWS__	1
#endif
#endif
//!@}

//!@doc Platform-defined macro to check if the current compiler is microsoft-like
//!@{
#if (defined(_MSC_VER))
#define __MSVC__	1
#endif
//!@}



#if (!defined(__GNUC__) && defined(__MSVC__))
/* Disable microsoft warnings for posix functions */
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif




//!@doc The data model for this platform (ie: the sizes of the c builtin integer types)
//!@{
#if (__WINDOWS__) // Check platform data model (Windows)
	#if (defined(_WIN64))
		#define __DATAMODEL__	__DATAMODEL_LLP64__
	#elif (defined(_WIN32))
		#define __DATAMODEL__	__DATAMODEL_ILP32__
	#else
		#define __DATAMODEL__	__DATAMODEL_LP32__
	#endif

#elif (__GNUC__) // Check platform data model (Unix)
	#if (__x86_64__ || __ppc64__)
		#define __DATAMODEL__	__DATAMODEL_LP64__
	#else
		#define __DATAMODEL__	__DATAMODEL_ILP32__
	#endif

#else
	#warning "Unknown data model: this platform is unsupported, and may need some manual configuration to build." \
		"\n""To be specific, the '_IS_[32/64]BIT' and '_SIZEOF_[SHORT/INT/LONG/LONGLONG/POINTER]' macros will not work." \
		"\n""Please run the libccc 'make test-predef' simple test program, to check which macros are predefined in your environment." \

#endif
//!@}

//!@doc Macros for the various C integer type data models
/*!
**	Convienence macros which describe the various different data model standards, ie: integer type sizes
*/
//!@{
#define __DATAMODEL_LP32__	0x02020404ul //!< (int is 16-bit, long and pointer are 32-bit) 32bit: Win16 API
#define __DATAMODEL_ILP32__	0x02040404ul //!< (int, long, and pointer are all size 32-bit) 32bit: Win32 API, Unix and Unix-like systems (Linux, macOS)
#define __DATAMODEL_LLP64__	0x02040408ul //!< (int and long are 32-bit, pointer is 64-bit) 64bit: Win64 API
#define __DATAMODEL_LP64__	0x02040808ul //!< (int is 32-bit, long and pointer are 64-bit) 64bit: Unix and Unix-like systems (Linux, macOS)
//!@}



//!@doc Platform bitness checking macros
/*!
**	These macros are always defined: their value expands to `0` or `1` depending on the platform bitness.
*/
//!@{
//! If this is a 32-bit platform, then this macro's value will resolve to `1`, otherwise `0`
#define _IS_32BIT	(__DATAMODEL__ == __DATAMODEL_LP32__ || __DATAMODEL__ == __DATAMODEL_ILP32__)
//! If this is a 64-bit platform, then this macro's value will resolve to `1`, otherwise `0`
#define _IS_64BIT	(__DATAMODEL__ == __DATAMODEL_LP64__ || __DATAMODEL__ == __DATAMODEL_LLP64__)
//!@}



//!@doc Macros for preprocessor integer size checking
/*!
**	These macros can be used to check native type sizes at preprocess-time, ie: in `#if` statements.
*/
//!@{
#define _SIZEOF_SHORT     ((__DATAMODEL__ >> 24) & 0xFF)
#define _SIZEOF_INT       ((__DATAMODEL__ >> 16) & 0xFF)
#define _SIZEOF_LONG      ((__DATAMODEL__ >>  8) & 0xFF)
#define _SIZEOF_LONGLONG  ((__DATAMODEL__ >>  0) & 0xFF)
#define _SIZEOF_POINTER   (_IS_32BIT ? 4 : 8)
//!@}



//!@doc Platform-specific 128-bit integer types
//!@{

#if defined(__SIZEOF_INT128__) \
	|| defined(__int128)

	#if (__SIZEOF_INT128__ != 16)
	#warning "Bad predefined macro: `__SIZEOF_INT128__` should have a value of `16`, or not be defined at all."
	#endif

	#ifndef __int128
	#define __int128 \
			__int128
	#endif

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
	typedef unsigned __int128	_UInt128; //!< Harmonized type for 128-bit unsigned integers
	typedef   signed __int128	_SInt128; //!< Harmonized type for 128-bit signed integers
	#pragma GCC diagnostic pop
#endif

//! This macro is set to `1` if the current platform supports 128-bit integers, or `0` otherwise
#ifdef __int128
#define _HAS_INT128	1
#else
#define _HAS_INT128	0
#endif

//!@}



//!@doc Platform-specific extended-precision `long double` floating-point types
//!@{

#if defined(__LDBL_MANT_DIG__) \
	|| defined(__float80)	\
	|| defined(__float128)	\

#if (__LDBL_MANT_DIG__ == 0)
#warning "Bad predefined macro: `__LDBL_MANT_DIG__` should not be defined with value of `0`"

#elif (__LDBL_MANT_DIG__ <= 24)
// `long double` is 32-bit (mantissa: 23 bits, exponent: 8 bits)

#elif (__LDBL_MANT_DIG__ <= 53)
// `long double` is 64-bit (mantissa: 52 bits, exponent: 11 bits)

#elif (__LDBL_MANT_DIG__ <= 64) || defined(__float80)
// `long double` is 80/96-bit (mantissa: 64 bits, exponent: 15 bits)
	#ifndef __float80
	#define __float80	long double
	#endif
	//! Harmonized type for 80-bit extended-precision floating-point numbers.
	typedef long double	_Float80;

#elif (__LDBL_MANT_DIG__ <= 113) || defined(__float128)
// `long double` is 128-bit (mantissa: 113 bits, exponent: 15 bits)
	#ifndef __float128
	#define __float128	long double
	#endif
	//! Harmonized type for 128-bit quadruple-precision floating-point numbers.
	typedef long double	_Float128;

#else
#warning "This platform provides an unknown `long double` type (neither 80-bit not 128-bit).\
		Please run 'make test-env-predef' to check the values of your platform's `__LDBL_*` macros."
#endif
#endif

//! This macro is set to `1` if the current platform supports 80-bit (96-bit) floats, or `0` otherwise
#ifdef __float80
#define _HAS_FLOAT80	1
#else
#define _HAS_FLOAT80	0
#endif

//! This macro is set to `1` if the current platform supports 128-bit floats, or `0` otherwise
#ifdef __float128
#define _HAS_FLOAT128	1
#else
#define _HAS_FLOAT128	0
#endif

//!@}



/*
** ************************************************************************** *|
**                           Common Macro Definitions                         *|
** ************************************************************************** *|
*/

//!@doc General convienence macro constants for function return values
/*!
**	These are similar in nature to the [STD C exit() return macros](https://en.cppreference.com/w/c/program/EXIT_status).
**	This is a common general macro used for return values, used by several libccc functions.
*/
//!@{
#ifdef	OK
#undef	OK
#endif
#define OK		(0) //!< Represents a successful function return (expands to `(0)`)

#ifdef	ERROR
#undef	ERROR
#endif
#define ERROR	(-1) //!< Represents a failure function return (expands to `(-1)`, ie: every bit set to 1)
//!@}



//!@doc Macro operator: token concatenation
/*!
**	This macro function concatenates the two given tokens `TOKEN1` and `TOKEN2` into a single token.
**
**	This is useful because the token-paste concatenation operator `A##B` merges its operand tokens
**	immediately after expanding the macro's arguments, but it happens before expanding their respective values.
**	With this macro function, not only can this be done anywhere (not just in a `#define` directive),
**	but an additional layer of macro indirection forces the macro expansion to occur before token-pasting.
*/
//!@{
#define CONCAT(TOKEN1, TOKEN2)	CONCAT_(TOKEN1, TOKEN2)
#define CONCAT_(TOKEN1, TOKEN2)	TOKEN1##TOKEN2
//!@}



//!@doc Macro operator: token stringization
/*!
**	This macro function expands and stringizes the given `TOKEN` argument
**
**	This is useful because the macro stringization operator `#A` transforms its operand into a string literal
**	immediately after expanding the macro's arguments, but it happens before expanding their respective values.
**	With this macro function, not only can this be done anywhere (not just in a `#define` directive),
**	but an additional layer of macro indirection forces the macro expansion to occur before stringization.
*/
//!@{
#define STRING(TOKEN)		STRING_(TOKEN)
#define STRING_(TOKEN)		#TOKEN
//!@}



//!@doc Macro operator: get string literal's length
/*!
**	Works like `strlen()` (aka String_Length()) but is resolved at compile time
*/
//!@{
#define STRLEN(X)			STRING_LENGTH(X)
#define STRING_LENGTH(X)	(sizeof(X) - sizeof(""))
//!@}



//!@doc Macro operator: check that two string literals are equal
/*!
**	Works like `strnequ()` (aka String_Equals_N(), with max 16 chars) but is resolved at compile time
*/
//!@{
#define STREQU(STR1, STR2, N)			STRING_EQUALS(STR1, STR2, N)
#define STRING_EQUALS(STR1, STR2, N)	STRING_EQUALS_##N(STR1, STR2)

#define STRING_EQUALS_0(X)	(1)
#define STRING_EQUALS_1(X)	(S1[0]==S2[0])
#define STRING_EQUALS_2(X)	(S1[0]==S2[0] && S1[1]==S2[1])
#define STRING_EQUALS_3(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2])
#define STRING_EQUALS_4(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3])
#define STRING_EQUALS_5(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4])
#define STRING_EQUALS_6(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5])
#define STRING_EQUALS_7(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6])
#define STRING_EQUALS_8(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7])
#define STRING_EQUALS_9(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8])
#define STRING_EQUALS_10(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9])
#define STRING_EQUALS_11(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9] && S1[10]==S2[10])
#define STRING_EQUALS_12(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9] && S1[10]==S2[10] && S1[11]==S2[11])
#define STRING_EQUALS_13(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9] && S1[10]==S2[10] && S1[11]==S2[11] && S1[12]==S2[12])
#define STRING_EQUALS_14(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9] && S1[10]==S2[10] && S1[11]==S2[11] && S1[12]==S2[12] && S1[13]==S2[13])
#define STRING_EQUALS_15(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9] && S1[10]==S2[10] && S1[11]==S2[11] && S1[12]==S2[12] && S1[13]==S2[13] && S1[14]==S2[14])
#define STRING_EQUALS_16(X)	(S1[0]==S2[0] && S1[1]==S2[1] && S1[2]==S2[2] && S1[3]==S2[3] && S1[4]==S2[4] && S1[5]==S2[5] && S1[6]==S2[6] && S1[7]==S2[7] && S1[8]==S2[8] && S1[9]==S2[9] && S1[10]==S2[10] && S1[11]==S2[11] && S1[12]==S2[12] && S1[13]==S2[13] && S1[14]==S2[14] && S1[15]==S2[15])
//!@}



/*
** ************************************************************************** *|
**                         Cross-platform C keywords                          *|
** ************************************************************************** *|
*/

//!@doc Cross-platform C keyword function macros
//!@{

//! Cross-platform keyword macro: `__asm__`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/language/asm}
*/
#ifndef __asm__
#ifdef __MSVC__
	#define __asm__	__asm
#elif !defined(__GNUC__)
	#define __asm__	asm
#endif
#endif

//! Cross-platform keyword macro: `__restrict__`
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/language/restrict}
*/
#ifndef __restrict__
#ifdef __MSVC__
	#define __restrict__	__restrict
#elif !defined(__GNUC__)
	#define __restrict__	restrict
#endif
#endif

//! Cross-platform keyword macro: `__inline__`
/*!
**	@isostd{C99,https://en.cppreference.com/w/c/language/inline}
*/
#ifndef __inline__
#ifdef __MSVC__
	#define __inline__	__inline
#elif !defined(__GNUC__)
	#define __inline__	inline
#endif
#endif

//!@}

#ifndef __cplusplus
#ifdef __MSVC__
	#if (_MSC_VER < 1900) /* older versions of MSVC do not support C99 inline at all */
		#define inline	
	#else
		#define inline	__inline
	#endif
#endif
#endif



/*
** ************************************************************************** *|
**                         Cross-platform C operators                         *|
** ************************************************************************** *|
*/

//!@doc Cross-platform C operator function macros
//!@{

//! Cross-platform operator macro: `__sizeof__`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/types/sizeof}
**	
**	The sizeof() function is a builtin C operator: this macro is only defined
**	here purely for the sake of completeness/exhaustiveness.
*/
#ifndef __sizeof__
#define __sizeof__(X)	sizeof(X)
#endif

//! Cross-platform operator macro: `__typeof__`
/*!
**	@isostd{GNU,https://gcc.gnu.org/onlinedocs/gcc/Typeof.html}
*/
#ifndef __typeof__
#ifdef __MSVC__
	#define __typeof__(X)	decltype(X)
#elif !defined(__GNUC__)
	#define __typeof__(X)	typeof(X)
#endif
#endif

//! Cross-platform operator macro: `__offsetof__`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/types/offsetof}
*/
#ifndef __offsetof__
#define __offsetof__(STRUCT, MEMBER)	offsetof(STRUCT, MEMBER)
#endif

#ifndef offsetof
#ifdef __NOSTD__
	#define offsetof(STRUCT, MEMBER)	((size_t)((char*)&((STRUCT*)0)->MEMBER - (char*)0))
#else
//	#include <stddef.h>
#endif
#endif

//! Cross-platform operator macro: `__alignof__`
/*!
**	@isostd{C11,https://en.cppreference.com/w/c/language/_Alignof}
*/
#ifndef __alignof__
#ifdef __NOSTD__
	#define __alignof__(X)	_Alignof(X)
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= __STDC_VERSION_C11__)
	#define __alignof__(X)	_Alignof(X)
#elif defined(alignof)
	#define __alignof__(X)	alignof(X)
#elif (!defined(__MSVC__))
	#include <stdalign.h>
	#define __alignof__(X)	alignof(X)
#else
	#define __alignof__(X)	
#endif
#endif

//! Cross-platform operator macro: `__alignas__`
/*!
**	@isostd{C11,https://en.cppreference.com/w/c/language/_Alignas}
*/
#ifndef __alignas__
#ifdef __NOSTD__
	#define __alignas__(X)	_Alignas(X)
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= __STDC_VERSION_C11__)
	#define __alignas__(X)	_Alignas(X)
#elif defined(alignas)
	#define __alignas__(X)	alignas(X)
#elif (!defined(__MSVC__))
	#include <stdalign.h>
	#define __alignas__(X)	alignas(X)
#else
	#define __alignas__(X)	
#endif
#endif

//!@}



/*
** ************************************************************************** *|
**                     For-Each loop (FOREACH) keyword macro                  *|
** ************************************************************************** *|
*/

//!@doc C extension: `foreach` keyword, to use with iterable types
/*!
**	A 'foreach' keyword macro, to use with any iterable types, rather than an index-based 'for' loop
**
**	Currently, the types that work with this 'foreach' keyword are: s_array, s_list, s_dict
**	Here are some more details on how to use this macro:
**	- for `s_array<t_char*>`:	`foreach (t_char*, my_str, s_array, my_array) { ... }`
**	- for `s_list<t_char*>`:	`foreach (t_char*, my_str, s_list,  my_list)  { ... }`
**	- for `s_dict<t_char*>`:	`foreach (t_char*, my_str, s_dict,  my_dict)  { ... }`
*/
#define foreach(VARIABLE_TYPE, VARIABLE, ITERABLE_TYPE, ITERABLE) \
	foreach_##ITERABLE_TYPE##_init(VARIABLE_TYPE, VARIABLE, ITERABLE)			\
	foreach_##ITERABLE_TYPE##_exit(VARIABLE_TYPE, VARIABLE, ITERABLE)			\
	for(foreach_##ITERABLE_TYPE##_loop_init(VARIABLE_TYPE, VARIABLE, ITERABLE);	\
		foreach_##ITERABLE_TYPE##_loop_exit(VARIABLE_TYPE, VARIABLE, ITERABLE);	\
		foreach_##ITERABLE_TYPE##_loop_incr(VARIABLE_TYPE, VARIABLE, ITERABLE),	\
		foreach_##ITERABLE_TYPE##_loop_setv(VARIABLE_TYPE, VARIABLE, ITERABLE))	\



/*
** ************************************************************************** *|
**              Cross-platform function declaration flag macros               *|
** ************************************************************************** *|
*/

//!@doc Cross-platform generic-typed function declaration specifier
/*!
**	This macro is used before any generic-type function's declaration:
**	it is used to perform dead code elimination on unused functions automatically.
**
**	To be more precise, this macro is used when including a generic-type file
**	(ie: the files located in `hdr/libccc/monad/` with the file extension `.c`),
**	to make all generic-type functions be declared as `static` (so they are local to a unit),
**	all the while suppressing the annoying "static function never used" warnings,
**	and still have the compiler/linker perform dead code elimination as appropriate.
*/
//!@{
#ifndef _GENERIC
#define _GENERIC()	
#endif
//!@}



//!@doc Cross-platform function attribute macros
//!@{

#undef _FORMAT
#undef _ALIAS
#undef _ALIGN
#undef _PURE
#undef _MALLOC
#undef _UNUSED
#undef _INLINE
#undef _NOINLINE
#undef _NORETURN
#undef _PACKED
//#undef _EXPORT

#if defined(__NOSTD__) || defined(__DOXYGEN__)
	#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS) //!< Before a function def: make the compiler give warnings for a variadic-args function with a format string
	#define _ALIAS(FUNCTION) //!< Before a function or variable def: sets the token to be an alias for the one given as arg
	#define _ALIGN(MINIMUM)  //!< Before a function or variable def: sets minimum byte alignment size (power of 2)
	#define _PURE()          //!< Before a function def: indicates that the function has no side-effects
	#define _MALLOC()        //!< Before a function def: indicates that it returns newly allocated ptr
	#define _UNUSED()        //!< Before a function def: suppresses warnings for empty/incomplete function
	#define _INLINE()        //!< Before a function def: makes the function be always inlined regardless of compiler config
	#define _NOINLINE()      //!< Before a function def: makes the function be always inlined regardless of compiler config
	#define _NORETURN()      //!< Before a function def: indicates that it never returns (runs forever, and/or calls abort() or exit())
	#define _PACKED()        //!< Before a struct/union def: do not perform byte-padding on this struct/union type
//	#define _EXPORT()        //!< Before a function def: always export the symbol (regardless of static/dynamic linking)

#elif defined(__GNUC__)
	#if (defined(__MINGW32__) && !defined(__clang__))
		#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)	__attribute__((format(gnu_##FUNCTION, POS_FORMAT, POS_VARARGS)))
	#else
		#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)	__attribute__((format(FUNCTION, POS_FORMAT, POS_VARARGS)))
	#endif
	#define _ALIAS(FUNCTION)	__attribute__((alias(#FUNCTION)))
	#define _ALIGN(MINIMUM)		__attribute__((aligned(MINIMUM)))
	#define _PURE()				__attribute__((pure))
	#define _MALLOC()			__attribute__((malloc))
	#define _UNUSED()			__attribute__((unused))
	#define _INLINE()			__attribute__((always_inline))
	#define _NOINLINE()			__attribute__((noinline))
	#define _NORETURN()			__attribute__((noreturn))
	#define _PACKED()			__attribute__((packed))

#elif defined(__MSVC__)
	#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)	
	#define _ALIAS(FUNCTION)	define ALIAS	FUNCTION
	#define _ALIGN(MINIMUM)		__declspec(align(MINIMUM))
	#define _PURE()				__declspec(noalias)
	#define _MALLOC()			__declspec(allocator)
	#define _UNUSED()			__declspec(deprecated)
	#define _INLINE()			inline
	#define _NOINLINE()			__declspec(noinline)
	#define _NORETURN()			__declspec(noreturn)
	#define _PACKED()			__pragma(pack(push, 1))	__pragma(pack(pop)) // TODO find a way to make this work in pure C ?

#else
	#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)	
	#define _ALIAS(FUNCTION)	
	#define _ALIGN(MINIMUM)		
	#define _PURE()				
	#define _MALLOC()			
	#define _UNUSED()			
	#define _INLINE()			
	#define _NOINLINE()			
	#define _NORETURN()			
	#define _PACKED()			

#endif

//!@}



/*
** ************************************************************************** *|
**                        Include Binary (INCBIN) ASM macro                   *|
** ************************************************************************** *|
*/

//!@doc INCBIN(): include a binary file directly as a global variable.
/*!
**	This macro embeds the given binary file at `FILEPATH` into a global const variable named `NAME`.
**
**	@param	NAME		The name to give to the global variable(s) which will be created
**	@param	FILEPATH	The relative or oabsolute path of the file to include
**	@returns	This macro doesn't return anything per se, but it declares 3 global variables within its ASM code:
**	- `t_u8 const*	NAME`        : The statically allocated byte array containing the binary file data
**	- `t_u8 const*	NAME##_end`  : The pointer to the end of the file data byte array: contains 1 byte set to zero (works like a string null-terminator)
**	- `int const*	NAME##_size` : The pointer 1 byte after '*_end', contains the file size. Use it like this: t_size len = (t_size)(*myfile_size);
*/
#define INCBIN(NAME, FILEPATH) \
/*extern t_u8 const	NAME[];        */ \
/*extern t_u8 const	NAME##_end[];  */ \
/*extern int const	NAME##_size[]; */ \
__asm__ \
( \
	"\n" INCBIN_SECTION \
	"\n" \
	"\n" INCBIN_GLOBAL " " INCBIN_MANGLE(#NAME) \
	"\n" INCBIN_MANGLE(#NAME)":" \
	"\n\t.incbin \"" FILEPATH "\"" \
	"\n" \
	"\n" INCBIN_GLOBAL " " INCBIN_MANGLE(#NAME)"_end" \
	"\n" INCBIN_MANGLE(#NAME)"_end"":" \
	"\n\t" INCBIN_BYTE " 0" \
	"\n" \
	"\n" INCBIN_GLOBAL " " INCBIN_MANGLE(#NAME)"_size" \
	"\n" INCBIN_MANGLE(#NAME)"_size"":" \
	"\n\t" INCBIN_SIZE " ( " INCBIN_MANGLE(#NAME)"_end - " INCBIN_MANGLE(#NAME)" )"	\
	"\n" \
	"\n" INCBIN_PREVIOUS \
	"\n" \
);

//!@doc Cross-platform ASM support macros for INCBIN()
/*!
**	These are cross-platform helper macros used to abstract away
**	GAS asmimplement the INCBIN() macro function
*/
//!@{
#if defined(__DOXYGEN__)
	#define INCBIN_SECTION      //!< The ASM directive to set the assembly section in which the file is embedded.
	#define INCBIN_PREVIOUS     //!< The ASM directive to return to the previous section.
	#define INCBIN_GLOBAL       //!< The ASM directive to make an address label globally visible.
	#define INCBIN_MANGLE(NAME) //!< The C symbol-mangling in the GAS ASM code.
	#define INCBIN_BYTE         //!< The ASM directive to output a single byte (for the _end label).
	#define INCBIN_SIZE         //!< The ASM directive to output an integer (for the _size label).

#elif defined(__APPLE__)
	#define INCBIN_SECTION	".section __DATA,__const"
	#define INCBIN_PREVIOUS	".previous"
	#define INCBIN_GLOBAL	".globl"
	#define INCBIN_MANGLE(NAME)	"_" NAME
	#define INCBIN_BYTE	".byte"
	#define INCBIN_SIZE	".long"

#else
	#if defined(__ELF__)
		#define INCBIN_SECTION	".section \".rodata\", \"a\", @progbits"
		#define INCBIN_PREVIOUS	".previous"
	#else
		#define INCBIN_SECTION	".section .rodata"
		#define INCBIN_PREVIOUS	""
	#endif
	#define INCBIN_GLOBAL	".global"
	#define INCBIN_MANGLE(NAME)	"" NAME
	#define INCBIN_BYTE	".byte"
	#define INCBIN_SIZE	".int"

#endif
//!@}

// TODO add .align pseudo-instruction ?
// TODO use .equ or .set rather than .int/.long ?



/*! @endgroup */
HEADER_END
#endif
