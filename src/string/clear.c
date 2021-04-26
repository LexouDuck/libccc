
#include "libccc/string.h"



void	String_Clear(t_char* str)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, )
	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		++i;
	}
}
