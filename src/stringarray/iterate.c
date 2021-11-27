
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringArray_Iterate(t_char** strarr,
	t_char* (*f)(t_char* str))
{
	t_uint	i;
	t_char*	tmp;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	i = 0;
	while (strarr[i])
	{
		tmp = f(strarr[i]);
		if (tmp != strarr[i])
			String_Delete(strarr + i);
		strarr[i] = tmp;
		++i;
	}
}



void	StringArray_Iterate_I(t_char** strarr,
	t_char* (*f)(t_char* str, t_uint index))
{
	t_uint	i;
	t_char*	tmp;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return;)
	HANDLE_ERROR(NULLPOINTER, (f == NULL), return;)
	i = 0;
	while (strarr[i])
	{
		tmp = f(strarr[i], i);
		if (tmp != strarr[i])
			String_Delete(strarr + i);
		strarr[i] = tmp;
		++i;
	}
}
