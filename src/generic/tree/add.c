
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_Insert(T)(s_tree(T)* tree, s_tree(T) node, t_size index)
{
	s_tree(T)*	nodes;

	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	if CCCERROR((index > tree->node_count), ERROR_INDEX2LARGE,
		"index given (" SF_SIZE ") is beyond the amount of sub-nodes (" SF_SIZE ")", index, tree->node_count)
		return (NULL);
	// NOTE: Memory_Reallocate() does not accept a NULL pointer (unlike standard realloc)
	if (tree->nodes == NULL)
		nodes = (s_tree(T)*)Memory_Allocate((tree->node_count + 1) * sizeof(s_tree(T)));
	else
		nodes = (s_tree(T)*)Memory_Reallocate(tree->nodes, (tree->node_count + 1) * sizeof(s_tree(T)));
	if CCCERROR((nodes == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	tree->nodes = nodes;
	for (t_size i = tree->node_count; i > index; --i)
	{
		tree->nodes[i] = tree->nodes[i - 1];
	}
	tree->nodes[index] = node;
	tree->node_count += 1;
	return (&tree->nodes[index]);
}

_GENERIC()
s_tree(T)*	Tree_Append(T)(s_tree(T)* tree, s_tree(T) node)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	return (Tree_Insert(T)(tree, node, tree->node_count));
}

_GENERIC()
s_tree(T)*	Tree_Prepend(T)(s_tree(T)* tree, s_tree(T) node)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	return (Tree_Insert(T)(tree, node, 0));
}
