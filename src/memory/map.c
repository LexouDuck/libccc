
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



void*	Memory_Map(void const* ptr, t_size n, t_u8 (*map)(t_u8 byte))
{
	t_u8*	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_New(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		result[i] = map(((t_u8*)ptr)[i]);
	}
	return (result);
}


void*	Memory_Map_I(void const* ptr, t_size n, t_u8 (*map)(t_u8 byte, t_uint index))
{
	t_u8*	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	result = (t_u8*)Memory_New(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; i < n; ++i)
	{
		result[i] = map(((t_u8*)ptr)[i], i);
	}
	return (result);
}
