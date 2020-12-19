
#include "libft_char.h"
#include "libft_convert.h"



t_size	Convert_String_To_Size(char const* str)
{
	t_size	result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - '0';
		++i;
	}
	return (result);
}
