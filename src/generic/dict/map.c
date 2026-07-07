
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_dict(T)*	Dict_Map(T)(s_dict(T) const* dict, T (*map)(t_char const* key, T value))
{
	s_dict(T)*	result;

	if CCCERROR((map == NULL), ERROR_NULLPOINTER, "map() function given is NULL")
		return (NULL);
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	result = Dict_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (Dict_Set(T)(result, dict->items[i].key,
			map(dict->items[i].key, dict->items[i].value)) == NULL)
		{
			Dict_Free(T)(result);
			return (NULL);
		}
	}
	return (result);
}
