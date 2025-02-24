
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS && (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= __POSIX_VERSION_2001__)
_INLINE()
t_ascii*	String_Duplicate(t_ascii const* str)
{
	return (strdup(str));
}
#else
t_ascii*	String_Duplicate(t_ascii const* str)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
	{
		++length;
	}
	result = String_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS && (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= __POSIX_VERSION_2008__)
_INLINE()
t_ascii*	String_Duplicate_N(t_ascii const* str, t_size n)
{
	return (strndup(str, n));
}
#else
t_ascii*	String_Duplicate_N(t_ascii const* str, t_size n)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length] && length < n)
	{
		++length;
	}
	result = String_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
#endif



t_ascii*	String_Duplicate_Char(t_ascii const* str, t_ascii const c)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length] && str[length] != c)
	{
		++length;
	}
	result = String_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_ascii*	String_Duplicate_Charset(t_ascii const* str, t_ascii const* charset)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length] && !Char_IsInCharset(str[length], charset))
	{
		++length;
	}
	result = String_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_ascii*	String_Duplicate_String(t_ascii const* str, t_ascii const* target)
{
	t_ascii*	result;
	t_size	length;
	t_size	n;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	n = String_Length(target);
	length = 0;
	while (str[length] && !String_Equals_N(str + length, target, n))
	{
		++length;
	}
	result = String_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
