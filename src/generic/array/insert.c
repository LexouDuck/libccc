
#include "libccc/memory.h"
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Insert(T)(s_array(T)* dest, T item, t_uint index)
{
	T*	result;

	if (dest == NULL)
	{	// as documented: a new single-item array is created, if `dest` is NULL and `index` is zero
		if CCCERROR((index != 0), ERROR_INDEX2LARGE,
			"cannot insert at index (" SF_UINT ") into a NULL array", index)
			return (NULL);
		dest = (s_array(T)*)Memory_New(sizeof(s_array(T)));
		if CCCERROR((dest == NULL), ERROR_ALLOCFAILURE, NULL)
			return (NULL);
		*dest = Array_Item(T)(item);
		return (dest);
	}
	if CCCERROR((dest->length > 0 && dest->items == NULL), ERROR_INVALIDARGS,
		"destination array given is invalid - `.length` doesn't match `.items`")
		return (dest);
	if CCCERROR((index > dest->length), ERROR_INDEX2LARGE, 
		"index given (" SF_UINT ") is beyond the end of the destination dest (length: " SF_UINT ")", index, dest->length)
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
