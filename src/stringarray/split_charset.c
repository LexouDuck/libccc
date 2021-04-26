
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



static int	String_Split_WordCount(t_char const* str, t_char const* sep_chars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (Char_IsInCharset(str[i], sep_chars))
			++i;
		if (str[i] == '\0')
			return (count);
		count++;
		while (!Char_IsInCharset(str[i], sep_chars) && str[i])
			++i;
	}
	return (count);
}

static int	String_Split_SingleWordLetterCount(t_char const* str, int ws, t_char const* seps)
{
	int i;

	i = 0;
	while (!Char_IsInCharset(str[ws + i], seps) && str[ws + i])
		++i;
	return (i);
}

t_char**	String_Split_Charset(t_char const* str, t_char const* sep_chars)
{
	int		i;
	int		j;
	int		wstart;
	int		length;
	t_char**	strarr;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(sep_chars, NULL)
	if (!(strarr = StringArray_New(String_Split_WordCount(str, sep_chars))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < String_Split_WordCount(str, sep_chars))
	{
		while (Char_IsInCharset(str[j], sep_chars))
			++j;
		wstart = j--;
		length = String_Split_SingleWordLetterCount(str, wstart, sep_chars);
		if (!(strarr[i] = String_New(length)))
			return (NULL);
		while (++j < wstart + length)
			strarr[i][j - wstart] = str[j];
		strarr[i++][j - wstart] = '\0';
	}
	strarr[i] = 0;
	return (strarr);
}
