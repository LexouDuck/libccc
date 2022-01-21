
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Array_Iterate(T)(s_array(T)* array, void (*f)(T item))
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
void	Array_Iterate_I(T)(s_array(T)* array, void (*f)(T item, t_uint index))
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
