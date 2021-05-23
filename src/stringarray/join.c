
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_char**	StringArray_Join(t_char const** strarr1, t_char const** strarr2)
{
	t_char**	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (strarr1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (strarr2 == NULL), return (NULL);)
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	result = (t_char**)Memory_Alloc(sizeof(t_char*) * (length1 + length2 + 1));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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
