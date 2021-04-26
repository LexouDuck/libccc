
#include "libccc/memory.h"
#include "libccc/string.h"



inline void	String_Delete(t_char** a_str)
{
	LIBCONFIG_HANDLE_NULLPOINTER(a_str, )
	if (*a_str)
	{
		Memory_Free(*a_str);
		*a_str = NULL;
	}
}
