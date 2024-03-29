
#include "libccc/char.h"
#include "libccc/text/string_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*		String_Trim(t_ascii const* str, t_ascii const* charset)
{
	t_size	offset;
	t_size	length;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	offset = 0;
	length = 0;
	while (str[length])
	{
		++length;
	}
	while (offset < length && Char_IsInCharset(str[offset], charset))
	{
		++offset;
	}
	if (offset == length)
		return (String_New(0));
	length -= 1;
	while (length > offset && Char_IsInCharset(str[length], charset))
	{
		--length;
	}
	length -= offset - 1;
	return (String_Sub(str, offset, length));
}

t_ascii*		String_Trim_L(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (Char_IsInCharset(str[i], charset))
			++i;
		else
			break;
	}
	return (String_Sub(str, i, String_Length(str + i)));
}



t_ascii*		String_Trim_R(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	i = String_Length(str);
	while (i--)
	{
		if (!Char_IsInCharset(str[i], charset))
			break;
	}
	if (i || !Char_IsInCharset(str[i], charset))
		++i;
	return (String_Sub(str, 0, i));
}
