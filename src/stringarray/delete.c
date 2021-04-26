
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



void	c_strarrdel(char** *a_strarr)
{
	int		i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return;
#endif
	if (*a_strarr)
	{
		i = 0;
		while ((*a_strarr)[i])
		{
			c_strdel((*a_strarr) + i);
			++i;
		}
		c_memdel((void**)a_strarr);
	}
}
