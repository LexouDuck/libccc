
#include "libccc/string.h"



void	String_Iterate(t_char* str, void (*f)(t_char* c))
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, )
	LIBCONFIG_HANDLE_NULLPOINTER(f, )
	i = 0;
	while (str[i])
	{
		f(&(str[i]));
		++i;
	}
}



void	String_Iterate_I(t_char* str, void (*f)(t_char* c, t_size index))
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, )
	LIBCONFIG_HANDLE_NULLPOINTER(f, )
	i = 0;
	while (str[i])
	{
		f(&(str[i]), i);
		++i;
	}
}
