
#include "libccc/text/char_unicode.h"
#include "libccc/pointer.h"
#include "libccc/string.h"
#include "libccc/sys/io.h"

#include LIBCONFIG_ERROR_INCLUDE



t_size		CharUTF32_ToUTF16(t_utf16* dest, t_utf32 c)
{
	if CCCERROR((dest == NULL), ERROR_NULLPOINTER, "destination string given is NULL")
		return (0);
	if (c >= UTF16_SURROGATE_HI)
	{
		if CCCERROR((c < UTF16_SURROGATE_END), ERROR_ILLEGALBYTES, 
			"illegal unicode character, code point: "SF_U32, c)
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



t_utf32		CharUTF32_FromUTF16(t_utf16 const* str)
{
	t_u16 c;

	if CCCERROR((str == NULL), ERROR_NULLPOINTER, "string given is NULL")
		return (ERROR);
	c = str[0];
	if (c >= UTF16_SURROGATE_HI)
	{
		t_utf32 result = (c - UTF16_SURROGATE_HI) << 10;
		c = str[1];
		if CCCERROR((c < UTF16_SURROGATE_LO), ERROR_ILLEGALBYTES, 
			"illegal unicode character, code point: "SF_U32, c)
			return (ERROR);
		result |= (c - UTF16_SURROGATE_LO);
		result += UTF16_BIAS;
		return (result);
	}
	else return ((t_utf32)c);
}
