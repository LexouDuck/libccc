
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_u32		StringArray_Length(t_char const** strarr)
{
	t_u32		i;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}
