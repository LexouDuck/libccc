
#include "libccc/string.h"



t_char*	String_Find_R_Char(t_char const* str, t_char c)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	i = 0;
	while (str[i])
		++i;
	if (c == '\0')
		return ((t_char*)(str + i));
	else if (i == 0)
		return (NULL);
	while (i--)
	{
		if (str[i] == c)
			return ((t_char*)str + i);
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_R_Char(t_char const* str, t_char c)
{
	t_char* result = String_Find_R_Char(str, c);
	return (result ? result - str : -1);
}



t_char*	String_Find_R_Charset(t_char const* str, t_char const* charset)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, charset)
	i = 0;
	while (str[i])
		++i;
	if (charset[0] == '\0')
		return ((t_char*)(str + i));
	else if (i == 0)
		return (NULL);
	while (i--)
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((t_char*)str + i);
		}
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_R_Charset(t_char const* str, t_char const* charset)
{
	t_char* result = String_Find_R_Charset(str, charset);
	return (result ? result - str : -1);
}



t_char*	String_Find_R_String(t_char const* str, t_char const* query)
{
	t_size	length;
	t_size	match;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, query)
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
			return ((t_char*)str + i);
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_R_String(t_char const* str, t_char const* query)
{
	t_char* result = String_Find_R_String(str, query);
	return (result ? result - str : -1);
}
