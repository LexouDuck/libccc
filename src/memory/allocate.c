
/*
**	Functions used from <stdlib.h>:
**	-	void*	malloc(size_t n);
**	-	void*	realloc(void* ptr, size_t n);
**	-	void	free(void* ptr);
*/
#include <stdlib.h>

#include "libccc/memory.h"



inline
void*	Memory_Allocate(t_size size)
{
	return (malloc(size));
}



inline
void*	Memory_Reallocate(void *ptr, t_size size)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return (NULL);
#endif
	return (realloc(ptr, size));
}



inline
void	Memory_Deallocate(void *ptr)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (ptr == NULL)
		return;
#endif
	free(ptr);
}
