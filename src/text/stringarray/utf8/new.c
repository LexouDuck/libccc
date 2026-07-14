
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringArrayUTF8_New(t_uint length)
{
	t_utf8**	result;

	result = (t_utf8**)Memory_New(sizeof(t_utf8*) * (length + 1));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	return (result);
}



t_utf8**	StringArrayUTF8_New_C(t_uint n, t_size length, t_utf32 c)
{
	t_utf8**	result;
	t_utf8	encoded[4];
	t_size	charlen;
	t_uint	i;
	t_size	j;
	t_size	b;

	charlen = CharUTF32_ToUTF8(encoded, c);
	if CCCERROR((charlen == 0), ERROR_INVALIDARGS,
		"fill character given is not a valid unicode code point")
		return (NULL);
	result = StringArrayUTF8_New(n);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = StringUTF8_New(length * charlen);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArrayUTF8_Delete(&result);
			return (NULL);
		}
		for (j = 0; j < length; ++j)
		{
			for (b = 0; b < charlen; ++b)
				result[i][j * charlen + b] = encoded[b];
		}
		result[i][length * charlen] = '\0';
		++i;
	}
	result[n] = NULL;
	return (result);
}
