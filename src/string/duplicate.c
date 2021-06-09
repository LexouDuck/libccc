
#include "libccc/char.h"
#include "libccc/memory.h"
#include "libccc/string.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS && (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= __POSIX_VERSION_2001__)
inline
t_char*	String_Duplicate(t_char const* str)
{ return (strdup(str)); }
#else
t_char*	String_Duplicate(t_char const* str)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length])
	{
		++length;
	}
	result = String_New(length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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
inline
t_char*	String_Duplicate_N(t_char const* str, t_size n)
{ return (strndup(str, n)); }
#else
t_char*	String_Duplicate_N(t_char const* str, t_size n)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length] && length < n)
	{
		++length;
	}
	result = String_New(length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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



t_char*	String_Duplicate_Char(t_char const* str, t_char const c)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length] && str[length] != c)
	{
		++length;
	}
	result = String_New(length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_char*	String_Duplicate_Charset(t_char const* str, t_char const* charset)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length] && !Char_IsInCharset(str[length], charset))
	{
		++length;
	}
	result = String_New(length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_char*	String_Duplicate_String(t_char const* str, t_char const* target)
{
	t_char*	result;
	t_size	length;
	t_size	n;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	n = String_Length(target);
	length = 0;
	while (str[length] && !String_Equals_N(str + length, target, n))
	{
		++length;
	}
	result = String_New(length);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
