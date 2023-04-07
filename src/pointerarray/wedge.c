
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Wedge(void** dest, void* const* src, t_uint index)
{
	void**	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination pointer array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "pointer array to wedge given is NULL")
		return (NULL);
	result = PointerArray_Sub((void* const*)dest, 0, index);
	PointerArray_Append(&result, src);
	PointerArray_Append(&result, (void* const*)dest + index);
	PointerArray_Free(dest);
	return (result);
}
