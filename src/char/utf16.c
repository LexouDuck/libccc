
#include "libccc/char.h"
#include "libccc/pointer.h"



#define SURROGATE_HI	0xD800
#define SURROGATE_LO	0xDC00
#define UTF16_BIAS		0x10000



t_size		Char_ToUTF16(t_utf16* dest, t_utf32 c)
{
#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (dest == NULL)
		return (0);
#endif
	if (c >= SURROGATE_HI)
	{
		// if (c < 0xE000) // INVALID UTF-16
		c -= UTF16_BIAS;
		dest[0] = (c >> 10) + SURROGATE_HI;
		dest[1] = (c & ((1 << 10) - 1)) + SURROGATE_LO;
		return (4);
	}
	else
	{
		dest[0] = (t_utf16)c;
		return (2);
	}
}



t_utf32		UTF16_Get(t_utf16 const* str)
{
	t_u16 c;

#if LIBCONFIG_HANDLE_NULLPOINTERS
	if (str == NULL)
		return (ERROR);
#endif
	c = str[0];
	if (c >= SURROGATE_HI)
	{
		t_utf32 result = (c - SURROGATE_HI) << 10;
		c = str[1];
		// if (c < SURROGATE_LO) // INVALID UTF-16
		result |= (c - SURROGATE_LO);
		result += UTF16_BIAS;
		return (result);
	}
	else return ((t_utf32)c);
}
