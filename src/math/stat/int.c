
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/math/stat.h"
#define NOTYPEDEF // avoid typedef redefinitions
#define T_TYPE	t_sint
#define T_NAME	int
#define T_NULL	0
#include "libccc/monad/array.c"

#include LIBCONFIG_ERROR_INCLUDE



#define TYPE		t_sint
#define IS_ERROR(x)	(LIBCONFIG_SINT_ERROR && (x) == SINT_ERROR)



s_array(int)	Stat_Int_New(t_uint length)
{
	s_array(int)	result;

	result.items = NULL;
	result.length = 0;
	if (length == 0)
		return (result);
	result.items = (TYPE*)Memory_Allocate(sizeof(TYPE) * length);
	if CCCERROR((result.items == NULL), ERROR_ALLOCFAILURE, NULL)
		return (result);
	result.length = length;
	return (result);
}



void	Stat_Int_Delete(s_array(int) *ilst)
{
	if CCCERROR((ilst == NULL), ERROR_NULLPOINTER, "array of integers given is NULL")
		return;
	if (ilst->items)
	{
		Memory_Free(ilst->items);
		ilst->items = NULL;
	}
	ilst->length = 0;
}



s_array(int)	Stat_Int_Duplicate(s_array(int) const ilst)
{
	s_array(int)	result;

	result = Stat_Int_New(ilst.length);
	if (!result.items)
		return (result);
	for (t_uint i = 0; i < result.length; ++i)
	{
		result.items[i] = ilst.items[i];
	}
	return (result);
}



s_array(int)	Stat_Int_Concat(
	s_array(int) *start,
	s_array(int) *append)
{
	s_array(int)			result;
	t_uint				i;
	t_uint				j;

	if CCCERROR((start  == NULL), ERROR_NULLPOINTER, "array of integers given is NULL")
		return ((s_array(int)){ 0, NULL });
	if CCCERROR((append == NULL), ERROR_NULLPOINTER, "array of integers to append to given is NULL")
		return ((s_array(int)){ 0, NULL });
	if (start->length == 0 && append->length == 0)
		return (Stat_Int_New(0));
	else if (!start->items || start->length == 0)
		return (*append);
	else if (!append->items || append->length == 0)
		return (*start);
	result = Stat_Int_New(start->length + append->length);
	if (!(result.items))
		return (result);

	for (i = 0; i < start->length; ++i)
	{
		result.items[i] = start->items[i];
	}
	for (j = 0; i < result.length; ++i, ++j)
	{
		result.items[i] = append->items[j];
	}
	Stat_Int_Delete(start);
	Stat_Int_Delete(append);
	return (result);
}



t_uint	Stat_Int_Count(s_array(int) ilst, TYPE elem)
{
	t_uint	i;
	t_uint	result;

	i = 0;
	result = 0;
	while (i < ilst.length)
	{
		if (ilst.items[i] == elem)
			++result;
		++i;
	}
	return (result);
}



s_set_int	Stat_Int_ToSet(s_array(int) const ilst)
{
	s_array(int)	result;
	s_array(int)	set;
	t_uint		i;
	t_uint		j;

	set = Stat_Int_New(ilst.length);
	set.length = 0;
	i = 0;
	while (i < ilst.length)
	{
		j = 0;
		while (j < set.length)
		{
			if (set.items[j] == ilst.items[i])
				break;
			++j;
		}
		if (j == set.length)
			set.items[(set.length)++] = ilst.items[i];
		++i;
	}
	result = Stat_Int_New(set.length);
	Memory_Copy(result.items, set.items, set.length * sizeof(TYPE));
	Memory_Free(set.items);
	return (result);
}



s_prob_mass	Stat_Int_ToPMF(s_array(int) const ilst)
{
	s_prob_mass	result;
	s_array(int)	set;
	t_uint		i;
	t_float		inv_sample_size;

	if (ilst.items == NULL || ilst.length == 0)
		return (Stat_ProbMassFunc_New(0));
	set = Stat_Int_ToSet(ilst);
	result = Stat_ProbMassFunc_New(set.length);
	i = 0;
	inv_sample_size = 1.0 / ilst.length;
	while (i < result.length)
	{
		result.value[i] = (t_float)set.items[i];
		result.prob[i] = (t_float)Stat_Int_Count(ilst, set.items[i]);
		result.prob[i] *= inv_sample_size;
		++i;
	}
	Stat_Int_Delete(&set);
	return (result);
}



/*
**	Both indices provided are to be included in those written to.
**	The recursive function can be called with start at 0 and end at
**	tmp_lst.length - 1 to sort in place.
*/
static
void	Stat_Int_Quicksort_Recurse(
	s_array(int)	tmp_lst,
	t_uint		start,
	t_uint		end)
{
	TYPE	pivot;
	t_uint	pivot_id;
	t_uint	rise_id;
	t_uint	fall_id;

	pivot = tmp_lst.items[start];
	if (start >= end || IS_ERROR(pivot))
		return;
	if (start == end - 1)
	{
		if (pivot > tmp_lst.items[end])
			Memory_Swap(tmp_lst.items + start, tmp_lst.items + end, sizeof(TYPE));
		return;
	}

	rise_id = start + 1;
	fall_id = end;
	while (rise_id < fall_id)
	{
		while (rise_id <= end && tmp_lst.items[rise_id] <= pivot)
		{
			++rise_id;
		}
		while (fall_id > start && tmp_lst.items[fall_id] > pivot)
		{
			--fall_id;
		}
		if (rise_id < fall_id)
			Memory_Swap(tmp_lst.items + rise_id, tmp_lst.items + fall_id, sizeof(TYPE));
	}
	pivot_id = fall_id;
	if (start != fall_id)
		Memory_Swap(tmp_lst.items + start, tmp_lst.items + fall_id, sizeof(TYPE));

	if (pivot_id > start)
		Stat_Int_Quicksort_Recurse(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		Stat_Int_Quicksort_Recurse(tmp_lst, pivot_id + 1, end);
}

void	Stat_Int_Quicksort_InPlace(s_array(int) ilst)
{
	Stat_Int_Quicksort_Recurse(ilst, 0, ilst.length - 1);
}

s_array(int)	Stat_Int_Quicksort(s_array(int) const ilst)
{
	s_array(int)	result;

	if (ilst.length <= 1)
		return (ilst);
	result = Stat_Int_Duplicate(ilst);
	Stat_Int_Quicksort_Recurse(result, 0, ilst.length - 1);
	return (result);
}



t_sint	Stat_Int_GetMin(s_array(int) const values)
{
	t_sint result = SINT_MAX;
	for (t_uint i = 0; i < values.length; ++i)
	{
		if (IS_ERROR(values.items[i]))
			continue;
		if (result > values.items[i])
			result = values.items[i];
	}
	return (result);
}

t_sint	Stat_Int_GetMax(s_array(int) const values)
{
	t_sint result = SINT_MIN;
	for (t_uint i = 0; i < values.length; ++i)
	{
		if (IS_ERROR(values.items[i]))
			continue;
		if (result < values.items[i])
			result = values.items[i];
	}
	return (result);
}



_INLINE()
t_sint	Stat_Int_Median(s_sorted_int const ilst)
{
	return ((ilst.length % 2) ?
		ilst.items[ilst.length / 2] :
		(ilst.items[ilst.length / 2] + ilst.items[ilst.length / 2 + 1]) / 2);
}



t_float	Stat_Int_Average(s_array(int) const ilst)
{
	t_float	inv_len;
	t_float	sum;
	t_uint	i;

	sum = 0;
	i = 0;
	inv_len = (1. / ilst.length);
	while (i < ilst.length)
	{
		sum += inv_len * ilst.items[i];
		++i;
	}
	return (sum);
}



/*
**	Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more operations (n subtractions).
*/
t_float	Stat_Int_Variance(s_array(int) const ilst)
{
	t_float	sum;
	t_uint	i;
	t_float	average;
	t_float	tmp;

	average = Stat_Int_Average(ilst);
	sum = 0;
	i = 0;
	while (i < ilst.length)
	{
		tmp = ilst.items[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));
}



_INLINE()
t_float	Stat_Int_StandardDeviation(s_array(int) const ilst)
{
	return Float_Root2(Stat_Int_Variance(ilst));
}


/* TODO implement
void	Stat_Int_Decile(s_array_int const ilst)
{
	return;
}
*/


t_bool	Stat_Int_ProbabilityIsValid(s_array(int) const prob_ilst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_uint		i;

	prob_sum = 0.;
	i = 0;
	while (i < prob_ilst.length)
	{
		tmp = prob_ilst.items[i];
		if CCCERROR((tmp < 0. || 1. < tmp), ERROR_INVALIDRANGE,
			"Probability %f at index %d is out of [0, 1]\n", tmp, i)
			return (FALSE);
		prob_sum += tmp;
		++i;
	}
	if CCCERROR((SInt_Abs(prob_sum - 1.) > PROB_APPROX), ERROR_INVALIDRANGE,
		"Probability sum %s is too far from 1.\n", prob_sum)
		return (FALSE);
	return (TRUE);
}
