
#include "libccc/bool.h"
#include "libccc/sys/unicode.h"
#include "libccc/pointer.h"



t_bool	UTF32_IsInCharset(t_utf32 c, t_utf32 const* charset)
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
