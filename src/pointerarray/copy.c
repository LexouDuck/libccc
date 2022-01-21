
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Copy(
	void** dest,      t_uint dest_i,
	void* const* src, t_uint src_i,
	t_uint n)
{
	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, ( src == NULL), return (NULL);)
	t_uint	dest_length = PointerArray_Length((void const* const*)dest);
	t_uint	src_length  = PointerArray_Length((void const* const*)src);
	HANDLE_ERROR(INDEX2LARGE, (dest_i >= dest_length),    return (NULL);)
	HANDLE_ERROR(INDEX2LARGE, ( src_i >=  src_length),    return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (dest_i + n > dest_length), return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, ( src_i + n >  src_length), return (NULL);)
	if (n == 0)
		n = src_length - src_i;
	for (t_uint i = 0; i < n; ++i)
	{
		if (dest_i + i >= dest_length)
			return (dest);
		dest[dest_i + i] = src[src_i + i];
	}
	return (dest);
}
