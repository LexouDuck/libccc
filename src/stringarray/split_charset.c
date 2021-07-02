
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_size	String_Split_WordCount(t_char const* str, t_char const* sep_chars)
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
t_size	String_Split_SingleWordLetterCount(t_char const* str, int ws, t_char const* seps)
{
	t_size	i;

	i = 0;
	while (!Char_IsInCharset(str[ws + i], seps) && str[ws + i])
	{
		++i;
	}
	return (i);
}



t_char**	String_Split_Charset(t_char const* str, t_char const* sep_chars)
{
	t_char**	result;
	t_size		length;
	t_size		wstart;
	t_size		i;
	t_size		j;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (sep_chars == NULL), return (NULL);)
	result = StringArray_New(String_Split_WordCount(str, sep_chars));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	j = 0;
	while (i < String_Split_WordCount(str, sep_chars))
	{
		while (Char_IsInCharset(str[j], sep_chars))
		{
			++j;
		}
		wstart = j--;
		length = String_Split_SingleWordLetterCount(str, wstart, sep_chars);
		result[i] = String_New(length);
		HANDLE_ERROR(ALLOCFAILURE, (result[i] == NULL), return (NULL);)
		while (++j < wstart + length)
		{
			result[i][j - wstart] = str[j];
		}
		result[i++][j - wstart] = '\0';
	}
	result[i] = 0;
	return (result);
}
