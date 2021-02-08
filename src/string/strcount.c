
#include "libccc/string.h"



t_size	String_Count_Char(char const *str, char c)
{
	t_size	result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			++result;
		++i;
	}
	return (result);
}



t_size	String_Count_Charset(char const *str, char const *charset)
{
	t_size	result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (0);
#endif
	result = 0;
	i = 0;
	while (str[i])
	{
		if (String_Find_Char(charset, str[i]))
			++result;
		++i;
	}
	return (result);
}



t_size	String_Count_String(char const *str, char const *query)
{
	t_size	result;
	t_size	length;
	t_size	i;
	t_size	j;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (0);
#endif
	result = 0;
	length = 0;
	while (query[length])
		++length;
	if (length == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		for (j = 0; (str[i + j] == query[j]); ++j)
		{
			if (query[j] == '\0' && str[i + j] == '\0')
			{
				++j;
				break;
			}
		}
		if (j == length)
			++result;
		++i;
	}
	return (result);
}
