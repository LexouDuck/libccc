
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_ascii	CharASCII_ToUppercase(t_ascii c)
{ return (toupper(c)); }
#else
inline
t_ascii	CharASCII_ToUppercase(t_ascii c)
{
	return (('a' <= c && c <= 'z') ? (c - ('a' - 'A')) : c);
}
#endif



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_ascii	CharASCII_ToLowercase(t_ascii c)
{ return (tolower(c)); }
#else
inline
t_ascii	CharASCII_ToLowercase(t_ascii c)
{
	return (('A' <= c && c <= 'Z') ? (c + ('a' - 'A')) : c);
}
#endif
