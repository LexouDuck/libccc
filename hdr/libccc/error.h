/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_error.h                           |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ERROR_H
#define __LIBCCC_ERROR_H
/*! @file libccc_error.h
**	@addtogroup libccc_error
**	@{
**	This header defines the utility functions for error handling
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_define.h"
#include "libccc/char.h"
#include "libccc/sys/io.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                           Error globals (errno-like)                       *|
** ************************************************************************** *|
*/


//! The "get error" function, to be used after getting an unsatisfactory result return.
/*!
**	This function can be used for analysing failed parses.
**	This returns a pointer to the parse error location in the given KVT string.
**	You'll probably need to look a few chars back to make sense of it.
**	Defined when KVT_Parse() returns 0.
**	Otherwise, NULL when KVT_Parse() succeeds.
*/
e_stderror		Error_Get(void);

//! Sets the current 'errno' global
e_stderror		Error_Set(e_stderror error);



//! Returns the (string constant) error message corresponding to the given `error` number
t_char const*	Error_GetMessage(e_stderror error);

//! Returns the (string constant) error enum item name (ie: `ERROR_UNKNOWN`)
t_char const*	Error_GetName(e_stderror error);

//! Returns the error code corresponding the the given error `name` (or)
e_stderror		Error_GetCode(t_char const* name);



/*! @} */
HEADER_END
#endif
