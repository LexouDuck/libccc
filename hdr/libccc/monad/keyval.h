/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/keyval.h                    |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_KEYVAL_H
#define __LIBCCC_MONAD_KEYVAL_H
/*!@group{libccc_monad_keyval}
** @{
**	This header defines a simple dictionary type and utility functions for it.
**
**	@file
*/

#ifndef T
#define T	void*
#endif
#ifndef T_NAME
#define T_NAME	
#endif
#ifndef T_DEFAULT
#define T_DEFAULT	NULL
#endif
#ifndef T_EQUALS
#define T_EQUALS(A, B)	((A) == (B))
#endif

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define KeyVal_T	CONCAT(KeyVal, T_NAME)
#define keyval_T	CONCAT(keyval, T_NAME)
#define s_keyval_T	CONCAT(s_keyval, T_NAME)

//! A simple key+value pair struct, used in the 's_dict' dictionary struct
/*
**	TODO document this
*/
typedef struct keyval_T
{
	char*	key;	//!< The key string associated with the `value`
	T		value;	//!< The pointer to the data for the `value`
}				s_keyval_T;



/*
** ************************************************************************** *|
**                            Basic KeyVal Operations                         *|
** ************************************************************************** *|
*/

// TODO KeyVal_New
// TODO KeyVal_Delete
// TODO KeyVal_Duplicate

// TODO KeyVal_Get
// TODO KeyVal_Set

// TODO KeyVal_Equals
// TODO KeyVal_Equals_N
// TODO KeyVal_Compare
// TODO KeyVal_Compare_N



/*! @} */
HEADER_END
#endif
