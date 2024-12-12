
#include <math.h>

#include "libccc/text/format.h"
#include "libccc/sys/io.h"
#include "libccc/random/random.h"
#include "libccc/math/stat.h"
#define NOTYPEDEF // avoid typedef redefinitions
#define T_TYPE	t_sint
#define T_NAME	int
#define T_NULL	0
#include "libccc/monad/array.c"

#include "test.h"



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math_stat(void) // TODO increment total tests counter for these tests
{
	print_suite_title("libccc/math/stat");

	static const int	samples = 20000;
	s_sorted_int	values_sorted = print_test_random(samples);
/*
	for (int i = 0; i < i_lst.length; ++i)
		printf("%d, ", i_lst.items[i]);
	printf("\n");
*/
	t_float	tmp;
	t_float	decile_inc = samples / 10.;

	if (g_test.config.verbose)
	{
		t_u64	intmax = (t_u32)-1;
		printf("\tMedian:   %i"" | intmax   :" SF_U64 "\n", Stat_Int_Median(values_sorted), intmax);
		printf("\tAverage:  %12f | intmax/2 :" SF_U64 "\n", Stat_Int_Average(values_sorted), intmax / 2);
		tmp = Stat_Int_Variance(values_sorted);
		printf("\tVariance: %12f | StdDev: %12f\n", tmp, sqrt(tmp));

		printf("\tDeciles int:\n"
			"\t\t 0: " SF_SINT "\n"
			"\t\t 1: " SF_SINT "\n"
			"\t\t 2: " SF_SINT "\n"
			"\t\t 3: " SF_SINT "\n"
			"\t\t 4: " SF_SINT "\n"
			"\t\t 5: " SF_SINT "\n"
			"\t\t 6: " SF_SINT "\n"
			"\t\t 7: " SF_SINT "\n"
			"\t\t 8: " SF_SINT "\n"
			"\t\t 9: " SF_SINT "\n"
			"\t\t10: " SF_SINT "\n\n",
			values_sorted.items[0],
			values_sorted.items[(t_u32)(decile_inc)],
			values_sorted.items[(t_u32)(decile_inc * 2)],
			values_sorted.items[(t_u32)(decile_inc * 3)],
			values_sorted.items[(t_u32)(decile_inc * 4)],
			values_sorted.items[(t_u32)(decile_inc * 5)],
			values_sorted.items[(t_u32)(decile_inc * 6)],
			values_sorted.items[(t_u32)(decile_inc * 7)],
			values_sorted.items[(t_u32)(decile_inc * 8)],
			values_sorted.items[(t_u32)(decile_inc * 9)],
			values_sorted.items[samples - 1]);
	}
//	if (g_test.config.show_args) // TODO special program option for this ?
//	{
//		printf("\tDeciles uint:\n"
//			"\t\t 0: %12lu\n"
//			"\t\t 1: %12lu\n"
//			"\t\t 2: %12lu\n"
//			"\t\t 3: %12lu\n"
//			"\t\t 4: %12lu\n"
//			"\t\t 5: %12lu\n"
//			"\t\t 6: %12lu\n"
//			"\t\t 7: %12lu\n"
//			"\t\t 8: %12lu\n"
//			"\t\t 9: %12lu\n"
//			"\t\t10: %12lu\n\n",
//			values_sorted.items[0],
//			values_sorted.items[(t_u32)decile_inc],
//			values_sorted.items[(t_u32)(decile_inc * 2)],
//			values_sorted.items[(t_u32)(decile_inc * 3)],
//			values_sorted.items[(t_u32)(decile_inc * 4)],
//			values_sorted.items[(t_u32)(decile_inc * 5)],
//			values_sorted.items[(t_u32)(decile_inc * 6)],
//			values_sorted.items[(t_u32)(decile_inc * 7)],
//			values_sorted.items[(t_u32)(decile_inc * 8)],
//			values_sorted.items[(t_u32)(decile_inc * 9)],
//			values_sorted.items[samples - 1]);
//
//		printf("\tDeciles hex:\n"
//			"\t\t 0: %#12lx\n"
//			"\t\t 1: %#12lx\n"
//			"\t\t 2: %#12lx\n"
//			"\t\t 3: %#12lx\n"
//			"\t\t 4: %#12lx\n"
//			"\t\t 5: %#12lx\n"
//			"\t\t 6: %#12lx\n"
//			"\t\t 7: %#12lx\n"
//			"\t\t 8: %#12lx\n"
//			"\t\t 9: %#12lx\n"
//			"\t\t10: %#12lx\n\n",
//			values_sorted.items[0],
//			values_sorted.items[(t_u32)decile_inc],
//			values_sorted.items[(t_u32)(decile_inc * 2)],
//			values_sorted.items[(t_u32)(decile_inc * 3)],
//			values_sorted.items[(t_u32)(decile_inc * 4)],
//			values_sorted.items[(t_u32)(decile_inc * 5)],
//			values_sorted.items[(t_u32)(decile_inc * 6)],
//			values_sorted.items[(t_u32)(decile_inc * 7)],
//			values_sorted.items[(t_u32)(decile_inc * 8)],
//			values_sorted.items[(t_u32)(decile_inc * 9)],
//			values_sorted.items[samples - 1]);
//	}

	s_prob_mass		pmf;

	pmf = Stat_Int_ToPMF(values_sorted);

	if (g_test.config.verbose && g_test.config.show_args) // TODO special program option for this ?
	{
		printf("Probability mass function for the RNG\n");
		for (t_uint i = 0; i < pmf.length; ++i)
		{
			printf("\t%5d: val %12f; prob %.4f\n", i, pmf.value[i], pmf.prob[i]);
		}
	}
	tmp = 0.;
	for (t_uint i = 0; i < pmf.length; ++i)
	{
		tmp += pmf.prob[i];
	}
	if (g_test.config.verbose)
	{
		printf("Sum of probs: %.12f\n", tmp);
	}
	Stat_Int_Delete(&values_sorted);
	return (OK);
}
