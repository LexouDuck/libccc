
#include "libccc/monad/array.h"


_GENERIC()
t_bool	CONCAT(Array_Has,T_NAME)(s_array_T const* array, s_array_T const* target)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (FALSE);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (CONCAT(Array_Contains,T_NAME)(target, array->items[i]))
			return (TRUE);
	}
	return (FALSE);
}


_GENERIC()
t_bool	CONCAT(Array_HasOnly,T_NAME)(s_array_T const* array, s_array_T const* target)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (array == NULL || array->items == NULL)
		return (FALSE);
#endif
	for (t_uint i = 0; i < array->length; ++i)
	{
		if (!CONCAT(Array_Contains,T_NAME)(target, array->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
