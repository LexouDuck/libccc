
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Reverse(t_ascii const* str)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;
	t_size	j;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
		++length;
	result = (t_ascii*)Memory_Allocate(length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
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
