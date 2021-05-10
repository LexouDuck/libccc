
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/memory.h"
#include "libccc/pointer.h"



inline t_char*	Size_ToString(t_size number)
{
	return (U64_ToString(number));
}

inline t_char*	Size_ToString_Hex(t_size number)
{
	return (U64_ToString_Hex(number, TRUE));
}

t_char*	Size_ToString_Readable(t_size number)
{
	static const t_char* units[6] = { "B\0", "KB", "MB", "GB", "TB", "PB" };
	t_float len = (t_float)number;
	t_u32 unit = 0;
	while (len >= 1024 && unit < 5)
	{
		unit++;
		len /= 1024;
	}

	t_char*	result;
	t_u8	digits[sizeof(t_size) / 2 * 5];
	t_u8	i;
	t_size	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (t_char*)Memory_Alloc(i + 3)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n++] = units[unit][0];
	result[n++] = units[unit][1];
	result[n] = '\0';
	return (result);
}
