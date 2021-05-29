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

//! Returns a newly allocated error message from the given `errno_value`
/*!
**	@isostd{https://en.cppreference.com/w/c/string/byte/strerror}
**
**	This is equivalent to the STD C `strerror()` functions (thread-safe).
**
**	@returns A newly allocated string which contains the standard errno message.
*/
t_char*							Error_STDC(int errno_value);
#define c_strerror				Error_STDC
#define c_strerror_r			Error_STDC
#define c_strerror_s			Error_STDC
#define Error_STDC_GetMessage	Error_STDC



//! Returns the latest global error code (thread-safe)
e_stderror	Error_Get(void);

//! Sets the global error code (thread-safe)
e_stderror	Error_Set(e_stderror error);



//! Returns newly allocated error message corresponding to the given `error` number
t_char*		Error_GetMessage(e_stderror error);

//! Returns newly allocated error enum item name (ie: `ERROR_UNKNOWN`)
t_char*		Error_GetName(e_stderror error);

//! Returns the error code corresponding the the given error `name` (or)
e_stderror	Error_GetCode(t_char const* name);



/*! @} */
HEADER_END
#endif
