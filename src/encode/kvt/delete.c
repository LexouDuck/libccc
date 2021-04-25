
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"



void	KVT_Delete(s_kvt* item)
{
	s_kvt* next = NULL;
	while (item != NULL)
	{
		next = item->next;
		if (!(item->type & KVT_TYPE_ISREFERENCE) && (item->child != NULL))
		{
			KVT_Delete(item->child);
		}
		if (!(item->type & KVT_TYPE_ISREFERENCE) && (item->value_string != NULL))
		{
			Memory_Free(item->value_string);
		}
		if (!(item->type & KVT_TYPE_CONSTSTRING) && (item->key != NULL))
		{
			Memory_Free(item->key);
		}
		Memory_Free(item);
		item = next;
	}
}

void	KVT_DeleteItemFromArray(s_kvt* array, t_sint which)
{
	KVT_Delete(KVT_DetachItemFromArray(array, which));
}

void	KVT_DeleteItemFromObject(s_kvt* object, t_char const* key)
{
	KVT_Delete(KVT_DetachItemFromObject(object, key));
}

void	KVT_DeleteItemFromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	KVT_Delete(KVT_DetachItemFromObject_CaseSensitive(object, key));
}
