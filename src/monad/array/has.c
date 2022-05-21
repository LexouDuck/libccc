
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Array_Has(T)(s_array(T) const* array, s_array(T) const* target)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((array->items == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (Array_Contains(T)(target, array->items[i]))
			return (TRUE);
	}
	return (FALSE);
}


_GENERIC()
t_bool	Array_HasOnly(T)(s_array(T) const* array, s_array(T) const* target)
{
	if CCCERROR((array == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((array->items == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (!Array_Contains(T)(target, array->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
