
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_char**	StringArray_Pad_L(t_char const** strarr, t_char const c, t_u32 n)
{
	t_char**		result;
	t_u32		strarr_length;
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(strarr, NULL)
	strarr_length = StringArray_Length(strarr);
	if (!(result = StringArray_New(strarr_length)))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = String_Pad_L(strarr[i], c, n);
		if (!result[i])
		{
			StringArray_Delete(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}

// TODO StringArray_Pad_R
// TODO StringArray_Pad
