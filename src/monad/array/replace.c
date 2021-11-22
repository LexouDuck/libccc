
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Replace,T_NAME)(s_array_T const* array, T old, T new)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = CONCAT(Array_Duplicate,T_NAME)(array);
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	for (t_uint i = 0; i < result->length; ++i)
	{
		if (T_EQUALS(result->items[i], old))
		{
			result->items[i] = new;
			return (result);
		}
	}
	return (result);
}



_GENERIC()
s_array_T*	CONCAT(Array_ReplaceAll,T_NAME)(s_array_T const* array, T old, T new)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = CONCAT(Array_Duplicate,T_NAME)(array);
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	for (t_uint i = 0; i < result->length; ++i)
	{
		if (T_EQUALS(result->items[i], old))
		{
			result->items[i] = new;
		}
	}
	return (result);
}
