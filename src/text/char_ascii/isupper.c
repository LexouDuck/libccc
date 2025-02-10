
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharASCII_IsUppercase(t_ascii c)
{ return (isupper(c)); }
#else
_INLINE()
t_bool	CharASCII_IsUppercase(t_ascii c)
{
	return ('A' <= c && c <= 'Z');
}
#endif
