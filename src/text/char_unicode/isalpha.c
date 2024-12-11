
#include "libccc/text/char_unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_bool	CharUTF32_IsLetter(t_utf32 c)
{ return (iswalpha(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsLetter(t_utf32 c)
{
	if (c == 0x01C5)				return (TRUE); // ǅ
	if (c == 0x01C8)				return (TRUE); // ǈ
	if (c == 0x01CB)				return (TRUE); // ǋ
	if (c == 0x01F2)				return (TRUE); // ǲ
	if (c == 0x04F6)				return (FALSE); // Ӷ
	if (c == 0x04F7)				return (FALSE); // ӷ
	if (0x1F88 <= c && c < 0x1FB0)	return (TRUE);
	if (c == 0x1FBC)				return (TRUE); // ᾼ
	if (c == 0x1FCC)				return (TRUE); // ῌ
	if (c == 0x1FFC)				return (TRUE); // ῼ
	return (CharUTF32_IsLowercase(c) ||
			CharUTF32_IsUppercase(c));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
extern inline
t_bool	CharUTF32_IsAlphaNumeric(t_utf32 c)
{ return (iswalnum(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsAlphaNumeric(t_utf32 c)
{
	return (CharUTF32_IsLetter(c) ||
			CharUTF32_IsDigit(c));
}
#endif
