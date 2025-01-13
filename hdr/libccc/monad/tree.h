/*============================================================================*\
||                                            ______________________________  ||
||  libccc/monad/tree.h                      |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MONAD_TREE_H
#define __LIBCCC_MONAD_TREE_H
/*!@group{libccc_monad_tree,34,libccc/monad/tree.h}
**
**	This header defines a simple tree/node/leaf type and utility functions for it.
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/bool.h"
#include "libccc/int.h"
#include "libccc/pointer.h"

HEADER_CPP

//! set up generic declaration macros, to have `mygeneric(T)` syntax
#undef	T
#define	T	T_TYPE
#include "libccc/monad/tree.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! A simple tree/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*
**	TODO document this
*/
struct tree(T)
{
	t_size			node_count;	//!< The amount of sub-nodes of this tree node
	struct tree(T)*	nodes;		//!< The array of sub-nodes of this tree node
	T				value;		//!< The value stored in this tree node
};
#ifndef NOTYPEDEF // used to avoid type redefinitions
typedef struct tree(T)	s_tree(T);
#endif



#define foreach_s_tree_init(		_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_exit(		_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_loop_init(	_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_loop_exit(	_TYPE_, _VAR_, _TREE_)	
#define foreach_s_tree_loop_incr(	_TYPE_, _VAR_, _TREE_)	



/*============================================================================*\
||                             Basic Tree Operations                          ||
\*============================================================================*/

// TODO Tree
// TODO Tree_New
// TODO Tree_Delete
// TODO Tree_Delete_F
// TODO Tree_Duplicate
// TODO Tree_Get
// TODO Tree_Set
// TODO Tree_Copy

// TODO Tree_Append
// TODO Tree_Prepend
// TODO Tree_Insert
// TODO Tree_Remove
// TODO Tree_Remove_F
// TODO Tree_RemoveAll
// TODO Tree_RemoveAll_F
// TODO Tree_RemoveAt
// TODO Tree_RemoveAt_F
// TODO Tree_Replace

// TODO Tree_Find
// TODO Tree_Find_F
// TODO Tree_Count
// TODO Tree_Contains
// TODO Tree_Has
// TODO Tree_HasOnly
// TODO Tree_Equals
// TODO Tree_Equals_N
// TODO Tree_Compare
// TODO Tree_Compare_N

// TODO Tree_Iterate
// TODO Tree_Iterate_I
// TODO Tree_Map
// TODO Tree_Map_I
// TODO Tree_Filter
// TODO Tree_Filter_I

// TODO Tree_Reduce ?



/*! @endgroup */
HEADER_END
#endif
