/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/object.h                    |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_OBJECT_H
#define __LIBCCC_MONAD_OBJECT_H
/*!@group{libccc_monad_object}
** @{
**	This header defines a generic object type and utility functions for it.
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

#include "libccc/monad/keyval.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

#define object_T	CONCAT(object, T_NAME)
#define s_object_T	CONCAT(s_object, T_NAME)

//! A dynamic object struct, stores several key-value pairs
/*
**	TODO document this
*/
typedef struct object_T
{
#if LIBCONFIG_LIST_DOUBLYLINKED
	struct object_T*	prev;	//!< The pointer to the previous item in the list (or NULL if this is the first item)
#endif
	struct object_T*	next;	//!< The pointer to the next item in the list (or NULL if this is the last item)
	s_keyval_T*			items;	//!< The fields (key-value pairs) contained within this object
}				s_object_T;



#define foreach_s_object_init(		_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_exit(		_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_loop_init(	_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_loop_exit(	_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_loop_incr(	_TYPE_, _VAR_, _OBJECT_)	



#ifndef __LIBCCC_NOFUNCTIONS__

/*
** ************************************************************************** *|
**                             Basic Object Operations                          *|
** ************************************************************************** *|
*/

// TODO Object
// TODO Object_New
// TODO Object_Delete
// TODO Object_Delete_F
// TODO Object_Duplicate
// TODO Object_Get
// TODO Object_Set
// TODO Object_Copy
// TODO Object_Sub

// TODO Object_Append
// TODO Object_Prepend
// TODO Object_Insert
// TODO Object_Remove
// TODO Object_Remove_F
// TODO Object_RemoveAll
// TODO Object_RemoveAll_F
// TODO Object_RemoveAt
// TODO Object_RemoveAt_F
// TODO Object_Replace

// TODO Object_Find
// TODO Object_Find_F
// TODO Object_Count
// TODO Object_Contains
// TODO Object_Has
// TODO Object_HasOnly
// TODO Object_Equals
// TODO Object_Equals_N
// TODO Object_Compare
// TODO Object_Compare_N

// TODO Object_Iterate
// TODO Object_Iterate_I
// TODO Object_Map
// TODO Object_Map_I
// TODO Object_Filter
// TODO Object_Filter_I

// TODO Object_Reduce ?



#endif

/*! @} */
HEADER_END
#endif
