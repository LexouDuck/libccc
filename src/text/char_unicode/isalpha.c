
#include "libccc/text/char_unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsLetter(t_utf32 c)
{ return (iswalpha(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsLetter(t_utf32 c)
{
	return (CharUTF32_IsLowercase(c) ||
			CharUTF32_IsUppercase(c));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
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
