#include "libccc/text/char_ascii.h"

#include LIBCONFIG_ERROR_INCLUDE


t_size CharASCII_ToEscaped_xFF(t_ascii *dest, t_ascii c)
{
	if (dest)
	{
		t_u8 nibble0 = (c & 0x0F) >> 0;
		t_u8 nibble1 = (c & 0xF0) >> 4;

		dest[0] = '\\';
		dest[1] = 'x';
		dest[2] = (nibble1 < 10) ? (nibble1 + '0') : (nibble1 - 10 + 'A');
		dest[3] = (nibble0 < 10) ? (nibble0 + '0') : (nibble0 - 10 + 'A');
	}
	return 4;
}
