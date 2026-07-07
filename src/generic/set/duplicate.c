
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_set(T)*	Set_Duplicate(T)(s_set(T) const* set)
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (set->length == 0)
		return (result);
	result->items = (T*)Memory_Allocate(set->length * sizeof(T));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Set_Free(T)(result);
		return (NULL);
	}
	// NOTE: the source set already holds unique values, so they can simply be copied
	for (i = 0; i < set->length; ++i)
	{
		result->items[i] = set->items[i];
	}
	result->length = set->length;
	return (result);
}
