
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Tree_Iterate(T)(s_tree(T)* tree, void (*f)(s_tree(T)* node))
{
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	// the subtree is visited in depth-first pre-order (a node is visited before its sub-nodes)
	f(tree);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		Tree_Iterate(T)(&tree->nodes[i], f);
	}
}



//! (internal recursive helper for Tree_Iterate_D, suffixed by instantiated type name)
#define __Tree_IterateDepth	CONCAT(__Tree_IterateDepth_, T_NAME)

static
void	__Tree_IterateDepth(s_tree(T)* tree, void (*f)(s_tree(T)* node, t_size depth), t_size depth)
{
	f(tree, depth);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		__Tree_IterateDepth(&tree->nodes[i], f, depth + 1);
	}
}

_GENERIC()
void	Tree_Iterate_D(T)(s_tree(T)* tree, void (*f)(s_tree(T)* node, t_size depth))
{
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	// the given node itself is visited with a depth of 0, its direct sub-nodes with 1, and so on
	__Tree_IterateDepth(tree, f, 0);
}

#undef __Tree_IterateDepth
