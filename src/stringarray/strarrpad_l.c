
#include "libccc_string.h"
#include "libccc_stringarray.h"



char	**c_strarrpad_l(char const** strarr, char const c, t_u32 n)
{
	char		**result;
	t_u32		strarr_length;
	t_u32		i;

#if LIBCCCCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (NULL);
#endif
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
