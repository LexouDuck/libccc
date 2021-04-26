
#include "libccc/string.h"



void	c_striter(t_char* str, void (*f)(t_char* c))
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while (str[i])
	{
		f(&(str[i]));
		++i;
	}
}



void	c_striteri(t_char* str, void (*f)(t_char* c, t_size index))
{
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || f == NULL)
		return ;
#endif
	i = 0;
	while (str[i])
	{
		f(&(str[i]), i);
		++i;
	}
}
