
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Sub(t_ascii const* str, t_size index, t_size n)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	HANDLE_ERROR_SF(INDEX2LARGE, (index > length), return (NULL);,
		"should be "SF_SIZE" or less, but got "SF_SIZE, length, index)
	HANDLE_ERROR_SF(LENGTH2LARGE, (index + n > length), return (NULL);,
		"should be "SF_SIZE" or less, but got "SF_SIZE, length, index + n)
	result = (t_ascii*)Memory_Allocate(n + sizeof(""));
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
