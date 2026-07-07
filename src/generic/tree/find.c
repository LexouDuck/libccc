
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_Find(T)(s_tree(T) const* tree, T value)
{
	s_tree(T)*	result;

	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	// the subtree is searched in depth-first pre-order (a node is visited before its sub-nodes)
	if (T_EQUALS(tree->value, value))
		return ((s_tree(T)*)tree);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		result = Tree_Find(T)(&tree->nodes[i], value);
		if (result != NULL)
			return (result);
	}
	return (NULL);
}

_GENERIC()
s_tree(T)*	Tree_Find_F(T)(s_tree(T) const* tree, t_bool (*match)(s_tree(T) const* node))
{
	s_tree(T)*	result;

	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (NULL);
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	// the subtree is searched in depth-first pre-order (a node is visited before its sub-nodes)
	if (match(tree))
		return ((s_tree(T)*)tree);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		result = Tree_Find_F(T)(&tree->nodes[i], match);
		if (result != NULL)
			return (result);
	}
	return (NULL);
}
