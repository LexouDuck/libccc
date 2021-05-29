
#include "libccc/string.h"
#include "libccc/stringarray.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_u32		StringArray_Count_Char(t_char const** strarr, t_char const c)
{
	t_u32		i;
	t_u32		count;

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
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

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (0);)
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

	HANDLE_ERROR(NULLPOINTER, (strarr == NULL), return (0);)
	HANDLE_ERROR(NULLPOINTER, (query == NULL), return (0);)
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += String_Count_String(strarr[i], query);
		++i;
	}
	return (count);
}
