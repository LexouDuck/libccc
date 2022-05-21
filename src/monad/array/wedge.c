
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Wedge(T)(s_array(T)* dest, s_array(T) const* src, t_uint index)
{
	T*	result;

	if CCCERROR((dest        == NULL), ERROR_NULLPOINTER, NULL) return (dest);
	if CCCERROR((dest->items == NULL), ERROR_NULLPOINTER, NULL) return (dest);
	if CCCERROR((index > dest->length), ERROR_INDEX2LARGE, 
		"index given ("SF_UINT") is beyond the end of the destination array (length: "SF_UINT")", index, dest->length)
		return (dest);
	result = (T*)Memory_Allocate(sizeof(T) * (dest->length + src->length));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) return (dest);
	for (t_uint i = 0; i < dest->length; ++i)
	{
		if (i < index)
			result[i] = dest->items[i];
		else if (i == index)
		{
			for (t_uint j = 0; j < src->length; ++j)
			{
				result[i + j] = src->items[j];
			}
			result[i + src->length] = dest->items[i];
		}
		else
			result[i + src->length] = dest->items[i];
	}
	Memory_Free(dest->items);
	dest->items = result;
	dest->length += 1;
	return (dest);
}
