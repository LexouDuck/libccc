
#include "libccc/stringarray.h"



t_char**	StringArray_Merge(t_char** *a_strarr1, t_char** *a_strarr2)
{
	t_char**	result;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, a_strarr1)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, a_strarr2)
	result = StringArray_Join((t_char const**)*a_strarr1, (t_char const**)*a_strarr2);
	StringArray_Delete(a_strarr1);
	StringArray_Delete(a_strarr2);
	*a_strarr1 = result;
	*a_strarr2 = result;
	return (result);
}
