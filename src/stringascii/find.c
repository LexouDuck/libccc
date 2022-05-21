#include "libccc/text/stringascii.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_ascii*	String_Find_Char(t_ascii const* str, t_utf32 c)
{
	return (strchr(str, c));
}
#else
t_ascii*	String_Find_Char(t_ascii const* str, t_utf32 c)
{
	t_size	i = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if (c >= 0x80) // Searching for a multi-byte utf8 glyph
	{
		// TODO: if t_ascii is t_ascii then
		return NULL
		t_sint size = 0;
		t_utf32 current = 0;
		while (str[i])
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
		while (str[i])
		{
			if (str[i] == (t_ascii)c)
				return ((t_ascii*)str + i);
			i += 1;
		}
		if (str[i] == '\0' && c == '\0')
			return ((t_ascii*)str + i);
	}
	if CCCERROR((TRUE), ERROR_NOTFOUND, 
		"no char '%c'/0x%X found in string \"%s\"", c, c, str)
		return (NULL);
}
#endif

inline
t_sintmax	String_IndexOf_Char(t_ascii const* str, t_utf32 c)
{
	t_ascii* result = String_Find_Char(str, c);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_ascii*	String_Find_Charset(t_ascii const* str, t_ascii const* charset)
{
	return (strpbrk(str, charset));
}
#else
t_ascii*	String_Find_Charset(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset string given is NULL")
		return (NULL);
	if (charset[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i])
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((t_ascii*)str + i);
		}
		++i;
	}
	if CCCERROR((TRUE), ERROR_NOTFOUND, 
		"no char from charset \"%s\" found in string \"%s\"", charset, str)
		return (NULL);
}
#endif

inline
t_sintmax	String_IndexOf_Charset(t_ascii const* str, t_ascii const* charset)
{
	t_ascii* result = String_Find_Charset(str, charset);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_ascii*	String_Find_String(t_ascii const* str, t_ascii const* query)
{
	return (strstr(str, query));
}
#else
t_ascii*	String_Find_String(t_ascii const* str, t_ascii const* query)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "query string given is NULL")
		return (NULL);
	if (query[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i])
	{
		t_size j = 0;
		while (query[j] == str[i + j])
		{
			++j;
			if (query[j] == '\0')
				return ((t_ascii*)str + i);
			if (str[i + j] == '\0')
				return (NULL);
		}
		++i;
	}
	if CCCERROR((TRUE), ERROR_NOTFOUND, 
		"no string \"%s\" found in string \"%s\"", query, str)
		return (NULL);
}
#endif

inline
t_sintmax	String_IndexOf_String(t_ascii const* str, t_ascii const* query)
{
	t_ascii* result = String_Find_String(str, query);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}
