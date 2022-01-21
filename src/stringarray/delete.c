
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
void	StringArray_Free(t_char** strarr)
{
	for (t_uint i = 0; strarr[i]; ++i)
	{
		String_Free(strarr[i]);
	}
	Memory_Free(strarr);
}



void	StringArray_Delete(t_char** *a_strarr)
{
	HANDLE_ERROR(NULLPOINTER, (a_strarr == NULL), return;)
	if (*a_strarr)
	{
		for (t_uint i = 0; (*a_strarr)[i]; ++i)
		{
			String_Free((*a_strarr)[i]);
		}
		Memory_Delete((void**)a_strarr);
	}
}
