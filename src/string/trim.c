
#include "libccc/char.h"
#include "libccc/string.h"

#include LIBCONFIG_ERROR_INCLUDE



t_char*		String_Trim(t_char const* str, t_char const* charset)
{
	t_size	offset;
	t_size	length;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (NULL);)
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

t_char*		String_Trim_L(t_char const* str, t_char const* charset)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (NULL);)
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



t_char*		String_Trim_R(t_char const* str, t_char const* charset)
{
	t_size	i;

	HANDLE_ERROR(NULLPOINTER, (str == NULL), return (NULL);)
	HANDLE_ERROR(NULLPOINTER, (charset == NULL), return (NULL);)
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
