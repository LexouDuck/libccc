
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_uint	String_Split_String_CountDistinctSubs(t_char const* str, t_char const* sub)
{
	t_uint	occ;
	t_uint	i;
	t_uint	j;

	occ = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && sub[j] && str[i + j] == sub[j])
		{
			if (sub[j + 1] == '\0')
			{
				++occ;
				i += j;
				break;
			}
			++j;
		}
		++i;
	}
	return (occ);
}



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
static
t_sintmax	String_Split_String_IndexOf(t_char const* str, t_char const* query)
{ return (strstr(str, query)); }
#else
static
t_sintmax	String_Split_String_IndexOf(t_char const* str, t_char const* query)
{
	t_size	i;

	if (query[0] == '\0')
		return (ERROR);
	i = 0;
	while (str[i])
	{
		t_size j = 0;
		while (query[j] == str[i + j])
		{
			++j;
			if (query[j] == '\0')
				return (i);
			if (str[i + j] == '\0')
				return (ERROR);
		}
		++i;
	}
	return (ERROR);
}
#endif



static
t_char*	String_Split_String_GetNextChunk(t_char const* str, t_uint str_len, t_char const* sub, t_uint sub_len, t_uint *i)
{
	t_char*		result;
	t_sintmax	new_len;

	new_len = String_Split_String_IndexOf(str + *i, sub);
	if (new_len < 0)
	{
		result = String_Duplicate(str + *i);
		*i = str_len;
	}
	else
	{
		result = String_Sub(str, *i, (t_size)new_len);
		*i += new_len + sub_len;
	}
	return (result);
}



t_char**	String_Split_String(t_char const* str, t_char const* sub)
{
	t_char**	result;
	t_uint	reslen;
	t_uint	i;
	t_uint	j;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (sub == NULL), return (NULL);)
	if (sub[0] == '\0')
		return (String_Divide(str, 1));
	reslen = String_Split_String_CountDistinctSubs(str, sub) + 1;
	result = StringArray_New(reslen);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	j = 0;
	if (reslen == 1)
		result[0] = String_Duplicate(str);
	else
	{
		t_uint	str_len = String_Length(str);
		t_uint	sub_len = String_Length(sub);
		while (j < reslen)
		{
			result[j] = String_Split_String_GetNextChunk(str, str_len, sub, sub_len, &i);
			++j;
		}
	}
	return (result);
}
