/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert/ft_str_to_float.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_convert.h"
#include "libft_char.h"
#include "libft_string.h"



static char	*ft_str_to_float_toupper(char const *str)
{
	char	*result;
	t_s32	end;
	t_s32	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	end = ft_strlen(str) - 1;
	while (end >= 0 && !ft_isalnum(str[end]))
		--end;
	if (end == -1 || 1 + end <= i)
		return (NULL);
	result = ft_strsub(str, i, 1 + end - i);
	i = 0;
	while (result[i])
	{
		result[i] = ft_toupper(result[i]);
		++i;
	}
	return (result);
}

int			ft_str_to_float_checkinvalid(char const *str, char **result_tmp)
{
	char	*tmp;
	t_size	count_p;
	t_size	count_e;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (ERROR);
#endif
	*result_tmp = NULL;
	if (str[0] == '\0' || !(tmp = ft_str_to_float_toupper(str)))
		return (ERROR);
	if (ft_strequ(tmp, "INF") || ft_strequ(tmp, "INFINITY") ||
		ft_strequ(tmp, "+INF") || ft_strequ(tmp, "+INFINITY") ||
		ft_strequ(tmp, "-INF") || ft_strequ(tmp, "-INFINITY"))
	{
		*result_tmp = tmp;
		return (OK);
	}
	count_p = ft_strcount_char(tmp, 'P');
	count_e = ft_strcount_char(tmp, 'E');
	if (!tmp || !tmp[0] || !ft_strhasonly(tmp, "0123456789.+-ABCDEFXP") ||
		count_p > 1 || (count_p == 0 && count_e > 1))
	{
		if (tmp)
			free(tmp);
		return (ERROR);
	}
	*result_tmp = tmp;
	return (OK);
}
