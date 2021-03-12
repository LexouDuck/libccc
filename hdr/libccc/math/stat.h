/*============================================================================*/
/*                                            ______________________________  */
/*  libccc/math/stat.h                       |    __    __  ___      _____  | */
/*                                           |   / /\  / /\/ . |\   /  __|\ | */
/*  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | */
/*                                           | /___/\/_/ /___-'\   \____/\  | */
/* Comprehensive|Cross-platform|Customizable | \____/\__/\____-'    \____/  | */
/* This source code follows the MIT License. |______________________________| */
/*                                                                            */
/*============================================================================*/

#ifndef __LIBCCC_MATH_STAT_H
#define __LIBCCC_MATH_STAT_H
/*!@group{libccc_math_stat}
** @{
**	This header defines some common statistics functions, for lists of int/float
**
**	@file
*/

// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc.h"

HEADER_CPP

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

//! This struct stores a list of integer values (contiguously, like an array)
typedef struct	s_list_int_
{
	t_sint		*data;		//!< The list of integer values
	t_u32		length;		//!< The amount of items in the list
}				s_list_int;

//! Define the value for an empty list of integers
#define NULL_LIST_INT		((s_list_int){ 0, 0 })



//! This struct stores a list of float values (contiguously, like an array)
typedef struct	s_list_float_
{
	t_float		*data;		//!< The list of float values
	t_u32		length;		//!< The amount of items in the list
}				s_list_float;

//! Define the value for an empty list of floats
#define NULL_LIST_FLOAT		((s_list_float){ 0, 0 })



typedef s_list_int		s_set_int;			//!< This type represents a list of integers with no duplicate values
typedef s_list_float	s_set_float;		//!< This type represents a list of floats with no duplicate values

typedef s_list_int		s_sortedlist_int;	//!< This type represents a list of integers whose values are ordered from smallest to largest
typedef s_list_float	s_sortedlist_float;	//!< This type represents a list of floats whose values are ordered from smallest to largest



/*! @file libccc/math/stat.h
**	Remember:
**
**	A random variable X is a function from an input set O to an output set V,
**	where:
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
**	To summarize, there are 3 major spaces: (O, A, P), V and [0,1], and they are
**	linked thus:
**		- X: (O, A, P) -> V
**		- P: (O, A, P) -> [0, 1]
**		- f: V -> [0, 1]
**
**	In the following implementation, discrete universes are kept finite and
**	indexed, each atomic event is given by an index of the list.
**	"value[i]" corresponds to X(i); "prob[i]" corresponds to f(X(i)).
*/

//! The amount of probabilistic approximation for libccc/math/stat functions
#define PROB_APPROX			(0.000001)

//! A struct for the probability mass function describing a discrete random var.
typedef struct	s_prob_mass_
{
	t_float		*value;		// TODO document this
	t_float		*prob;		// TODO document this
	t_u32		length;		// TODO document this
}				s_prob_mass;



/*
** ************************************************************************** *|
**                         Statistics & Probabilities                         *|
** ************************************************************************** *|
*/

//! TODO document this
s_list_int						Stat_Int_NewList(t_u32 length);
#define c_stat_new_ilst			Stat_Int_NewList

//! TODO document this
void							Stat_Int_FreeList(s_list_int* ilst);
#define c_stat_free_ilst		Stat_Int_FreeList

//! TODO document this
s_list_int						Stat_Int_MergeList(s_list_int* start, s_list_int* append);
#define c_stat_merge_ilst		Stat_Int_MergeList

//! TODO document this
/*!
**	@isostd{https://en.cppreference.com/w/c/algorithm/qsort}
**
*/
s_list_int 						Stat_Int_Quicksort(s_list_int const ilst);
#define c_stat_quicksort_i_new	Stat_Int_Quicksort

//! TODO document this
void							Stat_Int_Quicksort_InPlace(s_list_int ilst);
#define c_stat_quicksort_i		Stat_Int_Quicksort_InPlace

//! TODO document this
t_float							Stat_Int_Median(s_sortedlist_int const ilst);
#define c_stat_median_i			Stat_Int_Median

//! TODO document this
t_float							Stat_Int_Average(s_list_int const ilst);
#define c_stat_average_i		Stat_Int_Average

//! TODO document this
t_float							Stat_Int_Variance(s_list_int const ilst);
#define c_stat_variance_i		Stat_Int_Variance

//! TODO document this
t_float							Stat_Int_StandardDeviation(s_list_int const ilst);
#define c_stat_stddev_i			Stat_Int_StandardDeviation

//! TODO document this
void							Stat_Int_Decile(s_list_int const ilst);
#define c_stat_decile_i			Stat_Int_Decile

//! TODO implement & document this
//t_bool						Stat_Int_ProbabilityIsValid(t_prob_sample_i const i_problst);
//#define c_prob_is_valid_i		Stat_Int_ProbabilityIsValid



//! TODO document this
s_list_float					Stat_Float_NewList(t_u32 length);
#define c_stat_new_flst			Stat_Float_NewList

//! TODO document this
void							Stat_Float_FreeList(s_list_float* flst);
#define c_stat_free_flst		Stat_Float_FreeList

//! TODO document this
s_list_float					Stat_Float_MergeList(s_list_float* start, s_list_float* append);
#define c_stat_merge_flst		Stat_Float_MergeList

//! TODO document this
s_list_float 					Stat_Float_Quicksort_f_n(s_list_float const flst);
#define c_stat_quicksort_f_new	Stat_Float_Quicksort_f_n

//! TODO document this
void							Stat_Float_Quicksort(s_list_float flst);
#define c_stat_quicksort_f		Stat_Float_Quicksort

//! TODO document this
t_float							Stat_Float_Median(s_sortedlist_float const flst);
#define c_stat_median_f			Stat_Float_Median

//! TODO document this
t_float							Stat_Float_Average(s_list_float const flst);
#define c_stat_average_f		Stat_Float_Average

//! TODO document this
t_float							Stat_Float_Variance(s_list_float const flst);
#define c_stat_variance_f		Stat_Float_Variance

//! TODO document this
t_float							Stat_Float_StandardDeviation(s_list_float const flst);
#define c_stat_stddev_f			Stat_Float_StandardDeviation

//! TODO document this
void							Stat_Float_Decile(s_list_float const flst);
#define c_stat_decile_f			Stat_Float_Decile

//! TODO implement & document this
//t_bool							Stat_Float_ProbabilityIsValid(t_prob_sample_f const f_problst);
//#define c_prob_is_valid_f		Stat_Float_ProbabilityIsValid



//! TODO document this
s_prob_mass						Stat_NewPMF(t_u32 length);
#define c_stat_new_pmf			Stat_NewPMF

//! TODO document this
void							Stat_FreePMF(s_prob_mass *drv);
#define c_stat_free_pmf			Stat_FreePMF

//! TODO document this
s_list_int						Stat_IntList_To_Set(s_list_int const ilst);
#define c_stat_ilst_to_iset		Stat_IntList_To_Set

//! TODO document this
t_u32							Stat_IntList_Count(s_list_int ilst, t_sint elem);
#define c_stat_ilst_count		Stat_IntList_Count

//! TODO document this
s_prob_mass						Stat_IntList_To_PMF(s_list_int const ilst);
#define c_stat_ilst_to_pmf		Stat_IntList_To_PMF



/*! @} */
HEADER_END
#endif
