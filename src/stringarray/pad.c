
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_char**	StringArray_Pad_L(t_char const** strarr, t_char const c, t_u32 n)
{
	t_char**		result;
	t_u32		strarr_length;
	t_u32		i;

	LIBCONFIG_HANDLE_NULLPOINTER(strarr, NULL)
	strarr_length = c_strarrlen(strarr);
	if (!(result = c_strarrnew(strarr_length)))
		return (NULL);
	i = 0;
	while (strarr[i])
	{
		result[i] = c_strpad_l(strarr[i], c, n);
		if (!result[i])
		{
			c_strarrdel(&result);
			return (NULL);
		}
		++i;
	}
	result[i] = NULL;
	return (result);
}

// TODO StringArray_Pad_R
// TODO StringArray_Pad
