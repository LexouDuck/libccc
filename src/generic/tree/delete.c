
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Tree_Clear(T)(s_tree(T)* tree)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	for (t_size i = 0; i < tree->node_count; ++i)
	{
		Tree_Clear(T)(&tree->nodes[i]);
	}
	if (tree->nodes != NULL) // (a leaf node has nothing to free)
		Memory_Free(tree->nodes);
	tree->nodes = NULL;
	tree->node_count = 0;
}

_GENERIC()
void	Tree_Clear_F(T)(s_tree(T)* tree, void (*del)(T value))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	for (t_size i = 0; i < tree->node_count; ++i)
	{	// NOTE: `del` is called for every descendant value, but not for `tree->value` itself
		Tree_Clear_F(T)(&tree->nodes[i], del);
		del(tree->nodes[i].value);
	}
	if (tree->nodes != NULL) // (a leaf node has nothing to free)
		Memory_Free(tree->nodes);
	tree->nodes = NULL;
	tree->node_count = 0;
}

_GENERIC()
void	Tree_Free(T)(s_tree(T)* tree)
{
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	Tree_Clear(T)(tree);
	Memory_Free(tree);
}

_GENERIC()
void	Tree_Free_F(T)(s_tree(T)* tree, void (*del)(T value))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((tree == NULL), ERROR_NULLPOINTER, "tree given is NULL")
		return;
	del(tree->value); // NOTE: `del` is called for every value of the subtree, including this node's own
	Tree_Clear_F(T)(tree, del);
	Memory_Free(tree);
}

_GENERIC()
void	Tree_Delete(T)(s_tree(T)* *a_tree)
{
	if CCCERROR((a_tree == NULL), ERROR_NULLPOINTER, "tree address given is NULL")
		return;
	if CCCERROR((*a_tree == NULL), ERROR_NULLPOINTER, NULL)
		return;
	Tree_Free(T)(*a_tree);
	(*a_tree) = NULL;
}

_GENERIC()
void	Tree_Delete_F(T)(s_tree(T)* *a_tree, void (*del)(T value))
{
	if CCCERROR((a_tree == NULL), ERROR_NULLPOINTER, "tree address given is NULL")
		return;
	if CCCERROR((*a_tree == NULL), ERROR_NULLPOINTER, NULL)
		return;
	Tree_Free_F(T)(*a_tree, del);
	(*a_tree) = NULL;
}
