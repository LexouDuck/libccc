
#include "libft_string.h"



void	ft_striter(char *str, void (*f)(char *))
{
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while (str[i])
	{
		f(str + i);
		++i;
	}
}



void	ft_striteri(char *str, void (*f)(t_size, char *))
{
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while (str[i])
	{
		f(i, str + i);
		++i;
	}
}
