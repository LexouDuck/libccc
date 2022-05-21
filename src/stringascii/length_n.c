
#include "libccc/text/stringascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE


inline
t_size	String_Length_N(t_ascii const* str, t_size n)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		++i;
	}
	return (i);
}
