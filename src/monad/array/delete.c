
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
void	CONCAT(Array_Delete,T_NAME)(s_array_T* *a_array)
{
	s_array_T*	array;

	HANDLE_ERROR(NULLPOINTER, (a_array == NULL), return;)
	array = *a_array;
	if (array)
	{
		Memory_Free(array->items);
		array->items = NULL;
		array->length = 0;
		*a_array = NULL;
	}
}



_GENERIC()
void	CONCAT(Array_Delete_F,T_NAME)(s_array_T* *a_array, void (*delete)(T item))
{
	s_array_T*	array;

	HANDLE_ERROR(NULLPOINTER, (a_array == NULL), return;)
	array = *a_array;
	if (array)
	{
		for (t_uint i = 0; i < array->length; ++i)
		{
			delete(array->items[i]);
		}
		Memory_Free(array->items);
		array->items = NULL;
		array->length = 0;
		*a_array = NULL;
	}
}
