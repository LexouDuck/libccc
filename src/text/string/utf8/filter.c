
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Filter(t_utf8 const* str, t_bool (*filter)(t_utf32 c))
{
	t_utf8*	result;
	t_size	written;
	t_size	i;
	t_size	j;
	t_size	charlen;
	t_sint	length;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	result = (t_utf8*)Memory_Allocate(StringUTF8_Length(str) + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	written = 0;
	i = 0;
	while (str[i])
	{
		length = CharUTF8_Length(str + i);
		charlen = (length <= 0 ? 1 : (t_size)length);
		if (filter(CharUTF32_FromUTF8(str + i)))
		{
			for (j = 0; j < charlen; ++j)
				result[written++] = str[i + j];
		}
		i += charlen;
	}
	result[written] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Filter_I(t_utf8 const* str, t_bool (*filter)(t_utf32 c, t_size index))
{
	t_utf8*	result;
	t_size	written;
	t_size	i;
	t_size	j;
	t_size	charlen;
	t_sint	length;

	if CCCERROR((filter == NULL), ERROR_NULLPOINTER, "filter() function given is NULL")
		return (NULL);
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	result = (t_utf8*)Memory_Allocate(StringUTF8_Length(str) + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	written = 0;
	i = 0;
	while (str[i])
	{
		length = CharUTF8_Length(str + i);
		charlen = (length <= 0 ? 1 : (t_size)length);
		if (filter(CharUTF32_FromUTF8(str + i), i))
		{
			for (j = 0; j < charlen; ++j)
				result[written++] = str[i + j];
		}
		i += charlen;
	}
	result[written] = '\0';
	return (result);
}
