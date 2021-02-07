
#include "libccc/char.h"
#include "libccc/pointer.h"



#define MASK	((1 << 6) - 1)



t_size		Char_ToUTF8(t_utf8* dest, t_utf32 c)
{
	t_u8 mask;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (0);
#endif
	if (c < 0x80)
	{
		dest[0] = (t_u8)c;
		return (1);
	}
	else if (c < 0x800)
	{
		mask = ((1 << 5) - 1);
		dest[0] = (mask & (c >> (6 * 1))) | 0xC0;
		dest[1] = (MASK & (c >> (6 * 0))) | 0x80;
		return (2);
	}
	else if (c < 0x10000)
	{
		mask = ((1 << 4) - 1);
		dest[0] = (mask & (c >> (6 * 2))) | 0xE0;
		dest[1] = (MASK & (c >> (6 * 1))) | 0x80;
		dest[2] = (MASK & (c >> (6 * 0))) | 0x80;
		return (3);
	}
	else if (c < 0x10FFFF)
	{
		mask = ((1 << 3) - 1);
		dest[0] = (mask & (c >> (6 * 3))) | 0xF0;
		dest[1] = (MASK & (c >> (6 * 2))) | 0x80;
		dest[2] = (MASK & (c >> (6 * 1))) | 0x80;
		dest[3] = (MASK & (c >> (6 * 0))) | 0x80;
		return (4);
	}
	else return (0); // INVALID UTF-8
}



t_utf32		UTF8_Get(t_utf8 const* str)
{
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
