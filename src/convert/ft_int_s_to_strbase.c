/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_int_s_to_strbase.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"

static size_t	ft_s_to_strbase_getlength(char const *base)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
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

char			*ft_s8_to_strbase(t_s8 number, char const *base)
{
	char	*result;
	char	digits[8];
	size_t	length;
	size_t	i;
	t_u8	n;

	length = ft_s_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	if ((n = number) && number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? base[0] : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char			*ft_s16_to_strbase(t_s16 number, char const *base)
{
	char	*result;
	char	digits[16];
	size_t	length;
	size_t	i;
	t_u16	n;

	length = ft_s_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	if ((n = number) && number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? base[0] : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char			*ft_s32_to_strbase(t_s32 number, char const *base)
{
	char	*result;
	char	digits[32];
	size_t	length;
	size_t	i;
	t_u32	n;

	length = ft_s_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	if ((n = number) && number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? base[0] : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}

char			*ft_s64_to_strbase(t_s64 number, char const *base)
{
	char	*result;
	char	digits[64];
	size_t	length;
	size_t	i;
	t_u64	n;

	length = ft_s_to_strbase_getlength(base);
	if (length == 0)
		return (NULL);
	if ((n = number) && number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = base[n % length];
		n /= length;
	}
	if (!(result = (char *)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? base[0] : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}
