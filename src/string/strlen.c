
#include "libft_string.h"



inline t_size	ft_strlen(char const *str)
{
	t_size	i;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (0);
#endif
	i = 0;
	while (str[i])
		++i;
	return (i);
}
