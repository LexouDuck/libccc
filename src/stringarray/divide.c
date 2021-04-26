
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_char**	String_Divide(t_char const* str, t_size n)
{
	t_char**	result;
	int		lines;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
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
