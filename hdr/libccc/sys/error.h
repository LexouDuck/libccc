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



//! This struct holds all relevant information for one error type
typedef struct error_info
{
	int				code;
	t_char const*	name;
	t_char const*	message;
}	s_error_info;



//! The function pointer type for an error-handling function
typedef void (*f_ccchandler)(e_cccerror error, t_char const* funcname, t_char const* message);
//! A struct which holds an association of an error handler function, and its corresponding error code
typedef struct ccchandler
{
	e_cccerror		code;
	f_ccchandler	handler;
}	s_ccchandler;


// TODO document this
#define PARSE_RETURN(VALUE) \
	{	if (dest)	*dest = (VALUE);	return (i);	}


#endif
#ifndef __LIBCCC_SYS_ERROR_F
#define __LIBCCC_SYS_ERROR_F

/*
** ************************************************************************** *|
**                       libccc error handling functions                      *|
** ************************************************************************** *|
*/

//!@doc The root-most error handling-function: used in `if ()` statements, to check and handle errors
//!@{
t_bool Error_If(e_cccerror errorcode,
    t_bool shouldhandle,
    char const* funcname,
    char const* format, ...);
#define c_error		Error_If
//!@}

//!@doc The parent function which handles any error: is called when an error check evaluates to `TRUE`
//!@{
void					Error_Handle(e_cccerror error, t_char const* funcname, t_char* message);
#define c_errorhandle	Error_Handle
//!@}

//!@doc The default error handler function (its body can be configured, see #LIBCONFIG_ERROR_DEFAULTHANDLER)
//!@{
void					Error_Handler(e_cccerror error, t_char const* funcname, t_char const* message);
#define c_errorhandler	Error_Handler
//!@}



//!@doc Get the currently set handler function for the given `error` code
//!@{
f_ccchandler				Error_GetHandler(e_cccerror error);
#define c_geterrhandler		Error_GetHandler
//!@}

//!@doc Set the handler function to call for a certain `error` code
//!@{
void						Error_SetHandler(e_cccerror error, f_ccchandler handler);
#define c_seterrhandler		Error_SetHandler
//!@}

//!@doc Set the handler function for every kind of error, at once
//!@{
void						Error_SetAllHandlers(f_ccchandler handler);
#define c_setallerrhandlers	Error_SetAllHandlers
//!@}



/*
** ************************************************************************** *|
**                         custom error util functions                        *|
** ************************************************************************** *|
*/

#ifndef LIBCONFIG_ERROR_DEFAULTFUNCTIONS
#define LIBCONFIG_ERROR_DEFAULTFUNCTIONS	CCC
#endif



#define Error_Message		CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_Message)
#define c_errormsg			Error_Message

#define Error_GetMessage	CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_GetMessage)
#define c_errorsmsg			Error_GetMessage

#define Error_Name			CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_Name)
#define c_errorname			Error_Name

#define Error_GetName		CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_GetName)
#define c_errorsname		Error_GetName

#define Error_Code			CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_Code)
#define c_errorcode			Error_Code



#define Error_Get	CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_Get)
#define c_errorget	Error_Get

#define Error_Set	CONCAT(CONCAT(Error_,LIBCONFIG_ERROR_DEFAULTFUNCTIONS),_Set)
#define c_errorset	Error_Set



/*
** ************************************************************************** *|
**                         libccc error util functions                        *|
** ************************************************************************** *|
*/

//!@doc Returns newly allocated error message corresponding to the given `error` number
//!@{
t_char const*				Error_CCC_Message(e_cccerror error);
#define c_cccerrormsg		Error_CCC_Message
//!@}

//!@doc Returns newly allocated error message corresponding to the given `error` number
//!@{
t_char*						Error_CCC_GetMessage(e_cccerror error);
#define c_cccerrorsmsg		Error_CCC_GetMessage
//!@}



//!@doc Returns newly allocated error enum item name (ie: `ERROR_UNKNOWN`)
//!@{
t_char const*				Error_CCC_Name(e_cccerror error);
#define c_cccerrorname		Error_CCC_Name
//!@}

//!@doc Returns newly allocated error enum item name (ie: `ERROR_UNKNOWN`)
//!@{
t_char*						Error_CCC_GetName(e_cccerror error);
#define c_cccerrorsname		Error_CCC_GetName
//!@}



//!@doc Returns the error code corresponding the the given error `name` (or)
//!@{
e_cccerror					Error_CCC_Code(t_char const* name);
#define c_cccerrorcode		Error_CCC_Code
//!@}



//!@doc Returns the latest global error code (thread-safe)
//!@{
e_cccerror				Error_CCC_Get(void);
#define c_cccerrorget	Error_CCC_Get
//!@}

//!@doc Sets the global error code (thread-safe)
//!@{
e_cccerror				Error_CCC_Set(e_cccerror error);
#define c_cccerrorset	Error_CCC_Set
//!@}



/*
** ************************************************************************** *|
**                        Error util functions: std errno                     *|
** ************************************************************************** *|
*/

//!@doc Returns the error message for the given `error`
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/string/byte/strerror}
**	@isostd{POSIX,https://linux.die.net/man/3/strerror}
**
**	This is equivalent to the STD C `strerror()` function (not thread-safe).
**
**	@returns
**	A global constant string which contains the standard errno message.
*/
//!@{
t_char const*				Error_STD_Message(t_errno error);
#define c_stderrormsg		Error_STD_Message
#define c_strerror			Error_STD_Message
//!@}

//!@doc Returns a newly allocated error message from the given `error`
/*!
**	@see Error_Message_STD
**
**	@returns
**	A newly allocated string which contains the standard errno message.
*/
//!@{
t_char*						Error_STD_GetMessage(t_errno error);
#define c_stderrorsmsg		Error_STD_GetMessage
#define c_strerror_r		Error_STD_GetMessage
#define c_strerror_s		Error_STD_GetMessage
//!@}



//!@doc Returns newly allocated error enum item name (ie: `ERROR_UNKNOWN`)
//!@{
t_char const*				Error_STD_Name(t_errno error);
#define c_stderrorname		Error_STD_Name
//!@}

//!@doc Returns newly allocated error enum item name (ie: `ERROR_UNKNOWN`)
//!@{
t_char*						Error_STD_GetName(t_errno error);
#define c_stderrorsname		Error_STD_GetName
//!@}



//!@doc Returns the error code corresponding the the given error `name` (or)
//!@{
t_errno						Error_STD_Code(t_char const* name);
#define c_stderrorcode		Error_STD_Code
//!@}



//!@doc Returns the latest global error code (thread-safe)
//!@{
t_errno					Error_STD_Get(void);
#define c_stderrorget	Error_STD_Get
//!@}

//!@doc Sets the global error code (thread-safe)
//!@{
t_errno					Error_STD_Set(t_errno error);
#define c_stderrorset	Error_STD_Set
//!@}



#endif

/*! @endgroup */
HEADER_END
#endif
