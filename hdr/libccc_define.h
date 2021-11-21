/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_define.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_DEFINE_H
#define __LIBCCC_DEFINE_H
/*! @file libccc_define.h
**	@addtogroup libccc_define
**	@{
**	This header defines all the common macros used to extend the C language.
**
**	Important read - regarding identifiers, storage duration, alignment:
**	@isostd{C,https://en.cppreference.com/w/c/language/object}
**
**	Interesting read, little known fact about C syntax and code text encodings.
**	@isostd{C,https://en.cppreference.com/w/c/language/operator_alternative}
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
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
**                   Useful cross-platform compiler macros                    *|
** ************************************************************************** *|
*/

/*! @file libccc.h
**	NB: The following macros listed here exist on almost any platform/compiler:
**
**	Here is the list of all the predefined ANSI C macros
**	__cplusplus	Defined only when a C++ compiler is being used.
**	__OBJC__	Defined as 1 when the compiler is Objective-C.
**	__DATE__	String literal: The current date, in "MMM DD YYYY" format.
**	__TIME__	String literal: The current time, in "HH:MM:SS" format.
**	__FILE__	String literal: This contains the current source code filename.
**	__LINE__	Integer constant: the current source code line number.
**	__STDC__	Defined as 1 when the compiler complies with the ISO C standard.
**	__STDC_VERSION__	Defined as a `long` literal value, in the format `YYYYMMl`, eg: 199901l means the C99 standard
**
**	There's also this very useful (non-macro) identifier, only defined in C99/C++:
**	__func__	String constant: The current function name.
**
**	Here are some of the many common GNU C macros (only present with GNU-compliant compilers):
**	__GNUC__			Integer constant (with value = GCC version), if the compiler is GNU-compliant.
**	__COUNTER__			Starts as 0, increments every time it is expanded - can be useful to generate names with token-paste '##' operator
**	__BASE_FILE__		String literal: the source entry point filename (the file which holds the 'main()' function)
**	__INCLUDE_LEVEL__	Integer constant: The current depth of nesting within `#include` directives.
**
**	      __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__	If TRUE, this machine stores integers in reverse byte ordering (least-to-most signficant)
**	      __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__	If TRUE, this machine stores integers in regular byte ordering (most-to-least signficant)
**	      __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__	If TRUE, this machine stores integers in strange byte ordering (word-reverse + byte-reverse)
**	__FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__	If TRUE, this machine stores multi-word floats in reverse ordering (least-to-most signficant)
**	__FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__	If TRUE, this machine stores multi-word floats in regular ordering (most-to-least signficant)
*/



//! These are convienence macros, to check for different C standards in preprocessor `#if` statements.
//!@{
#define __STDC_VERSION_ANSI__	0l	//!< NOTE: when only ANSI/C89/C90 support is present, __STDC_VERSION__ will not be defined !
#define __STDC_VERSION_C95__	199409l
#define __STDC_VERSION_C99__	199901l
#define __STDC_VERSION_C11__	201112l
#define __STDC_VERSION_C17__	201710l
#define __STDC_VERSION_C23__	(-1)	//!< TBD
//!@}



//! These are convienence macros, to check for different POSIX standards in preprocessor `#if` statements.
//!@{
#define __POSIX_VERSION_1990__ 1		//!< The 1990 edition of the POSIX.1  standard (IEEE Standard 1003.1-1990)
#define __POSIX_VERSION_1992__ 2		//!< The 1992 edition of the POSIX.2  standard (IEEE Standard 1003.2-1992)
#define __POSIX_VERSION_1993__ 199309l	//!< The 1993 edition of the POSIX.1b standard (IEEE Standard 1003.1b-1993)
#define __POSIX_VERSION_1995__ 199506l	//!< The 1995 edition of the POSIX.1c standard (IEEE Standard 1003.1c-1995)
#define __POSIX_VERSION_2001__ 200112l	//!< The 2001 edition of the POSIX    standard (IEEE Standard 1003.1-2001)
#define __POSIX_VERSION_2008__ 200809l	//!< The 2008 edition of the POSIX    standard (IEEE Standard 1003.1-2008)
//!@}



/*! @def __WINDOWS__
**	Platform macro to check if the current environment is windows (regardless of compiler)
*/
//!@{
#if (defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER))
#ifndef __WINDOWS__
#define __WINDOWS__	1
#endif
#endif
//!@}

/*! @def __MSVC__
**	Platform macro to check if the current compiler is microsoft-like
*/
//!@{
#if (defined(_MSC_VER))
#define __MSVC__	1
#endif
//!@}



//! These are convienence macros, to check for different C data model standards in preprocessor `#if` statements.
//!@{
#define __DATAMODEL_LP32__	0x02020404ul //!< (int is 16-bit, long and pointer are 32-bit) 32bit: Win16 API
#define __DATAMODEL_ILP32__	0x02040404ul //!< (int, long, and pointer are all size 32-bit) 32bit: Win32 API, Unix and Unix-like systems (Linux, macOS)
#define __DATAMODEL_LLP64__	0x02040408ul //!< (int and long are 32-bit, pointer is 64-bit) 64bit: Win64 API
#define __DATAMODEL_LP64__	0x02040808ul //!< (int is 32-bit, long and pointer are 64-bit) 64bit: Unix and Unix-like systems (Linux, macOS)
//!@}

// Check platform: windows
#if (__WINDOWS__)
	#if (defined(_WIN64))
		#define __DATAMODEL__	__DATAMODEL_LLP64__
	#elif (defined(_WIN32))
		#define __DATAMODEL__	__DATAMODEL_ILP32__
	#else
		#define __DATAMODEL__	__DATAMODEL_LP32__
	#endif

// Check platform: Unix
#elif (__GNUC__)
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



//!< If this is a 32-bit platform, then this expands to `1`, otherwise `0`
#define _IS_32BIT	(__DATAMODEL__ == __DATAMODEL_LP32__ || __DATAMODEL__ == __DATAMODEL_ILP32__)
//!< If this is a 64-bit platform, then this expands to `1`, otherwise `0`
#define _IS_64BIT	(__DATAMODEL__ == __DATAMODEL_LP64__ || __DATAMODEL__ == __DATAMODEL_LLP64__)



//! These macros can be used to check native type sizes at preprocess-time, ie: in `#if` statements.
//!@{
#define _SIZEOF_SHORT     ((__DATAMODEL__ >> 24) & 0xFF)
#define _SIZEOF_INT       ((__DATAMODEL__ >> 16) & 0xFF)
#define _SIZEOF_LONG      ((__DATAMODEL__ >>  8) & 0xFF)
#define _SIZEOF_LONGLONG  ((__DATAMODEL__ >>  0) & 0xFF)
#define _SIZEOF_POINTER   (_IS_32BIT ? 4 : 8)
//!@}



//! This macro allows to check if the current platform supports 128-bit integers
//!@{
#ifndef __int128
#define _HAS_128BIT	0
#else
#define _HAS_128BIT	1
#endif
//!@}



/*
** ************************************************************************** *|
**                           Common Macro Definitions                         *|
** ************************************************************************** *|
*/

//! Represents a successful function return (expands to `(0)`)
/*!
**	Similar to the [STD C exit() return macros](https://en.cppreference.com/w/c/program/EXIT_status),
**	This is a common general macro used for return values, used by several libccc functions.
*/
//!@{
#ifdef	OK
#undef	OK
#endif
#define OK		(0)
//!@}

//! Represents a failure function return (expands to `(-1)`)
/*!
**	Similar to the [STD C exit() return macros](https://en.cppreference.com/w/c/program/EXIT_status),
**	This is a common general macro used for return values, used by several libccc functions.
*/
//!@{
#ifdef	ERROR
#undef	ERROR
#endif
#define ERROR	(-1)
//!@}



//! This macro function expands and merges the two given tokens `TOKEN1` and `TOKEN2` into a single token
/*!
**	NB: This is useful because the token-paste concatenation operator `##`
**		merges tokens after expanding the macro's arguments, but it happens
**		before expanding their respective values. Here, an additional layer
**		of macro indirection forces the expansion to occur before token-pasting.
*/
//!@{
#define CONCAT(TOKEN1, TOKEN2)	CONCAT_(TOKEN1, TOKEN2)
#define CONCAT_(TOKEN1, TOKEN2)	TOKEN1##TOKEN2
//!@}

//! This macro function expands and stringizes the given `TOKEN` argument
/*!
**	NB: This is useful because the stringization operator `#` converts
**		the tokens after expanding the macro's arguments, but it happens
**		before expanding their respective values. Here, an additional layer
**		of macro indirection forces the expansion to occur before stringizing.
*/
//!@{
#define STRING(TOKEN)		STRING_(TOKEN)
#define STRING_(TOKEN)		#TOKEN
//!@}



//! Works like `strlen()` (aka String_Length()) but is resolved at compile time
//!@{
#define STRING_LENGTH(X)	(sizeof(X) - sizeof(""))
#define STRLEN(X)			STRING_LENGTH(X)
//!@}



/*
** ************************************************************************** *|
**                         Cross-platform C keywords                          *|
** ************************************************************************** *|
*/

/*! @def __asm__
**	@isostd{C89,https://en.cppreference.com/w/c/language/asm}
*/
//!@{
#ifndef __asm__
#ifdef __MSVC__
	#define __asm__	__asm
#elif !defined(__GNUC__)
	#define __asm__	asm
#endif
#endif
//!@}



/*! @def __inline__
**	@isostd{C99,https://en.cppreference.com/w/c/language/inline}
*/
//!@{
#ifndef __inline__
#ifdef __MSVC__
	#define __inline__	__inline
#elif !defined(__GNUC__)
	#define __inline__	inline
#endif
#endif
//!@}



/*! @def __restrict__
**	@isostd{C99,https://en.cppreference.com/w/c/language/restrict}
*/
//!@{
#ifndef __restrict__
#ifdef __MSVC__
	#define __restrict__	__restrict
#elif !defined(__GNUC__)
	#define __restrict__	restrict
#endif
#endif
//!@}



/*
** ************************************************************************** *|
**                         Cross-platform C operators                         *|
** ************************************************************************** *|
*/

/*! @def __sizeof__
**	@isostd{C89,https://en.cppreference.com/w/c/types/sizeof}
*/
//!@{
#ifndef __sizeof__
#define __sizeof__(X)	sizeof(X)
#endif
//!@}



/*! @def __typeof__
**	@isostd{GNU,https://gcc.gnu.org/onlinedocs/gcc/Typeof.html}
*/
//!@{
#ifndef __typeof__
#ifdef __MSVC__
	#define __typeof__(X)	decltype(X)
#else
	#define __typeof__(X)	typeof(X)
#endif
#endif
//!@}



/*! @def __offsetof__
**	@isostd{C89,https://en.cppreference.com/w/c/types/offsetof}
*/
//!@{
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
//!@}



/*! @def __alignof__
**	@isostd{C11,https://en.cppreference.com/w/c/language/_Alignof}
*/
//!@{
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
//!@}



/*! @def __alignas__
**	@isostd{C11,https://en.cppreference.com/w/c/language/_Alignas}
*/
//!@{
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



//! A 'foreach' keyword macro, to use with any iterable types, rather than an index-based 'for' loop
/*!
**	Currently, the types that work with this 'foreach' keyword are: s_array, s_list, s_dict
**	Here are some more details on how to use this macro:
**	- s_array<t_char*>:	foreach (t_char*, my_str, s_array, my_array) { ... }
**	- s_list<t_char*>:	foreach (t_char*, my_str, s_list,  my_list)  { ... }
**	- s_dict<t_char*>:	foreach (t_char*, my_str, s_dict,  my_dict)  { ... }
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
**               Cross-platform function attribute flags macros               *|
** ************************************************************************** *|
*/

//! This macro is used for generic-type functions, to perform dead code elimination on unused functions
/*!
**	To be more precise, this macro is used when including a generic-type file
**	(ie: the files located in `hdr/libccc/monad/` with the file extension `.c`),
**	to make all generic-type functions be declared as `static` (so they are local to a unit),
**	all the while suppressing the annoying "static function never used" warnings,
**	and still have the compiler/linker perform dead code elimination as appropriate.
*/
#define _GENERIC()	



#undef _FORMAT   //!< @def _FORMAT   Before a function def: make the compiler give warnings for a variadic-args function with a format string
#undef _ALIAS    //!< @def _ALIAS    Before a function or variable def: sets the token to be an alias for the one given as arg
#undef _ALIGN    //!< @def _ALIGN    Before a function or variable def: sets minimum byte alignment size (power of 2)
#undef _PURE     //!< @def _PURE     Before a function def: indicates that the function has no side-effects
#undef _MALLOC   //!< @def _MALLOC   Before a function def: indicates that it returns newly allocated ptr
#undef _UNUSED   //!< @def _UNUSED   Before a function def: suppresses warnings for empty/incomplete function
#undef _INLINE   //!< @def _INLINE   Before a function def: makes the function be always inlined regardless of compiler config
#undef _NOINLINE //!< @def _NOINLINE Before a function def: makes the function be always inlined regardless of compiler config
#undef _NORETURN //!< @def _NORETURN Before a function def: indicates that it never returns (runs forever, and/or calls abort() or exit())
#undef _PACKED   //!< @def _PACKED   Before a struct/union def: do not perform byte-padding on this struct/union type
//#undef _EXPORT   //!< @def _EXPORT   Before a function def: always export the symbol (regardless of static/dynamic linking)



#ifdef __NOSTD__

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



/*
** ************************************************************************** *|
**                        Include Binary (INCBIN) ASM macro                   *|
** ************************************************************************** *|
*/

//! These are cross-platform macros used to implement the INCBIN() macro function
//!@{
#ifdef __APPLE__
	#define INCBIN_MANGLE	"_"
	#define INCBIN_GLOBAL	".globl"
	#define INCBIN_INTEGER	".long"
	#define INCBIN_SECTION	".section __DATA,__const"
	#define INCBIN_PREVIOUS	".previous"
#else
	#define INCBIN_MANGLE	""
	#define INCBIN_GLOBAL	".global"
	#define INCBIN_INTEGER	".int"
	#ifdef __ELF__
		#define INCBIN_SECTION	".section \".rodata\", \"a\", @progbits"
		#define INCBIN_PREVIOUS	".previous"
	#else
		#define INCBIN_SECTION	".section .rodata"
		#define INCBIN_PREVIOUS	""
	#endif
#endif
//!@}

// TODO add .align pseudo-instruction ?
// TODO use .equ or .set rather than .int/.long ?

//! This macro includes the given binary file at "_PATH" (string) into a global const variable named `_NAME` (token)
/*!
**	@param	_NAME		The name to give to the global variable(s) which will be created
**	@param	_FILEPATH	The relative or oabsolute path of the file to include
**	@returns	This macro doesn't return anything per se, but it declares 3 global variables within its ASM code:
**	- `t_u8 const*	_NAME`			The statically allocated byte array containing the binary file data
**	- `t_u8 const*	_NAME##_end`	The pointer to the end of the file data byte array: contains 1 byte set to zero (works like a string null-terminator)
**	- `int const*	_NAME##_size`	The pointer 1 byte after '*_end', contains the file size. Use it like this: t_size len = (t_size)(*myfile_size);
*/
#define INCBIN(_NAME, _FILEPATH) \
/*extern t_u8 const	_NAME[];		*/	\
/*extern t_u8 const	_NAME##_end[];	*/	\
/*extern int const	_NAME##_size[];	*/	\
__asm__									\
(										\
	"\n"INCBIN_SECTION					\
	"\n"								\
	"\n"INCBIN_GLOBAL" "				\
		INCBIN_MANGLE#_NAME				\
	"\n"INCBIN_MANGLE#_NAME":"			\
	"\n\t.incbin \""_FILEPATH"\""		\
	"\n"								\
	"\n"INCBIN_GLOBAL" "				\
		INCBIN_MANGLE#_NAME"_end"		\
	"\n"INCBIN_MANGLE#_NAME"_end"":"	\
	"\n\t.byte 0"						\
	"\n"								\
	"\n"INCBIN_GLOBAL" "				\
		INCBIN_MANGLE#_NAME"_size"		\
	"\n"INCBIN_MANGLE#_NAME"_size"":"	\
	"\n\t"INCBIN_INTEGER				\
		" ( "INCBIN_MANGLE#_NAME"_end"	\
		" - "INCBIN_MANGLE#_NAME" )"	\
	"\n"								\
	"\n"INCBIN_PREVIOUS					\
	"\n"								\
);



/*! @} */
HEADER_END
#endif
