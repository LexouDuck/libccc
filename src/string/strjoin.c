
#include "libccc_memory.h"
#include "libccc_string.h"


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
