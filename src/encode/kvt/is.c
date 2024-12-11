
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline
t_bool	KVT_IsInvalid(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_INVALID);
	// TODO check for conflicting type flags
}

extern inline
t_bool	KVT_IsNull(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_NULL);
}

extern inline
t_bool	KVT_IsBoolean(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_BOOLEAN) != 0);
}

extern inline
t_bool	KVT_IsInteger(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_INTEGER);
}

extern inline
t_bool	KVT_IsFloat(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_FLOAT);
}

extern inline
t_bool	KVT_IsString(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_STRING);
}

extern inline
t_bool	KVT_IsArray(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_ARRAY);
}

extern inline
t_bool	KVT_IsObject(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_OBJECT);
}

extern inline
t_bool	KVT_IsRaw(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_RAW);
}
