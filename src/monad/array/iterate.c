
#include "libccc/monad/array.h"


_GENERIC()
void	CONCAT(Array_Iterate,T_NAME)(s_array_T* array, void (*f)(T item))
{
	t_uint i;

	LIBCONFIG_HANDLE_NULLPOINTER(, f)
	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	LIBCONFIG_HANDLE_NULLPOINTER(, array->items)
	for (i = 0; i < array->length; ++i)
	{
		f(array->items[i]);
	}
}


_GENERIC()
void	CONCAT(Array_Iterate_I,T_NAME)(s_array_T* array, void (*f)(T item, t_uint index))
{
	t_uint i;

	LIBCONFIG_HANDLE_NULLPOINTER(, f)
	LIBCONFIG_HANDLE_NULLPOINTER(, array)
	LIBCONFIG_HANDLE_NULLPOINTER(, array->items)
	for (i = 0; i < array->length; ++i)
	{
		f(array->items[i], i);
	}
}
