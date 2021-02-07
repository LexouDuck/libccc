
#include "libccc/bool.h"
#include "libccc/char.h"
#include "libccc/pointer.h"



t_bool	Char_IsInCharset(t_utf32 c, t_char const* charset)
{
	t_size	i = 0;
	while (charset[i])
	{
		if ((t_char)c == charset[i])
			return (TRUE);
		++i;
	}
	return (FALSE);
}
