/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/dict.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_DICT_H
#define __LIBCCC_MONAD_DICT_H
/*!@group{libccc_monad_dict}
** @{
**	This header defines a simple dictionary type and utility functions for it.
**
**	@file
*/

#ifndef T
#define T	void*
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

//! A simple key+value pair struct, used in the 's_dict' dictionary struct
/*
**	TODO document this
*/
typedef struct keyval
{
	char*		key;		//!< The key string associated with the `value`
	void*		value;		//!< The pointer to the data for the `value`
	t_size		value_size;	//!< The size (in bytes) of the contents of `value`
}				s_keyval;
TYPEDEF_ALIAS(	s_keyval, KEYVAL, STRUCT)

#define KEYVAL_NULL	(s_keyval){ 0 } // TODO



//! A simple dictionary struct, stores an array of key/value pairs.
/*
**	TODO document this
*/
typedef struct dict
{
	t_size		item_count;	//!< The amount of key/value pairs stored in this dictionary
	s_keyval*	items;		//!< The array of key/value pairs stored in this dictionary
}				s_dict;
TYPEDEF_ALIAS(	s_dict, DICT, STRUCT)

//! A literal of an 's_dict' struct which has all fields set to zero
#define DICT_NULL	(s_dict){ .item_count = 0, .item_size = 0, .items = NULL }



#define foreach_s_dict_init(		_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_exit(		_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_loop_init(	_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_loop_exit(	_TYPE_, _VAR_, _DICT_)	
#define foreach_s_dict_loop_incr(	_TYPE_, _VAR_, _DICT_)	



/*
** ************************************************************************** *|
**                             Basic Dict Operations                          *|
** ************************************************************************** *|
*/

// TODO Dict_New
// TODO Dict_Delete
// TODO Dict_Copy
// TODO Dict_Duplicate
// TODO Dict_Equals
// TODO Dict_Add
// TODO Dict_Get
// TODO Dict_Set
// TODO Dict_Find



/*! @} */
HEADER_END
#endif
