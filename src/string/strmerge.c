
#include "libccc/string.h"



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



char*	String_Insert_InPlace(char* *a_dest, char const* src, t_u32 index)
{
	char*	tmp;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = String_Sub(*a_dest, 0, index);
	String_Append(&tmp, src);
	String_Append(&tmp, (*a_dest) + index);
	String_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
