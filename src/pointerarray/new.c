
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_New(t_size n)
{
	void**	result;

	result = (void**)Memory_New(sizeof(void**) * (n + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	return (result);
}
