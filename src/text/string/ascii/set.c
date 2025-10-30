
#include "libccc/text/string/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringASCII_Set(t_ascii* str, t_ascii c)
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
