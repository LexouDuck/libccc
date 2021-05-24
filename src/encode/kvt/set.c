
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_HANDLE_INCLUDE



e_stderror	KVT_SetValue_Boolean(s_kvt* object, t_bool value)
{
	HANDLE_ERROR(WRONGTYPE, !(object->type & DYNAMICTYPE_BOOLEAN),
		return (ERROR_WRONGTYPE);)
	object->value.boolean = value;
	return (OK);
}

e_stderror	KVT_SetValue_Integer(s_kvt* object, t_s64 value)
{
	HANDLE_ERROR(WRONGTYPE, !(object->type & DYNAMICTYPE_INTEGER),
		return (ERROR_WRONGTYPE);)
	object->value.integer = value;
	return (OK);
}

e_stderror	KVT_SetValue_Float(s_kvt* object, t_f64 value)
{
	HANDLE_ERROR(WRONGTYPE, !(object->type & DYNAMICTYPE_FLOAT),
		return (ERROR_WRONGTYPE);)
	object->value.number = value;
	return (OK);
}

e_stderror	KVT_SetValue_String(s_kvt* object, t_char* value)
{
	t_char* copy = NULL;
	// if object's type is not DYNAMICTYPE_STRING or is DYNAMICTYPE_ISREFERENCE, it should not set value.string
	HANDLE_ERROR(WRONGTYPE, !(object->type & DYNAMICTYPE_STRING),
		return (ERROR_WRONGTYPE);)
	HANDLE_ERROR(DELETEREF, ((object->type & DYNAMICTYPE_ISREFERENCE)),
		return (ERROR_DELETEREF);)
	if (String_Length(value) <= String_Length(object->value.string))
	{
		String_Copy(object->value.string, value);
		return (OK);
	}
    copy = (t_char*)String_Duplicate((t_char const*)value);
	HANDLE_ERROR(ALLOCFAILURE, (copy == NULL),
		return (ERROR_ALLOCFAILURE);)
	if (object->value.string != NULL)
	{
		Memory_Free(object->value.string);
	}
	object->value.string = copy;
	return (OK);
}
