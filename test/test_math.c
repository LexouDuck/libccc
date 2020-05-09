
#include <math.h>
#include <time.h>

#include "libft_math.h"
#include "libft_stat.h"

#include "test.h"



#define PRINTF_FORMAT	":\t%s%g"
static inline void printf_colored(const char* label, t_float precision, t_float value)
{
	printf(label);
	if (precision == 0.)
	{
		if (value == 0. || IS_NAN(value))
			printf(PRINTF_FORMAT"\n", "", value);
		else if (value < 0)
			printf(PRINTF_FORMAT"\n"C_RESET, C_RED, value);
		else if (value > 0)
			printf(PRINTF_FORMAT"\n"C_RESET, C_GREEN, value);
	}
	else
	{
		if (value < precision)
			printf(PRINTF_FORMAT"\n"C_RESET, C_GREEN, value);
		else
			printf(PRINTF_FORMAT"\n"C_RESET, C_RED, value);
	}
}



static t_float	ft_get_largest_f(t_list_float list)
{
	t_float result = 0.;
	for (t_int i = 0; i < list.len; ++i)
	{
		if (result < list.data[i])
			result = list.data[i];
		if (IS_NAN(list.data[i]))
			result = NAN;
	}
	return (result);
}



#define _MATH_TEST_VERBOSE_FUNCTIONS_ 0
#define _MATH_TEST_VERBOSE_RNG_LIST_ 0

int		test_compare_real_functions(
	char const *	func_name,
	t_real_func		witness_func,
	t_real_func		ft_func,
	t_float			precision,
	t_interval		interval)
{
	//Test variables
	static const t_u32	tests = 1000;
	t_float			expects[tests];
	t_float			results[tests];
	t_u32			failed_tests = 0;
	t_float			percent;

	//sampling variables
	t_float			start = interval.start;
	t_float			end = interval.end;
	t_float			step;
	t_float			tmp;
	t_list_float	error_list;

	//execution time variables
	t_timer		timer = {0};


	step = (end - start) / tests;
	failed_tests = 0;
	error_list = ft_stat_new_flst(tests);

	tmp = start;
	timer_clock(&timer.start1);
	for (int i = 0; i < tests; ++i)
	{
		tmp += step;
		results[i] = ft_func(tmp);
	}
	timer_clock(&timer.end1);

	tmp = start;
	timer_clock(&timer.start2);
	for (int i = 0; i < tests; ++i)
	{
		tmp += step;
		expects[i] = witness_func(tmp);
	}
	timer_clock(&timer.end2);

	tmp = start;
	for (int i = 0; i < tests; ++i)
	{
		tmp += step;
		if (expects[i] == results[i] || (IS_NAN(expects[i]) && IS_NAN(results[i])))
			error_list.data[i] = 0;
		else if (IS_NAN(expects[i]) || IS_NAN(results[i]))
			error_list.data[i] = NAN;
		else
			error_list.data[i] = ft_distance_float(expects[i], results[i]);

		if (IS_NAN(error_list.data[i]) || error_list.data[i] > precision)
		{
			++failed_tests;
#if _MATH_TEST_VERBOSE_FUNCTIONS_
			if (expects[i] != results[i])
			{
				printf(C_RED"TEST N°%d -> difference: %g\n"C_RESET, i, error_list.data[i]);
				printf("->    %s(%g)\t-> %g\n", func_name, tmp, expects[i]);
				printf("-> ft_%s(%g)\t-> %g\n", func_name, tmp, results[i]);
			}
#endif
		}
	}

	printf("%s\n", func_name);
	printf("Tests run: %d, on interval: [%g,%g] -> with increment: %g\n", tests, start, end, step);

	ft_stat_quicksort_f(error_list);
	percent = (tests - failed_tests) * 100. / tests;
	printf("Success rate for %g precision: %s%g%%"C_RESET"\n", precision,
		percent == 100 ? C_BLUE : (percent >= 90 ? C_GREEN : C_RED), percent);
	printf_colored("Largest error",			precision, ft_get_largest_f(error_list));
	printf_colored("Average error",			precision, ft_stat_average_f(error_list));
	printf_colored("Median error",			precision, ft_stat_median_f(error_list));
	printf_colored("Standard deviation",	precision, sqrt(ft_stat_variance_f(error_list)));
	printf("-> Execution time:");
	print_timer_result(&timer, TRUE);

	printf("\n\n\n");

	ft_stat_free_flst(&error_list);
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

#ifdef _FLOAT_32_

	printf("\n\n\n"C_BLUE"Floating-point (32-bit single precision) math functions"C_RESET"\n\n");

	printf("\n\n\n"C_BLUE"Floor:"C_RESET"\n\n");
	test_compare_real_functions("floor", &floorf, &ft_floor, 0.0001, (t_interval){-10, 10});
	test_compare_real_functions("floor", &floorf, &ft_floor, 0.0001, (t_interval){-1e9, 1e9});

	printf("\n\n\n"C_BLUE"Ceiling:"C_RESET"\n\n");
	test_compare_real_functions("ceil", &ceilf, &ft_ceil, 0.0001, (t_interval){-10, 10});
	test_compare_real_functions("ceil", &ceilf, &ft_ceil, 0.0001, (t_interval){-1e9, 1e9});



//	printf("\n\n\n"C_BLUE"Power:"C_RESET"\n\n");
//	test_compare_real_functions("pow", &powf, &ft_pow, 0.0001, (t_interval){0, 4});
//	test_compare_real_functions("pow", &powf, &ft_pow, 0.0001, (t_interval){-100, 1000000});



	printf("\n\n\n"C_BLUE"Square root:"C_RESET"\n\n");
	test_compare_real_functions("sqrt", &sqrtf, &ft_sqrt, 0.0001, (t_interval){0., 5.});
	test_compare_real_functions("sqrt", &sqrtf, &ft_sqrt, 0.0001, (t_interval){-100., 1e9});

	printf("\n\n\n"C_BLUE"Cubic root:"C_RESET"\n\n");
	test_compare_real_functions("cbrt", &cbrtf, &ft_cbrt, 0.0001, (t_interval){0., 5.});
	test_compare_real_functions("cbrt", &cbrtf, &ft_cbrt, 0.0001, (t_interval){-1e9, 1e9});

//	printf("\n\n\n"C_BLUE"N-power root:"C_RESET"\n\n");
//	test_compare_real_functions("sqrt", &nrtf, &ft_nrt, 0.0001, (t_interval){0, 5});
//	test_compare_real_functions("sqrt", &nrtf, &ft_nrt, 0.0001, (t_interval){-1e9, 1e9});



	printf("\n\n\n"C_BLUE"Exponential:"C_RESET"\n\n");
	test_compare_real_functions("exp", &expf, &ft_exp, 0.0001, (t_interval){-1000., 1.});
	test_compare_real_functions("exp", &expf, &ft_exp, 0.0001, (t_interval){1., 1e9});

	printf("\n\n\n"C_BLUE"Logarithm:"C_RESET"\n\n");
	test_compare_real_functions("ln", &logf, &ft_ln, 0.0001, (t_interval){0., 1.});
	test_compare_real_functions("ln", &logf, &ft_ln, 0.0001, (t_interval){1., 1e9});



	printf("\n\n\n"C_BLUE"Trigonometry:"C_RESET"\n\n");

	test_compare_real_functions("cos", &cosf, &ft_cos, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cos", &cosf, &ft_cos, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("sin", &sinf, &ft_sin, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sin", &sinf, &ft_sin, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("tan", &tanf, &ft_tan, 0.0001, (t_interval){-HALF_PI, HALF_PI});
	test_compare_real_functions("tan", &tanf, &ft_tan, 0.0001, (t_interval){-1e9, 1e9});


	test_compare_real_functions("acos", &acosf, &ft_acos, 0.0001, (t_interval){-1, 1});
	test_compare_real_functions("acos", &acosf, &ft_acos, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("asin", &asinf, &ft_asin, 0.0001, (t_interval){-1, 1});
	test_compare_real_functions("asin", &asinf, &ft_asin, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("atan", &atanf, &ft_atan, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("atan", &atanf, &ft_atan, 0.0001, (t_interval){-1e9, 1e9});



	test_compare_real_functions("cosh", &coshf, &ft_cosh, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("cosh", &coshf, &ft_cosh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("sinh", &sinhf, &ft_sinh, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("sinh", &sinhf, &ft_sinh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("tanh", &tanhf, &ft_tanh, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("tanh", &tanhf, &ft_tanh, 0.0001, (t_interval){-1e9, 1e9});


	test_compare_real_functions("acosh", &acoshf, &ft_acosh, 0.0001, (t_interval){1., 50.});
	test_compare_real_functions("acosh", &acoshf, &ft_acosh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("asinh", &asinhf, &ft_asinh, 0.0001, (t_interval){-50., 50.});
	test_compare_real_functions("asinh", &asinhf, &ft_asinh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("atanh", &atanhf, &ft_atanh, 0.0001, (t_interval){-1., 1.});
	test_compare_real_functions("atanh", &atanhf, &ft_atanh, 0.0001, (t_interval){-1e9, 1e9});

#endif



#ifdef _FLOAT_64_

	printf("\n\n\n"C_BLUE"Floating-point (64-bit single precision) math functions"C_RESET"\n\n");

	printf("\n\n\n"C_BLUE"Floor:"C_RESET"\n\n");
	test_compare_real_functions("floor", &floor, &ft_floor, 0.0001, (t_interval){-10, 10});
	test_compare_real_functions("floor", &floor, &ft_floor, 0.0001, (t_interval){-1e9, 1e9});

	printf("\n\n\n"C_BLUE"Ceiling:"C_RESET"\n\n");
	test_compare_real_functions("ceil", &ceil, &ft_ceil, 0.0001, (t_interval){-10, 10});
	test_compare_real_functions("ceil", &ceil, &ft_ceil, 0.0001, (t_interval){-1e9, 1e9});



//	printf("\n\n\n"C_BLUE"Power:"C_RESET"\n\n");
//	test_compare_real_functions("pow", &pow, &ft_pow, 0.0001, (t_interval){0, 4});
//	test_compare_real_functions("pow", &pow, &ft_pow, 0.0001, (t_interval){-100, 1000000});



	printf("\n\n\n"C_BLUE"Square root:"C_RESET"\n\n");
	test_compare_real_functions("sqrt", &sqrt, &ft_sqrt, 0.0001, (t_interval){0., 5.});
	test_compare_real_functions("sqrt", &sqrt, &ft_sqrt, 0.0001, (t_interval){-100., 1e9});

	printf("\n\n\n"C_BLUE"Cubic root:"C_RESET"\n\n");
	test_compare_real_functions("cbrt", &cbrt, &ft_cbrt, 0.0001, (t_interval){0., 5.});
	test_compare_real_functions("cbrt", &cbrt, &ft_cbrt, 0.0001, (t_interval){-1e9, 1e9});

//	printf("\n\n\n"C_BLUE"N-power root:"C_RESET"\n\n");
//	test_compare_real_functions("sqrt", &nrt, &ft_nrt, 0.0001, (t_interval){0, 5});
//	test_compare_real_functions("sqrt", &nrt, &ft_nrt, 0.0001, (t_interval){-1e9, 1e9});



	printf("\n\n\n"C_BLUE"Exponential:"C_RESET"\n\n");
	test_compare_real_functions("exp", &exp, &ft_exp, 0.0001, (t_interval){-1000., 1.});
	test_compare_real_functions("exp", &exp, &ft_exp, 0.0001, (t_interval){1., 1e9});

	printf("\n\n\n"C_BLUE"Logarithm:"C_RESET"\n\n");
	test_compare_real_functions("ln", &log, &ft_ln, 0.0001, (t_interval){0., 1.});
	test_compare_real_functions("ln", &log, &ft_ln, 0.0001, (t_interval){1., 1e9});



	printf("\n\n\n"C_BLUE"Trigonometry:"C_RESET"\n\n");

	test_compare_real_functions("cos", &cos, &ft_cos, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cos", &cos, &ft_cos, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("sin", &sin, &ft_sin, 0.0001, (t_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sin", &sin, &ft_sin, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("tan", &tan, &ft_tan, 0.0001, (t_interval){-HALF_PI, HALF_PI});
	test_compare_real_functions("tan", &tan, &ft_tan, 0.0001, (t_interval){-1e9, 1e9});


	test_compare_real_functions("acos", &acos, &ft_acos, 0.0001, (t_interval){-1, 1});
	test_compare_real_functions("acos", &acos, &ft_acos, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("asin", &asin, &ft_asin, 0.0001, (t_interval){-1, 1});
	test_compare_real_functions("asin", &asin, &ft_asin, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("atan", &atan, &ft_atan, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("atan", &atan, &ft_atan, 0.0001, (t_interval){-1e9, 1e9});



	test_compare_real_functions("cosh", &cosh, &ft_cosh, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("cosh", &cosh, &ft_cosh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("sinh", &sinh, &ft_sinh, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("sinh", &sinh, &ft_sinh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("tanh", &tanh, &ft_tanh, 0.0001, (t_interval){-TAU, TAU});
	test_compare_real_functions("tanh", &tanh, &ft_tanh, 0.0001, (t_interval){-1e9, 1e9});


	test_compare_real_functions("acosh", &acosh, &ft_acosh, 0.0001, (t_interval){1., 50.});
	test_compare_real_functions("acosh", &acosh, &ft_acosh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("asinh", &asinh, &ft_asinh, 0.0001, (t_interval){-50., 50.});
	test_compare_real_functions("asinh", &asinh, &ft_asinh, 0.0001, (t_interval){-1e9, 1e9});

	test_compare_real_functions("atanh", &atanh, &ft_atanh, 0.0001, (t_interval){-1., 1.});
	test_compare_real_functions("atanh", &atanh, &ft_atanh, 0.0001, (t_interval){-1e9, 1e9});

#endif

printf("\n\n\n");

	return (OK);
}
