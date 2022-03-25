
#include "libccc.h"
#include "libccc/enum.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char const*	Enum_String(t_enum value, s_enum_type const* enum_type)
{
	HANDLE_ERROR(NULLPOINTER, (enum_type == NULL), return (NULL);)
	for (t_uint i = 0; i < enum_type->length; ++i)
	{
		if (value == enum_type->items[i].value)
		{
			return (enum_type->items[i].name);
		}
	}
	HANDLE_ERROR(INVALIDENUM,
		(TRUE), return (NULL);)
}

t_size	Enum_Print(t_char* dest, t_enum value, s_enum_type const* enum_type)
{
	t_char const*	name;
	t_size	length;
	HANDLE_ERROR(NULLPOINTER, (enum_type == NULL), return (0);)
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
