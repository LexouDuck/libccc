
#include "libccc/memory.h"
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Sub(void* const* ptrarr, t_uint index, t_uint n)
{
	void**		result;
	t_uint		length;
	t_uint		i;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length((void const* const*)ptrarr);
	HANDLE_ERROR(INDEX2LARGE, (index > length), return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (index + n > length), return (NULL);)
	result = PointerArray_New(n, NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < n)
	{
		result[i] = ptrarr[index + i];
		HANDLE_ERROR(ALLOCFAILURE, (result == NULL),
		{
			PointerArray_Delete(&result);
			return (NULL);
		})
		++i;
	}
	result[i] = NULL;
	return (result);
}
