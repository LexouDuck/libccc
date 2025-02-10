
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	Array_Count(T)(s_array(T) const* array, T item)
{
	t_uint	result = 0;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (0);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "array given is invalid")
		return (0);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			result += 1;
	}
	return (result);
}
