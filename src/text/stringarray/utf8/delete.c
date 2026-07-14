
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArrayUTF8_Free(t_utf8** strarr)
{
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return;
	for (i = 0; strarr[i]; ++i)
	{
		StringUTF8_Free(strarr[i]);
	}
	Memory_Free(strarr);
}



void	StringArrayUTF8_Delete(t_utf8** *a_strarr)
{
	t_uint	i;

	if CCCERROR((a_strarr == NULL), ERROR_NULLPOINTER, "string array address given is NULL")
		return;
	if (*a_strarr)
	{
		for (i = 0; (*a_strarr)[i]; ++i)
		{
			StringUTF8_Free((*a_strarr)[i]);
		}
		Memory_Delete((void**)a_strarr);
	}
}
