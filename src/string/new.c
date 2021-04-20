
#include "libccc/memory.h"
#include "libccc/string.h"



char	*c_strnew(t_size n)
{
	char	*result;
	t_size	i;

	if (!(result = (char *)c_memalloc(n + 1)))
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



char	*c_strcnew(t_size n, char c)
{
	char	*result;
	t_size	i;

	if (!(result = (char *)c_memalloc(n + 1)))
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
