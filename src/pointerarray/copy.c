
#include "libccc/pointerarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void**	PointerArray_Copy(
	void** dest,      t_uint dest_i,
	void* const* src, t_uint src_i,
	t_uint n)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination pointer array given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source pointer array given is NULL")
		return (NULL);
	t_uint	dest_length = PointerArray_Length((void const* const*)dest);
	t_uint	src_length  = PointerArray_Length((void const* const*)src);
	if CCCERROR((dest_i >= dest_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i >=  src_length), ERROR_INDEX2LARGE, NULL)	return (NULL);
	if CCCERROR((dest_i + n > dest_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
	if CCCERROR(( src_i + n >  src_length), ERROR_LENGTH2LARGE, NULL)	return (NULL);
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
