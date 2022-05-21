
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/memory.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE


t_size CharUTF32_ToEscaped_xFF(t_char *dest, t_utf32 c)
{
	if (c > 0xFF) // TODO: this is dangerous because of signedness
		return ERROR;

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

t_size CharUTF32_ToEscaped_uFFFF(t_char *dest, t_utf32 c)
{
	if (c > 0xFFFF)
		return ERROR;

	if (dest)
	{
		t_u8 nibble0 = (c & 0x000F) >> 0;
		t_u8 nibble1 = (c & 0x00F0) >> 4;
		t_u8 nibble2 = (c & 0x0F00) >> 8;
		t_u8 nibble3 = (c & 0xF000) >> 12;

		dest[0] = '\\';
		dest[1] = 'u';
		dest[2] = (nibble3 < 10) ? (nibble3 + '0') : (nibble3 - 10 + 'A');
		dest[3] = (nibble2 < 10) ? (nibble2 + '0') : (nibble2 - 10 + 'A');
		dest[4] = (nibble1 < 10) ? (nibble1 + '0') : (nibble1 - 10 + 'A');
		dest[5] = (nibble0 < 10) ? (nibble0 + '0') : (nibble0 - 10 + 'A');
	}
	return 6;
}

t_size CharUTF32_ToEscaped_UFFFFFFFF(t_char *dest, t_utf32 c)
{
	if (dest)
	{
		t_u8 nibble0 = (c & 0x0000000F) >> 0;
		t_u8 nibble1 = (c & 0x000000F0) >> 4;
		t_u8 nibble2 = (c & 0x00000F00) >> 8;
		t_u8 nibble3 = (c & 0x0000F000) >> 12;
		t_u8 nibble4 = (c & 0x000F0000) >> 16;
		t_u8 nibble5 = (c & 0x00F00000) >> 20;
		t_u8 nibble6 = (c & 0x0F000000) >> 24;
		t_u8 nibble7 = (c & 0xF0000000) >> 28;

		dest[0] = '\\';
		dest[1] = 'U';
		dest[2] = (nibble7 < 10) ? (nibble7 + '0') : (nibble7 - 10 + 'A');
		dest[3] = (nibble6 < 10) ? (nibble6 + '0') : (nibble6 - 10 + 'A');
		dest[4] = (nibble5 < 10) ? (nibble5 + '0') : (nibble5 - 10 + 'A');
		dest[5] = (nibble4 < 10) ? (nibble4 + '0') : (nibble4 - 10 + 'A');
		dest[6] = (nibble3 < 10) ? (nibble3 + '0') : (nibble3 - 10 + 'A');
		dest[7] = (nibble2 < 10) ? (nibble2 + '0') : (nibble2 - 10 + 'A');
		dest[8] = (nibble1 < 10) ? (nibble1 + '0') : (nibble1 - 10 + 'A');
		dest[9] = (nibble0 < 10) ? (nibble0 + '0') : (nibble0 - 10 + 'A');
	}
	return 10;
}

t_size CharUTF32_ToEscaped_smart(t_char *dest, t_utf32 c)
{
	if (c <= 0xFF)
		return CharUTF32_ToEscaped_xFF(dest, c);
	else if (c <= 0xFFFF)
		return CharUTF32_ToEscaped_uFFFF(dest, c);
	else
		return CharUTF32_ToEscaped_UFFFFFFFF(dest, c);
}

