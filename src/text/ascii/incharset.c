
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/text/ascii.h"
#include "libccc/pointer.h"

#include LIBCONFIG_ERROR_INCLUDE



t_bool	CharASCII_IsInCharset(t_ascii c, t_ascii const* charset)
{
	t_size	i;

	if CCCERROR((charset == NULL), ERROR_NULLPOINTER, "charset string given is NULL")
		return (FALSE);
	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (TRUE);
		++i;
	}
	return (FALSE);
}
