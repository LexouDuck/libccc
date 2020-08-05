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

/*
**	Functions used from <stdio.h>:
**	-	char*	snprintf(char* dest, size_t n, char const* format, ...);
*/
#include <stdio.h>

#include "libft_string.h"
#include "libft_math.h"
#include "libft_convert.h"



// TODO change the following 25 lines

static const int max_size = 64;

char	*ft_f32_to_str(t_f32 number)
{
	char* tmp = ft_strnew(max_size);
	if (tmp == NULL)
		return (NULL);
	snprintf(tmp, max_size, "%g", number);
	char* result = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (result);
}

char	*ft_f64_to_str(t_f64 number)
{
	char* tmp = ft_strnew(max_size);
	if (tmp == NULL)
		return (NULL);
	snprintf(tmp, max_size, "%g", number);
	char* result = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (result);
}



t_bool		ft_float_to_str_checkspecial(t_f32 number, char **result)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (result == NULL)
		return (FALSE);
#endif
	if (IS_NAN(number))
	{
		*result = ft_strdup("NaN");
		return (TRUE);
	}
	else if (IS_INFINITY(number))
	{
		*result = (number < 0 ?
			ft_strdup("-INFINITY") :
			ft_strdup("+INFINITY"));
		return (TRUE);
	}
	return (FALSE);
}
