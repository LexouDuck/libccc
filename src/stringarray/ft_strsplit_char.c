/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strsplit_char.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_stringarray.h"



static int	ft_strcsplit_get_count(char const *str, char c)
{
	int		result;
	t_bool	separator;
	size_t	i;

	separator = 1;
	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			separator = TRUE;
			++i;
		}
		if (str[i])
		{
			if (separator)
				++result;
		}
		else
			break ;
		separator = FALSE;
		++i;
	}
	return (result);
}

char		**ft_strsplit_char(char const *str, char c)
{
	char	**result;
	size_t	offset;
	size_t	length;
	int		count;
	int		i;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	count = ft_strcsplit_get_count(str, c);
	if (!(result = ft_strarrnew(count)))
		return (NULL);
	offset = 0;
	length = 0;
	i = 0;
	while (i < count)
	{
		offset += length;
		while (str[offset] && str[offset] == c)
			++offset;
		length = 0;
		while (str[offset + length] && str[offset + length] != c)
			++length;
		if (length > 0)
			result[i++] = ft_strsub(str, offset, length);
	}
	result[count] = NULL;
	return (result);
}
