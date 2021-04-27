
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_char**		StringArray_Map(t_char const** strarr, t_char* (*map)(t_char const*))
{
	t_u32	i;
	t_char**	result;

	LIBCONFIG_HANDLE_NULLPOINTER(NULL, strarr)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, *strarr)
	LIBCONFIG_HANDLE_NULLPOINTER(NULL, map)
	if (!(result = StringArray_New(StringArray_Length(strarr))))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = (*map)(strarr[i]);
		++i;
	}
	return (result);
}



void		StringArray_Map_InPlace(t_char** *a_strarr, t_char* (*map)(t_char*))
{
	t_u32	i;
	t_char*	tmp;

	LIBCONFIG_HANDLE_NULLPOINTER(, a_strarr)
	LIBCONFIG_HANDLE_NULLPOINTER(, *a_strarr)
	LIBCONFIG_HANDLE_NULLPOINTER(, map)
	i = 0;
	while ((*a_strarr)[i])
	{
		tmp = (*map)((*a_strarr)[i]);
		if (tmp != (*a_strarr)[i])
			String_Delete(*a_strarr + i);
		(*a_strarr)[i] = tmp;
		++i;
	}
}
