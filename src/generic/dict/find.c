
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_keyval(T)*	Dict_Find(T)(s_dict(T) const* dict, t_char const* key)
{
	t_u64	hash;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "key string given is NULL")
		return (NULL);
	if CCCERROR((dict->length > 0 && dict->items == NULL), ERROR_INVALIDARGS,
		"dict given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	hash = Dict_HashKey(T)(key);
	for (t_uint i = 0; i < dict->length; ++i)
	{	// compare the cached hashes first (fast), and only compare the full strings if the hashes match
		if (dict->items[i].hash == hash && String_Equals(dict->items[i].key, key))
			return (&dict->items[i]);
	}
	return (NULL);
}

_GENERIC()
s_keyval(T)*	Dict_Find_F(T)(s_dict(T) const* dict, t_bool (*match)(s_keyval(T) keyval))
{
	if CCCERROR((match == NULL), ERROR_NULLPOINTER, "match() function given is NULL")
		return (NULL);
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (match(dict->items[i]))
			return (&dict->items[i]);
	}
	return (NULL);
}

_GENERIC()
t_bool	Dict_HasKey(T)(s_dict(T) const* dict, t_char const* key)
{
	if (dict == NULL || key == NULL)
		return (FALSE);
	return (Dict_Find(T)(dict, key) != NULL);
}

_GENERIC()
t_char const*	Dict_KeyOf(T)(s_dict(T) const* dict, T value)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
			return (dict->items[i].key);
	}
	return (NULL);
}
