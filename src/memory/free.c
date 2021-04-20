
/*
**	Functions used from <stdlib.h>:
**	-	void	free(void* ptr);
*/
#include <stdlib.h>

#include "libccc/memory.h"



inline void	c_memfree(void *ptr)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	free(ptr);
}
