/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/array.h                     |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ARRAY_ARRAY_H
#define __LIBCCC_ARRAY_ARRAY_H
/*!@group{libccc_array_array}
** @{
**	This header defines a simple linked list type and utility functions for it.
**
**	@file
*/

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

typedef struct list	s_list;

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This struct holds an array of items which can be of any type
/*!
**	The 's_array' struct holds a `void*` pointer to the array of items, the size
**	of a single item in the array, and the total amount of items in this array.
**	As such, a s_array can hold any number of items, but they must all share the same type.
*/
typedef struct array
{
	t_size		item_count;	//!< The amount of elements in the 'items' array
	t_size		item_size;	//!< The size (in bytes) of one object in this array
	void*		items;		//!< The pointer to the array (items can be of any one type)
}				s_array;
TYPEDEF_ALIAS(	s_array, ARRAY, STRUCT)

//! A literal of an 's_array' struct which has all fields set to zero
#define ARRAY_NULL	(s_array){ .item_count = 0, .item_size = 0, .items = NULL }



#define foreach_s_array_init(		TYPE, VAR, ARRAY)	t_size VAR##_i = 0;
#define foreach_s_array_exit(		TYPE, VAR, ARRAY)	if (ARRAY && (ARRAY)->items)
#define foreach_s_array_loop_init(	TYPE, VAR, ARRAY)	TYPE VAR = ((TYPE*)(ARRAY)->items)[0]
#define foreach_s_array_loop_exit(	TYPE, VAR, ARRAY)	VAR##_i < (ARRAY)->item_count
#define foreach_s_array_loop_incr(	TYPE, VAR, ARRAY)	++VAR##_i, VAR = ((TYPE*)((t_u8*)(ARRAY)->items + VAR##_i * (ARRAY)->item_size))[0]



/*
** ************************************************************************** *|
**                            Basic Array Operations                          *|
** ************************************************************************** *|
*/

// TODO everything



/*! @} */
HEADER_END
#endif
