
#include "libccc/memory.h"
#include "libccc/math/stat.h"

#include LIBCONFIG_HANDLE_INCLUDE



s_list_int		c_stat_new_ilst(t_u32 length)
{
	s_list_int		result;

	result.data = NULL;
	result.length = 0;
	if (length == 0)
		return (result);
	result.data = (t_sint*)Memory_Alloc(sizeof(t_sint) * length);
	HANDLE_ERROR(ALLOCFAILURE, (result.data == NULL), return (result);)
	result.length = length;
	return (result);
}

void			c_stat_free_ilst(s_list_int *ilst)
{
	HANDLE_ERROR(NULLPOINTER, (ilst == NULL), return;)
	if (ilst->data)
	{
		Memory_Free(ilst->data);
		ilst->data = NULL;
	}
	ilst->length = 0;
}

static
s_list_int		c_stat_ilst_dup(s_list_int const ilst)
{
	s_list_int	result;

	result = c_stat_new_ilst(ilst.length);
	if (!result.data)
		return (result);
	for (t_u32 i = 0; i < result.length; ++i)
		result.data[i] = ilst.data[i];
	return (result);
}

s_list_int		c_stat_merge_ilst(
	s_list_int *start,
	s_list_int *append)
{
	s_list_int			result;
	t_u32				i;
	t_u32				j;

	HANDLE_ERROR(NULLPOINTER, (start == NULL), return (NULL_LIST_INT);)
	HANDLE_ERROR(NULLPOINTER, (append == NULL), return (NULL_LIST_INT);)
	if (start->length == 0 && append->length == 0)
		return (c_stat_new_ilst(0));
	else if (!start->data || start->length == 0)
		return (*append);
	else if (!append->data || append->length == 0)
		return (*start);
	result = c_stat_new_ilst(start->length + append->length);
	if (!(result.data))
		return (result);

	for (i = 0; i < start->length; ++i)
		result.data[i] = start->data[i];
	for (j = 0; i < result.length; ++i, ++j)
		result.data[i] = append->data[j];
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
void			c_stat_quicksort_i_rec
(
	s_list_int	tmp_lst,
	t_u32		start,
	t_u32		end
)
{
	t_sint	pivot;
	t_u32	pivot_id;
	t_u32	rise_id;
	t_u32	fall_id;

	pivot = tmp_lst.data[start];
	if (start >= end)
		return;
	if (start == end - 1)
	{
		if (pivot > tmp_lst.data[end])
			c_memswap(tmp_lst.data + start, tmp_lst.data + end, sizeof(t_sint));
		return;
	}

	rise_id = start + 1;
	fall_id = end;
	while (rise_id < fall_id)
	{
		while (rise_id <= end && tmp_lst.data[rise_id] <= pivot)
			++rise_id;
		while (fall_id > start && tmp_lst.data[fall_id] > pivot)
			--fall_id;
		if (rise_id < fall_id)
			c_memswap(tmp_lst.data + rise_id, tmp_lst.data + fall_id, sizeof(t_sint));
	}
	pivot_id = fall_id;
	if (start != fall_id)
		c_memswap(tmp_lst.data + start, tmp_lst.data + fall_id, sizeof(t_sint));

	if (pivot_id > start)
		c_stat_quicksort_i_rec(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		c_stat_quicksort_i_rec(tmp_lst, pivot_id + 1, end);
}

s_list_int 		c_stat_quicksort_i_new(s_list_int const ilst)
{
	s_list_int	result;

	if (ilst.length <= 1)
		return (ilst);
	result = c_stat_ilst_dup(ilst);
	c_stat_quicksort_i_rec(result, 0, ilst.length - 1);
	return (result);
}

void			c_stat_quicksort_i(s_list_int ilst)
{
	c_stat_quicksort_i_rec(ilst, 0, ilst.length - 1);
}



inline t_float	c_stat_median_i(s_sortedlist_int const ilst)
{
	return ((ilst.length % 2) ?
		ilst.data[ilst.length / 2] :
		(ilst.data[ilst.length / 2] + ilst.data[ilst.length / 2 + 1]) / 2);
}

t_float			c_stat_average_i(s_list_int const ilst)
{
	t_float		sum;
	t_u32		i;

	sum = 0;
	i = 0;
	while (i < ilst.length)
	{
		sum += ilst.data[i];
		++i;
	}
	return (sum / i);
}

/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/
t_float			c_stat_variance_i(s_list_int const ilst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = c_stat_average_i(ilst);
	sum = 0;
	i = 0;
	while (i < ilst.length)
	{
		tmp = ilst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));
}

// TODO
/*
inline t_float	c_stat_stddev_i(s_list_int const ilst)
{

}
*/

/*
t_bool			c_prob_is_valid_i(t_prob_sample_i const i_problst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_u32		i;

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



s_prob_mass		c_stat_new_pmf(t_u32 length)
{
	s_prob_mass	result;

	result.value = NULL;
	result.prob = NULL;
	result.length = 0;
	if (length == 0)	return (result);
	result.value = (t_float*)Memory_Alloc(length * sizeof(t_float));
	HANDLE_ERROR(ALLOCFAILURE, (result.value == NULL), return (result);)
	result.prob = (t_float*)Memory_Alloc(length * sizeof(t_float));
	HANDLE_ERROR(ALLOCFAILURE, (result.prob == NULL), return (result);)
	result.length = length;
	return (result);
}

void			c_stat_free_pmf(s_prob_mass *drv)
{
	HANDLE_ERROR(NULLPOINTER, (drv == NULL), return;)
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

s_set_int		c_stat_ilst_to_iset(s_list_int const ilst)
{
	s_list_int				result;
	s_list_int				set;
	t_u32					i;
	t_u32					j;

	set = c_stat_new_ilst(ilst.length);
	set.length = 0;
	i = 0;
	while (i < ilst.length)
	{
		j = 0;
		while (j < set.length)
		{
			if (set.data[j] == ilst.data[i])
				break;
			++j;
		}
		if (j == set.length)
			set.data[(set.length)++] = ilst.data[i];
		++i;
	}
	result = c_stat_new_ilst(set.length);
	Memory_Copy(result.data, set.data, set.length * sizeof(t_sint));
//	memcpy(result.data, set.data, set.length * sizeof(t_sint));
	Memory_Free(set.data);
	return (result);
}

t_u32			c_stat_ilst_count(s_list_int ilst, t_sint elem)
{
	t_u32		i;
	t_u32		result;

	i = 0;
	result = 0;
	while (i < ilst.length)
	{
		if (ilst.data[i] == elem)
			++result;
		++i;
	}
	return (result);
}

/*
** Returns the probability distribution of a list of integers.
*/
s_prob_mass		c_stat_ilst_to_pmf(s_list_int const ilst)
{
	s_prob_mass	result;
	s_list_int	set;
	t_u32		i;
	t_float		inv_sample_size;

	if (ilst.data == NULL || ilst.length == 0)
		return (c_stat_new_pmf(0));
	set = c_stat_ilst_to_iset(ilst);
	result = c_stat_new_pmf(set.length);
	i = 0;
	inv_sample_size = 1.0 / ilst.length;
	while (i < result.length)
	{
		result.value[i] = (t_float)set.data[i];
		result.prob[i] = (t_float)c_stat_ilst_count(ilst, set.data[i]);
		result.prob[i] *= inv_sample_size;
		++i;
	}
	c_stat_free_ilst(&set);
	return (result);
}
