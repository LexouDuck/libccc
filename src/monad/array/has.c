
#include "libccc/monad/array.h"



t_bool	CONCAT(Array_T,_Has)(s_array_T const* array, s_array_T const* target)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (FALSE);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (CONCAT(Array_T,_Contains)(target, array->items[i]))
			return (TRUE);
	}
	return (FALSE);
}



t_bool	CONCAT(Array_T,_HasOnly)(s_array_T const* array, s_array_T const* target)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (FALSE);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (!CONCAT(Array_T,_Contains)(target, array->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
