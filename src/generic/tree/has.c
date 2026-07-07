
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Tree_Has(T)(s_tree(T) const* tree, s_tree(T) const* target)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (FALSE);
	if CCCERROR((target == NULL), ERROR_NULLPOINTER, "target tree given is NULL")
		return (FALSE);
	if (Tree_Contains(T)(target, tree->value))
		return (TRUE);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		if (Tree_Has(T)(&tree->nodes[i], target))
			return (TRUE);
	}
	return (FALSE);
}

_GENERIC()
t_bool	Tree_HasOnly(T)(s_tree(T) const* tree, s_tree(T) const* target)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (FALSE);
	if CCCERROR((target == NULL), ERROR_NULLPOINTER, "target tree given is NULL")
		return (FALSE);
	if (!Tree_Contains(T)(target, tree->value))
		return (FALSE);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		if (!Tree_HasOnly(T)(&tree->nodes[i], target))
			return (FALSE);
	}
	return (TRUE);
}
