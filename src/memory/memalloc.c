
/*
**	Functions used from <stdlib.h>:
**	-	void*	malloc(size_t n);
*/
#include <stdlib.h>

#include "libccc_memory.h"



inline void	*c_memalloc(t_size size)
{
	return (malloc(size));
}
