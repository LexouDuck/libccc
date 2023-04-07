
#include "libccc/memory.h"
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*	String_Sub(t_ascii const* str, t_size index, t_size n)
{
	t_ascii*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
		++length;
	if CCCERROR((index > length), ERROR_INDEX2LARGE, 
		"should be "SF_SIZE" or less, but got "SF_SIZE, length, index)
	return (NULL);
	if CCCERROR((index + n > length), ERROR_LENGTH2LARGE, 
		"should be "SF_SIZE" or less, but got "SF_SIZE, length, index + n)
	return (NULL);
	result = (t_ascii*)Memory_Allocate(n + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
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
