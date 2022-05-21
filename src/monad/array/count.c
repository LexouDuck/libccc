
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	Array_Count(T)(s_array(T) const* array, T item)
{
	t_uint	result = 0;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if CCCERROR((array->items == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			result += 1;
	}
	return (result);
}
