
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
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
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
	HANDLE_ERROR(NOTFOUND, (TRUE), return (NULL);)
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
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
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
	HANDLE_ERROR(NOTFOUND, (TRUE), return (ERROR);)
}
