
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(Array_Free,T_NAME)(s_array_T* array)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
	Memory_Free(array);
}



_GENERIC()
void	CONCAT(Array_Free_F,T_NAME)(s_array_T* array, void (*delete)(T* item))
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (delete == NULL), return;)
	for (t_uint i = 0; i < array->length; ++i)
	{
		delete(&array->items[i]);
	}
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
	Memory_Free(array);
}
