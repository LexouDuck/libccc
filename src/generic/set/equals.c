
#include "libccc/memory.h"
#include "libccc/generic/set.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Set_Equals(T)(s_set(T) const* set1, s_set(T) const* set2)
{
	t_uint	i;

	if (set1 == set2)
		return (TRUE);
	if CCCERROR((set1 == NULL), ERROR_NULLPOINTER, "set1 given is NULL")
		return (FALSE);
	if CCCERROR((set2 == NULL), ERROR_NULLPOINTER, "set2 given is NULL")
		return (FALSE);
	if (set1->length != set2->length)
		return (FALSE);
	// NOTE: this comparison is order-independent: since both sets hold unique
	// values and have the same length, checking that every item of `set1` is
	// contained in `set2` is sufficient to prove that both sets are equal
	for (i = 0; i < set1->length; ++i)
	{
		if (!Set_Contains(T)(set2, set1->items[i]))
			return (FALSE);
	}
	return (TRUE);
}



_GENERIC()
t_bool	Set_IsSubset(T)(s_set(T) const* sub, s_set(T) const* super)
{
	t_uint	i;

	if CCCERROR((sub == NULL), ERROR_NULLPOINTER, "subset given is NULL")
		return (FALSE);
	if CCCERROR((super == NULL), ERROR_NULLPOINTER, "superset given is NULL")
		return (FALSE);
	if (sub == super)
		return (TRUE);
	if (sub->length > super->length)
		return (FALSE);
	for (i = 0; i < sub->length; ++i)
	{
		if (!Set_Contains(T)(super, sub->items[i]))
			return (FALSE);
	}
	return (TRUE);
}



_GENERIC()
t_bool	Set_IsDisjoint(T)(s_set(T) const* set1, s_set(T) const* set2)
{
	t_uint	i;

	if CCCERROR((set1 == NULL), ERROR_NULLPOINTER, "set1 given is NULL")
		return (FALSE);
	if CCCERROR((set2 == NULL), ERROR_NULLPOINTER, "set2 given is NULL")
		return (FALSE);
	for (i = 0; i < set1->length; ++i)
	{
		if (Set_Contains(T)(set2, set1->items[i]))
			return (FALSE);
	}
	return (TRUE);
}
