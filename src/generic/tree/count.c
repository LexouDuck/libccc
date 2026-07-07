
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_size	Tree_Size(T)(s_tree(T) const* tree)
{
	t_size	result;

	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (0);
	result = 1; // the given node itself is counted
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		result += Tree_Size(T)(&tree->nodes[i]);
	}
	return (result);
}

_GENERIC()
t_size	Tree_Depth(T)(s_tree(T) const* tree)
{
	t_size	depth;
	t_size	result;

	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (0);
	result = 0;
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		depth = Tree_Depth(T)(&tree->nodes[i]);
		if (result < depth)
			result = depth;
	}
	return (result + 1); // a single leaf node has a depth of 1
}

_GENERIC()
t_size	Tree_Count(T)(s_tree(T) const* tree, T value)
{
	t_size	result;

	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (0);
	result = (T_EQUALS(tree->value, value) ? 1 : 0);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		result += Tree_Count(T)(&tree->nodes[i], value);
	}
	return (result);
}

_GENERIC()
t_bool	Tree_Contains(T)(s_tree(T) const* tree, T value)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (FALSE);
	if (T_EQUALS(tree->value, value))
		return (TRUE);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		if (Tree_Contains(T)(&tree->nodes[i], value))
			return (TRUE);
	}
	return (FALSE);
}
