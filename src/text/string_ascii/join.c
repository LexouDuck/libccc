
#include "libccc/text/string_ascii.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



static
void	String_Join_GetWordAndCharCount(t_ascii const** strarr, t_sint* w_nb, t_sint* c_nb)
{
	t_sint str_at;

	str_at = 0;
	while (strarr[str_at])
	{
		*(c_nb) += String_Length(strarr[str_at]);
		++str_at;
	}
	*w_nb = str_at;
}

static
void	String_Join_FoldIntoString(t_ascii* dest, t_ascii const** strarr, t_ascii const* separator)
{
	t_sint i;
	t_sint words;
	t_sint chars;
	t_sint sep_i;

	i = 0;
	words = -1;
	while (strarr[++words])
	{
		chars = 0;
		while (strarr[words][chars])
		{
			dest[i] = strarr[words][chars];
			++i;
			++chars;
		}
		sep_i = 0;
		while (separator[sep_i] && strarr[words + 1])
		{
			dest[i] = separator[sep_i];
			++i;
			++sep_i;
		}
	}
	dest[i] = '\0';
}



t_ascii*		String_Join(t_ascii const** strarr, t_ascii const* separator)
{
	t_ascii*	str;
	t_sint	strarr_strs;
	t_sint	strarr_chars;
	t_sint	total_sep_chars;
	t_sint	total_chars;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	if CCCERROR((separator == NULL), ERROR_NULLPOINTER, "separator given is NULL")
		return (NULL);
	if (strarr[0] == NULL)
		return (String_Duplicate(""));
	strarr_strs = 0;
	strarr_chars = 0;
	String_Join_GetWordAndCharCount(strarr, &strarr_strs, &strarr_chars);
	total_sep_chars = (strarr_strs - 1) * String_Length(separator);
	total_chars = total_sep_chars + strarr_chars;
	str = String_New(total_chars + 1);
	if CCCERROR((str == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	String_Join_FoldIntoString(str, strarr, separator);
	return (str);
}
