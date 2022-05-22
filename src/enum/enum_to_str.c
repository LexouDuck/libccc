
#include "libccc.h"
#include "libccc/enum.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char const*	Enum_String(t_enum value, s_enum_type const* enum_type)
{
	if CCCERROR((enum_type == NULL), ERROR_NULLPOINTER, NULL)
		return (NULL);
	for (t_uint i = 0; i < enum_type->length; ++i)
	{
		if (value == enum_type->items[i].value)
		{
			return (enum_type->items[i].name);
		}
	}
	CCCERROR(TRUE, ERROR_INVALIDENUM, "Invalid enum value (%d) for enum type %s", value, enum_type->name);
	return (NULL);
}

t_size	Enum_Print(t_char* dest, t_enum value, s_enum_type const* enum_type)
{
	t_char const*	name;
	t_size	length;
	if CCCERROR((enum_type == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	name = Enum_String(value, enum_type);
	if (name == NULL)
		return (0);
	length = String_Length(name);
	String_Copy_N(dest, name, length);
	return (length);
}

inline
t_char*	Enum_ToString(t_enum value, s_enum_type const* enum_type)
{
	return (String_Duplicate(Enum_String(value, enum_type)));
}
