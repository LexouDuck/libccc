
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

t_sint	String_GraphemeCount_N(t_char const* str, t_size n)
{
	t_size	i;
	t_sint	result = 0;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (0);)
	i = 0;
	while (str[i])
	{
		t_sint charlen = UTF8_Length_N(str, n);
		if (charlen == ERROR)
			return ERROR;
		i += charlen;
		++result;
	}
	return (i);
}
