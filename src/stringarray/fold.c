
#include "libccc/string.h"
#include "libccc/stringarray.h"


static void	StringArray_GetWordAndCharCount(char const** strarr, int* w_nb, int* c_nb)
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

static void	Fold_Into_String(char* dest, char const** strarr, char const* sep)
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
		while (sep[sep_i] && strarr[words + 1])
		{
			dest[i] = sep[sep_i];
			++i;
			++sep_i;
		}
	}
	dest[i] = '\0';
}

char*		StringArray_Fold(char const** strarr, char const* sep)
{
	char*	str;
	int		strarr_str_nb;
	int		strarr_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || sep == NULL)
		return (NULL);
#endif
	strarr_str_nb = 0;
	strarr_char_nb = 0;
	StringArray_GetWordAndCharCount(strarr, &strarr_str_nb, &strarr_char_nb);
	total_sep_char_nb = (strarr_str_nb - 1) * String_Length(sep);
	total_char_nb = total_sep_char_nb + strarr_char_nb;
	if (!(str = String_New(total_char_nb + 1)))
		return (NULL);
	Fold_Into_String(str, strarr, sep);
	return (str);
}
