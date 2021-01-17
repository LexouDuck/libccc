
#include "libccc_memory.h"
#include "libccc_string.h"



char	*c_strsub(char const *str, t_size index, t_size n)
{
	char	*result;
	t_size	length;
	t_size	i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	length = 0;
	while (str[length])
		++length;
	if (index > length || index + n > length)
		return (NULL);
	if (!(result = (char *)c_memalloc(n + 1)))
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
