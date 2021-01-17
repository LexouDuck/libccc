
/*
**	Functions used from <stdlib.h>:
**	-	void	free(void* ptr);
*/
#include <stdlib.h>

#include "libccc_memory.h"



inline void	c_memfree(void *ptr)
{
#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	free(ptr);
}
