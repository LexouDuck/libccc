
#include "libccc_string.h"



void	c_striter(char *str, void (*f)(char *))
{
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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



void	c_striteri(char *str, void (*f)(t_size, char *))
{
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
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
