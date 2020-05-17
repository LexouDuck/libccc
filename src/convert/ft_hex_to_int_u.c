/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_hex_to_int_u.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_convert.h"



static inline int	ft_hex_to_int_u_getdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (c - '0');
	if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}



t_u8				ft_hex_to_u8(char const *str)
{
	t_u8	result;
	t_size	i;

	i = 0;
	while (!(('0' <= str[i] && str[i] <= '9') ||
			('A' <= str[i] && str[i] <= 'F') ||
			('a' <= str[i] && str[i] <= 'f') ||
			str[i] == '+'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	else if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	result = 0;
	while (str[i] && (('0' <= str[i] && str[i] <= '9') ||
		('A' <= str[i] && str[i] <= 'F') || ('a' <= str[i] && str[i] <= 'f')))
	{
		result = result * 16 + ft_hex_to_int_u_getdigit(str[i]);
		++i;
	}
	return (result);
}



t_u16				ft_hex_to_u16(char const *str)
{
	t_u16	result;
	t_size	i;

	i = 0;
	while (!(('0' <= str[i] && str[i] <= '9') ||
			('A' <= str[i] && str[i] <= 'F') ||
			('a' <= str[i] && str[i] <= 'f') ||
			str[i] == '+'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	else if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	result = 0;
	while (str[i] && (('0' <= str[i] && str[i] <= '9') ||
		('A' <= str[i] && str[i] <= 'F') || ('a' <= str[i] && str[i] <= 'f')))
	{
		result = result * 16 + ft_hex_to_int_u_getdigit(str[i]);
		++i;
	}
	return (result);
}



t_u32				ft_hex_to_u32(char const *str)
{
	t_u32	result;
	t_size	i;

	i = 0;
	while (!(('0' <= str[i] && str[i] <= '9') ||
			('A' <= str[i] && str[i] <= 'F') ||
			('a' <= str[i] && str[i] <= 'f') ||
			str[i] == '+'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	else if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	result = 0;
	while (str[i] && (('0' <= str[i] && str[i] <= '9') ||
		('A' <= str[i] && str[i] <= 'F') || ('a' <= str[i] && str[i] <= 'f')))
	{
		result = result * 16 + ft_hex_to_int_u_getdigit(str[i]);
		++i;
	}
	return (result);
}



t_u64				ft_hex_to_u64(char const *str)
{
	t_u64	result;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (!(('0' <= str[i] && str[i] <= '9') ||
			('A' <= str[i] && str[i] <= 'F') ||
			('a' <= str[i] && str[i] <= 'f') ||
			str[i] == '+'))
	{
		if (!str[i] || !ft_isspace(str[i]))
			return (0);
		++i;
	}
	if (str[i] == '+')
		++i;
	else if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	result = 0;
	while (str[i] && (('0' <= str[i] && str[i] <= '9') ||
		('A' <= str[i] && str[i] <= 'F') || ('a' <= str[i] && str[i] <= 'f')))
	{
		result = result * 16 + ft_hex_to_int_u_getdigit(str[i]);
		++i;
	}
	return (result);
}
