
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_array_T*	CONCAT(Array_Add,T_NAME)(s_array_T* array, T item)
{
	if (array == NULL)
	{
		array = (s_array_T*)Memory_New(sizeof(s_array_T));
		HANDLE_ERROR(ALLOCFAILURE, (array == NULL), return (NULL);)
		*array = CONCAT(Array_Item,T_NAME)(item);
		return (array);
	}
	array->length += 1;
	array->items = (T*)Memory_Reallocate(array->items, sizeof(T) * array->length);
	HANDLE_ERROR(ALLOCFAILURE, (array->items == NULL), return (NULL);)
	array->items[array->length - 1] = item;
	return (array);
}
