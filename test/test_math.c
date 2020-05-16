
#include <math.h>
#include <time.h>

#include "libft_math.h"
#include "libft_stat.h"

#include "test.h"



void	print_math_foreword(void)
{
	if (g_test.flags.verbose)
	{
		printf("\n\n"C_BLUE"Floating-point (%d-bit %s precision) math functions"C_RESET"\n\n",
#ifdef _FLOAT_32_
			32, "single");
#endif
#ifdef _FLOAT_64_
			64, "double");
#endif
	}
}

void	print_math_title(char const * title)
{
	if (g_test.flags.verbose)
	{
		printf("\n\n"C_BLUE"%s"C_RESET"\n", title);
	}
}



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



static t_float	ft_get_largest_f(s_list_float list)
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

#define TEST_MATH_PERFORM(CALL, RESULTS, FUNCTION) \
	tmp = start; \
	timer_clock(&timer.start##CALL); \
	for (int i = 0; i < tests; ++i) \
	{ \
		tmp += step; \
		RESULTS[i] = FUNCTION(tmp); \
	} \
	timer_clock(&timer.end##CALL); \



int		test_compare_real_functions(
	char const *	func_name,
	f_real_func		witness_func,
	f_real_func		ft_func,
	t_float			precision,
	s_interval		interval)
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
	s_list_float	error_list;

	//execution time variables
	s_timer		timer = {0};


	step = (end - start) / tests;
	failed_tests = 0;
	error_list = ft_stat_new_flst(tests);

	TEST_MATH_PERFORM(1, results, ft_func)
	TEST_MATH_PERFORM(2, expects, witness_func)

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
			if (g_test.flags.show_args && expects[i] != results[i])
			{
				printf("TEST N°%d: (arg=%g) -> return difference is "C_RED"%g\n"C_RESET, i, tmp, error_list.data[i]);
				if (precision < abs(results[i] - expects[i]))
				{
					printf(C_RED"-> ft_%s(%g)\t-> %g"C_RESET"\n", func_name, tmp, results[i]);
					printf(C_RED"->    %s(%g)\t-> %g"C_RESET"\n", func_name, tmp, expects[i]);
				}
			}
		}
	}
	g_test.totals.tests += tests;
	g_test.totals.failed += failed_tests;
	percent = (tests - failed_tests) * 100. / tests;
	if (g_test.flags.verbose || percent < 90.)
	{
		printf("%s\n", func_name);
		printf("Tests run: %d, on interval: [%g,%g] -> with increment: %g\n", tests, start, end, step);
		printf("Success rate for %g precision: ", precision);
		print_percent(percent);

		ft_stat_quicksort_f(error_list);
		printf_colored("Largest error",			precision, ft_get_largest_f(error_list));
		printf_colored("Average error",			precision, ft_stat_average_f(error_list));
		printf_colored("Median error",			precision, ft_stat_median_f(error_list));
		printf_colored("Standard deviation",	precision, sqrt(ft_stat_variance_f(error_list)));
	}
	if (g_test.flags.show_speed)
	{
		printf("-> Execution time:");
		prins_timer_result(&timer, TRUE);
	}
	if (g_test.flags.verbose)
	{
		printf("\n");
	}
	ft_stat_free_flst(&error_list);
}



int		test_math(void)
{
	print_suite_title("math");

	print_math_foreword();

	print_math_title("Floor");
	test_compare_real_functions("floor", &floorf, &ft_floor, 0.0001, (s_interval){-10, 10});
	test_compare_real_functions("floor", &floorf, &ft_floor, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Ceiling");
	test_compare_real_functions("ceil", &ceilf, &ft_ceil, 0.0001, (s_interval){-10, 10});
	test_compare_real_functions("ceil", &ceilf, &ft_ceil, 0.0001, (s_interval){-1e9, 1e9});



//	print_math_title("Power");
//	test_compare_real_functions("pow", &powf, &ft_pow, 0.0001, (s_interval){0, 4});
//	test_compare_real_functions("pow", &powf, &ft_pow, 0.0001, (s_interval){-100, 1000000});



	print_math_title("Square root");
	test_compare_real_functions("sqrt", &sqrtf, &ft_sqrt, 0.0001, (s_interval){0., 5.});
	test_compare_real_functions("sqrt", &sqrtf, &ft_sqrt, 0.0001, (s_interval){-100., 1e9});

	print_math_title("Cubic root");
	test_compare_real_functions("cbrt", &cbrtf, &ft_cbrt, 0.0001, (s_interval){0., 5.});
	test_compare_real_functions("cbrt", &cbrtf, &ft_cbrt, 0.0001, (s_interval){-1e9, 1e9});

//	print_math_title("N-power root");
//	test_compare_real_functions("nrt", &nrtf, &ft_nrt, 0.0001, (s_interval){0, 5});
//	test_compare_real_functions("nrt", &nrtf, &ft_nrt, 0.0001, (s_interval){-1e9, 1e9});



	print_math_title("Exponential");
	test_compare_real_functions("exp", &expf, &ft_exp, 0.0001, (s_interval){-1000., 1.});
	test_compare_real_functions("exp", &expf, &ft_exp, 0.0001, (s_interval){1., 1e9});

	print_math_title("Logarithm");
	test_compare_real_functions("ln", &logf, &ft_ln, 0.0001, (s_interval){0., 1.});
	test_compare_real_functions("ln", &logf, &ft_ln, 0.0001, (s_interval){1., 1e9});



	print_math_title("Cosine");
	test_compare_real_functions("cos", &cosf, &ft_cos, 0.0001, (s_interval){-TAU, 2 * TAU});
	test_compare_real_functions("cos", &cosf, &ft_cos, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Sine");
	test_compare_real_functions("sin", &sinf, &ft_sin, 0.0001, (s_interval){-TAU, 2 * TAU});
	test_compare_real_functions("sin", &sinf, &ft_sin, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Tangent");
	test_compare_real_functions("tan", &tanf, &ft_tan, 0.0001, (s_interval){-HALF_PI, HALF_PI});
	test_compare_real_functions("tan", &tanf, &ft_tan, 0.0001, (s_interval){-1e9, 1e9});


	print_math_title("Arc-Cosine");
	test_compare_real_functions("acos", &acosf, &ft_acos, 0.0001, (s_interval){-1, 1});
	test_compare_real_functions("acos", &acosf, &ft_acos, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Sine");
	test_compare_real_functions("asin", &asinf, &ft_asin, 0.0001, (s_interval){-1, 1});
	test_compare_real_functions("asin", &asinf, &ft_asin, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Tangent");
	test_compare_real_functions("atan", &atanf, &ft_atan, 0.0001, (s_interval){-TAU, TAU});
	test_compare_real_functions("atan", &atanf, &ft_atan, 0.0001, (s_interval){-1e9, 1e9});


	print_math_title("Hyperbolic Cosine");
	test_compare_real_functions("cosh", &coshf, &ft_cosh, 0.0001, (s_interval){-TAU, TAU});
	test_compare_real_functions("cosh", &coshf, &ft_cosh, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Sine");
	test_compare_real_functions("sinh", &sinhf, &ft_sinh, 0.0001, (s_interval){-TAU, TAU});
	test_compare_real_functions("sinh", &sinhf, &ft_sinh, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Tangent");
	test_compare_real_functions("tanh", &tanhf, &ft_tanh, 0.0001, (s_interval){-TAU, TAU});
	test_compare_real_functions("tanh", &tanhf, &ft_tanh, 0.0001, (s_interval){-1e9, 1e9});


	print_math_title("Hyperbolic Arc-Cosine");
	test_compare_real_functions("acosh", &acoshf, &ft_acosh, 0.0001, (s_interval){1., 50.});
	test_compare_real_functions("acosh", &acoshf, &ft_acosh, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Sine");
	test_compare_real_functions("asinh", &asinhf, &ft_asinh, 0.0001, (s_interval){-50., 50.});
	test_compare_real_functions("asinh", &asinhf, &ft_asinh, 0.0001, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Tangent");
	test_compare_real_functions("atanh", &atanhf, &ft_atanh, 0.0001, (s_interval){-1., 1.});
	test_compare_real_functions("atanh", &atanhf, &ft_atanh, 0.0001, (s_interval){-1e9, 1e9});

	return (OK);
}
