
#include "libccc/text/string/ascii.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Find_N_Char(t_utf8 const* str, t_utf32 c, t_size n)
{
	t_size	i = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if (c >= 0x80) // Searching for a multi-byte utf8 glyph
	{
		t_sint size = 0;
		t_utf32 current = 0;
		while (i < n && str[i])
		{
			current = CharUTF32_FromUTF8(str + i);
			if (current == c)
				return ((t_utf8 *)str + i);
			size = CharUTF8_Length(str + i);
			if (size <= 0)
				break;
			i += size;
		}
	}
	else // Searching for an ascii character
	{
		c &= 0x7F;
		while (i < n && str[i])
		{
			if (str[i] == (t_utf8)c)
				return ((t_utf8*)str + i);
			i += 1;
		}
		if (str[i] == '\0' && c == '\0')
			return ((t_utf8*)str + i);
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no char '%c'/0x%X found in the first " SF_SIZE " chars of string \"%s\"", c, c, n, str);
	return (NULL);
}

_INLINE()
t_sintmax	StringUTF8_IndexOf_N_Char(t_utf8 const* str, t_utf32 c, t_size n)
{
	t_utf8* result = StringUTF8_Find_N_Char(str, c, n);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



t_utf8*	StringUTF8_Find_N_Charset(t_utf8 const* str, t_utf8 const* charset, t_size n)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset string given is NULL")
		return (NULL);
	i = 0;
	while (str[i] && i <= n)
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((t_utf8*)str + i);
		}
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no char from charset \"%s\" found in the first " SF_SIZE " chars of string \"%s\"", charset, n, str);
	return (NULL);
}

_INLINE()
t_sintmax	StringUTF8_IndexOf_N_Charset(t_utf8 const* str, t_utf8 const* charset, t_size n)
{
	t_utf8* result = StringUTF8_Find_N_Charset(str, charset, n);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



t_utf8*	StringUTF8_Find_N_String(t_utf8 const* str, t_utf8 const* query, t_size n)
{
	t_size	length;
	t_size	match;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "query string given is NULL")
		return (NULL);
	length = 0;
	while (query[length])
		++length;
	i = 0;
	while (str[i] && i + length <= n)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				match++;
			else
				break;
		}
		if (match == length)
			return ((t_utf8*)str + i);
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no string \"%s\" found in the first " SF_SIZE " chars of string \"%s\"", query, n, str);
	return (NULL);
}

_INLINE()
t_sintmax	StringUTF8_IndexOf_N_String(t_utf8 const* str, t_utf8 const* query, t_size n)
{
	t_utf8* result = StringUTF8_Find_N_String(str, query, n);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}
