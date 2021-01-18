
#include "libccc_stringarray.h"



t_u32		c_strarrlen(char const** strarr)
{
	t_u32		i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (0);
#endif
	i = 0;
	while (strarr[i])
	{
		++i;
	}
	return (i);
}
