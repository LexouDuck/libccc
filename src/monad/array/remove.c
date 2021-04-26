
#include "libccc/memory.h"
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_Remove,T_NAME)(s_array_T* array, T item)
{
	LIBCONFIG_HANDLE_NULLPOINTER(array, )
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, )
	t_sint	index = CONCAT(Array_IndexOf,T_NAME)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_RemoveAt,T_NAME)(array, index);
}


_GENERIC()
void	CONCAT(Array_Remove_F,T_NAME)(s_array_T* array, T item, void (*delete)(T))
{
	LIBCONFIG_HANDLE_NULLPOINTER(array, )
	LIBCONFIG_HANDLE_NULLPOINTER(array->items, )
	t_sint	index = CONCAT(Array_IndexOf,T_NAME)(array, item);
	if (index == ERROR)
		return;
	CONCAT(Array_RemoveAt_F,T_NAME)(array, index, delete);
}
