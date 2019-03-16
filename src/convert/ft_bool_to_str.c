/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_bool_to_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_convert.h"

char	*ft_bool_to_str(t_bool number, t_bool uppercase)
{
	char	*result;

	if (number)
	{
		if (!(result = (char *)malloc(5)))
			return (NULL);
		result[0] = uppercase ? 'T' : 't';
		result[1] = uppercase ? 'R' : 'r';
		result[2] = uppercase ? 'U' : 'u';
		result[3] = uppercase ? 'E' : 'e';
		result[4] = '\0';
	}
	else
	{
		if (!(result = (char *)malloc(6)))
			return (NULL);
		result[0] = uppercase ? 'F' : 'f';
		result[1] = uppercase ? 'A' : 'a';
		result[2] = uppercase ? 'L' : 'l';
		result[3] = uppercase ? 'S' : 's';
		result[4] = uppercase ? 'E' : 'e';
		result[5] = '\0';
	}
	return (result);
}
