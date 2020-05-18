/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat/ft_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_memory.h"
#include "libft_math.h"
#include "libft_stat.h"



s_list_float	ft_stat_new_flst(t_u32 len)
{
	s_list_float	res;

	res.data = NULL;
	res.len = 0;
	if (len == 0)
		return (res);
	if (!(res.data = (t_float*)ft_memalloc(sizeof(t_float) * len)))
		return (res);
	res.len = len;
	return (res);
}

void			ft_stat_free_flst(s_list_float *flst)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (flst == NULL)
		return ;
#endif
	if (flst->data)
	{
		ft_memfree(flst->data);
		flst->data = NULL;
	}
	flst->len = 0;
}

s_list_float	ft_stat_flst_dup(s_list_float const flst)
{
	s_list_float	res;

	res = ft_stat_new_flst(flst.len);
	if (!res.data)
		return (res);
	for (t_u32 i = 0; i < res.len; ++i)
		res.data[i] = flst.data[i];
	return (res);
}

s_list_float 	ft_stat_merge_flst(
	s_list_float *start,
	s_list_float *append)
{
	s_list_float		res;
	t_u32				i;
	t_u32				j;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (start == NULL || append == NULL)
		return (NULL_LIST_FLOAT);
#endif
	if (start->len == 0 && append->len == 0)
		return (ft_stat_new_flst(0));
	else if (!start->data || start->len == 0)
		return (*append);
	else if (!append->data || append->len == 0)
		return (*start);
	res = ft_stat_new_flst(start->len + append->len);
	if (!(res.data))
		return (res);

	for (i = 0; i < start->len; ++i)
		res.data[i] = start->data[i];
	for (j = 0; i < res.len; ++i, ++j)
		res.data[i] = append->data[j];
	ft_stat_free_flst(start);
	ft_stat_free_flst(append);

	return (res);
}



/*
** Both indices provided are to be included in those written to.
** The recursive function can be called with start at 0 and end at
** tmp_lst.len - 1 to sort in place.
*/
void				ft_stat_quicksort_f_rec
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
		return ;
	if (start == end - 1)
	{
		if (pivot > tmp_lst.data[end])
			ft_memswap(tmp_lst.data + start, tmp_lst.data + end, sizeof(t_float));
		return ;
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
			ft_memswap(tmp_lst.data + rise_id, tmp_lst.data + fall_id, sizeof(t_float));
	}
	pivot_id = fall_id;
	if (start != fall_id)
		ft_memswap(tmp_lst.data + start, tmp_lst.data + fall_id, sizeof(t_float));

	if (pivot_id > start)
		ft_stat_quicksort_f_rec(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		ft_stat_quicksort_f_rec(tmp_lst, pivot_id + 1, end);
}

s_list_float 		ft_stat_quicksort_f_new(s_list_float const flst)
{
	s_list_float	res;

	if (flst.len <= 1)
		return (flst);
	res = ft_stat_flst_dup(flst);
	ft_stat_quicksort_f_rec(res, 0, flst.len - 1);
	return (res);
}

inline void			ft_stat_quicksort_f(s_list_float flst)
{
	ft_stat_quicksort_f_rec(flst, 0, flst.len - 1);
}



inline t_float		ft_stat_median_f(s_sortedlist_float const flst)
{
	return ((flst.len % 2) ?
		flst.data[flst.len / 2] :
		(flst.data[flst.len / 2] + flst.data[flst.len / 2 + 1]) / 2);
}

t_float				ft_stat_average_f(s_list_float const flst)
{
	t_float		sum;
	t_u32		i;

	sum = 0.;
	i = 0;
	if (IS_INFINITY(flst.data[i] * flst.len * 1e6))
	{
		t_float inv_len = (1. / flst.len);
		while (i < flst.len)
		{
			sum += inv_len * flst.data[i];
			++i;
		}
		return (sum);
	}
	else
	{
		while (i < flst.len)
		{
			sum += flst.data[i];
			++i;
		}
		return (sum / i);
	}
}

/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/
t_float				ft_stat_variance_f(s_list_float const flst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = ft_stat_average_f(flst);
	sum = 0;
	i = 0;
	while (i < flst.len)
	{
		tmp = flst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));

}

// TODO
/*
inline t_float		ft_stat_stddev_f(s_list_float const flst)
{
	
}
*/

/*
t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);
{

}
*/
