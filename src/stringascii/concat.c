
#include "libccc/memory.h"
#include "libccc/text/stringascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*		String_Concat(t_ascii const* str1, t_ascii const* str2)
{
	t_ascii*	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (str2 == NULL), return (NULL);)
	length1 = String_Length(str1);
	length2 = String_Length(str2);
	result = (t_ascii*)Memory_Allocate(length1 + length2 + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
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

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = String_Concat(*a_dest, src);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_ascii*	String_Prepend(t_ascii const* src, t_ascii** a_dest)
{
	t_ascii*	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = String_Concat(src, *a_dest);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_ascii*	String_Merge(t_ascii** a_str1, t_ascii** a_str2)
{
	t_ascii*	result;

	HANDLE_ERROR(NULLPOINTER, (a_str1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_str2 == NULL), return (NULL);)
	result = String_Concat(*a_str1, *a_str2);
	String_Delete(a_str1);
	String_Delete(a_str2);
	*a_str1 = result;
	*a_str2 = result;
	return (result);
}
