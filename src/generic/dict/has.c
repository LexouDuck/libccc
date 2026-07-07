
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_bool	Dict_Has(T)(s_dict(T) const* dict, s_dict(T) const* target)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (FALSE);
	if CCCERROR((target == NULL), ERROR_NULLPOINTER, "target dict given is NULL")
		return (FALSE);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (Dict_HasKey(T)(target, dict->items[i].key))
			return (TRUE);
	}
	return (FALSE);
}

_GENERIC()
t_bool	Dict_HasOnly(T)(s_dict(T) const* dict, s_dict(T) const* target)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (FALSE);
	if CCCERROR((target == NULL), ERROR_NULLPOINTER, "target dict given is NULL")
		return (FALSE);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (!Dict_HasKey(T)(target, dict->items[i].key))
			return (FALSE);
	}
	return (TRUE);
}
