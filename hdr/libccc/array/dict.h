/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/dict.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ARRAY_DICT_H
#define __LIBCCC_ARRAY_DICT_H
/*! @file libccc/array/dict.h
**	This header defines a simple dictionary type and utility functions for it.
**	@addtogroup libccc/array/dict
**	@{
*/

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
typedef struct	s_keyval_
{
	char*		key;		//!< The key string associated with the 'value'
	void*		value;		//!< The pointer to the data for the 'value'
	char*		value_type;	//!< The amount of elements in the 'items' array
	t_size		value_size;	//!< The size (in bytes) of one object in this array
}				s_keyval;

//! A simple dictionary struct, stores an array of key/value pairs.
/*
**	TODO document this
*/
typedef struct	s_dict_
{
	t_size		item_count;
	s_keyval*	items;
}				s_dict;



//! A literal of an 's_dict' struct which has all fields set to zero
#define DICT_NULL	(s_dict){ .item_count = 0, .item_size = 0, .items = NULL }



#define foreach_s_dict_init(		TYPE, VAR, DICT)	
#define foreach_s_dict_init_1(		TYPE, VAR, DICT)	
#define foreach_s_dict_init_2(		TYPE, VAR, DICT)	
#define foreach_s_dict_exit(		TYPE, VAR, DICT)	
#define foreach_s_dict_loop_init(	TYPE, VAR, DICT)	
#define foreach_s_dict_loop_exit(	TYPE, VAR, DICT)	
#define foreach_s_dict_loop_incr(	TYPE, VAR, DICT)	
#define foreach_s_dict_loop_incr_1(	TYPE, VAR, DICT)	
#define foreach_s_dict_loop_incr_2(	TYPE, VAR, DICT)	



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
