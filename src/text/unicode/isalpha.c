
#include "libccc/text/unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsUppercase(t_utf32 c)
{ return (iswupper(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsUppercase(t_utf32 c)
{
	return ('A' <= c && c <= 'Z');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsLowercase(t_utf32 c)
{ return (iswlower(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsLowercase(t_utf32 c)
{
	return ('a' <= c && c <= 'z');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsLetter(t_utf32 c)
{ return (iswalpha(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsLetter(t_utf32 c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
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
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}
#endif
