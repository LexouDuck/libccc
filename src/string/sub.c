
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	String_Sub(t_char const* str, t_size index, t_size n)
{
	t_char*	result;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	length = 0;
	while (str[length])
		++length;
	LIBCONFIG_HANDLE_INDEX2LARGE(index, NULL, length)
	LIBCONFIG_HANDLE_INDEX2LARGE(index + n, NULL, length)
	if (!(result = (t_char*)Memory_Alloc(n + sizeof(""))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = str[index + i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
