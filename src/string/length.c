
#include "libccc/string.h"



inline t_size	String_Length(t_char const* str)
{
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(0, str)
	i = 0;
	while (str[i])
		++i;
	return (i);
}
