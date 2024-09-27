/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_int_u_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"

char	*ft_u8_to_str(t_u8 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_8BIT];
	t_u8	i;
	t_u8	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}

char	*ft_u16_to_str(t_u16 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_16BIT];
	t_u8	i;
	t_u16	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}

char	*ft_u32_to_str(t_u32 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_32BIT];
	t_u8	i;
	t_u32	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}

char	*ft_u64_to_str(t_u64 number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
	t_u8	i;
	t_u64	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char *)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n] = '\0';
	return (result);
}
