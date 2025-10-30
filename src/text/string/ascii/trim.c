
#include "libccc/char.h"
#include "libccc/text/string/ascii.h"

#include LIBCONFIG_ERROR_INCLUDE



t_ascii*		StringASCII_Trim(t_ascii const* str, t_ascii const* charset)
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
	while (offset < length && CharASCII_IsInCharset(str[offset], charset))
	{
		++offset;
	}
	if (offset == length)
		return (StringASCII_New(0));
	length -= 1;
	while (length > offset && CharASCII_IsInCharset(str[length], charset))
	{
		--length;
	}
	length -= offset - 1;
	return (StringASCII_Sub(str, offset, length));
}

t_ascii*		StringASCII_Trim_L(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (CharASCII_IsInCharset(str[i], charset))
			++i;
		else
			break;
	}
	return (StringASCII_Sub(str, i, StringASCII_Length(str + i)));
}



t_ascii*		StringASCII_Trim_R(t_ascii const* str, t_ascii const* charset)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (NULL);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "trim charset given is NULL")
		return (NULL);
	i = StringASCII_Length(str);
	while (i--)
	{
		if (!CharASCII_IsInCharset(str[i], charset))
			break;
	}
	if (i || !CharASCII_IsInCharset(str[i], charset))
		++i;
	return (StringASCII_Sub(str, 0, i));
}
