
#include "libccc/char.h"
#include "libccc/string.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_HANDLE_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_sint	String_Compare(t_char const* str1, t_char const* str2)
{ return (strcmp(str1, str2)); }
#else
t_sint	String_Compare(t_char const* str1, t_char const* str2)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (str1 == NULL), return ((str1 - str2));)
	HANDLE_ERROR(NULLPOINTER, (str2 == NULL), return ((str1 - str2));)
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_sint	String_Compare_N(t_char const* str1, t_char const* str2, t_size n)
{ return (strncmp(str1, str2, n)); }
#else
t_sint	String_Compare_N(t_char const* str1, t_char const* str2, t_size n)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (str1 == NULL), return ((str1 - str2));)
	HANDLE_ERROR(NULLPOINTER, (str2 == NULL), return ((str1 - str2));)
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
		if (i == n)
			return (0);
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_sint	String_Compare_IgnoreCase(t_char const* str1, t_char const* str2)
{ return (strcasecmp(str1, str2)); }
#else
t_sint	String_Compare_IgnoreCase(t_char const* str1, t_char const* str2)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (str1 == NULL), return ((str1 - str2));)
	HANDLE_ERROR(NULLPOINTER, (str2 == NULL), return ((str1 - str2));)
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(Char_IsLower(str1[i]) && Char_ToUpper(str1[i]) == str2[i]) &&
			!(Char_IsUpper(str1[i]) && Char_ToLower(str1[i]) == str2[i]))
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_sint	String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n)
{ return (strncasecmp(str1, str2, n)); }
#else
t_sint	String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	HANDLE_ERROR(NULLPOINTER, (str1 == NULL), return ((str1 - str2));)
	HANDLE_ERROR(NULLPOINTER, (str2 == NULL), return ((str1 - str2));)
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(Char_IsLower(str1[i]) && Char_ToUpper(str1[i]) == str2[i]) &&
			!(Char_IsUpper(str1[i]) && Char_ToLower(str1[i]) == str2[i]))
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
		if (i == n)
			return (0);
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif
