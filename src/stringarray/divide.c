
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_char**	String_Divide(t_char const* str, t_size n)
{
	t_char**	result;
	int		lines;
	t_size	length;
	t_size	i;

	LIBCONFIG_HANDLE_NULLPOINTER(str, NULL)
	length = String_Length(str);
	lines = length % n == 0 ? length / n : length / n + 1;
	if (lines == 0 || !(result = StringArray_New(lines)))
		return (NULL);
	i = 0;
	while (i < length)
	{
		if (i + n < length)
			result[i / n] = String_Sub(str, i, n);
		else
			result[i / n] = String_Duplicate(str + i);
		i += n;
	}
	result[lines] = NULL;
	return (result);
}
