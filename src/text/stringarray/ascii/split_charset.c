
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_size	StringASCII_Split_WordCount(t_char const* str, t_char const* sep_chars)
{
	t_size	i;
	t_size	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (Char_IsInCharset(str[i], sep_chars))
		{
			++i;
		}
		if (str[i] == '\0')
			return (count);
		count++;
		while (!Char_IsInCharset(str[i], sep_chars) && str[i])
		{
			++i;
		}
	}
	return (count);
}

static
t_size	StringASCII_Split_SingleWordLetterCount(t_char const* str, int ws, t_char const* seps)
{
	t_size	i;

	i = 0;
	while (!Char_IsInCharset(str[ws + i], seps) && str[ws + i])
	{
		++i;
	}
	return (i);
}



t_char**	StringASCII_Split_Charset(t_char const* str, t_char const* sep_chars)
{
	t_char**	result;
	t_size		length;
	t_size		wstart;
	t_size		i;
	t_size		j;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to split given is NULL")
		return (NULL);
	if CCCERROR((sep_chars == NULL), ERROR_NULLPOINTER, "separator charset given is NULL")
		return (NULL);
	result = StringArrayASCII_New(StringASCII_Split_WordCount(str, sep_chars));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < StringASCII_Split_WordCount(str, sep_chars))
	{
		while (Char_IsInCharset(str[j], sep_chars))
		{
			++j;
		}
		wstart = j--;
		length = StringASCII_Split_SingleWordLetterCount(str, wstart, sep_chars);
		result[i] = StringASCII_New(length);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
			return (NULL);
		while (++j < wstart + length)
		{
			result[i][j - wstart] = str[j];
		}
		result[i++][j - wstart] = '\0';
	}
	result[i] = 0;
	return (result);
}
