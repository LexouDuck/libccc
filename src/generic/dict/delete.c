
#include "libccc/memory.h"
#include "libccc/generic/dict.h"

#include LIBCONFIG_ERROR_INCLUDE



_GENERIC()
void	Dict_Free(T)(s_dict(T)* dict)
{
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	for (t_uint i = 0; i < dict->length; ++i)
	{
		KeyVal_Free(T)(&dict->items[i]);
	}
	Memory_Free(dict->items);
	dict->items = NULL;
	dict->length = 0;
	Memory_Free(dict);
}

_GENERIC()
void	Dict_Free_F(T)(s_dict(T)* dict, void (*del)(T value))
{
	if CCCERROR((del == NULL), ERROR_NULLPOINTER, "del() function given is NULL")
		return;
	if CCCERROR((dict == NULL), ERROR_NULLPOINTER, "dict given is NULL")
		return;
	for (t_uint i = 0; i < dict->length; ++i)
	{
		del(dict->items[i].value);
		KeyVal_Free(T)(&dict->items[i]);
	}
	Memory_Free(dict->items);
	dict->items = NULL;
	dict->length = 0;
	Memory_Free(dict);
}

_GENERIC()
void	Dict_Delete(T)(s_dict(T)* *a_dict)
{
	if CCCERROR((a_dict == NULL), ERROR_NULLPOINTER, "dict address given is NULL")
		return;
	if CCCERROR((*a_dict == NULL), ERROR_NULLPOINTER, NULL)
		return;
	Dict_Free(T)(*a_dict);
	(*a_dict) = NULL;
}

_GENERIC()
void	Dict_Delete_F(T)(s_dict(T)* *a_dict, void (*del)(T value))
{
	if CCCERROR((a_dict == NULL), ERROR_NULLPOINTER, "dict address given is NULL")
		return;
	if CCCERROR((*a_dict == NULL), ERROR_NULLPOINTER, NULL)
		return;
	Dict_Free_F(T)(*a_dict, del);
	(*a_dict) = NULL;
}
