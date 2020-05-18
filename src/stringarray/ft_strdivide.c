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



char	**ft_strdivide(const char *str, t_size n)
{
	char	**result;
	int		lines;
	t_size	length;
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	length = ft_strlen(str);
	lines = length % n == 0 ? length / n : length / n + 1;
	if (lines == 0 || !(result = ft_strarrnew(lines)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		if (i + n < length)
			result[i / n] = ft_strsub(str, i, n);
		else
			result[i / n] = ft_strdup(str + i);
		i += n;
	}
	result[lines] = NULL;
	return (result);
}
