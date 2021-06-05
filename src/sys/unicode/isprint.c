
#include "libccc/sys/unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	UTF32_IsSpace(t_utf32 c)
{ return (iswspace(c)); }
#else
// TODO UTF handling
t_bool	UTF32_IsSpace(t_utf32 c)
{
	return ((c == ' ') || ('\t' <= c && c <= '\r'));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	UTF32_IsPunctuation(t_utf32 c)
{ return (iswpunct(c)); }
#else
// TODO UTF handling
t_bool	UTF32_IsPunctuation(t_utf32 c)
{
	return (
		('!' <= c && c <= '/') ||
		(':' <= c && c <= '@') ||
		('[' <= c && c <= '`') ||
		('{' <= c && c <= '~'));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	UTF32_IsPrintable(t_utf32 c)
{ return (iswprint(c)); }
#else
// TODO UTF handling
t_bool	UTF32_IsPrintable(t_utf32 c)
{
	return (!(c < 0x20) &&	// C0 control code char
		!(c == 0x7F) &&	// DEL character
		!(0x80 <= c && c < 0xA0) &&	// C1 control code char
		UTF32_IsValid(c));
}
#endif



inline
t_bool	UTF32_IsASCII(t_utf32 c)
{
	return (c < 0x80);
}



inline
t_bool	UTF32_IsValid(t_utf32 c)
{
	return (c < 0xFDD0 ||
		(c >= 0xFDF0 &&
			((c & 0xFFFF) != 0xFFFF) &&
			((c & 0xFFFE) != 0xFFFE) &&
			c <= UTF8_4BYTE));
}
