/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/keyval.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_KEYVAL_H
#define __LIBCCC_MONAD_KEYVAL_H
/*!@group{libccc_monad_keyval}
** @{
**	This header defines a generic dictionary type and utility functions for it.
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/monad/keyval.c"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! A simple key+value pair struct, used in the 's_dict' dictionary struct
/*
**	TODO document this
*/
typedef struct keyval(T)
{
	t_char*		key;	//!< The key string associated with the `value`
	T			value;	//!< The pointer to the data for the `value`
}				s_keyval(T);



/*
** ************************************************************************** *|
**                            Basic KeyVal Operations                         *|
** ************************************************************************** *|
*/

// TODO KeyVal
// TODO KeyVal_New
// TODO KeyVal_Delete
// TODO KeyVal_Duplicate

// TODO KeyVal_Get
// TODO KeyVal_Set

// TODO KeyVal_Equals
// TODO KeyVal_Compare



/*! @} */
HEADER_END
#endif
