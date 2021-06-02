
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_HANDLE_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	ASCII_IsUppercase(t_ascii c)
{ return (isupper(c)); }
#else
inline
t_bool	ASCII_IsUppercase(t_ascii c)
{
	return ('A' <= c && c <= 'Z');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	ASCII_IsLowercase(t_ascii c)
{ return (islower(c)); }
#else
inline
t_bool	ASCII_IsLowercase(t_ascii c)
{
	return ('a' <= c && c <= 'z');
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	ASCII_IsLetter(t_ascii c)
{ return (isalpha(c)); }
#else
inline
t_bool	ASCII_IsLetter(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z'));
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	ASCII_IsAlphaNumeric(t_ascii c)
{ return (isalnum(c)); }
#else
inline
t_bool	ASCII_IsAlphaNumeric(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ||
			('a' <= c && c <= 'z') ||
			('0' <= c && c <= '9'));
}
#endif
