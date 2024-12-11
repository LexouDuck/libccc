
#include "libccc/text/string_ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_ascii*	String_Add(t_ascii* dest, t_ascii const* src)
{
	return (strcat(dest, src));
}
#else
t_ascii*	String_Add(t_ascii* dest, t_ascii const* src)
{
	t_size	length;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (dest);
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
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_ascii*	String_Add_N(t_ascii* dest, t_ascii const* src, t_size n)
{
	return (strncat(dest, src, n));
}
#else
t_ascii*	String_Add_N(t_ascii* dest, t_ascii const* src, t_size n)
{
	t_size	length;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (dest);
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
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS && (defined(__FreeBSD__) && __FreeBSD__ >= 3)
extern inline
t_size	String_Add_L(t_ascii* dest, t_ascii const* src, t_size size)
{
	return (strlcat(dest, src, size));
}
#else
t_size	String_Add_L(t_ascii* dest, t_ascii const* src, t_size size)
{
	t_size	dst_len;
	t_size	src_len;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (0);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (0);
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
#endif
