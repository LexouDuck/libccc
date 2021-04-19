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
**	This header defines a dynamic object type and utility functions for it.
**
**	@file
*/

#ifndef T
#define T	void*
#endif

#ifndef TYPE
#define TYPE	
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

#ifdef	object_T
#undef	object_T
#endif
#define object_T	CONCAT(object, TYPE)

#ifdef	s_object_T
#undef	s_object_T
#endif
#define s_object_T	CONCAT(s_object, TYPE)

//! A dynamic object struct, stores several key-value pairs
/*
**	TODO document this
*/
typedef struct object_T
{
//	struct object_T*	prev;	//!< The pointer to the previous item in the list (or NULL if this is the first item)
	struct object_T*	next;	//!< The pointer to the next item in the list (or NULL if this is the last item)
	s_keyval_T*			items;	//!< The fields (key-value pairs) contained within this object
}				s_object_T;
TYPEDEF_ALIAS(	s_object_T, OBJECT, STRUCT)



#define foreach_s_object_init(		_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_exit(		_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_loop_init(	_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_loop_exit(	_TYPE_, _VAR_, _OBJECT_)	
#define foreach_s_object_loop_incr(	_TYPE_, _VAR_, _OBJECT_)	



/*
** ************************************************************************** *|
**                             Basic Object Operations                          *|
** ************************************************************************** *|
*/

// TODO Object_New
// TODO Object_Delete
// TODO Object_Duplicate

// TODO Object_Get
// TODO Object_Set
// TODO Object_Copy
// TODO Object_Sub

// TODO Object_Append
// TODO Object_Prepend
// TODO Object_Insert
// TODO Object_Remove
// TODO Object_RemoveAll
// TODO Object_Replace

// TODO Object_Find
// TODO Object_IndexOf

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



/*! @} */
HEADER_END
#endif
