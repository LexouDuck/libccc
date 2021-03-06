
#include "libccc/string.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



t_char*	String_Find_N_Char(t_char const* str, t_char c, t_size n)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
			return ((t_char*)str + i);
		if (str[i] == '\0')
			break;
		++i;
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		", no char '%c' in the first %zu chars of string \"%s\"", c, n, str)
}

inline
t_sintmax	String_IndexOf_N_Char(t_char const* str, t_char c, t_size n)
{
	t_char* result = String_Find_N_Char(str, c, n);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}



t_char*	String_Find_N_Charset(t_char const* str, t_char const* charset, t_size n)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (NULL);)
	i = 0;
	while (str[i] && i <= n)
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((t_char*)str + i);
		}
		++i;
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		", no char from charset \"%s\" in the first %zu chars of string \"%s\"", charset, n, str)
}

inline
t_sintmax	String_IndexOf_N_Charset(t_char const* str, t_char const* charset, t_size n)
{
	t_char* result = String_Find_N_Charset(str, charset, n);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}



t_char*	String_Find_N_String(t_char const* str, t_char const* query, t_size n)
{
	t_size	length;
	t_size	match;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (query == NULL), return (NULL);)
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
			return ((t_char*)str + i);
		++i;
	}
	HANDLE_ERROR_SF(NOTFOUND, (TRUE), return (NULL);,
		", no string \"%s\" in the first %zu chars of string \"%s\"", query, n, str)
}

inline
t_sintmax	String_IndexOf_N_String(t_char const* str, t_char const* query, t_size n)
{
	t_char* result = String_Find_N_String(str, query, n);
	HANDLE_ERROR(NOTFOUND, (result == NULL), return (ERROR);)
	return (result - str);
}
