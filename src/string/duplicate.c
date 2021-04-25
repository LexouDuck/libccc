
#include "libccc/memory.h"
#include "libccc/string.h"


t_char*	c_strcdup(t_char const* str, t_char const c)
{
	t_char*	result;
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

t_char*	c_strndup(t_char const* str, t_size n)
{
	t_char*	result;
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

t_char*	c_strdup(t_char const* str)
{
	t_char*	result;
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
