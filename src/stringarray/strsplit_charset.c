
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



static int	c_in_charset(char c, char const* charset)
{
	int i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static int	c_str_word_nb(char const* str, char const* sep_chars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (c_in_charset(str[i], sep_chars))
			++i;
		if (str[i] == '\0')
			return (count);
		count++;
		while (!c_in_charset(str[i], sep_chars) && str[i])
			++i;
	}
	return (count);
}

static int	c_sing_word_lett_count(char const* str, int ws, char const* seps)
{
	int i;

	i = 0;
	while (!c_in_charset(str[ws + i], seps) && str[ws + i])
		++i;
	return (i);
}

char		**c_strsplit_charset(char const* str, char const* sep_chars)
{
	int		i;
	int		j;
	int		wstart;
	int		length;
	char	**strarr;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || sep_chars == NULL)
		return (NULL);
#endif
	if (!(strarr = c_strarrnew(c_str_word_nb(str, sep_chars))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < c_str_word_nb(str, sep_chars))
	{
		while (c_in_charset(str[j], sep_chars))
			++j;
		wstart = j--;
		length = c_sing_word_lett_count(str, wstart, sep_chars);
		if (!(strarr[i] = c_strnew(length)))
			return (NULL);
		while (++j < wstart + length)
			strarr[i][j - wstart] = str[j];
		strarr[i++][j - wstart] = '\0';
	}
	strarr[i] = 0;
	return (strarr);
}
