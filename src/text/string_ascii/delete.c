
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
void	String_Free(t_ascii* str)
{
	Memory_Free(str);
}



_INLINE()
void	String_Delete(t_ascii** a_str)
{
	if CCCERROR((a_str == NULL), ERROR_NULLPOINTER, "string address given is NULL")
		return;
	if (*a_str)
	{
		Memory_Free(*a_str);
		*a_str = NULL;
	}
}
