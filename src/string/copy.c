
#include "libccc/string.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_HANDLE_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_char*	String_Copy(t_char* dest, t_char const* src)
{ return (strcpy(dest, src)); }
#else
t_char*	String_Copy(t_char* dest, t_char const* src)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (dest);)
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
inline
t_char*	String_Copy_N(t_char* dest, t_char const* src, t_size n)
{ return (strncpy(dest, src, n)); }
#else
t_char*	String_Copy_N(t_char* dest, t_char const* src, t_size n)
{
	t_char*	str;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (dest);)
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
inline
t_size	String_Copy_L(t_char* dest, t_char const* src, t_size size)
{ return (strlcpy(dest, src, size)); }
#else
t_size	String_Copy_L(t_char* dest, t_char const* src, t_size size)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (dest == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (0);)
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
