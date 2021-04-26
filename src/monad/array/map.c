
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
s_array_T	CONCAT(Array_Map,T_NAME)(s_array_T const* array, T (*map)(T item))
{
	s_array_T	result = {0};
	t_uint	i;

	LIBCONFIG_HANDLE_NULLPOINTER(map, result)
	LIBCONFIG_HANDLE_NULLPOINTER(array, result)
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, result)
	result.items = (T*)Memory_Alloc(sizeof(T) * array->length);
	if (result.items == NULL)
		return (result);
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

	LIBCONFIG_HANDLE_NULLPOINTER(map, result)
	LIBCONFIG_HANDLE_NULLPOINTER(array, result)
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, result)
	result.items = (T*)Memory_Alloc(sizeof(T) * array->length);
	if (result.items == NULL)
		return (result);
	result.length = array->length;
	for (i = 0; i < result.length; ++i)
	{
		result.items[i] = map(array->items[i], i);
	}
	return (result);
}
