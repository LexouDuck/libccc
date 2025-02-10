
#include "libccc.h"
#include "libccc/memory.h"
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



#define DEFINETEST_RANDOM(TYPE, TYPENAME) \
s_sorted_##TYPE	print_test_random_##TYPE(t_uint sample_size, t_##TYPE range_min, t_##TYPE range_max) \
{ \
	s_sorted_##TYPE	result; \
 \
	if (g_test.config.verbose) \
	{ \
		printf("Statistic repartition test of RNG for `t_"#TYPE"` values (sample size: %lu)\n", sample_size); \
	} \
	result = Stat_##TYPENAME##_New(sample_size); \
	Memory_Delete((void**)&result.items); \
	result.items = Random_SampleInRange_##TYPENAME(sample_size, range_min, range_max); \
/* \
	static t_##TYPE arr[5] = {-339, 214, 394, -162, -50};//{-339, -162, -50, 214, 394}; \
	for (int i = 0; i < result.length; ++i) \
		result.items[i] = arr[i]; \
	for (int i = 0; i < result.length; ++i) \
		printf("%d, ", result.items[i]); \
	printf("\n"); \
*/ \
	if (g_test.config.verbose) \
		printf("Quicksorting..."); \
	quicksort_##TYPE(result.items, 0, result.length); \
	if (g_test.config.verbose) \
		printf(" done!\n"); \
/* \
	for (int i = 0; i < result.length - 1; ++i) \
	{ \
		if (result.items[i] > result.items[i + 1]) \
			printf(ANSI_COLOR_FG_RED"Sorting error at index %d\n"ANSI_RESET, i); \
	} \
	c_stat_free_ilst(&result); \
*/ \
	return (result); \
} \

DEFINETEST_RANDOM(uint,  UInt)
DEFINETEST_RANDOM(sint,  SInt)
DEFINETEST_RANDOM(fixed, Fixed)
DEFINETEST_RANDOM(float, Float)



/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int	testsuite_math_random(void)
{
	static const int	sample_size = 10000;

	print_suite_title("libccc/math/random");

	s_sorted_uint	values_sorted_uint	= print_test_random_uint	(sample_size,  UInt_FromSInt(   0),  UInt_FromSInt(1000));	Stat_UInt_Delete(&values_sorted_uint);
	s_sorted_sint	values_sorted_sint	= print_test_random_sint	(sample_size,  SInt_FromSInt(-500),  SInt_FromSInt(+500));	Stat_SInt_Delete(&values_sorted_sint);
	s_sorted_fixed	values_sorted_fixed	= print_test_random_fixed	(sample_size, Fixed_FromSInt(-500), Fixed_FromSInt(+500));	Stat_Fixed_Delete(&values_sorted_fixed);
	s_sorted_float	values_sorted_float	= print_test_random_float	(sample_size, Float_FromSInt(-500), Float_FromSInt(+500));	Stat_Float_Delete(&values_sorted_float);

	return (OK);
}
