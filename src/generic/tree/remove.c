
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Tree_RemoveAt(T)(s_tree(T)* tree, t_size index)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	if CCCERROR((index >= tree->node_count), ERROR_INDEX2LARGE,
		"index given (" SF_SIZE ") is beyond the amount of sub-nodes (" SF_SIZE ")", index, tree->node_count)
		return;
	Tree_Clear(T)(&tree->nodes[index]); // the removed sub-node's whole subtree is deleted with it
	tree->node_count -= 1;
	if (tree->node_count == 0)
	{
		Memory_Free(tree->nodes);
		tree->nodes = NULL;
		return;
	}
	for (t_size i = index; i < tree->node_count; ++i)
	{
		tree->nodes[i] = tree->nodes[i + 1];
	}
}

_GENERIC()
void	Tree_RemoveAt_F(T)(s_tree(T)* tree, t_size index, void (*del)(T value))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	if CCCERROR((index >= tree->node_count), ERROR_INDEX2LARGE,
		"index given (" SF_SIZE ") is beyond the amount of sub-nodes (" SF_SIZE ")", index, tree->node_count)
		return;
	// `del` is called for every value of the removed subtree, including the removed sub-node's own
	del(tree->nodes[index].value);
	Tree_Clear_F(T)(&tree->nodes[index], del);
	tree->node_count -= 1;
	if (tree->node_count == 0)
	{
		Memory_Free(tree->nodes);
		tree->nodes = NULL;
		return;
	}
	for (t_size i = index; i < tree->node_count; ++i)
	{
		tree->nodes[i] = tree->nodes[i + 1];
	}
}

_GENERIC()
void	Tree_Remove(T)(s_tree(T)* tree, T value)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	for (t_size i = 0; i < tree->node_count; ++i)
	{	// NOTE: only the *direct* sub-nodes of the given node are considered
		if (T_EQUALS(tree->nodes[i].value, value))
		{
			Tree_RemoveAt(T)(tree, i);
			return;
		}
	}
}

_GENERIC()
void	Tree_Remove_F(T)(s_tree(T)* tree, T value, void (*del)(T value))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	for (t_size i = 0; i < tree->node_count; ++i)
	{	// NOTE: only the *direct* sub-nodes of the given node are considered
		if (T_EQUALS(tree->nodes[i].value, value))
		{
			Tree_RemoveAt_F(T)(tree, i, del);
			return;
		}
	}
}

_GENERIC()
void	Tree_RemoveAll(T)(s_tree(T)* tree, T value)
{
	t_size	amount;

	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	amount = 0; // used as the write index while compacting the sub-nodes array
	for (t_size i = 0; i < tree->node_count; ++i)
	{	// NOTE: only the *direct* sub-nodes of the given node are considered
		if (T_EQUALS(tree->nodes[i].value, value))
		{
			Tree_Clear(T)(&tree->nodes[i]);
			continue;
		}
		tree->nodes[amount++] = tree->nodes[i];
	}
	tree->node_count = amount;
	if (tree->node_count == 0)
	{
		Memory_Free(tree->nodes);
		tree->nodes = NULL;
	}
}

_GENERIC()
void	Tree_RemoveAll_F(T)(s_tree(T)* tree, T value, void (*del)(T value))
{
	t_size	amount;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	amount = 0; // used as the write index while compacting the sub-nodes array
	for (t_size i = 0; i < tree->node_count; ++i)
	{	// NOTE: only the *direct* sub-nodes of the given node are considered
		if (T_EQUALS(tree->nodes[i].value, value))
		{
			del(tree->nodes[i].value);
			Tree_Clear_F(T)(&tree->nodes[i], del);
			continue;
		}
		tree->nodes[amount++] = tree->nodes[i];
	}
	tree->node_count = amount;
	if (tree->node_count == 0)
	{
		Memory_Free(tree->nodes);
		tree->nodes = NULL;
	}
}
