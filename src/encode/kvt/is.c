
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
t_bool	KVT_IsInvalid(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_INVALID);
	// TODO check for conflicting type flags
}

inline
t_bool	KVT_IsNull(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_NULL);
}

inline
t_bool	KVT_IsBoolean(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_BOOLEAN) != 0);
}

inline
t_bool	KVT_IsInteger(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_INTEGER);
}

inline
t_bool	KVT_IsFloat(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_FLOAT);
}

inline
t_bool	KVT_IsString(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_STRING);
}

inline
t_bool	KVT_IsArray(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_ARRAY);
}

inline
t_bool	KVT_IsObject(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_OBJECT);
}

inline
t_bool	KVT_IsRaw(s_kvt const* item)
{
	if (item == NULL)
		return (FALSE);
	return ((item->type & DYNAMICTYPE_MASK) == DYNAMICTYPE_RAW);
}
