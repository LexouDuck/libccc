
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

	if CCCERROR((strarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side string array given is NULL")
		return (NULL);
	if CCCERROR((strarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side string array given is NULL")
		return (NULL);
	length1 = StringArray_Length(strarr1);
	length2 = StringArray_Length(strarr2);
	result = (t_char**)Memory_Allocate(sizeof(t_char*) * (length1 + length2 + 1));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
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



t_char**	StringArray_Append(t_char** *a_dest, t_char const* const* src)
{
	t_char**	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string array address is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to append given is NULL")
		return (NULL);
	tmp = StringArray_Concat((t_char const* const*)*a_dest, src);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char**	StringArray_Prepend(t_char const* const* src, t_char** *a_dest)
{
	t_char**	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string array address is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string array to prepend given is NULL")
		return (NULL);
	tmp = StringArray_Concat(src, (t_char const* const*)*a_dest);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char**	StringArray_Merge(t_char** *a_strarr1, t_char** *a_strarr2)
{
	t_char**	result;

	if CCCERROR((a_strarr1 == NULL), ERROR_NULLPOINTER, "left-hand-side string array given is NULL")
		return (NULL);
	if CCCERROR((a_strarr2 == NULL), ERROR_NULLPOINTER, "right-hand-side string array given is NULL")
		return (NULL);
	result = StringArray_Concat((t_char const**)*a_strarr1, (t_char const**)*a_strarr2);
	StringArray_Delete(a_strarr1);
	StringArray_Delete(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}
