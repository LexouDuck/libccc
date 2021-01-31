
#include "libccc/string.h"



char	*c_strstr(char const *str, char const *query)
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
	i = 0;
	while (str[i])
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
		++i;
	}
	return (NULL);
}



char	*c_strrstr(char const *str, char const *query)
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



char	*c_strnstr(char const *str, char const *query, t_size n)
{
	t_size	length;
	t_size	match;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (NULL);
#endif
	length = c_strlen(query);
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



t_s32		c_stristr(char const *str, char const *query)
{
	t_size	i;
	t_size	j;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (-1);
#endif
	if (query[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (query[j] == str[i + j])
		{
			if (query[j + 1] == '\0')
				return (i);
			if (str[i + j + 1] == '\0')
				return (-1);
			++j;
		}
		++i;
	}
	return (-1);
}
