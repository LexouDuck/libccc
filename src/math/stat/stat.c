
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/math/int.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"
#include "libccc/math/stat.h"
#include "libccc/math/sort.h"

#define NOTYPEDEF // avoid typedef redefinitions

#define T_TYPE	t_uint
#define T_NAME	uint
#define T_NULL	0
#define T_EQUALS(X,Y)	UInt_Equals((X), (Y))
#include "libccc/generic/array.c"

#define T_TYPE	t_sint
#define T_NAME	sint
#define T_NULL	0
#define T_EQUALS(X,Y)	SInt_Equals((X), (Y))
#include "libccc/generic/array.c"

#define T_TYPE	t_fixed
#define T_NAME	fixed
#define T_NULL	(t_fixed){ 0 }
#define T_EQUALS(X,Y)	Fixed_Equals((X), (Y))
#include "libccc/generic/array.c"

#define T_TYPE	t_float
#define T_NAME	float
#define T_NULL	0.
#define T_EQUALS(X,Y)	Float_Equals((X), (Y))
#include "libccc/generic/array.c"

#include LIBCONFIG_ERROR_INCLUDE



s_prob_mass	Stat_ProbabilityMassFunction_New(t_uint length)
{
	s_prob_mass	result;

	result.value = NULL;
	result.prob = NULL;
	result.length = 0;
	if (length == 0)	return (result);
	result.value = (t_float*)Memory_Allocate(length * sizeof(t_float));
	if CCCERROR((result.value == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	result.prob = (t_float*)Memory_Allocate(length * sizeof(t_float));
	if CCCERROR((result.prob == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	result.length = length;
	return (result);
}



void	Stat_ProbabilityMassFunction_Delete(s_prob_mass *drv)
{
	if CCCERROR((drv == NULL), ERROR_NULLPOINTER, NULL)
		return;
	if (drv->value)
	{
		Memory_Free(drv->value);
		drv->value = NULL;
	}
	if (drv->prob)
	{
		Memory_Free(drv->prob);
		drv->prob = NULL;
	}
	drv->length = 0;
}



#define DEFINEFUNCTIONS_STATS(TYPE, TYPE_LOWER, TYPE_MIXED, TYPE_UPPER, CHECK_INVALID) \
/*!  */ \
s_array(TYPE_LOWER)	Stat_##TYPE_MIXED##_New(t_uint length) \
{ \
	s_array(TYPE_LOWER)	result; \
	result.items = NULL; \
	result.length = 0; \
	if (length == 0) \
		return (result); \
	result.items = (TYPE*)Memory_Allocate(length * sizeof(TYPE)); \
	if CCCERROR((result.items == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (result); \
	result.length = length; \
	return (result); \
} \
/*!  */ \
void	Stat_##TYPE_MIXED##_Delete(s_array(TYPE_LOWER) *sample) \
{ \
	if CCCERROR((sample == NULL), ERROR_NULLPOINTER, "array of floating-point numbers given is NULL") \
		return; \
	if (sample->items) \
	{ \
		Memory_Free(sample->items); \
		sample->items = NULL; \
	} \
	sample->length = 0; \
} \
/*!  */ \
s_array(TYPE_LOWER)	Stat_##TYPE_MIXED##_Duplicate(s_array(TYPE_LOWER) const sample) \
{ \
	s_array(TYPE_LOWER)	result; \
	result = Stat_##TYPE_MIXED##_New(sample.length); \
	if (!result.items) \
		return (result); \
	for (t_uint i = 0; i < result.length; ++i) \
	{ \
		result.items[i] = sample.items[i]; \
	} \
	return (result); \
} \
/*!  */ \
s_array(TYPE_LOWER)	Stat_##TYPE_MIXED##_Concat( \
	s_array(TYPE_LOWER)* start, \
	s_array(TYPE_LOWER)* append) \
{ \
	s_array(TYPE_LOWER)	result; \
	t_uint	i; \
	t_uint	j; \
	if CCCERROR((start == NULL), ERROR_NULLPOINTER, "array of floating-point numbers given is NULL") \
		return ((s_array(TYPE_LOWER)){ 0, NULL }); \
	if CCCERROR((append == NULL), ERROR_NULLPOINTER, "array of floating-point numbers to append given is NULL") \
		return ((s_array(TYPE_LOWER)){ 0, NULL }); \
	if (start->length == 0 && append->length == 0) \
		return (Stat_##TYPE_MIXED##_New(0)); \
	else if (!start->items || start->length == 0) \
		return (*append); \
	else if (!append->items || append->length == 0) \
		return (*start); \
	result = Stat_##TYPE_MIXED##_New(start->length + append->length); \
	if (!(result.items)) \
		return (result); \
	for (i = 0; i < start->length; ++i) \
	{ \
		result.items[i] = start->items[i]; \
	} \
	for (j = 0; i < result.length; ++i, ++j) \
	{ \
		result.items[i] = append->items[j]; \
	} \
	Stat_##TYPE_MIXED##_Delete(start); \
	Stat_##TYPE_MIXED##_Delete(append); \
	return (result); \
} \
/*!  */ \
t_uint	Stat_##TYPE_MIXED##_Count(s_array(TYPE_LOWER) sample, TYPE elem) \
{ \
	t_uint	i; \
	t_uint	result = 0; \
	if (TYPE_MIXED##_IsNaN(elem)) \
		for (i = 0; i < sample.length; ++i) \
		{ \
			if (TYPE_MIXED##_IsNaN(sample.items[i])) \
				++result; \
		} \
	else \
		for (i = 0; i < sample.length; ++i) \
		{ \
			if (TYPE_MIXED##_Equals(sample.items[i], elem)) \
				++result; \
		} \
	return (result); \
} \
/*!  */ \
s_set_##TYPE_LOWER	Stat_##TYPE_MIXED##_ToSet(s_array(TYPE_LOWER) const sample) \
{ \
	s_array(TYPE_LOWER)	result; \
	s_array(TYPE_LOWER)	set; \
	t_uint	i; \
	t_uint	j; \
	set = Stat_##TYPE_MIXED##_New(sample.length); \
	set.length = 0; \
	for (i = 0; i < sample.length; ++i) \
	{ \
		for (j = 0; j < set.length; ++j) \
		{ \
			if (TYPE_MIXED##_Equals(set.items[j], sample.items[i])) \
				break; \
		} \
		if (j == set.length) \
			set.items[(set.length)++] = sample.items[i]; \
	} \
	result = Stat_##TYPE_MIXED##_New(set.length); \
	Memory_Copy(result.items, set.items, set.length * sizeof(TYPE)); \
	Memory_Free(set.items); \
	return (result); \
} \
 \
static \
t_sint	Stat_##TYPE_MIXED##_Compare(void const* a, void const* b) \
{ \
	TYPE	x = (*(TYPE const*)a); \
	TYPE	y = (*(TYPE const*)b); \
	if (TYPE_MIXED##_IsNaN(x))	return -1; \
	return (Float_Sgn(Float_From##TYPE_MIXED(x) - Float_From##TYPE_MIXED(y))); \
} \
s_array(TYPE_LOWER)	Stat_##TYPE_MIXED##_Sort(s_array(TYPE_LOWER) const sample) \
{ \
	return (s_array(TYPE_LOWER)) \
		{ \
			.length = sample.length, \
			.items = (TYPE*)QuickSort_New(sample.items, sample.length, sizeof(TYPE), Stat_##TYPE_MIXED##_Compare), \
		}; \
} \
void	Stat_##TYPE_MIXED##_Sort_InPlace(s_array(TYPE_LOWER) sample) \
{ \
	QuickSort(sample.items, sample.length, sizeof(TYPE), Stat_##TYPE_MIXED##_Compare); \
} \
/*! https://en.wikipedia.org/wiki/ */ \
s_prob_mass	Stat_##TYPE_MIXED##_ProbabilityMassFunction(s_array(TYPE_LOWER) const sample) \
{ \
	s_prob_mass	result; \
	s_array(TYPE_LOWER)	set; \
	t_uint	i; \
	t_float	inv_sample_size; \
	if (sample.items == NULL || sample.length == 0) \
		return (Stat_ProbabilityMassFunction_New(0)); \
	set = Stat_##TYPE_MIXED##_ToSet(sample); \
	result = Stat_ProbabilityMassFunction_New(set.length); \
	i = 0; \
	inv_sample_size = 1.0 / sample.length; \
	while (i < result.length) \
	{ \
		result.value[i] = Float_From##TYPE_MIXED(set.items[i]); \
		result.prob[i] = (t_float)Stat_##TYPE_MIXED##_Count(sample, set.items[i]); \
		result.prob[i] *= inv_sample_size; \
		++i; \
	} \
	Stat_##TYPE_MIXED##_Delete(&set); \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Sample_maximum_and_minimum */ \
TYPE	Stat_##TYPE_MIXED##_GetMin(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	TYPE	result = TYPE_UPPER##_MAX; \
	for (t_uint i = 0; i < sample.length; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_GreaterThan(result ,/*>*/ value)) \
			result = value; \
	} \
	if CCCERROR(TYPE_MIXED##_Equals(result, TYPE_UPPER##_MAX), ERROR_INVALIDARGS, "no minimum value was found") \
		return (TYPE_UPPER##_ERROR); \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Sample_maximum_and_minimum */ \
TYPE	Stat_##TYPE_MIXED##_GetMax(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	TYPE	result = TYPE_UPPER##_MIN; \
	for (t_uint i = 0; i < sample.length; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_LessThan(result ,/*<*/ value)) \
			result = value; \
	} \
	if CCCERROR(TYPE_MIXED##_Equals(result, TYPE_UPPER##_MIN), ERROR_INVALIDARGS, "no maximum value was found") \
		return (TYPE_UPPER##_ERROR); \
	return (result); \
} \
/*! https://en.wikipedia.org/wiki/Quantile */ \
t_float*	Stat_##TYPE_MIXED##_Quantiles(s_array(TYPE_LOWER) const sample, t_uint n) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	t_float*	result = (t_float*)Memory_Allocate((n + 1) * sizeof(t_float)); \
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NULL); \
	t_uint	position; \
	for (t_uint i = 0; i < n; ++i) \
	{ \
		position = i * sample.length / n; \
		result[i] = ((sample.length - (n - 1)) % n == 0) ? \
			(Float_From##TYPE_MIXED(sample.items[position])) : \
			((Float_From##TYPE_MIXED(sample.items[position]) + Float_From##TYPE_MIXED(sample.items[position + 1])) / 2); \
	} \
	result[n] = Float_From##TYPE_MIXED(sample.items[sample.length - 1]); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Median */ \
t_float	Stat_##TYPE_MIXED##_Median(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	return ((sample.length % 2) ? \
		(Float_From##TYPE_MIXED(sample.items[sample.length / 2])) : \
		((Float_From##TYPE_MIXED(sample.items[sample.length / 2]) + Float_From##TYPE_MIXED(sample.items[sample.length / 2 + 1])) / 2)); \
} \
/*! https://en.wikipedia.org/wiki/Mode_(statistics) */ \
t_float	Stat_##TYPE_MIXED##_Mode(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	TYPE	value; \
	TYPE	result = TYPE_UPPER##_ERROR; \
	TYPE	previous = TYPE_UPPER##_ERROR; \
	t_uint	consecutive_record = 0; \
	t_uint	consecutive_current = 0; \
	for (t_uint i = 0; i < sample.length; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_Equals(previous, value)) \
			consecutive_current++; \
		if (consecutive_record < consecutive_current) \
		{ \
			consecutive_record = consecutive_current; \
			result = value; \
		} \
		previous = value; \
	} \
	return Float_From##TYPE_MIXED(result); \
} \
/*! https://en.wikipedia.org/wiki/Range_(statistics) */ \
t_float	Stat_##TYPE_MIXED##_Range(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	TYPE	value; \
	TYPE	minval = TYPE_UPPER##_MAX; \
	TYPE	maxval = TYPE_UPPER##_MIN; \
	for (t_uint i = 0; i < sample.length; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_GreaterThan(minval,/*>*/ sample.items[i])) \
			minval = sample.items[i]; \
		if (TYPE_MIXED##_LessThan(maxval,/*<*/ sample.items[i])) \
			maxval = sample.items[i]; \
	} \
	if CCCERROR(TYPE_MIXED##_Equals(minval, TYPE_UPPER##_MAX), ERROR_INVALIDARGS, "no minimum value was found") \
		return (NAN); \
	if CCCERROR(TYPE_MIXED##_Equals(maxval, TYPE_UPPER##_MIN), ERROR_INVALIDARGS, "no maximum value was found") \
		return (NAN); \
	return Float_Sub(Float_From##TYPE_MIXED(maxval), Float_From##TYPE_MIXED(minval)); \
} \
/*! https://en.wikipedia.org/wiki/Midrange */ \
t_float	Stat_##TYPE_MIXED##_Midrange(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	TYPE	value; \
	TYPE	minval = TYPE_UPPER##_MAX; \
	TYPE	maxval = TYPE_UPPER##_MIN; \
	for (t_uint i = 0; i < sample.length; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_GreaterThan(minval,/*>*/ sample.items[i])) \
			minval = sample.items[i]; \
		if (TYPE_MIXED##_LessThan(maxval,/*<*/ sample.items[i])) \
			maxval = sample.items[i]; \
	} \
	if CCCERROR(TYPE_MIXED##_Equals(minval, TYPE_UPPER##_MAX), ERROR_INVALIDARGS, "no minimum value was found") \
		return (NAN); \
	if CCCERROR(TYPE_MIXED##_Equals(maxval, TYPE_UPPER##_MIN), ERROR_INVALIDARGS, "no maximum value was found") \
		return (NAN); \
	return ((Float_From##TYPE_MIXED(minval) + Float_From##TYPE_MIXED(maxval)) / 2.); \
} \
/*! https://en.wikipedia.org/wiki/Midhinge */ \
t_float	Stat_##TYPE_MIXED##_Midhinge(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	t_float*	quartiles = Stat_##TYPE_MIXED##_Quantiles(sample, 4); \
	return (quartiles[1] + quartiles[3]) / 2; \
} \
/*! https://en.wikipedia.org/wiki/Trimean */ \
t_float	Stat_##TYPE_MIXED##_Trimean(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	t_float*	quartiles = Stat_##TYPE_MIXED##_Quantiles(sample, 4); \
	return (quartiles[1] + quartiles[2] + quartiles[2] + quartiles[3]) / 4; \
} \
/*! https://en.wikipedia.org/wiki/Arithmetic_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Arithmetic(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		sum += Float_From##TYPE_MIXED(value); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Geometric_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Geometric(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float	product = 1.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		product *= Float_From##TYPE_MIXED(value); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return Float_Pow(product, 1. / n); \
} \
/*! https://en.wikipedia.org/wiki/Harmonic_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Harmonic(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float	invsum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		invsum += 1. / Float_From##TYPE_MIXED(value); \
		n++; \
	} \
	if CCCERROR((n == 0 || invsum == 0.), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (n / invsum); \
} \
/*! https://en.wikipedia.org/wiki/Contraharmonic_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Contraharmonic(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum1 = 0.; \
	t_float	sum2 = 0.; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum1 += value_float; \
		sum2 += value_float * value_float; \
	} \
	if CCCERROR((sum1 == 0. && sum2 == 0.), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum2 / sum1); \
} \
/*! https://en.wikipedia.org/wiki/Interquartile_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Interquartile(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	t_float*	quartiles = Stat_##TYPE_MIXED##_Quantiles(sample, 4); \
	TYPE	value; \
	t_float	value_float; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		if (value_float < quartiles[1] || value_float > quartiles[3]) \
			continue; \
		sum += value_float; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Quadratic_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Quadratic(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum += value_float * value_float; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (Float_Root2(sum / n)); \
} \
/*! https://en.wikipedia.org/wiki/Cubic_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Cubic(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum += value_float * value_float * value_float; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (Float_Root3(sum / n)); \
} \
/*! https://en.wikipedia.org/wiki/Power_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Power(s_array(TYPE_LOWER) const sample, t_float p) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum += Float_Pow(value_float, p); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (Float_Pow(sum / n, 1 / p)); \
} \
/*! https://en.wikipedia.org/wiki/Lehmer_mean */ \
t_float	Stat_##TYPE_MIXED##_Mean_Lehmer(s_array(TYPE_LOWER) const sample, t_sint power) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum1 = 0.; \
	t_float	sum2 = 0.; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum1 += Float_Pow(value_float, power - 1); \
		sum2 += Float_Pow(value_float, power); \
	} \
	if CCCERROR((sum1 == 0. && sum2 == 0.), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum2 / sum1); \
} \
/*! https://en.wikipedia.org/wiki/Variance */ \
t_float	Stat_##TYPE_MIXED##_Variance(s_array(TYPE_LOWER) const sample) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum = 0.; \
	t_float	average = Stat_##TYPE_MIXED##_Mean_Arithmetic(sample); \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum += value_float * value_float; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return ((sum / n) - (average * average)); \
} \
/*! https://en.wikipedia.org/wiki/Standard_deviation */ \
t_float	Stat_##TYPE_MIXED##_StandardDeviation(s_array(TYPE_LOWER) const sample) \
{ \
	return Float_Root2(Stat_##TYPE_MIXED##_Variance(sample)); \
} \
/*! https://en.wikipedia.org/wiki/Coefficient_of_variation */ \
t_float	Stat_##TYPE_MIXED##_CoefficientOfVariation(s_array(TYPE_LOWER) const sample) \
{ \
	t_float average = Stat_##TYPE_MIXED##_Mean_Arithmetic(sample); \
	if CCCERROR((average == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (Stat_##TYPE_MIXED##_StandardDeviation(sample) / average); \
} \
/*! https://en.wikipedia.org/wiki/Interquartile_range */ \
t_float	Stat_##TYPE_MIXED##_InterquartileRange(s_array(TYPE_LOWER) const sample) \
{ \
	/* if (sort)	quicksort_##TYPE_LOWER(sample.items, 0, sample.length); */ \
	t_float*	quartiles = Stat_##TYPE_MIXED##_Quantiles(sample, 4); \
	return (quartiles[3] - quartiles[1]); \
} \
/*! https://en.wikipedia.org/wiki/Median_absolute_deviation */ \
t_float	Stat_##TYPE_MIXED##_MedianAbsoluteDeviation(s_array(TYPE_LOWER) const sample) \
{ \
	t_float*	pairs = (t_float*)Memory_Allocate(sample.length * sizeof(t_float)); \
	if CCCERROR((pairs == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NAN); \
	t_float	median = Stat_##TYPE_MIXED##_Median(sample); \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		pairs[i] = Float_Abs(Float_From##TYPE_MIXED(sample.items[i]) - median); \
	} \
	t_float	result = Stat_Float_Median((s_array(float)){ .length = sample.length, .items = pairs }); \
	Memory_Free(pairs); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Average_absolute_deviation */ \
t_float	Stat_##TYPE_MIXED##_AverageAbsoluteDeviation(s_array(TYPE_LOWER) const sample, TYPE center) \
{ \
	TYPE	value; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		sum += Float_From##TYPE_MIXED(value) - Float_From##TYPE_MIXED(center); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Arithmetic%E2%80%93geometric_mean */ \
t_float	Stat_##TYPE_MIXED##_ArithmeticGeometricMean(TYPE x, TYPE y) \
{ \
	t_float a, a_n; \
	t_float g, g_n; \
	if (TYPE_MIXED##_GreaterThan(x ,/*>*/ y)) \
		{	a = Float_From##TYPE_MIXED(x);	g = Float_From##TYPE_MIXED(y);	} \
	else{	a = Float_From##TYPE_MIXED(y);	g = Float_From##TYPE_MIXED(x);	} \
	while (a != g) \
	{ \
		a_n = (a + g) * 0.5; \
		g_n = Float_Root2(a * g); \
		a = a_n; \
		g = g_n; \
	} \
	return a; \
} \
/*! https://en.wikipedia.org/wiki/Mean_signed_deviation */ \
t_float	Stat_##TYPE_MIXED##_MeanSignedDeviation(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float	error; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		error = Float_From##TYPE_MIXED(expect[i]) - Float_From##TYPE_MIXED(value); \
		sum += error; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_squared_error */ \
t_float	Stat_##TYPE_MIXED##_MeanSquaredError(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float	error; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		error = Float_From##TYPE_MIXED(value) - Float_From##TYPE_MIXED(expect[i]); \
		sum += error * error; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_error */ \
t_float	Stat_##TYPE_MIXED##_MeanAbsoluteError(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float	error; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		error = Float_From##TYPE_MIXED(expect[i]) - Float_From##TYPE_MIXED(value); \
		sum += Float_Abs(error); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_difference */ \
t_float	Stat_##TYPE_MIXED##_MeanAbsoluteDifference(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float	error; \
	t_float*	pairs = (t_float*)Memory_Allocate(sample.length * sizeof(t_float)); \
	if CCCERROR((pairs == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NAN); \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		error = Float_From##TYPE_MIXED(expect[i]) - Float_From##TYPE_MIXED(value); \
		pairs[n] = Float_Abs(error); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	t_float	result = Stat_Float_Mean_Arithmetic((s_array(float)){ .length = n, .items = pairs }); \
	Memory_Free(pairs); \
	return result; \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_difference#Relative_mean_absolute_difference */ \
t_float	Stat_##TYPE_MIXED##_RelativeMeanAbsoluteDifference(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	return (Stat_##TYPE_MIXED##_MeanAbsoluteDifference(sample, expect) / Stat_##TYPE_MIXED##_Mean_Arithmetic(sample)); \
} \
/*! https://en.wikipedia.org/wiki/Root_mean_square_deviation */ \
t_float	Stat_##TYPE_MIXED##_RootMeanSquareDeviation(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	return Float_Root2(Stat_##TYPE_MIXED##_MeanSquaredError(sample, expect)); \
} \
/*! https://en.wikipedia.org/wiki/Mean_percentage_error */ \
t_float	Stat_##TYPE_MIXED##_MeanPercentageError(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_Equals(value, TYPE_MIXED##_FromSInt(0)))	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum += (value_float - Float_From##TYPE_MIXED(expect[i])) / value_float; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n) * 100.; \
} \
/*! https://en.wikipedia.org/wiki/Mean_absolute_percentage_error */ \
t_float	Stat_##TYPE_MIXED##_MeanAbsolutePercentageError(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float value_float; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		if (TYPE_MIXED##_Equals(value, TYPE_MIXED##_FromSInt(0)))	continue; \
		value_float = Float_From##TYPE_MIXED(value); \
		sum += Float_Abs((value_float - Float_From##TYPE_MIXED(expect[i])) / value_float); \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n) * 100.; \
} \
/*! https://en.wikipedia.org/wiki/Mean_squared_prediction_error */ \
t_float	Stat_##TYPE_MIXED##_MeanSquaredPredictionError(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float	error; \
	t_float	sum = 0.; \
	t_uint	n = 0; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		error = Float_From##TYPE_MIXED(value) - Float_From##TYPE_MIXED(expect[i]); \
		sum += error; \
		n++; \
	} \
	if CCCERROR((n == 0), ERROR_INVALIDARGS, "invalid sample given") \
		return (NAN); \
	return (sum / n); \
} \
/*! https://en.wikipedia.org/wiki/Residual_sum_of_squares */ \
t_float	Stat_##TYPE_MIXED##_ResidualSumOfSquares(s_array(TYPE_LOWER) const sample, TYPE const* expect) \
{ \
	TYPE	value; \
	t_float	error; \
	t_float	sum = 0.; \
	for (t_uint i = 0; i < sample.length ; ++i) \
	{ \
		value = sample.items[i]; \
		if (CHECK_INVALID)	continue; \
		error = Float_From##TYPE_MIXED(value) - Float_From##TYPE_MIXED(expect[i]); \
		sum += error * error; \
	} \
	return (sum); \
} \
/*! https://en.wikipedia.org/wiki/Squared_deviations_from_the_mean */ \
/*TODO*/



DEFINEFUNCTIONS_STATS(t_uint,  uint , UInt , UINT , (  UInt_IsNaN(value) ||  UInt_IsInf(value) ))
/*
DEFINEFUNCTIONS_STATS(t_u8,    u8   , U8   , U8   , (    U8_IsNaN(value) ||    U8_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_u16,   u16  , U16  , U16  , (   U16_IsNaN(value) ||   U16_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_u32,   u32  , U32  , U32  , (   U32_IsNaN(value) ||   U32_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_u64,   u64  , U64  , U64  , (   U64_IsNaN(value) ||   U64_IsInf(value) ))
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(t_u128,  u128 , U128 , U128 , (  U128_IsNaN(value) ||  U128_IsInf(value) ))
#endif
*/

DEFINEFUNCTIONS_STATS(t_sint,  sint , SInt , SINT , (  SInt_IsNaN(value) ||  SInt_IsInf(value) ))
/*
DEFINEFUNCTIONS_STATS(t_s8,    s8   , S8   , S8   , (    S8_IsNaN(value) ||    S8_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_s16,   s16  , S16  , S16  , (   S16_IsNaN(value) ||   S16_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_s32,   s32  , S32  , S32  , (   S32_IsNaN(value) ||   S32_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_s64,   s64  , S64  , S64  , (   S64_IsNaN(value) ||   S64_IsInf(value) ))
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(t_s128,  s128 , S128 , S128 , (  S128_IsNaN(value) ||  S128_IsInf(value) ))
#endif
*/

DEFINEFUNCTIONS_STATS(t_fixed, fixed, Fixed, FIXED, ( Fixed_IsNaN(value) || Fixed_IsInf(value) ))
/*
DEFINEFUNCTIONS_STATS(t_q16,   q16  , Q16  , Q16  , (   Q16_IsNaN(value) ||   Q16_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_q32,   q32  , Q32  , Q32  , (   Q32_IsNaN(value) ||   Q32_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_q64,   q64  , Q64  , Q64  , (   Q64_IsNaN(value) ||   Q64_IsInf(value) ))
#if LIBCONFIG_USE_INT128
DEFINEFUNCTIONS_STATS(t_q128,  q128 , Q128 , Q128 , (  Q128_IsNaN(value) ||  Q128_IsInf(value) ))
#endif
*/

DEFINEFUNCTIONS_STATS(t_float, float, Float, FLOAT, ( Float_IsNaN(value) || Float_IsInf(value) ))
/*
DEFINEFUNCTIONS_STATS(t_f32,   f32  , F32  , F32  , (   F32_IsNaN(value) ||   F32_IsInf(value) ))
DEFINEFUNCTIONS_STATS(t_f64,   f64  , F64  , F64  , (   F64_IsNaN(value) ||   F64_IsInf(value) ))
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNCTIONS_STATS(t_f80,   f80  , F80  , F80  , (   F80_IsNaN(value) ||   F80_IsInf(value) ))
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNCTIONS_STATS(t_f128,  f128 , F128 , F128 , (  F128_IsNaN(value) ||  F128_IsInf(value) ))
#endif
*/

