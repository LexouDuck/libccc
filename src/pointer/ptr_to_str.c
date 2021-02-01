
#include "libccc/int.h"
#include "libccc/float.h"
#include "libccc/memory.h"



char*	Convert_Pointer_To_String(void const* ptr)
{
	char*	result;
	t_u8	digits[16];
	t_u8	i;
	t_size	n;

	n = (t_size)ptr;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 16;
		n /= 16;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char*)Memory_Alloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);
	result[n] = '\0';
	return (result);
}



char*	Convert_Size_To_String_Readable(t_size number)
{
	static const char* units[6] = { "B\0", "KB", "MB", "GB", "TB", "PB" };
	t_float len = (t_float)number;
	t_u32 unit = 0;
	while (len >= 1024 && unit < 5)
	{
		unit++;
		len /= 1024;
	}

	char	*result;
	t_u8	digits[MAXDIGIT_64BIT];
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
	if (!(result = (char*)Memory_Alloc(i + 3)))
		return (NULL);
	n = 0;
	while (i--)
		result[n++] = '0' + digits[i];
	result[n++] = units[unit][0];
	result[n++] = units[unit][1];
	result[n] = '\0';
	return (result);
}
