
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Wedge(void** dest, void* const* src, t_uint index)
{
	void**	result;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src  == NULL), return (NULL);)
	result = PointerArray_Sub((void* const*)dest, 0, index);
	PointerArray_Append(&result, src);
	PointerArray_Append(&result, (void* const*)dest + index);
	PointerArray_Free(dest);
	return (result);
}
