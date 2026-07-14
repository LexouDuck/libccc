
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_utf8*	StringUTF8_Trim(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	start;
	t_size	end;
	t_size	i;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	start = 0;
	while (str[start] && CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + start)))
	{
		charlen = CharUTF8_Length(str + start);
		start += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	end = start;
	i = start;
	while (str[i])
	{
		t_size	prev = i;

		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
		if (!CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + prev)))
			end = i;
	}
	if (start >= end)
		return (StringUTF8_New(0));
	return (StringUTF8_Sub(str, start, end - start));
}



t_utf8*	StringUTF8_Trim_L(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	start;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	start = 0;
	while (str[start] && CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + start)))
	{
		charlen = CharUTF8_Length(str + start);
		start += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (StringUTF8_Sub(str, start, StringUTF8_Length(str + start)));
}



t_utf8*	StringUTF8_Trim_R(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	end;
	t_size	i;
	t_size	prev;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	end = 0;
	i = 0;
	while (str[i])
	{
		prev = i;
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
		if (!CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + prev)))
			end = i;
	}
	return (StringUTF8_Sub(str, 0, end));
}
