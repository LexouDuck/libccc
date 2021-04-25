
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	c_strnew(t_size n)
{
	t_char*	result;
	t_size	i;

	if (!(result = (t_char* )c_memalloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = '\0';
		++i;
	}
	result[n] = '\0';
	return (result);
}



t_char*	c_strcnew(t_size n, t_char c)
{
	t_char*	result;
	t_size	i;

	if (!(result = (t_char* )c_memalloc(n + 1)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = c;
		++i;
	}
	result[n] = '\0';
	return (result);
}
