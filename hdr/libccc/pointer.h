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
**	This header defines the common standard memory manipulation functions.
**	@addtogroup libccc/pointer
**	@{
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

//! Get the string decimal representation of a 64-bit unsigned integer
_MALLOC()
char*					Convert_Size_To_String(t_size value);
#define c_size_to_str	Convert_Size_To_String

//! Parse a memory-size uint from the given string
t_size					Convert_String_To_Size(char const* str);
#define c_str_to_size	Convert_String_To_Size

//! Get the string decimal human-readable representation of a 64-bit unsigned integer, with bytes units (KB,MB,GB,etc)
_MALLOC()
char*							Convert_Size_To_String_Readable(t_size value);
#define c_size_to_str_readable	Convert_Size_To_String_Readable



//! Get the string hexadecimal representation of a pointer/address value
_MALLOC()
char*						Convert_Pointer_To_HexString(void const* ptr);
#define c_ptr_to_strhex		Convert_Pointer_To_HexString



/*! @} */
HEADER_END
#endif
