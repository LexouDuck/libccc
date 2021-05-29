
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



inline
t_char**	StringArray_New(t_u32 length)
{
	return ((t_char**)Memory_New(sizeof(t_char*) * (length + 1)));
}



t_char**	StringArray_New_C(t_u32 y, t_size x, const t_char c)
{
	t_char**	strarr;
	t_u32	i;

	if (!(strarr = StringArray_New(y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(strarr[i] = String_New(x)))
		{
			strarr[i] = NULL;
			StringArray_Delete(&strarr);
			return (NULL);
		}
		Memory_Set(strarr[i], c, x);
		strarr[i][x] = '\0';
		++i;
	}
	strarr[y] = NULL;
	return (strarr);
}
