
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



static
t_u32	String_Split_String_CountDistinctSubs(t_char const* str, t_char const* sub)
{
	t_u32	occ;
	t_u32	i;
	t_u32	j;

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



static
t_char*	String_Split_String_GetNextChunk(t_char const* str, t_u32 str_len, t_char const* sub, t_u32 sub_len, t_u32 *i)
{
	t_char*		result;
	t_ptrdiff	new_len;

	new_len = String_IndexOf_String(str + *i, sub);
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
	t_u32	reslen;
	t_u32	i;
	t_u32	j;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (sub == NULL), return (NULL);)
	if (sub[0] == '\0')
		return (String_Divide(str, 1));
	reslen = String_Split_String_CountDistinctSubs(str, sub) + 1;
	if (!(result = StringArray_New(reslen)))
		return (NULL);
	i = 0;
	j = 0;
	if (reslen == 1)
		result[0] = String_Duplicate(str);
	else
	{
		t_u32	str_len = String_Length(str);
		t_u32	sub_len = String_Length(sub);
		while (j < reslen)
		{
			result[j] = String_Split_String_GetNextChunk(str, str_len, sub, sub_len, &i);
			++j;
		}
	}
	return (result);
}
