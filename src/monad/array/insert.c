
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Insert,T_NAME)(s_array_T* array, T item, t_uint index)
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (array        == NULL), return (array);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (array);)
	HANDLE_ERROR_SF(INDEX2LARGE, (array->length <= index), return (array);,
		", index given ("SF_UINT") is beyond end of array (length: "SF_UINT")",
		index, array->length)
	result = (T*)Memory_Allocate(sizeof(T) * (array->length + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (array);)
	for (t_uint i = 0; i <= array->length; ++i)
	{
		if (i < index)
			result[i] = array->items[i];
		else if (i == index)
			result[i] = item;
		else
			result[i] = array->items[i - 1];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length += 1;
	return (array);
}
