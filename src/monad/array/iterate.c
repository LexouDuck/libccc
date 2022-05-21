
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Array_Iterate(T)(s_array(T)* array, void (*f)(T item))
{
	t_uint i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if CCCERROR((array->items == NULL), ERROR_NULLPOINTER, NULL)
		return;
	for (i = 0; i < array->length; ++i)
	{
		f(array->items[i]);
	}
}


_GENERIC()
void	Array_Iterate_I(T)(s_array(T)* array, void (*f)(T item, t_uint index))
{
	t_uint i;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if CCCERROR((array->items == NULL), ERROR_NULLPOINTER, NULL)
		return;
	for (i = 0; i < array->length; ++i)
	{
		f(array->items[i], i);
	}
}
