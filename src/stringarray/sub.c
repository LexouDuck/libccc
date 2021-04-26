
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_char**	c_strarrsub(t_char const** strarr, t_u32 start, t_u32 n)
{
	t_char**		result;
	t_u32		length;
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(strarr, NULL)
	length = c_strarrlen(strarr);
	if (start > length || start + n > length)
		return (NULL);
	if (!(result = c_strarrnew(n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (!(result[i] = c_strdup(strarr[start + i])))
		{
			c_strarrdel(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}
