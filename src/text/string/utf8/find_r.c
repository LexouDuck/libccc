
#include "libccc/text/string/ascii.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_utf8*	StringUTF8_Find_R_Char(t_utf8 const* str, t_utf32 c)
{
	return (strchr(str, c));
}
#else
t_utf8*	StringUTF8_Find_R_Char(t_utf8 const* str, t_utf32 c)
{
	t_size	i = 0;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if (c == '\0')
		return ((t_utf8*)(str + i));
	i = StringUTF8_Length(str);
	if (i == 0)
		return (NULL);
	if (c >= 0x80) // Searching for a multi-byte utf8 glyph
	{
		t_utf32 current = 0;
		while (i--)
		{
			while (i && (str[i] & 0xC0) == 0x80)
				i -= 1;
			current = CharUTF32_FromUTF8(str + i);
			if (current == c)
				return ((t_utf8 *)str + i);
			if (i == 0)
				break;
		}
	}
	else // Searching for an ascii character
	{
		c &= 0x7F;
		while (i--)
		{
			if (str[i] == (t_utf8)c)
				return ((t_utf8*)str + i);
		}
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no char '%c'/0x%X found in string \"%s\"", c, c, str);
	return (NULL);
}
#endif

_INLINE()
t_sintmax	StringUTF8_IndexOf_R_Char(t_utf8 const* str, t_utf32 c)
{
	t_utf8* result = StringUTF8_Find_R_Char(str, c);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



t_utf8*	StringUTF8_Find_R_Charset(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset string given is NULL")
		return (NULL);
	i = 0;
	while (str[i])
		++i;
	if (charset[0] == '\0')
		return ((t_utf8*)(str + i));
	else if (i == 0)
		return (NULL);
	// scan forward through the string symbol-wise, remembering the last match
	// (UTF-8 strings cannot be safely iterated backwards byte-by-byte)
	{
		t_utf8 const*	last = NULL;
		t_sint	size;
		i = 0;
		while (str[i])
		{
			if (CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + i)))
				last = (str + i);
			size = CharUTF8_Length(str + i);
			if (size <= 0)
				break;
			i += (t_size)size;
		}
		if (last != NULL)
			return ((t_utf8*)last);
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no char from charset \"%s\" found in string \"%s\"", charset, str);
	return (NULL);
}

_INLINE()
t_sintmax	StringUTF8_IndexOf_R_Charset(t_utf8 const* str, t_utf8 const* charset)
{
	t_utf8* result = StringUTF8_Find_R_Charset(str, charset);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}



t_utf8*	StringUTF8_Find_R_String(t_utf8 const* str, t_utf8 const* query)
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
	if (length == 0)
		return (NULL);
	i = StringUTF8_Length(str);
	while (i--)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				++match;
			else
				break;
		}
		if (match == length)
			return ((t_utf8*)str + i);
	}
	CCCERROR(TRUE, ERROR_NOTFOUND, 
		"no string \"%s\" found in string \"%s\"", query, str);
	return (NULL);
}

_INLINE()
t_sintmax	StringUTF8_IndexOf_R_String(t_utf8 const* str, t_utf8 const* query)
{
	t_utf8* result = StringUTF8_Find_R_String(str, query);
	if CCCERROR((result == NULL), ERROR_NOTFOUND, NULL)
		return (ERROR);
	return (result - str);
}
