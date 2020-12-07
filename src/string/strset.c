
#include "libft_string.h"



inline void	ft_strset(char *str, char c)
{
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return ;
#endif
	i = 0;
	while (str[i])
	{
		str[i] = c;
		++i;
	}
}
