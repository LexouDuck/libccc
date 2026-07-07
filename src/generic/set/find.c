
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Set_Find(T)(s_set(T) const* set, T item)
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	for (i = 0; i < set->length; ++i)
	{
		if (T_EQUALS(set->items[i], item))
			return ((T*)&set->items[i]);
	}
	// NOTE: no error is set here: an absent item is a normal occurrence
	// (this function is used as a membership probe by several other functions)
	return (NULL);
}



_GENERIC()
T*	Set_Find_F(T)(s_set(T) const* set, t_bool (*match)(T item))
{
	t_uint	i;

	if CCCERROR((set == NULL), ERROR_NULLPOINTER, "set given is NULL")
		return (NULL);
	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (NULL);
	for (i = 0; i < set->length; ++i)
	{
		if (match(set->items[i]))
			return ((T*)&set->items[i]);
	}
	return (NULL);
}



_GENERIC()
t_bool	Set_Contains(T)(s_set(T) const* set, T item)
{
	return (Set_Find(T)(set, item) != NULL);
}
