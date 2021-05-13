
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"



t_bool	KVT_IsInvalid(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_INVALID);
}

t_bool	KVT_IsNull(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_NULL);
}

t_bool	KVT_IsBoolean(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_BOOLEAN) != 0);
}

t_bool	KVT_IsInteger(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_INTEGER);
}

t_bool	KVT_IsFloat(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_FLOAT);
}

t_bool	KVT_IsString(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_STRING);
}

t_bool	KVT_IsArray(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_ARRAY);
}

t_bool	KVT_IsObject(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_OBJECT);
}

t_bool	KVT_IsRaw(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMIC_TYPE_MASK) == DYNAMIC_TYPE_RAW);
}
