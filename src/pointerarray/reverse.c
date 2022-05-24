
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Reverse(void* const* ptrarr)
{
	void**	result;
	t_uint	length;
	t_uint	index;

	if CCCERROR((ptrarr == NULL), ERROR_NULLPOINTER, "pointer array given is NULL")
		return (NULL);
	length = PointerArray_Length((void const* const*)ptrarr);
	result = PointerArray_New(length, NULL);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	index = length - 1;
	for (t_uint i = 0; i < length; ++i, --index)
	{
		result[i] = ptrarr[index];
	}
	return (result);
}
