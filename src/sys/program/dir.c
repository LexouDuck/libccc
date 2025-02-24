
#include "libccc.h"

#ifndef __NOSTD__
	#if (!defined(__GNUC__) && defined(__MSVC__))
	#include "libccc/compatibility/msvc/types.h"
	#include "libccc/compatibility/msvc/unistd.h"
	#else
	#include <unistd.h>
	#endif
#else
	typedef unsigned long	size_t;
	char*	getcwd(char* dest, size_t size);
#endif

#include "libccc/sys/program.h"

#include LIBCONFIG_ERROR_INCLUDE



#define MIN_BUFFER_SIZE		((t_size)16)
#define MAX_BUFFER_SIZE		((t_size)1024)



_INLINE()
t_char*	Program_GetCWD(void)
{
	t_char*	result = NULL;
	t_char*	buffer = NULL;
	t_size	size = 0;

	// attempt to have the function allocate the result by itself
	result = getcwd(NULL, 0);
	if (result != NULL)
		return (result);
	// since that behavior is not available here, fall back to allocating the buffer ourselves
	do
	{
		String_Delete(&result);
		if (size == 0)
			size = MIN_BUFFER_SIZE;
		else size *= 2;
		buffer = String_New(size);
		if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
			return (NULL);
		result = getcwd(buffer, size - 1);
	}
	while (result == NULL && size < MAX_BUFFER_SIZE);
	if CCCERROR((size >= MAX_BUFFER_SIZE), ERROR_INVALIDARGS, 
		"could not write date to string, size is too large (" SF_SIZE "), should be under " SF_SIZE,
		size, MAX_BUFFER_SIZE)
		return (NULL);
	return (NULL);
}
