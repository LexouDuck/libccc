
#include "libccc/memory.h"

#ifndef __NOSTD__
	#include <stdlib.h>
#else
	void*	malloc(size_t n);
	void*	realloc(void* ptr, size_t n);
	void	free(void* ptr);
#endif



inline
void*	Memory_Allocate(t_size size)
{
	return (malloc(size));
}



inline
void*	Memory_Reallocate(void* ptr, t_size size)
{
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, ptr)
	return (realloc(ptr, size));
}



inline
void	Memory_Deallocate(void* ptr)
{
	LIBCONFIG_HANDLE_NULLPOINTER(, ptr)
	free(ptr);
}
