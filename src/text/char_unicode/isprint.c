
#include "libccc/text/char_ascii.h"
#include "libccc/text/char_unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharUTF32_IsSpace(t_utf32 c)
{ return (iswspace(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsSpace(t_utf32 c)
{
	if (c == ' ')					return (TRUE);
	if ('\t' <= c && c <= '\r')		return (TRUE);
	if (c == 0x0085)				return (TRUE); // 
	if (c == 0x00A0)				return (TRUE); //  
	if (c == 0x1680)				return (TRUE); //  
	if (0x2000 <= c && c < 0x200C)	return (TRUE); // ​
	if (c == 0x2028)				return (TRUE); //  
	if (c == 0x2029)				return (TRUE); //  
	if (c == 0x202F)				return (TRUE); //  
	if (c == 0x205F)				return (TRUE); //  
	if (c == 0x3000)				return (TRUE); // 　
	return (FALSE);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharUTF32_IsPrintable(t_utf32 c)
{ return (iswprint(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsPrintable(t_utf32 c)
{
	return (!(c < 0x20) // C0 control code char
		&& !(c == 0x7F) // DEL character
		&& !(0x80 <= c && c < 0xA0) // C1 control code char
		&& CharUTF32_IsValid(c) // NOTE: this is different from the standard iswprint(), which returns 0 for every unicode char
	);
}
#endif



_INLINE()
t_bool	CharUTF32_IsASCII(t_utf32 c)
{
	return (c < 0x80);
}



_INLINE()
t_bool	CharUTF32_IsValid(t_utf32 c)
{
	return (c < 0xFDD0 ||
		(c >= 0xFDF0 &&
			((c & 0xFFFF) != 0xFFFF) &&
			((c & 0xFFFE) != 0xFFFE) &&
			c <= UTF8_4BYTE));
}
