
#include "libccc/char.h"



inline t_bool	Char_IsSpace(t_utf32 c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}



inline t_bool	Char_IsPunctuation(t_utf32 c)
{
	return (('!' <= c && c <= '/') ||
			(':' <= c && c <= '@') ||
			('[' <= c && c <= '`') ||
			('{' <= c && c <= '~'));
}



inline t_bool	Char_IsPrintable(t_utf32 c)
{
	return (0x20 <= c && c <= 0x7E);
}



inline t_bool	Char_IsASCII(t_utf32 c)
{
	return (0x00 <= c && c <= 0x7F);
}
