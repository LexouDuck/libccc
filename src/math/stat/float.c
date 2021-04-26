
#include "libccc/memory.h"
#include "libccc/math/math.h"
#include "libccc/math/stat.h"



s_list_float	c_stat_new_flst(t_u32 length)
{
	s_list_float	result;

	result.data = NULL;
	result.length = 0;
	if (length == 0)
		return (result);
	if (!(result.data = (t_float*)c_memalloc(sizeof(t_float) * length)))
		return (result);
	result.length = length;
	return (result);
}

void			c_stat_free_flst(s_list_float *flst)
{
	LIBCONFIG_HANDLE_NULLPOINTER(flst, )
	if (flst->data)
	{
		c_memfree(flst->data);
		flst->data = NULL;
	}
	flst->length = 0;
}

s_list_float	c_stat_flst_dup(s_list_float const flst)
{
	s_list_float	result;

	result = c_stat_new_flst(flst.length);
	if (!result.data)
		return (result);
	for (t_u32 i = 0; i < result.length; ++i)
		result.data[i] = flst.data[i];
	return (result);
}

s_list_float 	c_stat_merge_flst(
	s_list_float *start,
	s_list_float *append)
{
	s_list_float		result;
	t_u32				i;
	t_u32				j;

	LIBCONFIG_HANDLE_NULLPOINTER(start, NULL_LIST_FLOAT)
	LIBCONFIG_HANDLE_NULLPOINTER(append, NULL_LIST_FLOAT)
	if (start->length == 0 && append->length == 0)
		return (c_stat_new_flst(0));
	else if (!start->data || start->length == 0)
		return (*append);
	else if (!append->data || append->length == 0)
		return (*start);
	result = c_stat_new_flst(start->length + append->length);
	if (!(result.data))
		return (result);

	for (i = 0; i < start->length; ++i)
		result.data[i] = start->data[i];
	for (j = 0; i < result.length; ++i, ++j)
		result.data[i] = append->data[j];
	c_stat_free_flst(start);
	c_stat_free_flst(append);

	return (result);
}



/*
** Both indices provided are to be included in those written to.
** The recursive function can be called with start at 0 and end at
** tmp_lst.length - 1 to sort in place.
*/
void				c_stat_quicksort_f_rec
(
	s_list_float	tmp_lst,
	t_u32			start,
	t_u32			end
)
{
	t_float	pivot;
	t_u32	pivot_id;
	t_u32	rise_id;
	t_u32	fall_id;

	pivot = tmp_lst.data[start];
	if (start >= end || pivot != pivot)
		return;
	if (start == end - 1)
	{
		if (pivot > tmp_lst.data[end])
			c_memswap(tmp_lst.data + start, tmp_lst.data + end, sizeof(t_float));
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
			c_memswap(tmp_lst.data + rise_id, tmp_lst.data + fall_id, sizeof(t_float));
	}
	pivot_id = fall_id;
	if (start != fall_id)
		c_memswap(tmp_lst.data + start, tmp_lst.data + fall_id, sizeof(t_float));

	if (pivot_id > start)
		c_stat_quicksort_f_rec(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		c_stat_quicksort_f_rec(tmp_lst, pivot_id + 1, end);
}

s_list_float 		c_stat_quicksort_f_new(s_list_float const flst)
{
	s_list_float	result;

	if (flst.length <= 1)
		return (flst);
	result = c_stat_flst_dup(flst);
	c_stat_quicksort_f_rec(result, 0, flst.length - 1);
	return (result);
}

inline void			c_stat_quicksort_f(s_list_float flst)
{
	c_stat_quicksort_f_rec(flst, 0, flst.length - 1);
}



inline t_float		c_stat_median_f(s_sortedlist_float const flst)
{
	return ((flst.length % 2) ?
		flst.data[flst.length / 2] :
		(flst.data[flst.length / 2] + flst.data[flst.length / 2 + 1]) / 2);
}

t_float				c_stat_average_f(s_list_float const flst)
{
	t_float		sum;
	t_u32		i;

	sum = 0.;
	i = 0;
	t_float inv_len = (1. / flst.length);
	while (i < flst.length)
	{
		sum += inv_len * flst.data[i];
		++i;
	}
	return (sum);
}

/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/
t_float				c_stat_variance_f(s_list_float const flst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = c_stat_average_f(flst);
	sum = 0;
	i = 0;
	while (i < flst.length)
	{
		tmp = flst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));

}

// TODO
/*
inline t_float		c_stat_stddev_f(s_list_float const flst)
{
	
}
*/

/*
t_bool				c_prob_is_valid_f(t_prob_sample_f const f_problst);
{

}
*/
