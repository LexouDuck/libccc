
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_keyval(T)*	Dict_Set(T)(s_dict(T)* dict, t_char const* key, T value)
{
	s_keyval(T)*	items;
	s_keyval(T)*	keyval;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "key string given is NULL")
		return (NULL);
	keyval = Dict_Find(T)(dict, key);
	if (keyval)
	{	// the key already exists in this dict: simply overwrite its associated value
		keyval->value = value;
		return (keyval);
	}
	// otherwise, append a new key/value pair at the end
	// NOTE: Memory_Reallocate() does not accept a NULL pointer (unlike standard realloc)
	if (dict->items == NULL)
		items = (s_keyval(T)*)Memory_Allocate((dict->length + 1) * sizeof(s_keyval(T)));
	else
		items = (s_keyval(T)*)Memory_Reallocate(dict->items, (dict->length + 1) * sizeof(s_keyval(T)));
	if CCCERROR((items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	dict->items = items;
	dict->items[dict->length] = KeyVal(T)(key, value);
	if CCCERROR((dict->items[dict->length].key == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL); // NOTE: `length` is not incremented, so the dict stays in a coherent state
	dict->length += 1;
	return (&dict->items[dict->length - 1]);
}
