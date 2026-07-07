
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_keyval(T)	KeyVal(T)(t_char const* key, T value)
{
	s_keyval(T)	result = { .hash = 0, .key = NULL, .value = value };

	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "key string given is NULL")
		return (result);
	result.key = String_Duplicate(key);
	if CCCERROR((result.key == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	result.hash = Dict_HashKey(T)(key);
	return (result);
}

_GENERIC()
void	KeyVal_Free(T)(s_keyval(T)* keyval)
{
	if CCCERROR((keyval == NULL), ERROR_NULLPOINTER, "keyval given is NULL")
		return;
	if (keyval->key)
	{
		Memory_Free(keyval->key);
		keyval->key = NULL;
	}
	keyval->hash = 0;
}
