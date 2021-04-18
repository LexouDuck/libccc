
#include "libccc/string.h"
#include "libccc/monad/stringarray.h"



char	**c_strdivide(char const* str, t_size n)
{
	char	**result;
	int		lines;
	t_size	length;
	t_size	i;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	length = c_strlen(str);
	lines = length % n == 0 ? length / n : length / n + 1;
	if (lines == 0 || !(result = c_strarrnew(lines)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		if (i + n < length)
			result[i / n] = c_strsub(str, i, n);
		else
			result[i / n] = c_strdup(str + i);
		i += n;
	}
	result[lines] = NULL;
	return (result);
}
