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
**	This header defines all the common macros/defines used to "extend" C.
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



//! This macro function expands and merges the two given tokens `TOKEN1` and `TOKEN2` into a single token
/*
**	NB: This is useful because the token-paste concatenation operator `##`
**		merges tokens after expanding the macro's arguments, but it happens
**		before expanding their respective values. Here, an additional layer
**		of macro indirection forces the expansion to occur before token-pasting.
*/
#define CONCAT(TOKEN1, TOKEN2)	CONCAT_(TOKEN1, TOKEN2)
#define CONCAT_(TOKEN1, TOKEN2)	TOKEN1##TOKEN2

//! This macro function expands and stringizes the given `TOKEN` argument
/*
**	NB: This is useful because the stringize token operator `#` converts
**		the tokens after expanding the macro's arguments, but it happens
**		before expanding their respective values. Here, an additional layer
**		of macro indirection forces the expansion to occur before stringizing.
*/
#define STRING(TOKEN)		STRING_(TOKEN)
#define STRING_(TOKEN)		#TOKEN



//! A 'foreach' keyword macro, to use with any iterable types, rather than an index-based 'for' loop
/*
**	Currently, the types that work with this 'foreach' keyword are: s_array, s_list, s_dict
**	Here are some more details on how to use this macro:
**	- s_array<char*>:	foreach (char*, str, s_array, array) { ... }
**	- s_list<char*>:	foreach (char*, str, s_list,  list)  { ... }
**	- s_dict<char*>:	foreach (char*, str, s_dict,  dict)  { ... }
*/
#define foreach(VARIABLE_TYPE, VARIABLE, ITERABLE_TYPE, ITERABLE) \
	foreach_##ITERABLE_TYPE##_init(VARIABLE_TYPE, VARIABLE, ITERABLE)			\
	foreach_##ITERABLE_TYPE##_exit(VARIABLE_TYPE, VARIABLE, ITERABLE)			\
	for(foreach_##ITERABLE_TYPE##_loop_init(VARIABLE_TYPE, VARIABLE, ITERABLE);	\
		foreach_##ITERABLE_TYPE##_loop_exit(VARIABLE_TYPE, VARIABLE, ITERABLE);	\
		foreach_##ITERABLE_TYPE##_loop_incr(VARIABLE_TYPE, VARIABLE, ITERABLE))	\



/*
**	Define macros for common function attributes (as documented by GNU)
*/
#ifdef __GNUC__
	#ifdef __clang__
		#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)		__attribute__((format(FUNCTION, POS_FORMAT, POS_VARARGS)))
	#else
		#ifdef __MINGW32__
			#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)	__attribute__((format(gnu_##FUNCTION, POS_FORMAT, POS_VARARGS)))
		#else
			#define _FORMAT(FUNCTION, POS_FORMAT, POS_VARARGS)	__attribute__((format(FUNCTION, POS_FORMAT, POS_VARARGS)))
		#endif
	#endif
	#define _ALIAS(FUNCTION)	__attribute__((alias(#FUNCTION)))		//!< before function or variable def: sets the token to be an alias for the one given as arg
	#define _ALIGN(MINIMUM)		__attribute__((aligned(MINIMUM)))		//!< before function or variable def: sets minimum byte alignment size (power of 2)
	#define _PURE()				__attribute__((pure))					//!< before function def: indicates that the function has no side-effects
	#define _INLINE()			__attribute__((always_inline)) inline	//!< before function def: makes the function be always inlined regardless of compiler config
	#define _MALLOC()			__attribute__((malloc))					//!< before function def: indicates that it returns newly allocated ptr
	#define _DELETE()			__attribute__((delete))					//!< before function def: indicates that it deletes/frees memory
	#define _UNUSED()			__attribute__((unused))					//!< before function def: suppresses warnings for empty/incomplete function
	#define _PACKED()			__attribute__((packed))					//!< before struct/union def: do not perform byte-padding on this struct/union type
#endif



/*
** ************************************************************************** *|
**                   Useful cross-platform compiler macros                    *|
** ************************************************************************** *|
*/

/*! @file libccc_define.h
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



/*
** ************************************************************************** *|
**                        Include Binary (INCBIN) ASM macro                   *|
** ************************************************************************** *|
*/

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

// TODO add .align pseudo-instruction ?
// TODO use .equ or .set rather than .int/.long ?

//! This macro includes the given binary file at "_PATH" (string) into a global const variable named <_NAME> (token)
/*!
**	@param	_NAME		The name to give to the global variable(s) which will be created
**	@param	_FILEPATH	
**	@returns - This macro doesn't return anything per se, but it declares 3 global/extern variables:
**		t_u8 const*	<_NAME>			The statically allocated byte array containing the binary file data
**		t_u8 const*	<_NAME>_end		The pointer to the end of the file data byte array: contains 1 byte set to zero (works like a string null-terminator)
**		int const*	<_NAME>_size	The pointer 1 byte after '*_end', contains the file size. Use it like this: t_size len = (t_size)(*myfile_size);
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
);										\



/*! @} */
HEADER_END
#endif
