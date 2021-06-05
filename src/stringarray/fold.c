
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



static void	StringArray_GetWordAndCharCount(t_char const** strarr, int* w_nb, int* c_nb)
{
	int str_at;

	str_at = 0;
	while (strarr[str_at])
	{
		*(c_nb) += String_Length(strarr[str_at]);
		++str_at;
	}
	*w_nb = str_at;
}

static void	Fold_Into_String(t_char* dest, t_char const** strarr, t_char const* separator)
{
	int i;
	int words;
	int chars;
	int sep_i;

	i = 0;
	sep_i = 0;
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

t_char*		StringArray_Fold(t_char const** strarr, t_char const* separator)
{
	t_char*	str;
	int		strarr_str_nb;
	int		strarr_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (separator == NULL), return (NULL);)
	strarr_str_nb = 0;
	strarr_char_nb = 0;
	StringArray_GetWordAndCharCount(strarr, &strarr_str_nb, &strarr_char_nb);
	total_sep_char_nb = (strarr_str_nb - 1) * String_Length(separator);
	total_char_nb = total_sep_char_nb + strarr_char_nb;
	str = String_New(total_char_nb + 1);
	HANDLE_ERROR(ALLOCFAILURE, (str == NULL), return (NULL);)
	Fold_Into_String(str, strarr, separator);
	return (str);
}
