/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_int_u_to_strbase.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

static size_t	ft_u_to_strbase_getlength(char const *base)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (base[i])
	{
		j = i - 1;
		while (j != (size_t)-1)
		{
			if (base[i] == base[j])
				return (0);
			--j;
		}
		++i;
	}
	return (i < 2 ? 0 : i);
}

char			*ft_u8_to_strbase(t_u8 number, char const *base)
{
	char	*result;
	char	digits[8];
	size_t	length;
	size_t	i;
	t_u8	n;

	length = ft_u_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (i == 0)
		digits[i++] = base[0];
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char			*ft_u16_to_strbase(t_u16 number, char const *base)
{
	char	*result;
	char	digits[16];
	size_t	length;
	size_t	i;
	t_u16	n;

	length = ft_u_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (i == 0)
		digits[i++] = base[0];
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char			*ft_u32_to_strbase(t_u32 number, char const *base)
{
	char	*result;
	char	digits[32];
	size_t	length;
	size_t	i;
	t_u32	n;

	length = ft_u_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (i == 0)
		digits[i++] = base[0];
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char			*ft_u64_to_strbase(t_u64 number, char const *base)
{
	char	*result;
	char	digits[64];
	size_t	length;
	size_t	i;
	t_u64	n;

	length = ft_u_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (i == 0)
		digits[i++] = base[0];
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}
