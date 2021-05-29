
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
void	CONCAT(Array_Iterate,T_NAME)(s_array_T* array, void (*f)(T item))
{
	t_uint i;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	for (i = 0; i < array->length; ++i)
	{
		f(array->items[i]);
	}
}


_GENERIC()
void	CONCAT(Array_Iterate_I,T_NAME)(s_array_T* array, void (*f)(T item, t_uint index))
{
	t_uint i;

	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return;)
	for (i = 0; i < array->length; ++i)
	{
		f(array->items[i], i);
	}
}
