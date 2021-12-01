
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Reverse(void* const* ptrarr)
{
	void**	result;
	t_uint	length;
	t_uint	index;

	HANDLE_ERROR(NULLPOINTER, (ptrarr == NULL), return (NULL);)
	length = PointerArray_Length(ptrarr);
	HANDLE_ERROR(NULLPOINTER, (length > 0 && ptrarr == NULL), return (NULL);)
	result = PointerArray_New(length, NULL);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	index = length - 1;
	for (t_uint i = 0; i < length; ++i, --index)
	{
		result[i] = ptrarr[index];
	}
	return (result);
}
