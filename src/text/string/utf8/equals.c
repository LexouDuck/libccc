
#include "libccc/char.h"
#include "libccc/text/string/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	StringUTF8_Equals(t_utf8 const* str1, t_utf8 const* str2)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size i;

	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2)
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	StringUTF8_Equals_N(t_utf8 const* str1, t_utf8 const* str2, t_size n)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size i;

	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2)
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}



t_bool	StringUTF8_Equals_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size i;

	if (str1 == str2)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2 &&
			!(CharUTF32_ToLower(c1) == CharUTF32_ToLower(c2)) &&
			!(CharUTF32_ToUpper(c1) == CharUTF32_ToUpper(c2)))
			return (FALSE);
		++i;
	}
	return (str1[i] == str2[i]);
}



t_bool	StringUTF8_Equals_N_IgnoreCase(t_utf8 const* str1, t_utf8 const* str2, t_size n)
{
	t_utf32 c1;
	t_utf32 c2;
	t_size i;

	if (str1 == str2 || n == 0)
		return (TRUE);
	if (str1 == NULL)	return (FALSE);
	if (str2 == NULL)	return (FALSE);
	i = 0;
	while (str1[i] && str2[i])
	{
		c1 = CharUTF32_FromUTF8(str1 + i);
		c2 = CharUTF32_FromUTF8(str2 + i);
		if (c1 != c2 &&
			!(CharUTF32_ToLower(c1) == CharUTF32_ToLower(c2)) &&
			!(CharUTF32_ToUpper(c1) == CharUTF32_ToUpper(c2)))
			return (FALSE);
		++i;
		if (i == n)
			return (TRUE);
	}
	return (str1[i] == str2[i]);
}
