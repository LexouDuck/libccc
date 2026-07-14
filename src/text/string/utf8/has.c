
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	StringUTF8_Has(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	i;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (FALSE);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + i)))
			return (TRUE);
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (FALSE);
}



t_bool	StringUTF8_HasOnly(t_utf8 const* str, t_utf8 const* charset)
{
	t_size	i;
	t_sint	charlen;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (FALSE);
	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset given is NULL")
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (!CharUTF8_IsInCharset(charset, CharUTF32_FromUTF8(str + i)))
			return (FALSE);
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
	return (TRUE);
}
