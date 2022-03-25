
#include "libccc.h"
#include "libccc/enum.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_size	Enum_Parse(t_enum *dest, t_size n, t_char const* str, s_enum_type const* enum_type)
{
	HANDLE_ERROR(NULLPOINTER, (dest      == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (str       == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (enum_type == NULL), return (0);)
	t_size	length = String_Length(str);
	if (length < n)
		n = length;
	for (t_uint i = 0; i < enum_type->length; ++i)
	{
		if (String_Equals_N(str, enum_type->items[i].name, n))
		{
			*dest = enum_type->items[i].value;
			return (n);
		}
	}
	HANDLE_ERROR_SF(NOTFOUND,
		(TRUE), return (0);,
		"enum type \"%s\" has no item with name \"%s\"", enum_type->name, str)
}



inline
t_enum	Enum_FromString(t_char const* str, s_enum_type const* enum_type)
{
	t_size	length = String_Length(str);
	t_enum	result = 0;
	Enum_Parse(&result, length, str, enum_type);
	return (result);
}
