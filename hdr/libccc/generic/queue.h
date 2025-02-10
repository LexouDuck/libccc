/*============================================================================*\
||                                            ______________________________  ||
||  libccc/generic/queue.h                   |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_GENERIC_QUEUE_H
#define __LIBCCC_GENERIC_QUEUE_H
/*!@group{libccc_generic_queue,36,libccc/generic/queue.h}
**
**	This header defines a simple queue (LIFO) type and utility functions for it.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/generic/queue.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! A simple queue/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*
**	TODO document this
*/
struct queue(T)
{
	t_uint	length;	//!< The amount of elements in the 'items' array
	T*		items;	//!< The pointer to the array (items can be of any one type)
};
typedef struct queue(T)	s_queue(T);
#ifndef NOTYPEDEF // used to avoid type redefinitions
#endif



#define foreach_s_queue_init(		_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_exit(		_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_loop_init(	_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_loop_exit(	_TYPE_, _VAR_, _QUEUE_)	
#define foreach_s_queue_loop_incr(	_TYPE_, _VAR_, _QUEUE_)	



/*============================================================================*\
||                             Basic Queue Operations                         ||
\*============================================================================*/

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



/*! @endgroup */
HEADER_END
#endif
