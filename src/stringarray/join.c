
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"


t_char**	StringArray_Join(t_char const** strarr1, t_char const** strarr2)
{
	t_char**	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(strarr1, NULL)
	LIBCONFIG_HANDLE_NULLPOINTER(strarr2, NULL)
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	if (!(result = (t_char**)Memory_Alloc(sizeof(t_char*) * (length1 + length2 + 1))))
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
