
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8**	StringUTF8_Divide(t_utf8 const* str, t_size n)
{
	t_utf8**	result;
	t_uint	chunks;
	t_size	chars;
	t_size	offset;
	t_size	length;
	t_size	count;
	t_sint	charlen;
	t_uint	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "chunk size given is zero")
		return (NULL);
	chars = StringUTF8_Chars(str);
	chunks = (t_uint)(chars / n + (chars % n == 0 ? 0 : 1));
	result = StringArrayUTF8_New(chunks);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	offset = 0;
	for (i = 0; i < chunks; ++i)
	{	// each chunk contains (at most) `n` glyphs
		length = 0;
		count = 0;
		while (str[offset + length] && count < n)
		{
			charlen = CharUTF8_Length(str + offset + length);
			length += (charlen <= 0 ? 1 : (t_size)charlen);
			++count;
		}
		result[i] = StringUTF8_Sub(str, offset, length);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArrayUTF8_Delete(&result);
			return (NULL);
		}
		offset += length;
	}
	result[chunks] = NULL;
	return (result);
}
