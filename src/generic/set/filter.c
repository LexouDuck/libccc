
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_set(T)*	Set_Filter(T)(s_set(T) const* set, t_bool (*filter)(T item))
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < set->length; ++i)
	{
		if (filter(set->items[i]))
		{
			// NOTE: the source set holds unique values, so no duplicate checking
			// is needed here, but Set_Add() is used regardless, for code clarity
			if (Set_Add(T)(result, set->items[i]) == NULL)
			{
				Set_Free(T)(result);
				return (NULL);
			}
		}
	}
	return (result);
}
