
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



t_uintmax	Memory_GetBits(t_uintmax value, t_u8 bit, t_u8 length)
{
	t_uintmax	mask;
	t_u8		i;

	HANDLE_ERROR(INDEX2LARGE, (bit >= sizeof(t_uintmax) * 8),
		return (0);)
	HANDLE_ERROR(LENGTH2LARGE, (bit + length >= sizeof(t_uintmax) * 8),
		return (0);)
	mask = 0;
	i = 0;
	while (i < length)
	{
		mask <<= 1;
		mask |= 1;
		++i;
	}
	return ((value >> bit) & mask);
}



t_u8	Memory_CountBits(t_uintmax value)
{
	t_u8	result;
	t_u8	i;

	result = 0;
	i = 0;
	while (i < sizeof(t_uintmax) * 8)
	{
		if (value & 1)
			result += 1;
		value >>= 1;
		++i;
	}
	return (result);
}



// TODO implement using CLZ functions, and check if leading bits go beyond range
t_s8	Memory_GetMostSignificantBit(t_uintmax value)
{
	static const t_uintmax	mask = ((t_uintmax)1 << ((sizeof(t_uintmax) * 8) - 1));
	t_u8	result;
	t_u8	i;

	if (value == 0)
		return (ERROR);
	result = 0;
	i = 0;
	while (i < sizeof(t_uintmax) * 8)
	{
		if (value & mask)
			return (i);
		value >>= 1;
		++i;
	}
	return (ERROR);
}



t_s8	Memory_GetLeastSignificantBit(t_uintmax value)
{
	t_u8	result;
	t_u8	i;

	if (value == 0)
		return (ERROR);
	result = 0;
	i = 0;
	while (i < sizeof(t_uintmax) * 8)
	{
		if (value & 1)
			return (i);
		value >>= 1;
		++i;
	}
	return (ERROR);
}
