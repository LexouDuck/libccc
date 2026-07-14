
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Join(t_utf8 const** strarr, t_utf8 const* sep)
{
	t_utf8*	result;
	t_size	total;
	t_size	length_sep;
	t_uint	amount;
	t_uint	i;
	t_size	index;
	t_size	j;

	if CCCERROR((strarr == NULL), ERROR_NULLPOINTER, "string array given is NULL")
		return (NULL);
	if CCCERROR((sep == NULL), ERROR_NULLPOINTER, "separator given is NULL")
		return (NULL);
	if (strarr[0] == NULL)
		return (StringUTF8_New(0));
	length_sep = StringUTF8_Length(sep);
	amount = 0;
	total = 0;
	while (strarr[amount])
	{
		total += StringUTF8_Length(strarr[amount]);
		++amount;
		if (strarr[amount])
			total += length_sep;
	}
	result = StringUTF8_New(total);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	index = 0;
	for (i = 0; i < amount; ++i)
	{
		for (j = 0; strarr[i][j]; ++j)
		{
			result[index++] = strarr[i][j];
		}
		if (i + 1 < amount)
		{
			for (j = 0; j < length_sep; ++j)
			{
				result[index++] = sep[j];
			}
		}
	}
	result[index] = '\0';
	return (result);
}
