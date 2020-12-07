
#include "libft_char.h"
#include "libft_convert.h"



t_u8	ft_str_to_u8(char const *str)
{
	t_u8	result;
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



t_u16	ft_str_to_u16(char const *str)
{
	t_u16	result;
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



t_u32	ft_str_to_u32(char const *str)
{
	t_u32	result;
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



t_u64	ft_str_to_u64(char const *str)
{
	t_u64	result;
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
