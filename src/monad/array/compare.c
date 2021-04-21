
#include "libccc/monad/array.h"



_GENERIC()
t_sint	CONCAT(Array_T,_Compare)(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2))
{
	t_sint	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
		return (0);
	if (array1 == NULL || array1->items == NULL ||
		array2 == NULL || array2->items == NULL ||
		compare == NULL)
		return (ERROR);
#endif
	for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
	{
		result = compare(array1->items[i], array2->items[i]);
		if (result)
			return (result);
	}
	return (0);
}



_GENERIC()
t_sint	CONCAT(Array_T,_Compare_N)(s_array_T const* array1, s_array_T const* array2, t_sint (*compare)(T item1, T item2), t_uint n)
{
	t_sint	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
		return (0);
	if (array1 == NULL || array1->items == NULL ||
		array2 == NULL || array2->items == NULL ||
		compare == NULL)
		return (ERROR);
#endif
	for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
	{
		result = compare(array1->items[i], array2->items[i]);
		if (result)
			return (result);
	}
	return (0);
}
