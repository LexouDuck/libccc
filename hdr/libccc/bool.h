/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/bool.h                            |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_BOOL_H
#define __LIBCCC_BOOL_H
/*! @file libccc/bool.h
**	@addtogroup libccc_bool
**	@{
**	This header defines the boolean (TRUE/FALSE) primitive type and functions.
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc_config.h"
#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                             Common Definitions                             *|
** ************************************************************************** *|
*/

/*
**	Define the common useful macros for writing some pseudo-boolean syntax.
*/
#ifdef	FALSE
#undef	FALSE
#endif	//! Represents a boolean false value (0)
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif	//! Represents a boolean true value  (1)
#define TRUE	(1)

//! Primitve type: The boolean type (`TRUE` or `FALSE`)
/*!
**	@isostd https://en.cppreference.com/w/c/types/boolean
**
**	Here, we use the native (since C99) `_Bool` boolean type.
**	This type is useful because its value will always be 0 or 1, never more.
**	This means you will not have strange behaviors caused by the use of integer
**	arithmetic operations on booleans - do not assume `t_bool` works like int types.
**	NB: Conversion to `_Bool` does not work the same as conversion to other
**	integer types: `(bool)0.5` gives `1`, whereas `(int)0.5` gives `​0`​.
**
**	@see
**	- Bool_ToString()
**	- Bool_FromString()
*/
typedef _Bool		t_bool;
TYPEDEF_ALIAS(		t_bool, BOOL, PRIMITIVE)



/*
** ************************************************************************** *|
**                             String Conversions                             *|
** ************************************************************************** *|
*/

//! Get the string representation of a boolean value (TRUE or FALSE)
_MALLOC()
char*					Bool_ToString(t_bool value, t_bool uppercase);
#define c_bool_to_str	Bool_ToString

//! Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
t_bool					Bool_FromString(char const* str);
#define c_str_to_bool	Bool_FromString



/*! @} */
HEADER_END
#endif
