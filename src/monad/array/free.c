
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Array_Free(T)(s_array(T)* array)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	Memory_Free(array->items);
	array->items = NULL;
	array->length = 0;
	Memory_Free(array);
}



_GENERIC()
void	Array_Free_F(T)(s_array(T)* array, void (*delete)(T* item))
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
