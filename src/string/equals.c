
#include "libccc/char.h"
#include "libccc/string.h"



t_bool	String_Equals(t_char const* str1, t_char const* str2)
{
	t_size i;

//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
//#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	String_Equals_N(t_char const* str1, t_char const* str2, t_size n)
{
	t_size i;

//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
//#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}



t_bool	String_Equals_IgnoreCase(t_char const* str1, t_char const* str2)
{
	t_size i;

//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
//#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(Char_IsLower(str1[i]) && Char_ToUpper(str1[i]) == str2[i]) &&
			!(Char_IsUpper(str1[i]) && Char_ToLower(str1[i]) == str2[i]))
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	String_Equals_N_IgnoreCase(t_char const* str1, t_char const* str2, t_size n)
{
	t_size i;

//#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
//#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(Char_IsLower(str1[i]) && Char_ToUpper(str1[i]) == str2[i]) &&
			!(Char_IsUpper(str1[i]) && Char_ToLower(str1[i]) == str2[i]))
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}
