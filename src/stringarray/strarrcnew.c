
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"



char	**c_strarrcnew(t_u32 y, t_size x, const char c)
{
	char	**strarr;
	t_u32	i;

	if (!(strarr = c_strarrnew(y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(strarr[i] = c_strnew(x)))
		{
			strarr[i] = NULL;
			c_strarrdel(&strarr);
			return (NULL);
		}
		c_memset(strarr[i], c, x);
		strarr[i][x] = '\0';
		++i;
	}
	strarr[y] = NULL;
	return (strarr);
}
