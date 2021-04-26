
#include "libccc/monad/array.h"



_GENERIC()
t_sint	CONCAT(Array_Compare,T_NAME)(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2))
{
	t_sint	result;

	LIBCONFIG_HANDLE_NULLPOINTER(compare, 0)
	if (array1 == array2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(array1, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array2, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array1->items, (array1->items - array2->items))
	LIBCONFIG_HANDLE_NULLPOINTER(array2->items, (array1->items - array2->items))
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
	{
		result = compare(array1->items[i], array2->items[i]);
		if (result)
			return (result);
	}
	return (0);
}



_GENERIC()
t_sint	CONCAT(Array_Compare_N,T_NAME)(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_uint n)
{
	t_sint	result;

	LIBCONFIG_HANDLE_NULLPOINTER(compare, 0)
	if (array1 == array2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(array1, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array2, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array1->items, (array1->items - array2->items))
	LIBCONFIG_HANDLE_NULLPOINTER(array2->items, (array1->items - array2->items))
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
	{
		result = compare(array1->items[i], array2->items[i]);
		if (result)
			return (result);
	}
	return (0);
}
