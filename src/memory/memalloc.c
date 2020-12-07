
/*
**	Functions used from <stdlib.h>:
**	-	void*	malloc(size_t n);
*/
#include <stdlib.h>

#include "libft_memory.h"



inline void	*ft_memalloc(t_size size)
{
	return (malloc(size));
}
