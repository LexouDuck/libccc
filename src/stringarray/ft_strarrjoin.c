/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strarrjoin.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"



static void	ft_strnb_charnb_in_strarr(const char **strarr, int *w_nb, int *c_nb)
{
	int str_at;

	str_at = 0;
	while (strarr[str_at])
	{
		*(c_nb) += ft_strlen(strarr[str_at]);
		++str_at;
	}
	*w_nb = str_at;
}

static void	ft_build_str(char *dest, char const **strarr, char const *sep)
{
	int i;
	int words;
	int chars;
	int sep_i;

	i = 0;
	sep_i = 0;
	words = -1;
	while (strarr[++words])
	{
		chars = 0;
		while (strarr[words][chars])
			dest[i++] = strarr[words][chars++];
		sep_i = 0;
		while (sep[sep_i] && strarr[words + 1])
			dest[i++] = sep[sep_i++];
	}
	dest[i] = '\0';
}

char		*ft_strarrjoin(char const **strarr, char const *sep)
{
	char	*str;
	int		strarr_str_nb;
	int		strarr_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || sep == NULL)
		return (NULL);
#endif
	strarr_str_nb = 0;
	strarr_char_nb = 0;
	ft_strnb_charnb_in_strarr(strarr, &strarr_str_nb, &strarr_char_nb);
	total_sep_char_nb = (strarr_str_nb - 1) * ft_strlen(sep);
	total_char_nb = total_sep_char_nb + strarr_char_nb;
	if (!(str = ft_strnew(total_char_nb + 1)))
		return (NULL);
	ft_build_str(str, strarr, sep);
	return (str);
}

/*
**	if (!strarr || !sep)
**		return (NULL);
*/