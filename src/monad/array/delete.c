
#include "libccc/memory.h"
#include "libccc/monad/array.h"



_GENERIC()
void	CONCAT(Array_Delete,T_NAME)(s_array_T* array)
{
	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
}



_GENERIC()
void	CONCAT(Array_Delete_F,T_NAME)(s_array_T* array, void (*delete)(T item))
{
	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	for (t_uint i = 0; i < array->length; ++i)
	{
		delete(array->items[i]);
	}
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
}
