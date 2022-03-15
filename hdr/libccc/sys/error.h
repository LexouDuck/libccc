/*============================================================================*\
||                                            ______________________________  ||
||  libccc/sys/error.h                       |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_SYS_ERROR_H
#define __LIBCCC_SYS_ERROR_H
/*!@group{libccc_sys_error,10,libccc/sys/error.h}
**
**	This header defines the utility functions for error handling
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

#include "libccc/string.h"
#include "libccc/format.h"
#include "libccc/sys/io.h"

HEADER_CPP

#ifndef __LIBCCC_SYS_ERROR_T
#define __LIBCCC_SYS_ERROR_T

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#if __STDC__ >= __STDC_VERSION_C11__
typedef errno_t	t_errno;
#else
typedef int	t_errno;
#endif



//! The function pointer type for an error-handling function
typedef void (*f_ccchandler)(e_cccerror, t_char const*);



// TODO document this
#define PARSE_RETURN(VALUE) \
	{	if (dest)	*dest = (VALUE);	return (i);	}
// TODO document this
#define PRINT_RETURN(VALUE) \
	{	if (dest)	*dest = (VALUE);	return (i);	}



#endif
#ifndef __LIBCCC_SYS_ERROR_F
#define __LIBCCC_SYS_ERROR_F

/*
** ************************************************************************** *|
**                           Error globals (errno-like)                       *|
** ************************************************************************** *|
*/

//!@doc Returns a newly allocated error message from the given `errno_value`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strerror}
**	@isostd{POSIX,https://linux.die.net/man/3/strerror}
**
**	This is equivalent to the STD C `strerror()` functions (thread-safe).
**
**	@returns
**	A newly allocated string which contains the standard errno message.
*/
//!@{
t_char*							Error_STDC(int errno_value);
#define c_strerror				Error_STDC
#define c_strerror_r			Error_STDC
#define c_strerror_s			Error_STDC
#define Error_STDC_GetMessage	Error_STDC
//!@}



//!@doc Returns the latest global error code (thread-safe)
//!@{
e_cccerror			Error_Get(void);
#define c_errorget	Error_Get
//!@}

//!@doc Sets the global error code (thread-safe)
//!@{
e_cccerror			Error_Set(e_cccerror error);
#define c_errorset	Error_Set
//!@}



//!@doc Returns newly allocated error message corresponding to the given `error` number
//!@{
t_char*					Error_GetMessage(e_cccerror error);
#define c_errorgetmsg	Error_GetMessage
//!@}

//!@doc Returns newly allocated error enum item name (ie: `ERROR_UNKNOWN`)
//!@{
t_char*					Error_GetName(e_cccerror error);
#define c_errorgetname	Error_GetName
//!@}

//!@doc Returns the error code corresponding the the given error `name` (or)
//!@{
e_cccerror				Error_GetCode(t_char const* name);
#define c_errorgetcode	Error_GetCode
//!@}



//!@doc The parent function which handles any error: is called when an error check is `TRUE`
//!@{
void					Error_Handle(e_cccerror error, t_char const* funcname, t_char* message);
#define c_errorhandle	Error_Handle
//!@}

//!@doc The default error handler function (its body can be configured, see #LIBCONFIG_ERROR_DEFAULTHANDLER)
//!@{
void					Error_Handler(e_cccerror error, t_char const* message);
#define c_errorhandler	Error_Handler
//!@}



//!@doc Get the currently set handler function for the given `error` code
//!@{
f_ccchandler				Error_GetHandler(e_cccerror error);
#define c_gethandler		Error_GetHandler
//!@}

//!@doc Set the handler function to call for a certain `error` code
//!@{
void						Error_SetHandler(e_cccerror error, f_ccchandler handler);
#define c_sethandler		Error_SetHandler
//!@}

//!@doc Set the handler function for every kind of error, at once
//!@{
void						Error_SetAllHandlers(f_ccchandler handler);
#define c_setallhandlers	Error_SetAllHandlers
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
