
#include <ctype.h>
#include <math.h>

#include "libccc/math/math.h"
#include "libccc/sys/time.h"

#include "test.h"



int	bool_equals(int a, int b)
{
	return (a == 0) ? (b == 0) : (b != 0);
}



int	str_equals(char const* str1, char const* str2)
{
	size_t i;

	if (str1 == str2)
		return (TRUE);
	if (str1 && str2)
	{
		i = 0;
		while (str1[i] && str2[i])
		{
			if (str1[i] != str2[i])
				return (FALSE);
			++i;
		}
		return (str1[i] == str2[i]);
	}
	return (FALSE);
}



int str_equals_until(char const* str1, char const* str2, char c)
{
	size_t i;

	if (str1 == str2)
		return (TRUE);
	if (str1 && str2)
	{
		i = 0;
		while (
			str1[i] && str1[i] != c &&
			str2[i] && str2[i] != c)
		{
			if (str1[i] != str2[i])
				return (FALSE);
			++i;
		}
		if (str1[i] == c ||
			str2[i] == c)
			return (TRUE);
		return (str1[i] == str2[i]);
	}
	return (FALSE);
}



int	ptrarr_equals(void const** ptr1, void const** ptr2)
{
	size_t	i;

	if (ptr1 == ptr2)
		return (TRUE);
	if (ptr1 && ptr2)
	{
		i = 0;
		while (ptr1[i] && ptr2[i])
		{
			if (ptr1[i] != ptr2[i])
				return (FALSE);
			++i;
		}
		return (ptr1[i] == ptr2[i]);
	}
	return (FALSE);
}



int	strarr_equals(char const** strarr1, char const** strarr2)
{
	size_t	i;

	if (strarr1 == strarr2)
		return (TRUE);
	if (strarr1 && strarr2)
	{
		i = 0;
		while (strarr1[i] && strarr2[i])
		{
			if (!str_equals(strarr1[i], strarr2[i]))
				return (FALSE);
			++i;
		}
		return (strarr1[i] && strarr2[i]);
	}
	return (FALSE);
}



char*	print_memory(void const* ptr, size_t length)
{
	char*	result;
	t_u8	byte;
	char	hi;
	char	lo;

	if (ptr == NULL)
		return (NULL);
	if (!(result = (char*)malloc(length * 3)))
		return (NULL);
	for (size_t i = 0; i < length; ++i)
	{
		byte = ((t_u8 const* )ptr)[i];
		hi = ((byte >> 4) & 0xF);
		lo = (byte & 0xF);
		result[i * 3 + 0] = hi + (hi < 10 ? '0' : 'A' - 10);
		result[i * 3 + 1] = lo + (lo < 10 ? '0' : 'A' - 10);
		result[i * 3 + 2] = (i + 1 == length) ? '\0' : ' ';
	}
	return (result);
}



char*	strtoescape(char const* str)
{
	unsigned char HI_nibble;
	unsigned char LO_nibble;
	char*	result;
	size_t	index = 0;
	size_t	i = 0;

	if (str == NULL)
		return (NULL);
	if (!(result = (char*)malloc(strlen(str) * 4 + 2)))
		return (NULL);
	while (str[index])
	{
		if (str[index] == '\'' ||
			str[index] == '\"' ||
			str[index] == '\\' ||
			!isprint(str[index]))
		{
			result[i++] = '\\';
			switch (str[index])
			{
				case 0x07:	result[i++] = 'a';	break; // Alert (Beep, Bell) (added in C89)[1]
				case 0x08:	result[i++] = 'b';	break; // Backspace
				case 0x0C:	result[i++] = 'f';	break; // Formfeed
				case 0x0A:	result[i++] = 'n';	break; // Newline (Line Feed); see notes below
				case 0x0D:	result[i++] = 'r';	break; // Carriage Return
				case 0x09:	result[i++] = 't';	break; // Horizontal Tab
				case 0x0B:	result[i++] = 'v';	break; // Vertical Tab
				case 0x27:	result[i++] = '\'';	break; // Single quotation mark
				case 0x22:	result[i++] = '\"';	break; // Double quotation mark
				case 0x5C:	result[i++] = '\\';	break; // Backslash
				case 0x3F:	result[i++] = '?';	break; // Question mark (used to avoid trigraphs)
				default:	result[i++] = 'x';	// Hexadecimal char notation: \xFF
					HI_nibble = (str[index] & 0xF0) >> 4;
					LO_nibble = (str[index] & 0x0F);
					result[i++] = (HI_nibble < 10) ? (HI_nibble + '0') : (HI_nibble - 10 + 'A');
					result[i++] = (LO_nibble < 10) ? (LO_nibble + '0') : (LO_nibble - 10 + 'A');
				break;
			}
		}
		else result[i++] = str[index];
		++index;
	}
	result[i] = '\0';
	return (result);
}



char*	strsurround(char const* str, char begin, char end)
{
	char*	result;
	size_t	length;
	size_t	i = 0;

	if (str == NULL)
		return (NULL);
	length = strlen(str);
	if (!(result = (char*)malloc(length + 3)))
		return (NULL);
	result[i++] = begin;
	memcpy(result + i, str, length);
	i += length;
	result[i++] = end;
	result[i] = '\0';
	return (result);
}



char*	sinttostr(t_s64 number)
{
	char*	result;
	t_u8	digits[20];
	t_u8	i;
	t_u64	n;

	n = number;
	if (number < 0)
		n = -n;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (!(result = (char*)malloc(i + 2)))
		return (NULL);
	result[0] = (number == 0) ? '0' : '-';
	n = 1;
	while (i--)
	{
		result[n++] = '0' + digits[i];
	}
	result[n] = '\0';
	return (number <= 0 ? result : result + 1);
}



char*	uinttostr(t_u64 number)
{
	char*	result;
	t_u8	digits[20];
	t_u8	i;
	t_u64	n;

	n = number;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 10;
		n /= 10;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char*)malloc(i + 1)))
		return (NULL);
	n = 0;
	while (i--)
	{
		result[n++] = '0' + digits[i];
	}
	result[n] = '\0';
	return (result);
}



char*	ptrtostr(void const* ptr)
{
	char*	result;
	t_u8	digits[sizeof(void const*) * 2];
	t_u8	i;
	t_uintmax	n;

	n = (t_uintmax)ptr;
	i = 0;
	while (n > 0)
	{
		digits[i++] = n % 16;
		n /= 16;
	}
	if (i == 0)
		digits[i++] = 0;
	if (!(result = (char*)malloc(2 + i + 1)))
		return (NULL);
	n = 0;
	result[n++] = '0';
	result[n++] = 'x';
	while (i--)
	{
		result[n++] = digits[i] + (digits[i] < 10 ? '0' : 'A' - 10);
	}
	result[n] = '\0';
	return (result);
}
