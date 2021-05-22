
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_char*	String_Find_Char(t_char const* str, t_char c)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	i = 0;
	while (TRUE)
	{
		if (str[i] == c)
			return ((t_char*)str + i);
		if (str[i] == '\0')
			break;
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_Char(t_char const* str, t_char c)
{
	t_char* result = String_Find_Char(str, c);
	return (result ? result - str : -1);
}



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
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_Charset(t_char const* str, t_char const* charset)
{
	t_char* result = String_Find_Charset(str, charset);
	return (result ? result - str : -1);
}



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
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_String(t_char const* str, t_char const* query)
{
	t_char* result = String_Find_String(str, query);
	return (result ? result - str : -1);
}
