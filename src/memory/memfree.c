
/*
**	Functions used from <stdlib.h>:
**	-	void	free(void* ptr);
*/
#include <stdlib.h>

#include "libft_memory.h"



inline void	ft_memfree(void *ptr)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return ;
#endif
	free(ptr);
}
