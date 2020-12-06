
#include "libft_string.h"



t_bool		ft_strhas(char const *str, char const *charset)
{
	t_size	i;
	t_size	c;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (FALSE);
#endif
	i = 0;
	while (str[i])
	{
		c = 0;
		while (charset[c])
		{
			if (str[i] == charset[c])
				return (TRUE);
			++c;
		}
		++i;
	}
	return (FALSE);
}



t_bool		ft_strhasonly(char const *str, char const *charset)
{
	t_size	i;
	t_size	c;
	t_bool	match;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || charset == NULL)
		return (FALSE);
#endif
	i = 0;
	while (str[i])
	{
		match = FALSE;
		c = 0;
		while (charset[c])
		{
			if (str[i] == charset[c])
			{
				match = TRUE;
				break ;
			}
			++c;
		}
		if (match == FALSE)
			return (FALSE);
		++i;
	}
	return (TRUE);
}
