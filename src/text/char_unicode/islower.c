
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsLowercase(t_utf32 c)
{ return (iswlower(c)); }
#else
inline
t_bool	CharUTF32_IsLowercase(t_utf32 c)
{
	return (
		('a' <= c && c <= 'z')
		|| (c == 0x00AA)
		|| (c == 0x00B5)
		|| (c == 0x00BA)
	);
}
#endif
