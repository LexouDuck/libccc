
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/sys/ascii.h"
#include "libccc/pointer.h"



t_bool	ASCII_IsInCharset(t_ascii c, t_ascii const* charset)
{
	t_size	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (TRUE);
		++i;
	}
	return (FALSE);
}
