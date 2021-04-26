
#include "libccc/monad/array.h"


_GENERIC()
t_bool	CONCAT(Array_Equals,T_NAME)(s_array_T const* array1, s_array_T const* array2)
{
	if (array1 == array2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(array1, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array2, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array1->items, (array1->items - array2->items))
	LIBCONFIG_HANDLE_NULLPOINTER(array2->items, (array1->items - array2->items))
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
t_bool	CONCAT(Array_Equals_N,T_NAME)(s_array_T const* array1, s_array_T const* array2, t_uint n)
{
	if (array1 == array2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(array1, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array2, (array1 - array2))
	LIBCONFIG_HANDLE_NULLPOINTER(array1->items, (array1->items - array2->items))
	LIBCONFIG_HANDLE_NULLPOINTER(array2->items, (array1->items - array2->items))
	if (array1->length == array2->length && array1->items == array2->items)
		return (0);
	for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
	{
		if (!T_EQUALS(array1->items[i], array2->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
