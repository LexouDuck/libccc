
#include "libccc/memory.h"
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Wedge(T)(s_array(T)* dest, s_array(T) const* src, t_uint index)
{
	T*	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination array given is NULL")
		return (dest);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "array to insert given is NULL")
		return (dest);
	if CCCERROR((dest->length > 0 && dest->items == NULL), ERROR_INVALIDARGS, "destination array given is invalid")
		return (dest);
	if CCCERROR((index > dest->length), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond the end of the destination array (length: " SF_UINT ")", index, dest->length)
		return (dest);
	if (src->length == 0)
		return (dest);
	result = (T*)Memory_Allocate(sizeof(T) * (dest->length + src->length));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (dest);
	for (t_uint i = 0; i < index; ++i)
	{
		result[i] = dest->items[i];
	}
	for (t_uint j = 0; j < src->length; ++j)
	{
		result[index + j] = src->items[j];
	}
	for (t_uint i = index; i < dest->length; ++i)
	{
		result[i + src->length] = dest->items[i];
	}
	Memory_Free(dest->items);
	dest->items = result;
	dest->length += src->length;
	return (dest);
}
