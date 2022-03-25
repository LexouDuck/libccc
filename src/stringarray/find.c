
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char* const*	StringArray_Find(t_char* const* strarr, t_char const* str)
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length((t_char const* const*)strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (String_Equals(strarr[i], str))
			return (&(strarr[i]));
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no string matching \"%s\" found in string array of length "SF_UINT, str, length)
}


t_char* const*	StringArray_Find_F(t_char* const* strarr, t_bool (*match)(t_char const* str))
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length((t_char const* const*)strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (match(strarr[i]))
			return (&(strarr[i]));
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no matching string found in string array of length "SF_UINT, length)
}


t_sint	StringArray_IndexOf(t_char const* const* strarr, t_char const* str)
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (ERROR);)
	length = StringArray_Length(strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (String_Equals(strarr[i], str))
			return (i);
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (ERROR);,
		"no string matching \"%s\" found in string array of length "SF_UINT, str, length)
}


t_sint	StringArray_IndexOf_F(t_char const* const* strarr, t_bool (*match)(t_char const* str))
{
	t_uint	length;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (ERROR);)
	length = StringArray_Length(strarr);
	for (t_uint i = 0; i < length; ++i)
	{
		if (match(strarr[i]))
			return (i);
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (ERROR);,
		"no matching string found in string array of length "SF_UINT, length)
}
