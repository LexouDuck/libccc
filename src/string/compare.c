
#include "libccc/char.h"
#include "libccc/string.h"



int	String_Compare(t_char const* str1, t_char const* str2)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return ((str1 == NULL ? 0 : str1[0]) -
				(str2 == NULL ? 0 : str2[0]));
#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
		++i;
	}
	return ((int)((t_u8)str1[i] - (t_u8)str2[i]));
}



int	String_Compare_N(t_char const* str1, t_char const* str2, t_size n)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return ((str1 == NULL ? 0 : str1[0]) -
				(str2 == NULL ? 0 : str2[0]));
#endif
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



int	String_Compare_IgnoreCase(t_char const* str1, t_char const* str2)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return ((str1 == NULL ? 0 : str1[0]) -
				(str2 == NULL ? 0 : str2[0]));
#endif
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



int	String_Compare_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (0);
	if (str1 == NULL || str2 == NULL)
		return ((str1 == NULL ? 0 : str1[0]) -
				(str2 == NULL ? 0 : str2[0]));
#endif
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
