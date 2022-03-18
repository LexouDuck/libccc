
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Insert(T)(s_array(T)* dest, T item, t_uint index)
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (dest        == NULL), return (dest);)
	HANDLE_ERROR(NULLPOINTER, (dest->items == NULL), return (dest);)
	HANDLE_ERROR_SF(INDEX2LARGE, (index > dest->length), return (dest);,
		"index given ("SF_UINT") is beyond the end of the destination dest (length: "SF_UINT")",
		index, dest->length)
	result = (T*)Memory_Allocate(sizeof(T) * (dest->length + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (dest);)
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
