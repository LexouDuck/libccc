
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(Array_Delete,T_NAME)(s_array_T* *a_array)
{
	HANDLE_ERROR(NULLPOINTER, (a_array  == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (*a_array == NULL), return;)
	Memory_Free((*a_array)->items);
	(*a_array)->items = NULL;
	(*a_array)->length = 0;
	Memory_Free(*a_array);
	(*a_array) = NULL;
}



_GENERIC()
void	CONCAT(Array_Delete_F,T_NAME)(s_array_T* *a_array, void (*delete)(T* item))
{
	HANDLE_ERROR(NULLPOINTER, (delete   == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (a_array  == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (*a_array == NULL), return;)
	for (t_uint i = 0; i < (*a_array)->length; ++i)
	{
		delete(&(*a_array)->items[i]);
	}
	Memory_Free((*a_array)->items);
	(*a_array)->items = NULL;
	(*a_array)->length = 0;
	Memory_Free(*a_array);
	(*a_array) = NULL;
}
