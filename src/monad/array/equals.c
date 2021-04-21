
#include "libccc/monad/array.h"


_GENERIC()
t_bool	CONCAT(Array_Equals,T_NAME)(s_array_T const* array1, s_array_T const* array2)
{
//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
		return (TRUE);
	if (array1 == NULL || array1->items == NULL ||
		array2 == NULL || array2->items == NULL)
		return (FALSE);
//#endif
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
//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array1 == array2 || (array1->length == array2->length && array1->items == array2->items))
		return (TRUE);
	if (array1 == NULL || array1->items == NULL ||
		array2 == NULL || array2->items == NULL)
		return (FALSE);
//#endif
	for (t_uint i = 0; (i < n) && (i < array1->length) && (i < array2->length); ++i)
	{
		if (!T_EQUALS(array1->items[i], array2->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
