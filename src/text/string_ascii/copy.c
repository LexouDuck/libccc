
#include "libccc/text/string_ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_ascii*	String_Copy(t_ascii* dest, t_ascii const* src)
{
	return (strcpy(dest, src));
}
#else
t_ascii*	String_Copy(t_ascii* dest, t_ascii const* src)
{
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (dest);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_ascii*	String_Copy_N(t_ascii* dest, t_ascii const* src, t_size n)
{
	return (strncpy(dest, src, n));
}
#else
t_ascii*	String_Copy_N(t_ascii* dest, t_ascii const* src, t_size n)
{
	t_ascii*	str;
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (dest);
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
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS && (defined(__FreeBSD__) && __FreeBSD__ >= 3)
extern inline
t_size	String_Copy_L(t_ascii* dest, t_ascii const* src, t_size size)
{
	return (strlcpy(dest, src, size));
}
#else
t_size	String_Copy_L(t_ascii* dest, t_ascii const* src, t_size size)
{
	t_size	i;

	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (0);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "source string given is NULL")
		return (0);
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
#endif
