
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)	Tree_Item(T)(T value)
{
	s_tree(T)	result = { .node_count = 0, .nodes = NULL, .value = value };
	return (result);
}
