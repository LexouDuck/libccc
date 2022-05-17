
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



inline
void	String_Free(t_char* str)
{
	Memory_Free(str);
}



inline
void	String_Delete(t_char** a_str)
{
	HANDLE_ERROR(NULLPOINTER, (a_str == NULL), return;)
	if (*a_str)
	{
		Memory_Free(*a_str);
		*a_str = NULL;
	}
}
