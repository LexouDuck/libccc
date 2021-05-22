
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



e_error_kvt	KVT_Delete(s_kvt* item)
{
	s_kvt* next = NULL;
	while (item != NULL)
	{
		next = item->next;
		if (!(item->type & DYNAMICTYPE_ISREFERENCE))
		{
			if ((item->type & DYNAMICTYPE_ARRAY) ||
				(item->type & DYNAMICTYPE_OBJECT))
			{
				if (item->value.child != NULL)
				{
					e_error_kvt error = KVT_Delete(item->value.child);
					if (error)	return (error);
				}
			}
			else if ((item->type & DYNAMICTYPE_STRING))
			{
				if (item->value.string != NULL)
					Memory_Free(item->value.string);
			}
		}
		if (item->key != NULL)
		{
			Memory_Free(item->key);
		}
		Memory_Free(item);
		item = next;
	}
	return (OK);
}

e_error_kvt	KVT_Delete_FromArray(s_kvt* array, t_sint which)
{
	return (KVT_Delete(KVT_Detach_FromArray(array, which)));
}

e_error_kvt	KVT_Delete_FromObject_IgnoreCase(s_kvt* object, t_char const* key)
{
	return (KVT_Delete(KVT_Detach_FromObject_IgnoreCase(object, key)));
}

e_error_kvt	KVT_Delete_FromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	return (KVT_Delete(KVT_Detach_FromObject_CaseSensitive(object, key)));
}
