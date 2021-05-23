/*============================================================================*/
/*                                            ______________________________  */
/*  libccc_errors.h                          |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ERRORS_H
#define __LIBCCC_ERRORS_H
/*! @file libccc_errors.h
**	@addtogroup libccc_errors
**	@{
**	This header defines all the primitive types and common macros to use.
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc_define.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                             Error handling logic                           *|
** ************************************************************************** *|
*/

//! These macros allow you to configure how libccc handles exceptions/error cases.
/*!
**	These macro functions determine how exception cases are to be handled by libccc.
**	You may change the logic here (to implement custom exception handling for example).
*/
//!@{

//! TODO configurable IO error handling

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_NULLPOINTER(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_ALLOCFAILURE(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_INVALIDENUM(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_INDEX2SMALL(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_INDEX2LARGE(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_LENGTH2SMALL(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_LENGTH2LARGE(...) \
	IO_Output_Format(__VA_ARGS__);

//! Set this macro's value to nothing to deactivate this kind of error handling
#define LIBCONFIG_HANDLE_ERROR_PARSINGERROR(...) \
	IO_Output_Format(__VA_ARGS__);

//!@}

//! The file to include in source files which use `HANDLE_ERROR()`
#define LIBCONFIG_HANDLE_INCLUDE	"libccc/sys/io.h"



//! These macros allow you to configure how libccc handles exceptions/error cases.
/*!
**	These "plural-named" can be used to activate or deactivate exception handling at will.
*/
//!@{
#define HANDLE_ERRORS_ALLOCFAILURE
#define HANDLE_ERRORS_NULLPOINTER
#define HANDLE_ERRORS_INVALIDENUM
#define HANDLE_ERRORS_INDEX2SMALL
#define HANDLE_ERRORS_INDEX2LARGE
#define HANDLE_ERRORS_LENGTH2SMALL
#define HANDLE_ERRORS_LENGTH2LARGE
#define HANDLE_ERRORS_PARSINGERROR
//!@}
//! Comment out this `#define` to deactivate all error handling (not recommended)
#define HANDLE_ERRORS
#ifndef HANDLE_ERRORS
#define HANDLE_ERROR(ERRORTYPE, CONDITION, ...) 
#else
#define HANDLE_ERROR(ERRORTYPE, CONDITION, ...) \
	if (CONDITION)					\
	{								\
		HANDLE_ERROR_##ERRORTYPE()	\
		__VA_ARGS__					\
	}
#endif

#define HANDLE_ERROR_ALLOCFAILURE()	LIBCONFIG_HANDLE_ERROR_ALLOCFAILURE("%s -> %s", __func__, "Allocation failure")
#define HANDLE_ERROR_NULLPOINTER()	LIBCONFIG_HANDLE_ERROR_NULLPOINTER ("%s -> %s", __func__, "Invalid arg: null pointer")
#define HANDLE_ERROR_INVALIDENUM()	LIBCONFIG_HANDLE_ERROR_INVALIDENUM ("%s -> %s", __func__, "Invalid arg: enum out of bounds")
#define HANDLE_ERROR_INDEX2SMALL()	LIBCONFIG_HANDLE_ERROR_INDEX2SMALL ("%s -> %s", __func__, "Invalid arg: index too large")
#define HANDLE_ERROR_INDEX2LARGE()	LIBCONFIG_HANDLE_ERROR_INDEX2LARGE ("%s -> %s", __func__, "Invalid arg: index too small")
#define HANDLE_ERROR_LENGTH2SMALL()	LIBCONFIG_HANDLE_ERROR_LENGTH2SMALL("%s -> %s", __func__, "Invalid arg: length too small")
#define HANDLE_ERROR_LENGTH2LARGE()	LIBCONFIG_HANDLE_ERROR_LENGTH2LARGE("%s -> %s", __func__, "Invalid arg: length too large")
#define HANDLE_ERROR_PARSINGERROR()	LIBCONFIG_HANDLE_ERROR_PARSINGERROR("%s -> %s", __func__, "Parsing error")



/*
** ************************************************************************** *|
**                           Error codes for libccc                           *|
** ************************************************************************** *|
*/

typedef enum stderror
{
	ERROR_NONE   = 0,
	ENUMLENGTH_ERROR,
}		e_stderror;



/*! @} */
HEADER_END
#endif
