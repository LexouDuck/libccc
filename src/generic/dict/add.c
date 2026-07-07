
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_keyval(T)*	Dict_Add(T)(s_dict(T)* dict, t_char const* key, T value)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "key string given is NULL")
		return (NULL);
	if CCCERROR((Dict_Find(T)(dict, key) != NULL), ERROR_INVALIDARGS,
		"a value with key \"%s\" already exists in this dict", key)
		return (NULL);
	return (Dict_Set(T)(dict, key, value));
}
