
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Wedge,T_NAME)(s_array_T* dest, s_array_T const* src, t_uint index)
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (dest        == NULL), return (dest);)
	HANDLE_ERROR(NULLPOINTER, (dest->items == NULL), return (dest);)
	HANDLE_ERROR_SF(INDEX2LARGE, (index > dest->length), return (dest);,
		", index given ("SF_UINT") is beyond the end of the destination array (length: "SF_UINT")",
		index, dest->length)
	result = (T*)Memory_Allocate(sizeof(T) * (dest->length + src->length));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (dest);)
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
