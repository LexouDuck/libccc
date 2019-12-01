
#include <math.h>
#include <time.h>

#include "../libft_math.h"
#include "../libft_stat.h"

#include "test.h"



#define _MATH_TEST_VERBOSE_FUNCTIONS_ 0
#define _MATH_TEST_VERBOSE_RNG_LIST_ 0

int		test_compare_real_functions
(
	char const *	func_name,
	t_real_func		witness_func,
	t_real_func		ft_func,
	t_float			precision,
	t_interval		interval
)
{
	//Test variables
	t_u32			test_nb = 1000;
	t_u32			failed_tests = 0;
	t_float			expected_res;
	t_float			test_res;

	//sampling variables
	t_float			start = interval.start;
	t_float			end = interval.end;
	t_float			step;
	t_float			tmp;
	t_list_float	error_list;

	//execution time variables
	t_u32			failed_speed_tests = 0;
	time_t			start_time;
	time_t			end_time;
	t_f64			stdC_time;
	t_f64			ft_time;
	t_list_float	time_diff_list;


	step = (end - start) / test_nb;
	tmp = start;
	failed_tests = 0;
	error_list = ft_stat_new_flst(test_nb);
	time_diff_list = ft_stat_new_flst(test_nb);

	for (int i = 0; i < test_nb; ++i)
	{
		tmp += step;

		time(&start_time);
		printf("%lf\n", start_time);
		expected_res = witness_func(tmp);
		time(&end_time);
		stdC_time = (t_f64)(end_time - start_time);

		time(&start_time);
		test_res = ft_func(tmp);
		time(&end_time);
		ft_time = (t_f64)(end_time - start_time);

		time_diff_list.data[i] = stdC_time - ft_time; //(stdC - ft < 0 <=> stdC < ft <=> stdC wins in speed)
		if (time_diff_list.data[i] < 0)
			++failed_speed_tests;

#		if _MATH_TEST_VERBOSE_FUNCTIONS_
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



	printf("\tQuicksorting error list...\n");			ft_stat_quicksort_f(error_list);		printf("\tDone !\n");
	printf("Average error : %g | Median error : %g | Std dev : %g\n\n\n",
			ft_stat_average_f(error_list), ft_stat_median_f(error_list), sqrt(ft_stat_variance_f(error_list)));



	printf("\tQuicksorting speed test list...\n");		ft_stat_quicksort_f(time_diff_list);	printf("\tDone !\n");
	printf("Success rate for speed tests function \"%s\": %g%%\n",
									func_name, (test_nb - failed_speed_tests) * 100. / test_nb);
	printf("Average time diff : %g | Median time diff : %g | Std dev : %g | (NB: negative scores means we lose against std C)\n\n\n",
			ft_stat_average_f(time_diff_list), ft_stat_median_f(time_diff_list), sqrt(ft_stat_variance_f(time_diff_list)));


	ft_stat_free_flst(&error_list);
	ft_stat_free_flst(&time_diff_list);
}



int		test_math(void)
{

	printf("\n");

	printf("       .--------------------------.       \n");
	printf("---==={   LIBFT TEST: libft_math   }===---\n");
	printf("       '--------------------------'       \n");

	printf("\n");

/*
** =============================================
**        Classical real functions tests
** =============================================
*/

#	ifdef _FLOAT_32_

	printf(C_BLUE"\n\nTrigonometry:\n\n"C_RESET);
	test_compare_real_functions("cosf", &cosf, &ft_cos, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cosf", &cosf, &ft_cos, 0.0001, (t_interval){-1000000, 1000000});

	test_compare_real_functions("sinf", &sinf, &ft_sin, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sinf", &sinf, &ft_sin, 0.0001, (t_interval){-1000000, 1000000});


	printf(C_BLUE"\n\n\nSquare root:\n\n"C_RESET);
//	test_compare_real_functions("sqrtf", &sqrtf, &ft_sqrt32, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sqrtf", &sqrtf, &ft_sqrt32, 0.0001, (t_interval){-1000000, 0});
	test_compare_real_functions("sqrtf", &sqrtf, &ft_sqrt32, 0.0001, (t_interval){0, 1000000});
	test_compare_real_functions("sqrtf", &sqrtf, &ft_sqrt32, 0.0001, (t_interval){0, 4});


	printf(C_BLUE"\n\n\nExp & log:\n\n"C_RESET);
	test_compare_real_functions("lnf", &logf, &ft_ln, 0.0001, (t_interval){0., 1.});
	test_compare_real_functions("lnf", &logf, &ft_ln, 0.0001, (t_interval){1., 10000000.});

	printf("\n\n\n");

#	endif



#	ifdef _FLOAT_64_

	test_compare_real_functions("cos", &cos, &ft_cos, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cos", &cos, &ft_cos, 0.0001, (t_interval){-1000000, 1000000});
	test_compare_real_functions("sin", &sin, &ft_sin, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sin", &sin, &ft_sin, 0.0001, (t_interval){-1000000, 1000000});



	test_compare_real_functions("ln", &log, &ft_ln, 0.000001, (t_interval){0., 1.});
	test_compare_real_functions("ln", &log, &ft_ln, 0.000001, (t_interval){1., 10000000.});

#	endif

	return (OK);
}
