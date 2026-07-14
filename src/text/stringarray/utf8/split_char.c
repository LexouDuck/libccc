
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"
#include "libccc/text/stringarray/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



static
t_uint	StringUTF8_Split_Char_GetCount(t_utf8 const* str, t_utf32 sep)
{
	t_uint	result;
	t_size	i;
	t_sint	charlen;

	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && CharUTF32_FromUTF8(str + i) == sep)
		{
			charlen = CharUTF8_Length(str + i);
			i += (charlen <= 0 ? 1 : (t_size)charlen);
		}
		if (str[i] == '\0')
			break;
		++result;
		while (str[i] && CharUTF32_FromUTF8(str + i) != sep)
		{
			charlen = CharUTF8_Length(str + i);
			i += (charlen <= 0 ? 1 : (t_size)charlen);
		}
	}
	return (result);
}



t_utf8**	StringUTF8_Split_Char(t_utf8 const* str, t_utf32 sep)
{
	t_utf8**	result;
	t_size	offset;
	t_size	length;
	t_uint	count;
	t_sint	charlen;
	t_uint	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string to split given is NULL")
		return (NULL);
	count = StringUTF8_Split_Char_GetCount(str, sep);
	result = StringArrayUTF8_New(count);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	offset = 0;
	for (i = 0; i < count; ++i)
	{
		while (str[offset] && CharUTF32_FromUTF8(str + offset) == sep)
		{
			charlen = CharUTF8_Length(str + offset);
			offset += (charlen <= 0 ? 1 : (t_size)charlen);
		}
		length = 0;
		while (str[offset + length] && CharUTF32_FromUTF8(str + offset + length) != sep)
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
