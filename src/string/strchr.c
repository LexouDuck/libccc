
#include "libccc_string.h"



char	*c_strchr(char const *str, char c)
{
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	i = 0;
	while (TRUE)
	{
		if (str[i] == c)
			return ((char *)str + i);
		if (str[i] == '\0')
			break ;
		++i;
	}
	return (NULL);
}



char	*c_strrchr(char const *str, char c)
{
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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



char	*c_strnchr(char const *str, char c, t_size n)
{
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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



t_s32	c_strichr(char const *str, char c)
{
	t_s32	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (-1);
#endif
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
