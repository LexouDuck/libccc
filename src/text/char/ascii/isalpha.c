
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharASCII_IsLetter(t_ascii c)
{ return (isalpha(c)); }
#else
_INLINE()
t_bool	CharASCII_IsLetter(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharASCII_IsAlphaNumeric(t_ascii c)
{ return (isalnum(c)); }
#else
_INLINE()
t_bool	CharASCII_IsAlphaNumeric(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}
#endif
