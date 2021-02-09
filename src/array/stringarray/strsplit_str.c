
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/stringarray.h"



static t_u32	String_Split_String_CountDistinctSubs(char const* str, char const* sub)
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
				break ;
			}
			++j;
		}
		++i;
	}
	return (occ);
}

static char*	String_Split_String_GetNextChunk(char const* str, char const* sub, t_u32 *i)
{
	char*		result;
	t_size		sub_len;
	t_size		str_len;
	t_ptrdiff	new_len;

	sub_len = String_Length(sub);
	str_len = String_Length(str);
	new_len = String_IndexOf_String(str + *i, sub);
	if (new_len < 0)
	{
		result = String_Duplicate(str + *i);
		*i = str_len;
	}
	else
	{
		result = String_Sub(str, *i, (t_size)new_len);
		*i += new_len + sub_len * (new_len != -1);
	}
	return (result);
}

char**		String_Split_String(char const* str, char const* sub)
{
	char**	result;
	t_u32	reslen;
	t_u32	i;
	t_u32	j;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || sub == NULL)
		return (NULL);
#endif
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
		while (j < reslen)
		{
			result[j] = String_Split_String_GetNextChunk(str, sub, &i);
			++j;
		}
	return (result);
}
