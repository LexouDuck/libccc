/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_int_s_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_convert.h"



char	*ft_s8_to_str(t_s8 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_8BIT];
	t_u8	i;
	t_u8	n;

	if (number < 0)
		n = -number;
	else n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)ft_memalloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}



char	*ft_s16_to_str(t_s16 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_16BIT];
	t_u8	i;
	t_u16	n;

	if (number < 0)
		n = -number;
	else n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)ft_memalloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}



char	*ft_s32_to_str(t_s32 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_32BIT];
	t_u8	i;
	t_u32	n;

	if (number < 0)
		n = -number;
	else n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)ft_memalloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}



char	*ft_s64_to_str(t_s64 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
	t_u8	i;
	t_u64	n;

	if (number < 0)
		n = -number;
	else n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char *)ft_memalloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = (number <= 0) ? 1 : 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}
