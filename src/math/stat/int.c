
#include "libccc/memory.h"
#include "libccc/math.h"
#include "libccc/math/stat.h"

#define T_TYPE	t_sint
#define T_NAME	int
#define T_NULL	0
#include "libccc/monad/array.c"

#include LIBCONFIG_ERROR_INCLUDE



#define TYPE		t_sint



s_array(int)	c_stat_new_ilst(t_uint length)
{
	s_array(int)		result;

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



void	c_stat_free_ilst(s_array(int) *ilst)
{
	if CCCERROR((ilst == NULL), ERROR_NULLPOINTER, "array of ints given is NULL")
		return;
	if (ilst->items)
	{
		Memory_Free(ilst->items);
		ilst->items = NULL;
	}
	ilst->length = 0;
}



static
s_array(int)	c_stat_ilst_dup(s_array(int) const ilst)
{
	s_array(int)	result;

	result = c_stat_new_ilst(ilst.length);
	if (!result.items)
		return (result);
	for (t_uint i = 0; i < result.length; ++i)
	{
		result.items[i] = ilst.items[i];
	}
	return (result);
}



s_array(int)	c_stat_merge_ilst(
	s_array(int) *start,
	s_array(int) *append)
{
	s_array(int)			result;
	t_uint				i;
	t_uint				j;

	if CCCERROR((start  == NULL), ERROR_NULLPOINTER, "array of ints given is NULL")
		return ((s_array(int)){ 0, NULL });
	if CCCERROR((append == NULL), ERROR_NULLPOINTER, "array of ints to append to given is NULL")
		return ((s_array(int)){ 0, NULL });
	if (start->length == 0 && append->length == 0)
		return (c_stat_new_ilst(0));
	else if (!start->items || start->length == 0)
		return (*append);
	else if (!append->items || append->length == 0)
		return (*start);
	result = c_stat_new_ilst(start->length + append->length);
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
	c_stat_free_ilst(start);
	c_stat_free_ilst(append);

	return (result);
}



/*
** Both indices provided are to be included in those written to.
** The recursive function can be called with start at 0 and end at
** tmp_lst.length - 1 to sort in place.
*/
static
void		c_stat_quicksort_i_rec(
	s_array(int)	tmp_lst,
	t_uint		start,
	t_uint		end)
{
	TYPE	pivot;
	t_uint	pivot_id;
	t_uint	rise_id;
	t_uint	fall_id;

	pivot = tmp_lst.items[start];
	if (start >= end)
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
		c_stat_quicksort_i_rec(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		c_stat_quicksort_i_rec(tmp_lst, pivot_id + 1, end);
}



s_array(int) c_stat_quicksort_i_new(s_array(int) const ilst)
{
	s_array(int)	result;

	if (ilst.length <= 1)
		return (ilst);
	result = c_stat_ilst_dup(ilst);
	c_stat_quicksort_i_rec(result, 0, ilst.length - 1);
	return (result);
}



void		c_stat_quicksort_i(s_array(int) ilst)
{
	c_stat_quicksort_i_rec(ilst, 0, ilst.length - 1);
}



inline
t_float		c_stat_median_i(s_sorted_int const ilst)
{
	return ((ilst.length % 2) ?
		ilst.items[ilst.length / 2] :
		(ilst.items[ilst.length / 2] + ilst.items[ilst.length / 2 + 1]) / 2);
}

t_float		c_stat_average_i(s_array(int) const ilst)
{
	t_float		sum;
	t_uint		i;

	sum = 0;
	i = 0;
	while (i < ilst.length)
	{
		sum += ilst.items[i];
		++i;
	}
	return (sum / i);
}



/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/
t_float		c_stat_variance_i(s_array(int) const ilst)
{
	t_float		sum;
	t_uint		i;
	t_float		average;
	t_float		tmp;

	average = c_stat_average_i(ilst);
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



// TODO
/*
inline
t_float		c_stat_stddev_i(s_array(int) const ilst)
{

}
*/

/*
t_bool		c_prob_is_valid_i(t_prob_sample_i const i_problst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_uint		i;

	prob_sum = 0.;
	i = 0;
	while (i < i_problst.length)
	{
		tmp = i_problst.prob[i];
		if (tmp < 0. || 1. < tmp)
		{
			c_printf_fd(2, "Proba %f at index %d is out of [0, 1]\n", tmp, i);
			return (FALSE);
		}
		prob_sum += tmp;
		++i;
	}
	if (c_fabs(prob_sum - 1.) > PROB_APPROX)
	{
		c_printf_fd(2, "Proba sum %s is too far from 1.\n", prob_sum);
		return (FALSE);
	}
	return (TRUE);
}
*/



s_prob_mass	c_stat_new_pmf(t_uint length)
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



void		c_stat_free_pmf(s_prob_mass *drv)
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



s_set_int	c_stat_ilst_to_iset(s_array(int) const ilst)
{
	s_array(int)	result;
	s_array(int)	set;
	t_uint		i;
	t_uint		j;

	set = c_stat_new_ilst(ilst.length);
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
	result = c_stat_new_ilst(set.length);
	Memory_Copy(result.items, set.items, set.length * sizeof(TYPE));
//	memcpy(result.items, set.items, set.length * sizeof(TYPE));
	Memory_Free(set.items);
	return (result);
}



t_uint		c_stat_ilst_count(s_array(int) ilst, TYPE elem)
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



s_prob_mass	c_stat_ilst_to_pmf(s_array(int) const ilst)
{
	s_prob_mass	result;
	s_array(int)	set;
	t_uint		i;
	t_float		inv_sample_size;

	if (ilst.items == NULL || ilst.length == 0)
		return (c_stat_new_pmf(0));
	set = c_stat_ilst_to_iset(ilst);
	result = c_stat_new_pmf(set.length);
	i = 0;
	inv_sample_size = 1.0 / ilst.length;
	while (i < result.length)
	{
		result.value[i] = (t_float)set.items[i];
		result.prob[i] = (t_float)c_stat_ilst_count(ilst, set.items[i]);
		result.prob[i] *= inv_sample_size;
		++i;
	}
	c_stat_free_ilst(&set);
	return (result);
}
