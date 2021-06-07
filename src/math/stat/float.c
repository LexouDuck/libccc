
#include "libccc/memory.h"
#include "libccc/math/math.h"
#include "libccc/math/stat.h"
#define T			t_float
#define T_NAME		_float
#define T_DEFAULT	0.
#include "libccc/monad/array.c"

#include LIBCONFIG_ERROR_INCLUDE



#define TYPE		t_float



s_array_float	c_stat_new_flst(t_u32 length)
{
	s_array_float	result;

	result.items = NULL;
	result.length = 0;
	if (length == 0)
		return (result);
	result.items = (TYPE*)Memory_Allocate(sizeof(TYPE) * length);
	HANDLE_ERROR(ALLOCFAILURE, (result.items == NULL), return (result);)
	result.length = length;
	return (result);
}



void	c_stat_free_flst(s_array_float *flst)
{
	HANDLE_ERROR(NULLPOINTER, (flst == NULL), return;)
	if (flst->items)
	{
		Memory_Free(flst->items);
		flst->items = NULL;
	}
	flst->length = 0;
}



static
s_array_float	c_stat_flst_dup(s_array_float const flst)
{
	s_array_float	result;

	result = c_stat_new_flst(flst.length);
	if (!result.items)
		return (result);
	for (t_u32 i = 0; i < result.length; ++i)
	{
		result.items[i] = flst.items[i];
	}
	return (result);
}



s_array_float 	c_stat_merge_flst(
	s_array_float *start,
	s_array_float *append)
{
	s_array_float	result;
	t_u32	i;
	t_u32	j;

	HANDLE_ERROR(NULLPOINTER, (start  == NULL), return ((s_array_float){ 0, NULL });)
	HANDLE_ERROR(NULLPOINTER, (append == NULL), return ((s_array_float){ 0, NULL });)
	if (start->length == 0 && append->length == 0)
		return (c_stat_new_flst(0));
	else if (!start->items || start->length == 0)
		return (*append);
	else if (!append->items || append->length == 0)
		return (*start);
	result = c_stat_new_flst(start->length + append->length);
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
	c_stat_free_flst(start);
	c_stat_free_flst(append);

	return (result);
}



/*
** Both indices provided are to be included in those written to.
** The recursive function can be called with start at 0 and end at
** tmp_lst.length - 1 to sort in place.
*/
static
void		c_stat_quicksort_f_rec(
	s_array_float	tmp_lst,
	t_u32			start,
	t_u32			end)
{
	TYPE	pivot;
	t_u32	pivot_id;
	t_u32	rise_id;
	t_u32	fall_id;

	pivot = tmp_lst.items[start];
	if (start >= end || pivot != pivot)
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
		c_stat_quicksort_f_rec(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		c_stat_quicksort_f_rec(tmp_lst, pivot_id + 1, end);
}



s_array_float 	c_stat_quicksort_f_new(s_array_float const flst)
{
	s_array_float	result;

	if (flst.length <= 1)
		return (flst);
	result = c_stat_flst_dup(flst);
	c_stat_quicksort_f_rec(result, 0, flst.length - 1);
	return (result);
}



void		c_stat_quicksort_f(s_array_float flst)
{
	c_stat_quicksort_f_rec(flst, 0, flst.length - 1);
}



inline
t_float		c_stat_median_f(s_sorted_float const flst)
{
	return ((flst.length % 2) ?
		flst.items[flst.length / 2] :
		(flst.items[flst.length / 2] + flst.items[flst.length / 2 + 1]) / 2);
}



t_float		c_stat_average_f(s_array_float const flst)
{
	TYPE	sum;
	t_u32	i;

	sum = 0.;
	i = 0;
	TYPE inv_len = (1. / flst.length);
	while (i < flst.length)
	{
		sum += inv_len * flst.items[i];
		++i;
	}
	return (sum);
}



/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/
t_float		c_stat_variance_f(s_array_float const flst)
{
	TYPE	sum;
	t_u32	i;
	TYPE	average;
	TYPE	tmp;

	average = c_stat_average_f(flst);
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


// TODO
/*
inline
t_float		c_stat_stddev_f(s_array_float const flst)
{
	
}
*/

/*
t_bool		c_prob_is_valid_f(t_prob_sample_f const f_problst);
{

}
*/
