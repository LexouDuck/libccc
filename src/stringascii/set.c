
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



void	String_Set(t_ascii* str, t_ascii c)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	i = 0;
	while (str[i])
	{
		str[i] = c;
		++i;
	}
}
