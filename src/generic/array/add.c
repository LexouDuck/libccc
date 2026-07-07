
#include "libccc/memory.h"
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array(T)*	Array_Add(T)(s_array(T)* array, T item)
{
	if (array == NULL)
	{
		array = (s_array(T)*)Memory_New(sizeof(s_array(T)));
		if CCCERROR((array == NULL), ERROR_ALLOCFAILURE, NULL)
			return (NULL);
		*array = Array_Item(T)(item);
		return (array);
	}
	T* items = (T*)Memory_Reallocate(array->items, sizeof(T) * (array->length + 1));
	if CCCERROR((items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	array->items = items;
	array->items[array->length] = item;
	array->length += 1;
	return (array);
}
