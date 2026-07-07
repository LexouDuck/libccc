
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
T*	Dict_Get(T)(s_dict(T) const* dict, t_char const* key)
{
	s_keyval(T)*	keyval;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "key string given is NULL")
		return (NULL);
	keyval = Dict_Find(T)(dict, key);
	if CCCERROR((keyval == NULL), ERROR_KEYNOTFOUND,
		"no value with key \"%s\" exists in this dict", key)
		return (NULL);
	return (&keyval->value);
}
