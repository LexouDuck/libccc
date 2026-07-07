
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void*	Dict_Reduce(T)(s_dict(T) const* dict, void* (*f)(s_keyval(T) keyval, void* acc))
{
	void*	accumulator = NULL;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (NULL);
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		accumulator = f(dict->items[i], accumulator);
	}
	return (accumulator);
}

_GENERIC()
void*	Dict_Fold(T)(s_dict(T) const* dict, void* (*f)(s_keyval(T) keyval, void* acc), void* initial)
{
	void*	accumulator = initial;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return (initial);
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (initial);
	for (t_uint i = 0; i < dict->length; ++i)
	{
		accumulator = f(dict->items[i], accumulator);
	}
	return (accumulator);
}
