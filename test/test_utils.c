
#include <ctype.h>
#include <float.h>
#include <math.h>

#include "libccc.h"
#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"

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



#define DEFINEFUNC_SINTTOSTR(BITS) \
char*	s##BITS##tostr(t_s##BITS number) \
{ \
	char*		result; \
	uint8_t	digits[64] = { 0 }; \
	uint8_t	i; \
	uint##BITS##_t	n; \
 \
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



#define DEFINEFUNC_UINTTOSTR(BITS) \
char*	u##BITS##tostr(t_u##BITS number) \
{ \
	char*		result; \
	uint8_t	digits[64] = { 0 }; \
	uint8_t	i; \
	uint##BITS##_t	n; \
 \
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



#define DEFINEFUNCTIONS_STATS(NAME_UPPER, NAME, TYPE, CHECK_INVALID) \
/*! https://en.wikipedia.org/wiki/Quicksort */ \
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
/*! https://en.wikipedia.org/wiki/Sample_maximum_and_minimum */ \
TYPE	stat_getmin_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	result = NAME_UPPER##_MAX; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (result > value) \
			result = value; \
	} \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Sample_maximum_and_minimum */ \
TYPE	stat_getmax_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	result = NAME_UPPER##_MIN; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (result < value) \
			result = value; \
	} \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Quantile */ \
double*	stat_quantiles_##NAME(const TYPE * values, unsigned int length, unsigned int n) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	double*	result = malloc((n + 1) * sizeof(double)); \
	unsigned int	position; \
	for (unsigned int i = 0; i < n; ++i) \
	{ \
		position = i * length / n; \
		result[i] = ((length - (n - 1)) % n == 0) ? \
			((double)values[position]) : \
			((double)values[position] + values[position + 1]) / 2; \
	} \
	result[n] = values[length - 1]; \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Median */ \
double	stat_median_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	return ((length % 2) ? \
		values[length / 2] : \
		(values[length / 2] + values[length / 2 + 1]) / 2); \
} \
/*! https://en.wikipedia.org/wiki/Mode_(statistics) */ \
double	stat_mode_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	TYPE	value; \
	TYPE	result = NAME_UPPER##_ERROR; \
	TYPE	previous = 0; \
	unsigned int	consecutive_record = 0; \
	unsigned int	consecutive_current = 0; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (previous == value) \
			consecutive_current++; \
		if (consecutive_record < consecutive_current) \
		{ \
			consecutive_record = consecutive_current; \
			result = value; \
		} \
		previous = value; \
		n++; \
	} \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Range_(statistics) */ \
double	stat_range_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	TYPE	value; \
	TYPE	minval = NAME_UPPER##_MIN; \
	TYPE	maxval = NAME_UPPER##_MAX; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (minval > values[i]) \
			minval = values[i]; \
		if (maxval < values[i]) \
			maxval = values[i]; \
	} \
	return (maxval - minval); \
} \
/*! https://en.wikipedia.org/wiki/Midrange */ \
double	stat_midrange_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	TYPE	value; \
	TYPE	minval = NAME_UPPER##_MIN; \
	TYPE	maxval = NAME_UPPER##_MAX; \
	for (unsigned int i = 0; i < length; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (minval > values[i]) \
			minval = values[i]; \
		if (maxval < values[i]) \
			maxval = values[i]; \
	} \
	return (minval + maxval) / 2; \
} \
/*! https://en.wikipedia.org/wiki/Midhinge */ \
double	stat_midhinge_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##NAME(values, length, 4); \
	return (quartiles[1] + quartiles[3]) / 2; \
} \
/*! https://en.wikipedia.org/wiki/Trimean */ \
double	stat_trimean_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##NAME(values, length, 4); \
	return (quartiles[1] + quartiles[2] + quartiles[2] + quartiles[3]) / 4; \
} \
/*! https://en.wikipedia.org/wiki/Arithmetic_mean */ \
double	stat_mean_arithmetic_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += value; \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Geometric_mean */ \
double	stat_mean_geometric_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	product = 1.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		product *= value; \
		n++; \
	} \
	return pow(product, 1. / length); \
} \
/*! https://en.wikipedia.org/wiki/Harmonic_mean */ \
double	stat_mean_harmonic_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	invsum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		invsum += 1. / value; \
		n++; \
	} \
	return (n / invsum); \
} \
/*! https://en.wikipedia.org/wiki/Contraharmonic_mean */ \
double	stat_mean_contraharmonic_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum1 = 0.; \
	double	sum2 = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum1 += value; \
		sum2 += value * value; \
		n++; \
	} \
	return (sum2 / sum1); \
} \
/*! https://en.wikipedia.org/wiki/Lehmer_mean */ \
double	stat_mean_lehmer_##NAME(const TYPE * values, unsigned int length, int power) \
{ \
	TYPE	value; \
	double	sum1 = 0.; \
	double	sum2 = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum1 += pow(value, power - 1); \
		sum2 += pow(value, power); \
		n++; \
	} \
	return (sum2 / sum1); \
} \
/*! https://en.wikipedia.org/wiki/Interquartile_mean */ \
double	stat_mean_interquartile_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##NAME(values, length, 4); \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		if (value < quartiles[1] || value > quartiles[3]) \
			continue; \
		sum += value; \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Quadratic_mean */ \
double	stat_mean_quadratic_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += (value * value); \
		n++; \
	} \
	return sqrt(sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Cubic_mean */ \
double	stat_mean_cubic_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += (value * value * value); \
		n++; \
	} \
	return cbrt(sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Power_mean */ \
double	stat_mean_power_##NAME(const TYPE * values, unsigned int length, double p) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += pow(value, p); \
		n++; \
	} \
	return (pow(sum / n, 1 / p)); \
} \
/*! https://en.wikipedia.org/wiki/Variance */ \
double	stat_variance_##NAME(const TYPE * values, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	double	average = stat_mean_arithmetic_##NAME(values, length); \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += value * value; \
		n++; \
	} \
	return ((sum / n) - (average * average)); \
} \
 /*! https://en.wikipedia.org/wiki/Standard_deviation */ \
double	stat_stddev_##NAME(const TYPE * values, unsigned int length) \
{ \
	return sqrt(stat_variance_##NAME(values, length)); \
} \
/*! https://en.wikipedia.org/wiki/Coefficient_of_variation */ \
double	stat_cv_##NAME(const TYPE * values, unsigned int length) \
{ \
	return (stat_stddev_##NAME(values, length) / stat_mean_arithmetic_##NAME(values, length)); \
} \
/*! https://en.wikipedia.org/wiki/Interquartile_range */ \
double	stat_iqr_##NAME(const TYPE * values, unsigned int length) \
{ \
	/* if (sort)	quicksort_##NAME(values, 0, length); */ \
	double*	quartiles = stat_quantiles_##NAME(values, length, 4); \
	return (quartiles[3] - quartiles[1]); \
} \
/*! https://en.wikipedia.org/wiki/Median_absolute_deviation */ \
double	stat_mad_##NAME(const TYPE * values, unsigned int length) \
{ \
	double*	pairs = (double*)malloc(length * sizeof(double)); \
	double	median = stat_median_##NAME(values, length); \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		pairs[i] = fabs((double)values[i] - median); \
	} \
	double	result = stat_median_f64(pairs, length); \
	free(pairs); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Average_absolute_deviation */ \
double	stat_aad_##NAME(const TYPE * values, unsigned int length, TYPE center) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += (value - center); \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Arithmetic%E2%80%93geometric_mean */ \
double	stat_agm_##NAME(TYPE x, TYPE y) \
{ \
	double a, a_n; \
	double g, g_n; \
	if(x>y)	{	a = x;	g = y;	} \
	else	{	a = y;	g = x;	} \
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
double	stat_msd_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	error; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (expect[i] - value); \
		sum += (double)error; \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_squared_error */ \
double	stat_mse_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	error; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (value - expect[i]); \
		sum += (double)error * (double)error; \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_error */ \
double	stat_mae_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	error; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (expect[i] - value); \
		sum += fabs((double)error); \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_difference */ \
double	stat_md_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	error; \
	double*	pairs = (double*)malloc(length * sizeof(double)); \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (expect[i] - value); \
		pairs[n] = fabs((double)error); \
		n++; \
	} \
	double	result = stat_mean_arithmetic_f64(pairs, n); \
	free(pairs); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_difference#Relative_mean_absolute_difference */ \
double	stat_rmd_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	return (stat_md_##NAME(values, expect, length) / stat_mean_arithmetic_##NAME(values, length)); \
} \
/*! https://en.wikipedia.org/wiki/Root_mean_square_deviation */ \
double	stat_rmsd_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	return sqrt(stat_mse_##NAME(values, expect, length)); \
} \
/*! https://en.wikipedia.org/wiki/Mean_percentage_error */ \
double	stat_mpe_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += ((double)value - expect[i]) / value; \
		n++; \
	} \
	return (sum / n) * 100.; \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_percentage_error */ \
double	stat_mape_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		sum += fabs(((double)value - expect[i]) / value); \
		n++; \
	} \
	return (sum / n) * 100.; \
} \
/*! https://en.wikipedia.org/wiki/Mean_squared_prediction_error */ \
double	stat_mspe_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	error; \
	double	sum = 0.; \
	unsigned int	n = 0; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (value - expect[i]); \
		sum += (double)error; \
		n++; \
	} \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Residual_sum_of_squares */ \
double	stat_rss_##NAME(const TYPE * values, const TYPE * expect, unsigned int length) \
{ \
	TYPE	value; \
	TYPE	error; \
	double	sum = 0.; \
	for (unsigned int i = 0; i < length ; ++i) \
	{ \
		value = values[i]; \
		if (CHECK_INVALID)	continue; \
		error = (value - expect[i]); \
		sum += (double)error * (double)error; \
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

DEFINEFUNCTIONS_STATS(UINT , uint , t_uint,  (LIBCONFIG_UINT_NAN  ? (value ==  UINT_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(U8   , u8   , t_u8,    (LIBCONFIG_UINT_NAN  ? (value ==    U8_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(U16  , u16  , t_u16,   (LIBCONFIG_UINT_NAN  ? (value ==   U16_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(U32  , u32  , t_u32,   (LIBCONFIG_UINT_NAN  ? (value ==   U32_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(U64  , u64  , t_u64,   (LIBCONFIG_UINT_NAN  ? (value ==   U64_ERROR) : FALSE))
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(U128 , u128 , t_u128,  (LIBCONFIG_UINT_NAN  ? (value ==  U128_ERROR) : FALSE))
#endif
DEFINEFUNCTIONS_STATS(SINT , sint , t_sint,  (LIBCONFIG_SINT_NAN  ? (value ==  SINT_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(S8   , s8   , t_s8,    (LIBCONFIG_SINT_NAN  ? (value ==    S8_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(S16  , s16  , t_s16,   (LIBCONFIG_SINT_NAN  ? (value ==   S16_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(S32  , s32  , t_s32,   (LIBCONFIG_SINT_NAN  ? (value ==   S32_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(S64  , s64  , t_s64,   (LIBCONFIG_SINT_NAN  ? (value ==   S64_ERROR) : FALSE))
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(S128 , s128 , t_s128,  (LIBCONFIG_SINT_NAN  ? (value ==  S128_ERROR) : FALSE))
#endif
DEFINEFUNCTIONS_STATS(FIXED, fixed, t_fixed, (LIBCONFIG_FIXED_NAN ? (value == FIXED_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(Q16  , q16  , t_q16,   (LIBCONFIG_FIXED_NAN ? (value ==   Q16_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(Q32  , q32  , t_q32,   (LIBCONFIG_FIXED_NAN ? (value ==   Q32_ERROR) : FALSE))
DEFINEFUNCTIONS_STATS(Q64  , q64  , t_q64,   (LIBCONFIG_FIXED_NAN ? (value ==   Q64_ERROR) : FALSE))
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(Q128 , q128 , t_q128,  (LIBCONFIG_FIXED_NAN ? (value ==  Q128_ERROR) : FALSE))
#endif
DEFINEFUNCTIONS_STATS(FLOAT, float, t_float, !isnormal(value))
DEFINEFUNCTIONS_STATS(F32  , f32  , t_f32,   !isnormal(value))
DEFINEFUNCTIONS_STATS(F64  , f64  , t_f64,   !isnormal(value))
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNCTIONS_STATS(F80  , f80  , t_f80,   !isnormal(value))
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNCTIONS_STATS(F128 , f128 , t_f128,  !isnormal(value))
#endif
