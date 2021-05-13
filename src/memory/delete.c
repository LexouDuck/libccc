
#include "libccc/memory.h"



inline
void	Memory_Delete(void* *ptr)
{
	LIBCONFIG_HANDLE_NULLPOINTER(, ptr)
	if (*ptr)
	{
		Memory_Free(*ptr);
		*ptr = NULL;
	}
}
