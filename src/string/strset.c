
#include "libccc_string.h"



inline void	c_strset(char *str, char c)
{
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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
