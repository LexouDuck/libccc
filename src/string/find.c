
#include "libccc/string.h"



t_char*	String_Find_Char(t_char const* str, t_char c)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (TRUE)
	{
		if (str[i] == c)
			return ((t_char*)str + i);
		if (str[i] == '\0')
			break ;
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

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (NULL);
#endif
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

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (NULL);
#endif
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
