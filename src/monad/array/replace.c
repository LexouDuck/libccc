
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T	CONCAT(Array_Replace,T_NAME)(s_array_T const* array, T old, T new)
{
	s_array_T	result;// = CONCAT(NULL_ARRAY,T_NAME);

	Memory_Clear(&result, sizeof(s_array_T));
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (result);)
	result.items = (T*)Memory_Duplicate(array->items, sizeof(T) * array->length);
	if (result.items == NULL)
		return (result);
	result.length = array->length;
	for (t_uint i = 0; i < result.length; ++i)
	{
		if (T_EQUALS(result.items[i], old))
			result.items[i] = new;
	}
	return (result);
}
