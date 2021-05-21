/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/pointer.h                         |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_POINTER_H
#define __LIBCCC_POINTER_H
/*!@group{libccc_pointer}
** @{
**	This header defines the standard memory size and pointer integer types.
**
**	@isostd{https://en.cppreference.com/w/c/types/integer}
**	@isostd{https://en.cppreference.com/w/c/types/limits}
**
**	The types defined here are aliases for all the primitive integer types
**	which have a varying (platform-dependent) amount of bits. These types
**	are all used to deal with computer memory or adresses/pointers in some way.
**
**	These `typedef`s are here purely for nomenclature consistency reasons.
**	- all primitive type aliases are prefixed with 't_'
**	- all signed integer types have names that start with `s`, ie: `sint`
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#ifndef __NOSTD__
	#include <stddef.h>
#else
	#define size_t		unsigned long long
	#define ptrdiff_t	signed long long
#endif

#ifndef __NOSTD__
	#include <stdint.h>
#else
	#define uintmax_t	unsigned long long
	#define uintptr_t	unsigned long long
	#define intmax_t	signed long long
	#define intptr_t	signed long long
#endif

#include "libccc_config.h"
#include "libccc_naming.h"
#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#ifdef	NULL
#undef	NULL
#endif
//! Represents a NULL (0-value) pointer, of type 'void'
/*!
**	@isostd{https://en.cppreference.com/w/c/types/NULL}
**
**	The `NULL` pointer is simply an integer value of zero, cast to `void*`.
*/
#define NULL	((void*)0)



//! Primitive type: The address memory size integer type
/*!
**	@isostd{https://en.cppreference.com/w/c/types/size_t}
**
**	@see
**	- Size_ToString()
**	- Size_ToString_Hex()
**	- Size_ToString_Pretty()
**	- Size_FromString()
*/
typedef size_t		t_size;
TYPEDEF_ALIAS(		t_size, SIZE, PRIMITIVE)

//! Primitive type: The pointer subtraction integer type
/*!
**	@isostd{https://en.cppreference.com/w/c/types/ptrdiff_t}
*/
typedef ptrdiff_t	t_ptrdiff;
TYPEDEF_ALIAS(		t_ptrdiff, PTRDIFF, PRIMITIVE)



//! Primitive type: Maximum-width signed integer type
/*!
**	@isostd{https://en.cppreference.com/w/cpp/types/integer}
*/
typedef intmax_t	t_sintmax;
TYPEDEF_ALIAS(		t_sintmax, SINTMAX, PRIMITIVE)

//! Primitive type: Maximum-width unsigned integer type
/*!
**	@isostd{https://en.cppreference.com/w/cpp/types/integer}
*/
typedef uintmax_t	t_uintmax;
TYPEDEF_ALIAS(		t_uintmax, UINTMAX, PRIMITIVE)



//! Primitive type: Pointer-sized signed integer type
/*!
**	@isostd{https://en.cppreference.com/w/cpp/types/integer}
*/
typedef intptr_t	t_sintptr;
TYPEDEF_ALIAS(		t_sintptr, SINTPTR, PRIMITIVE)

//! Primitive type: Pointer-sized unsigned integer type
/*!
**	@isostd{https://en.cppreference.com/w/cpp/types/integer}
*/
typedef uintptr_t	t_uintptr;
TYPEDEF_ALIAS(		t_uintptr, UINTPTR, PRIMITIVE)



#include "libccc/char.h"

/*
** ************************************************************************** *|
**                        String Conversion Functions                         *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of the given size integer `value`
_MALLOC()
t_char*					Size_ToString(t_size value);
#define c_sizetostr		Size_ToString //!< @alias{Size_ToString}

//! Get the string hexadecimal representation of the given size integer `value`
_MALLOC()
t_char*					Size_ToString_Hex(t_size value);
#define c_sizetostrhex	Size_ToString_Hex //!< @alias{Size_ToString_Hex}

//! Get the string representation of `value` in short readable form, ie: with bytes units (KB,MB,GB,etc)
_MALLOC()
t_char*							Size_ToString_Pretty(t_size value);
#define c_sizetostr_readable	Size_ToString_Pretty //!< @alias{Size_ToString_Pretty}

//! Parse a size integer value from the given string `str`
t_size					Size_FromString(t_char const* str);
#define c_strtosize		Size_FromString //!< @alias{Size_FromString}




//! Get the string decimal representation of a pointer/address value
_MALLOC()
t_char*					Pointer_ToString(void const* ptr);
#define c_ptrtostr		Pointer_ToString //!< @alias{Pointer_ToString}
//! Get the string hexadecimal representation of a pointer/address value
_MALLOC()
t_char*					Pointer_ToString_Hex(void const* ptr);
#define c_ptrtostrhex	Pointer_ToString_Hex //!< @alias{Pointer_ToString_Hex}



/*! @} */
HEADER_END
#endif
