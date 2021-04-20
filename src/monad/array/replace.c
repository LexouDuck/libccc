
#include "libccc/memory.h"
#include "libccc/monad/array.h"



s_array_T	CONCAT(Array_T,_Replace)(s_array_T const* array, T old, T new)
{
	s_array_T	result = {0};

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (result);
#endif
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
