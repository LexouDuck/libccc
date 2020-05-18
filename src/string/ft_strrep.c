/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strrep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_string.h"
#include "libft_stringarray.h"



//TODO char		*ft_strrep_char(char const *str, char const old, char const new)
//TODO char		*ft_strrep_charset(char const *str, char const *old, char const *new)

char		*ft_strrep_str(char const *str, char const *old, char const *new)
{
	char	**strarr;
	char	*result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || old == NULL || new == NULL)
		return (NULL);
#endif
	strarr = ft_strsplit_str(str, old);
	result = ft_strarrjoin((const char **)strarr, new);
	ft_strarrdel(&strarr);
	return (result);
}



void		ft_strrep_char_inplace(char *str, char const old, char const new)
{
	static char		old_as_str[2] = {0};
	static char		new_as_str[2] = {0};

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return ;
#endif
	if (old == '\0' || new == '\0')
		return ;
	old_as_str[0] = old;
	new_as_str[0] = new;
	ft_strrep_charset_inplace(str, old_as_str, new_as_str);
}



void		ft_strrep_charset_inplace(char *str, char const *old, char const *new)
{
	t_u32	i;
	t_u32	j;
	int		c_i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || old == NULL || new == NULL)
		return ;
#endif
	if (ft_strlen(old) != ft_strlen(new))
		return ;
	i = 0;
	while (old[i])
	{
		j = i;
		while (old[++j])
			if (old[i] == old[j])
				return ;
		++i;
	}
	i = 0;
	while (str[i])
	{
		if ((c_i = ft_strichr(old, str[i])) >= 0)
			str[i] = new[c_i];
		++i;
	}
}



void	ft_strrep_str_inplace(char **a_str, char const *old, char const *new)
{
	char	*tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_str == NULL || old == NULL || new == NULL)
		return ;
#endif
	if (ft_stristr(*a_str, old) == -1)
		return ;
	tmp = ft_strrep_str(*a_str, old, new);
	ft_strdel(a_str);
	*a_str = tmp;
}
