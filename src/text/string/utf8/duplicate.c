
#include "libccc/memory.h"
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Duplicate(t_utf8 const* str)
{
	t_utf8*	result;
	t_size	length;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
	{
		++length;
	}
	result = StringUTF8_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Duplicate_N(t_utf8 const* str, t_size n)
{
	t_utf8*	result;
	t_size	length;
	t_sint	charlen;
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length] && length < n)
	{	// only copy whole multi-byte sequences: stop before any glyph which would be cut by the `n` bytes limit
		charlen = CharUTF8_Length(str + length);
		if (charlen <= 0)
			charlen = 1;
		if (length + (t_size)charlen > n)
			break;
		length += (t_size)charlen;
	}
	result = StringUTF8_New(length);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}



t_utf8*	StringUTF8_Duplicate_Char(t_utf8 const* str, t_utf32 c)
{
	t_size	length;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
	{
		if (CharUTF32_FromUTF8(str + length) == c)
			break;
		charlen = CharUTF8_Length(str + length);
		length += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (StringUTF8_Duplicate_N(str, length));
}



t_utf8*	StringUTF8_Duplicate_Charset(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	length;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (NULL);
	length = 0;
	while (str[length])
	{
		if (CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + length)))
			break;
		charlen = CharUTF8_Length(str + length);
		length += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (StringUTF8_Duplicate_N(str, length));
}




//! Like StringUTF8_IndexOf_String(), but does not log an error when the query is not found
static
t_sintmax	StringUTF8_Duplicate_IndexOf(t_utf8 const* str, t_utf8 const* query)
{
	t_size	i;
	t_size	j;

	if (query[0] == '\0')
		return (ERROR);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (query[j] == str[i + j])
		{
			++j;
			if (query[j] == '\0')
				return ((t_sintmax)i);
			if (str[i + j] == '\0')
				return (ERROR);
		}
		++i;
	}
	return (ERROR);
}



t_utf8*	StringUTF8_Duplicate_String(t_utf8 const* str, t_utf8 const* target)
{
	t_sintmax	index;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((target == NULL), ERROR_NULLPOINTER, "target string given is NULL")
		return (NULL);
	index = StringUTF8_Duplicate_IndexOf(str, target);
	if (index < 0)
		return (StringUTF8_Duplicate(str));
	return (StringUTF8_Duplicate_N(str, (t_size)index));
}
