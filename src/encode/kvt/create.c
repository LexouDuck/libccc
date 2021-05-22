
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_kvt*	KVT_CreateNull(void)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_NULL;
	}
	return (item);
}

s_kvt*	KVT_CreateBoolean(t_bool value)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_BOOLEAN;
		item->value.boolean = value;
	}
	return (item);
}

s_kvt*	KVT_CreateInteger(t_s64 value)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_INTEGER;
		item->value.integer = value;
	}
	return (item);
}

s_kvt*	KVT_CreateFloat(t_f64 value)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_FLOAT;
		item->value.number = value;
	}
	return (item);
}

s_kvt*	KVT_CreateString(t_char const* string)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_STRING;
		item->value.string = (t_char*)String_Duplicate((t_char const*)string);
		if (!item->value.string)
		{
			KVT_Delete(item);
			return (NULL);
		}
	}
	return (item);
}

s_kvt*	KVT_CreateArray(void)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_ARRAY;
		item->value.child = NULL;
	}
	return (item);
}

s_kvt*	KVT_CreateObject(void)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_OBJECT;
		item->value.child = NULL;
	}
	return (item);
}

s_kvt*	KVT_CreateRaw(t_char const* raw)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_RAW;
		item->value.string = (t_char*)String_Duplicate((t_char const*)raw);
		if (!item->value.string)
		{
			KVT_Delete(item);
			return (NULL);
		}
	}
	return (item);
}



s_kvt*	KVT_CreateStringReference(t_char const* string)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_STRING;
		item->type |= DYNAMICTYPE_ISREFERENCE;
		item->value.string = (t_char*)string;
	}
	return (item);
}

s_kvt*	KVT_CreateObjectReference(s_kvt const* child)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_OBJECT;
		item->type |= DYNAMICTYPE_ISREFERENCE;
		item->value.child = (s_kvt*)child;
	}
	return (item);
}

s_kvt*	KVT_CreateArrayReference(s_kvt const* child)
{
	s_kvt* item = KVT_Item();
	if (item)
	{
		item->type = DYNAMICTYPE_ARRAY;
		item->type |= DYNAMICTYPE_ISREFERENCE;
		item->value.child = (s_kvt*)child;
	}
	return (item);
}
