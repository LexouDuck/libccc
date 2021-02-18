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
/*! @file libccc/pointer.h
**	@addtogroup libccc_pointer
**	@{
**	This header defines the standard memory size and pointer integer types.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

/*
**	Included to use the following std types:
**	- size_t
**	- ptrdiff_t
*/
#include <stddef.h>
/*
**	Included to use the following std types:
**	- uintmax_t
**	- uintptr_t
**	- intmax_t
**	- intptr_t
*/
#include <stdint.h>

#include "libccc_config.h"
#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	Define the common NULL pointer macros.
*/
#ifdef	NULL
#undef	NULL
#endif	//! Represents a NULL (0-value) pointer, of type 'void'
#define NULL	(void*)(0)

#ifdef	TYPED_NULL
#undef	TYPED_NULL
#endif	//! Represents a NULL pointer, of the given 'TYPE'
#define TYPED_NULL(TYPE)	(TYPE*)(0)



//! The RAM memory size type
/*!
**	This typedef is here purely for nomenclature consistency
**	(all primitive typedefs are prefixed with 't_')
*/
typedef size_t		t_size;
TYPEDEF_ALIAS(		t_size, SIZE, PRIMITIVE)

//! The pointer difference substraction result type
/*!
**	This typedef is here purely for nomenclature consistency
**	(all primitive typedefs are prefixed with 't_')
*/
typedef ptrdiff_t	t_ptrdiff;
TYPEDEF_ALIAS(		t_ptrdiff, PTRDIFF, PRIMITIVE)



//! Maximum-width signed integer type
typedef intmax_t	t_sintmax;
TYPEDEF_ALIAS(		t_sintmax, SINTMAX, PRIMITIVE)

//! Maximum-width unsigned integer type
typedef uintmax_t	t_uintmax;
TYPEDEF_ALIAS(		t_uintmax, UINTMAX, PRIMITIVE)



//! Pointer-size signed integer type
typedef intptr_t	t_sintptr;
TYPEDEF_ALIAS(		t_sintptr, SINTPTR, PRIMITIVE)

//! Pointer-size unsigned integer type
typedef uintptr_t	t_uintptr;
TYPEDEF_ALIAS(		t_uintptr, UINTPTR, PRIMITIVE)



/*
** ************************************************************************** *|
**                         Other Conversion Functions                         *|
** ************************************************************************** *|
*/

//! Get the string decimal representation of a RAM memory size integer
_MALLOC()
char*					Size_ToString(t_size value);
#define c_size_to_str	Size_ToString

//! Get the string hexadecimal representation of a RAM memory size integer
_MALLOC()
char*						Size_ToString_Hex(t_size value);
#define c_size_to_strhex	Size_ToString_Hex

//! Get the string human-readable representation of a RAM memory size integer, in short readable form, with bytes units (KB,MB,GB,etc)
_MALLOC()
char*							Size_ToString_Readable(t_size value);
#define c_size_to_str_readable	Size_ToString_Readable

//! Parse a memory-size uint from the given string
t_size					Size_FromString(char const* str);
#define c_str_to_size	Size_FromString




//! Get the string decimal representation of a pointer/address value
_MALLOC()
char*					Pointer_ToString(void const* ptr);
#define c_ptr_to_str	Pointer_ToString
//! Get the string hexadecimal representation of a pointer/address value
_MALLOC()
char*						Pointer_ToString_Hex(void const* ptr);
#define c_ptr_to_strhex		Pointer_ToString_Hex



/*! @} */
HEADER_END
#endif
