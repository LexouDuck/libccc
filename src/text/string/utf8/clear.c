
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringUTF8_Clear(t_utf8* str)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		++i;
	}
}
