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
/*!@group{libccc_math_stat,57,libccc/math/stat.h}
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
typedef struct array_fixed	s_array_fixed;	//!< @see "libccc/monad/array.h"
typedef struct array_float	s_array_float;	//!< @see "libccc/monad/array.h"

// TODO implement stat functions for `fixed` type

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef s_array_int		s_set_int;		//!< This type represents a list of integers with no duplicate values
typedef s_array_fixed	s_set_fixed;	//!< This type represents a list of fixed-point numbers with no duplicate values
typedef s_array_float	s_set_float;	//!< This type represents a list of floating-point numbers with no duplicate values

typedef s_array_int		s_sorted_int;	//!< This type represents a list of integers whose values are ordered from smallest to largest
typedef s_array_fixed	s_sorted_fixed;	//!< This type represents a list of fixed-point numbers whose values are ordered from smallest to largest
typedef s_array_float	s_sorted_float;	//!< This type represents a list of floating-point numbers whose values are ordered from smallest to largest



//! The amount of probabilistic approximation for libccc/math/stat functions
#define PROB_APPROX	(0.000001)

//! A struct for the probability mass function describing a discrete random var.
typedef struct prob_mass
{
	t_float	*value;		// TODO document this
	t_float	*prob;		// TODO document this
	t_uint	length;		// TODO document this
}	s_prob_mass;



/*
** ************************************************************************** *|
**                         Statistics & Probabilities                         *|
** ************************************************************************** *|
*/

//!@doc TODO document this
//!@{
s_prob_mass					Stat_ProbMassFunc_New(t_uint length);
#define c_pmfnew			Stat_ProbMassFunc_New
//!@}

//!@doc TODO document this
//!@{
void						Stat_ProbMassFunc_Delete(s_prob_mass *drv);
#define c_pmfdel			Stat_ProbMassFunc_Delete
#define c_pmffree			Stat_ProbMassFunc_Delete
//!@}

//!@doc TODO document this
//!@{
s_array_int					Stat_Int_New(t_uint length);
#define c_ilstnew			Stat_Int_New
s_array_fixed				Stat_Fixed_New(t_uint length);
#define c_qlstnew			Stat_Fixed_New
s_array_float				Stat_Float_New(t_uint length);
#define c_flstnew			Stat_Float_New
//!@}

//!@doc TODO document this
//!@{
void						Stat_Int_Delete(s_array_int* ilst);
#define c_ilstdel			Stat_Int_Delete
#define c_ilstfree			Stat_Int_Delete
void						Stat_Fixed_Delete(s_array_fixed* qlst);
#define c_qlstdel			Stat_Fixed_Delete
#define c_qlstfree			Stat_Fixed_Delete
void						Stat_Float_Delete(s_array_float* flst);
#define c_flstdel			Stat_Float_Delete
#define c_flstfree			Stat_Float_Delete
//!@}

//!@doc TODO document this
//!@{
s_array_int					Stat_Int_Duplicate(s_array_int const ilst);
#define c_ilstdup			Stat_Int_Duplicate
s_array_fixed				Stat_Fixed_Duplicate(s_array_fixed const qlst);
#define c_qlstdup			Stat_Fixed_Duplicate
s_array_float				Stat_Float_Duplicate(s_array_float const flst);
#define c_flstdup			Stat_Float_Duplicate
//!@}

//!@doc TODO document this
//!@{
s_array_int					Stat_Int_Concat(s_array_int* start, s_array_int* append);
#define c_ilstcat			Stat_Int_Concat
#define c_ilstconcat		Stat_Int_Concat
s_array_fixed				Stat_Fixed_Concat(s_array_fixed* start, s_array_fixed* append);
#define c_qlstcat			Stat_Fixed_Concat
#define c_qlstconcat		Stat_Fixed_Concat
s_array_float				Stat_Float_Concat(s_array_float* start, s_array_float* append);
#define c_flstcat			Stat_Float_Concat
#define c_flstconcat		Stat_Float_Concat
//!@}

//!@doc TODO document this
//!@{
t_uint						Stat_Int_Count(s_array_int ilst, t_sint elem);
#define c_ilstn				Stat_Int_Count
#define c_ilstcount			Stat_Int_Count
t_uint						Stat_Fixed_Count(s_array_fixed qlst, t_fixed elem);
#define c_qlstn				Stat_Fixed_Count
#define c_qlstcount			Stat_Fixed_Count
t_uint						Stat_Float_Count(s_array_float flst, t_float elem);
#define c_flstn				Stat_Float_Count
#define c_flstcount			Stat_Float_Count
//!@}

//!@doc TODO document this
//!@{
s_array_int					Stat_Int_ToSet(s_array_int const ilst);
#define c_ilsttoset			Stat_Int_ToSet
#define c_ilsttoiset		Stat_Int_ToSet
s_array_fixed				Stat_Fixed_ToSet(s_array_fixed const qlst);
#define c_qlsttoset			Stat_Fixed_ToSet
#define c_qlsttoqset		Stat_Fixed_ToSet
s_array_float				Stat_Float_ToSet(s_array_float const flst);
#define c_flsttoset			Stat_Float_ToSet
#define c_flsttofset		Stat_Float_ToSet
//!@}

//!@doc Returns the probability distribution of an array of integers.
//!@{
s_prob_mass					Stat_Int_ToPMF(s_array_int const ilst);
#define c_ilstpmf			Stat_Int_ToPMF
#define c_ilsttopmf			Stat_Int_ToPMF
s_prob_mass					Stat_Fixed_ToPMF(s_array_fixed const qlst);
#define c_qlstpmf			Stat_Fixed_ToPMF
#define c_qlsttopmf			Stat_Fixed_ToPMF
s_prob_mass					Stat_Float_ToPMF(s_array_float const flst);
#define c_flstpmf			Stat_Float_ToPMF
#define c_flsttopmf			Stat_Float_ToPMF
//!@}

//!@doc TODO document this
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/algorithm/qsort}
*/
//!@{
void						Stat_Int_Quicksort_InPlace(s_array_int ilst);
#define c_ilstsort			Stat_Int_Quicksort_InPlace
#define c_ilstqsort			Stat_Int_Quicksort_InPlace
void						Stat_Fixed_Quicksort_InPlace(s_array_fixed qlst);
#define c_qlstsort			Stat_Fixed_Quicksort_InPlace
#define c_qlstqsort			Stat_Fixed_Quicksort_InPlace
void						Stat_Float_Quicksort_InPlace(s_array_float flst);
#define c_flstsort			Stat_Float_Quicksort_InPlace
#define c_flstqsort			Stat_Float_Quicksort_InPlace
//!@}

//!@doc TODO document this
//!@{
s_array_int 				Stat_Int_Quicksort(s_array_int const ilst);
#define c_ilstsortnew		Stat_Int_Quicksort
#define c_ilstqsortnew		Stat_Int_Quicksort
s_array_fixed 				Stat_Fixed_Quicksort(s_array_fixed const qlst);
#define c_qlstsortnew		Stat_Fixed_Quicksort
#define c_qlstqsortnew		Stat_Fixed_Quicksort
s_array_float 				Stat_Float_Quicksort(s_array_float const flst);
#define c_flstsortnew		Stat_Float_Quicksort
#define c_flstqsortnew		Stat_Float_Quicksort
//!@}

//!@doc TODO document this
//!@{
t_sint						Stat_Int_GetMin(s_array_int const values);
#define c_ilstmin			Stat_Int_GetMin
#define c_ilstgetmin		Stat_Int_GetMin
t_fixed						Stat_Fixed_GetMin(s_array_fixed const values);
#define c_qlstmin			Stat_Fixed_GetMin
#define c_qlstgetmin		Stat_Fixed_GetMin
t_float						Stat_Float_GetMin(s_array_float const values);
#define c_flstmin			Stat_Float_GetMin
#define c_flstgetmin		Stat_Float_GetMin
//!@}

//!@doc TODO document this
//!@{
t_sint						Stat_Int_GetMax(s_array_int const values);
#define c_ilstmax			Stat_Int_GetMax
#define c_ilstgetmax		Stat_Int_GetMax
t_fixed						Stat_Fixed_GetMax(s_array_fixed const values);
#define c_qlstmax			Stat_Fixed_GetMax
#define c_qlstgetmax		Stat_Fixed_GetMax
t_float						Stat_Float_GetMax(s_array_float const values);
#define c_flstmax			Stat_Float_GetMax
#define c_flstgetmax		Stat_Float_GetMax
//!@}

//!@doc TODO document this
//!@{
t_sint						Stat_Int_Median(s_sorted_int const ilst);
#define c_ilstmdn			Stat_Int_Median
#define c_ilstmedian		Stat_Int_Median
t_fixed						Stat_Fixed_Median(s_sorted_fixed const qlst);
#define c_qlstmdn			Stat_Fixed_Median
#define c_qlstmedian		Stat_Fixed_Median
t_float						Stat_Float_Median(s_sorted_float const flst);
#define c_flstmdn			Stat_Float_Median
#define c_flstmedian		Stat_Float_Median
//!@}

//!@doc TODO document this
//!@{
t_float						Stat_Int_Average(s_array_int const ilst);
#define c_ilstavg			Stat_Int_Average
#define c_ilstaverage		Stat_Int_Average
t_float						Stat_Fixed_Average(s_array_fixed const qlst);
#define c_qlstavg			Stat_Fixed_Average
#define c_qlstaverage		Stat_Fixed_Average
t_float						Stat_Float_Average(s_array_float const flst);
#define c_flstavg			Stat_Float_Average
#define c_flstaverage		Stat_Float_Average
//!@}

//!@doc TODO document this
//!@{
t_float						Stat_Int_Variance(s_array_int const ilst);
#define c_ilstvar			Stat_Int_Variance
#define c_ilstvariance		Stat_Int_Variance
t_float						Stat_Fixed_Variance(s_array_fixed const qlst);
#define c_qlstvar			Stat_Fixed_Variance
#define c_qlstvariance		Stat_Fixed_Variance
t_float						Stat_Float_Variance(s_array_float const flst);
#define c_flstvar			Stat_Float_Variance
#define c_flstvariance		Stat_Float_Variance
//!@}

//!@doc TODO document this
//!@{
t_float						Stat_Int_StandardDeviation(s_array_int const ilst);
#define c_ilstdev			Stat_Int_StandardDeviation
#define c_ilststddev		Stat_Int_StandardDeviation
t_float						Stat_Fixed_StandardDeviation(s_array_fixed const qlst);
#define c_qlstdev			Stat_Fixed_StandardDeviation
#define c_qlststddev		Stat_Fixed_StandardDeviation
t_float						Stat_Float_StandardDeviation(s_array_float const flst);
#define c_flstdev			Stat_Float_StandardDeviation
#define c_flststddev		Stat_Float_StandardDeviation
//!@}

//!@doc TODO document this
//!@{
void						Stat_Int_Decile(s_array_int const ilst);
#define c_ilstdec			Stat_Int_Decile
#define c_ilstdecile		Stat_Int_Decile
void						Stat_Fixed_Decile(s_array_fixed const qlst);
#define c_qlstdec			Stat_Fixed_Decile
#define c_qlstdecile		Stat_Fixed_Decile
void						Stat_Float_Decile(s_array_float const flst);
#define c_flstdec			Stat_Float_Decile
#define c_flstdecile		Stat_Float_Decile
//!@}

//!@doc TODO document this
//!@{
t_bool						Stat_Int_ProbabilityIsValid(s_array_int const prob_ilst);
#define c_ilstprobvalid		Stat_Int_ProbabilityIsValid
t_bool						Stat_Fixed_ProbabilityIsValid(s_array_fixed const prob_qlst);
#define c_qlstprobvalid		Stat_Fixed_ProbabilityIsValid
t_bool						Stat_Float_ProbabilityIsValid(s_array_float const prob_flst);
#define c_flstprobvalid		Stat_Float_ProbabilityIsValid
//!@}



/*! @endgroup */
HEADER_END
#endif
