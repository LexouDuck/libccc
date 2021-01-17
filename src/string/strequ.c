
#include "libccc_char.h"
#include "libccc_string.h"



t_bool	c_strequ(char const *str1, char const *str2)
{
	t_size i;

//#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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



t_bool	c_strnequ(char const *str1, char const *str2, t_size n)
{
	t_size i;

//#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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



t_bool	c_striequ(char const *str1, char const *str2)
{
	t_size i;

//#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
//#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			str1[i] != Char_ToUpper(str2[i]) &&
			str1[i] != Char_ToLower(str2[i]))
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	c_strniequ(char const *str1, char const *str2, t_size n)
{
	t_size i;

//#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL || str2 == NULL)
		return (FALSE);
//#endif
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] &&
			str1[i] != Char_ToUpper(str2[i]) &&
			str1[i] != Char_ToLower(str2[i]))
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}
