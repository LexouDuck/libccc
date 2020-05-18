
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
		if (IS_NAN(error_list.data[i]) || error_list.data[i] > fabs(precision * expects[i])) \
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

//	#define _f(x)	f(x)
#ifdef _FLOAT_32_
	#define _getexp		ilogbf
	#define _fabs		fabsf
	#define _fmod		fmodf
	#define _round		roundf
	#define _trunc		truncf
	#define _floor		floorf
	#define _ceil		ceilf
	#define _pow		powf
	#define _sqrt		sqrtf
	#define _cbrt		cbrtf
	#define _exp		expf
	#define _ln			logf
	#define _lg			log2f
	#define _log		log10f
	#define _cos		cosf
	#define _sin		sinf
	#define _tan		tanf
	#define _acos		acosf
	#define _asin		asinf
	#define _atan		atanf
	#define _atan2		atan2f
	#define _cosh		coshf
	#define _sinh		sinhf
	#define _tanh		tanhf
	#define _acosh		acoshf
	#define _asinh		asinhf
	#define _atanh		atanhf
#endif

#ifdef _FLOAT_64_
	#define _getexp		ilogb
	#define _fabs		fabs
	#define _fmod		fmod
	#define _round		round
	#define _trunc		trunc
	#define _floor		floor
	#define _ceil		ceil
	#define _pow		pow
	#define _sqrt		sqrt
	#define _cbrt		cbrt
	#define _exp		exp
	#define _ln			log
	#define _lg			log2
	#define _log		log10
	#define _cos		cos
	#define _sin		sin
	#define _tan		tan
	#define _acos		acos
	#define _asin		asin
	#define _atan		atan
	#define _atan2		atan2
	#define _cosh		cosh
	#define _sinh		sinh
	#define _tanh		tanh
	#define _acosh		acosh
	#define _asinh		asinh
	#define _atanh		atanh
#endif

#ifdef _FLOAT_80_
	#define _getexp		ilogbl
	#define _fabs		fabsl
	#define _fmod		fmodl
	#define _round		roundl
	#define _trunc		truncl
	#define _floor		floorl
	#define _ceil		ceill
	#define _pow		powl
	#define _sqrt		sqrtl
	#define _cbrt		cbrtl
	#define _exp		expl
	#define _ln			logl
	#define _lg			log2l
	#define _log		log10l
	#define _cos		cosl
	#define _sin		sinl
	#define _tan		tanl
	#define _acos		acosl
	#define _asin		asinl
	#define _atan		atanl
	#define _atan2		atan2l
	#define _cosh		coshl
	#define _sinh		sinhl
	#define _tanh		tanhl
	#define _acosh		acoshl
	#define _asinh		asinhl
	#define _atanh		atanhl
#endif

#ifdef _FLOAT_128_
	#define _getexp		ilogbq
	#define _fabs		fabsq
	#define _fmod		fmodq
	#define _round		roundq
	#define _trunc		truncq
	#define _floor		floorq
	#define _ceil		ceilq
	#define _pow		powq
	#define _sqrt		sqrtq
	#define _cbrt		cbrtq
	#define _exp		expq
	#define _ln			logq
	#define _lg			log2q
	#define _log		log10q
	#define _cos		cosq
	#define _sin		sinq
	#define _tan		tanq
	#define _acos		acosq
	#define _asin		asinq
	#define _atan		atanq
	#define _atan2		atan2q
	#define _cosh		coshq
	#define _sinh		sinhq
	#define _tanh		tanhq
	#define _acosh		acoshq
	#define _asinh		asinhq
	#define _atanh		atanhq
#endif



int		test_math(void)
{
	print_suite_title("math");

	print_math_foreword();



	// TODO test getexp()

	print_math_title("Absolute Value");
	test_math_realfunction_libc("fabs", &_fabs, &ft_fabs, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("fabs", &_fabs, &ft_fabs, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Modulo");
	test_math_realoperator_libc("fmod", &_fmod, &ft_fmod, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-10, 10});
	test_math_realoperator_libc("fmod", &_fmod, &ft_fmod, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-10, 10});
	test_math_realoperator_libc("fmod", &_fmod, &ft_fmod, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-1e9, 1e9});
	test_math_realoperator_libc("fmod", &_fmod, &ft_fmod, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-1e9, 1e9});



//	TODO
//	print_math_title("Round");
//	test_math_realfunction_libc("round", &_round, &ft_round, 0.0001, 1000, (s_interval){-10, 10});
//	test_math_realfunction_libc("round", &_round, &ft_round, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Truncate");
	test_math_realfunction_libc("trunc", &_trunc, &ft_trunc, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("trunc", &_trunc, &ft_trunc, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Floor");
	test_math_realfunction_libc("floor", &_floor, &ft_floor, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("floor", &_floor, &ft_floor, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Ceiling");
	test_math_realfunction_libc("ceil", &_ceil, &ft_ceil, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("ceil", &_ceil, &ft_ceil, 0.0001, 1000, (s_interval){-1e9, 1e9});



	print_math_title("Power");
	test_math_realoperator_libc("pow", &_pow, &ft_pow, 0.0001, 100, (s_interval){0, 4},		(s_interval){-10, 10});
	test_math_realoperator_libc("pow", &_pow, &ft_pow, 0.0001, 100, (s_interval){-100, 1e9},(s_interval){-10, 10});
	test_math_realoperator_libc("pow", &_pow, &ft_pow, 0.0001, 100, (s_interval){0, 4},		(s_interval){-1e6, 1e6});
	test_math_realoperator_libc("pow", &_pow, &ft_pow, 0.0001, 100, (s_interval){-100, 1e9},(s_interval){-1e6, 1e6});

//	TODO
//	print_math_title("N-Power");
//	test_math_realoperator_libc("pow_n", NULL, &ft_pow_n, 0.0001, 100, (s_interval){0, 4},		(s_interval){-10, 10});
//	test_math_realoperator_libc("pow_n", NULL, &ft_pow_n, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-10, 10});
//	test_math_realoperator_libc("pow_n", NULL, &ft_pow_n, 0.0001, 100, (s_interval){0, 4},		(s_interval){-1e6, 1e6});
//	test_math_realoperator_libc("pow_n", NULL, &ft_pow_n, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-1e6, 1e6});



	print_math_title("Square root");
	test_math_realfunction_libc("sqrt", &_sqrt, &ft_sqrt, 0.0001, 1000, (s_interval){0., 5.});
	test_math_realfunction_libc("sqrt", &_sqrt, &ft_sqrt, 0.0001, 1000, (s_interval){-100., 1e9});

	print_math_title("Cubic root");
	test_math_realfunction_libc("cbrt", &_cbrt, &ft_cbrt, 0.0001, 1000, (s_interval){0., 5.});
	test_math_realfunction_libc("cbrt", &_cbrt, &ft_cbrt, 0.0001, 1000, (s_interval){-1e9, 1e9});

//	TODO
//	print_math_title("N-Power root");
//	test_math_realoperator_libc("nrt", NULL, &ft_nrt, 0.0001, 100, (s_interval){0, 5},		(s_interval){-10, 10});
//	test_math_realoperator_libc("nrt", NULL, &ft_nrt, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-10, 10});
//	test_math_realoperator_libc("nrt", NULL, &ft_nrt, 0.0001, 100, (s_interval){0, 5},		(s_interval){-1e6, 1e6});
//	test_math_realoperator_libc("nrt", NULL, &ft_nrt, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-1e6, 1e6});



	print_math_title("Exponential");
	test_math_realfunction_libc("exp", &_exp, &ft_exp, 0.0001, 1000, (s_interval){-1000., 1.});
	test_math_realfunction_libc("exp", &_exp, &ft_exp, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Natural Logarithm");
	test_math_realfunction_libc("ln", &_ln, &ft_ln, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("ln", &_ln, &ft_ln, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Logarithm, base 2");
	test_math_realfunction_libc("lg", &_lg, &ft_lg, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("lg", &_lg, &ft_lg, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Logarithm, base 10");
	test_math_realfunction_libc("log", &_log, &ft_log, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("log", &_log, &ft_log, 0.0001, 1000, (s_interval){1., 1e9});

//	TODO
//	print_math_title("Logarithm, base N");
//	test_math_realoperator_libc("log_n", NULL, &ft_log_n, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-10, 10});
//	test_math_realoperator_libc("log_n", NULL, &ft_log_n, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-10, 10});
//	test_math_realoperator_libc("log_n", NULL, &ft_log_n, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-1e9, 1e9});
//	test_math_realoperator_libc("log_n", NULL, &ft_log_n, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-1e9, 1e9});



	print_math_title("Cosine");
	test_math_realfunction_libc("cos", &_cos, &ft_cos, 0.0001, 1000, (s_interval){-TAU, 2 * TAU});
	test_math_realfunction_libc("cos", &_cos, &ft_cos, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Sine");
	test_math_realfunction_libc("sin", &_sin, &ft_sin, 0.0001, 1000, (s_interval){-TAU, 2 * TAU});
	test_math_realfunction_libc("sin", &_sin, &ft_sin, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Tangent");
	test_math_realfunction_libc("tan", &_tan, &ft_tan, 0.0001, 1000, (s_interval){-HALF_PI, HALF_PI});
	test_math_realfunction_libc("tan", &_tan, &ft_tan, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Cosine");
	test_math_realfunction_libc("acos", &_acos, &ft_acos, 0.0001, 1000, (s_interval){-1, 1});
	test_math_realfunction_libc("acos", &_acos, &ft_acos, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Sine");
	test_math_realfunction_libc("asin", &_asin, &ft_asin, 0.0001, 1000, (s_interval){-1, 1});
	test_math_realfunction_libc("asin", &_asin, &ft_asin, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Tangent");
	test_math_realfunction_libc("atan", &_atan, &ft_atan, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("atan", &_atan, &ft_atan, 0.0001, 1000, (s_interval){-1e9, 1e9});



	print_math_title("Arc-Tangent of (Y / X)");
	test_math_realoperator_libc("atan2", &_atan2, &ft_atan2, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-10, 10});
	test_math_realoperator_libc("atan2", &_atan2, &ft_atan2, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-10, 10});
	test_math_realoperator_libc("atan2", &_atan2, &ft_atan2, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-1e9, 1e9});
	test_math_realoperator_libc("atan2", &_atan2, &ft_atan2, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-1e9, 1e9});



	print_math_title("Hyperbolic Cosine");
	test_math_realfunction_libc("cosh", &_cosh, &ft_cosh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("cosh", &_cosh, &ft_cosh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Sine");
	test_math_realfunction_libc("sinh", &_sinh, &ft_sinh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("sinh", &_sinh, &ft_sinh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Tangent");
	test_math_realfunction_libc("tanh", &_tanh, &ft_tanh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("tanh", &_tanh, &ft_tanh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Cosine");
	test_math_realfunction_libc("acosh", &_acosh, &ft_acosh, 0.0001, 1000, (s_interval){1., 50.});
	test_math_realfunction_libc("acosh", &_acosh, &ft_acosh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Sine");
	test_math_realfunction_libc("asinh", &_asinh, &ft_asinh, 0.0001, 1000, (s_interval){-50., 50.});
	test_math_realfunction_libc("asinh", &_asinh, &ft_asinh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Tangent");
	test_math_realfunction_libc("atanh", &_atanh, &ft_atanh, 0.0001, 1000, (s_interval){-1., 1.});
	test_math_realfunction_libc("atanh", &_atanh, &ft_atanh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	return (OK);
}
