
#include "libccc/string.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_ascii*	String_Find_R_Char(t_ascii const* str, t_utf32 c)
{ return (strchr(str, c)); }
#else
t_ascii*	String_Find_R_Char(t_ascii const* str, t_utf32 c)
{
	t_size	i = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	if (c == '\0')
		return ((t_ascii*)(str + i));
	i = String_Length(str);
	if (i == 0)
		return (NULL);
	if (c >= 0x80) // Searching for a multi-byte utf8 glyph
	{
		// TODO: if t_ascii is t_ascii then return NULL
		t_utf32 current = 0;
		while (i--)
		{
			while (i && (str[i] & 0xC0) == 0x80)
				i -= 1;
			current = CharUTF32_FromUTF8(str + i);
			if (current == c)
				return ((t_ascii *)str + i);
			if (i == 0)
				break;
		}
	}
	else // Searching for an ascii character
	{
		c &= 0x7F;
		while (i--)
		{
			if (str[i] == (t_ascii)c)
				return ((t_ascii*)str + i);
		}
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no char '%c'/0x%X found in string \"%s\"", c, c, str)
}
#endif

inline
t_sintmax	String_IndexOf_R_Char(t_ascii const* str, t_utf32 c)
{
	t_ascii* result = String_Find_R_Char(str, c);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}



t_ascii*	String_Find_R_Charset(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (NULL);)
	i = 0;
	while (str[i])
		++i;
	if (charset[0] == '\0')
		return ((t_ascii*)(str + i));
	else if (i == 0)
		return (NULL);
	while (i--)
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((t_ascii*)str + i);
		}
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no char from charset \"%s\" found in string \"%s\"", charset, str)
}

inline
t_sintmax	String_IndexOf_R_Charset(t_ascii const* str, t_ascii const* charset)
{
	t_ascii* result = String_Find_R_Charset(str, charset);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}



t_ascii*	String_Find_R_String(t_ascii const* str, t_ascii const* query)
{
	t_size	length;
	t_size	match;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (query == NULL), return (NULL);)
	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (NULL);
	i = String_Length(str);
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
			return ((t_ascii*)str + i);
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no string \"%s\" found in string \"%s\"", query, str)
}

inline
t_sintmax	String_IndexOf_R_String(t_ascii const* str, t_ascii const* query)
{
	t_ascii* result = String_Find_R_String(str, query);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}
