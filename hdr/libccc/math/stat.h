/*============================================================================*\
||                                            ______________________________  ||
||  libccc/math/stat.h                       |    __    __  ___      _____  | ||
||                                           |   / /\  / /\/ . |\   /  __|\ | ||
||  https://github.com/LexouDuck/libccc.git  |  / /_/ / / / . <_/  |  /___| | ||
||                                           | /___/\/_/ /___,'\   \____/\  | ||
|| Comprehensive|Cross-platform|Customizable | \____/\__/\____,'    \____/  | ||
|| This source code follows the MIT License. |______________________________| ||
||                                                                            ||
\*============================================================================*/

#ifndef __LIBCCC_MATH_STAT_H
#define __LIBCCC_MATH_STAT_H
/*!@group{libccc_math_stat}
**
**	This header defines some common statistics functions, for lists of int/float
**
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

// TODO add other function macros for integral, distance, etc

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"

HEADER_CPP

typedef struct array_int	s_array_int;	//!< @see "libccc/monad/array.h"
typedef struct array_float	s_array_float;	//!< @see "libccc/monad/array.h"

// TODO implement stat functions for `fixed` type

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef s_array_int		s_set_int;		//!< This type represents a list of integers with no duplicate values
typedef s_array_float	s_set_float;	//!< This type represents a list of floats with no duplicate values

typedef s_array_int		s_sorted_int;	//!< This type represents a list of integers whose values are ordered from smallest to largest
typedef s_array_float	s_sorted_float;	//!< This type represents a list of floats whose values are ordered from smallest to largest



//! The amount of probabilistic approximation for libccc/math/stat functions
#define PROB_APPROX			(0.000001)

//! A struct for the probability mass function describing a discrete random var.
typedef struct prob_mass
{
	t_float		*value;		// TODO document this
	t_float		*prob;		// TODO document this
	t_uint		length;		// TODO document this
}	s_prob_mass;



/*
** ************************************************************************** *|
**                         Statistics & Probabilities                         *|
** ************************************************************************** *|
*/

//!@doc TODO document this
//!@{
s_array_int						Stat_Int_NewList(t_uint length);
#define c_stat_new_ilst			Stat_Int_NewList
//!@}

//!@doc TODO document this
//!@{
void							Stat_Int_FreeList(s_array_int* ilst);
#define c_stat_free_ilst		Stat_Int_FreeList
//!@}

//!@doc TODO document this
//!@{
s_array_int						Stat_Int_MergeList(s_array_int* start, s_array_int* append);
#define c_stat_merge_ilst		Stat_Int_MergeList
//!@}

//!@doc TODO document this
//!@{
s_array_int 					Stat_Int_Quicksort(s_array_int const ilst);
#define c_stat_quicksort_i_new	Stat_Int_Quicksort
//!@}

//!@doc TODO document this
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/algorithm/qsort}
*/
//!@{
void							Stat_Int_Quicksort_InPlace(s_array_int ilst);
#define c_stat_quicksort_i		Stat_Int_Quicksort_InPlace
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Int_Median(s_sorted_int const ilst);
#define c_stat_median_i			Stat_Int_Median
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Int_Average(s_array_int const ilst);
#define c_stat_average_i		Stat_Int_Average
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Int_Variance(s_array_int const ilst);
#define c_stat_variance_i		Stat_Int_Variance
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Int_StandardDeviation(s_array_int const ilst);
#define c_stat_stddev_i			Stat_Int_StandardDeviation
//!@}

//!@doc TODO document this
//!@{
void							Stat_Int_Decile(s_array_int const ilst);
#define c_stat_decile_i			Stat_Int_Decile
//!@}

//! TODO implement & document this
//t_bool						Stat_Int_ProbabilityIsValid(t_prob_sample_i const i_problst);
//#define c_prob_is_valid_i		Stat_Int_ProbabilityIsValid



//!@doc TODO document this
//!@{
s_array_float					Stat_Float_NewList(t_uint length);
#define c_stat_new_flst			Stat_Float_NewList
//!@}

//!@doc TODO document this
//!@{
void							Stat_Float_FreeList(s_array_float* flst);
#define c_stat_free_flst		Stat_Float_FreeList
//!@}

//!@doc TODO document this
//!@{
s_array_float					Stat_Float_MergeList(s_array_float* start, s_array_float* append);
#define c_stat_merge_flst		Stat_Float_MergeList
//!@}

//!@doc TODO document this
//!@{
s_array_float 					Stat_Float_Quicksort(s_array_float const flst);
#define c_stat_quicksort_f_new	Stat_Float_Quicksort
//!@}

//!@doc TODO document this
//!@{
void							Stat_Float_Quicksort_InPlace(s_array_float flst);
#define c_stat_quicksort_f		Stat_Float_Quicksort_InPlace
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Float_Median(s_sorted_float const flst);
#define c_stat_median_f			Stat_Float_Median
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Float_Average(s_array_float const flst);
#define c_stat_average_f		Stat_Float_Average
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Float_Variance(s_array_float const flst);
#define c_stat_variance_f		Stat_Float_Variance
//!@}

//!@doc TODO document this
//!@{
t_float							Stat_Float_StandardDeviation(s_array_float const flst);
#define c_stat_stddev_f			Stat_Float_StandardDeviation
//!@}

//!@doc TODO document this
//!@{
void							Stat_Float_Decile(s_array_float const flst);
#define c_stat_decile_f			Stat_Float_Decile
//!@}

//! TODO implement & document this
//t_bool						Stat_Float_ProbabilityIsValid(t_prob_sample_f const f_problst);
//#define c_prob_is_valid_f		Stat_Float_ProbabilityIsValid



//!@doc TODO document this
//!@{
s_prob_mass						Stat_NewPMF(t_uint length);
#define c_stat_new_pmf			Stat_NewPMF
//!@}

//!@doc TODO document this
//!@{
void							Stat_FreePMF(s_prob_mass *drv);
#define c_stat_free_pmf			Stat_FreePMF
//!@}

//!@doc TODO document this
//!@{
s_array_int						Stat_IntList_To_Set(s_array_int const ilst);
#define c_stat_ilst_to_iset		Stat_IntList_To_Set
//!@}

//!@doc TODO document this
//!@{
t_uint							Stat_IntList_Count(s_array_int ilst, t_sint elem);
#define c_stat_ilst_count		Stat_IntList_Count
//!@}

//!@doc Returns the probability distribution of an array of integers.
//!@{
s_prob_mass						Stat_IntList_To_PMF(s_array_int const ilst);
#define c_stat_ilst_to_pmf		Stat_IntList_To_PMF
//!@}



/*! @endgroup */
HEADER_END
#endif
