
#include "libccc/memory.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
void	Memory_Delete(void* *ptr)
{
	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return;)
	if (*ptr)
	{
		Memory_Free(*ptr);
		*ptr = NULL;
	}
}
