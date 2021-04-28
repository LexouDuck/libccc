
#include "libccc/char.h"



inline
t_bool	Char_IsSpace(t_utf32 c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}



inline
t_bool	Char_IsPunctuation(t_utf32 c)
{
	return (('!' <= c && c <= '/') ||
			(':' <= c && c <= '@') ||
			('[' <= c && c <= '`') ||
			('{' <= c && c <= '~'));
}



inline
t_bool	Char_IsPrintable(t_utf32 c)
{
	return ('\x20' <= c &&
		!(0x7F <= c && c <= 0xFF));
}



inline
t_bool	Char_IsASCII(t_utf32 c)
{
	return (c < 0x80);
}
