
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Insert(void** dest, void const* ptr, t_uint index)
{
	void**	result;
	t_size	length;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination pointer array given is NULL")
		return (NULL);
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer given is NULL")
		return (NULL);
	length = PointerArray_Length((void const* const*)dest);
	result = PointerArray_New(length + 1, NULL);
	for (t_uint i = 0; i <= length; ++i)
	{
		if (i < index)
			result[i] = dest[i];
		else if (i == index)
			result[i] = (void*)ptr;
		else
			result[i] = dest[i - 1];
	}
	PointerArray_Free(dest);
	return (result);
}
