
#include "libccc/monad/array.h"



T*	CONCAT(Array_T,_Find)(s_array_T const* array, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (NULL);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (array->items[i] == item)
			return (&(array->items[i]));
	}
	return (NULL);
}



t_sint	CONCAT(Array_T,_IndexOf)(s_array_T const* array, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (ERROR);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (array->items[i] == item)
			return (i);
	}
	return (ERROR);
}
