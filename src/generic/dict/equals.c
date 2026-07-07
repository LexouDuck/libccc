
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Dict_Equals(T)(s_dict(T) const* dict1, s_dict(T) const* dict2)
{
	s_keyval(T)*	keyval;

	if (dict1 == dict2)
		return (TRUE);
	if CCCERROR((dict1 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if CCCERROR((dict2 == NULL), ERROR_NULLPOINTER, NULL) return (FALSE);
	if (dict1->length != dict2->length)
		return (FALSE);
	// NOTE: this check is order-independent: since keys within a dict are unique,
	// having equal lengths and finding every pair of `dict1` in `dict2` is sufficient
	for (t_uint i = 0; i < dict1->length; ++i)
	{
		keyval = Dict_Find(T)(dict2, dict1->items[i].key);
		if (keyval == NULL)
			return (FALSE);
		if (!T_EQUALS(dict1->items[i].value, keyval->value))
			return (FALSE);
	}
	return (TRUE);
}
