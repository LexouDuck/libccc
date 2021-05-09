
#include "libccc/char.h"



inline
t_bool	Char_IsSpace(t_utf32 c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}



inline
t_bool	Char_IsPunctuation(t_utf32 c)
{
	return (
		('!' <= c && c <= '/') ||
		(':' <= c && c <= '@') ||
		('[' <= c && c <= '`') ||
		('{' <= c && c <= '~'));
}



inline
t_bool	Char_IsPrintable(t_utf32 c)
{
	return (!(c < 0x20) &&	// C0 control code char
		!(c == 0x7F) &&	// DEL character
		!(0x80 <= c && c < 0xA0) &&	// C1 control code char
		Char_IsValid(c));
}



inline
t_bool	Char_IsASCII(t_utf32 c)
{
	return (c < 0x80);
}



inline
t_bool	Char_IsValid(t_utf32 c)
{
	return (c < 0xFDD0 ||
		(c >= 0xFDF0 &&
			((c & 0xFFFF) != 0xFFFF) &&
			((c & 0xFFFE) != 0xFFFE) &&
			c <= UTF8_4BYTE));
}
