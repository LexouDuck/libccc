
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_Map(T)(s_tree(T) const* tree, T (*map)(T value))
{
	s_tree(T)*	result;
	s_tree(T)*	subtree;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return (NULL);
	result = Tree_New(T)(map(tree->value));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		subtree = Tree_Map(T)(&tree->nodes[i], map);
		if (subtree == NULL)
		{
			Tree_Free(T)(result);
			return (NULL);
		}
		// the mapped subtree is copied by value into the result (ownership is transferred),
		// so only its temporary top-level "shell" struct needs to be freed afterwards
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
