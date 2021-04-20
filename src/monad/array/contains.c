
#include "libccc/monad/array.h"



t_bool	CONCAT(Array_T,_Contains)(s_array_T const* array, T item)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (FALSE);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (T_EQUALS(array->items[i], item))
			return (TRUE);
	}
	return (FALSE);
}
