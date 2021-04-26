
#include "libccc/char.h"
#include "libccc/string.h"



t_sint	String_Compare(t_char const* str1, t_char const* str2)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(str1, (str1 - str2))
	LIBCONFIG_HANDLE_NULLPOINTER(str2, (str1 - str2))
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}



t_sint	String_Compare_N(t_char const* str1, t_char const* str2, t_size n)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(str1, (str1 - str2))
	LIBCONFIG_HANDLE_NULLPOINTER(str2, (str1 - str2))
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



t_sint	String_Compare_IgnoreCase(t_char const* str1, t_char const* str2)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(str1, (str1 - str2))
	LIBCONFIG_HANDLE_NULLPOINTER(str2, (str1 - str2))
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



t_sint	String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n)
{
	t_size	i;

	if (str1 == str2)
		return (0);
	LIBCONFIG_HANDLE_NULLPOINTER(str1, (str1 - str2))
	LIBCONFIG_HANDLE_NULLPOINTER(str2, (str1 - str2))
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
