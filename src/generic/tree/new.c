
#include "libccc/memory.h"
#include "libccc/generic/tree.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_tree(T)*	Tree_New(T)(T value)
{
	s_tree(T)*	result;

	result = (s_tree(T)*)Memory_New(sizeof(s_tree(T)));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result->value = value;
	return (result); // a single leaf node
}
