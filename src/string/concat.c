
#include "libccc/string.h"



t_char*	String_Concat(t_char* dest, t_char const* src)
{
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(dest, src)
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



t_char*	String_Concat_N(t_char* dest, t_char const* src, t_size n)
{
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(dest, src)
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



t_size	String_Concat_L(t_char* dest, t_char const* src, t_size size)
{
	t_size	dst_len;
	t_size	src_len;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(0, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(0, src)
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
