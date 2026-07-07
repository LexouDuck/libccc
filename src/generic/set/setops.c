
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_set(T)*	Set_Union(T)(s_set(T) const* set1, s_set(T) const* set2)
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((set1 == NULL), ERROR_NULLPOINTER, "set1 given is NULL")
		return (NULL);
	if CCCERROR((set2 == NULL), ERROR_NULLPOINTER, "set2 given is NULL")
		return (NULL);
	result = Set_Duplicate(T)(set1);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < set2->length; ++i)
	{
		// NOTE: Set_Add() ignores any item of `set2` which is already present
		if (Set_Add(T)(result, set2->items[i]) == NULL)
		{
			Set_Free(T)(result);
			return (NULL);
		}
	}
	return (result);
}



_GENERIC()
s_set(T)*	Set_Intersect(T)(s_set(T) const* set1, s_set(T) const* set2)
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((set1 == NULL), ERROR_NULLPOINTER, "set1 given is NULL")
		return (NULL);
	if CCCERROR((set2 == NULL), ERROR_NULLPOINTER, "set2 given is NULL")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < set1->length; ++i)
	{
		if (Set_Contains(T)(set2, set1->items[i]))
		{
			if (Set_Add(T)(result, set1->items[i]) == NULL)
			{
				Set_Free(T)(result);
				return (NULL);
			}
		}
	}
	return (result);
}



_GENERIC()
s_set(T)*	Set_Difference(T)(s_set(T) const* set1, s_set(T) const* set2)
{
	s_set(T)*	result;
	t_uint	i;

	if CCCERROR((set1 == NULL), ERROR_NULLPOINTER, "set1 given is NULL")
		return (NULL);
	if CCCERROR((set2 == NULL), ERROR_NULLPOINTER, "set2 given is NULL")
		return (NULL);
	result = Set_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < set1->length; ++i)
	{
		if (!Set_Contains(T)(set2, set1->items[i]))
		{
			if (Set_Add(T)(result, set1->items[i]) == NULL)
			{
				Set_Free(T)(result);
				return (NULL);
			}
		}
	}
	return (result);
}
