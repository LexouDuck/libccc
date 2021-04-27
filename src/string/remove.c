
#include "libccc/memory.h"
#include "libccc/string.h"



t_char*	String_Remove(t_char const* str, t_char const* query)
{
	t_char*	result;
	t_size	matches;
	t_size	length;
	t_size	length_query;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, str)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, query)
	matches = String_Count_String(str, query);
	length = String_Length(str);
	length_query = String_Length(query);
	i = matches * length_query;
	length = (length < i) ? 0 : length - i;
	if (!(result = (t_char*)Memory_Alloc(length + sizeof(""))))
		return (NULL);
	matches = (t_size)(String_Find_String(str, query) - str);
	i = 0;
	while (i < length)
	{
		if (i == matches && (str += length_query))
			matches = (t_size)(String_Find_String(str, query) - str);
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
