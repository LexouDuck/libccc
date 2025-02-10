
#include "libccc/generic/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Array_Equals(T)(s_array(T) const* array1, s_array(T) const* array2)
{
	if (array1 == array2)
		return (0);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, NULL) return (array1 - array2);
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, NULL) return (array1 - array2);
	if CCCERROR((array1->items == NULL), ERROR_NULLPOINTER, NULL) return (array1->items - array2->items);
	if CCCERROR((array2->items == NULL), ERROR_NULLPOINTER, NULL) return (array1->items - array2->items);
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
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
		return (0);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, NULL) return (array1 - array2);
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, NULL) return (array1 - array2);
	if CCCERROR((array1->items == NULL), ERROR_NULLPOINTER, NULL) return (array1->items - array2->items);
	if CCCERROR((array2->items == NULL), ERROR_NULLPOINTER, NULL) return (array1->items - array2->items);
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
	{
		if (!T_EQUALS(array1->items[i], array2->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
