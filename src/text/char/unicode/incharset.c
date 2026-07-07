
#include "libccc/bool.h"
#include "libccc/text/char/unicode.h"
#include "libccc/pointer.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	CharUTF8_IsInCharset(t_utf8 const* charset, t_utf32 c)
{
	t_size	i;
	t_sint	size;

	i = 0;
	while (charset[i])
	{
		if (CharUTF32_FromUTF8(charset + i) == c)
			return (TRUE);
		size = CharUTF8_Length(charset + i);
		if (size <= 0)
			return (FALSE);
		i += (t_size)size;
	}
	return (FALSE);
}



t_bool	CharUTF32_IsInCharset(t_utf32 const* charset, t_utf32 c)
{
	t_size	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (TRUE);
		++i;
	}
	return (FALSE);
}
