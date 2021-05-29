
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline t_size	String_Length(t_char const* str)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	i = 0;
	while (str[i])
		++i;
	return (i);
}
