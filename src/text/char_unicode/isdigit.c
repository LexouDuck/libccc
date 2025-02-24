
#include "libccc/text/char_unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharUTF32_IsDigit(t_utf32 c)
{ return (iswdigit(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsDigit(t_utf32 c)
{
	return ('0' <= c && c <= '9');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharUTF32_IsDigit_Hex(t_utf32 c)
{ return (iswxdigit(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsDigit_Hex(t_utf32 c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}
#endif



// TODO UTF handling
t_bool	CharUTF32_IsDigit_Oct(t_utf32 c)
{
	return (('0' <= c && c <= '7'));
}



// TODO UTF handling
t_bool	CharUTF32_IsDigit_Bin(t_utf32 c)
{
	return (c == '0' || c == '1');
}
