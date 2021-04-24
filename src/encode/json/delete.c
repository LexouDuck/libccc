
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/encode/json.h"



void	JSON_Delete(s_json* item)
{
	s_json* next = NULL;
	while (item != NULL)
	{
		next = item->next;
		if (!(item->type & JSON_TYPE_ISREFERENCE) && (item->child != NULL))
		{
			JSON_Delete(item->child);
		}
		if (!(item->type & JSON_TYPE_ISREFERENCE) && (item->value_string != NULL))
		{
			Memory_Free(item->value_string);
		}
		if (!(item->type & JSON_TYPE_CONSTSTRING) && (item->key != NULL))
		{
			Memory_Free(item->key);
		}
		Memory_Free(item);
		item = next;
	}
}

void	JSON_DeleteItemFromArray(s_json* array, t_sint which)
{
	JSON_Delete(JSON_DetachItemFromArray(array, which));
}

void	JSON_DeleteItemFromObject(s_json* object, t_char const* key)
{
	JSON_Delete(JSON_DetachItemFromObject(object, key));
}

void	JSON_DeleteItemFromObject_CaseSensitive(s_json* object, t_char const* key)
{
	JSON_Delete(JSON_DetachItemFromObject_CaseSensitive(object, key));
}
