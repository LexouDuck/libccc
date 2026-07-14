
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uint	StringArrayUTF8_Count_Char(t_utf8 const* const* strarr, t_utf32 c)
{
	t_uint	count;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += StringUTF8_Count_Char(strarr[i], c);
		++i;
	}
	return (count);
}



t_uint	StringArrayUTF8_Count_Charset(t_utf8 const* const* strarr, t_utf8 const* cset)
{
	t_uint	count;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	if CCCERROR((cset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (0);
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += StringUTF8_Count_Charset(strarr[i], cset);
		++i;
	}
	return (count);
}



t_uint	StringArrayUTF8_Count_String(t_utf8 const* const* strarr, t_utf8 const* query)
{
	t_uint	count;
	t_uint	i;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (0);
	if CCCERROR((query == NULL), ERROR_NULLPOINTER, "query string given is NULL")
		return (0);
	count = 0;
	i = 0;
	while (strarr[i])
	{
		count += StringUTF8_Count_String(strarr[i], query);
		++i;
	}
	return (count);
}
