
#include "libccc/string.h"



inline void	String_Set(t_char* str, t_char c)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, )
	i = 0;
	while (str[i])
	{
		str[i] = c;
		++i;
	}
}
