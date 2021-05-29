
#include "libccc/memory.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_char**	StringArray_Sub(t_char const** strarr, t_u32 start, t_u32 n)
{
	t_char**		result;
	t_u32		length;
	t_u32		i;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (NULL);)
	length = StringArray_Length(strarr);
	if (start > length || start + n > length)
		return (NULL);
	if (!(result = StringArray_New(n)))
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (!(result[i] = String_Duplicate(strarr[start + i])))
		{
			StringArray_Delete(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}
