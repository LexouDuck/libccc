
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
s_array_T	CONCAT(Array_T,_Map)(s_array_T const* array, T (*map)(T item))
{
	s_array_T	result = {0};
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL || map == NULL)
		return (result);
#endif
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
s_array_T	CONCAT(Array_T,_Map_I)(s_array_T const* array, T (*map)(T item, t_uint index))
{
	s_array_T	result = {0};
	t_uint	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL || map == NULL)
		return (result);
#endif
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
