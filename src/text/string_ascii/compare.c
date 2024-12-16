
#include "libccc/char.h"
#include "libccc/text/string_ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	String_Compare(t_ascii const* str1, t_ascii const* str2)
{
	return (strcmp(str1, str2));
}
#else
t_sint	String_Compare(t_ascii const* str1, t_ascii const* str2)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	String_Compare_N(t_ascii const* str1, t_ascii const* str2, t_size n)
{
	return (strncmp(str1, str2, n));
}
#else
t_sint	String_Compare_N(t_ascii const* str1, t_ascii const* str2, t_size n)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
		if (i == n)
			return (0);
	}
	return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	String_Compare_IgnoreCase(t_ascii const* str1, t_ascii const* str2)
{
	return (strcasecmp(str1, str2));
}
#else
t_sint	String_Compare_IgnoreCase(t_ascii const* str1, t_ascii const* str2)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(Char_IsLower(str1[i]) && Char_ToUpper(str1[i]) == str2[i]) &&
			!(Char_IsUpper(str1[i]) && Char_ToLower(str1[i]) == str2[i]))
			return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_sint	String_Compare_N_IgnoreCase(t_ascii const* str1, t_ascii const* str2, t_size n)
{
	return (strncasecmp(str1, str2, n));
}
#else
t_sint	String_Compare_N_IgnoreCase(t_ascii const* str1, t_ascii const* str2, t_size n)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, NULL)	return ((str1 - str2));
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(Char_IsLower(str1[i]) && Char_ToUpper(str1[i]) == str2[i]) &&
			!(Char_IsUpper(str1[i]) && Char_ToLower(str1[i]) == str2[i]))
			return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
		if (i == n)
			return (0);
	}
	return ((t_sint)((t_u8)str1[i] - (t_u8)str2[i]));
}
#endif
