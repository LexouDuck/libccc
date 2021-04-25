
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



t_f64	KVT_SetValue_Number(s_kvt* object, t_f64 value)
{
	object->value_number = value;
	return (value);
}

t_char*	KVT_SetValue_String(s_kvt* object, t_char* value)
{
	t_char* copy = NULL;
	// if object's type is not KVT_TYPE_STRING or is KVT_TYPE_ISREFERENCE, it should not set value_string
	if (!(object->type & KVT_TYPE_STRING) || (object->type & KVT_TYPE_ISREFERENCE))
		return (NULL);
	if (String_Length(value) <= String_Length(object->value_string))
	{
		String_Copy(object->value_string, value);
		return (object->value_string);
	}
    copy = (t_char*)String_Duplicate((t_char const*)value);
	if (copy == NULL)
		return (NULL);
	if (object->value_string != NULL)
	{
		Memory_Free(object->value_string);
	}
	object->value_string = copy;
	return (copy);
}
