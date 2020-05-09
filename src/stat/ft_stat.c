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

#include "libft_stat.h"
#include "libft_memory.h"

// TODO subdivide this file into several .c files

t_list_int		ft_stat_new_ilst(t_u32 len)
{
	t_list_int		res;

	res.data = NULL;
	res.len = 0;
	if (len == 0 || !(res.data = malloc(sizeof(t_int) * len)))
		return (res);
	res.len = len;
	return (res);
}

t_list_float	ft_stat_new_flst(t_u32 len)
{
	t_list_float	res;

	res.data = NULL;
	res.len = 0;
	if (len == 0 || !(res.data = malloc(sizeof(t_int) * len)))
		return (res);
	res.len = len;
	return (res);
}

void			ft_stat_free_ilst(t_list_int *ilst)
{
#if HANDLE_NULLPOINTERS
	if (ilst == NULL)
		return ;
#endif
	if (ilst->data)
	{
		free(ilst->data);
		ilst->data = NULL;
	}
	ilst->len = 0;
}

void			ft_stat_free_flst(t_list_float *flst)
{
#if HANDLE_NULLPOINTERS
	if (flst == NULL)
		return ;
#endif
	if (flst->data)
	{
		free(flst->data);
		flst->data = NULL;
	}
	flst->len = 0;
}

t_list_int		ft_stat_ilst_dup(t_list_int const ilst)
{
	t_list_int	res;

	res = ft_stat_new_ilst(ilst.len);
	if (!res.data)
		return (res);
	for (t_u32 i = 0; i < res.len; ++i)
		res.data[i] = ilst.data[i];
	return (res);
}

t_list_float	ft_stat_flst_dup(t_list_float const flst)
{
	t_list_float	res;

	res = ft_stat_new_flst(flst.len);
	if (!res.data)
		return (res);
	for (t_u32 i = 0; i < res.len; ++i)
		res.data[i] = flst.data[i];
	return (res);
}

t_list_int		ft_stat_merge_ilst(
	t_list_int *start,
	t_list_int *append)
{
	t_list_int			res;
	t_u32				i;
	t_u32				j;

#if HANDLE_NULLPOINTERS
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

t_list_float 	ft_stat_merge_flst(
	t_list_float *start,
	t_list_float *append)
{
	t_list_float		res;
	t_u32				i;
	t_u32				j;

#if HANDLE_NULLPOINTERS
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
static void		ft_stat_quicksort_i_rec
(
	t_list_int	tmp_lst,
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

t_list_int 			ft_stat_quicksort_i_new(t_list_int const i_lst)
{
	t_list_int	res;

	if (i_lst.len <= 1)
		return (i_lst);
	res = ft_stat_ilst_dup(i_lst);
	ft_stat_quicksort_i_rec(res, 0, i_lst.len - 1);
	return (res);
}

inline void			ft_stat_quicksort_i(t_list_int i_lst)
{
	ft_stat_quicksort_i_rec(i_lst, 0, i_lst.len - 1);
}

/*
** Both indices provided are to be included in those written to.
** The recursive function can be called with start at 0 and end at
** tmp_lst.len - 1 to sort in place.
*/
void				ft_stat_quicksort_f_rec
(
	t_list_float	tmp_lst,
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

t_list_float 		ft_stat_quicksort_f_new(t_list_float const f_lst)
{
	t_list_float	res;

	if (f_lst.len <= 1)
		return (f_lst);
	res = ft_stat_flst_dup(f_lst);
	ft_stat_quicksort_f_rec(res, 0, f_lst.len - 1);
	return (res);
}

inline void			ft_stat_quicksort_f(t_list_float f_lst)
{
	ft_stat_quicksort_f_rec(f_lst, 0, f_lst.len - 1);
}



inline t_float		ft_stat_median_i(t_sortedlist_int const i_lst)
{
	return ((i_lst.len % 2) ?
		i_lst.data[i_lst.len / 2] :
		(i_lst.data[i_lst.len / 2] + i_lst.data[i_lst.len / 2 + 1]) / 2);
}

inline t_float		ft_stat_median_f(t_sortedlist_float const f_lst)
{
	return ((f_lst.len % 2) ?
		f_lst.data[f_lst.len / 2] :
		(f_lst.data[f_lst.len / 2] + f_lst.data[f_lst.len / 2 + 1]) / 2);
}

t_float				ft_stat_average_i(t_list_int const i_lst)
{
	t_float		sum;
	t_u32		i;

	sum = 0;
	i = 0;
	while (i < i_lst.len)
	{
		sum += i_lst.data[i];
		++i;
	}
	return (sum / i);

}

t_float				ft_stat_average_f(t_list_float const f_lst)
{
	t_float		sum;
	t_u32		i;

	sum = 0.;
	i = 0;
	while (i < f_lst.len)
	{
		sum += f_lst.data[i];
		++i;
	}
	return (sum / i);
}

/*
** Using V(X) = E(X^2) - E(X)^2 rather than E( [X - E(X)]^2 ) which has more
**	operations (n subtractions).
*/

t_float				ft_stat_variance_i(t_list_int const i_lst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = ft_stat_average_i(i_lst);
	sum = 0;
	i = 0;
	while (i < i_lst.len)
	{
		tmp = i_lst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));

}

t_float				ft_stat_variance_f(t_list_float const f_lst)
{
	t_float		sum;
	t_u32		i;
	t_float		average;
	t_float		tmp;

	average = ft_stat_average_f(f_lst);
	sum = 0;
	i = 0;
	while (i < f_lst.len)
	{
		tmp = f_lst.data[i];
		sum += tmp * tmp;
		++i;
	}
	return ((sum / i) - (average * average));

}
/*
inline t_float				ft_stat_stddev_i(t_list_int const i_lst)
{
	return (ft_sqrt)
}
inline t_float				ft_stat_stddev_f(t_list_float const f_lst)
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

t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);
{

}
*/


t_prob_mass				ft_stat_new_pmf(t_u32 len)
{
	t_prob_mass	res;

	res.value = NULL;
	res.prob = NULL;
	res.len = 0;
	if (len == 0 ||
		!(res.value = malloc(len * sizeof(t_float))) ||
		!(res.prob = malloc(len * sizeof(t_float))))
		return (res);
	res.len = len;
	return (res);
}

void					ft_stat_free_pmf(t_prob_mass *drv)
{
#if HANDLE_NULLPOINTERS
	if (drv == NULL)
		return ;
#endif
	if (drv->value)
	{
		free(drv->value);
		drv->value = NULL;
	}
	if (drv->prob)
	{
		free(drv->prob);
		drv->prob = NULL;
	}
	drv->len = 0;
}

t_set_int				ft_stat_ilst_to_iset(t_list_int const ilst)
{
	t_list_int				res;
	t_list_int				set;
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
	free(set.data);
	return (res);
}

t_u32				ft_stat_ilst_count(t_list_int ilst, t_int elem)
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
t_prob_mass			ft_stat_ilst_to_pmf(t_list_int const ilst)
{
	t_prob_mass			res;
	t_list_int			set;
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

