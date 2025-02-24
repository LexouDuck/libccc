
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharASCII_IsDigit_Decimal(t_ascii c)
{ return (isdigit(c)); }
#else
_INLINE()
t_bool	CharASCII_IsDigit_Decimal(t_ascii c)
{
	return ('0' <= c && c <= '9');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharASCII_IsDigit_Hexadecimal(t_ascii c)
{ return (isxdigit(c)); }
#else
_INLINE()
t_bool	CharASCII_IsDigit_Hexadecimal(t_ascii c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}
#endif



_INLINE()
t_bool	CharASCII_IsDigit_Octal(t_ascii c)
{
	return (('0' <= c && c <= '7'));
}



_INLINE()
t_bool	CharASCII_IsDigit_Binary(t_ascii c)
{
	return (c == '0' || c == '1');
}
