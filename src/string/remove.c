
#include "libccc/memory.h"
#include "libccc/string.h"



char	*c_strremove(char const *str, char const *query)
{
	char	*result;
	t_size	matches;
	t_size	length;
	t_size	length_query;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL || query == NULL)
		return (NULL);
#endif
	matches = c_strcount_str(str, query);
	length = c_strlen(str);
	length_query = c_strlen(query);
	i = matches * length_query;
	length = (length < i) ? 0 : length - i;
	if (!(result = (char *)c_memalloc(length + 1)))
		return (NULL);
	matches = (t_size)(c_strstr(str, query) - str);
	i = 0;
	while (i < length)
	{
		if (i == matches && (str += length_query))
			matches = (t_size)(c_strstr(str, query) - str);
		result[i] = *(str++);
		++i;
	}
	result[i] = '\0';
	return (result);
}

/*
**	if (str == NULL)
**		return (NULL);
*/
