
#include "libft_stat.h"
#include "libft_random.h"

#include "test.h"



int		test_stat(void)
{

printf("\n");

	printf("       .--------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_stat   }===---\n");
	printf("       '--------------------------'       \n");

printf("\n");

	ft_random_renew_seed();

	t_u32				sample_nb = 20000;
	printf("Stat test of rng, sample size: %d\n", sample_nb);

	t_list_int			i_lst;
	t_sortedlist_int	si_lst;
	t_u64				intmax = (t_u32)-1;
	t_float				tmp;
	t_float				decile_inc = sample_nb / 10.;


	i_lst = ft_stat_new_ilst(sample_nb);

	for (int i = 0; i < i_lst.len; ++i)
		i_lst.data[i] = ft_random_int_a_to_b(-500, 501);

/*	static t_int arr[5] = {-339, 214, 394, -162, -50};//{-339, -162, -50, 214, 394};
	for (int i = 0; i < i_lst.len; ++i)
		i_lst.data[i] = arr[i];

	for (int i = 0; i < i_lst.len; ++i)
		printf("%d, ", i_lst.data[i]);
	printf("\n");
*/
	printf("Quicksorting...\n");
	si_lst = ft_stat_quicksort_i_new(i_lst);
	printf("Done !\n");

	for (int i = 0; i < si_lst.len - 1; ++i)
		if (si_lst.data[i] > si_lst.data[i + 1])
			printf(C_RED"Sorting error at index %d\n"C_RESET, i);


/*	for (int i = 0; i < i_lst.len; ++i)
		printf("%d, ", i_lst.data[i]);
	printf("\n");
*/
	printf("\tMedian:   %12f | intmax   :%lu\n", ft_stat_median_i(si_lst), intmax);
	printf("\tAverage:  %12f | intmax/2 :%lu\n", ft_stat_average_i(si_lst), intmax / 2);
	tmp = ft_stat_variance_i(si_lst);
	printf("\tVariance: %12f | StdDev: %12f\n", tmp, sqrt(tmp));

	printf("\tDeciles int:\n\t\t0 : %12d\n\t\t1 : %12d\n\t\t2 : %12d\n\t\t3 : %12d\n\t\t4 : %12d\n\t\t5 : %12d\n\t\t6 : %12d\n\t\t7 : %12d\n\t\t8 : %12d\n\t\t9 : %12d\n\t\t10: %12d\n\n",
		si_lst.data[0],
		si_lst.data[(t_u32)decile_inc],
		si_lst.data[(t_u32)(decile_inc * 2)],
		si_lst.data[(t_u32)(decile_inc * 3)],
		si_lst.data[(t_u32)(decile_inc * 4)],
		si_lst.data[(t_u32)(decile_inc * 5)],
		si_lst.data[(t_u32)(decile_inc * 6)],
		si_lst.data[(t_u32)(decile_inc * 7)],
		si_lst.data[(t_u32)(decile_inc * 8)],
		si_lst.data[(t_u32)(decile_inc * 9)],
		si_lst.data[sample_nb - 1]);


#	if _MATH_TEST_VERBOSE_RNG_LIST_
	printf("\tDeciles uint:\n\t\t0 : %12lu\n\t\t1 : %12lu\n\t\t2 : %12lu\n\t\t3 : %12lu\n\t\t4 : %12lu\n\t\t5 : %12lu\n\t\t6 : %12lu\n\t\t7 : %12lu\n\t\t8 : %12lu\n\t\t9 : %12lu\n\t\t10: %12lu\n\n",
		si_lst.data[0],
		si_lst.data[(t_u32)decile_inc],
		si_lst.data[(t_u32)(decile_inc * 2)],
		si_lst.data[(t_u32)(decile_inc * 3)],
		si_lst.data[(t_u32)(decile_inc * 4)],
		si_lst.data[(t_u32)(decile_inc * 5)],
		si_lst.data[(t_u32)(decile_inc * 6)],
		si_lst.data[(t_u32)(decile_inc * 7)],
		si_lst.data[(t_u32)(decile_inc * 8)],
		si_lst.data[(t_u32)(decile_inc * 9)],
		si_lst.data[sample_nb - 1]);

	printf("\tDeciles hex:\n\t\t0 : %#12lx\n\t\t1 : %#12lx\n\t\t2 : %#12lx\n\t\t3 : %#12lx\n\t\t4 : %#12lx\n\t\t5 : %#12lx\n\t\t6 : %#12lx\n\t\t7 : %#12lx\n\t\t8 : %#12lx\n\t\t9 : %#12lx\n\t\t10: %#12lx\n\n",
		si_lst.data[0],
		si_lst.data[(t_u32)decile_inc],
		si_lst.data[(t_u32)(decile_inc * 2)],
		si_lst.data[(t_u32)(decile_inc * 3)],
		si_lst.data[(t_u32)(decile_inc * 4)],
		si_lst.data[(t_u32)(decile_inc * 5)],
		si_lst.data[(t_u32)(decile_inc * 6)],
		si_lst.data[(t_u32)(decile_inc * 7)],
		si_lst.data[(t_u32)(decile_inc * 8)],
		si_lst.data[(t_u32)(decile_inc * 9)],
		si_lst.data[sample_nb - 1]);
#	endif

	t_prob_mass		pmf;

	pmf = ft_stat_ilst_to_pmf(si_lst);

#	if _MATH_TEST_VERBOSE_RNG_LIST_
	printf("Probability mass function for the RNG\n");
	for (int i = 0; i < pmf.len; ++i)
		printf("\t%5d: val %12f; prob %.4f\n", i, pmf.value[i], pmf.prob[i]);
#	endif

	tmp = 0.;
	for (int i = 0; i < pmf.len; ++i)
		tmp += pmf.prob[i];

	printf("Sum of probs: %.12f\n", tmp);


	ft_stat_free_ilst(&i_lst);
	ft_stat_free_ilst(&si_lst);

	return (OK);
}
