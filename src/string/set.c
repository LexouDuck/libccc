
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline void	String_Set(t_char* str, t_char c)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return;)
	i = 0;
	while (str[i])
	{
		str[i] = c;
		++i;
	}
}
