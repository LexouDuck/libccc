
#include "libccc/stringarray.h"



t_u32		StringArray_Length(t_char const** strarr)
{
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(strarr, 0)
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}
