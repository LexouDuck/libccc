
#include "libccc/char.h"
#include "libccc/pointer.h"



t_size		Char_ToUTF8(t_utf8* dest, t_utf32 c)
{
	return (0);
}



t_utf32		UTF8_Get(t_utf8 const* str)
{
	static const t_u8 MASK = ((1 << 6) - 1);
	t_u8 c;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (ERROR);
#endif
	c = str[0];
	if (c & (1 << 7)) // multi-byte character
	{
		t_utf32 result = 0;
		t_u8 mask;
		if (c & (1 << 6)) // 2-byte character
		{
			if (c & (1 << 5)) // 3-byte character
			{
				if (c & (1 << 4)) // 4-byte character
				{
					if (c & (1 << 3))
						return ((t_utf32)c); // INVALID UTF-8
					mask = ((1 << 3) - 1);
					result |= (c & mask) << (6 * 3);	c = str[1];
					result |= (c & MASK) << (6 * 2);	c = str[2];
					result |= (c & MASK) << (6 * 1);	c = str[3];
					result |= (c & MASK);
					return (result);
				}
				else
				{
					mask = ((1 << 4) - 1);
					result |= (c & mask) << (6 * 2);	c = str[1];
					result |= (c & MASK) << (6 * 1);	c = str[2];
					result |= (c & MASK);
					return (result);
				}
			}
			else
			{
				mask = ((1 << 5) - 1);
				result |= (c & mask) << (6 * 1);	c = str[1];
				result |= (c & MASK);
				return (result);
			}
		}
		else return ((t_utf32)c); // INVALID UTF-8
	}
	else return ((t_utf32)c);
}
