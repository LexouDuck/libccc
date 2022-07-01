/*============================================================================*\
||                                            ______________________________  ||
||  libccc/pointer.h                         |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_POINTER_H
#define __LIBCCC_POINTER_H
/*!@group{libccc_pointer,16,libccc/pointer.h}
**
**	This header defines the standard memory size and pointer integer types.
**
**	@isostd{C,https://en.cppreference.com/w/c/types/integer}
**	@isostd{C,https://en.cppreference.com/w/c/types/limits}
**
**	The types defined here are aliases for all the primitive integer types
**	which have a varying (platform-dependent) amount of bits. These types
**	are all used to deal with computer memory or adresses/pointers in some way.
**
**	These `typedef`s are here purely for nomenclature consistency reasons.
**	- all primitive type aliases are prefixed with 't_'
**	- all signed integer types have names that start with `s`, ie: `sint`
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stddef.h>
#else
	typedef unsigned long	size_t;
	typedef signed long	ptrdiff_t;
	#define SIZE_MAX	(size_t)-1
	#define PTRDIFF_MIN	((ptrdiff_t)(SIZE_MAX >> 1))
	#define PTRDIFF_MAX	((ptrdiff_t)((SIZE_MAX >> 1) + 1))
	#define INTMAX_MAX	((t_sintmax)+((~(t_uintmax)0) >> 1))
	#define INTMAX_MIN	((t_sintmax)-((~(t_uintmax)0) >> 1))
	#define INTPTR_MAX	((t_sintptr)+((~(t_uintptr)0) >> 1))
	#define INTPTR_MIN	((t_sintptr)-((~(t_uintptr)0) >> 1))
#endif

#ifndef __NOSTD__
	#include <stdint.h>
#else
	typedef unsigned long long	uintmax_t;
	typedef unsigned long long	uintptr_t;
	typedef signed long long	intmax_t;
	typedef signed long long	intptr_t;
#endif

#include "libccc.h"

HEADER_CPP

#ifndef __LIBCCC_POINTER_T
#define __LIBCCC_POINTER_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! Represents a NULL (0-value) pointer, of type 'void'
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/NULL}
**
**	The `NULL` pointer is simply an integer value of zero, cast to `void*`.
*/
#ifndef NULL
#define NULL	((void*)0)
#endif



//!@doc Primitive type: The memory byte size integer type
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/size_t}
**
**	@see
**	- Size_ToString()
**	- Size_ToString_Hex()
**	- Size_ToString_Pretty()
**	- Size_FromString()
*/
//!@{
typedef size_t		t_size;
TYPEDEF_ALIAS(		t_size, SIZE, PRIMITIVE)
//!@}

//!@doc Primitive type: The pointer subtraction integer type
/*!
**	@isostd{C,https://en.cppreference.com/w/c/types/ptrdiff_t}
*/
//!@{
typedef ptrdiff_t	t_ptrdiff;
TYPEDEF_ALIAS(		t_ptrdiff, PTRDIFF, PRIMITIVE)
//!@}



//!@doc Primitive type: Pointer-sized integer types
/*!
**	@isostd{C,https://en.cppreference.com/w/cpp/types/integer}
*/
//!@{
//! Pointer-sized signed integer type
typedef intptr_t	t_sintptr;
TYPEDEF_ALIAS(		t_sintptr, SINTPTR, PRIMITIVE)
//! Pointer-sized unsigned integer type
typedef uintptr_t	t_uintptr;
TYPEDEF_ALIAS(		t_uintptr, UINTPTR, PRIMITIVE)
//!@}



//!@doc Primitive type: Maximum-width integer types
/*!
**	@isostd{C,https://en.cppreference.com/w/cpp/types/integer}
*/
//!@{
//! Maximum-width signed integer type
typedef intmax_t	t_sintmax;
TYPEDEF_ALIAS(		t_sintmax, SINTMAX, PRIMITIVE)
//! Maximum-width unsigned integer type
typedef uintmax_t	t_uintmax;
TYPEDEF_ALIAS(		t_uintmax, UINTMAX, PRIMITIVE)
//!@}


// @Lexou When you'll do the `#define SIZE_ERROR ((t_size)-1)` refactor, 
// search for the string "DZ_ON_REFACTOR_OF_SIZE_ERROR" in the code and see what you need to do
#if (LIBCONFIG_UINT_ERROR == 0)

	#define SIZE_ERROR	0
	#ifndef SIZE_MAX
	#define SIZE_MAX	((t_size)-1)
	#endif

	#define UINTMAX_ERROR	0
	#ifndef UINTMAX_MAX
	#define UINTMAX_MAX	((t_uintmax)-1)
	#endif

	#define UINTPTR_ERROR	0
	#ifndef UINTPTR_MAX
	#define UINTPTR_MAX	((t_uintptr)-1)
	#endif

#else

	#define SIZE_ERROR		((t_size)-1)
	#undef	SIZE_MAX
	#define SIZE_MAX		((t_size)-2)

	#define UINTMAX_ERROR	((t_uintmax)-1)
	#undef	UINTMAX_MAX
	#define UINTMAX_MAX		((t_uintmax)-2)

	#define UINTPTR_ERROR	((t_uintptr)-1)
	#undef	UINTPTR_MAX
	#define UINTPTR_MAX		((t_uintptr)-2)

#endif



#if (LIBCONFIG_SINT_ERROR == 0)

	#define PTRDIFF_ERROR	0

	#define SINTMAX_ERROR	0

	#define SINTPTR_ERROR	0

#else

	#define PTRDIFF_ERROR	((t_ptrdiff)((~(t_size)0) >> 1) + 1))
	#undef	PTRDIFF_MAX
	#define PTRDIFF_MAX		((t_ptrdiff)((~(t_size)0) >> 1))
	#undef	PTRDIFF_MIN
	#define PTRDIFF_MIN		((t_ptrdiff)-((~(t_size)0) >> 1))

	#define SINTMAX_ERROR	((t_sintmax)((~(t_uintmax)0) >> 1) + 1))
	#undef	INTMAX_MAX
	#define INTMAX_MAX		((t_sintmax)((~(t_uintmax)0) >> 1))
	#undef	INTMAX_MIN
	#define INTMAX_MIN		((t_sintmax)-((~(t_uintmax)0) >> 1))

	#define SINTPTR_ERROR	((t_sintptr)((~(t_uintptr)0) >> 1) + 1))
	#undef	INTPTR_MAX
	#define INTPTR_MAX		((t_sintptr)((~(t_uintptr)0) >> 1))
	#undef	INTPTR_MIN
	#define INTPTR_MIN		((t_sintptr)-((~(t_uintptr)0) >> 1))

#endif

#define SINTMAX_MIN		INTMAX_MIN
#define SINTMAX_MAX		INTMAX_MAX

#define SINTPTR_MIN		INTPTR_MIN
#define SINTPTR_MAX		INTPTR_MAX



#endif
#ifndef __LIBCCC_POINTER_F
#define __LIBCCC_POINTER_F

/*
** ************************************************************************** *|
**                        String Conversion Functions                         *|
** ************************************************************************** *|
*/

//!@doc Get the string decimal representation of the given size integer `value`
/*!
**	@nonstd
*/
//!@{
_MALLOC()
t_char*					Size_ToString(t_size value);
#define c_sizetostr		Size_ToString
//!@}

//!@doc Get the string hexadecimal representation of the given size integer `value`
/*!
**	@nonstd
*/
//!@{
_MALLOC()
t_char*					Size_ToString_Hex(t_size value);
#define c_sizetostrhex	Size_ToString_Hex
//!@}

//!@doc Get the string representation of `value` in short readable form, ie: with bytes units (KB,MB,GB,etc)
/*!
**	@nonstd
*/
//!@{
_MALLOC()
t_char*							Size_ToString_Pretty(t_size value);
#define c_sizetostr_readable	Size_ToString_Pretty
//!@}



//!@doc Get the string decimal representation of a pointer/address value
/*!
**	@nonstd
*/
//!@{
_MALLOC()
t_char*					Pointer_ToString(void const* ptr);
#define c_ptrtostr		Pointer_ToString
//!@}

//!@doc Get the string hexadecimal representation of a pointer/address value
/*!
**	@nonstd
*/
//!@{
_MALLOC()
t_char*					Pointer_ToString_Hex(void const* ptr);
#define c_ptrtostrhex	Pointer_ToString_Hex
//!@}



/*
** ************************************************************************** *|
**                        String Conversion Functions                         *|
** ************************************************************************** *|
*/

// TODO define macro alias functions UIntMax_Parse() and SIntMax_Parse()



//!@doc See #t_size, UInt_Parse()
//!@{
t_size					Size_Parse(t_size *dest, t_char const* str);
#define c_sizeparse		Size_Parse
//!@}

//!@doc See #t_size, UInt_FromString()
//!@{
t_size					Size_FromString(t_char const* str);
#define c_strtosize		Size_FromString
//!@}



//!@doc See #t_ptrdiff, SInt_Parse()
//!@{
t_size					PtrDiff_Parse(t_ptrdiff *dest, t_char const* str);
#define c_ptrdiffparse	PtrDiff_Parse
//!@}

//!@doc See #t_ptrdiff, SInt_FromString()
//!@{
t_ptrdiff				PtrDiff_FromString(t_char const* str);
#define c_strtoptrdiff	PtrDiff_FromString
//!@}



//!@doc See #t_uintmax, UInt_Parse()
//!@{
t_size					UIntMax_Parse(t_uintmax *dest, t_char const* str);
#define c_uintmaxparse	UIntMax_Parse
//!@}

//!@doc See #t_uintmax, UInt_FromString()
//!@{
t_uintmax				UIntMax_FromString(t_char const* str);
#define c_strtouintmax	UIntMax_FromString
//!@}

//!@doc See #t_sintmax, SInt_Parse()
//!@{
t_size					SIntMax_Parse(t_sintmax *dest, t_char const* str);
#define c_sintmaxparse	SIntMax_Parse
//!@}

//!@doc See #t_sintmax, SInt_FromString()
//!@{
t_sintmax				SIntMax_FromString(t_char const* str);
#define c_strtosintmax	SIntMax_FromString
//!@}



//!@doc See #t_uintptr, UInt_Parse()
//!@{
t_size					UIntPtr_Parse(t_uintptr *dest, t_char const* str);
#define c_uintptrparse	UIntPtr_Parse
//!@}

//!@doc See #t_uintptr, UInt_FromString()
//!@{
t_uintptr				UIntPtr_FromString(t_char const* str);
#define c_strtouintptr	UIntPtr_FromString
//!@}

//!@doc See #t_sintptr, SInt_Parse()
//!@{
t_size					SIntPtr_Parse(t_sintptr *dest, t_char const* str);
#define c_sintptrparse	SIntPtr_Parse
//!@}

//!@doc See #t_sintptr, SInt_FromString()
//!@{
t_sintptr				SIntPtr_FromString(t_char const* str);
#define c_strtosintptr	SIntPtr_FromString
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
