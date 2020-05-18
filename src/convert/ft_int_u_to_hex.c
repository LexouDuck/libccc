/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_int_u_to_hex.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_convert.h"



char	*ft_u8_to_hex(t_u8 number)
{
	char	*result;
	t_u8	digits[2];
	t_u8	i;
	t_u8	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 16;
		n /= 16;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);
	result[n] = '\0';
	return (result);
}



char	*ft_u16_to_hex(t_u16 number)
{
	char	*result;
	t_u8	digits[4];
	t_u8	i;
	t_u16	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 16;
		n /= 16;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);
	result[n] = '\0';
	return (result);
}



char	*ft_u32_to_hex(t_u32 number)
{
	char	*result;
	t_u8	digits[8];
	t_u8	i;
	t_u32	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 16;
		n /= 16;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);
	result[n] = '\0';
	return (result);
}



char	*ft_u64_to_hex(t_u64 number)
{
	char	*result;
	t_u8	digits[16];
	t_u8	i;
	t_u64	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 16;
		n /= 16;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)ft_memalloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);
	result[n] = '\0';
	return (result);
}
