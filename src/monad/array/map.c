
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Map,T_NAME)(s_array_T const* array, T (*map)(T item))
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (map   == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	if (array->length == 0 || array->items == NULL)
		return ((s_array_T*)Memory_New(sizeof(s_array_T)));
	result = CONCAT(Array_New,T_NAME)(array->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		result->items[i] = map(array->items[i]);
	}
	return (result);
}


_GENERIC()
s_array_T*	CONCAT(Array_Map_I,T_NAME)(s_array_T const* array, T (*map)(T item, t_uint index))
{
	s_array_T*	result;

	HANDLE_ERROR(NULLPOINTER, (map   == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (NULL);)
	if (array->length == 0 || array->items == NULL)
		return ((s_array_T*)Memory_New(sizeof(s_array_T)));
	result = CONCAT(Array_New,T_NAME)(array->length, T_DEFAULT);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		result->items[i] = map(array->items[i], i);
	}
	return (result);
}
