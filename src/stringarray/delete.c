
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



void	StringArray_Delete(t_char** *a_strarr)
{
	int		i;

	HANDLE_ERROR(NULLPOINTER, (a_strarr == NULL), return;)
	if (*a_strarr)
	{
		i = 0;
		while ((*a_strarr)[i])
		{
			String_Delete((*a_strarr) + i);
			++i;
		}
		Memory_Delete((void**)a_strarr);
	}
}
