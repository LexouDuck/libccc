
#include "libccc/memory.h"
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	CONCAT(Array_Remove,T_NAME)(s_array_T* array, T item)
{
	t_sint	index;
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	index = CONCAT(Array_IndexOf,T_NAME)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_RemoveAt,T_NAME)(array, index);
}


_GENERIC()
void	CONCAT(Array_Remove_F,T_NAME)(s_array_T* array, T item, void (*delete)(T))
{
	t_sint	index;
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	index = CONCAT(Array_IndexOf,T_NAME)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_RemoveAt_F,T_NAME)(array, index, delete);
}
