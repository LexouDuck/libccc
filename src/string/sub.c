
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char*	String_Sub(t_char const* str, t_size index, t_size n)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	HANDLE_ERROR(INDEX2LARGE, (index > length), return (NULL);)
	HANDLE_ERROR(LENGTH2LARGE, (index + n > length), return (NULL);)
	result = (t_char*)Memory_Allocate(n + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < n)
	{
		result[i] = str[index + i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
