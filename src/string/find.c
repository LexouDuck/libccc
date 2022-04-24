
#include "libccc/string.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_char*	String_Find_Char(t_char const* str, t_utf32 c)
{ return (strchr(str, c)); }
#else
t_char*	String_Find_Char(t_char const* str, t_utf32 c)
{
	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)

	if (c & 0xFFFFFF80) // Searching for a multi-byte utf8 glyph
	{
		// TODO: if t_char is t_ascii then return NULL 

		t_size i = 0;
		while (str[i] != '\0')
		{
			t_utf32 current_char = UTF32_FromUTF8(str + i);

			if (current_char == c)
				return ((t_char *)str + i);

			i += UTF8_Length(str, SIZE_MAX);
		}
	}
	else // Searching for an ascii character
	{
		t_ascii c_as_ascii = (c & 0x8F);

		for (t_size i = 0; str[i] != '\0'; ++i)
		{
			if (str[i] == c_as_ascii)
				return ((t_char*)str + i);
		}
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no char '%c' found in string \"%s\"", c, str)
}
#endif

inline
t_sintmax	String_IndexOf_Char(t_char const* str, t_char c)
{
	t_char* result = String_Find_Char(str, c);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_char*	String_Find_Charset(t_char const* str, t_char const* charset)
{ return (strpbrk(str, charset)); }
#else
t_char*	String_Find_Charset(t_char const* str, t_char const* charset)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (NULL);)
	if (charset[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i])
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((t_char*)str + i);
		}
		++i;
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no char from charset \"%s\" found in string \"%s\"", charset, str)
}
#endif

inline
t_sintmax	String_IndexOf_Charset(t_char const* str, t_char const* charset)
{
	t_char* result = String_Find_Charset(str, charset);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_char*	String_Find_String(t_char const* str, t_char const* query)
{ return (strstr(str, query)); }
#else
t_char*	String_Find_String(t_char const* str, t_char const* query)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (query == NULL), return (NULL);)
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
				return ((t_char*)str + i);
			if (str[i + j] == '\0')
				return (NULL);
		}
		++i;
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		"no string \"%s\" found in string \"%s\"", query, str)
}
#endif

inline
t_sintmax	String_IndexOf_String(t_char const* str, t_char const* query)
{
	t_char* result = String_Find_String(str, query);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}
