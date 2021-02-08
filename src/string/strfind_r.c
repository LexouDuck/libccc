
#include "libccc/string.h"



char*	String_Find_R_Char(char const *str, char c)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i])
		++i;
	if (c == '\0')
		return ((char *)(str + i));
	else if (i == 0)
		return (NULL);
	while (i--)
	{
		if (str[i] == c)
			return ((char *)str + i);
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_R_Char(char const *str, char c)
{
	char* result = String_Find_R_Char(str, c);
	return (result ? str - result : -1);
}



char*	String_Find_R_Charset(char const *str, char const* charset)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i])
		++i;
	if (charset[0] == '\0')
		return ((char *)(str + i));
	else if (i == 0)
		return (NULL);
	while (i--)
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((char *)str + i);
		}
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_R_Charset(char const *str, char const *charset)
{
	char* result = String_Find_R_Charset(str, charset);
	return (result ? str - result : -1);
}



char*	String_Find_R_String(char const *str, char const *query)
{
	t_size	length;
	t_size	match;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (NULL);
#endif
	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (NULL);
	i = c_strlen(str);
	while (i--)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				++match;
			else
				break ;
		}
		if (match == length)
			return ((char *)str + i);
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_R_String(char const *str, char const *query)
{
	char* result = String_Find_R_String(str, query);
	return (result ? str - result : -1);
}
