
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/monad/stringarray.h"



char	**c_strarrsub(char const **strarr, t_u32 start, t_u32 n)
{
	char		**result;
	t_u32		length;
	t_u32		i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (NULL);
#endif
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
