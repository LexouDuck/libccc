
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringUTF8_Iterate(t_utf8* str, void (*f)(t_utf32 c))
{
	t_size	i;
	t_sint	charlen;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	i = 0;
	while (str[i])
	{
		f(CharUTF32_FromUTF8(str + i));
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
}



void	StringUTF8_Iterate_I(t_utf8* str, void (*f)(t_utf32 c, t_size index))
{
	t_size	i;
	t_sint	charlen;

	if CCCERROR((f == NULL), ERROR_NULLPOINTER, "f() function given is NULL")
		return;
	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	i = 0;
	while (str[i])
	{
		f(CharUTF32_FromUTF8(str + i), i);
		charlen = CharUTF8_Length(str + i);
		i += (charlen <= 0 ? 1 : (t_size)charlen);
	}
}
