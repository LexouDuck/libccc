
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
s_dict(T)*	Dict_Duplicate(T)(s_dict(T) const* dict)
{
	s_dict(T)*	result;

	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return (NULL);
	if CCCERROR((dict->length > 0 && dict->items == NULL), ERROR_INVALIDARGS,
		"dict given is invalid - `.length` doesn't match `.items`")
		return (NULL);
	result = Dict_New(T)();
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (dict->length == 0)
		return (result);
	result->items = (s_keyval(T)*)Memory_Allocate(dict->length * sizeof(s_keyval(T)));
	if CCCERROR((result->items == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(result);
		return (NULL);
	}
	for (t_uint i = 0; i < dict->length; ++i)
	{
		result->items[i].hash = dict->items[i].hash;
		result->items[i].value = dict->items[i].value;
		result->items[i].key = String_Duplicate(dict->items[i].key);
		if CCCERROR((result->items[i].key == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			result->length = i;
			Dict_Free(T)(result);
			return (NULL);
		}
	}
	result->length = dict->length;
	return (result);
}
