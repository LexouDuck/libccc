
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*		String_Concat(t_ascii const* str1, t_ascii const* str2)
{
	t_ascii*	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	if CCCERROR((str1 == NULL), ERROR_NULLPOINTER, "left-hand-side string given is NULL")
		return (NULL);
	if CCCERROR((str2 == NULL), ERROR_NULLPOINTER, "right-hand-side string given is NULL")
		return (NULL);
	length1 = String_Length(str1);
	length2 = String_Length(str2);
	result = (t_ascii*)Memory_Allocate(length1 + length2 + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	for (i = 0; i < length1; ++i)
	{
		result[i] = str1[i];
	}
	for (i = 0; i < length2; ++i)
	{
		result[length1 + i] = str2[i];
	}
	result[length1 + length2] = '\0';
	return (result);
}



t_ascii*	String_Append(t_ascii** a_dest, t_ascii const* src)
{
	t_ascii*	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to append given is NULL")
		return (NULL);
	tmp = String_Concat(*a_dest, src);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_ascii*	String_Prepend(t_ascii const* src, t_ascii** a_dest)
{
	t_ascii*	tmp;

	if CCCERROR((a_dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (NULL);
	if CCCERROR((src == NULL), ERROR_NULLPOINTER, "string to prepend given is NULL")
		return (NULL);
	tmp = String_Concat(src, *a_dest);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_ascii*	String_Merge(t_ascii** a_str1, t_ascii** a_str2)
{
	t_ascii*	result;

	if CCCERROR((a_str1 == NULL), ERROR_NULLPOINTER, "left-hand-side string given is NULL")
		return (NULL);
	if CCCERROR((a_str2 == NULL), ERROR_NULLPOINTER, "right-hand-side string given is NULL")
		return (NULL);
	result = String_Concat(*a_str1, *a_str2);
	String_Delete(a_str1);
	String_Delete(a_str2);
	*a_str1 = result;
	*a_str2 = result;
	return (result);
}
