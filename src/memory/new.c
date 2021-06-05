
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	Memory_New(t_size size)
{
	t_u8*	result;
	t_size	i;

	result = (t_u8* )Memory_Allocate(size);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < size)
	{
		result[i] = 0;
		++i;
	}
	return ((void* )result);
}



void*	Memory_New_C(t_size size, char c)
{
	t_u8*	result;
	t_size	i;

	result = (t_u8* )Memory_Allocate(size);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < size)
	{
		result[i] = c;
		++i;
	}
	return ((void* )result);
}
