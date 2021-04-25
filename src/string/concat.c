
#include "libccc/string.h"



t_char*	c_strcat(t_char* dest, t_char const* src)
{
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	length = 0;
	while (dest[length])
		++length;
	i = 0;
	while (src[i])
	{
		dest[length + i] = src[i];
		++i;
	}
	dest[length + i] = '\0';
	return (dest);
}



t_char*	c_strncat(t_char* dest, t_char const* src, t_size n)
{
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (NULL);
	if (src == NULL)
		return (dest);
#endif
	length = 0;
	while (dest[length])
		++length;
	i = 0;
	while (i < n && src[i])
	{
		dest[length + i] = src[i];
		++i;
	}
	while (src[i])
	{
		dest[length + i] = '\0';
		++i;
	}
	dest[length + i] = '\0';
	return (dest);
}



t_size	c_strlcat(t_char* dest, t_char const* src, t_size size)
{
	t_size	dst_len;
	t_size	src_len;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL || src == NULL)
		return (0);
#endif
	src_len = 0;
	while (src[src_len])
		++src_len;
	dst_len = 0;
	while (dest[dst_len])
		++dst_len;
	if (dst_len >= size)
		dst_len = size;
	if (dst_len != size)
	{
		i = 0;
		while (dst_len + i + 1 < size && src[i])
		{
			dest[dst_len + i] = src[i];
			++i;
		}
		dest[dst_len + i] = '\0';
	}
	return (dst_len + src_len);
}
