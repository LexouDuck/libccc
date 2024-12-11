
#include "libccc/text/string_ascii.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_size	String_Length(t_ascii const* str)
{ return (strlen(str)); }
#else
extern inline
t_size	String_Length(t_ascii const* str)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (0);
	i = 0;
	while (str[i])
	{
		++i;
	}
	return (i);
}
#endif
