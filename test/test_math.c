
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



#define TEST_INIT_MATH() \
	s_timer			timer = {0}; \
	int				failed_tests = 0; \

#define TEST_INIT_MATH_REALFUNCTION() \
	TEST_INIT_MATH() \
	t_float			expects[tests]; \
	t_float			results[tests]; \
	s_list_float	error_list = ft_stat_new_flst(tests); \
	t_float	x; \
	t_float	step = (interval.end - interval.start) / tests; \

#define TEST_INIT_MATH_REALOPERATOR() \
	TEST_INIT_MATH() \
	int tests_interval = tests; \
	tests *= tests; \
	t_float			expects[tests]; \
	t_float			results[tests]; \
	s_list_float	error_list = ft_stat_new_flst(tests); \
	t_float	x; \
	t_float	y; \
	t_float	step_x = (interval_x.end - interval_x.start) / tests_interval; \
	t_float	step_y = (interval_y.end - interval_y.start) / tests_interval; \
	



#define TEST_PERFORM_MATH_REALFUNCTION(CALL, RESULTS, FUNCTION) \
	x = interval.start; \
	timer_clock(&timer.start##CALL); \
	for (int i = 0; i < tests; ++i) \
	{ \
		x += step; \
		RESULTS[i] = FUNCTION(x); \
	} \
	timer_clock(&timer.end##CALL); \

#define TEST_PERFORM_MATH_REALOPERATOR(CALL, RESULTS, FUNCTION) \
	x = interval_x.start; \
	y = interval_y.start; \
	timer_clock(&timer.start##CALL); \
	for (int i = 0; i < tests_interval; ++i) \
	{ \
		for (int j = 0; j < tests_interval; ++j) \
		{ \
			x += step_x; \
			RESULTS[i * tests_interval + j] = FUNCTION(x, y); \
		} \
		y += step_y; \
	} \
	timer_clock(&timer.end##CALL); \



#define TEST_GET_RESULTS() \
	for (int i = 0; i < tests; ++i) \
	{ \
		if (expects[i] == results[i] || (IS_NAN(expects[i]) && IS_NAN(results[i]))) \
			error_list.data[i] = 0; \
		else if (IS_NAN(expects[i]) || IS_NAN(results[i])) \
			error_list.data[i] = NAN; \
		else \
			error_list.data[i] = ft_distance_float(expects[i], results[i]); \
		if (IS_NAN(error_list.data[i]) || error_list.data[i] > precision) \
		{ \
			++failed_tests; \
			if (g_test.flags.verbose && g_test.flags.show_args && precision < abs(results[i] - expects[i])) \
			{ \
				printf("TEST N°%d: -> returned %g but libc returned %g (difference is "C_RED"%g"C_RESET")\n", \
					i, results[i], expects[i], error_list.data[i]); \
			} \
		} \
	} \



#define TEST_PRINT_MATH(FORMAT, ...) \
	g_test.totals.tests += tests; \
	g_test.totals.failed += failed_tests; \
	t_float percent = (tests - failed_tests) * 100. / tests; \
	if (g_test.flags.verbose || percent < 90.) \
	{ \
		printf("\n%s\n", func_name); \
		printf(FORMAT, ##__VA_ARGS__); \
		printf("Success rate for %g precision: ", precision); \
		print_percent(percent); \
	} \

static void	print_test_math(s_timer timer, s_list_float error_list, t_float precision)
{
	if (g_test.flags.verbose)
	{
		ft_stat_quicksort_f(error_list);
		printf_colored("Largest error",			precision, ft_get_largest_f(error_list));
		printf_colored("Average error",			precision, ft_stat_average_f(error_list));
		printf_colored("Median error",			precision, ft_stat_median_f(error_list));
		printf_colored("Standard deviation",	precision, sqrt(ft_stat_variance_f(error_list)));
	}
	if (g_test.flags.show_speed)
	{
		printf("-> Execution time:");
		print_timer_result(&timer, TRUE);
	}
	if (g_test.flags.verbose)
	{
		printf("\n");
	}
	ft_stat_free_flst(&error_list);
}



int		test_math_realfunction_libc(
	char const *	func_name,
	f_real_function	func_libc,
	f_real_function	func_libft,
	t_float			precision,
	int				tests,
	s_interval		interval)
{
	TEST_INIT_MATH_REALFUNCTION()
	TEST_PERFORM_MATH_REALFUNCTION(1, results, func_libft)
	if (func_libc)
	{
		TEST_PERFORM_MATH_REALFUNCTION(2, expects, func_libc)
	}
	TEST_GET_RESULTS()
	TEST_PRINT_MATH("Ran %d tests on interval [%g,%g], with increment=%g\n", tests, interval.start, interval.end, step)
	print_test_math(timer, error_list, precision);
}

int		test_math_realoperator_libc(
	char const *	func_name,
	f_real_operator	func_libc,
	f_real_operator	func_libft,
	t_float			precision,
	int				tests,
	s_interval		interval_x,
	s_interval		interval_y)
{
	TEST_INIT_MATH_REALOPERATOR()
	TEST_PERFORM_MATH_REALOPERATOR(1, results, func_libft)
	if (func_libc)
	{
		TEST_PERFORM_MATH_REALOPERATOR(2, expects, func_libc)
	}
	TEST_GET_RESULTS()
	TEST_PRINT_MATH("Ran %d tests with:\n"
		"arg1: interval [%g,%g], with increment=%g\n"
		"arg2: interval [%g,%g], with increment=%g\n",
		tests,
		interval_x.start, interval_x.end, step_x,
		interval_y.start, interval_y.end, step_y)
	print_test_math(timer, error_list, precision);
}



int		test_math(void)
{
	print_suite_title("math");

	print_math_foreword();

	print_math_title("Floor");
	test_math_realfunction_libc("floor", &floorf, &ft_floor, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("floor", &floorf, &ft_floor, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Ceiling");
	test_math_realfunction_libc("ceil", &ceilf, &ft_ceil, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("ceil", &ceilf, &ft_ceil, 0.0001, 1000, (s_interval){-1e9, 1e9});



	print_math_title("Power");
	test_math_realoperator_libc("pow", &powf, &ft_pow, 0.0001, 100, (s_interval){0, 4}, (s_interval){-10, 10});
	test_math_realoperator_libc("pow", &powf, &ft_pow, 0.0001, 100, (s_interval){-100, 1000000}, (s_interval){-10, 10});



	print_math_title("Square root");
	test_math_realfunction_libc("sqrt", &sqrtf, &ft_sqrt, 0.0001, 1000, (s_interval){0., 5.});
	test_math_realfunction_libc("sqrt", &sqrtf, &ft_sqrt, 0.0001, 1000, (s_interval){-100., 1e9});

	print_math_title("Cubic root");
	test_math_realfunction_libc("cbrt", &cbrtf, &ft_cbrt, 0.0001, 1000, (s_interval){0., 5.});
	test_math_realfunction_libc("cbrt", &cbrtf, &ft_cbrt, 0.0001, 1000, (s_interval){-1e9, 1e9});

//	print_math_title("N-power root");
//	test_math_realoperator_libc("nrt", NULL, &ft_nrt, 0.0001, 100, (s_interval){0, 5}, (s_interval){-10, 10});
//	test_math_realoperator_libc("nrt", NULL, &ft_nrt, 0.0001, 100, (s_interval){-1e9, 1e9}, (s_interval){-10, 10});



	print_math_title("Exponential");
	test_math_realfunction_libc("exp", &expf, &ft_exp, 0.0001, 1000, (s_interval){-1000., 1.});
	test_math_realfunction_libc("exp", &expf, &ft_exp, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Logarithm");
	test_math_realfunction_libc("ln", &logf, &ft_ln, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("ln", &logf, &ft_ln, 0.0001, 1000, (s_interval){1., 1e9});



	print_math_title("Cosine");
	test_math_realfunction_libc("cos", &cosf, &ft_cos, 0.0001, 1000, (s_interval){-TAU, 2 * TAU});
	test_math_realfunction_libc("cos", &cosf, &ft_cos, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Sine");
	test_math_realfunction_libc("sin", &sinf, &ft_sin, 0.0001, 1000, (s_interval){-TAU, 2 * TAU});
	test_math_realfunction_libc("sin", &sinf, &ft_sin, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Tangent");
	test_math_realfunction_libc("tan", &tanf, &ft_tan, 0.0001, 1000, (s_interval){-HALF_PI, HALF_PI});
	test_math_realfunction_libc("tan", &tanf, &ft_tan, 0.0001, 1000, (s_interval){-1e9, 1e9});


	print_math_title("Arc-Cosine");
	test_math_realfunction_libc("acos", &acosf, &ft_acos, 0.0001, 1000, (s_interval){-1, 1});
	test_math_realfunction_libc("acos", &acosf, &ft_acos, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Sine");
	test_math_realfunction_libc("asin", &asinf, &ft_asin, 0.0001, 1000, (s_interval){-1, 1});
	test_math_realfunction_libc("asin", &asinf, &ft_asin, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Tangent");
	test_math_realfunction_libc("atan", &atanf, &ft_atan, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("atan", &atanf, &ft_atan, 0.0001, 1000, (s_interval){-1e9, 1e9});


	print_math_title("Hyperbolic Cosine");
	test_math_realfunction_libc("cosh", &coshf, &ft_cosh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("cosh", &coshf, &ft_cosh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Sine");
	test_math_realfunction_libc("sinh", &sinhf, &ft_sinh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("sinh", &sinhf, &ft_sinh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Tangent");
	test_math_realfunction_libc("tanh", &tanhf, &ft_tanh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("tanh", &tanhf, &ft_tanh, 0.0001, 1000, (s_interval){-1e9, 1e9});


	print_math_title("Hyperbolic Arc-Cosine");
	test_math_realfunction_libc("acosh", &acoshf, &ft_acosh, 0.0001, 1000, (s_interval){1., 50.});
	test_math_realfunction_libc("acosh", &acoshf, &ft_acosh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Sine");
	test_math_realfunction_libc("asinh", &asinhf, &ft_asinh, 0.0001, 1000, (s_interval){-50., 50.});
	test_math_realfunction_libc("asinh", &asinhf, &ft_asinh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Tangent");
	test_math_realfunction_libc("atanh", &atanhf, &ft_atanh, 0.0001, 1000, (s_interval){-1., 1.});
	test_math_realfunction_libc("atanh", &atanhf, &ft_atanh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	return (OK);
}
