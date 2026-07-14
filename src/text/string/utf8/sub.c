
#include "libccc/memory.h"
#include "libccc/text/format.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Sub(t_utf8 const* str, t_size index, t_size n)
{
	t_utf8*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	if CCCERROR((index > length), ERROR_INDEX2LARGE,
		"should be " SF_SIZE " or less, but got " SF_SIZE, length, index)
		return (NULL);
	if CCCERROR((index + n > length), ERROR_LENGTH2LARGE,
		"should be " SF_SIZE " or less, but got " SF_SIZE, length, index + n)
		return (NULL);
	result = (t_utf8*)Memory_Allocate(n + sizeof(""));
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
