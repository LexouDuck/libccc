
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Insert(T)(s_array(T)* dest, T item, t_uint index)
{
	T*	result;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination array given is NULL")
		return (dest);
	if CCCERROR((dest->items == NULL), ERROR_INVALIDARGS, NULL)
		return (dest);
	if CCCERROR((index > dest->length), ERROR_INDEX2LARGE, 
		"index given ("SF_UINT") is beyond the end of the destination dest (length: "SF_UINT")", index, dest->length)
		return (dest);
	result = (T*)Memory_Allocate(sizeof(T) * (dest->length + 1));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (dest);
	for (t_uint i = 0; i <= dest->length; ++i)
	{
		if (i < index)
			result[i] = dest->items[i];
		else if (i == index)
			result[i] = item;
		else
			result[i] = dest->items[i - 1];
	}
	Memory_Free(dest->items);
	dest->items = result;
	dest->length += 1;
	return (dest);
}
