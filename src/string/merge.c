
#include "libccc/memory.h"
#include "libccc/string.h"



char*		String_Join(char const* str1, char const* str2)
{
	char*	result;
	t_size	length1;
	t_size	length2;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str1 == NULL || str2 == NULL)
		return (NULL);
#endif
	length1 = String_Length(str1);
	length2 = String_Length(str2);
	if (!(result = (char*)Memory_Alloc(length1 + length2 + 1)))
		return (NULL);
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



char*	String_Append(char* *a_dest, char const* src)
{
	char*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = String_Join(*a_dest, src);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char*	String_Prepend(char const* src, char* *a_dest)
{
	char*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = String_Join(src, *a_dest);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char*	String_Merge(char* *a_str1, char* *a_str2)
{
	char*	result;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_str1 == NULL || a_str2 == NULL)
		return (NULL);
#endif
	result = String_Join(*a_str1, *a_str2);
	String_Delete(a_str1);
	String_Delete(a_str2);
	*a_str1 = result;
	*a_str2 = result;
	return (result);
}
