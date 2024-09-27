/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_float_to_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../libft_convert.h"
#include "../../libft_string.h"

t_bool		ft_float_to_str_checkspecial(t_f32 number, char **result)
{
	if (isnan(number))
	{
		*result = ft_strdup("NaN");
		return (TRUE);
	}
	else if (number == INFINITY)
	{
		*result = ft_strdup("+INFINITY");
		return (TRUE);
	}
	else if (number == -INFINITY)
	{
		*result = ft_strdup("-INFINITY");
		return (TRUE);
	}
	return (FALSE);
}
