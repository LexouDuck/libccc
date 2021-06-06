
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	ASCII_IsDigit_Dec(t_ascii c)
{ return (isdigit(c)); }
#else
inline
t_bool	ASCII_IsDigit_Dec(t_ascii c)
{
	return ('0' <= c && c <= '9');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	ASCII_IsDigit_Hex(t_ascii c)
{ return (isxdigit(c)); }
#else
inline
t_bool	ASCII_IsDigit_Hex(t_ascii c)
{
	return (('0' <= c && c <= '9') ||
			('A' <= c && c <= 'F') ||
			('a' <= c && c <= 'f'));
}
#endif



inline
t_bool	ASCII_IsDigit_Oct(t_ascii c)
{
	return (('0' <= c && c <= '7'));
}



inline
t_bool	ASCII_IsDigit_Bin(t_ascii c)
{
	return (c == '0' || c == '1');
}
