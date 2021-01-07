
#include "libft_string.h"



t_size	ft_strcount_char(char const *str, char c)
{
	t_size	result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
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



t_size	ft_strcount_charset(char const *str, char const *cset)
{
	t_size	result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || cset == NULL)
		return (0);
#endif
	result = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(cset, str[i]))
			++result;
		++i;
	}
	return (result);
}



t_size	ft_strcount_str(char const *str, char const *query)
{
	t_size	result;
	t_size	length;
	t_size	i;
	t_size	j;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
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
		j = 0;
		while (query[j] && str[i + j] && str[i + j] == query[j])
			++j;
		if (j == length)
			++result;
		++i;
	}
	return (result);
}
