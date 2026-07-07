
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
t_uint	Dict_Count(T)(s_dict(T) const* dict, T value)
{
	t_uint	result = 0;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (0);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
			result += 1;
	}
	return (result);
}

_GENERIC()
t_bool	Dict_Contains(T)(s_dict(T) const* dict, T value)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (FALSE);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
			return (TRUE);
	}
	return (FALSE);
}
