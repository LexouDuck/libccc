
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	c_strsub(t_char const* str, t_size index, t_size n)
{
	t_char*	result;
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (index > length || index + n > length)
		return (NULL);
	if (!(result = (t_char* )c_memalloc(n + 1)))
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
