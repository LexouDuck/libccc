
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
s_array_T	CONCAT(Array_Map,T_NAME)(s_array_T const* array, T (*map)(T item))
{
	s_array_T	result = {0};
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (result);)
	result.items = (T*)Memory_Allocate(sizeof(T) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (result.items == NULL), return (result);)
	result.length = array->length;
	for (i = 0; i < result.length; ++i)
	{
		result.items[i] = map(array->items[i]);
	}
	return (result);
}


_GENERIC()
s_array_T	CONCAT(Array_Map_I,T_NAME)(s_array_T const* array, T (*map)(T item, t_uint index))
{
	s_array_T	result = {0};
	t_uint	i;

	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (result);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (result);)
	result.items = (T*)Memory_Allocate(sizeof(T) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (result.items == NULL), return (result);)
	result.length = array->length;
	for (i = 0; i < result.length; ++i)
	{
		result.items[i] = map(array->items[i], i);
	}
	return (result);
}
