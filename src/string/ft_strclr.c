
#include "libft_string.h"



void	ft_strclr(char *str)
{
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return ;
#endif
	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		++i;
	}
}
