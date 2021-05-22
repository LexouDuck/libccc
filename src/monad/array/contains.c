
#include "libccc/monad/array.h"

#include LIBCONFIG_HANDLE_INCLUDE



_GENERIC()
t_bool	CONCAT(Array_Contains,T_NAME)(s_array_T const* array, T item)
{
	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (FALSE);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (FALSE);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (TRUE);
	}
	return (FALSE);
}
