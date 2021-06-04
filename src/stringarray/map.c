
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_char**		StringArray_Map(t_char const** strarr, t_char* (*map)(t_char const*))
{
	t_uint	i;
	t_char**	result;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (*strarr == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return (NULL);)
	result = StringArray_New(StringArray_Length(strarr));
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), return (NULL);)
	i = 0;
	while (strarr[i])
	{
		result[i] = map(strarr[i]);
		++i;
	}
	return (result);
}



void		StringArray_Map_InPlace(t_char** *a_strarr, t_char* (*map)(t_char*))
{
	t_uint	i;
	t_char*	tmp;

	HANDLE_ERROR(NULLPOINTER, (a_strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (*a_strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (map == NULL), return;)
	i = 0;
	while ((*a_strarr)[i])
	{
		tmp = map((*a_strarr)[i]);
		if (tmp != (*a_strarr)[i])
			String_Delete(*a_strarr + i);
		(*a_strarr)[i] = tmp;
		++i;
	}
}
