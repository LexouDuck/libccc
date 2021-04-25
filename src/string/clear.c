
#include "libccc/string.h"



void	c_strclr(t_char* str)
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
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
