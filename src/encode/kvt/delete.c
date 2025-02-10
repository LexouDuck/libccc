
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	KVT_Delete(s_kvt* item)
{
	if CCCERROR((item == NULL), ERROR_NULLPOINTER, "KVT item given is NULL")
		return (ERROR_NULLPOINTER);
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
					e_cccerror error = KVT_Delete(item->value.child);
					if (error)	return (error);
				}
			}
			else if ((item->type & DYNAMICTYPE_STRING))
			{
				if (item->value.string != NULL)
					String_Delete(&item->value.string);
			}
		}
		if (item->key != NULL)
		{
			String_Delete(&item->key);
		}
		Memory_Delete((void* *)&item);
		item = next;
	}
	return (ERROR_NONE);
}

e_cccerror	KVT_Delete_FromArray(s_kvt* array, t_sint index)
{
	s_kvt*	tmp;

	if CCCERROR((array == NULL), ERROR_NULLPOINTER, "KVT array given is NULL")
		return (ERROR_NULLPOINTER);
	tmp = KVT_Detach_FromArray(array, index);
	if CCCERROR((tmp == NULL), ERROR_INDEX2LARGE,
		"could not delete array value, invalid index: " SF_SINT, index)
		return (ERROR_INDEX2LARGE);
	return (KVT_Delete(tmp));
}

e_cccerror	KVT_Delete_FromObject_IgnoreCase(s_kvt* object, t_char const* key)
{
	s_kvt*	tmp;

	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "KVT object given is NULL")
		return (ERROR_NULLPOINTER);
	tmp = KVT_Detach_FromObject_IgnoreCase(object, key);
	if CCCERROR((tmp == NULL), ERROR_KEYNOTFOUND,
		"could not delete object value, no matching key: \"%s\"", key)
		return (ERROR_KEYNOTFOUND);
	return (KVT_Delete(tmp));
}

e_cccerror	KVT_Delete_FromObject_CaseSensitive(s_kvt* object, t_char const* key)
{
	s_kvt*	tmp;

	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "KVT object given is NULL")
		return (ERROR_NULLPOINTER);
	tmp = KVT_Detach_FromObject_CaseSensitive(object, key);
	if CCCERROR((tmp == NULL), ERROR_KEYNOTFOUND,
		"could not delete object value, no matching key: \"%s\"", key)
		return (ERROR_KEYNOTFOUND);
	return (KVT_Delete(tmp));
}
