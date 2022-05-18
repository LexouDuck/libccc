
#include "libccc/string.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_size	String_Length(t_ascii const* str)
{ return (strlen(str)); }
#else
inline
t_size	String_Length(t_ascii const* str)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	i = 0;
	while (str[i])
	{
		++i;
	}
	return (i);
}
#endif
