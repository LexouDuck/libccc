
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



void	StringArray_Delete(t_char** *a_strarr)
{
	int		i;

	LIBCONFIG_HANDLE_NULLPOINTER(a_strarr, )
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
