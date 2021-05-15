
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



e_error_kvt	KVT_SetValue_Boolean(s_kvt* object, t_bool value)
{
	if (!(object->type & DYNAMICTYPE_BOOLEAN))
		return (KVT_SetError(ERROR_KVT_INCORRECTTYPE));
	object->value.boolean = value;
	return (OK);
}

e_error_kvt	KVT_SetValue_Integer(s_kvt* object, t_s64 value)
{
	if (!(object->type & DYNAMICTYPE_INTEGER))
		return (KVT_SetError(ERROR_KVT_INCORRECTTYPE));
	object->value.integer = value;
	return (OK);
}

e_error_kvt	KVT_SetValue_Float(s_kvt* object, t_f64 value)
{
	if (!(object->type & DYNAMICTYPE_FLOAT))
		return (KVT_SetError(ERROR_KVT_INCORRECTTYPE));
	object->value.number = value;
	return (OK);
}

e_error_kvt	KVT_SetValue_String(s_kvt* object, t_char* value)
{
	t_char* copy = NULL;
	// if object's type is not DYNAMICTYPE_STRING or is DYNAMICTYPE_ISREFERENCE, it should not set value.string
	if (!(object->type & DYNAMICTYPE_STRING))
		return (KVT_SetError(ERROR_KVT_INCORRECTTYPE));
	if ((object->type & DYNAMICTYPE_ISREFERENCE))
		return (KVT_SetError(ERROR_KVT_ISREFERENCE));
	if (String_Length(value) <= String_Length(object->value.string))
	{
		String_Copy(object->value.string, value);
		return (OK);
	}
    copy = (t_char*)String_Duplicate((t_char const*)value);
	if (copy == NULL)
		return (KVT_SetError(ERROR_KVT_ALLOCATIONFAILURE));
	if (object->value.string != NULL)
	{
		Memory_Free(object->value.string);
	}
	object->value.string = copy;
	return (OK);
}
