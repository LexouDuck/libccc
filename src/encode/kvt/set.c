
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	KVT_SetValue_Boolean(s_kvt* object, t_bool value)
{
	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR_SF(WRONGTYPE,
		!(object->type & DYNAMICTYPE_BOOLEAN),
		return (ERROR_WRONGTYPE);,
		"attempted to read value as boolean, but type is "SF_ENUM, object->type)
	object->value.boolean = value;
	return (OK);
}

e_cccerror	KVT_SetValue_Integer(s_kvt* object, t_s64 value)
{
	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR_SF(WRONGTYPE,
		!(object->type & DYNAMICTYPE_INTEGER),
		return (ERROR_WRONGTYPE);,
		"attempted to read value as integer, but type is "SF_ENUM, object->type)
	object->value.integer = value;
	return (OK);
}

e_cccerror	KVT_SetValue_Float(s_kvt* object, t_f64 value)
{
	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR_SF(WRONGTYPE,
		!(object->type & DYNAMICTYPE_FLOAT),
		return (ERROR_WRONGTYPE);,
		"attempted to read value as float, but type is "SF_ENUM, object->type)
	object->value.number = value;
	return (OK);
}

e_cccerror	KVT_SetValue_String(s_kvt* object, t_char* value)
{
	t_char* copy = NULL;

	HANDLE_ERROR(NULLPOINTER, (object == NULL), return (ERROR_NULLPOINTER);)
	HANDLE_ERROR_SF(WRONGTYPE,
		!(object->type & DYNAMICTYPE_STRING),
		return (ERROR_WRONGTYPE);,
		"attempted to read value as string, but type is "SF_ENUM, object->type)
	// if object's type is not DYNAMICTYPE_STRING or is DYNAMICTYPE_ISREFERENCE, it should not set value.string
	HANDLE_ERROR(DELETEREF,
		((object->type & DYNAMICTYPE_ISREFERENCE)),
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
