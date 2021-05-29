/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/queue.h                     |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_QUEUE_H
#define __LIBCCC_MONAD_QUEUE_H
/*!@group{libccc_monad_queue}
** @{
**	This header defines a simple queue (LIFO) type and utility functions for it.
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

#define queue_T		CONCAT(queue, T_NAME)
#define s_queue_T	CONCAT(s_queue, T_NAME)

//! A simple queue/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*
**	TODO document this
*/
typedef struct queue_T
{
	t_uint	length;	//!< The amount of elements in the 'items' array
	T*		items;	//!< The pointer to the array (items can be of any one type)
}				s_queue_T;



#define foreach_s_queue_init(		_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_exit(		_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_loop_init(	_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_loop_exit(	_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_loop_incr(	_TYPE_, _VAR_, _QUEUE_)	



/*
** ************************************************************************** *|
**                             Basic Queue Operations                         *|
** ************************************************************************** *|
*/

// TODO Queue
// TODO Queue_New
// TODO Queue_Delete
// TODO Queue_Delete_F
// TODO Queue_Duplicate

// TODO Queue_Read

// TODO Queue_Pop
// TODO Queue_Pop_F
// TODO Queue_Push
// TODO Queue_Push_F



/*! @} */
HEADER_END
#endif
