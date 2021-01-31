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
**	This header defines all the primitive types and common macros to use.
**	@addtogroup libccc/bool
**	@{
*/

/*
** ************************************************************************** *|
**                                 Includes                                   *|
** ************************************************************************** *|
*/

#include "libccc.h"

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

//! The primitive `bool` boolean type
/*!
**	Here, we use the native (from C99 onwards) '_Bool' type.
**	This type is useful because its value will always be 0 or 1, never more.
*/
typedef _Bool		t_bool;



/*
** ************************************************************************** *|
**                         Primitive Type Conversions                         *|
** ************************************************************************** *|
*/

//! Get the string representation of a boolean value (TRUE or FALSE)
char*					Convert_Bool_To_String(t_bool value, t_bool uppercase);
#define c_bool_to_str	Convert_Bool_To_String

//! Parse a boolean value from the given string (can be 1/0/TRUE/FALSE/true/false)
t_bool					Convert_String_To_Bool(char const* str);
#define c_str_to_bool	Convert_String_To_Bool



/*! @} */
HEADER_END
#endif
