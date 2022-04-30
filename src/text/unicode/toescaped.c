
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/stringarray.h"
#include "libccc/memory.h"
#include "libccc/math.h"

#include LIBCONFIG_ERROR_INCLUDE


t_size UTF32_ToEscaped_xFF(t_char *dest, t_utf32 c)
{
	if (c > 0xFF)
		return ERROR;

	if (dest)
	{
		t_u8 hexa0 = (c & 0x0F) >> 0;
		t_u8 hexa1 = (c & 0xF0) >> 4;

		dest[0] = '\\';
		dest[1] = 'x';
		dest[2] = (hexa1 < 10) ? (hexa1 + '0') : (hexa1 - 10 + 'A');
		dest[3] = (hexa0 < 10) ? (hexa0 + '0') : (hexa0 - 10 + 'A');
	}
	return 4;
}

t_size UTF32_ToEscaped_uFFFF(t_char *dest, t_utf32 c)
{
	if (c > 0xFFFF)
		return ERROR;

	if (dest)
	{
		t_u8 hexa0 = (c & 0x000F) >> 0;
		t_u8 hexa1 = (c & 0x00F0) >> 4;
		t_u8 hexa2 = (c & 0x0F00) >> 8;
		t_u8 hexa3 = (c & 0xF000) >> 12;

		dest[0] = '\\';
		dest[1] = 'u';
		dest[2] = (hexa3 < 10) ? (hexa3 + '0') : (hexa3 - 10 + 'A');
		dest[3] = (hexa2 < 10) ? (hexa2 + '0') : (hexa2 - 10 + 'A');
		dest[4] = (hexa1 < 10) ? (hexa1 + '0') : (hexa1 - 10 + 'A');
		dest[5] = (hexa0 < 10) ? (hexa0 + '0') : (hexa0 - 10 + 'A');
	}
	return 6;
}

t_size UTF32_ToEscaped_UFFFFFFFF(t_char *dest, t_utf32 c)
{
	if (dest)
	{
		t_u8 hexa0 = (c & 0x0000000F) >> 0;
		t_u8 hexa1 = (c & 0x000000F0) >> 4;
		t_u8 hexa2 = (c & 0x00000F00) >> 8;
		t_u8 hexa3 = (c & 0x0000F000) >> 12;
		t_u8 hexa4 = (c & 0x000F0000) >> 16;
		t_u8 hexa5 = (c & 0x00F00000) >> 20;
		t_u8 hexa6 = (c & 0x0F000000) >> 24;
		t_u8 hexa7 = (c & 0xF0000000) >> 28;

		dest[0] = '\\';
		dest[1] = 'U';
		dest[2] = (hexa7 < 10) ? (hexa7 + '0') : (hexa7 - 10 + 'A');
		dest[3] = (hexa6 < 10) ? (hexa6 + '0') : (hexa6 - 10 + 'A');
		dest[4] = (hexa5 < 10) ? (hexa5 + '0') : (hexa5 - 10 + 'A');
		dest[5] = (hexa4 < 10) ? (hexa4 + '0') : (hexa4 - 10 + 'A');
		dest[6] = (hexa3 < 10) ? (hexa3 + '0') : (hexa3 - 10 + 'A');
		dest[7] = (hexa2 < 10) ? (hexa2 + '0') : (hexa2 - 10 + 'A');
		dest[8] = (hexa1 < 10) ? (hexa1 + '0') : (hexa1 - 10 + 'A');
		dest[9] = (hexa0 < 10) ? (hexa0 + '0') : (hexa0 - 10 + 'A');
	}
	return 10;
}

t_size UTF32_ToEscaped_smart(t_char *dest, t_utf32 c)
{
	if (c <= 0xFF)
		return UTF32_ToEscaped_xFF(dest, c);
	else if (c <= 0xFFFF)
		return UTF32_ToEscaped_uFFFF(dest, c);
	else
		return UTF32_ToEscaped_UFFFFFFFF(dest, c);
}

