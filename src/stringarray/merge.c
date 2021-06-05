
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArray_Merge(t_char** *a_strarr1, t_char** *a_strarr2)
{
	t_char**	result;

	HANDLE_ERROR(NULLPOINTER, (a_strarr1 == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (a_strarr2 == NULL), return (NULL);)
	result = StringArray_Join((t_char const**)*a_strarr1, (t_char const**)*a_strarr2);
	StringArray_Delete(a_strarr1);
	StringArray_Delete(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}
