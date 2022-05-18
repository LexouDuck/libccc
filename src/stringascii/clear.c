
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



void	String_Clear(t_ascii* str)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return;)
	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		++i;
	}
}
