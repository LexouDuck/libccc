
#include "libccc/string.h"
#include "libccc/stringarray.h"



static int	String_Split_Char_GetCount(t_char const* str, t_char c)
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
			break;
		separator = FALSE;
		++i;
	}
	return (result);
}

t_char**		String_Split_Char(t_char const* str, t_char c)
{
	t_char**	result;
	t_size	offset;
	t_size	length;
	int		count;
	int		i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	count = String_Split_Char_GetCount(str, c);
	if (!(result = StringArray_New(count)))
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
			result[i++] = String_Sub(str, offset, length);
	}
	result[count] = NULL;
	return (result);
}
