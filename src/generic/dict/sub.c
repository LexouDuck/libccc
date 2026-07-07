
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_dict(T)*	Dict_Sub(T)(s_dict(T) const* dict, t_char const* const* keys)
{
	s_dict(T)*	result;
	s_keyval(T)*	keyval;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	if CCCERROR((keys == NULL), ERROR_NULLPOINTER, "keys list given is NULL")
		return (NULL);
	result = Dict_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (t_uint i = 0; keys[i]; ++i)
	{
		keyval = Dict_Find(T)(dict, keys[i]);
		if (keyval == NULL)
			continue; // keys which are not present in the given dict are simply ignored
		if (Dict_Set(T)(result, keyval->key, keyval->value) == NULL)
		{
			Dict_Free(T)(result);
			return (NULL);
		}
	}
	return (result);
}
