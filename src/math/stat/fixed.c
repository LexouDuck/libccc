
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/math/stat.h"
#define NOTYPEDEF // avoid typedef redefinitions
#define T_TYPE	t_fixed
#define T_NAME	fixed
#define T_NULL	0.
#include "libccc/monad/array.c"

#include LIBCONFIG_ERROR_INCLUDE



#define TYPE		t_fixed
#define IS_ERROR(x)	(LIBCONFIG_FIXED_ERROR && (x) == FIXED_ERROR)



s_array(fixed)	Stat_Fixed_New(t_uint length)
{
	s_array(fixed)	result;

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



void	Stat_Fixed_Delete(s_array(fixed) *qlst)
{
	if CCCERROR((qlst == NULL), ERROR_NULLPOINTER, "array of fixed-point numbers given is NULL")
		return;
	if (qlst->items)
	{
		Memory_Free(qlst->items);
		qlst->items = NULL;
	}
	qlst->length = 0;
}



s_array(fixed)	Stat_Fixed_Duplicate(s_array(fixed) const qlst)
{
	s_array(fixed)	result;

	result = Stat_Fixed_New(qlst.length);
	if (!result.items)
		return (result);
	for (t_uint i = 0; i < result.length; ++i)
	{
		result.items[i] = qlst.items[i];
	}
	return (result);
}



s_array(fixed) 	Stat_Fixed_Concat(
	s_array(fixed) *start,
	s_array(fixed) *append)
{
	s_array(fixed)	result;
	t_uint	i;
	t_uint	j;

	if CCCERROR((start == NULL), ERROR_NULLPOINTER, "array of fixed-point numbers given is NULL")
		return ((s_array(fixed)){ 0, NULL });
	if CCCERROR((append == NULL), ERROR_NULLPOINTER, "array of fixed-point numbers to append given is NULL")
		return ((s_array(fixed)){ 0, NULL });
	if (start->length == 0 && append->length == 0)
		return (Stat_Fixed_New(0));
	else if (!start->items || start->length == 0)
		return (*append);
	else if (!append->items || append->length == 0)
		return (*start);
	result = Stat_Fixed_New(start->length + append->length);
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
	Stat_Fixed_Delete(start);
	Stat_Fixed_Delete(append);
	return (result);
}



t_uint	Stat_Fixed_Count(s_array(fixed) qlst, TYPE elem)
{
	t_uint	i;
	t_uint	result;

	i = 0;
	result = 0;
	while (i < qlst.length)
	{
		if (qlst.items[i] == elem)
			++result;
		++i;
	}
	return (result);
}



s_set_fixed	Stat_Fixed_ToSet(s_array(fixed) const qlst)
{
	s_array(fixed)	result;
	s_array(fixed)	set;
	t_uint	i;
	t_uint	j;

	set = Stat_Fixed_New(qlst.length);
	set.length = 0;
	i = 0;
	while (i < qlst.length)
	{
		j = 0;
		while (j < set.length)
		{
			if (set.items[j] == qlst.items[i])
				break;
			++j;
		}
		if (j == set.length)
			set.items[(set.length)++] = qlst.items[i];
		++i;
	}
	result = Stat_Fixed_New(set.length);
	Memory_Copy(result.items, set.items, set.length * sizeof(TYPE));
	Memory_Free(set.items);
	return (result);
}



s_prob_mass	Stat_Fixed_ToPMF(s_array(fixed) const qlst)
{
	s_prob_mass	result;
	s_array(fixed)	set;
	t_uint	i;
	t_float	inv_sample_size;

	if (qlst.items == NULL || qlst.length == 0)
		return (Stat_ProbMassFunc_New(0));
	set = Stat_Fixed_ToSet(qlst);
	result = Stat_ProbMassFunc_New(set.length);
	i = 0;
	inv_sample_size = 1.0 / qlst.length;
	while (i < result.length)
	{
		result.value[i] = (t_float)set.items[i];
		result.prob[i] = (t_float)Stat_Fixed_Count(qlst, set.items[i]);
		result.prob[i] *= inv_sample_size;
		++i;
	}
	Stat_Fixed_Delete(&set);
	return (result);
}



/*
**	Both indices provided are to be included in those written to.
**	The recursive function can be called with start at 0 and end at
**	tmp_lst.length - 1 to sort in place.
*/
static
void	Stat_Fixed_Quicksort_Recurse(
	s_array(fixed)	tmp_lst,
	t_uint			start,
	t_uint			end)
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
		Stat_Fixed_Quicksort_Recurse(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		Stat_Fixed_Quicksort_Recurse(tmp_lst, pivot_id + 1, end);
}

void	Stat_Fixed_Quicksort_InPlace(s_array(fixed) qlst)
{
	Stat_Fixed_Quicksort_Recurse(qlst, 0, qlst.length - 1);
}

s_array(fixed) 	Stat_Fixed_Quicksort(s_array(fixed) const qlst)
{
	s_array(fixed)	result;

	if (qlst.length <= 1)
		return (qlst);
	result = Stat_Fixed_Duplicate(qlst);
	Stat_Fixed_Quicksort_Recurse(result, 0, qlst.length - 1);
	return (result);
}



t_fixed	Stat_Fixed_GetMin(s_array(fixed) const values)
{
	t_float result = +INF;
	for (t_uint i = 0; i < values.length; ++i)
	{
		if (IS_ERROR(values.items[i]))
			continue;
		if (result > values.items[i])
			result = values.items[i];
	}
	return (result);
}

t_fixed	Stat_Fixed_GetMax(s_array(fixed) const values)
{
	t_float result = -INF;
	for (t_uint i = 0; i < values.length; ++i)
	{
		if (IS_ERROR(values.items[i]))
			continue;
		if (result < values.items[i])
			result = values.items[i];
	}
	return (result);
}



extern inline
t_fixed	Stat_Fixed_Median(s_sorted_fixed const qlst)
{
	return ((qlst.length % 2) ?
		qlst.items[qlst.length / 2] :
		(qlst.items[qlst.length / 2] + qlst.items[qlst.length / 2 + 1]) / 2);
}



t_float	Stat_Fixed_Average(s_array(fixed) const qlst)
{
	t_float inv_len;
	t_float	sum;
	t_uint	i;

	sum = 0.;
	i = 0;
	inv_len = (1. / qlst.length);
	while (i < qlst.length)
	{
		sum += inv_len * qlst.items[i];
		++i;
	}
	return (sum);
}



/*
**	Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more operations (n subtractions).
*/
t_float	Stat_Fixed_Variance(s_array(fixed) const qlst)
{
	TYPE	sum;
	t_uint	i;
	TYPE	average;
	TYPE	tmp;

	average = Stat_Fixed_Average(qlst);
	sum = 0;
	i = 0;
	while (i < qlst.length)
	{
		tmp = qlst.items[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));
}



extern inline
t_float	Stat_Fixed_StandardDeviation(s_array(fixed) const qlst)
{
	return Float_Root2(Stat_Fixed_Variance(qlst));
}



void	Stat_Fixed_Decile(s_array(fixed) const qlst)
{
	return; // TODO implement
}



t_bool	Stat_Fixed_ProbabilityIsValid(s_array(fixed) const prob_qlst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_uint		i;

	prob_sum = 0.;
	i = 0;
	while (i < prob_qlst.length)
	{
		tmp = prob_qlst.items[i];
		if CCCERROR((tmp < 0. || 1. < tmp), ERROR_INVALIDRANGE,
			"Probability %f at index %d is out of [0, 1]\n", tmp, i)
			return (FALSE);
		prob_sum += tmp;
		++i;
	}
	if CCCERROR((Float_Abs(prob_sum - 1.) > PROB_APPROX), ERROR_INVALIDRANGE,
		"Probability sum %s is too far from 1.\n", prob_sum)
		return (FALSE);
	return (TRUE);
}
