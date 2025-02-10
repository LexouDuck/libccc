
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



_INLINE()
void	Memory_Delete(void* *ptr)
{
	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, "pointer address given is NULL")
		return;
	if (*ptr)
	{
		Memory_Free(*ptr);
		*ptr = NULL;
	}
}
