
#include "libccc.h"
#include "libccc/random/random.h"
#include "libccc/math/stat.h"
#define NOTYPEDEF // avoid typedef redefinitions
#define T_TYPE	t_sint
#define T_NAME	int
#define T_NULL	0
#include "libccc/monad/array.c"

#include "test.h"
#include "test_utils.h"



s_sorted_int	print_test_random(int samples)
{
	s_sorted_int	result;
	t_rand*	rng;

	rng = Random_New();

	if (g_test.config.verbose)
	{
		printf("Statistic repartition test of RNG (sample size: %d)\n", samples);
	}
	result = Stat_Int_New(samples);
	for (t_uint i = 0; i < result.length; ++i)
	{
		result.items[i] = Random_SInt_Range(rng, -500, 501);
	}
/*
	static t_sint arr[5] = {-339, 214, 394, -162, -50};//{-339, -162, -50, 214, 394};
	for (int i = 0; i < result.length; ++i)
		result.items[i] = arr[i];
	for (int i = 0; i < result.length; ++i)
		printf("%d, ", result.items[i]);
	printf("\n");
*/
	if (g_test.config.verbose)
		printf("Quicksorting...");
	quicksort_sint(result.items, 0, result.length);
	if (g_test.config.verbose)
		printf("Done !\n");
/*
	for (int i = 0; i < result.length - 1; ++i)
	{
		if (result.items[i] > result.items[i + 1])
			printf(ANSI_COLOR_FG_RED"Sorting error at index %d\n"ANSI_RESET, i);
	}
	c_stat_free_ilst(&result);
*/
	Random_Delete(&rng);
	return (result);
}



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math_random(void)
{
	static const int	samples = 20000;
	s_sorted_int	values_sorted;

	print_suite_title("libccc/math/random");

	values_sorted = print_test_random(samples);
	Stat_Int_Delete(&values_sorted);

	return (OK);
}
