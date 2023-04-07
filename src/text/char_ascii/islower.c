
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharASCII_IsLowercase(t_ascii c)
{ return (islower(c)); }
#else
inline
t_bool	CharASCII_IsLowercase(t_ascii c)
{
	return ('a' <= c && c <= 'z');
}
#endif
