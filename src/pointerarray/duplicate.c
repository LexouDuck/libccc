
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**		PointerArray_Duplicate(void* const* ptrarr)
{
	t_uint	i;
	void**	result;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (*ptrarr == NULL), return (NULL);)
	result = PointerArray_New(PointerArray_Length(ptrarr), NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (ptrarr[i])
	{
		result[i] = ptrarr[i];
		++i;
	}
	return (result);
}
