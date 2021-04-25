
#include "libccc/string.h"



t_char*	c_strcpy(t_char* dest, t_char const* src)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}



t_char*	c_strncpy(t_char* dest, t_char const* src, t_size n)
{
	t_char*	str;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	str = dest;
	i = 0;
	while (n > 0 && src[i])
	{
		str[i] = src[i];
		++i;
		--n;
	}
	while (n > 0)
	{
		str[i] = '\0';
		++i;
		--n;
	}
	return (dest);
}



t_size	c_strlcpy(t_char* dest, t_char const* src, t_size size)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (0);
#endif
	i = 0;
	while (i < size - 1 && src[i])
	{
		if (size)
			dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	i = 0;
	while (src[i])
		++i;
	return (i);
}
