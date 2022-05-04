
#include "libccc/string.h"
#include "libccc/text/unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <string.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE


inline
t_size	String_Length_N(t_char const* str, t_size n)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	i = 0;
	while (str[i] && i < n)
	{
		++i;
	}
	return (i);
}
