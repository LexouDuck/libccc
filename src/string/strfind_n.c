
#include "libccc/string.h"



char*	String_Find_N_Char(char const *str, char c, t_size n)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (i < n)
	{
		if (str[i] == c)
			return ((char *)str + i);
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_N_Char(char const *str, char c, t_size n)
{
	char* result = String_Find_N_Char(str, c, n);
	return (result ? result - str : -1);
}



char*	String_Find_N_Charset(char const *str, char const *charset, t_size n)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i] && i <= n)
	{
		for (t_size j = 0; charset[j]; ++j)
		{
			if (str[i] == charset[j])
				return ((char *)str + i);
		}
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_N_Charset(char const *str, char const *charset, t_size n)
{
	char* result = String_Find_N_Charset(str, charset, n);
	return (result ? result - str : -1);
}



char*	String_Find_N_String(char const *str, char const *query, t_size n)
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
	i = 0;
	while (str[i] && i + length <= n)
	{
		match = 0;
		while (match < length)
		{
			if (str[i + match] == query[match])
				match++;
			else
				break ;
		}
		if (match == length)
			return ((char *)str + i);
		++i;
	}
	return (NULL);
}
inline
t_ptrdiff	String_IndexOf_N_String(char const *str, char const *query, t_size n)
{
	char* result = String_Find_N_String(str, query, n);
	return (result ? result - str : -1);
}
