/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strdivide.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_stringarray.h"

char	**ft_strdivide(const char *str, size_t n)
{
	char	**result;
	int		lines;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	lines = len % n == 0 ? len / n : len / n + 1;
	if (lines == 0 || !(result = ft_strarrnew(lines)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i + n < len)
			result[i / n] = ft_strsub(str, i, n);
		else
			result[i / n] = ft_strdup(str + i);
		i += n;
	}
	result[lines] = NULL;
	return (result);
}

/*
**	if (!str || n == 0)
**		return (NULL);
*/