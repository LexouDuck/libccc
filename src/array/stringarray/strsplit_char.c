
#include "libccc/string.h"
#include "libccc/array/stringarray.h"



static int	c_strcsplit_get_count(char const* str, char c)
{
	int		result;
	t_bool	separator;
	t_size	i;

	separator = 1;
	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			separator = TRUE;
			++i;
		}
		if (str[i])
		{
			if (separator)
				++result;
		}
		else
			break ;
		separator = FALSE;
		++i;
	}
	return (result);
}

char		**c_strsplit_char(char const* str, char c)
{
	char	**result;
	t_size	offset;
	t_size	length;
	int		count;
	int		i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	count = c_strcsplit_get_count(str, c);
	if (!(result = c_strarrnew(count)))
		return (NULL);
	offset = 0;
	length = 0;
	i = 0;
	while (i < count)
	{
		offset += length;
		while (str[offset] && str[offset] == c)
			++offset;
		length = 0;
		while (str[offset + length] && str[offset + length] != c)
			++length;
		if (length > 0)
			result[i++] = c_strsub(str, offset, length);
	}
	result[count] = NULL;
	return (result);
}
