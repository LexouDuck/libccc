
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_uint	StringUTF8_Split_Charset_GetCount(t_utf8 const* str, t_utf8 const* sep_chars)
{
	t_uint	result;
	t_size	i;
	t_sint	charlen;

	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && CharUTF8_IsInCharset(sep_chars, CharUTF32_FromUTF8(str + i)))
		{
			charlen = CharUTF8_Length(str + i);
			i += (charlen <= 0 ? 1 : (t_size)charlen);
		}
		if (str[i] == '\0')
			break;
		++result;
		while (str[i] && !CharUTF8_IsInCharset(sep_chars, CharUTF32_FromUTF8(str + i)))
		{
			charlen = CharUTF8_Length(str + i);
			i += (charlen <= 0 ? 1 : (t_size)charlen);
		}
	}
	return (result);
}



t_utf8**	StringUTF8_Split_Charset(t_utf8 const* str, t_utf8 const* sep_chars)
{
	t_utf8**	result;
	t_size	offset;
	t_size	length;
	t_uint	count;
	t_sint	charlen;
	t_uint	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to split given is NULL")
		return (NULL);
	if CCCERROR((sep_chars == NULL), ERROR_NULLPOINTER, "separator charset given is NULL")
		return (NULL);
	count = StringUTF8_Split_Charset_GetCount(str, sep_chars);
	result = StringArrayUTF8_New(count);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	offset = 0;
	for (i = 0; i < count; ++i)
	{
		while (str[offset] && CharUTF8_IsInCharset(sep_chars, CharUTF32_FromUTF8(str + offset)))
		{
			charlen = CharUTF8_Length(str + offset);
			offset += (charlen <= 0 ? 1 : (t_size)charlen);
		}
		length = 0;
		while (str[offset + length] && !CharUTF8_IsInCharset(sep_chars, CharUTF32_FromUTF8(str + offset + length)))
		{
			charlen = CharUTF8_Length(str + offset + length);
			length += (charlen <= 0 ? 1 : (t_size)charlen);
		}
		result[i] = StringUTF8_Sub(str, offset, length);
		if CCCERROR((result[i] == NULL), ERROR_ALLOCFAILURE, NULL)
		{
			StringArrayUTF8_Delete(&result);
			return (NULL);
		}
		offset += length;
	}
	result[count] = NULL;
	return (result);
}
