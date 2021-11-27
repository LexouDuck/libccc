
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	Array_Count(T)(s_array(T) const* array, T item)
{
	t_uint	result = 0;

	HANDLE_ERROR(NULLPOINTER, (array == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (array->items == NULL), return (0);)
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			result += 1;
	}
	return (result);
}
