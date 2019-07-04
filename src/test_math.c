#include <math.h>
#include "../libft_math.h"
#include "test.h"

# define _MATH_TEST_VERBOSE_ 0

int		test_compare_real_functions
(
	char const *	func_name,
	t_real_func		witness_func,
	t_real_func		ft_func,
	t_float			precision,
	t_interval		interval
)
{	
	t_u32			test_nb = 1000;
	t_u32			test_fail = 0;
	t_float			start = interval.start;
	t_float			end = interval.end;
	t_float			step;
	t_float			tmp;
	t_float_list	error_list;

	t_float		expected_res;
	t_float		test_res;
	t_float		failed_tests;

	step = (end - start) / test_nb;
	tmp = start;
	failed_tests = 0;
	error_list = ft_stat_new_flst(test_nb);

	for (int i = 0; i < test_nb; ++i)
	{
		tmp += step;

		expected_res = witness_func(tmp);
		test_res = ft_func(tmp);
#		if _MATH_TEST_VERBOSE_
		printf("   %s(%g) -> %g\n", func_name, tmp, expected_res);
		printf("ft_%s(%g) -> %g\n", func_name, tmp, test_res);
#		endif

		error_list.data[i] = ft_distance_float(expected_res, test_res);
		if (error_list.data[i] > precision)
			++failed_tests;
	}
	printf("Success rate for function \"%s\" at %g precision: %g%%\n",
									func_name, precision, (test_nb - failed_tests) * 100. / test_nb);
	printf("Tests run: %d | Step: %g | Interval: [%g,%g]\n", test_nb, step, start, end);
#if 0
	printf("\tQuicksorting...\n");
	error_list = ft_stat_quicksort_f(error_list);
	printf("\tDone !\n");
#endif
	printf("Average error : %g | Median error : %g | Std dev : %g\n\n\n",
			ft_stat_average_f(error_list), ft_stat_median_f(error_list), sqrt(ft_stat_variance_f(error_list)));

	ft_stat_free_flst(&error_list);
}

int		test_math(void)
{

printf("\n");

	printf("       .--------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_math   }===---\n");
	printf("       '--------------------------'       \n");

printf("\n");

	ft_random_renew_seed();

#if 0
#ifdef _FLOAT_32_

//	test_compare_real_functions("cosf", &cosf, &ft_cos, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cosf", &cosf, &ft_cos, 0.0001, (t_interval){-1000000, 1000000});
//	test_compare_real_functions("sinf", &sinf, &ft_sin, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sinf", &sinf, &ft_sin, 0.0001, (t_interval){-1000000, 1000000});

//	test_compare_real_functions("lnf", &logf, &ft_ln, 0.0001, (t_interval){0., 1.});
//	test_compare_real_functions("lnf", &logf, &ft_ln, 0.0001, (t_interval){1., 10000000.});

#endif



#ifdef _FLOAT_64_

	test_compare_real_functions("cos", &cos, &ft_cos, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cos", &cos, &ft_cos, 0.0001, (t_interval){-1000000, 1000000});
	test_compare_real_functions("sin", &sin, &ft_sin, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sin", &sin, &ft_sin, 0.0001, (t_interval){-1000000, 1000000});

	test_compare_real_functions("ln", &log, &ft_ln, 0.000001, (t_interval){0., 1.});
	test_compare_real_functions("ln", &log, &ft_ln, 0.000001, (t_interval){1., 10000000.});

#endif
#endif


	t_u32				sample_nb = 20000;
	printf("Stat test of rng, sample size: %d\n", sample_nb);

	t_int_list			i_lst;
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
	i_lst = ft_stat_quicksort_i(i_lst);
	printf("Done !\n");
	for (int i = 0; i < i_lst.len - 1; ++i)
		if (i_lst.data[i] > i_lst.data[i + 1])
			printf(C_RED"Sorting error at index %d\n"C_RESET, i);


/*	for (int i = 0; i < i_lst.len; ++i)
		printf("%d, ", i_lst.data[i]);
	printf("\n");
*/
	printf("\tMedian:   %12f | intmax   :%lu\n", ft_stat_median_i(i_lst), intmax);
	printf("\tAverage:  %12f | intmax/2 :%lu\n", ft_stat_average_i(i_lst), intmax / 2);
	tmp = ft_stat_variance_i(i_lst);
	printf("\tVariance: %12f | StdDev: %12f\n", tmp, sqrt(tmp));

	printf("\tDeciles int:\n\t\t0 : %12d\n\t\t1 : %12d\n\t\t2 : %12d\n\t\t3 : %12d\n\t\t4 : %12d\n\t\t5 : %12d\n\t\t6 : %12d\n\t\t7 : %12d\n\t\t8 : %12d\n\t\t9 : %12d\n\t\t10: %12d\n\n",
		i_lst.data[0],
		i_lst.data[(t_u32)decile_inc],
		i_lst.data[(t_u32)(decile_inc * 2)],
		i_lst.data[(t_u32)(decile_inc * 3)],
		i_lst.data[(t_u32)(decile_inc * 4)],
		i_lst.data[(t_u32)(decile_inc * 5)],
		i_lst.data[(t_u32)(decile_inc * 6)],
		i_lst.data[(t_u32)(decile_inc * 7)],
		i_lst.data[(t_u32)(decile_inc * 8)],
		i_lst.data[(t_u32)(decile_inc * 9)],
		i_lst.data[sample_nb - 1]);


#if _MATH_TEST_VERBOSE_
	printf("\tDeciles uint:\n\t\t0 : %12lu\n\t\t1 : %12lu\n\t\t2 : %12lu\n\t\t3 : %12lu\n\t\t4 : %12lu\n\t\t5 : %12lu\n\t\t6 : %12lu\n\t\t7 : %12lu\n\t\t8 : %12lu\n\t\t9 : %12lu\n\t\t10: %12lu\n\n",
		i_lst.data[0],
		i_lst.data[(t_u32)decile_inc],
		i_lst.data[(t_u32)(decile_inc * 2)],
		i_lst.data[(t_u32)(decile_inc * 3)],
		i_lst.data[(t_u32)(decile_inc * 4)],
		i_lst.data[(t_u32)(decile_inc * 5)],
		i_lst.data[(t_u32)(decile_inc * 6)],
		i_lst.data[(t_u32)(decile_inc * 7)],
		i_lst.data[(t_u32)(decile_inc * 8)],
		i_lst.data[(t_u32)(decile_inc * 9)],
		i_lst.data[sample_nb - 1]);

	printf("\tDeciles hex:\n\t\t0 : %#12lx\n\t\t1 : %#12lx\n\t\t2 : %#12lx\n\t\t3 : %#12lx\n\t\t4 : %#12lx\n\t\t5 : %#12lx\n\t\t6 : %#12lx\n\t\t7 : %#12lx\n\t\t8 : %#12lx\n\t\t9 : %#12lx\n\t\t10: %#12lx\n\n",
		i_lst.data[0],
		i_lst.data[(t_u32)decile_inc],
		i_lst.data[(t_u32)(decile_inc * 2)],
		i_lst.data[(t_u32)(decile_inc * 3)],
		i_lst.data[(t_u32)(decile_inc * 4)],
		i_lst.data[(t_u32)(decile_inc * 5)],
		i_lst.data[(t_u32)(decile_inc * 6)],
		i_lst.data[(t_u32)(decile_inc * 7)],
		i_lst.data[(t_u32)(decile_inc * 8)],
		i_lst.data[(t_u32)(decile_inc * 9)],
		i_lst.data[sample_nb - 1]);
#endif

	t_prob_mass		pmf;

	pmf = ft_stat_ilst_to_pmf(i_lst);

#if _MATH_TEST_VERBOSE_	
	printf("Probability mass function for the RNG\n");
	for (int i = 0; i < pmf.len; ++i)
		printf("\t%5d: val %12f; prob %.4f\n", i, pmf.value[i], pmf.prob[i]);
#endif

	tmp = 0.;
	for (int i = 0; i < pmf.len; ++i)
		tmp += pmf.prob[i];

	printf("Sum of probs: %.12f\n", tmp);


	return (OK);
}
