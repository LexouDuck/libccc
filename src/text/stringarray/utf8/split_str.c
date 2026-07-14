
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_uint	StringUTF8_Split_String_CountDistinctSubs(t_utf8 const* str, t_utf8 const* sub)
{
	t_uint	occ;
	t_size	i;
	t_size	j;

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



//! Like StringUTF8_IndexOf_String(), but does not log an error when the query is not found
static
t_sintmax	StringUTF8_Split_String_IndexOf(t_utf8 const* str, t_utf8 const* query)
{
	t_size	i;
	t_size	j;

	if (query[0] == '\0')
		return (ERROR);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (query[j] == str[i + j])
		{
			++j;
			if (query[j] == '\0')
				return ((t_sintmax)i);
			if (str[i + j] == '\0')
				return (ERROR);
		}
		++i;
	}
	return (ERROR);
}



static
t_utf8*	StringUTF8_Split_String_GetNextChunk(
	t_utf8 const* str, t_size str_len,
	t_size sub_len,
	t_utf8 const* sub,
	t_size *i)
{
	t_utf8*		result;
	t_sintmax	new_len;

	new_len = StringUTF8_Split_String_IndexOf(str + *i, sub);
	if (new_len < 0)
	{
		result = StringUTF8_Duplicate(str + *i);
		*i = str_len;
	}
	else
	{
		result = StringUTF8_Sub(str, *i, (t_size)new_len);
		*i += (t_size)new_len + sub_len;
	}
	return (result);
}



t_utf8**	StringUTF8_Split_String(t_utf8 const* str, t_utf8 const* sep)
{
	t_utf8**	result;
	t_uint	reslen;
	t_size	i;
	t_uint	j;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to split given is NULL")
		return (NULL);
	if CCCERROR((sep == NULL), ERROR_NULLPOINTER, "string separator given is NULL")
		return (NULL);
	if (sep[0] == '\0')
		return (StringUTF8_Divide(str, 1));
	reslen = StringUTF8_Split_String_CountDistinctSubs(str, sep) + 1;
	result = StringArrayUTF8_New(reslen);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if (reslen == 1)
	{
		result[0] = StringUTF8_Duplicate(str);
	}
	else
	{
		t_size	str_len = StringUTF8_Length(str);
		t_size	sep_len = StringUTF8_Length(sep);

		i = 0;
		j = 0;
		while (j < reslen)
		{
			result[j] = StringUTF8_Split_String_GetNextChunk(str, str_len, sep_len, sep, &i);
			if CCCERROR((result[j] == NULL), ERROR_ALLOCFAILURE, NULL)
			{
				StringArrayUTF8_Delete(&result);
				return (NULL);
			}
			++j;
		}
	}
	result[reslen] = NULL;
	return (result);
}
