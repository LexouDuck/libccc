
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	c_strremove(t_char const* str, t_char const* query)
{
	t_char*	result;
	t_size	matches;
	t_size	length;
	t_size	length_query;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(query, NULL)
	matches = c_strcount_str(str, query);
	length = c_strlen(str);
	length_query = c_strlen(query);
	i = matches * length_query;
	length = (length < i) ? 0 : length - i;
	if (!(result = (t_char* )c_memalloc(length + 1)))
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
