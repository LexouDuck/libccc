
#include <math.h>

#include "libccc.h"
#include "libccc/math/int.h"
#include "libccc/math/fixed.h"
#include "libccc/math/float.h"
#include "libccc/math/stat.h"
#include "libccc/random/random.h"

#define NOTYPEDEF // avoid typedef redefinitions

#define T_TYPE	t_uint
#define T_NAME	uint
#define T_NULL	0
#define T_EQUALS(X,Y)	UInt_Equals((X),(Y))
#include "libccc/monad/array.c"
#define T_TYPE	t_sint
#define T_NAME	sint
#define T_NULL	0
#define T_EQUALS(X,Y)	SInt_Equals((X),(Y))
#include "libccc/monad/array.c"
#define T_TYPE	t_fixed
#define T_NAME	fixed
#define T_NULL	(t_fixed){ 0 }
#define T_EQUALS(X,Y)	Fixed_Equals((X),(Y))
#include "libccc/monad/array.c"
#define T_TYPE	t_float
#define T_NAME	float
#define T_NULL	0
#define T_EQUALS(X,Y)	Float_Equals((X),(Y))
#include "libccc/monad/array.c"

#include "test.h"
#include "test_utils.h"



#define DEFINETEST_STAT(TYPE, TYPE_MIXED, TYPE_UPPER) \
t_bool	print_test_stat_##TYPE(t_uint sample_size, t_##TYPE range_min, t_##TYPE range_max) \
{ \
	s_sorted_##TYPE	values_sorted = print_test_random_##TYPE(sample_size, range_min, range_max); \
	s_sorted_##TYPE	expected_values = Stat_##TYPE_MIXED##_New(sample_size); \
	t_##TYPE step = TYPE_MIXED##_Div(TYPE_MIXED##_Abs(TYPE_MIXED##_Sub(range_max, range_min)), TYPE_MIXED##_FromUInt(sample_size)); \
	for (t_uint i = 0; i < sample_size; ++i) \
	{ \
		expected_values.items[i] = TYPE_MIXED##_Add(range_min, TYPE_MIXED##_Mul(step, TYPE_MIXED##_FromUInt(i))); \
	} \
/* \
	for (int i = 0; i < i_lst.length; ++i) \
		printf("%d, ", i_lst.items[i]); \
	printf("\n"); \
*/ \
	t_float* quartiles   = Stat_##TYPE_MIXED##_Quantiles(values_sorted,    4); \
	t_float* quintiles   = Stat_##TYPE_MIXED##_Quantiles(values_sorted,    5); \
	t_float* deciles     = Stat_##TYPE_MIXED##_Quantiles(values_sorted,   10); \
	t_float* percentiles = Stat_##TYPE_MIXED##_Quantiles(values_sorted,  100); \
	t_float* permilliles = Stat_##TYPE_MIXED##_Quantiles(values_sorted, 1000); \
 \
	if (g_test.config.verbose) \
	{ \
		printf("\t""Count (0):                       " SF_UINT "\n", Stat_##TYPE_MIXED##_Count(values_sorted, TYPE_MIXED##_FromSInt(0))); \
		printf("\t""Count (0 | nan):                 " SF_UINT "\n", Stat_##TYPE_MIXED##_Count(values_sorted, TYPE_UPPER##_ERROR)); \
		printf("\t""Count (min | -inf):              " SF_UINT "\n", Stat_##TYPE_MIXED##_Count(values_sorted, TYPE_UPPER##_MIN)); \
		printf("\t""Count (max | +inf):              " SF_UINT "\n", Stat_##TYPE_MIXED##_Count(values_sorted, TYPE_UPPER##_MAX)); \
		printf("\t""Quantiles (quartiles):           [%f,%f,%f,%f,%f]\n",                     quartiles[0],   quartiles[  1],   quartiles[  2],   quartiles[  3],   quartiles[  4]); \
		printf("\t""Quantiles (quintiles):           [%f,%f,%f,%f,%f,%f]\n",                  quintiles[0],   quintiles[  1],   quintiles[  2],   quintiles[  3],   quintiles[  4],   quintiles[  5]); \
		printf("\t""Quantiles (deciles):             [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]\n",     deciles[0],     deciles[  1],     deciles[  2],     deciles[  3],     deciles[  4],     deciles[  5],     deciles[  6],     deciles[  7],     deciles[  8],     deciles[  9],     deciles[  10]); \
		printf("\t""Quantiles (percentiles):         [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]\n", percentiles[0], percentiles[ 10], percentiles[ 20], percentiles[ 30], percentiles[ 40], percentiles[ 50], percentiles[ 60], percentiles[ 70], percentiles[ 80], percentiles[ 90], percentiles[ 100]); \
		printf("\t""Quantiles (permilliles):         [%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f]\n", permilliles[0], permilliles[100], permilliles[200], permilliles[300], permilliles[400], permilliles[500], permilliles[600], permilliles[700], permilliles[800], permilliles[900], permilliles[1000]); \
		printf("\t""GetMin:                          " SF_##TYPE_UPPER "\n", Stat_##TYPE_MIXED##_GetMin                         (values_sorted)); \
		printf("\t""GetMax:                          " SF_##TYPE_UPPER "\n", Stat_##TYPE_MIXED##_GetMax                         (values_sorted)); \
		printf("\t""Median:                          " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Median                         (values_sorted)); \
		printf("\t""Mode:                            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mode                           (values_sorted)); \
		printf("\t""Range:                           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Range                          (values_sorted)); \
		printf("\t""Midrange:                        " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Midrange                       (values_sorted)); \
		printf("\t""Midhinge:                        " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Midhinge                       (values_sorted)); \
		printf("\t""Variance:                        " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Variance                       (values_sorted)); \
		printf("\t""StandardDeviation:               " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_StandardDeviation              (values_sorted)); \
		printf("\t""CoefficientOfVariation:          " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_CoefficientOfVariation         (values_sorted)); \
		printf("\t""InterquartileRange:              " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_InterquartileRange             (values_sorted)); \
		printf("\t""Trimean:                         " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Trimean                        (values_sorted)); \
		printf("\t""Mean_Arithmetic:                 " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Arithmetic                (values_sorted)); \
		printf("\t""Mean_Geometric:                  " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Geometric                 (values_sorted)); \
		printf("\t""Mean_Harmonic:                   " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Harmonic                  (values_sorted)); \
		printf("\t""Mean_Contraharmonic:             " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Contraharmonic            (values_sorted)); \
		printf("\t""Mean_Interquartile:              " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Interquartile             (values_sorted)); \
		printf("\t""Mean_Quadratic:                  " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Quadratic                 (values_sorted)); \
		printf("\t""Mean_Cubic:                      " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Cubic                     (values_sorted)); \
		printf("\t""Mean_Power (pow  0.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted,  0.0)); \
		printf("\t""Mean_Power (pow +0.5):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +0.5)); \
		printf("\t""Mean_Power (pow +1.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +1.0)); \
		printf("\t""Mean_Power (pow +1.5):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +1.5)); \
		printf("\t""Mean_Power (pow +2.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +2.0)); \
		printf("\t""Mean_Power (pow +2.5):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +2.5)); \
		printf("\t""Mean_Power (pow +3.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +3.0)); \
		printf("\t""Mean_Power (pow +4.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, +4.0)); \
		printf("\t""Mean_Power (pow -0.5):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, -0.5)); \
		printf("\t""Mean_Power (pow -1.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, -1.0)); \
		printf("\t""Mean_Power (pow -1.5):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, -1.5)); \
		printf("\t""Mean_Power (pow -2.0):           " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Power                     (values_sorted, -2.0)); \
		printf("\t""Mean_Lehmer (pow  0):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted,  0)); \
		printf("\t""Mean_Lehmer (pow +1):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted, +1)); \
		printf("\t""Mean_Lehmer (pow +2):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted, +2)); \
		printf("\t""Mean_Lehmer (pow +3):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted, +3)); \
		printf("\t""Mean_Lehmer (pow +4):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted, +4)); \
		printf("\t""Mean_Lehmer (pow -1):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted, -1)); \
		printf("\t""Mean_Lehmer (pow -2):            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_Mean_Lehmer                    (values_sorted, -2)); \
		printf("\t""MedianAbsoluteDeviation:         " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MedianAbsoluteDeviation        (values_sorted)); \
		printf("\t""AverageAbsoluteDeviation:        " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_AverageAbsoluteDeviation       (values_sorted, TYPE_MIXED##_FromFloat(Stat_##TYPE_MIXED##_Mean_Arithmetic(values_sorted)))); \
/*		printf("\t""ArithmeticGeometricMean:         " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_ArithmeticGeometricMean        (values_sorted y)); */ \
		printf("\t""MeanSignedDeviation:             " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanSignedDeviation            (values_sorted, expected_values.items)); \
		printf("\t""MeanSquaredError:                " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanSquaredError               (values_sorted, expected_values.items)); \
		printf("\t""MeanAbsoluteError:               " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanAbsoluteError              (values_sorted, expected_values.items)); \
		printf("\t""MeanAbsoluteDifference:          " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanAbsoluteDifference         (values_sorted, expected_values.items)); \
		printf("\t""RelativeMeanAbsoluteDifference:  " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_RelativeMeanAbsoluteDifference (values_sorted, expected_values.items)); \
		printf("\t""RootMeanSquareDeviation:         " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_RootMeanSquareDeviation        (values_sorted, expected_values.items)); \
		printf("\t""MeanPercentageError:             " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanPercentageError            (values_sorted, expected_values.items)); \
		printf("\t""MeanAbsolutePercentageError:     " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanAbsolutePercentageError    (values_sorted, expected_values.items)); \
		printf("\t""MeanSquaredPredictionError:      " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_MeanSquaredPredictionError     (values_sorted, expected_values.items)); \
		printf("\t""ResidualSumOfSquares:            " SF_FLOAT        "\n", Stat_##TYPE_MIXED##_ResidualSumOfSquares           (values_sorted, expected_values.items)); \
	} \
	printf("\n"); \
/* \
	t_float	tmp; \
	s_prob_mass	pmf = Stat_##TYPE_MIXED##_ProbabilityMassFunction(values_sorted); \
	if (g_test.config.verbose && g_test.config.show_args) \
	{ \
		printf("Probability mass function for the RNG\n"); \
		for (t_uint i = 0; i < pmf.length; ++i) \
		{ \
			printf("\t%5lu: val %12f; prob %.4f\n", i, pmf.value[i], pmf.prob[i]); \
		} \
	} \
	tmp = 0.; \
	for (t_uint i = 0; i < pmf.length; ++i) \
	{ \
		tmp += pmf.prob[i]; \
	} \
	if (g_test.config.verbose) \
	{ \
		printf("Sum of probs: %.12f\n", tmp); \
	} \
	Stat_##TYPE_MIXED##_Delete(&values_sorted); \
*/ \
	return (OK); \
} \

DEFINETEST_STAT(uint,  UInt,  UINT )
DEFINETEST_STAT(sint,  SInt,  SINT )
DEFINETEST_STAT(fixed, Fixed, FIXED)
DEFINETEST_STAT(float, Float, FLOAT)



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math_stat(void) // TODO increment total tests counter for these tests
{
	static const int	sample_size = 1000;

	print_suite_title("libccc/math/stat");

	print_test_stat_uint	(sample_size,  UInt_FromSInt(   0),  UInt_FromSInt(1000));
	print_test_stat_sint	(sample_size,  SInt_FromSInt(-500),  SInt_FromSInt(+500));
	print_test_stat_fixed	(sample_size, Fixed_FromSInt(-500), Fixed_FromSInt(+500));
	print_test_stat_float	(sample_size, Float_FromSInt(-500), Float_FromSInt(+500));
	return (OK);
}
