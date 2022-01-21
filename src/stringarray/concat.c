
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Concat(t_char const* const* strarr1, t_char const* const* strarr2)
{
	t_char**	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (strarr1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (strarr2 == NULL), return (NULL);)
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	result = (t_char**)Memory_Allocate(sizeof(t_char*) * (length1 + length2 + 1));
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



t_char**	StringArray_Append(t_char** *a_dest, t_char const* const* src)
{
	t_char**	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = StringArray_Concat((t_char const* const*)*a_dest, src);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char**	StringArray_Prepend(t_char const* const* src, t_char** *a_dest)
{
	t_char**	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = StringArray_Concat(src, (t_char const* const*)*a_dest);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char**	StringArray_Merge(t_char** *a_strarr1, t_char** *a_strarr2)
{
	t_char**	result;

	HANDLE_ERROR(NULLPOINTER, (a_strarr1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_strarr2 == NULL), return (NULL);)
	result = StringArray_Concat((t_char const**)*a_strarr1, (t_char const**)*a_strarr2);
	StringArray_Delete(a_strarr1);
	StringArray_Delete(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}
