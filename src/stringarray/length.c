
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint		StringArray_Length(t_char const** strarr)
{
	t_uint		i;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}
