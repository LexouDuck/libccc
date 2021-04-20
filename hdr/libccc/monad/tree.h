/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/monad/tree.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MONAD_TREE_H
#define __LIBCCC_MONAD_TREE_H
/*!@group{libccc_monad_tree}
** @{
**	This header defines a simple tree/node/leaf type and utility functions for it.
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

#ifdef	Tree_T
#undef	Tree_T
#endif
#define Tree_T		CONCAT(Tree, T_NAME)

#ifdef	tree_T
#undef	tree_T
#endif
#define tree_T		CONCAT(tree, T_NAME)

#ifdef	s_tree_T
#undef	s_tree_T
#endif
#define s_tree_T	CONCAT(s_tree, T_NAME)

//! A simple tree/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*
**	TODO document this
*/
typedef struct tree_T
{
	t_size			node_count;	//!< The amount of sub-nodes of this tree node
	struct tree_T*	nodes;		//!< The array of sub-nodes of this tree node
	T				value;		//!< The value stored in this tree node
}				s_tree_T;



#define foreach_s_tree_init(		_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_exit(		_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_loop_init(	_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_loop_exit(	_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_loop_incr(	_TYPE_, _VAR_, _TREE_)	



/*
** ************************************************************************** *|
**                             Basic Tree Operations                          *|
** ************************************************************************** *|
*/

// TODO Tree_New
// TODO Tree_Delete
// TODO Tree_Duplicate

// TODO Tree_Get
// TODO Tree_Set
// TODO Tree_Copy

// TODO Tree_Append
// TODO Tree_Prepend
// TODO Tree_Insert

// TODO Tree_Equals
// TODO Tree_Equals_N
// TODO Tree_Compare
// TODO Tree_Compare_N

// TODO Tree_Replace
// TODO Tree_Find
// TODO Tree_IndexOf

// TODO Tree_Iterate
// TODO Tree_Iterate_I
// TODO Tree_Map
// TODO Tree_Map_I
// TODO Tree_Filter
// TODO Tree_Filter_I

// TODO Tree_Reduce ?



/*! @} */
HEADER_END
#endif
