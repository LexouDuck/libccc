
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/array/stringarray.h"


char**	StringArray_Join(char const** strarr1, char const** strarr2)
{
	char**	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr1 == NULL || strarr2 == NULL)
		return (NULL);
#endif
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	if (!(result = (char**)Memory_Alloc(sizeof(char*) * (length1 + length2 + 1))))
		return (NULL);
	i = 0;
	while (i < length1)
	{
		result[i] = String_Duplicate(strarr1[i]);
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = String_Duplicate(strarr2[i]);
		++i;
	}
	result[length1 + length2] = NULL;
	return (result);
}
