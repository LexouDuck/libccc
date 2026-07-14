
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE




//! Like StringUTF8_IndexOf_String(), but does not log an error when the query is not found
static
t_sintmax	StringUTF8_Remove_IndexOf(t_utf8 const* str, t_utf8 const* query)
{
	t_size	i;
	t_size	j;

	if (query[0] == '\0')
		return (ERROR);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (query[j] == str[i + j])
		{
			++j;
			if (query[j] == '\0')
				return ((t_sintmax)i);
			if (str[i + j] == '\0')
				return (ERROR);
		}
		++i;
	}
	return (ERROR);
}



t_utf8*	StringUTF8_Remove(t_utf8 const* str, t_utf8 const* query)
{
	t_utf8*		result;
	t_sintmax	match;
	t_sintmax	next;
	t_size	length;
	t_size	length_query;
	t_size	i;
	t_size	j;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "string to remove given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	length_query = StringUTF8_Length(query);
	if (length_query == 0)
		return (StringUTF8_Duplicate(str));
	i = StringUTF8_Count_String(str, query) * length_query;
	length = (length < i) ? 0 : length - i;
	result = (t_utf8*)Memory_Allocate(length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	match = StringUTF8_Remove_IndexOf(str, query);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (match >= 0 && i == (t_size)match)
		{	// skip this occurrence of the query, and find the next one
			i += length_query;
			next = StringUTF8_Remove_IndexOf(str + i, query);
			match = (next < 0 ? next : (t_sintmax)(i + (t_size)next));
			continue;
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
