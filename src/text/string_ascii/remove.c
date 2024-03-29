
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
static
t_sintmax	String_Remove_IndexOf(t_ascii const* str, t_ascii const* query)
{
	return (strstr(str, query));
}
#else
static
t_sintmax	String_Remove_IndexOf(t_ascii const* str, t_ascii const* query)
{
	t_size	i;

	if (query[0] == '\0')
		return (ERROR);
	i = 0;
	while (str[i])
	{
		t_size j = 0;
		while (query[j] == str[i + j])
		{
			++j;
			if (query[j] == '\0')
				return (i);
			if (str[i + j] == '\0')
				return (ERROR);
		}
		++i;
	}
	return (ERROR);
}
#endif



t_ascii*	String_Remove(t_ascii const* str, t_ascii const* query)
{
	t_sintmax	matches;
	t_ascii*	result;
	t_size	length;
	t_size	length_query;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "string to remove given is NULL")
		return (NULL);
	matches = String_Count_String(str, query);
	length = String_Length(str);
	length_query = String_Length(query);
	i = matches * length_query;
	length = (length < i) ? 0 : length - i;
	result = (t_ascii*)Memory_Allocate(length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	matches = String_Remove_IndexOf(str, query);
	i = 0;
	while (i < length)
	{
		if ((t_sintmax)i == matches && (str += length_query))
			matches = String_Remove_IndexOf(str, query);
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
