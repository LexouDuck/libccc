
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	Memory_Duplicate(const void* ptr, t_size n)
{
	t_u8*	result;
	t_u8*	source;
	t_size	i;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	result = (t_u8*)Memory_Allocate(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	source = (t_u8*)ptr;
	i = 0;
	while (i < n)
	{
		result[i] = source[i];
		++i;
	}
	return ((void* )result);
}
