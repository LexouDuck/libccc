
#include "libccc/monad/array.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_sint	Array_Compare(T)(s_array(T) const* array1, s_array(T) const* array2, t_sint (*compare)(T item1, T item2))
{
	t_sint	result;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (0);
	if (array1 == array2)
		return (0);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, NULL) return ((array1 - array2));
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, NULL) return ((array1 - array2));
	if CCCERROR((array1->items == NULL), ERROR_NULLPOINTER, NULL) return ((array1->items - array2->items));
	if CCCERROR((array2->items == NULL), ERROR_NULLPOINTER, NULL) return ((array1->items - array2->items));
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < array1->length) && (i < array2->length); ++i)
	{
		result = compare(array1->items[i], array2->items[i]);
		if (result)
			return (result);
	}
	return (0);
}



_GENERIC()
t_sint	Array_Compare_N(T)(s_array(T) const* array1, s_array(T) const* array2, t_sint (*compare)(T item1, T item2), t_uint n)
{
	t_sint	result;

	if CCCERROR((compare == NULL), ERROR_NULLPOINTER, "compare() function given is NULL")
		return (0);
	if (array1 == array2)
		return (0);
	if CCCERROR((array1 == NULL), ERROR_NULLPOINTER, NULL) return ((array1 - array2));
	if CCCERROR((array2 == NULL), ERROR_NULLPOINTER, NULL) return ((array1 - array2));
	if CCCERROR((array1->items == NULL), ERROR_NULLPOINTER, NULL) return ((array1->items - array2->items));
	if CCCERROR((array2->items == NULL), ERROR_NULLPOINTER, NULL) return ((array1->items - array2->items));
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
	{
		result = compare(array1->items[i], array2->items[i]);
		if (result)
			return (result);
	}
	return (0);
}
