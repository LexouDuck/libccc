
#include "libccc/string.h"



static t_bool	charset_contains(t_char const* charset, t_char c)
{
	t_size	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (TRUE);
		++i;
	}
	return (FALSE);
}



t_char*			String_Trim(t_char const* str, t_char const* charset)
{
	t_size	offset;
	t_size	length;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(charset, NULL)
	offset = 0;
	length = 0;
	while (str[length])
		++length;
	while (offset < length && charset_contains(charset, str[offset]))
		++offset;
	if (offset == length)
		return (c_strnew(0));
	length -= 1;
	while (length > offset && charset_contains(charset, str[length]))
		--length;
	length -= offset - 1;
	return (c_strsub(str, offset, length));
}

t_char*			String_Trim_L(t_char const* str, t_char const* charset)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(charset, NULL)
	i = 0;
	while (str[i])
	{
		if (charset_contains(charset, str[i]))
			++i;
		else
			break ;
	}
	return (String_Sub(str, i, String_Length(str + i)));
}



t_char*			String_Trim_R(t_char const* str, t_char const* charset)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(charset, NULL)
	i = String_Length(str);
	while (--i)

	{
		if (!charset_contains(charset, str[i]))
			break ;
	}
	if (i || !charset_contains(charset, str[i]))
		++i;
	return (String_Sub(str, 0, i));
}
