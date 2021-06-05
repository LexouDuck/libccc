
#include "libccc/memory.h"

#ifndef __NOSTD__
	#include <stdlib.h>
#else
	void*	malloc(size_t n);
	void*	realloc(void* ptr, size_t n);
	void	free(void* ptr);
#endif

#include LIBCONFIG_ERROR_INCLUDE



//#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
void*	Memory_Allocate(t_size size)
{
	return (malloc(size));
}



//#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
void*	Memory_Reallocate(void* ptr, t_size size)
{
	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return (NULL);)
	return (realloc(ptr, size));
}



//#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
void	Memory_Deallocate(void* ptr)
{
	HANDLE_ERROR(NULLPOINTER, (ptr == NULL), return;)
	free(ptr);
}
