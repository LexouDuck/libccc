
#include "libccc/char.h"
#include "libccc/pointer.h"



#define SURROGATE_HI	0xD800
#define SURROGATE_LO	0xDC00



t_size		Char_ToUTF16(t_utf16* dest, t_utf32 c)
{
	return (0);
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
		result |= (c - SURROGATE_LO) + 0x10000;
		return (result);
	}
	else return ((t_utf32)c);
}
