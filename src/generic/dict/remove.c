
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Dict_Remove(T)(s_dict(T)* dict, t_char const* key)
{
	s_keyval(T)*	keyval;
	t_uint	index;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	if CCCERROR((key == NULL), ERROR_NULLPOINTER, "key string given is NULL")
		return;
	keyval = Dict_Find(T)(dict, key);
	if (keyval == NULL)
		return;
	index = (t_uint)(keyval - dict->items);
	KeyVal_Free(T)(&dict->items[index]);
	dict->length -= 1;
	if (dict->length == 0)
	{
		Memory_Free(dict->items);
		dict->items = NULL;
		return;
	}
	for (t_uint i = index; i < dict->length; ++i)
	{
		dict->items[i] = dict->items[i + 1];
	}
}

_GENERIC()
void	Dict_Remove_F(T)(s_dict(T)* dict, t_char const* key, void (*del)(T value))
{
	s_keyval(T)*	keyval;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	keyval = Dict_Find(T)(dict, key);
	if (keyval == NULL)
		return;
	del(keyval->value);
	Dict_Remove(T)(dict, key);
}

_GENERIC()
void	Dict_RemoveMatch(T)(s_dict(T)* dict, T value)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
		{
			Dict_Remove(T)(dict, dict->items[i].key);
			return;
		}
	}
}

_GENERIC()
void	Dict_RemoveMatch_F(T)(s_dict(T)* dict, T value, void (*del)(T value))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
		{
			del(dict->items[i].value);
			Dict_Remove(T)(dict, dict->items[i].key);
			return;
		}
	}
}

_GENERIC()
void	Dict_RemoveMatches(T)(s_dict(T)* dict, T value)
{
	t_uint	amount;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	amount = 0; // used as the write index while compacting the items array
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
		{
			KeyVal_Free(T)(&dict->items[i]);
			continue;
		}
		dict->items[amount++] = dict->items[i];
	}
	dict->length = amount;
	if (dict->length == 0)
	{
		Memory_Free(dict->items);
		dict->items = NULL;
	}
}

_GENERIC()
void	Dict_RemoveMatches_F(T)(s_dict(T)* dict, T value, void (*del)(T value))
{
	t_uint	amount;

	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	amount = 0; // used as the write index while compacting the items array
	for (t_uint i = 0; i < dict->length; ++i)
	{
		if (T_EQUALS(dict->items[i].value, value))
		{
			del(dict->items[i].value);
			KeyVal_Free(T)(&dict->items[i]);
			continue;
		}
		dict->items[amount++] = dict->items[i];
	}
	dict->length = amount;
	if (dict->length == 0)
	{
		Memory_Free(dict->items);
		dict->items = NULL;
	}
}
