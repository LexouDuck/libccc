
#include "libccc/memory.h"
#include "libccc/string.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_char*		String_Join(t_char const* str1, t_char const* str2)
{
	t_char*	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (str2 == NULL), return (NULL);)
	length1 = String_Length(str1);
	length2 = String_Length(str2);
	result = (t_char*)Memory_Allocate(length1 + length2 + sizeof(""));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (i < length1)
	{
		result[i] = str1[i];
		++i;
	}
	i = 0;
	while (i < length2)
	{
		result[length1 + i] = str2[i];
		++i;
	}
	result[length1 + length2] = '\0';
	return (result);
}



t_char*	String_Append(t_char** a_dest, t_char const* src)
{
	t_char*	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = String_Join(*a_dest, src);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char*	String_Prepend(t_char const* src, t_char** a_dest)
{
	t_char*	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_dest == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (src == NULL), return (NULL);)
	tmp = String_Join(src, *a_dest);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



t_char*	String_Merge(t_char** a_str1, t_char** a_str2)
{
	t_char*	result;

	HANDLE_ERROR(NULLPOINTER, (a_str1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_str2 == NULL), return (NULL);)
	result = String_Join(*a_str1, *a_str2);
	String_Delete(a_str1);
	String_Delete(a_str2);
	*a_str1 = result;
	*a_str2 = result;
	return (result);
}
