
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Array_Contains(T)(s_array(T) const* array, T item)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "array given is NULL")
		return (FALSE);
	if CCCERROR((array->length > 0 && array->items == NULL), ERROR_INVALIDARGS, "array given is invalid")
		return (FALSE);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (TRUE);
	}
	return (FALSE);
}
