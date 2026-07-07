
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_set(T)*	Set_Map(T)(s_set(T) const* set, T (*map)(T item))
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < set->length; ++i)
	{
		// NOTE: if `map` yields the same value for two distinct items, that
		// value is only stored once (see the doc comment for the caveat about
		// mapped values which allocate)
		if (Set_Add(T)(result, map(set->items[i])) == NULL)
		{
			Set_Free(T)(result);
			return (NULL);
		}
	}
	return (result);
}
