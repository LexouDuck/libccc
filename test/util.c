
#include <ctype.h>
#include <math.h>

#include "libccc/math.h"
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



#define DEFINEFUNC_SINTTOSTR(BITS) \
char*	s##BITS##tostr(t_s##BITS number)		\
{												\
	char*		result;							\
	uint8_t	digits[64] = { 0 };					\
	uint8_t	i;									\
	uint##BITS##_t	n;							\
												\
	n = number;									\
	if (number < 0)								\
		n = -n;									\
	i = 0;										\
	while (n > 0)								\
	{											\
		digits[i++] = n % 10;					\
		n /= 10;								\
	}											\
	if (!(result = (char*)malloc(i + 2)))		\
		return (NULL);							\
	result[0] = (number == 0) ? '0' : '-';		\
	n = 1;										\
	while (i--)									\
	{											\
		result[n++] = '0' + digits[i];			\
	}											\
	result[n] = '\0';							\
	return (number <= 0 ? result : result + 1);	\
}												\

DEFINEFUNC_SINTTOSTR(8)
DEFINEFUNC_SINTTOSTR(16)
DEFINEFUNC_SINTTOSTR(32)
DEFINEFUNC_SINTTOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINTTOSTR(128)
#endif



#define DEFINEFUNC_UINTTOSTR(BITS) \
char*	u##BITS##tostr(t_u##BITS number)		\
{												\
	char*		result;							\
	uint8_t	digits[64] = { 0 };					\
	uint8_t	i;									\
	uint##BITS##_t	n;							\
												\
	n = number;									\
	i = 0;										\
	while (n > 0)								\
	{											\
		digits[i++] = n % 10;					\
		n /= 10;								\
	}											\
	if (i == 0)									\
		digits[i++] = 0;						\
	if (!(result = (char*)malloc(i + 1)))		\
		return (NULL);							\
	n = 0;										\
	while (i--)									\
	{											\
		result[n++] = '0' + digits[i];			\
	}											\
	result[n] = '\0';							\
	return (result);							\
}												\

DEFINEFUNC_UINTTOSTR(8)
DEFINEFUNC_UINTTOSTR(16)
DEFINEFUNC_UINTTOSTR(32)
DEFINEFUNC_UINTTOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINTTOSTR(128)
#endif



char*	ptrtostr(void const* ptr)
{
	char*	result;
	uint8_t	digits[sizeof(void const*) * 2];
	uint8_t	i;
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



static
t_bool	memswap(void* ptr1, void* ptr2, t_size size)
{
	uint8_t*	p1;
	uint8_t*	p2;
	size_t	i;

	if (ptr1 == NULL)	return (ERROR);
	if (ptr2 == NULL)	return (ERROR);
	if (ptr1 == ptr2 || size == 0)
		return (OK);
	if (ptr1 && ptr2)
	{
		p1 = (t_u8*)ptr1;
		p2 = (t_u8*)ptr2;
		i = 0;
		while (i < size)
		{
			p1[i] = (p1[i] ^ p2[i]);
			p2[i] = (p2[i] ^ p1[i]);
			p1[i] = (p1[i] ^ p2[i]);
			++i;
		}
		return (OK);
	}
	return (ERROR);
}

#include <stdio.h>

#define DEFINEFUNCTIONS_STATS(NAME_UPPER, NAME, TYPE) \
 \
TYPE	stat_getmin_##NAME(TYPE * const values, unsigned int length) \
{ \
	TYPE result = NAME_UPPER##_MAX; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		if (result > values[i]) \
			result = values[i]; \
	} \
	return (result); \
} \
 \
TYPE	stat_getmax_##NAME(TYPE * const values, unsigned int length) \
{ \
	TYPE result = NAME_UPPER##_MIN; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		if (result < values[i]) \
			result = values[i]; \
	} \
	return (result); \
} \
 \
double	stat_median_##NAME(TYPE * const values, unsigned int length) \
{ \
	return ((length % 2) ? \
		values[length / 2] : \
		(values[length / 2] + values[length / 2 + 1]) / 2); \
} \
 \
double	stat_average_##NAME(TYPE * const values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum; \
	double	inv_len; \
	unsigned int	i; \
	sum = 0.; \
	inv_len = (1. / length); \
	i = 0; \
	while (i < length) \
	{ \
		value = values[i]; \
		if (isnormal((double)value)) \
			sum += inv_len * value; \
		++i; \
	} \
	return (sum); \
} \
 \
double	stat_variance_##NAME(TYPE * const values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum; \
	double	average; \
	unsigned int	i; \
	average = stat_average_##NAME(values, length); \
	sum = 0.; \
	i = 0; \
	while (i < length) \
	{ \
		value = values[i]; \
		if (isnormal((double)value)) \
			sum += value * value; \
		++i; \
	} \
	return ((sum / i) - (average * average)); \
} \
inline double	stat_stddev_##NAME(TYPE * const values, unsigned int length) \
{ \
	return sqrt(stat_variance_##NAME(values, length)); \
} \
 \
void	quicksort_##NAME(TYPE * array, unsigned int start, unsigned int end) \
{ \
	TYPE pivot; \
	unsigned int pivot_id; \
	unsigned int rise_id; \
	unsigned int fall_id; \
	pivot = array[start]; \
	if (start >= end || pivot != pivot) \
		return; \
	if (start == end - 1) \
	{ \
		if (pivot > array[end]) \
			memswap(array + start, array + end, sizeof(TYPE)); \
		return; \
	} \
	rise_id = start + 1; \
	fall_id = end; \
	while (rise_id < fall_id) \
	{ \
		while (rise_id <= end && array[rise_id] <= pivot) \
		{ \
			++rise_id; \
		} \
		while (fall_id > start && array[fall_id] > pivot) \
		{ \
			--fall_id; \
		} \
		if (rise_id < fall_id) \
			memswap(array + rise_id, array + fall_id, sizeof(TYPE)); \
	} \
	pivot_id = fall_id; \
	if (start != fall_id) \
		memswap(array + start, array + fall_id, sizeof(TYPE)); \
	if (pivot_id > start) \
		quicksort_##NAME(array, start, pivot_id - 1); \
	if (pivot_id < end) \
		quicksort_##NAME(array, pivot_id + 1, end); \
} \

DEFINEFUNCTIONS_STATS(UINT , uint , t_uint)
DEFINEFUNCTIONS_STATS(U8   , u8   , t_u8)
DEFINEFUNCTIONS_STATS(U16  , u16  , t_u16)
DEFINEFUNCTIONS_STATS(U32  , u32  , t_u32)
DEFINEFUNCTIONS_STATS(U64  , u64  , t_u64)
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(U128 , u128 , t_u128)
#endif
DEFINEFUNCTIONS_STATS(SINT , sint , t_sint)
DEFINEFUNCTIONS_STATS(S8   , s8   , t_s8)
DEFINEFUNCTIONS_STATS(S16  , s16  , t_s16)
DEFINEFUNCTIONS_STATS(S32  , s32  , t_s32)
DEFINEFUNCTIONS_STATS(S64  , s64  , t_s64)
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(S128 , s128 , t_s128)
#endif
DEFINEFUNCTIONS_STATS(FIXED, fixed, t_fixed)
DEFINEFUNCTIONS_STATS(Q16  , q16  , t_q16)
DEFINEFUNCTIONS_STATS(Q32  , q32  , t_q32)
DEFINEFUNCTIONS_STATS(Q64  , q64  , t_q64)
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(Q128 , q128 , t_q128)
#endif
DEFINEFUNCTIONS_STATS(FLOAT, float, t_float)
DEFINEFUNCTIONS_STATS(F32  , f32  , t_f32)
DEFINEFUNCTIONS_STATS(F64  , f64  , t_f64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNCTIONS_STATS(F80  , f80  , t_f80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNCTIONS_STATS(F128 , f128 , t_f128)
#endif
