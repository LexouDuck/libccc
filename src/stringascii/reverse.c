
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char*	String_Reverse(t_char const* str)
{
	t_char*	result;
	t_size	length;
	t_size	i;
	t_size	j;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	length = 0;
	while (str[length])
		++length;
	result = (t_char*)Memory_Allocate(length + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	j = length - 1;
	while (i < length)
	{
		result[i] = str[j];
		++i;
		--j;
	}
	result[i] = '\0';
	return (result);
}
/*
**	if (str == NULL)
**		return (NULL);
*/
