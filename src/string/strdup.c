
#include "libccc/memory.h"
#include "libccc/string.h"


char	*c_strcdup(char const *str, char const c)
{
	char	*result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (!(result = c_strnew(i)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

char	*c_strndup(char const *str, t_size n)
{
	char	*result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i] && i < n)
		++i;
	if (!(result = c_strnew(i)))
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

char	*c_strdup(char const *str)
{
	char	*result;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i])
		++i;
	if (!(result = c_strnew(i)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
