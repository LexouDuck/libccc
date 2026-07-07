
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void*	Tree_Fold(T)(s_tree(T) const* tree, void* (*f)(s_tree(T) const* node, void* acc), void* initial)
{
	void*	accumulator = initial;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (initial);
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (initial);
	// the subtree is visited in depth-first pre-order (a node is visited before its sub-nodes)
	accumulator = f(tree, accumulator);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		accumulator = Tree_Fold(T)(&tree->nodes[i], f, accumulator);
	}
	return (accumulator);
}

_GENERIC()
void*	Tree_Reduce(T)(s_tree(T) const* tree, void* (*f)(s_tree(T) const* node, void* acc))
{
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	return (Tree_Fold(T)(tree, f, NULL));
}
