
#include "libccc/math/stat.h"
#include "libccc/math/random.h"

#include "test.h"



s_sortedlist_int	print_test_random(int samples)
{
	s_sortedlist_int	result;
	s_list_int			ilst;

	c_random_renew_seed();

	if (g_test.flags.verbose)
	{
		printf("Statistic repartition test of RNG (sample size: %d)\n", samples);
	}
	ilst = c_stat_new_ilst(samples);

	for (int i = 0; i < ilst.length; ++i)
	{
		ilst.data[i] = c_random_int_a_to_b(-500, 501);
	}

/*	static t_sint arr[5] = {-339, 214, 394, -162, -50};//{-339, -162, -50, 214, 394};
	for (int i = 0; i < ilst.length; ++i)
		ilst.data[i] = arr[i];

	for (int i = 0; i < ilst.length; ++i)
		printf("%d, ", ilst.data[i]);
	printf("\n");
*/
	if (g_test.flags.verbose)
		printf("Quicksorting... ");
	result = c_stat_quicksort_i_new(ilst);
	if (g_test.flags.verbose)
		printf("Done !\n");
/*
	for (int i = 0; i < result.length - 1; ++i)
	{
		if (result.data[i] > result.data[i + 1])
			printf(C_RED"Sorting error at index %d\n"C_RESET, i);
	}
	c_stat_free_ilst(&ilst);
*/
	return (result);
}



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math_random(void)
{
	print_suite_title("math/random");

	static const int	samples = 20000;
	s_sortedlist_int	ilst_sorted = print_test_random(samples);

	c_stat_free_ilst(&ilst_sorted);
	return (OK);
}
