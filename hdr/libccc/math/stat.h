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

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include "libccc/int.h"
#include "libccc/fixed.h"
#include "libccc/float.h"

HEADER_CPP

typedef struct array_uint	s_array_uint;	//!< @see "libccc/generic/array.h"
typedef struct array_sint	s_array_sint;	//!< @see "libccc/generic/array.h"
typedef struct array_fixed	s_array_fixed;	//!< @see "libccc/generic/array.h"
typedef struct array_float	s_array_float;	//!< @see "libccc/generic/array.h"

/*============================================================================*\
||                                 Definitions                                ||
\*============================================================================*/

typedef s_array_uint	s_set_uint;		//!< This type represents a list of unsigned integers with no duplicate values
typedef s_array_sint	s_set_sint;		//!< This type represents a list of signed integers with no duplicate values
typedef s_array_fixed	s_set_fixed;	//!< This type represents a list of fixed-point numbers with no duplicate values
typedef s_array_float	s_set_float;	//!< This type represents a list of floating-point numbers with no duplicate values

typedef s_array_uint	s_sorted_uint;	//!< This type represents a list of unsigned integers whose values are ordered from smallest to largest
typedef s_array_sint	s_sorted_sint;	//!< This type represents a list of signed integers whose values are ordered from smallest to largest
typedef s_array_fixed	s_sorted_fixed;	//!< This type represents a list of fixed-point numbers whose values are ordered from smallest to largest
typedef s_array_float	s_sorted_float;	//!< This type represents a list of floating-point numbers whose values are ordered from smallest to largest



//! The amount of probabilistic approximation for libccc/math/stat functions
#define PROB_APPROX	(0.000001)

//! A struct for the probability mass function describing a discrete random var.
typedef struct prob_mass
{
	t_float*	value;		//!< TODO document this
	t_float*	prob;		//!< TODO document this
	t_uint		length;		//!< TODO document this
}	s_prob_mass;



// TODO add other function macros for integral, distance, etc

/*============================================================================*\
||                           Basic utility functions                          ||
\*============================================================================*/

//!@doc Creates a new sample of numbers.
//!@{
s_array_uint                Stat_UInt_New(t_uint length);
#define c_ustat_new         Stat_UInt_New
s_array_sint                Stat_SInt_New(t_uint length);
#define c_sstat_new         Stat_SInt_New
s_array_fixed               Stat_Fixed_New(t_uint length);
#define c_qstat_new         Stat_Fixed_New
s_array_float               Stat_Float_New(t_uint length);
#define c_fstat_new         Stat_Float_New
//!@}

//!@doc Deletes an existing sample of numbers.
//!@{
void                        Stat_UInt_Delete(s_array_uint* sample);
#define c_ustat_del         Stat_UInt_Delete
void                        Stat_SInt_Delete(s_array_sint* sample);
#define c_sstat_del         Stat_SInt_Delete
void                        Stat_Fixed_Delete(s_array_fixed* sample);
#define c_qstat_del         Stat_Fixed_Delete
void                        Stat_Float_Delete(s_array_float* sample);
#define c_fstat_del         Stat_Float_Delete
//!@}

//!@doc Duplicates a sample of numbers.
//!@{
s_array_uint                Stat_UInt_Duplicate(s_array_uint const sample);
#define c_ustat_dup         Stat_UInt_Duplicate
s_array_sint                Stat_SInt_Duplicate(s_array_sint const sample);
#define c_sstat_dup         Stat_SInt_Duplicate
s_array_fixed               Stat_Fixed_Duplicate(s_array_fixed const sample);
#define c_qstat_dup         Stat_Fixed_Duplicate
s_array_float               Stat_Float_Duplicate(s_array_float const sample);
#define c_fstat_dup         Stat_Float_Duplicate
//!@}

//!@doc Concatenates two samples of numbers into a newly allocated sample.
//!@{
s_array_uint                Stat_UInt_Concat(s_array_uint* start, s_array_uint* append);
#define c_ustat_concat      Stat_UInt_Concat
s_array_sint                Stat_SInt_Concat(s_array_sint* start, s_array_sint* append);
#define c_sstat_concat      Stat_SInt_Concat
s_array_fixed               Stat_Fixed_Concat(s_array_fixed* start, s_array_fixed* append);
#define c_qstat_concat      Stat_Fixed_Concat
s_array_float               Stat_Float_Concat(s_array_float* start, s_array_float* append);
#define c_fstat_concat      Stat_Float_Concat
//!@}

//!@doc Counts the amount of occurrences of the given `elem` in the given sample.
//!@{
t_uint                      Stat_UInt_Count(s_array_uint sample, t_uint elem);
#define c_ustat_count       Stat_UInt_Count
t_uint                      Stat_SInt_Count(s_array_sint sample, t_sint elem);
#define c_sstat_count       Stat_SInt_Count
t_uint                      Stat_Fixed_Count(s_array_fixed sample, t_fixed elem);
#define c_qstat_count       Stat_Fixed_Count
t_uint                      Stat_Float_Count(s_array_float sample, t_float elem);
#define c_fstat_count       Stat_Float_Count
//!@}

//!@doc Creates a copy of the given sample wherein all duplicate values have been removed.
//!@{
s_array_uint                Stat_UInt_ToSet(s_array_uint const sample);
#define c_ustat_toset       Stat_UInt_ToSet
s_array_sint                Stat_SInt_ToSet(s_array_sint const sample);
#define c_sstat_toset       Stat_SInt_ToSet
s_array_fixed               Stat_Fixed_ToSet(s_array_fixed const sample);
#define c_qstat_toset       Stat_Fixed_ToSet
s_array_float               Stat_Float_ToSet(s_array_float const sample);
#define c_fstat_toset       Stat_Float_ToSet
//!@}



//!@doc Sorts the numbers in the given sample in ascending order.
/*!
**	@isostd{C89,https://en.cppreference.com/w/c/algorithm/qsort}
*/
//!@{
void                        Stat_UInt_Sort_InPlace(s_array_uint sample);
#define c_ustat_sort        Stat_UInt_Sort_InPlace
void                        Stat_SInt_Sort_InPlace(s_array_sint sample);
#define c_sstat_sort        Stat_SInt_Sort_InPlace
void                        Stat_Fixed_Sort_InPlace(s_array_fixed sample);
#define c_qstat_sort        Stat_Fixed_Sort_InPlace
void                        Stat_Float_Sort_InPlace(s_array_float sample);
#define c_fstat_sort        Stat_Float_Sort_InPlace
//!@}

//!@doc Creates a copy of the given sample wherein all values are sorted in ascending order.
//!@{
s_array_uint                Stat_UInt_Sort(s_array_uint const sample);
#define c_ustat_sortnew     Stat_UInt_Sort
s_array_sint                Stat_SInt_Sort(s_array_sint const sample);
#define c_sstat_sortnew     Stat_SInt_Sort
s_array_fixed               Stat_Fixed_Sort(s_array_fixed const sample);
#define c_qstat_sortnew     Stat_Fixed_Sort
s_array_float               Stat_Float_Sort(s_array_float const sample);
#define c_fstat_sortnew     Stat_Float_Sort
//!@}



/*============================================================================*\
||                      Probability distribution functions                    ||
\*============================================================================*/

//!@doc TODO document this
//!@{
t_bool                      Stat_UInt_ProbabilityIsValid(s_array_uint const prob_sample);
#define c_ustat_probisvalid Stat_UInt_ProbabilityIsValid
t_bool                      Stat_SInt_ProbabilityIsValid(s_array_sint const prob_sample);
#define c_sstat_probisvalid Stat_SInt_ProbabilityIsValid
t_bool                      Stat_Fixed_ProbabilityIsValid(s_array_fixed const prob_sample);
#define c_qstat_probisvalid Stat_Fixed_ProbabilityIsValid
t_bool                      Stat_Float_ProbabilityIsValid(s_array_float const prob_sample);
#define c_fstat_probisvalid Stat_Float_ProbabilityIsValid
//!@}



//!@doc Returns the probability mass function distribution of a sample of numbers
//!@{
s_prob_mass                 Stat_UInt_ProbabilityMassFunction(s_array_uint const sample);
#define c_ustat_pmf         Stat_UInt_ProbabilityMassFunction
#define Stat_UInt_PMF       Stat_UInt_ProbabilityMassFunction
s_prob_mass                 Stat_SInt_ProbabilityMassFunction(s_array_sint const sample);
#define c_sstat_pmf         Stat_SInt_ProbabilityMassFunction
#define Stat_SInt_PMF       Stat_SInt_ProbabilityMassFunction
s_prob_mass                 Stat_Fixed_ProbabilityMassFunction(s_array_fixed const sample);
#define c_qstat_pmf         Stat_Fixed_ProbabilityMassFunction
#define Stat_Fixed_PMF      Stat_Fixed_ProbabilityMassFunction
s_prob_mass                 Stat_Float_ProbabilityMassFunction(s_array_float const sample);
#define c_fstat_pmf         Stat_Float_ProbabilityMassFunction
#define Stat_Float_PMF      Stat_Float_ProbabilityMassFunction
//!@}

//!@doc TODO document this
//!@{
s_prob_mass                 Stat_ProbabilityMassFunction_New(t_uint length);
#define c_pmfnew            Stat_ProbabilityMassFunction_New
#define Stat_PMF_New        Stat_ProbabilityMassFunction_New
//!@}

//!@doc TODO document this
//!@{
void                        Stat_ProbabilityMassFunction_Delete(s_prob_mass* pmf);
#define c_pmfdel            Stat_ProbabilityMassFunction_Delete
#define Stat_PMF_Delete     Stat_ProbabilityMassFunction_Delete
//!@}



/*============================================================================*\
||                         Statistics & Probabilities                         ||
\*============================================================================*/

//!@doc TODO document this
//!@{
t_uint                               Stat_UInt_GetMin(s_array_uint const sample);
#define c_ustat_min                  Stat_UInt_GetMin
t_sint                               Stat_SInt_GetMin(s_array_sint const sample);
#define c_sstat_min                  Stat_SInt_GetMin
t_fixed                              Stat_Fixed_GetMin(s_array_fixed const sample);
#define c_qstat_min                  Stat_Fixed_GetMin
t_float                              Stat_Float_GetMin(s_array_float const sample);
#define c_fstat_min                  Stat_Float_GetMin
//!@}

//!@doc TODO document this
//!@{
t_uint                               Stat_UInt_GetMax(s_array_uint const sample);
#define c_ustat_max                  Stat_UInt_GetMax
t_sint                               Stat_SInt_GetMax(s_array_sint const sample);
#define c_sstat_max                  Stat_SInt_GetMax
t_fixed                              Stat_Fixed_GetMax(s_array_fixed const sample);
#define c_qstat_max                  Stat_Fixed_GetMax
t_float                              Stat_Float_GetMax(s_array_float const sample);
#define c_fstat_max                  Stat_Float_GetMax
//!@}



//!@doc TODO document this : https://en.wikipedia.org/wiki/Quantile
//!@{
t_float*                             Stat_UInt_Quantiles(s_array_uint const sample, t_uint n);
#define c_ustat_quantiles            Stat_UInt_Quantiles
t_float*                             Stat_SInt_Quantiles(s_array_sint const sample, t_uint n);
#define c_sstat_quantiles            Stat_SInt_Quantiles
t_float*                             Stat_Fixed_Quantiles(s_array_fixed const sample, t_uint n);
#define c_qstat_quantiles            Stat_Fixed_Quantiles
t_float*                             Stat_Float_Quantiles(s_array_float const sample, t_uint n);
#define c_fstat_quantiles            Stat_Float_Quantiles
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Median
//!@{
t_float                              Stat_UInt_Median(s_array_uint const sample);
#define c_ustat_median               Stat_UInt_Median
t_float                              Stat_SInt_Median(s_array_sint const sample);
#define c_sstat_median               Stat_SInt_Median
t_float                              Stat_Fixed_Median(s_array_fixed const sample);
#define c_qstat_median               Stat_Fixed_Median
t_float                              Stat_Float_Median(s_array_float const sample);
#define c_fstat_median               Stat_Float_Median
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mode_(statistics)
//!@{
t_float                              Stat_UInt_Mode(s_array_uint const sample);
#define c_ustat_mode                 Stat_UInt_Mode
t_float                              Stat_SInt_Mode(s_array_sint const sample);
#define c_sstat_mode                 Stat_SInt_Mode
t_float                              Stat_Fixed_Mode(s_array_fixed const sample);
#define c_qstat_mode                 Stat_Fixed_Mode
t_float                              Stat_Float_Mode(s_array_float const sample);
#define c_fstat_mode                 Stat_Float_Mode
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Range_(statistics)
//!@{
t_float                              Stat_UInt_Range(s_array_uint const sample);
#define c_ustat_range                Stat_UInt_Range
t_float                              Stat_SInt_Range(s_array_sint const sample);
#define c_sstat_range                Stat_SInt_Range
t_float                              Stat_Fixed_Range(s_array_fixed const sample);
#define c_qstat_range                Stat_Fixed_Range
t_float                              Stat_Float_Range(s_array_float const sample);
#define c_fstat_range                Stat_Float_Range
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Midrange
//!@{
t_float                              Stat_UInt_Midrange(s_array_uint const sample);
#define c_ustat_midrange             Stat_UInt_Midrange
t_float                              Stat_SInt_Midrange(s_array_sint const sample);
#define c_sstat_midrange             Stat_SInt_Midrange
t_float                              Stat_Fixed_Midrange(s_array_fixed const sample);
#define c_qstat_midrange             Stat_Fixed_Midrange
t_float                              Stat_Float_Midrange(s_array_float const sample);
#define c_fstat_midrange             Stat_Float_Midrange
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Midhinge
//!@{
t_float                              Stat_UInt_Midhinge(s_array_uint const sample);
#define c_ustat_midhinge             Stat_UInt_Midhinge
t_float                              Stat_SInt_Midhinge(s_array_sint const sample);
#define c_sstat_midhinge             Stat_SInt_Midhinge
t_float                              Stat_Fixed_Midhinge(s_array_fixed const sample);
#define c_qstat_midhinge             Stat_Fixed_Midhinge
t_float                              Stat_Float_Midhinge(s_array_float const sample);
#define c_fstat_midhinge             Stat_Float_Midhinge
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Trimean
//!@{
t_float                              Stat_UInt_Trimean(s_array_uint const sample);
#define c_ustat_trimean              Stat_UInt_Trimean
t_float                              Stat_SInt_Trimean(s_array_sint const sample);
#define c_sstat_trimean              Stat_SInt_Trimean
t_float                              Stat_Fixed_Trimean(s_array_fixed const sample);
#define c_qstat_trimean              Stat_Fixed_Trimean
t_float                              Stat_Float_Trimean(s_array_float const sample);
#define c_fstat_trimean              Stat_Float_Trimean
//!@}



//!@doc TODO document this : https://en.wikipedia.org/wiki/Arithmetic_mean
//!@{
t_float                              Stat_UInt_Mean_Arithmetic(s_array_uint const sample);
#define c_ustat_mean_arithmetic      Stat_UInt_Mean_Arithmetic
t_float                              Stat_SInt_Mean_Arithmetic(s_array_sint const sample);
#define c_sstat_mean_arithmetic      Stat_SInt_Mean_Arithmetic
t_float                              Stat_Fixed_Mean_Arithmetic(s_array_fixed const sample);
#define c_qstat_mean_arithmetic      Stat_Fixed_Mean_Arithmetic
t_float                              Stat_Float_Mean_Arithmetic(s_array_float const sample);
#define c_fstat_mean_arithmetic      Stat_Float_Mean_Arithmetic
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Geometric_mean
//!@{
t_float                              Stat_UInt_Mean_Geometric(s_array_uint const sample);
#define c_ustat_mean_geometric       Stat_UInt_Mean_Geometric
t_float                              Stat_SInt_Mean_Geometric(s_array_sint const sample);
#define c_sstat_mean_geometric       Stat_SInt_Mean_Geometric
t_float                              Stat_Fixed_Mean_Geometric(s_array_fixed const sample);
#define c_qstat_mean_geometric       Stat_Fixed_Mean_Geometric
t_float                              Stat_Float_Mean_Geometric(s_array_float const sample);
#define c_fstat_mean_geometric       Stat_Float_Mean_Geometric
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Harmonic_mean
//!@{
t_float                              Stat_UInt_Mean_Harmonic(s_array_uint const sample);
#define c_ustat_mean_harmonic        Stat_UInt_Mean_Harmonic
t_float                              Stat_SInt_Mean_Harmonic(s_array_sint const sample);
#define c_sstat_mean_harmonic        Stat_SInt_Mean_Harmonic
t_float                              Stat_Fixed_Mean_Harmonic(s_array_fixed const sample);
#define c_qstat_mean_harmonic        Stat_Fixed_Mean_Harmonic
t_float                              Stat_Float_Mean_Harmonic(s_array_float const sample);
#define c_fstat_mean_harmonic        Stat_Float_Mean_Harmonic
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Contraharmonic_mean
//!@{
t_float                              Stat_UInt_Mean_Contraharmonic(s_array_uint const sample);
#define c_ustat_mean_contraharmonic  Stat_UInt_Mean_Contraharmonic
t_float                              Stat_SInt_Mean_Contraharmonic(s_array_sint const sample);
#define c_sstat_mean_contraharmonic  Stat_SInt_Mean_Contraharmonic
t_float                              Stat_Fixed_Mean_Contraharmonic(s_array_fixed const sample);
#define c_qstat_mean_contraharmonic  Stat_Fixed_Mean_Contraharmonic
t_float                              Stat_Float_Mean_Contraharmonic(s_array_float const sample);
#define c_fstat_mean_contraharmonic  Stat_Float_Mean_Contraharmonic
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Interquartile_mean
//!@{
t_float                              Stat_UInt_Mean_Interquartile(s_array_uint const sample);
#define c_ustat_mean_iq              Stat_UInt_Mean_Interquartile
t_float                              Stat_SInt_Mean_Interquartile(s_array_sint const sample);
#define c_sstat_mean_iq              Stat_SInt_Mean_Interquartile
t_float                              Stat_Fixed_Mean_Interquartile(s_array_fixed const sample);
#define c_qstat_mean_iq              Stat_Fixed_Mean_Interquartile
t_float                              Stat_Float_Mean_Interquartile(s_array_float const sample);
#define c_fstat_mean_iq              Stat_Float_Mean_Interquartile
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Quadratic_mean
//!@{
t_float                              Stat_UInt_Mean_Quadratic(s_array_uint const sample);
#define c_ustat_mean_pow2            Stat_UInt_Mean_Quadratic
t_float                              Stat_SInt_Mean_Quadratic(s_array_sint const sample);
#define c_sstat_mean_pow2            Stat_SInt_Mean_Quadratic
t_float                              Stat_Fixed_Mean_Quadratic(s_array_fixed const sample);
#define c_qstat_mean_pow2            Stat_Fixed_Mean_Quadratic
t_float                              Stat_Float_Mean_Quadratic(s_array_float const sample);
#define c_fstat_mean_pow2            Stat_Float_Mean_Quadratic
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Cubic_mean
//!@{
t_float                              Stat_UInt_Mean_Cubic(s_array_uint const sample);
#define c_ustat_mean_pow3            Stat_UInt_Mean_Cubic
t_float                              Stat_SInt_Mean_Cubic(s_array_sint const sample);
#define c_sstat_mean_pow3            Stat_SInt_Mean_Cubic
t_float                              Stat_Fixed_Mean_Cubic(s_array_fixed const sample);
#define c_qstat_mean_pow3            Stat_Fixed_Mean_Cubic
t_float                              Stat_Float_Mean_Cubic(s_array_float const sample);
#define c_fstat_mean_pow3            Stat_Float_Mean_Cubic
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Power_mean
//!@{
t_float                              Stat_UInt_Mean_Power(s_array_uint const sample, t_float power);
#define c_ustat_mean_power           Stat_UInt_Mean_Power
t_float                              Stat_SInt_Mean_Power(s_array_sint const sample, t_float power);
#define c_sstat_mean_power           Stat_SInt_Mean_Power
t_float                              Stat_Fixed_Mean_Power(s_array_fixed const sample, t_float power);
#define c_qstat_mean_power           Stat_Fixed_Mean_Power
t_float                              Stat_Float_Mean_Power(s_array_float const sample, t_float power);
#define c_fstat_mean_power           Stat_Float_Mean_Power
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Lehmer_mean
//!@{
t_float                              Stat_UInt_Mean_Lehmer(s_array_uint const sample, t_sint power);
#define c_ustat_mean_lehmer          Stat_UInt_Mean_Lehmer
t_float                              Stat_SInt_Mean_Lehmer(s_array_sint const sample, t_sint power);
#define c_sstat_mean_lehmer          Stat_SInt_Mean_Lehmer
t_float                              Stat_Fixed_Mean_Lehmer(s_array_fixed const sample, t_sint power);
#define c_qstat_mean_lehmer          Stat_Fixed_Mean_Lehmer
t_float                              Stat_Float_Mean_Lehmer(s_array_float const sample, t_sint power);
#define c_fstat_mean_lehmer          Stat_Float_Mean_Lehmer
//!@}



//!@doc TODO document this : https://en.wikipedia.org/wiki/Variance
//!@{
t_float                              Stat_UInt_Variance(s_array_uint const sample);
#define c_ustat_variance             Stat_UInt_Variance
t_float                              Stat_SInt_Variance(s_array_sint const sample);
#define c_sstat_variance             Stat_SInt_Variance
t_float                              Stat_Fixed_Variance(s_array_fixed const sample);
#define c_qstat_variance             Stat_Fixed_Variance
t_float                              Stat_Float_Variance(s_array_float const sample);
#define c_fstat_variance             Stat_Float_Variance
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Standard_deviation
//!@{
t_float                              Stat_UInt_StandardDeviation(s_array_uint const sample);
#define c_ustat_stddev               Stat_UInt_StandardDeviation
t_float                              Stat_SInt_StandardDeviation(s_array_sint const sample);
#define c_sstat_stddev               Stat_SInt_StandardDeviation
t_float                              Stat_Fixed_StandardDeviation(s_array_fixed const sample);
#define c_qstat_stddev               Stat_Fixed_StandardDeviation
t_float                              Stat_Float_StandardDeviation(s_array_float const sample);
#define c_fstat_stddev               Stat_Float_StandardDeviation
//!@}



//!@doc TODO document this : https://en.wikipedia.org/wiki/Coefficient_of_variation
//!@{
t_float                              Stat_UInt_CoefficientOfVariation(s_array_uint const sample);
#define c_ustat_cv                   Stat_UInt_CoefficientOfVariation
#define Stat_UInt_CV                 Stat_UInt_CoefficientOfVariation
t_float                              Stat_SInt_CoefficientOfVariation(s_array_sint const sample);
#define c_sstat_cv                   Stat_SInt_CoefficientOfVariation
#define Stat_SInt_CV                 Stat_SInt_CoefficientOfVariation
t_float                              Stat_Fixed_CoefficientOfVariation(s_array_fixed const sample);
#define c_qstat_cv                   Stat_Fixed_CoefficientOfVariation
#define Stat_Fixed_CV                Stat_Fixed_CoefficientOfVariation
t_float                              Stat_Float_CoefficientOfVariation(s_array_float const sample);
#define c_fstat_cv                   Stat_Float_CoefficientOfVariation
#define Stat_Float_CV                Stat_Float_CoefficientOfVariation
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Interquartile_range
//!@{
t_float                              Stat_UInt_InterquartileRange(s_array_uint const sample);
#define c_ustat_iqr                  Stat_UInt_InterquartileRange
#define Stat_UInt_IQR                Stat_UInt_InterquartileRange
t_float                              Stat_SInt_InterquartileRange(s_array_sint const sample);
#define c_sstat_iqr                  Stat_SInt_InterquartileRange
#define Stat_SInt_IQR                Stat_SInt_InterquartileRange
t_float                              Stat_Fixed_InterquartileRange(s_array_fixed const sample);
#define c_qstat_iqr                  Stat_Fixed_InterquartileRange
#define Stat_Fixed_IQR               Stat_Fixed_InterquartileRange
t_float                              Stat_Float_InterquartileRange(s_array_float const sample);
#define c_fstat_iqr                  Stat_Float_InterquartileRange
#define Stat_Float_IQR               Stat_Float_InterquartileRange
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Median_absolute_deviation
//!@{
t_float                              Stat_UInt_MedianAbsoluteDeviation(s_array_uint const sample);
#define c_ustat_mad                  Stat_UInt_MedianAbsoluteDeviation
#define Stat_UInt_MAD                Stat_UInt_MedianAbsoluteDeviation
t_float                              Stat_SInt_MedianAbsoluteDeviation(s_array_sint const sample);
#define c_sstat_mad                  Stat_SInt_MedianAbsoluteDeviation
#define Stat_SInt_MAD                Stat_SInt_MedianAbsoluteDeviation
t_float                              Stat_Fixed_MedianAbsoluteDeviation(s_array_fixed const sample);
#define c_qstat_mad                  Stat_Fixed_MedianAbsoluteDeviation
#define Stat_Fixed_MAD               Stat_Fixed_MedianAbsoluteDeviation
t_float                              Stat_Float_MedianAbsoluteDeviation(s_array_float const sample);
#define c_fstat_mad                  Stat_Float_MedianAbsoluteDeviation
#define Stat_Float_MAD               Stat_Float_MedianAbsoluteDeviation
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Average_absolute_deviation
//!@{
t_float                              Stat_UInt_AverageAbsoluteDeviation(s_array_uint const sample, t_uint center);
#define c_ustat_aad                  Stat_UInt_AverageAbsoluteDeviation
#define Stat_UInt_AAD                Stat_UInt_AverageAbsoluteDeviation
t_float                              Stat_SInt_AverageAbsoluteDeviation(s_array_sint const sample, t_sint center);
#define c_sstat_aad                  Stat_SInt_AverageAbsoluteDeviation
#define Stat_SInt_AAD                Stat_SInt_AverageAbsoluteDeviation
t_float                              Stat_Fixed_AverageAbsoluteDeviation(s_array_fixed const sample, t_fixed center);
#define c_qstat_aad                  Stat_Fixed_AverageAbsoluteDeviation
#define Stat_Fixed_AAD               Stat_Fixed_AverageAbsoluteDeviation
t_float                              Stat_Float_AverageAbsoluteDeviation(s_array_float const sample, t_float center);
#define c_fstat_aad                  Stat_Float_AverageAbsoluteDeviation
#define Stat_Float_AAD               Stat_Float_AverageAbsoluteDeviation
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Arithmetic%E2%80%93geometric_mean
//!@{
t_float                              Stat_UInt_ArithmeticGeometricMean(t_uint x, t_uint y);
#define c_ustat_agm                  Stat_UInt_ArithmeticGeometricMean
#define Stat_UInt_AGM                Stat_UInt_ArithmeticGeometricMean
t_float                              Stat_SInt_ArithmeticGeometricMean(t_sint x, t_sint y);
#define c_sstat_agm                  Stat_SInt_ArithmeticGeometricMean
#define Stat_SInt_AGM                Stat_SInt_ArithmeticGeometricMean
t_float                              Stat_Fixed_ArithmeticGeometricMean(t_fixed x, t_fixed y);
#define c_qstat_agm                  Stat_Fixed_ArithmeticGeometricMean
#define Stat_Fixed_AGM               Stat_Fixed_ArithmeticGeometricMean
t_float                              Stat_Float_ArithmeticGeometricMean(t_float x, t_float y);
#define c_fstat_agm                  Stat_Float_ArithmeticGeometricMean
#define Stat_Float_AGM               Stat_Float_ArithmeticGeometricMean
//!@}



/*============================================================================*\
||                         Statistics & Probabilities                         ||
\*============================================================================*/

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_signed_deviation
//!@{
t_float                              Stat_UInt_MeanSignedDeviation(s_array_uint const sample, t_uint const* expect);
#define c_ustat_msd                  Stat_UInt_MeanSignedDeviation
#define Stat_UInt_MSD                Stat_UInt_MeanSignedDeviation
t_float                              Stat_SInt_MeanSignedDeviation(s_array_sint const sample, t_sint const* expect);
#define c_sstat_msd                  Stat_SInt_MeanSignedDeviation
#define Stat_SInt_MSD                Stat_SInt_MeanSignedDeviation
t_float                              Stat_Fixed_MeanSignedDeviation(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_msd                  Stat_Fixed_MeanSignedDeviation
#define Stat_Fixed_MSD               Stat_Fixed_MeanSignedDeviation
t_float                              Stat_Float_MeanSignedDeviation(s_array_float const sample, t_float const* expect);
#define c_fstat_msd                  Stat_Float_MeanSignedDeviation
#define Stat_Float_MSD               Stat_Float_MeanSignedDeviation
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_squared_error
//!@{
t_float                              Stat_UInt_MeanSquaredError(s_array_uint const sample, t_uint const* expect);
#define c_ustat_mse                  Stat_UInt_MeanSquaredError
#define Stat_UInt_MSE                Stat_UInt_MeanSquaredError
t_float                              Stat_SInt_MeanSquaredError(s_array_sint const sample, t_sint const* expect);
#define c_sstat_mse                  Stat_SInt_MeanSquaredError
#define Stat_SInt_MSE                Stat_SInt_MeanSquaredError
t_float                              Stat_Fixed_MeanSquaredError(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_mse                  Stat_Fixed_MeanSquaredError
#define Stat_Fixed_MSE               Stat_Fixed_MeanSquaredError
t_float                              Stat_Float_MeanSquaredError(s_array_float const sample, t_float const* expect);
#define c_fstat_mse                  Stat_Float_MeanSquaredError
#define Stat_Float_MSE               Stat_Float_MeanSquaredError
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_absolute_error
//!@{
t_float                              Stat_UInt_MeanAbsoluteError(s_array_uint const sample, t_uint const* expect);
#define c_ustat_mae                  Stat_UInt_MeanAbsoluteError
#define Stat_UInt_MAE                Stat_UInt_MeanAbsoluteError
t_float                              Stat_SInt_MeanAbsoluteError(s_array_sint const sample, t_sint const* expect);
#define c_sstat_mae                  Stat_SInt_MeanAbsoluteError
#define Stat_SInt_MAE                Stat_SInt_MeanAbsoluteError
t_float                              Stat_Fixed_MeanAbsoluteError(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_mae                  Stat_Fixed_MeanAbsoluteError
#define Stat_Fixed_MAE               Stat_Fixed_MeanAbsoluteError
t_float                              Stat_Float_MeanAbsoluteError(s_array_float const sample, t_float const* expect);
#define c_fstat_mae                  Stat_Float_MeanAbsoluteError
#define Stat_Float_MAE               Stat_Float_MeanAbsoluteError
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_absolute_difference
//!@{
t_float                              Stat_UInt_MeanAbsoluteDifference(s_array_uint const sample, t_uint const* expect);
#define c_ustat_md                   Stat_UInt_MeanAbsoluteDifference
#define Stat_UInt_MD                 Stat_UInt_MeanAbsoluteDifference
t_float                              Stat_SInt_MeanAbsoluteDifference(s_array_sint const sample, t_sint const* expect);
#define c_sstat_md                   Stat_SInt_MeanAbsoluteDifference
#define Stat_SInt_MD                 Stat_SInt_MeanAbsoluteDifference
t_float                              Stat_Fixed_MeanAbsoluteDifference(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_md                   Stat_Fixed_MeanAbsoluteDifference
#define Stat_Fixed_MD                Stat_Fixed_MeanAbsoluteDifference
t_float                              Stat_Float_MeanAbsoluteDifference(s_array_float const sample, t_float const* expect);
#define c_fstat_md                   Stat_Float_MeanAbsoluteDifference
#define Stat_Float_MD                Stat_Float_MeanAbsoluteDifference
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_absolute_difference#Relative_mean_absolute_difference
//!@{
t_float                              Stat_UInt_RelativeMeanAbsoluteDifference(s_array_uint const sample, t_uint const* expect);
#define c_ustat_rmd                  Stat_UInt_RelativeMeanAbsoluteDifference
#define Stat_UInt_RMD                Stat_UInt_RelativeMeanAbsoluteDifference
t_float                              Stat_SInt_RelativeMeanAbsoluteDifference(s_array_sint const sample, t_sint const* expect);
#define c_sstat_rmd                  Stat_SInt_RelativeMeanAbsoluteDifference
#define Stat_SInt_RMD                Stat_SInt_RelativeMeanAbsoluteDifference
t_float                              Stat_Fixed_RelativeMeanAbsoluteDifference(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_rmd                  Stat_Fixed_RelativeMeanAbsoluteDifference
#define Stat_Fixed_RMD               Stat_Fixed_RelativeMeanAbsoluteDifference
t_float                              Stat_Float_RelativeMeanAbsoluteDifference(s_array_float const sample, t_float const* expect);
#define c_fstat_rmd                  Stat_Float_RelativeMeanAbsoluteDifference
#define Stat_Float_RMD               Stat_Float_RelativeMeanAbsoluteDifference
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Root_mean_square_deviation
//!@{
t_float                              Stat_UInt_RootMeanSquareDeviation(s_array_uint const sample, t_uint const* expect);
#define c_ustat_rmsd                 Stat_UInt_RootMeanSquareDeviation
#define Stat_UInt_RMSD               Stat_UInt_RootMeanSquareDeviation
t_float                              Stat_SInt_RootMeanSquareDeviation(s_array_sint const sample, t_sint const* expect);
#define c_sstat_rmsd                 Stat_SInt_RootMeanSquareDeviation
#define Stat_SInt_RMSD               Stat_SInt_RootMeanSquareDeviation
t_float                              Stat_Fixed_RootMeanSquareDeviation(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_rmsd                 Stat_Fixed_RootMeanSquareDeviation
#define Stat_Fixed_RMSD              Stat_Fixed_RootMeanSquareDeviation
t_float                              Stat_Float_RootMeanSquareDeviation(s_array_float const sample, t_float const* expect);
#define c_fstat_rmsd                 Stat_Float_RootMeanSquareDeviation
#define Stat_Float_RMSD              Stat_Float_RootMeanSquareDeviation
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_percentage_error
//!@{
t_float                              Stat_UInt_MeanPercentageError(s_array_uint const sample, t_uint const* expect);
#define c_ustat_mpe                  Stat_UInt_MeanPercentageError
#define Stat_UInt_MPE                Stat_UInt_MeanPercentageError
t_float                              Stat_SInt_MeanPercentageError(s_array_sint const sample, t_sint const* expect);
#define c_sstat_mpe                  Stat_SInt_MeanPercentageError
#define Stat_SInt_MPE                Stat_SInt_MeanPercentageError
t_float                              Stat_Fixed_MeanPercentageError(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_mpe                  Stat_Fixed_MeanPercentageError
#define Stat_Fixed_MPE               Stat_Fixed_MeanPercentageError
t_float                              Stat_Float_MeanPercentageError(s_array_float const sample, t_float const* expect);
#define c_fstat_mpe                  Stat_Float_MeanPercentageError
#define Stat_Float_MPE               Stat_Float_MeanPercentageError
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_absolute_percentage_error
//!@{
t_float                              Stat_UInt_MeanAbsolutePercentageError(s_array_uint const sample, t_uint const* expect);
#define c_ustat_mape                 Stat_UInt_MeanAbsolutePercentageError
#define Stat_UInt_MAPE               Stat_UInt_MeanAbsolutePercentageError
t_float                              Stat_SInt_MeanAbsolutePercentageError(s_array_sint const sample, t_sint const* expect);
#define c_sstat_mape                 Stat_SInt_MeanAbsolutePercentageError
#define Stat_SInt_MAPE               Stat_SInt_MeanAbsolutePercentageError
t_float                              Stat_Fixed_MeanAbsolutePercentageError(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_mape                 Stat_Fixed_MeanAbsolutePercentageError
#define Stat_Fixed_MAPE              Stat_Fixed_MeanAbsolutePercentageError
t_float                              Stat_Float_MeanAbsolutePercentageError(s_array_float const sample, t_float const* expect);
#define c_fstat_mape                 Stat_Float_MeanAbsolutePercentageError
#define Stat_Float_MAPE              Stat_Float_MeanAbsolutePercentageError
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Mean_squared_prediction_error
//!@{
t_float                              Stat_UInt_MeanSquaredPredictionError(s_array_uint const sample, t_uint const* expect);
#define c_ustat_mspe                 Stat_UInt_MeanSquaredPredictionError
#define Stat_UInt_MSPE               Stat_UInt_MeanSquaredPredictionError
t_float                              Stat_SInt_MeanSquaredPredictionError(s_array_sint const sample, t_sint const* expect);
#define c_sstat_mspe                 Stat_SInt_MeanSquaredPredictionError
#define Stat_SInt_MSPE               Stat_SInt_MeanSquaredPredictionError
t_float                              Stat_Fixed_MeanSquaredPredictionError(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_mspe                 Stat_Fixed_MeanSquaredPredictionError
#define Stat_Fixed_MSPE              Stat_Fixed_MeanSquaredPredictionError
t_float                              Stat_Float_MeanSquaredPredictionError(s_array_float const sample, t_float const* expect);
#define c_fstat_mspe                 Stat_Float_MeanSquaredPredictionError
#define Stat_Float_MSPE              Stat_Float_MeanSquaredPredictionError
//!@}

//!@doc TODO document this : https://en.wikipedia.org/wiki/Residual_sum_of_squares
//!@{
t_float                              Stat_UInt_ResidualSumOfSquares(s_array_uint const sample, t_uint const* expect);
#define c_ustat_rss                  Stat_UInt_ResidualSumOfSquares
#define Stat_UInt_RSS                Stat_UInt_ResidualSumOfSquares
t_float                              Stat_SInt_ResidualSumOfSquares(s_array_sint const sample, t_sint const* expect);
#define c_sstat_rss                  Stat_SInt_ResidualSumOfSquares
#define Stat_SInt_RSS                Stat_SInt_ResidualSumOfSquares
t_float                              Stat_Fixed_ResidualSumOfSquares(s_array_fixed const sample, t_fixed const* expect);
#define c_qstat_rss                  Stat_Fixed_ResidualSumOfSquares
#define Stat_Fixed_RSS               Stat_Fixed_ResidualSumOfSquares
t_float                              Stat_Float_ResidualSumOfSquares(s_array_float const sample, t_float const* expect);
#define c_fstat_rss                  Stat_Float_ResidualSumOfSquares
#define Stat_Float_RSS               Stat_Float_ResidualSumOfSquares
//!@}

/*
t_float	stat_moving_average_simple_      ##NAME(s_array_##TYPE const CHAR##lst); \
t_float	stat_moving_average_cumulative_  ##NAME(s_array_##TYPE const CHAR##lst); \
t_float	stat_moving_average_weighted_    ##NAME(s_array_##TYPE const CHAR##lst); \
*/



/*! @endgroup */
HEADER_END
#endif
