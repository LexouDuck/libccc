
#include "libccc/stringarray.h"



t_u32		StringArray_Length(t_char const** strarr)
{
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(0, strarr)
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}
