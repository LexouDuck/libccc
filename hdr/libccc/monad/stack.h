/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/stack.h                     |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_STACK_H
#define __LIBCCC_MONAD_STACK_H
/*!@group{libccc_monad_stack}
**
**	This header defines a simple stack (FIFO) type and utility functions for it.
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
#include "libccc/monad/stack.c"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! A simple stack/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*
**	TODO document this
*/
typedef struct stack(T)
{
	t_uint	length;	//!< The amount of elements in the 'items' array
	T*		items;	//!< The pointer to the array (items can be of any one type)
}	s_stack(T);



#define foreach_s_stack_init(		_TYPE_, _VAR_, _STACK_)	
#define foreach_s_stack_exit(		_TYPE_, _VAR_, _STACK_)	
#define foreach_s_stack_loop_init(	_TYPE_, _VAR_, _STACK_)	
#define foreach_s_stack_loop_exit(	_TYPE_, _VAR_, _STACK_)	
#define foreach_s_stack_loop_incr(	_TYPE_, _VAR_, _STACK_)	



/*
** ************************************************************************** *|
**                             Basic Stack Operations                         *|
** ************************************************************************** *|
*/

// TODO Stack
// TODO Stack_New
// TODO Stack_Delete
// TODO Stack_Delete_F
// TODO Stack_Duplicate

// TODO Stack_Read

// TODO Stack_Pop
// TODO Stack_Pop_F
// TODO Stack_Push
// TODO Stack_Push_F



/*! @endgroup */
HEADER_END
#endif
