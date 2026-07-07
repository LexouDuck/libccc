
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Dict_Iterate(T)(s_dict(T)* dict, void (*f)(s_keyval(T) keyval))
{
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	for (t_uint i = 0; i < dict->length; ++i)
	{
		f(dict->items[i]);
	}
}

_GENERIC()
void	Dict_Iterate_I(T)(s_dict(T)* dict, void (*f)(s_keyval(T) keyval, t_uint index))
{
	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	for (t_uint i = 0; i < dict->length; ++i)
	{
		f(dict->items[i], i);
	}
}
