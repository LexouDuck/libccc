
#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>
#include <math.h>

#include "libccc.h"
#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"
#include "libccc/text/format.h"

#include "test.h"
#include "test_utils.h"



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



#if LIBCONFIG_USE_INT128
typedef _UInt128	uint128_t;
#endif



#define DEFINEFUNC_UINTTOSTR(BITS) \
char*	u##BITS##tostr(t_u##BITS number) \
{ \
	char*		result; \
	uint8_t	digits[64] = { 0 }; \
	uint8_t	i; \
	uint##BITS##_t	n; \
	if (LIBCONFIG_UINT_NAN && number == U##BITS##_ERROR)	return (strdup("nan")); \
	if (LIBCONFIG_UINT_INF && number == U##BITS##_MAX)	return (strdup("+inf")); \
	if (LIBCONFIG_UINT_INF && number == U##BITS##_MIN)	return (strdup("-inf")); \
	n = number; \
	i = 0; \
	while (n > 0) \
	{ \
		digits[i++] = n % 10; \
		n /= 10; \
	} \
	if (i == 0) \
		digits[i++] = 0; \
	if (!(result = (char*)malloc(i + 1))) \
		return (NULL); \
	n = 0; \
	while (i--) \
	{ \
		result[n++] = '0' + digits[i]; \
	} \
	result[n] = '\0'; \
	return (result); \
} \

DEFINEFUNC_UINTTOSTR(8)
DEFINEFUNC_UINTTOSTR(16)
DEFINEFUNC_UINTTOSTR(32)
DEFINEFUNC_UINTTOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_UINTTOSTR(128)
#endif



#define DEFINEFUNC_SINTTOSTR(BITS) \
char*	s##BITS##tostr(t_s##BITS number) \
{ \
	char*		result; \
	uint8_t	digits[64] = { 0 }; \
	uint8_t	i; \
	uint##BITS##_t	n; \
	if (LIBCONFIG_SINT_NAN && number == S##BITS##_ERROR)	return (strdup("nan")); \
	if (LIBCONFIG_SINT_INF && number == S##BITS##_MAX)	return (strdup("+inf")); \
	if (LIBCONFIG_SINT_INF && number == S##BITS##_MIN)	return (strdup("-inf")); \
	n = number; \
	if (number < 0) \
		n = -n; \
	i = 0; \
	while (n > 0) \
	{ \
		digits[i++] = n % 10; \
		n /= 10; \
	} \
	if (!(result = (char*)malloc(i + 2))) \
		return (NULL); \
	result[0] = (number == 0) ? '0' : '-'; \
	n = 1; \
	while (i--) \
	{ \
		result[n++] = '0' + digits[i]; \
	} \
	result[n] = '\0'; \
	return (number <= 0 ? result : result + 1); \
} \

DEFINEFUNC_SINTTOSTR(8)
DEFINEFUNC_SINTTOSTR(16)
DEFINEFUNC_SINTTOSTR(32)
DEFINEFUNC_SINTTOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_SINTTOSTR(128)
#endif



#define DEFINEFUNC_FIXEDTOSTR(BITS) \
char*	q##BITS##tostr(t_q##BITS number) \
{ \
	if (LIBCONFIG_FIXED_NAN && number._ == Q##BITS##_ERROR._)	return (strdup("nan")); \
	if (LIBCONFIG_FIXED_INF && number._ == Q##BITS##_MAX._)	return (strdup("+inf")); \
	if (LIBCONFIG_FIXED_INF && number._ == Q##BITS##_MIN._)	return (strdup("-inf")); \
	size_t maxlen = 40 * 3 + 8; \
	char* result = (char*)malloc(maxlen); \
/*	snprintf(result, maxlen, "%g", Q##BITS##_IntegerPart(number)._ + Q##BITS##_FractionPart(number)._ / (double)Q##BITS##_DENOM); */ \
	snprintf(result, maxlen, "" SF_S##BITS ".(" SF_S##BITS "/%i)", Q##BITS##_IntegerPart(number)._, Q##BITS##_FractionPart(number)._, Q##BITS##_DENOM); \
	return (result); \
} \

DEFINEFUNC_FIXEDTOSTR(8)
DEFINEFUNC_FIXEDTOSTR(16)
DEFINEFUNC_FIXEDTOSTR(32)
DEFINEFUNC_FIXEDTOSTR(64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_FIXEDTOSTR(128)
#endif



char*	ptrtostr(void const* ptr)
{
	char*	result;
	uint8_t	digits[sizeof(void const*) * 2];
	uint8_t	i;
	uintmax_t	n;

	n = (uintmax_t)ptr;
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



#define DEFINEFUNCTIONS_STATS(TYPE, TYPE_LOWER, TYPE_MIXED, TYPE_UPPER, CHECK_INVALID, GET) \
/*! https://en.wikipedia.org/wiki/Quicksort */ \
void	quicksort_##TYPE_LOWER(TYPE * array, unsigned int start, unsigned int end) \
{ \
	TYPE pivot; \
	unsigned int pivot_id; \
	unsigned int rise_id; \
	unsigned int fall_id; \
	pivot = array[start]; \
	if (start >= end || pivot GET != pivot GET) \
		return; \
	if (start == end - 1) \
	{ \
		if (pivot GET > array[end] GET) \
			memswap(array + start, array + end, sizeof(TYPE)); \
		return; \
	} \
	rise_id = start + 1; \
	fall_id = end; \
	while (rise_id < fall_id) \
	{ \
		while (rise_id <= end && array[rise_id] GET <= pivot GET) \
		{ \
			++rise_id; \
		} \
		while (fall_id > start && array[fall_id] GET > pivot GET) \
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
		quicksort_##TYPE_LOWER(array, start, pivot_id - 1); \
	if (pivot_id < end) \
		quicksort_##TYPE_LOWER(array, pivot_id + 1, end); \
} \
/*! https://en.wikipedia.org/wiki/Sample_maximum_and_minimum */ \
TYPE	stat_getmin_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	result = TYPE_UPPER##_MAX; \
	for (unsigned int  i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (result GET > value GET) \
			result GET = value GET; \
	} \
	if (result GET == TYPE_UPPER##_MAX GET) \
		return (TYPE_UPPER##_ERROR); \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Sample_maximum_and_minimum */ \
TYPE	stat_getmax_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	result = TYPE_UPPER##_MIN; \
	for (unsigned int  i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (result GET < value GET) \
			result GET = value GET; \
	} \
	if (result GET == TYPE_UPPER##_MIN GET) \
		return (TYPE_UPPER##_ERROR); \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Quantile */ \
double*	stat_quantiles_##TYPE_LOWER(const TYPE * values, unsigned int length, unsigned int  n) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	double*	result = (double*)malloc((n + 1) * sizeof(double)); \
	if (result == NULL) \
		return (NULL); \
	unsigned int 	position; \
	for (unsigned int  i = 0; i < n; ++i) \
	{ \
		position = i * length / n; \
		result[i] = ((length - (n - 1)) % n == 0) ? \
			((double)(values[position]GET)) : \
			(((double)(values[position]GET) + (double)(values[position + 1]GET)) / 2); \
	} \
	result[n] = (double)(values[length - 1]GET); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Median */ \
double	stat_median_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	return ((length % 2) ? \
		((double)(values[length / 2]GET)) : \
		(((double)(values[length / 2]GET) + (double)(values[length / 2 + 1]GET)) / 2)); \
} \
/*! https://en.wikipedia.org/wiki/Mode_(statistics) */ \
double	stat_mode_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	TYPE	value; \
	TYPE	result = TYPE_UPPER##_ERROR; \
	TYPE	previous = TYPE_UPPER##_ERROR; \
	unsigned int 	consecutive_record = 0; \
	unsigned int 	consecutive_current = 0; \
	for (unsigned int  i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (previous GET == value GET) \
			consecutive_current++; \
		if (consecutive_record < consecutive_current) \
		{ \
			consecutive_record = consecutive_current; \
			result = value; \
		} \
		previous = value; \
	} \
	return (double)(result GET); \
} \
/*! https://en.wikipedia.org/wiki/Range_(statistics) */ \
double	stat_range_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	TYPE	value; \
	TYPE	minval = TYPE_UPPER##_MAX; \
	TYPE	maxval = TYPE_UPPER##_MIN; \
	for (unsigned int  i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (minval GET > value GET) \
			minval GET = value GET; \
		if (maxval GET < value GET) \
			maxval GET = value GET; \
	} \
	if (minval GET == TYPE_UPPER##_MAX GET) \
		return (NAN); \
	if (maxval GET == TYPE_UPPER##_MIN GET) \
		return (NAN); \
	return (double)(maxval GET) - (double)(minval GET); \
} \
/*! https://en.wikipedia.org/wiki/Midrange */ \
double	stat_midrange_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	TYPE	value; \
	TYPE	minval = TYPE_UPPER##_MAX; \
	TYPE	maxval = TYPE_UPPER##_MIN; \
	for (unsigned int  i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (minval GET > value GET) \
			minval GET = value GET; \
		if (maxval GET < value GET) \
			maxval GET = value GET; \
	} \
	if (minval GET == TYPE_UPPER##_MAX GET) \
		return (NAN); \
	if (maxval GET == TYPE_UPPER##_MIN GET) \
		return (NAN); \
	return (((double)(minval GET) + (double)(maxval GET)) / 2.); \
} \
/*! https://en.wikipedia.org/wiki/Midhinge */ \
double	stat_midhinge_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##TYPE_LOWER(values, length, 4); \
	return (quartiles[1] + quartiles[3]) / 2; \
} \
/*! https://en.wikipedia.org/wiki/Trimean */ \
double	stat_trimean_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##TYPE_LOWER(values, length, 4); \
	return (quartiles[1] + quartiles[2] + quartiles[2] + quartiles[3]) / 4; \
} \
/*! https://en.wikipedia.org/wiki/Arithmetic_mean */ \
double	stat_mean_arithmetic_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += (double)(value GET); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Geometric_mean */ \
double	stat_mean_geometric_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	product = 1.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		product *= (double)(value GET); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return pow(product, 1. / n); \
} \
/*! https://en.wikipedia.org/wiki/Harmonic_mean */ \
double	stat_mean_harmonic_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	invsum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		invsum += 1. / (double)(value GET); \
		n++; \
	} \
	if (n == 0 || invsum == 0.) \
		return (NAN); \
	return (n / invsum); \
} \
/*! https://en.wikipedia.org/wiki/Contraharmonic_mean */ \
double	stat_mean_contraharmonic_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum1 = 0.; \
	double	sum2 = 0.; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		sum1 += value_float; \
		sum2 += value_float * value_float; \
	} \
	if (sum1 == 0. && sum2 == 0.) \
		return (NAN); \
	return (sum2 / sum1); \
} \
/*! https://en.wikipedia.org/wiki/Interquartile_mean */ \
double	stat_mean_interquartile_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##TYPE_LOWER(values, length, 4); \
	TYPE	value; \
	double	value_float; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		if (value_float < quartiles[1] || value_float > quartiles[3]) \
			continue; \
		sum += value_float; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Quadratic_mean */ \
double	stat_mean_quadratic_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		sum += value_float * value_float; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sqrt(sum / n)); \
} \
/*! https://en.wikipedia.org/wiki/Cubic_mean */ \
double	stat_mean_cubic_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		sum += value_float * value_float * value_float; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (cbrt(sum / n)); \
} \
/*! https://en.wikipedia.org/wiki/Power_mean */ \
double	stat_mean_power_##TYPE_LOWER(const TYPE * values, unsigned int length, double p) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		sum += pow(value_float, p); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (pow(sum / n, 1 / p)); \
} \
/*! https://en.wikipedia.org/wiki/Lehmer_mean */ \
double	stat_mean_lehmer_##TYPE_LOWER(const TYPE * values, unsigned int length, int power) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum1 = 0.; \
	double	sum2 = 0.; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		sum1 += pow(value_float, power - 1); \
		sum2 += pow(value_float, power); \
	} \
	if (sum1 == 0. && sum2 == 0.) \
		return (NAN); \
	return (sum2 / sum1); \
} \
/*! https://en.wikipedia.org/wiki/Variance */ \
double	stat_variance_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum = 0.; \
	double	average = stat_mean_arithmetic_##TYPE_LOWER(values, length); \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = (double)(value GET); \
		sum += value_float * value_float; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return ((sum / n) - (average * average)); \
} \
/*! https://en.wikipedia.org/wiki/Standard_deviation */ \
double	stat_stddev_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	return sqrt(stat_variance_##TYPE_LOWER(values, length)); \
} \
/*! https://en.wikipedia.org/wiki/Coefficient_of_variation */ \
double	stat_cv_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	double average = stat_mean_arithmetic_##TYPE_LOWER(values, length); \
	if (average == 0) \
		return (NAN); \
	return (stat_stddev_##TYPE_LOWER(values, length) / average); \
} \
/*! https://en.wikipedia.org/wiki/Interquartile_range */ \
double	stat_iqr_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##TYPE_LOWER(values, length, 4); \
	return (quartiles[3] - quartiles[1]); \
} \
/*! https://en.wikipedia.org/wiki/Median_absolute_deviation */ \
double	stat_mad_##TYPE_LOWER(const TYPE * values, unsigned int length) \
{ \
	double*	pairs = (double*)malloc(length * sizeof(double)); \
	if (pairs == NULL) \
		return (NAN); \
	double	median = stat_median_##TYPE_LOWER(values, length); \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		pairs[i] = fabs((double)(values[i] GET) - median); \
	} \
	double	result = stat_median_float(pairs, length); \
	free(pairs); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Average_absolute_deviation */ \
double	stat_aad_##TYPE_LOWER(const TYPE * values, unsigned int length, TYPE center) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += (double)(value GET) - (double)(center GET); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Arithmetic%E2%80%93geometric_mean */ \
double	stat_agm_##TYPE_LOWER(TYPE x, TYPE y) \
{ \
	double a, a_n; \
	double g, g_n; \
	if (x GET > y GET) \
		{	a = (double)(x GET);	g = (double)(y GET);	} \
	else{	a = (double)(y GET);	g = (double)(x GET);	} \
	while (a != g) \
	{ \
		a_n = (a + g) * 0.5; \
		g_n = sqrt(a * g); \
		a = a_n; \
		g = g_n; \
	} \
	return a; \
} \
/*! https://en.wikipedia.org/wiki/Mean_signed_deviation */ \
double	stat_msd_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	error; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (double)(expect[i] GET) - (double)(value GET); \
		sum += error; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_squared_error */ \
double	stat_mse_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	error; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (double)(value GET) - (double)(expect[i] GET); \
		sum += error * error; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_error */ \
double	stat_mae_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	error; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (double)(expect[i] GET) - (double)(value GET); \
		sum += fabs(error); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_difference */ \
double	stat_md_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	error; \
	double*	pairs = (double*)malloc(length * sizeof(double)); \
	if (pairs == NULL) \
		return (NAN); \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (double)(expect[i] GET) - (double)(value GET); \
		pairs[n] = fabs(error); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	double	result = stat_mean_arithmetic_float(pairs, n); \
	free(pairs); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_difference#Relative_mean_absolute_difference */ \
double	stat_rmd_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	return (stat_md_##TYPE_LOWER(values, expect, length) / stat_mean_arithmetic_##TYPE_LOWER(values, length)); \
} \
/*! https://en.wikipedia.org/wiki/Root_mean_square_deviation */ \
double	stat_rmsd_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	return sqrt(stat_mse_##TYPE_LOWER(values, expect, length)); \
} \
/*! https://en.wikipedia.org/wiki/Mean_percentage_error */ \
double	stat_mpe_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (value GET == 0)	continue; \
		value_float = (double)(value GET); \
		sum += (value_float - (double)(expect[i] GET)) / value_float; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n) * 100.; \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_percentage_error */ \
double	stat_mape_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double value_float; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (value GET == 0)	continue; \
		value_float = (double)(value GET); \
		sum += fabs((value_float - (double)(expect[i] GET)) / value_float); \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n) * 100.; \
} \
/*! https://en.wikipedia.org/wiki/Mean_squared_prediction_error */ \
double	stat_mspe_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	error; \
	double	sum = 0.; \
	unsigned int 	n = 0; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (double)(value GET) - (double)(expect[i] GET); \
		sum += error; \
		n++; \
	} \
	if (n == 0) \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Residual_sum_of_squares */ \
double	stat_rss_##TYPE_LOWER(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	error; \
	double	sum = 0.; \
	for (unsigned int  i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (double)(value GET) - (double)(expect[i] GET); \
		sum += error * error; \
	} \
	return (sum); \
} \
/*! https://en.wikipedia.org/wiki/Squared_deviations_from_the_mean */ \
/*TODO*/

#if 0

/*! https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average */ \
double	stat_moving_average_simple_##NAME(const TYPE * values, unsigned int length) \
{ \
	return ?; \
} \
/*! https://en.wikipedia.org/wiki/Moving_average#Cumulative_moving_average */ \
double	stat_moving_average_cumulative_##NAME(const TYPE * values, unsigned int length) \
{ \
	return ?; \
} \
/*! https://en.wikipedia.org/wiki/Moving_average#Weighted_moving_average */ \
double	stat_moving_average_weighted_##NAME(const TYPE * values, unsigned int length) \
{ \
	return ?; \
} \

#endif

DEFINEFUNCTIONS_STATS(t_uint , uint , UInt , UINT , (LIBCONFIG_UINT_NAN  ? (value ==  UINT_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_u8   , u8   , U8   , U8   , (LIBCONFIG_UINT_NAN  ? (value ==    U8_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_u16  , u16  , U16  , U16  , (LIBCONFIG_UINT_NAN  ? (value ==   U16_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_u32  , u32  , U32  , U32  , (LIBCONFIG_UINT_NAN  ? (value ==   U32_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_u64  , u64  , U64  , U64  , (LIBCONFIG_UINT_NAN  ? (value ==   U64_ERROR) : FALSE), )
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(t_u128 , u128 , U128 , U128 , (LIBCONFIG_UINT_NAN  ? (value ==  U128_ERROR) : FALSE), )
#endif

DEFINEFUNCTIONS_STATS(t_sint , sint , SInt , SINT , (LIBCONFIG_SINT_NAN  ? (value ==  SINT_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_s8   , s8   , S8   , S8   , (LIBCONFIG_SINT_NAN  ? (value ==    S8_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_s16  , s16  , S16  , S16  , (LIBCONFIG_SINT_NAN  ? (value ==   S16_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_s32  , s32  , S32  , S32  , (LIBCONFIG_SINT_NAN  ? (value ==   S32_ERROR) : FALSE), )
DEFINEFUNCTIONS_STATS(t_s64  , s64  , S64  , S64  , (LIBCONFIG_SINT_NAN  ? (value ==   S64_ERROR) : FALSE), )
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(t_s128 , s128 , S128 , S128 , (LIBCONFIG_SINT_NAN  ? (value ==  S128_ERROR) : FALSE), )
#endif

DEFINEFUNCTIONS_STATS(t_fixed, fixed, Fixed, FIXED, (LIBCONFIG_FIXED_NAN ? (value._ == FIXED_ERROR._) : FALSE), ._)
DEFINEFUNCTIONS_STATS(t_q8   , q8   , Q8   , Q8   , (LIBCONFIG_FIXED_NAN ? (value._ ==    Q8_ERROR._) : FALSE), ._)
DEFINEFUNCTIONS_STATS(t_q16  , q16  , Q16  , Q16  , (LIBCONFIG_FIXED_NAN ? (value._ ==   Q16_ERROR._) : FALSE), ._)
DEFINEFUNCTIONS_STATS(t_q32  , q32  , Q32  , Q32  , (LIBCONFIG_FIXED_NAN ? (value._ ==   Q32_ERROR._) : FALSE), ._)
DEFINEFUNCTIONS_STATS(t_q64  , q64  , Q64  , Q64  , (LIBCONFIG_FIXED_NAN ? (value._ ==   Q64_ERROR._) : FALSE), ._)
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(t_q128 , q128 , Q128 , Q128 , (LIBCONFIG_FIXED_NAN ? (value._ ==  Q128_ERROR._) : FALSE), ._)
#endif

DEFINEFUNCTIONS_STATS(t_float, float, Float, FLOAT, !isnormal(value), )
#if LIBCONFIG_USE_FLOAT16
DEFINEFUNCTIONS_STATS(t_f16  , f16  , F16  , F16  , !isnormal(value), )
#endif
DEFINEFUNCTIONS_STATS(t_f32  , f32  , F32  , F32  , !isnormal(value), )

DEFINEFUNCTIONS_STATS(t_f64  , f64  , F64  , F64  , !isnormal(value), )
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNCTIONS_STATS(t_f80  , f80  , F80  , F80  , !isnormal(value), )
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNCTIONS_STATS(t_f128 , f128 , F128 , F128 , !isnormal(value), )
#endif
