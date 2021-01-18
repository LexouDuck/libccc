
#include "libccc_memory.h"



inline void	c_memdel(void **ptr)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	if (*ptr)
	{
		c_memfree(*ptr);
		*ptr = NULL;
	}
}
