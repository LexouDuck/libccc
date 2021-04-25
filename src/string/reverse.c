
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	c_strrev(t_char const* str)
{
	t_char*	result;
	t_size	length;
	t_size	i;
	t_size	j;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	result = (t_char* )c_memalloc(length + 1);
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
