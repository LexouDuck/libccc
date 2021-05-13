
#include "libccc/bool.h"
#include "libccc/char.h"



inline
t_bool	ASCII_IsSpace(t_ascii c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}



inline
t_bool	ASCII_IsPunctuation(t_ascii c)
{
	return (
		('!' <= c && c <= '/') ||
		(':' <= c && c <= '@') ||
		('[' <= c && c <= '`') ||
		('{' <= c && c <= '~'));
}



inline
t_bool	ASCII_IsPrintable(t_ascii c)
{
	return (!(c < 0x20) &&	// C0 control code char
		!(c == 0x7F) &&	// DEL character
#if (CHAR_MIN == SCHAR_MIN && CHAR_MAX == SCHAR_MAX)
		!(c < (t_ascii)0xA0) &&	// C1 control code char
#else
		!(0x80 <= c && c < 0xA0) &&	// C1 control code char
#endif
		ASCII_IsValid(c));
}



inline
t_bool	ASCII_IsValid(t_ascii c)
{
#if (CHAR_MIN == SCHAR_MIN && CHAR_MAX == SCHAR_MAX)
	return (0 <= c);
#else
	return (0 <= c && c < 0x80);
#endif
}
