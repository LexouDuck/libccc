
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Array_Equals(T)(s_array(T) const* array1, s_array(T) const* array2)
{
	if (array1 == array2)
		return (TRUE);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if (array1->length != array2->length)
		return (FALSE);
	if (array1->items == array2->items)
		return (TRUE); // same items buffer (also covers two empty arrays)
	if CCCERROR((array1->items == NULL), ERROR_INVALIDARGS, NULL) return (FALSE);
	if CCCERROR((array2->items == NULL), ERROR_INVALIDARGS, NULL) return (FALSE);
	for (t_uint i = 0; i < array1->length; ++i)
	{
		if (!T_EQUALS(array1->items[i], array2->items[i]))
			return (FALSE);
	}
	return (TRUE);
}


_GENERIC()
t_bool	Array_Equals_N(T)(s_array(T) const* array1, s_array(T) const* array2, t_uint n)
{
	if (array1 == array2)
		return (TRUE);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((array1->length > 0 && array1->items == NULL), ERROR_INVALIDARGS, NULL) return (FALSE);
	if CCCERROR((array2->length > 0 && array2->items == NULL), ERROR_INVALIDARGS, NULL) return (FALSE);
	for (t_uint i = 0; i < n; ++i)
	{
		if (i >= array1->length || i >= array2->length)
			return (i >= array1->length && i >= array2->length); // both must end together, within the first `n` items
		if (!T_EQUALS(array1->items[i], array2->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
