
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	StringArray_Equals(t_char const* const* strarr1, t_char const* const* strarr2)
{
	t_uint	length1;
	t_uint	length2;

	if (strarr1 == strarr2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (strarr1 == NULL), return (strarr1 - strarr2);)
	HANDLE_ERROR(NULLPOINTER, (strarr2 == NULL), return (strarr1 - strarr2);)
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	for (t_uint i = 0; (i < length1) && (i < length2); ++i)
	{
		if (String_Equals(strarr1[i], strarr2[i]))
			return (FALSE);
	}
	return (TRUE);
}


t_bool	StringArray_Equals_N(t_char const* const* strarr1, t_char const* const* strarr2, t_uint n)
{
	t_uint	length1;
	t_uint	length2;

	if (strarr1 == strarr2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (strarr1 == NULL), return (strarr1 - strarr2);)
	HANDLE_ERROR(NULLPOINTER, (strarr2 == NULL), return (strarr1 - strarr2);)
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	for (t_uint i = 0; (i < n) && (i < length1) && (i < length2); ++i)
	{
		if (String_Equals(strarr1[i], strarr2[i]))
			return (FALSE);
	}
	return (TRUE);
}
