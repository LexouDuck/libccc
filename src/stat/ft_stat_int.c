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
#include "libft_stat.h"



s_list_int		ft_stat_new_ilst(t_u32 len)
{
	s_list_int		res;

	res.data = NULL;
	res.len = 0;
	if (len == 0)
		return (res);
	if (!(res.data = (t_int*)ft_memalloc(sizeof(t_int) * len)))
		return (res);
	res.len = len;
	return (res);
}

void			ft_stat_free_ilst(s_list_int *ilst)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (ilst == NULL)
		return ;
#endif
	if (ilst->data)
	{
		ft_memfree(ilst->data);
		ilst->data = NULL;
	}
	ilst->len = 0;
}

s_list_int		ft_stat_ilst_dup(s_list_int const ilst)
{
	s_list_int	res;

	res = ft_stat_new_ilst(ilst.len);
	if (!res.data)
		return (res);
	for (t_u32 i = 0; i < res.len; ++i)
		res.data[i] = ilst.data[i];
	return (res);
}

s_list_int		ft_stat_merge_ilst(
	s_list_int *start,
	s_list_int *append)
{
	s_list_int			res;
	t_u32				i;
	t_u32				j;

#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (start == NULL || append == NULL)
		return (NULL_LIST_INT);
#endif
	if (start->len == 0 && append->len == 0)
		return (ft_stat_new_ilst(0));
	else if (!start->data || start->len == 0)
		return (*append);
	else if (!append->data || append->len == 0)
		return (*start);
	res = ft_stat_new_ilst(start->len + append->len);
	if (!(res.data))
		return (res);

	for (i = 0; i < start->len; ++i)
		res.data[i] = start->data[i];
	for (j = 0; i < res.len; ++i, ++j)
		res.data[i] = append->data[j];
	ft_stat_free_ilst(start);
	ft_stat_free_ilst(append);

	return (res);
}



/*
** Both indices provided are to be included in those written to.
** The recursive function can be called with start at 0 and end at
** tmp_lst.len - 1 to sort in place.
*/
static void		ft_stat_quicksort_i_rec
(
	s_list_int	tmp_lst,
	t_u32		start,
	t_u32		end
)
{
	t_int	pivot;
	t_u32	pivot_id;
	t_u32	rise_id;
	t_u32	fall_id;

	pivot = tmp_lst.data[start];
	if (start >= end)
		return ;
	if (start == end - 1)
	{
		if (pivot > tmp_lst.data[end])
			ft_memswap(tmp_lst.data + start, tmp_lst.data + end, sizeof(t_int));
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
			ft_memswap(tmp_lst.data + rise_id, tmp_lst.data + fall_id, sizeof(t_int));
	}
	pivot_id = fall_id;
	if (start != fall_id)
		ft_memswap(tmp_lst.data + start, tmp_lst.data + fall_id, sizeof(t_int));

	if (pivot_id > start)
		ft_stat_quicksort_i_rec(tmp_lst, start, pivot_id - 1);
	if (pivot_id < end)
		ft_stat_quicksort_i_rec(tmp_lst, pivot_id + 1, end);
}

s_list_int 			ft_stat_quicksort_i_new(s_list_int const ilst)
{
	s_list_int	res;

	if (ilst.len <= 1)
		return (ilst);
	res = ft_stat_ilst_dup(ilst);
	ft_stat_quicksort_i_rec(res, 0, ilst.len - 1);
	return (res);
}

inline void			ft_stat_quicksort_i(s_list_int ilst)
{
	ft_stat_quicksort_i_rec(ilst, 0, ilst.len - 1);
}



inline t_float		ft_stat_median_i(s_sortedlist_int const ilst)
{
	return ((ilst.len % 2) ?
		ilst.data[ilst.len / 2] :
		(ilst.data[ilst.len / 2] + ilst.data[ilst.len / 2 + 1]) / 2);
}

t_float				ft_stat_average_i(s_list_int const ilst)
{
	t_float		sum;
	t_u32		i;

	sum = 0;
	i = 0;
	while (i < ilst.len)
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
t_float				ft_stat_variance_i(s_list_int const ilst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = ft_stat_average_i(ilst);
	sum = 0;
	i = 0;
	while (i < ilst.len)
	{
		tmp = ilst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));
}

// TODO
/*
inline t_float		ft_stat_stddev_i(s_list_int const ilst)
{

}
*/

/*
t_bool				ft_prob_is_valid_i(t_prob_sample_i const i_problst)
{
	t_float		prob_sum;
	t_float		tmp;
	t_u32		i;

	prob_sum = 0.;
	i = 0;
	while (i < i_problst.len)
	{
		tmp = i_problst.prob[i];
		if (tmp < 0. || 1. < tmp)
		{
			ft_printf_fd(2, "Proba %f at index %d is out of [0, 1]\n", tmp, i);
			return (FALSE);
		}
		prob_sum += tmp;
		++i;
	}
	if (ft_fabs(prob_sum - 1.) > PROB_APPROX)
	{
		ft_printf_fd(2, "Proba sum %s is too far from 1.\n", prob_sum);
		return (FALSE);
	}
	return (TRUE);
}
*/



s_prob_mass				ft_stat_new_pmf(t_u32 len)
{
	s_prob_mass	res;

	res.value = NULL;
	res.prob = NULL;
	res.len = 0;
	if (len == 0 ||
		!(res.value	= (t_float*)ft_memalloc(len * sizeof(t_float))) ||
		!(res.prob	= (t_float*)ft_memalloc(len * sizeof(t_float))))
		return (res);
	res.len = len;
	return (res);
}

void					ft_stat_free_pmf(s_prob_mass *drv)
{
#if LIBFTCONFIG_HANDLE_NULLPOINTERS
	if (drv == NULL)
		return ;
#endif
	if (drv->value)
	{
		ft_memfree(drv->value);
		drv->value = NULL;
	}
	if (drv->prob)
	{
		ft_memfree(drv->prob);
		drv->prob = NULL;
	}
	drv->len = 0;
}

s_set_int				ft_stat_ilst_to_iset(s_list_int const ilst)
{
	s_list_int				res;
	s_list_int				set;
	t_u32					i;
	t_u32					j;

	set = ft_stat_new_ilst(ilst.len);
	set.len = 0;
	i = 0;
	while (i < ilst.len)
	{
		j = 0;
		while (j < set.len)
		{
			if (set.data[j] == ilst.data[i])
				break;
			++j;
		}
		if (j == set.len)
			set.data[(set.len)++] = ilst.data[i];
		++i;
	}
	res = ft_stat_new_ilst(set.len);
	ft_memcpy(res.data, set.data, set.len * sizeof(t_int));
//	memcpy(res.data, set.data, set.len * sizeof(t_int));
	ft_memfree(set.data);
	return (res);
}

t_u32				ft_stat_ilst_count(s_list_int ilst, t_int elem)
{
	t_u32		i;
	t_u32		res;

	i = 0;
	res = 0;
	while (i < ilst.len)
	{
		if (ilst.data[i] == elem)
			++res;
		++i;
	}
	return (res);
}

/*
** Returns the probability distribution of a list of integers.
*/
s_prob_mass			ft_stat_ilst_to_pmf(s_list_int const ilst)
{
	s_prob_mass			res;
	s_list_int			set;
	t_u32				i;
	t_float				inv_sample_size;

	if (ilst.data == NULL || ilst.len == 0)
		return (ft_stat_new_pmf(0));
	set = ft_stat_ilst_to_iset(ilst);
	res = ft_stat_new_pmf(set.len);
	i = 0;
	inv_sample_size = 1.0 / ilst.len;
	while (i < res.len)
	{
		res.value[i] = (t_float)set.data[i];
		res.prob[i] = (t_float)ft_stat_ilst_count(ilst, set.data[i]);
		res.prob[i] *= inv_sample_size;
		++i;
	}
	ft_stat_free_ilst(&set);
	return (res);
}
