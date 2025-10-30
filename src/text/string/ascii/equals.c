
#include "libccc/char.h"
#include "libccc/text/string/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	StringASCII_Equals(t_ascii const* str1, t_ascii const* str2)
{
	t_size i;

	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	StringASCII_Equals_N(t_ascii const* str1, t_ascii const* str2, t_size n)
{
	t_size i;

	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
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



t_bool	StringASCII_Equals_IgnoreCase(t_ascii const* str1, t_ascii const* str2)
{
	t_size i;

	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(CharASCII_IsLower(str1[i]) && CharASCII_ToUpper(str1[i]) == str2[i]) &&
			!(CharASCII_IsUpper(str1[i]) && CharASCII_ToLower(str1[i]) == str2[i]))
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	StringASCII_Equals_N_IgnoreCase(t_ascii const* str1, t_ascii const* str2, t_size n)
{
	t_size i;

	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			!(CharASCII_IsLower(str1[i]) && CharASCII_ToUpper(str1[i]) == str2[i]) &&
			!(CharASCII_IsUpper(str1[i]) && CharASCII_ToLower(str1[i]) == str2[i]))
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}
