/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/array/tree.h                      |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_ARRAY_TREE_H
#define __LIBCCC_ARRAY_TREE_H
/*!@group{libccc_array_tree}
** @{
**	This header defines a simple tree/node/leaf type and utility functions for it.
**
**	@file
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

//! A simple tree/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*
**	TODO document this
*/
typedef struct tree
{
	t_size			node_count;	//!< The amount of sub-nodes of this tree node
	struct tree*	nodes;		//!< The array of sub-nodes of this tree node
	void*			value;		//!< The value stored in this tree node
	t_size			value_size;	//!< The size (in bytes) of `value`
}				s_tree;
TYPEDEF_ALIAS(	s_tree, TREE, STRUCT)

//! A literal of an 's_tree' struct which has all fields set to zero
#define TREE_NULL	(s_tree){ .node_count = 0, .nodes = 0, .value = NULL }



#define foreach_s_tree_init(		TYPE, VAR, TREE)	
#define foreach_s_tree_exit(		TYPE, VAR, TREE)	
#define foreach_s_tree_loop_init(	TYPE, VAR, TREE)	
#define foreach_s_tree_loop_exit(	TYPE, VAR, TREE)	
#define foreach_s_tree_loop_incr(	TYPE, VAR, TREE)	



/*
** ************************************************************************** *|
**                             Basic Tree Operations                          *|
** ************************************************************************** *|
*/

// TODO Tree_New
// TODO Tree_Delete
// TODO Tree_Copy
// TODO Tree_Duplicate
// TODO Tree_Equals
// TODO Tree_Add
// TODO Tree_Get
// TODO Tree_Set
// TODO Tree_Find



/*! @} */
HEADER_END
#endif
