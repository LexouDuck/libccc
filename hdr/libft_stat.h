/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_stat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STAT_H
#define LIBFT_STAT_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libft.h"

/*
** ************************************************************************** *|
**                                    Macros                                  *|
** ************************************************************************** *|
*/

#define Stat_Int_NewList				ft_stat_new_ilst
#define Stat_Int_FreeList				ft_stat_free_ilst
#define Stat_Int_MergeList				ft_stat_merge_ilst
#define Stat_Int_Quicksort				ft_stat_quicksort_i_new
#define Stat_Int_Quicksort_InPlace		ft_stat_quicksort_i
#define Stat_Int_Median					ft_stat_median_i
#define Stat_Int_Average				ft_stat_average_i
#define Stat_Int_Variance				ft_stat_variance_i
#define Stat_Int_StandardDeviation		ft_stat_stddev_i
#define Stat_Int_Decile					ft_stat_decile_i
#define Stat_Int_ProbabilityIsValid		ft_prob_is_valid_i

#define Stat_NewPMF				ft_stat_new_pmf
#define Stat_FreePMF			ft_stat_free_pmf
#define Stat_IntList_To_Set		ft_stat_ilst_to_iset
#define Stat_IntList_Count		ft_stat_ilst_count
#define Stat_IntList_To_PMF		ft_stat_ilst_to_pmf

#define Stat_Float_NewList				ft_stat_new_flst
#define Stat_Float_FreeList				ft_stat_free_flst
#define Stat_Float_MergeList			ft_stat_merge_flst
#define Stat_Float_Quicksort_f_n		ft_stat_quicksort_f_new
#define Stat_Float_Quicksort			ft_stat_quicksort_f
#define Stat_Float_Median				ft_stat_median_f
#define Stat_Float_Average				ft_stat_average_f
#define Stat_Float_Variance				ft_stat_variance_f
#define Stat_Float_StandardDeviation	ft_stat_stddev_f
#define Stat_Float_Decile				ft_stat_decile_f
#define Stat_Float_ProbabilityIsValid	ft_prob_is_valid_f

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

/*
**	This defines the amount of probabilistic approximation
*/
#define PROB_APPROX			0.000001



typedef struct	s_list_int_
{
	t_int		*data;
	t_u32		length;
}				s_list_int;
#define NULL_LIST_INT		((s_list_int){ 0, 0 })

typedef struct	s_list_float_
{
	t_float		*data;
	t_u32		length;
}				s_list_float;
#define NULL_LIST_FLOAT		((s_list_float){ 0, 0 })

/*
**	These types are used to signify a list with no duplicate values.
*/
typedef s_list_int		s_set_int;
typedef s_list_float	s_set_float;
/*
**	These types are used to signify a list whose values have been ordered.
*/
typedef s_list_int		s_sortedlist_int;
typedef s_list_float	s_sortedlist_float;

/*
** Remember:
**
** A random variable X is a function from an input set O to an output set V,
** where:
**		- The universe O of possible events is the input set of X.
**		- The universe O is endowed with a sigma-algebra A (think "power set or
**			appropriate continuous extension of the power set"). Events are the
**			members of A, or equivalently, events are the subsets of O.
**		- P is a measure over A with values in [0, 1] such that the event for
**			the whole of O is given measure 1 (=all possibilites). Generally P
**			is found/constructed by taking some obvious	measure M on O (like
**			Lebesgue or counting) and normalizing by defining for every event
**			'a' the following: P(a) = M(a) / M(O).
**		- The triplet (O, A, P) is called a probability space. It's in a sense
**			our "full" input space with all necessary structure.
**		- probability for a given output Y is the measure of the preimage of
**			Y by f. Ie, the measure of the set X in O, or element a in A,
**			such that f(X) = Y.
**			Eg, the probability of getting an even number on a uniform 6-sided
**			dice (event "e") is 1/2 because M(e) = #({2,4,6}) = 3 and
**			M(O) = #({1,2,3,4,5,6}) = 6 and P(e)= M(e) / M(O) = 3/6 = 1/2.
**		- "values" of X are the values in the output space V.
**		- the output set V is generally R, sometimes R^n, rarely N without
**			extending it to R naturally (ie, medians, average, etc. of integers
**			end up in the real numbers anyways).
**		- a probability distribution f is a function from V to [0,1] that
**			assigns its probability to each event, represented not as an element
**			of A, but as the (set of) value(s) of that event in V.
**		- if the input set is discrete, f is a "probability mass function".
**		- if the input set is continuous, f is a "probability density function".
**
** To summarize, there are 3 major spaces: (O, A, P), V and [0,1], and they are
** linked thus:
**		- X: (O, A, P) -> V
**		- P: (O, A, P) -> [0, 1]
**		- f: V -> [0, 1]
**
** In the following implementation, discrete universes are kept finite and
** indexed, each atomic event is given by an index of the list.
** "value[i]" corresponds to X(i); "prob[i]" corresponds to f(X(i)).
*/

/*
** A struct for the probability mass function describing a discrete random var.
*/
typedef struct	s_prob_mass_
{
	t_float		*value;
	t_float		*prob;
	t_u32		length;
}				s_prob_mass;



/*
** ************************************************************************** *|
**                         Statistics & Probabilities                         *|
** ************************************************************************** *|
*/

s_list_int			ft_stat_new_ilst(t_u32 length);
s_list_float		ft_stat_new_flst(t_u32 length);

void				ft_stat_free_ilst(s_list_int *ilst);
void				ft_stat_free_flst(s_list_float *flst);



s_list_int			ft_stat_merge_ilst(s_list_int *start, s_list_int *append);
s_list_float		ft_stat_merge_flst(s_list_float *start, s_list_float *append);

s_list_int 			ft_stat_quicksort_i_new(s_list_int const ilst);
void				ft_stat_quicksort_i(s_list_int ilst);
s_list_float 		ft_stat_quicksort_f_new(s_list_float const flst);
void				ft_stat_quicksort_f(s_list_float flst);

/*
** List is supposed to be already in order for this to return the right result.
*/
t_float				ft_stat_median_i(s_sortedlist_int const ilst);
t_float				ft_stat_median_f(s_sortedlist_float const flst);

t_float				ft_stat_average_i(s_list_int const ilst);
t_float				ft_stat_average_f(s_list_float const flst);

t_float				ft_stat_variance_i(s_list_int const ilst);
t_float				ft_stat_variance_f(s_list_float const flst);

t_float				ft_stat_stddev_i(s_list_int const ilst);
t_float				ft_stat_stddev_f(s_list_float const flst);

/*
void				ft_stat_decile_i(s_list_int const ilst);
void				ft_stat_decile_f(s_list_float const flst);

t_bool				ft_prob_is_valid_i(t_prob_sample_i const i_problst);
t_bool				ft_prob_is_valid_f(t_prob_sample_f const f_problst);
*/

s_prob_mass			ft_stat_new_pmf(t_u32 length);
void				ft_stat_free_pmf(s_prob_mass *drv);
s_list_int			ft_stat_ilst_to_iset(s_list_int const ilst);
t_u32				ft_stat_ilst_count(s_list_int ilst, t_int elem);
s_prob_mass			ft_stat_ilst_to_pmf(s_list_int const ilst);

#endif
