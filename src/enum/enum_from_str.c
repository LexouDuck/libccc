
#include "libccc.h"
#include "libccc/enum.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_size	Enum_Parse(t_enum *dest, t_size n, t_char const* str, s_enum_type const* enum_type)
{
	if CCCERROR((dest      == NULL), ERROR_NULLPOINTER, "destination given is NULL")
		return (SIZE_ERROR);
	if CCCERROR((str       == NULL), ERROR_NULLPOINTER, "string to parse is NULL")
		return (SIZE_ERROR);
	if CCCERROR((enum_type == NULL), ERROR_NULLPOINTER, "enum_type struct given is NULL")
		return (SIZE_ERROR);
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
	if CCCERROR((TRUE), ERROR_NOTFOUND, "enum type \"%s\" has no item named \"%s\"", enum_type->name, str)
		return (SIZE_ERROR);
}



inline
t_enum	Enum_FromString(t_char const* str, s_enum_type const* enum_type)
{
	t_size	length = String_Length(str);
	t_enum	result = 0;
	Enum_Parse(&result, length, str, enum_type);
	return (result);
}
