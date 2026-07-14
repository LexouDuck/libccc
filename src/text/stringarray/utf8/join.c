
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_Join(t_utf8 const* const* * strarrs, t_utf8 const* const* sep)
{
	t_utf8**	result;
	t_uint	total;
	t_uint	length_strarrs;
	t_uint	length_sep;
	t_uint	index;
	t_uint	i;
	t_uint	j;

	if CCCERROR((strarrs == NULL), ERROR_NULLPOINTER, "array of string arrays given is NULL")
		return (NULL);
	if CCCERROR((sep == NULL), ERROR_NULLPOINTER, "string array separator given is NULL")
		return (NULL);
	if (strarrs[0] == NULL)
		return (StringArrayUTF8_New(0));
	total = 0;
	length_sep = StringArrayUTF8_Length(sep);
	length_strarrs = 0;
	while (strarrs[length_strarrs])
	{
		total += StringArrayUTF8_Length(strarrs[length_strarrs]);
		++length_strarrs;
		if (strarrs[length_strarrs])
			total += length_sep;
	}
	result = StringArrayUTF8_New(total);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	index = 0;
	for (i = 0; i < length_strarrs; ++i)
	{
		for (j = 0; strarrs[i][j]; ++j)
		{
			result[index++] = StringUTF8_Duplicate(strarrs[i][j]);
		}
		if (index == total)
			break;
		for (j = 0; j < length_sep; ++j)
		{
			result[index++] = StringUTF8_Duplicate(sep[j]);
		}
	}
	return (result);
}
