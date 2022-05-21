
#include "libccc/text/stringascii.h"
#include "libccc/char.h"

#include LIBCONFIG_ERROR_INCLUDE



t_size	StringASCII_Count_Char(t_ascii const* str, t_utf32 c)
{
	t_size	result = 0;
	t_size	i = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	if (c >= 0x80) // Searching for a multi-byte utf8 glyph
	{
		// TODO: if t_ascii is t_ascii then return NULL
		t_sint size = 0;
		t_utf32 current = 0;
		while (str[i])
		{
			current = CharUTF32_FromUTF8(str + i);
			if (current == c)
				result += 1;
			size = CharUTF8_Length(str + i);
			if (size <= 0)
				break;
			i += size;
		}
	}
	else // Searching for an ascii character
	{
		c &= 0x7F;
		while (str[i])
		{
			if (str[i] == (t_ascii)c)
				result += 1;
			i += 1;
		}
		if (str[i] == '\0' && c == '\0')
			result += 1;
	}
	return (result);
}



t_size	StringASCII_Count_Charset(t_ascii const* str, t_ascii const* charset)
{
	t_size	result;
	t_size	i;
	t_size	j;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset string given is NULL")
		return (0);
	result = 0;
	i = 0;
	while (str[i])
	{
		for (j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
			{
				++result;
				break;
			}
		}
		++i;
	}
	return (result);
}



t_size	String_Count_String(t_ascii const* str, t_ascii const* query)
{
	t_size	result;
	t_size	length;
	t_size	i;
	t_size	j;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "query string given is NULL")
		return (0);
	result = 0;
	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		for (j = 0; (str[i + j] == query[j]); ++j)
		{
			if (query[j] == '\0' && str[i + j] == '\0')
			{
				++j;
				break;
			}
		}
		if (j == length)
			++result;
		++i;
	}
	return (result);
}
