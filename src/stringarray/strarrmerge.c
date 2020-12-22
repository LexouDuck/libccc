
#include "libft_memory.h"
#include "libft_string.h"
#include "libft_stringarray.h"



char**	StringArray_Merge(char** *a_strarr1, char** *a_strarr2)
{
	char**	result;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_strarr1 == NULL || a_strarr2 == NULL)
		return (NULL);
#endif
	result = StringArray_Join((char const**)*a_strarr1, (char const**)*a_strarr2);
	StringArray_Delete(a_strarr1);
	StringArray_Delete(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}



char**	StringArray_Append(char** *a_dest, char const** src)
{
	char**	tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = StringArray_Join((char const**)*a_dest, src);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char**	fStringArray_Prepend(char const** src, char** *a_dest)
{
	char**	tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = StringArray_Join(src, (char const**)*a_dest);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}



char**	StringArray_Insert_InPlace(char** *a_dest, char const** src, t_u32 index)
{
	char**	tmp;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (a_dest == NULL || src == NULL)
		return (NULL);
#endif
	tmp = StringArray_Sub((char const**)*a_dest, 0, index);
	StringArray_Append(&tmp, src);
	StringArray_Append(&tmp, (char const**)(*a_dest) + index);
	StringArray_Delete(a_dest);
	*a_dest = tmp;
	return (*a_dest);
}
