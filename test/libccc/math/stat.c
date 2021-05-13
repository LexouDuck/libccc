
#include <math.h>

#include "libccc/format.h"
#include "libccc/sys/io.h"
#include "libccc/math/stat.h"
#include "libccc/math/random.h"

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
	s_sortedlist_int	ilst_sorted = print_test_random(samples);
/*
	for (int i = 0; i < i_lst.length; ++i)
		printf("%d, ", i_lst.data[i]);
	printf("\n");
*/
	t_float				tmp;
	t_float				decile_inc = samples / 10.;

	if (g_test.flags.verbose)
	{
		t_u64	intmax = (t_u32)-1;
		printf("\tMedian:   %12f | intmax   :"SF_U64"\n", c_stat_median_i(ilst_sorted), intmax);
		printf("\tAverage:  %12f | intmax/2 :"SF_U64"\n", c_stat_average_i(ilst_sorted), intmax / 2);
		tmp = c_stat_variance_i(ilst_sorted);
		printf("\tVariance: %12f | StdDev: %12f\n", tmp, sqrt(tmp));

		printf("\tDeciles int:\n"
			"\t\t 0: %u\n"
			"\t\t 1: %u\n"
			"\t\t 2: %u\n"
			"\t\t 3: %u\n"
			"\t\t 4: %u\n"
			"\t\t 5: %u\n"
			"\t\t 6: %u\n"
			"\t\t 7: %u\n"
			"\t\t 8: %u\n"
			"\t\t 9: %u\n"
			"\t\t10: %u\n\n",
			ilst_sorted.data[0],
			ilst_sorted.data[(t_u32)decile_inc],
			ilst_sorted.data[(t_u32)(decile_inc * 2)],
			ilst_sorted.data[(t_u32)(decile_inc * 3)],
			ilst_sorted.data[(t_u32)(decile_inc * 4)],
			ilst_sorted.data[(t_u32)(decile_inc * 5)],
			ilst_sorted.data[(t_u32)(decile_inc * 6)],
			ilst_sorted.data[(t_u32)(decile_inc * 7)],
			ilst_sorted.data[(t_u32)(decile_inc * 8)],
			ilst_sorted.data[(t_u32)(decile_inc * 9)],
			ilst_sorted.data[samples - 1]);
	}
//	if (g_test.flags.show_args) // TODO special program option for this ?
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
//			ilst_sorted.data[0],
//			ilst_sorted.data[(t_u32)decile_inc],
//			ilst_sorted.data[(t_u32)(decile_inc * 2)],
//			ilst_sorted.data[(t_u32)(decile_inc * 3)],
//			ilst_sorted.data[(t_u32)(decile_inc * 4)],
//			ilst_sorted.data[(t_u32)(decile_inc * 5)],
//			ilst_sorted.data[(t_u32)(decile_inc * 6)],
//			ilst_sorted.data[(t_u32)(decile_inc * 7)],
//			ilst_sorted.data[(t_u32)(decile_inc * 8)],
//			ilst_sorted.data[(t_u32)(decile_inc * 9)],
//			ilst_sorted.data[samples - 1]);
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
//			ilst_sorted.data[0],
//			ilst_sorted.data[(t_u32)decile_inc],
//			ilst_sorted.data[(t_u32)(decile_inc * 2)],
//			ilst_sorted.data[(t_u32)(decile_inc * 3)],
//			ilst_sorted.data[(t_u32)(decile_inc * 4)],
//			ilst_sorted.data[(t_u32)(decile_inc * 5)],
//			ilst_sorted.data[(t_u32)(decile_inc * 6)],
//			ilst_sorted.data[(t_u32)(decile_inc * 7)],
//			ilst_sorted.data[(t_u32)(decile_inc * 8)],
//			ilst_sorted.data[(t_u32)(decile_inc * 9)],
//			ilst_sorted.data[samples - 1]);
//	}

	s_prob_mass		pmf;

	pmf = c_stat_ilst_to_pmf(ilst_sorted);

	if (g_test.flags.verbose && g_test.flags.show_args) // TODO special program option for this ?
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
	if (g_test.flags.verbose)
	{
		printf("Sum of probs: %.12f\n", tmp);
	}
	c_stat_free_ilst(&ilst_sorted);
	return (OK);
}
