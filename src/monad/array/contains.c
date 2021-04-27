
#include "libccc/monad/array.h"


_GENERIC()
t_bool	CONCAT(Array_Contains,T_NAME)(s_array_T const* array, T item)
{
	LIBCONFIG_HANDLE_NULLPOINTER(FALSE, array)
	LIBCONFIG_HANDLE_NULLPOINTER(FALSE, array->items)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (TRUE);
	}
	return (FALSE);
}
