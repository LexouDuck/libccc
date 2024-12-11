
#include "libccc/text/string_ascii.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Find_N_Char(t_ascii const* str, t_utf32 c, t_size n)
{
	t_size	i = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if (c >= 0x80) // Searching for a multi-byte utf8 glyph
	{
		// TODO: if t_ascii is t_ascii then return NULL
		t_sint size = 0;
		t_utf32 current = 0;
		while (i < n && str[i])
		{
			current = CharUTF32_FromUTF8(str + i);
			if (current == c)
				return ((t_ascii *)str + i);
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
			if (str[i] == (t_ascii)c)
				return ((t_ascii*)str + i);
			i += 1;
		}
		if (str[i] == '\0' && c == '\0')
			return ((t_ascii*)str + i);
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no char '%c'/0x%X found in the first " SF_SIZE " chars of string \"%s\"", c, c, n, str);
	return (NULL);
}

extern inline
t_sintmax	String_IndexOf_N_Char(t_ascii const* str, t_utf32 c, t_size n)
{
	t_ascii* result = String_Find_N_Char(str, c, n);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



t_ascii*	String_Find_N_Charset(t_ascii const* str, t_ascii const* charset, t_size n)
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
				return ((t_ascii*)str + i);
		}
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no char from charset \"%s\" found in the first " SF_SIZE " chars of string \"%s\"", charset, n, str);
	return (NULL);
}

extern inline
t_sintmax	String_IndexOf_N_Charset(t_ascii const* str, t_ascii const* charset, t_size n)
{
	t_ascii* result = String_Find_N_Charset(str, charset, n);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



t_ascii*	String_Find_N_String(t_ascii const* str, t_ascii const* query, t_size n)
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
			return ((t_ascii*)str + i);
		++i;
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no string \"%s\" found in the first " SF_SIZE " chars of string \"%s\"", query, n, str);
	return (NULL);
}

extern inline
t_sintmax	String_IndexOf_N_String(t_ascii const* str, t_ascii const* query, t_size n)
{
	t_ascii* result = String_Find_N_String(str, query, n);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}
