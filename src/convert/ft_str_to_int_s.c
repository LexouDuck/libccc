/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_str_to_int_s.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_convert.h"



t_s8	ft_str_to_s8(char const *str)
{
	t_u8	result;
	t_bool	negative;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	negative = FALSE;
	if (str[i] == '-')
	{
		negative = TRUE;
		++i;
	}
	else if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((t_s8)(negative ? -result : result));
}



t_s16	ft_str_to_s16(char const *str)
{
	t_u16	result;
	t_bool	negative;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	negative = FALSE;
	if (str[i] == '-')
	{
		negative = TRUE;
		++i;
	}
	else if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((t_s16)(negative ? -result : result));
}



t_s32	ft_str_to_s32(char const *str)
{
	t_u32	result;
	t_bool	negative;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	negative = FALSE;
	if (str[i] == '-')
	{
		negative = TRUE;
		++i;
	}
	else if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((t_s32)(negative ? -result : result));
}



t_s64	ft_str_to_s64(char const *str)
{
	t_u64	result;
	t_bool	negative;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (!(ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	negative = FALSE;
	if (str[i] == '-')
	{
		negative = TRUE;
		++i;
	}
	else if (str[i] == '+')
		++i;
	result = 0;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return ((t_s64)(negative ? -result : result));
}
