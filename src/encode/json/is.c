
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/json.h"



t_bool	JSON_IsInvalid(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_INVALID;
}

t_bool	JSON_IsFalse(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_FALSE;
}

t_bool	JSON_IsTrue(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & 0xff) == JSON_TYPE_TRUE;
}

t_bool	JSON_IsBool(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & (JSON_TYPE_TRUE | JSON_TYPE_FALSE)) != 0;
}
t_bool	JSON_IsNull(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_NULL;
}

t_bool	JSON_IsNumber(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_NUMBER;
}

t_bool	JSON_IsString(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_STRING;
}

t_bool	JSON_IsArray(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_ARRAY;
}

t_bool	JSON_IsObject(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_OBJECT;
}

t_bool	JSON_IsRaw(s_json const* const item)
{
	if (item == NULL)
		return (FALSE);
	return (item->type & JSON_TYPE_MASK) == JSON_TYPE_RAW;
}
