
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(Array_Append,T_NAME)(s_array_T* array, T item)
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	result = (T*)Memory_Allocate(sizeof(T) * (array->length + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	for (t_uint i = 0; i < array->length; ++i)
	{
		result[i] = array->items[i];
	}
	result[array->length] = item;
	Memory_Free(array->items);
	array->items = result;
	array->length += 1;
}
