
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



inline void	String_Set(t_ascii* str, t_ascii c)
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
