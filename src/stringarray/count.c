
#include "libccc/string.h"
#include "libccc/stringarray.h"



t_u32		StringArray_Count_Char(t_char const** strarr, t_char const c)
{
	t_u32		i;
	t_u32		count;

	LIBCONFIG_HANDLE_NULLPOINTER(0, strarr)
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_Char(strarr[i], c);
		++i;
	}
	return (count);
}



t_u32		StringArray_Count_Charset(t_char const** strarr, t_char const* charset)
{
	t_u32		i;
	t_u32		count;

	LIBCONFIG_HANDLE_NULLPOINTER(0, strarr)
	LIBCONFIG_HANDLE_NULLPOINTER(0, charset)
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_Charset(strarr[i], charset);
		++i;
	}
	return (count);
}



t_u32		StringArray_Count_String(t_char const** strarr, t_char const* query)
{
	t_u32		i;
	t_u32		count;

	LIBCONFIG_HANDLE_NULLPOINTER(0, strarr)
	LIBCONFIG_HANDLE_NULLPOINTER(0, query)
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_String(strarr[i], query);
		++i;
	}
	return (count);
}
