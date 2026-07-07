
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_Filter(T)(s_tree(T) const* tree, t_bool (*filter)(T value))
{
	s_tree(T)*	result;
	s_tree(T)*	subtree;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	// NOTE: if the given root node itself does not match, `NULL` is returned (with no error)
	if (!filter(tree->value))
		return (NULL);
	result = Tree_New(T)(tree->value);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		// when a sub-node does not match, its whole subtree is pruned along with it
		if (!filter(tree->nodes[i].value))
			continue;
		subtree = Tree_Filter(T)(&tree->nodes[i], filter);
		if (subtree == NULL)
		{
			Tree_Free(T)(result);
			return (NULL);
		}
		if (Tree_Append(T)(result, *subtree) == NULL)
		{
			Tree_Free(T)(subtree);
			Tree_Free(T)(result);
			return (NULL);
		}
		Memory_Free(subtree);
	}
	return (result);
}
