
#include "libccc/sys/unicode.h"
#include "libccc/pointer.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"



t_size		UTF32_ToUTF16(t_utf16* dest, t_utf32 c)
{
	LIBCONFIG_HANDLE_NULLPOINTER(0, dest)
	if (c >= UTF16_SURROGATE_HI)
	{
		if (c < UTF16_SURROGATE_END) // INVALID UTF-16
			return (ERROR);
		c -= UTF16_BIAS;
		dest[0] = (c >> 10) + UTF16_SURROGATE_HI;
		dest[1] = (c & ((1 << 10) - 1)) + UTF16_SURROGATE_LO;
		return (4);
	}
	else
	{
		dest[0] = (t_utf16)c;
		return (2);
	}
}



t_utf32		UTF32_FromUTF16(t_utf16 const* str)
{
	t_u16 c;

	LIBCONFIG_HANDLE_NULLPOINTER(ERROR, str)
	c = str[0];
	if (c >= UTF16_SURROGATE_HI)
	{
		t_utf32 result = (c - UTF16_SURROGATE_HI) << 10;
		c = str[1];
		if (c < UTF16_SURROGATE_LO) // INVALID UTF-16
			return (ERROR);
		result |= (c - UTF16_SURROGATE_LO);
		result += UTF16_BIAS;
		return (result);
	}
	else return ((t_utf32)c);
}
