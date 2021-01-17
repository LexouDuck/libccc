
#include "libccc_memory.h"
#include "libccc_string.h"
#include "libccc_stringarray.h"



void	c_strarrdel(char** *a_strarr)
{
	int		i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr == NULL)
		return ;
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
