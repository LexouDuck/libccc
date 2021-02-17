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
/*! @file libccc/array/tree.h
**	This header defines a simple tree/node/leaf type and utility functions for it.
**	@defgroup libccc_array_tree
**	@grouporder{33}
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

//! A simple tree leaf node struct, used in the 's_tree' tree/node/leaf struct
/*
**	TODO document this
*/
typedef struct	s_leaf_
{
	void*		value;		//!< The pointer to the data for the 'value'
	char*		value_type;	//!< The amount of elements in the 'items' array
	t_size		value_size;	//!< The size (in bytes) of one object in this array
}				s_leaf;
TYPEDEF_ALIAS(	s_leaf, LEAF, STRUCT)

#define LEAF_NULL	(s_leaf){ 0 } // TODO



//! A simple tree/node/leaf struct, stores an array of "branches" (ie: nodes).
/*
**	TODO document this
*/
typedef struct	s_tree_
{
	t_size			node_count;
	struct s_tree_*	nodes;
	void*			value;
}				s_tree;
TYPEDEF_ALIAS(	s_tree, TREE, STRUCT)

//! A literal of an 's_tree' struct which has all fields set to zero
#define TREE_NULL	(s_tree){ .node_count = 0, .nodes = 0, .value = NULL }



#define foreach_s_tree_init(		TYPE, VAR, TREE)	
#define foreach_s_tree_init_1(		TYPE, VAR, TREE)	
#define foreach_s_tree_init_2(		TYPE, VAR, TREE)	
#define foreach_s_tree_exit(		TYPE, VAR, TREE)	
#define foreach_s_tree_loop_init(	TYPE, VAR, TREE)	
#define foreach_s_tree_loop_exit(	TYPE, VAR, TREE)	
#define foreach_s_tree_loop_incr(	TYPE, VAR, TREE)	
#define foreach_s_tree_loop_incr_1(	TYPE, VAR, TREE)	
#define foreach_s_tree_loop_incr_2(	TYPE, VAR, TREE)	



/*
** ************************************************************************** *|
**                             Basic Dict Operations                          *|
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
