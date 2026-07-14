
#include "libccc/text/char/unicode.h"
#include "libccc/text/string/utf8.h"

#include LIBCONFIG_ERROR_INCLUDE



void	StringUTF8_SetBytes(t_utf8* str, t_utf8 c)
{
	t_size	i;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	i = 0;
	while (str[i])
	{
		str[i] = c;
		++i;
	}
}



void	StringUTF8_SetChars(t_utf8* str, t_utf8 c)
{
	t_size	read;
	t_size	write;
	t_sint	length;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return;
	read = 0;
	write = 0;
	while (str[read])
	{
		length = CharUTF8_Length(str + read);
		read += (length <= 0 ? 1 : (t_size)length);
		str[write++] = c;
	}
	str[write] = '\0';
}
