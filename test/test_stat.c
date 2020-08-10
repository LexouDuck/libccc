
#include <math.h>

#include "libft_io.h"
#include "libft_stat.h"
#include "libft_random.h"

#include "test.h"



int		test_stat(void) // TODO increment total tests counter for these tests
{
	print_suite_title("stat");

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
		printf("\tMedian:   %12f | intmax   :"PRINTF_U64"\n", ft_stat_median_i(ilst_sorted), intmax);
		printf("\tAverage:  %12f | intmax/2 :"PRINTF_U64"\n", ft_stat_average_i(ilst_sorted), intmax / 2);
		tmp = ft_stat_variance_i(ilst_sorted);
		printf("\tVariance: %12f | StdDev: %12f\n", tmp, sqrt(tmp));

		printf("\tDeciles int:\n"
			"\t\t 0: "PRINTF_W12_INT"\n"
			"\t\t 1: "PRINTF_W12_INT"\n"
			"\t\t 2: "PRINTF_W12_INT"\n"
			"\t\t 3: "PRINTF_W12_INT"\n"
			"\t\t 4: "PRINTF_W12_INT"\n"
			"\t\t 5: "PRINTF_W12_INT"\n"
			"\t\t 6: "PRINTF_W12_INT"\n"
			"\t\t 7: "PRINTF_W12_INT"\n"
			"\t\t 8: "PRINTF_W12_INT"\n"
			"\t\t 9: "PRINTF_W12_INT"\n"
			"\t\t10: "PRINTF_W12_INT"\n\n",
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

	pmf = ft_stat_ilst_to_pmf(ilst_sorted);

	if (g_test.flags.show_args) // TODO special program option for this ?
	{
		printf("Probability mass function for the RNG\n");
		for (int i = 0; i < pmf.length; ++i)
		{
			printf("\t%5d: val %12f; prob %.4f\n", i, pmf.value[i], pmf.prob[i]);
		}
	}
	tmp = 0.;
	for (int i = 0; i < pmf.length; ++i)
	{
		tmp += pmf.prob[i];
	}
	if (g_test.flags.verbose)
	{
		printf("Sum of probs: %.12f\n", tmp);
	}
	ft_stat_free_ilst(&ilst_sorted);
	return (OK);
}
