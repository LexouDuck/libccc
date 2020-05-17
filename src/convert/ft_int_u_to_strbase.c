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

#include "libft_memory.h"
#include "libft_convert.h"



static t_size	ft_u_to_strbase_getlength(char const *base)
{
	t_size	i;
	t_size	j;

#if HANDLE_NULLPOINTERS
	if (base == NULL)
		return (0);
#endif
	i = 0;
	while (base[i])
	{
		j = i - 1;
		while (j != (t_size)-1)
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
	t_size	length;
	t_size	i;
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
	if (!(result = (char *)ft_memalloc(i + 1)))
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
	t_size	length;
	t_size	i;
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
	if (!(result = (char *)ft_memalloc(i + 1)))
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
	t_size	length;
	t_size	i;
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
	if (!(result = (char *)ft_memalloc(i + 1)))
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
	t_size	length;
	t_size	i;
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
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i];
	result[n] = '\0';
	return (result);
}
