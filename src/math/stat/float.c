
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/math/stat.h"
#define NOTYPEDEF // avoid typedef redefinitions
#define T_TYPE	t_float
#define T_NAME	float
#define T_NULL	0.
#include "libccc/monad/array.c"

#include LIBCONFIG_ERROR_INCLUDE



#define TYPE		t_float
#define IS_ERROR(x)	(IS_NAN(x))



s_array(float)	Stat_Float_New(t_uint length)
{
	s_array(float)	result;

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



void	Stat_Float_Delete(s_array(float) *flst)
{
	if CCCERROR((flst == NULL), ERROR_NULLPOINTER, "array of floating-point numbers given is NULL")
		return;
	if (flst->items)
	{
		Memory_Free(flst->items);
		flst->items = NULL;
	}
	flst->length = 0;
}



s_array(float)	Stat_Float_Duplicate(s_array(float) const flst)
{
	s_array(float)	result;

	result = Stat_Float_New(flst.length);
	if (!result.items)
		return (result);
	for (t_uint i = 0; i < result.length; ++i)
	{
		result.items[i] = flst.items[i];
	}
	return (result);
}



s_array(float) 	Stat_Float_Concat(
	s_array(float) *start,
	s_array(float) *append)
{
	s_array(float)	result;
	t_uint	i;
	t_uint	j;

	if CCCERROR((start == NULL), ERROR_NULLPOINTER, "array of floating-point numbers given is NULL")
		return ((s_array(float)){ 0, NULL });
	if CCCERROR((append == NULL), ERROR_NULLPOINTER, "array of floating-point numbers to append given is NULL")
		return ((s_array(float)){ 0, NULL });
	if (start->length == 0 && append->length == 0)
		return (Stat_Float_New(0));
	else if (!start->items || start->length == 0)
		return (*append);
	else if (!append->items || append->length == 0)
		return (*start);
	result = Stat_Float_New(start->length + append->length);
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
	Stat_Float_Delete(start);
	Stat_Float_Delete(append);
	return (result);
}



t_uint	Stat_Float_Count(s_array(float) flst, TYPE elem)
{
	t_uint	i;
	t_uint	result;

	i = 0;
	result = 0;
	while (i < flst.length)
	{
		if (flst.items[i] == elem)
			++result;
		++i;
	}
	return (result);
}



s_set_float	Stat_Float_ToSet(s_array(float) const flst)
{
	s_array(float)	result;
	s_array(float)	set;
	t_uint	i;
	t_uint	j;

	set = Stat_Float_New(flst.length);
	set.length = 0;
	i = 0;
	while (i < flst.length)
	{
		j = 0;
		while (j < set.length)
		{
			if (set.items[j] == flst.items[i])
				break;
			++j;
		}
		if (j == set.length)
			set.items[(set.length)++] = flst.items[i];
		++i;
	}
	result = Stat_Float_New(set.length);
	Memory_Copy(result.items, set.items, set.length * sizeof(TYPE));
	Memory_Free(set.items);
	return (result);
}



s_prob_mass	Stat_Float_ToPMF(s_array(float) const flst)
{
	s_prob_mass	result;
	s_array(float)	set;
	t_uint	i;
	t_float	inv_sample_size;

	if (flst.items == NULL || flst.length == 0)
		return (Stat_ProbMassFunc_New(0));
	set = Stat_Float_ToSet(flst);
	result = Stat_ProbMassFunc_New(set.length);
	i = 0;
	inv_sample_size = 1.0 / flst.length;
	while (i < result.length)
	{
		result.value[i] = (t_float)set.items[i];
		result.prob[i] = (t_float)Stat_Float_Count(flst, set.items[i]);
		result.prob[i] *= inv_sample_size;
		++i;
	}
	Stat_Float_Delete(&set);
	return (result);
}



/*
**	Both indices provided are to be included in those written to.
**	The recursive function can be called with start at 0 and end at
**	tmp_lst.length - 1 to sort in place.
*/
static
void	Stat_Float_Quicksort_Recurse(
	s_array(float)	tmp_lst,
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
		Stat_Float_Quicksort_Recurse(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		Stat_Float_Quicksort_Recurse(tmp_lst, pivot_id + 1, end);
}

void	Stat_Float_Quicksort_InPlace(s_array(float) flst)
{
	Stat_Float_Quicksort_Recurse(flst, 0, flst.length - 1);
}

s_array(float) 	Stat_Float_Quicksort(s_array(float) const flst)
{
	s_array(float)	result;

	if (flst.length <= 1)
		return (flst);
	result = Stat_Float_Duplicate(flst);
	Stat_Float_Quicksort_Recurse(result, 0, flst.length - 1);
	return (result);
}



t_float	Stat_Float_GetMin(s_array(float) const values)
{
	t_float result = +INF;
	for (t_uint i = 0; i < values.length; ++i)
	{
		if (IS_NAN(values.items[i]))
			continue;
		if (result > values.items[i])
			result = values.items[i];
	}
	return (result);
}

t_float	Stat_Float_GetMax(s_array(float) const values)
{
	t_float result = -INF;
	for (t_uint i = 0; i < values.length; ++i)
	{
		if (IS_NAN(values.items[i]))
			continue;
		if (result < values.items[i])
			result = values.items[i];
	}
	return (result);
}



extern inline
t_float	Stat_Float_Median(s_sorted_float const flst)
{
	return ((flst.length % 2) ?
		flst.items[flst.length / 2] :
		(flst.items[flst.length / 2] + flst.items[flst.length / 2 + 1]) / 2);
}



t_float	Stat_Float_Average(s_array(float) const flst)
{
	t_float inv_len;
	t_float	sum;
	t_uint	i;

	sum = 0.;
	i = 0;
	inv_len = (1. / flst.length);
	while (i < flst.length)
	{
		sum += inv_len * flst.items[i];
		++i;
	}
	return (sum);
}



/*
**	Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more operations (n subtractions).
*/
t_float	Stat_Float_Variance(s_array(float) const flst)
{
	TYPE	sum;
	t_uint	i;
	TYPE	average;
	TYPE	tmp;

	average = Stat_Float_Average(flst);
	sum = 0;
	i = 0;
	while (i < flst.length)
	{
		tmp = flst.items[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));
}



extern inline
t_float	Stat_Float_StandardDeviation(s_array(float) const flst)
{
	return Float_Root2(Stat_Float_Variance(flst));
}



void	Stat_Float_Decile(s_array(float) const flst)
{
	return; // TODO implement
}



t_bool	Stat_Float_ProbabilityIsValid(s_array(float) const prob_flst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_uint		i;

	prob_sum = 0.;
	i = 0;
	while (i < prob_flst.length)
	{
		tmp = prob_flst.items[i];
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
