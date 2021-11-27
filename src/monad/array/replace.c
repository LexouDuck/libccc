
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Replace,T_NAME)(s_array_T const* array, T old, T new)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = CONCAT(Array_Duplicate,T_NAME)(array);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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



_GENERIC()
s_array_T*	CONCAT(Array_ReplaceFirst,T_NAME)(s_array_T const* array, T old, T new, t_uint n)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = CONCAT(Array_Duplicate,T_NAME)(array);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	for (t_uint i = 0; i < result->length; ++i)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(result->items[i], old))
		{
			result->items[i] = new;
			n -= 1;
		}
	}
	return (result);
}



_GENERIC()
s_array_T*	CONCAT(Array_ReplaceLast,T_NAME)(s_array_T const* array, T old, T new, t_uint n)
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array->length > 0 && array->items == NULL), return (NULL);)
	result = CONCAT(Array_Duplicate,T_NAME)(array);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	if (result->items == NULL)
		return (result);
	result->length = array->length;
	t_uint i = result->length;
	while (i--)
	{
		if (n == 0)
			return (result);
		if (T_EQUALS(result->items[i], old))
		{
			result->items[i] = new;
			n -= 1;
		}
	}
	return (result);
}
