
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Wedge(void** dest, void* const* src, t_uint index)
{
	void**	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination pointer array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "pointer array to wedge given is NULL")
		return (NULL);
	if CCCERROR((index > PointerArray_Length((void const* const*)dest)), ERROR_INDEX2LARGE,
		"index given (" SF_UINT ") is beyond end of ptrarr", index)
		return (NULL);
	if (index == 0)
		result = PointerArray_New(0, NULL);
	else result = PointerArray_Sub((void* const*)dest, 0, index);
	PointerArray_Append(&result, src);
	PointerArray_Append(&result, (void* const*)dest + index);
	PointerArray_Free(dest);
	return (result);
}
