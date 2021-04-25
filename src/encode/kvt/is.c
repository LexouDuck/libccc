
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"



t_bool	KVT_IsInvalid(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_INVALID;
}

t_bool	KVT_IsFalse(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_FALSE;
}

t_bool	KVT_IsTrue(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & 0xff) == KVT_TYPE_TRUE;
}

t_bool	KVT_IsBool(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & (KVT_TYPE_TRUE | KVT_TYPE_FALSE)) != 0;
}
t_bool	KVT_IsNull(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_NULL;
}

t_bool	KVT_IsNumber(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_NUMBER;
}

t_bool	KVT_IsString(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_STRING;
}

t_bool	KVT_IsArray(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_ARRAY;
}

t_bool	KVT_IsObject(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_OBJECT;
}

t_bool	KVT_IsRaw(s_kvt const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & KVT_TYPE_MASK) == KVT_TYPE_RAW;
}
