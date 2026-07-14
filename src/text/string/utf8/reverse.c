
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Reverse(t_utf8 const* str)
{
	t_utf8*	result;
	t_size	length;
	t_sint	charlen;
	t_size	i;
	t_size	j;
	t_size	c;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = StringUTF8_Length(str);
	result = (t_utf8*)Memory_Allocate(length + sizeof(""));
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	j = length;
	while (i < length)
	{	// the glyphs are written in reverse order, but the bytes within each glyph stay in order
		charlen = CharUTF8_Length(str + i);
		if (charlen <= 0)
			charlen = 1;
		j -= (t_size)charlen;
		for (c = 0; c < (t_size)charlen; ++c)
		{
			result[j + c] = str[i + c];
		}
		i += (t_size)charlen;
	}
	result[length] = '\0';
	return (result);
}
