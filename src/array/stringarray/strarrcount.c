
#include "libccc/string.h"
#include "libccc/array/stringarray.h"



t_u32		c_strarrcount_char(char const** strarr, char const c)
{
	t_u32		i;
	t_u32		count;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL)
		return (0);
#endif
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_Char(strarr[i], c);
		++i;
	}
	return (count);
}



t_u32		c_strarrcount_charset(char const** strarr, char const* cset)
{
	t_u32		i;
	t_u32		count;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || cset == NULL)
		return (0);
#endif
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_Charset(strarr[i], cset);
		++i;
	}
	return (count);
}



t_u32		c_strarrcount_str(char const** strarr, char const* query)
{
	t_u32		i;
	t_u32		count;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (strarr == NULL || query == NULL)
		return (0);
#endif
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_String(strarr[i], query);
		++i;
	}
	return (count);
}
