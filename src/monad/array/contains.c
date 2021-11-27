
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Array_Contains(T)(s_array(T) const* array, T item)
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
