
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Add(void** ptrarr, void const* ptr)
{
	t_uint	length;

	if (ptrarr == NULL)
	{
		length = 1;
		ptrarr = (void**)Memory_New((length + 1) * sizeof(void const*));
	}
	else
	{
		length = PointerArray_Length((void const* const*)ptrarr) + 1;
		ptrarr = (void**)Memory_Reallocate(ptrarr, (length + 1) * sizeof(void const*));
	}
	HANDLE_ERROR(ALLOCFAILURE, (ptrarr == NULL), return (NULL);)
	ptrarr[length - 1] = (void*)ptr;
	return (ptrarr);
}
