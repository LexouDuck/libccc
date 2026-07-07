
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_Get(T)(s_tree(T) const* tree, t_size index)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	if CCCERROR((index >= tree->node_count), ERROR_INDEX2LARGE,
		"index given (" SF_SIZE ") is beyond the amount of sub-nodes (" SF_SIZE ")", index, tree->node_count)
		return (NULL);
	return (&tree->nodes[index]);
}

_GENERIC()
s_tree(T)*	Tree_Set(T)(s_tree(T)* tree, t_size index, s_tree(T) node)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	if CCCERROR((index >= tree->node_count), ERROR_INDEX2LARGE,
		"index given (" SF_SIZE ") is beyond the amount of sub-nodes (" SF_SIZE ")", index, tree->node_count)
		return (NULL);
	// the previous sub-node at this index (and its whole subtree) is deleted
	Tree_Clear(T)(&tree->nodes[index]);
	tree->nodes[index] = node;
	return (&tree->nodes[index]);
}
