
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringUTF8_Free(t_utf8* str)
{
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	Memory_Free(str);
}



void	StringUTF8_Delete(t_utf8* *a_str)
{
	if CCCERROR((a_str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return;
	if (*a_str)
	{
		Memory_Delete((void**)a_str);
	}
}
