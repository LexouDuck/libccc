/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_size_to_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"

char	*ft_size_to_str(size_t number)
{
	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
	t_u8	i;
	size_t	n;

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
