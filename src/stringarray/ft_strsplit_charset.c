/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringarray/ft_strsplit_charset.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"



static int	ft_in_charset(char c, char const* charset)
{
	int i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

static int	ft_str_word_nb(char const* str, char const* sep_chars)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_in_charset(str[i], sep_chars))
			++i;
		if (str[i] == '\0')
			return (count);
		count++;
		while (!ft_in_charset(str[i], sep_chars) && str[i])
			++i;
	}
	return (count);
}

static int	ft_sing_word_lett_count(char const* str, int ws, char const* seps)
{
	int i;

	i = 0;
	while (!ft_in_charset(str[ws + i], seps) && str[ws + i])
		++i;
	return (i);
}

char		**ft_strsplit_charset(char const* str, char const* sep_chars)
{
	int		i;
	int		j;
	int		wstart;
	int		length;
	char	**strarr;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || sep_chars == NULL)
		return (NULL);
#endif
	if (!(strarr = ft_strarrnew(ft_str_word_nb(str, sep_chars))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_str_word_nb(str, sep_chars))
	{
		while (ft_in_charset(str[j], sep_chars))
			++j;
		wstart = j--;
		length = ft_sing_word_lett_count(str, wstart, sep_chars);
		if (!(strarr[i] = ft_strnew(length)))
			return (NULL);
		while (++j < wstart + length)
			strarr[i][j - wstart] = str[j];
		strarr[i++][j - wstart] = '\0';
	}
	strarr[i] = 0;
	return (strarr);
}
