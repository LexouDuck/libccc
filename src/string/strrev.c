
#include "libccc_memory.h"
#include "libccc_string.h"



char	*c_strrev(char const *str)
{
	char	*result;
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
	result = (char *)c_memalloc(length + 1);
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
