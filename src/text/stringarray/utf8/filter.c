
#include "libccc/memory.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Filter(t_utf8 const* const* strarr, t_bool (*filter)(t_utf8 const* str))
{
	t_utf8**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	index;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	if (length == 0)
		return (StringArrayUTF8_New(0));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(strarr[i]);
		if (tmp[i])
			++result_length;
	}
	result = StringArrayUTF8_New(result_length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(tmp);
		return (NULL);
	}
	index = 0;
	for (i = 0; i < length && index < result_length; ++i)
	{
		if (tmp[i])
		{
			result[index++] = StringUTF8_Duplicate(strarr[i]);
		}
	}
	Memory_Free(tmp);
	return (result);
}



t_utf8**	StringArrayUTF8_Filter_I(t_utf8 const* const* strarr, t_bool (*filter)(t_utf8 const* str, t_uint index))
{
	t_utf8**	result;
	t_bool*	tmp;
	t_uint	result_length;
	t_uint	length;
	t_uint	index;
	t_uint	i;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	length = StringArrayUTF8_Length(strarr);
	if (length == 0)
		return (StringArrayUTF8_New(0));
	tmp = (t_bool*)Memory_Allocate(sizeof(t_bool) * length);
	if CCCERROR((tmp == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	result_length = 0;
	for (i = 0; i < length; ++i)
	{
		tmp[i] = filter(strarr[i], i);
		if (tmp[i])
			++result_length;
	}
	result = StringArrayUTF8_New(result_length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
	{
		Memory_Free(tmp);
		return (NULL);
	}
	index = 0;
	for (i = 0; i < length && index < result_length; ++i)
	{
		if (tmp[i])
		{
			result[index++] = StringUTF8_Duplicate(strarr[i]);
		}
	}
	Memory_Free(tmp);
	return (result);
}
