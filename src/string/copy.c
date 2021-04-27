
#include "libccc/string.h"



t_char*	String_Copy(t_char* dest, t_char const* src)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(dest, src)
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}



t_char*	String_Copy_N(t_char* dest, t_char const* src, t_size n)
{
	t_char*	str;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(dest, src)
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



t_size	String_Copy_L(t_char* dest, t_char const* src, t_size size)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(0, dest)
	LIBCONFIG_HANDLE_NULLPOINTER(0, src)
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
