
#include "libccc/string.h"



char*	String_Find_Char(char const *str, char c)
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
			return ((char*)str + i);
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_Char(char const *str, char c)
{
	char* result = String_Find_Char(str, c);
	return (result ? result - str : -1);
}



char*	String_Find_Charset(char const *str, char const *charset)
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
				return ((char*)str + i);
		}
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_Charset(char const *str, char const *charset)
{
	char* result = String_Find_Charset(str, charset);
	return (result ? result - str : -1);
}



char*	String_Find_String(char const *str, char const *query)
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
				return ((char*)str + i);
			if (str[i + j] == '\0')
				return (NULL);
		}
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_String(char const *str, char const *query)
{
	char* result = String_Find_String(str, query);
	return (result ? result - str : -1);
}
