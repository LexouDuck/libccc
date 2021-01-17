
#include "libccc_memory.h"
#include "libccc_string.h"
#include "libccc_stringarray.h"



static t_u32	count_distinct_sub_in_str(char const* str, char const* sub)
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

static char		*get_next_chunk(char const* str, char const* sub, t_u32 *i)
{
	char	*result;
	t_u32	sub_len;
	t_u32	str_len;
	t_s32	new_len;

	sub_len = c_strlen(sub);
	str_len = c_strlen(str);
	new_len = c_stristr(str + *i, sub);
	if (new_len > -1)
	{
		result = c_strsub(str, *i, (t_u32)new_len);
		*i += new_len + sub_len * (t_s32)(new_len != -1);
	}
	else
	{
		result = c_strdup(str + *i);
		*i = str_len;
	}
	return (result);
}

char			**c_strsplit_str(char const* str, char const* sub)
{
	char	**result;
	t_u32	reslen;
	t_u32	i;
	t_u32	j;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || sub == NULL)
		return (NULL);
#endif
	if (sub[0] == '\0')
		return (c_strdivide(str, 1));
	reslen = count_distinct_sub_in_str(str, sub) + 1;
	if (!(result = c_strarrnew(reslen)))
		return (NULL);
	i = 0;
	j = 0;
	if (reslen == 1)
		result[0] = c_strdup(str);
	else
		while (j < reslen)
		{
			result[j] = get_next_chunk(str, sub, &i);
			++j;
		}
	return (result);
}
