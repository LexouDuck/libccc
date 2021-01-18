
#include "libccc_string.h"



static t_bool	charset_contains(char const *charset, char c)
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



char			*c_strtrim(char const *str, char const *charset)
{
	t_size	offset;
	t_size	length;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (NULL);
#endif
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

char			*c_strtrim_l(char const *str, char const *charset)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (NULL);
#endif
	i = 0;
	while (str[i])
	{
		if (charset_contains(charset, str[i]))
			++i;
		else
			break ;
	}
	return (c_strsub(str, i, c_strlen(str + i)));
}



char			*c_strtrim_r(char const *str, char const *charset)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (NULL);
#endif
	i = c_strlen(str);
	while (--i)

	{
		if (!charset_contains(charset, str[i]))
			break ;
	}
	if (i || !charset_contains(charset, str[i]))
		++i;
	return (c_strsub(str, 0, i));
}
