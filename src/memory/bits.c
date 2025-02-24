
#include "libccc/memory.h"

#include LIBCONFIG_ERROR_INCLUDE



#define UINTMAX_BITS	(sizeof(t_uintmax) * 8)



t_uintmax	Memory_GetBits(void const* ptr, t_size bit, t_u8 n)
{
	t_uintmax	result = 0;
	t_size		i;
	t_s8		b;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, NULL)
		return (0);
	if CCCERROR((n > UINTMAX_BITS), ERROR_LENGTH2LARGE,
		"bit amount given (%u bits) is beyond the largest integer type (%u bits)", n, UINTMAX_BITS)
		n = UINTMAX_BITS;
	else if (n == 0)
		return (0);
	i = bit / 8;
	b = bit % 8;
	if (b + n <= 8) // fits entirely inside one byte, no need to loop
	{
		return (((((t_u8*)ptr)[i] << b) >> b) >> (8 - b - n));
	}
	while (n > 0)
	{
		result <<= 8;
		if (b >= 0)
		{	// region begin
			result |= ((((t_u8*)ptr)[i] << b) >> b);
			n -= (8 - b);
			b = -1;
		}
		else if (n >= 8)
		{	// region middle
			result |= (((t_u8*)ptr)[i]);
			n -= 8;
		}
		else
		{	// region end
			result |= ((((t_u8*)ptr)[i] >> (8 - n)) << (8 - n));
			result >>= (8 - n);
			n = 0;
		}
		++i;
	}
	return (result);
}

void	Memory_SetBits(void* ptr, t_size bit, t_u8 n, t_uintmax value)
{
	t_u8*	result = (t_u8*)ptr;
	t_size	i;
	t_s8	b;
	t_u8	set;

	if CCCERROR((ptr == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if CCCERROR((n > UINTMAX_BITS), ERROR_LENGTH2LARGE,
		"bit amount given (%u bits) is beyond the largest integer type (%u bits)", n, UINTMAX_BITS)
		n = UINTMAX_BITS;
	else if (n == 0)
		return;
	i = bit / 8;
	b = bit % 8;
	value = Memory_BitRegion(value, 0, n);
	if (b + n <= 8) // fits entirely inside one byte, no need to loop
	{
		set = ((t_u8)value << (8 - b - n));
		result[i] &= ~((((t_uintmax)1 << n) - 1) << b);
		result[i] |= set;
		return;
	}
	while (n > 0)
	{
		if (b >= 0)
		{	// region begin
			b = (8 - b);
			result[i] >>= b;
			result[i] <<= b;
			result[i] |= Memory_BitRegion(value, (n - b), b);
			n -= b;
			b = -1;
		}
		else if (n >= 8)
		{	// region middle
			result[i] = Memory_BitRegion(value, (n - 8), 8);
			n -= 8;
		}
		else
		{	// region end
			result[i] <<= n;
			result[i] >>= n;
			result[i] |= Memory_BitRegion(value, 0, n) << (8 - n);
			n = 0;
		}
		++i;
	}
}



_INLINE()
t_uintmax	Memory_BitRegion(t_uintmax value, t_u8 bit, t_u8 length)
{
	t_uintmax	mask;

	if CCCERROR((bit >= UINTMAX_BITS), ERROR_INDEX2LARGE,
		"bit region start (%u) is beyond the largest integer type (%u bits)", bit, UINTMAX_BITS)
		return (0);
	if CCCERROR((bit + length >= UINTMAX_BITS), ERROR_LENGTH2LARGE,
		"bit region end (%u) is beyond the largest integer type (%u bits)", bit + length, UINTMAX_BITS)
		return (0);
	if (length >= UINTMAX_BITS)
		mask = ~(t_uintmax)0;
	else
		mask = ((t_uintmax)1 << length) - 1;
	return ((value >> bit) & mask);
}



t_u8	Memory_CountBits(t_uintmax value)
{
	t_u8	result;
	t_u8	i;

	result = 0;
	for (i = 0; i < UINTMAX_BITS; ++i)
	{
		if (value & 1)
			result += 1;
		value >>= 1;
	}
	return (result);
}



// TODO implement using CLZ functions, and check if leading bits go beyond range
t_s8	Memory_GetMostSignificantBit(t_uintmax value)
{
	t_uintmax	mask;
	t_sint	i;

	if (value == 0)
		return (ERROR);
	for (i = UINTMAX_BITS - 1; i >= 0; --i)
	{
		mask = ((t_uintmax)1 << i);
		if (value & mask)
			return (i);
	}
	return (ERROR);
}



t_s8	Memory_GetLeastSignificantBit(t_uintmax value)
{
	t_uint	i;

	if (value == 0)
		return (ERROR);
	for (i = 0; i < UINTMAX_BITS; ++i)
	{
		if (value & 1)
			return (i);
		value >>= 1;
	}
	return (ERROR);
}
