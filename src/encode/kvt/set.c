
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



e_cccerror	KVT_SetValue_Boolean(s_kvt* object, t_bool value)
{
	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "cannot set value on NULL kvt")
		return (ERROR_NULLPOINTER);
	if CCCERROR(!(object->type & DYNAMICTYPE_BOOLEAN), ERROR_WRONGTYPE,
		"attempted to read value as boolean, but type is " SF_ENUM, object->type)
		return (ERROR_WRONGTYPE);
	object->value.boolean = value;
	return (ERROR_NONE);
}

e_cccerror	KVT_SetValue_Integer(s_kvt* object, t_s64 value)
{
	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "cannot set value on NULL kvt")
		return (ERROR_NULLPOINTER);
	if CCCERROR(!(object->type & DYNAMICTYPE_INTEGER), ERROR_WRONGTYPE,
		"attempted to read value as integer, but type is " SF_ENUM, object->type)
		return (ERROR_WRONGTYPE);
	object->value.integer = value;
	return (ERROR_NONE);
}

e_cccerror	KVT_SetValue_Float(s_kvt* object, t_f64 value)
{
	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "cannot set value on NULL kvt")
		return (ERROR_NULLPOINTER);
	if CCCERROR(!(object->type & DYNAMICTYPE_FLOAT), ERROR_WRONGTYPE,
		"attempted to read value as float, but type is " SF_ENUM, object->type)
		return (ERROR_WRONGTYPE);
	object->value.number = value;
	return (ERROR_NONE);
}

e_cccerror	KVT_SetValue_String(s_kvt* object, t_char* value)
{
	t_char* copy = NULL;

	if CCCERROR((object == NULL), ERROR_NULLPOINTER, "cannot set value on NULL kvt")
		return (ERROR_NULLPOINTER);
	if CCCERROR(!(object->type & DYNAMICTYPE_STRING), ERROR_WRONGTYPE,
		"attempted to read value as string, but type is " SF_ENUM, object->type)
		return (ERROR_WRONGTYPE);
	// if object's type is not DYNAMICTYPE_STRING or is DYNAMICTYPE_ISREFERENCE, it should not set value.string
	if CCCERROR(((object->type & DYNAMICTYPE_ISREFERENCE)), ERROR_DELETEREF, NULL)
		return (ERROR_DELETEREF);
	if (String_Length(value) <= String_Length(object->value.string))
	{
		String_Copy(object->value.string, value);
		return (ERROR_NONE);
	}
    copy = (t_char*)String_Duplicate((t_char const*)value);
	if CCCERROR((copy == NULL), ERROR_ALLOCFAILURE, NULL)
		return (ERROR_ALLOCFAILURE);
	if (object->value.string != NULL)
	{
		Memory_Free(object->value.string);
	}
	object->value.string = copy;
	return (ERROR_NONE);
}
