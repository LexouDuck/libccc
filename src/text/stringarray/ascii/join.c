
#include "libccc/memory.h"
#include "libccc/text/string/ascii.h"
#include "libccc/text/stringarray/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char**	StringArrayASCII_Join(t_char const* const* * strarrs, t_char const* const* sep)
{
	t_char**	result;
	t_uint	total;
	t_uint	length_strarrs;
	t_uint	length_sep;
	t_uint	index;

	if CCCERROR((strarrs == NULL), ERROR_NULLPOINTER, "array of string arrays given is NULL")
		return (NULL);
	if CCCERROR((sep == NULL), ERROR_NULLPOINTER, "string array separator given is NULL")
		return (NULL);
	if (strarrs[0] == NULL)
		return (StringArrayASCII_New(0));
	total = 0;
	length_sep = StringArrayASCII_Length(sep);
	length_strarrs = 0;
	while (strarrs[length_strarrs])
	{
		total += StringArrayASCII_Length(strarrs[length_strarrs]);
		++length_strarrs;
		if (strarrs[length_strarrs])
			total += length_sep;
	}
	result = StringArrayASCII_New(total);
	index = 0;
	for (t_uint i = 0; i < length_strarrs; ++i)
	{
		for (t_uint j = 0; strarrs[i][j]; ++j)
		{
			result[index++] = StringASCII_Duplicate(strarrs[i][j]);
		}
		if (index == total)
			break;
		for (t_uint j = 0; j < length_sep; ++j)
		{
			result[index++] = StringASCII_Duplicate(sep[j]);
		}
	}
	return (result);
}
