/*============================================================================*\
||                                            ______________________________  ||
||  libccc/generic/tree.h                    |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_GENERIC_TREE_H
#define __LIBCCC_GENERIC_TREE_H
/*!@group{libccc_generic_tree,34,libccc/generic/tree.h}
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
#include "libccc/generic/tree.c"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

//! A simple tree/node/leaf struct, stores an array of "branches" (ie: sub-nodes).
/*!
**	This struct holds a single node of an n-ary tree: each node stores a `value`
**	of type `T`, and a dynamic array of sub-nodes (stored by value, contiguously).
**	A "leaf" is simply a node whose `node_count` is `0` (and `nodes` is `NULL`).
**	There is no separate "tree" struct: any node is the root of its own subtree.
**
**	NOTE: since sub-nodes are stored by value within their parent's `nodes` array,
**	any pointer to a sub-node is only valid until the next editing operation on
**	its parent node (adding/removing a sibling may reallocate the `nodes` array).
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



#define foreach_s_tree_init(		_TYPE_, _VAR_, _TREE_)	t_size _VAR_##_i = 0;
#define foreach_s_tree_exit(		_TYPE_, _VAR_, _TREE_)	if ((void*)(_TREE_) != NULL && (_TREE_)->nodes != NULL)
#define foreach_s_tree_loop_init(	_TYPE_, _VAR_, _TREE_)	_TYPE_ _VAR_ = &(_TREE_)->nodes[_VAR_##_i]
#define foreach_s_tree_loop_exit(	_TYPE_, _VAR_, _TREE_)	(_VAR_##_i < (_TREE_)->node_count)
#define foreach_s_tree_loop_incr(	_TYPE_, _VAR_, _TREE_)	++_VAR_##_i
#define foreach_s_tree_loop_setv(	_TYPE_, _VAR_, _TREE_)	_VAR_ = (_VAR_##_i == (_TREE_)->node_count ? _VAR_ : &(_TREE_)->nodes[_VAR_##_i])



/*============================================================================*\
||                             Basic Tree Operations                          ||
\*============================================================================*/

//!@doc Creates a single leaf node (returned by value), with the given `value`
/*!
**	@returns
**	A leaf node struct (ie: `node_count` is `0` and `nodes` is `NULL`),
**	holding the given `value`. This is the usual way to construct nodes
**	which are then given to `Tree_Append()`, `Tree_Insert()`, etc.
*/
//!@{
_GENERIC()
s_tree(T)				Tree_Item(T)(T value);
#define c_treeitem(T)		Tree_Item(T)
//!@}

//!@doc Allocates a single leaf node, with the given `value`
/*!
**	@returns
**	A newly allocated leaf node, holding the given `value`,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_tree(T)*				Tree_New(T)(T value);
#define c_treenew(T)		Tree_New(T)
//!@}

//!@doc Allocates a tree node with the given `value`, and `n` leaf sub-nodes taken from variadic arguments
/*!
**	@param	value	The value for the created (root) node
**	@param	n		The amount of leaf sub-node values given as variadic arguments
**	@param	...		The values for each leaf sub-node to attach (each of type `T`)
**	@returns
**	A newly allocated tree node with `n` leaf sub-nodes,
**	or `NULL` if an error occurred.
*/
//!@{
_MALLOC()
_GENERIC()
s_tree(T)*				Tree_Create(T)(T value, t_size n, ...);
#define c_treecreate(T)		Tree_Create(T)
//!@}

//!@doc Duplicates the given `tree` (deep copy: the whole subtree structure is duplicated)
/*!
**	NOTE: the `value` fields are copied shallowly (values are caller-managed).
*/
//!@{
_MALLOC()
_GENERIC()
s_tree(T)*				Tree_Duplicate(T)(s_tree(T) const* tree);
#define c_treedup(T)		Tree_Duplicate(T)
//!@}



//!@doc Deletes every sub-node of the given `tree` node (recursively), but not the node itself
/*!
**	This is useful to clean up a tree whose root node is stored by value
**	(for example, a root node which was created with `Tree_Item()`).
*/
//!@{
_GENERIC()
void					Tree_Clear(T)(s_tree(T)* tree);
#define c_treeclear(T)		Tree_Clear(T)
//!@}

//!@doc Like `Tree_Clear()`, but also calls the given `del` function on each sub-node value
/*!
**	NOTE: the `del` function is called for the values of every *descendant* node,
**	but not for the value of the given `tree` node itself.
*/
//!@{
_GENERIC()
void					Tree_Clear_F(T)(s_tree(T)* tree, void (*del)(T value));
#define c_treefclear(T)		Tree_Clear_F(T)
//!@}

//!@doc Deletes the given `tree` node and its whole subtree (frees every node, and the struct itself)
//!@{
_GENERIC()
void					Tree_Free(T)(s_tree(T)* tree);
#define c_treefree(T)		Tree_Free(T)
//!@}

//!@doc Like `Tree_Free()`, but also calls the given `del` function on every value of the subtree
/*!
**	NOTE: the `del` function is called for the values of every node of the
**	subtree, including the value of the given `tree` node itself.
*/
//!@{
_GENERIC()
void					Tree_Free_F(T)(s_tree(T)* tree, void (*del)(T value));
#define c_treeffree(T)		Tree_Free_F(T)
//!@}

//!@doc Deletes the tree pointed to by the given address `a_tree` (and sets `*a_tree` to `NULL`)
//!@{
_GENERIC()
void					Tree_Delete(T)(s_tree(T)* *a_tree);
#define c_treedel(T)		Tree_Delete(T)
//!@}

//!@doc Like `Tree_Delete()`, but also calls the given `del` function on every value of the subtree
//!@{
_GENERIC()
void					Tree_Delete_F(T)(s_tree(T)* *a_tree, void (*del)(T value));
#define c_treefdel(T)		Tree_Delete_F(T)
//!@}



//!@doc Gets the sub-node of the given `tree` node at the given `index`
/*!
**	@returns
**	A pointer to the sub-node at the given `index` (among the direct sub-nodes
**	of the given `tree` node), or `NULL` if `index` is out of bounds.
**	NOTE: the returned pointer refers to storage held within the given `tree`:
**	it is only valid until the next editing operation on this node.
*/
//!@{
_GENERIC()
s_tree(T)*				Tree_Get(T)(s_tree(T) const* tree, t_size index);
#define c_treeget(T)		Tree_Get(T)
//!@}

//!@doc Replaces the sub-node of the given `tree` node at the given `index` with the given `node`
/*!
**	The previous sub-node at this `index` (and its whole subtree) is deleted.
**	NOTE: the given `node` is copied by value: if it has sub-nodes of its own,
**	their ownership is transferred into the tree (the caller must not reuse them).
**
**	@returns
**	A pointer to the newly placed sub-node, or `NULL` if an error occurred.
*/
//!@{
_GENERIC()
s_tree(T)*				Tree_Set(T)(s_tree(T)* tree, t_size index, s_tree(T) node);
#define c_treeset(T)		Tree_Set(T)
//!@}



/*============================================================================*\
||                            Tree Editing Operations                         ||
\*============================================================================*/

//!@doc Adds the given `node` at the end of the sub-nodes of the given `tree` node
/*!
**	NOTE: the given `node` is copied by value: if it has sub-nodes of its own,
**	their ownership is transferred into the tree (the caller must not reuse them).
**
**	@returns
**	A pointer to the newly added sub-node (within the given `tree` node),
**	or `NULL` if an error occurred. NOTE: this pointer is only valid until
**	the next editing operation on the given `tree` node.
*/
//!@{
_GENERIC()
s_tree(T)*				Tree_Append(T)(s_tree(T)* tree, s_tree(T) node);
#define c_treeappend(T)		Tree_Append(T)
//!@}

//!@doc Adds the given `node` at the beginning of the sub-nodes of the given `tree` node
//!@{
_GENERIC()
s_tree(T)*				Tree_Prepend(T)(s_tree(T)* tree, s_tree(T) node);
#define c_treeprepend(T)	Tree_Prepend(T)
//!@}

//!@doc Adds the given `node` at the given `index` of the sub-nodes of the given `tree` node
/*!
**	@param	tree	The tree node whose sub-nodes should receive the given `node`
**	@param	node	The node to insert (copied by value, ownership is transferred)
**	@param	index	The index at which to insert (from `0` to `tree->node_count` included)
**	@returns
**	A pointer to the newly inserted sub-node, or `NULL` if an error occurred.
*/
//!@{
_GENERIC()
s_tree(T)*				Tree_Insert(T)(s_tree(T)* tree, s_tree(T) node, t_size index);
#define c_treeinsert(T)		Tree_Insert(T)
//!@}



//!@doc Removes the sub-node at the given `index` of the given `tree` node (deleting its whole subtree)
//!@{
_GENERIC()
void					Tree_RemoveAt(T)(s_tree(T)* tree, t_size index);
#define c_treeremoveat(T)	Tree_RemoveAt(T)
//!@}

//!@doc Like `Tree_RemoveAt()`, but also calls the given `del` function on every value of the removed subtree
//!@{
_GENERIC()
void					Tree_RemoveAt_F(T)(s_tree(T)* tree, t_size index, void (*del)(T value));
#define c_treefremoveat(T)	Tree_RemoveAt_F(T)
//!@}

//!@doc Removes the first direct sub-node of `tree` whose value is equal to the given `value` (if any)
/*!
**	NOTE: only the *direct* sub-nodes of the given `tree` node are considered
**	(this function does not search the whole subtree recursively).
**	The removed sub-node's whole subtree is deleted along with it.
*/
//!@{
_GENERIC()
void					Tree_Remove(T)(s_tree(T)* tree, T value);
#define c_treeremove(T)		Tree_Remove(T)
//!@}

//!@doc Like `Tree_Remove()`, but also calls the given `del` function on every value of the removed subtree
//!@{
_GENERIC()
void					Tree_Remove_F(T)(s_tree(T)* tree, T value, void (*del)(T value));
#define c_treefremove(T)	Tree_Remove_F(T)
//!@}

//!@doc Removes every direct sub-node of `tree` whose value is equal to the given `value` (if any)
/*!
**	NOTE: only the *direct* sub-nodes of the given `tree` node are considered
**	(this function does not search the whole subtree recursively).
*/
//!@{
_GENERIC()
void					Tree_RemoveAll(T)(s_tree(T)* tree, T value);
#define c_treeremall(T)		Tree_RemoveAll(T)
//!@}

//!@doc Like `Tree_RemoveAll()`, but also calls the given `del` function on every value of each removed subtree
//!@{
_GENERIC()
void					Tree_RemoveAll_F(T)(s_tree(T)* tree, T value, void (*del)(T value));
#define c_treefremall(T)	Tree_RemoveAll_F(T)
//!@}



/*============================================================================*\
||                            Tree Checking Operations                        ||
\*============================================================================*/

//!@doc Returns the total amount of nodes in the given `tree` (including the given node itself)
//!@{
_GENERIC()
t_size					Tree_Size(T)(s_tree(T) const* tree);
#define c_treesize(T)		Tree_Size(T)
//!@}

//!@doc Returns the depth of the given `tree` (a single leaf node has a depth of `1`)
//!@{
_GENERIC()
t_size					Tree_Depth(T)(s_tree(T) const* tree);
#define c_treedepth(T)		Tree_Depth(T)
//!@}



//!@doc Finds the first node of the given `tree` whose value is equal to the given `value`
/*!
**	The subtree is searched in depth-first pre-order (a node is visited
**	before its sub-nodes), starting with the given `tree` node itself.
**
**	@returns
**	A pointer to the first matching node, or `NULL` if no node matches.
*/
//!@{
_GENERIC()
s_tree(T)*				Tree_Find(T)(s_tree(T) const* tree, T value);
#define c_treefind(T)		Tree_Find(T)
//!@}

//!@doc Finds the first node of the given `tree` which matches the given `match` function
/*!
**	The subtree is searched in depth-first pre-order (a node is visited
**	before its sub-nodes), starting with the given `tree` node itself.
*/
//!@{
_GENERIC()
s_tree(T)*				Tree_Find_F(T)(s_tree(T) const* tree, t_bool (*match)(s_tree(T) const* node));
#define c_treeffind(T)		Tree_Find_F(T)
//!@}



//!@doc Returns the amount of nodes of `tree` whose value is equal to the given `value` (searched recursively)
//!@{
_GENERIC()
t_size					Tree_Count(T)(s_tree(T) const* tree, T value);
#define c_treecount(T)		Tree_Count(T)
//!@}

//!@doc Checks whether any node of the given `tree` has a value equal to the given `value` (searched recursively)
//!@{
_GENERIC()
t_bool					Tree_Contains(T)(s_tree(T) const* tree, T value);
#define c_treecontains(T)	Tree_Contains(T)
//!@}

//!@doc Checks whether any value of the given `tree` is present in the given `target` tree
//!@{
_GENERIC()
t_bool					Tree_Has(T)(s_tree(T) const* tree, s_tree(T) const* target);
#define c_treehas(T)		Tree_Has(T)
//!@}

//!@doc Checks whether every value of the given `tree` is present in the given `target` tree
//!@{
_GENERIC()
t_bool					Tree_HasOnly(T)(s_tree(T) const* tree, s_tree(T) const* target);
#define c_treehasonly(T)	Tree_HasOnly(T)
//!@}



//!@doc Checks whether the two given trees are equal (same structure, and equal values for each node)
/*!
**	NOTE: this check is order-sensitive: trees are ordered structures, so two
**	nodes whose sub-nodes hold the same values in a different order are NOT equal.
*/
//!@{
_GENERIC()
t_bool					Tree_Equals(T)(s_tree(T) const* tree1, s_tree(T) const* tree2);
#define c_treeequ(T)		Tree_Equals(T)
//!@}

//!@doc Like `Tree_Equals()`, but only compares nodes up to the given `depth`
/*!
**	@param	depth	The maximum depth to compare: `1` compares only the two root
**					node values, `2` also compares their direct sub-nodes, etc.
**					(if `depth` is `0`, nothing is compared: always returns `TRUE`)
*/
//!@{
_GENERIC()
t_bool					Tree_Equals_N(T)(s_tree(T) const* tree1, s_tree(T) const* tree2, t_size depth);
#define c_treeequn(T)		Tree_Equals_N(T)
//!@}



/*============================================================================*\
||                           Tree Functional Operations                       ||
\*============================================================================*/

//!@doc Iterates upon each node of the given `tree`, calling the given function `f` for each
/*!
**	The subtree is visited in depth-first pre-order (a node is visited
**	before its sub-nodes), starting with the given `tree` node itself.
*/
//!@{
_GENERIC()
void					Tree_Iterate(T)(s_tree(T)* tree, void (*f)(s_tree(T)* node));
#define c_treeiter(T)		Tree_Iterate(T)
//!@}

//!@doc Like `Tree_Iterate()`, but the given function `f` also receives the current node depth
/*!
**	NOTE: the given `tree` node itself is visited with a depth of `0`,
**	its direct sub-nodes with a depth of `1`, and so on.
*/
//!@{
_GENERIC()
void					Tree_Iterate_D(T)(s_tree(T)* tree, void (*f)(s_tree(T)* node, t_size depth));
#define c_treediter(T)		Tree_Iterate_D(T)
//!@}



//!@doc Creates a new tree with the same structure as `tree`, and values mapped by the given `map` function
//!@{
_MALLOC()
_GENERIC()
s_tree(T)*				Tree_Map(T)(s_tree(T) const* tree, T (*map)(T value));
#define c_treemap(T)		Tree_Map(T)
//!@}

//!@doc Creates a new tree, with only the nodes of `tree` whose values match the given `filter` function
/*!
**	NOTE: when a node does not match the given `filter` function, its whole
**	subtree is pruned along with it (its sub-nodes are not reattached).
**	If the given `tree` root node itself does not match, `NULL` is returned.
*/
//!@{
_MALLOC()
_GENERIC()
s_tree(T)*				Tree_Filter(T)(s_tree(T) const* tree, t_bool (*filter)(T value));
#define c_treefilter(T)		Tree_Filter(T)
//!@}



//!@doc Runs the given function `f` on each node of `tree` (in pre-order), accumulating into a single result
/*!
**	The accumulator starts as `NULL` (use `Tree_Fold()` to give an `initial` value).
*/
//!@{
_GENERIC()
void*					Tree_Reduce(T)(s_tree(T) const* tree, void* (*f)(s_tree(T) const* node, void* acc));
#define c_treereduce(T)		Tree_Reduce(T)
//!@}

//!@doc Like `Tree_Reduce()`, but the accumulator starts with the given `initial` value
//!@{
_GENERIC()
void*					Tree_Fold(T)(s_tree(T) const* tree, void* (*f)(s_tree(T) const* node, void* acc), void* initial);
#define c_treefold(T)		Tree_Fold(T)
//!@}



/*! @endgroup */
HEADER_END
#endif
