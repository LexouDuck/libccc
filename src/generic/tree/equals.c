
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Tree_Equals(T)(s_tree(T) const* tree1, s_tree(T) const* tree2)
{
	if (tree1 == tree2)
		return (TRUE);
	if CCCERROR((tree1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((tree2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if (!T_EQUALS(tree1->value, tree2->value))
		return (FALSE);
	if (tree1->node_count != tree2->node_count)
		return (FALSE);
	// NOTE: this check is order-sensitive: trees are ordered structures,
	// so sub-nodes are compared pairwise, in order
	for (t_size i = 0; i < tree1->node_count; ++i)
	{
		if (!Tree_Equals(T)(&tree1->nodes[i], &tree2->nodes[i]))
			return (FALSE);
	}
	return (TRUE);
}

_GENERIC()
t_bool	Tree_Equals_N(T)(s_tree(T) const* tree1, s_tree(T) const* tree2, t_size depth)
{
	if (depth == 0)
		return (TRUE); // a depth of 0 means nothing is compared
	if (tree1 == tree2)
		return (TRUE);
	if CCCERROR((tree1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((tree2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if (!T_EQUALS(tree1->value, tree2->value))
		return (FALSE);
	if (depth == 1)
		return (TRUE); // a depth of 1 means only the two root node values are compared
	if (tree1->node_count != tree2->node_count)
		return (FALSE);
	for (t_size i = 0; i < tree1->node_count; ++i)
	{
		if (!Tree_Equals_N(T)(&tree1->nodes[i], &tree2->nodes[i], depth - 1))
			return (FALSE);
	}
	return (TRUE);
}
