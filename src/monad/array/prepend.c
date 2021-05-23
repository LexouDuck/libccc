
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
void	CONCAT(Array_Prepend,T_NAME)(s_array_T* array, T item)
{
	T*	result;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	result = (T*)Memory_Allocate(sizeof(T) * (array->length + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return;)
	result[0] = item;
	for (t_uint i = 0; i < array->length; ++i)
	{
		result[i + 1] = array->items[i];
	}
	Memory_Free(array->items);
	array->items = result;
	array->length += 1;
}
