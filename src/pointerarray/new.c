
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_New(t_uint n, void const* value)
{
	void**	result;

	result = (void**)Memory_New(sizeof(void**) * (n + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; i < n; ++i)
	{
		result[i] = (void*)value;
	}
	return (result);
}
