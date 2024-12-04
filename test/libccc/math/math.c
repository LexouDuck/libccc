
#include <math.h>
#include <time.h>

#include "libccc/sys/io.h"
#include "libccc/math.h"
#include "libccc/math/algebra.h"
#include "libccc/math/stat.h"
#define NOTYPEDEF // avoid typedef redefinitions
#define T_TYPE	t_sint
#define T_NAME	int
#define T_NULL	0
#include "libccc/monad/array.c"
#define T_TYPE	t_float
#define T_NAME	float
#define T_NULL	0
#include "libccc/monad/array.c"

#include "test.h"



void	print_math_foreword(void)
{
	if (g_test.config.verbose)
	{
		printf("\n\n" ANSI_COLOR_FG_BLUE "Floating-point (%d-bit %s precision) math functions" ANSI_RESET "\n\n",
#if LIBCONFIG_FLOAT_BITS == 32
			32, "IEEE single");
#endif
#if LIBCONFIG_FLOAT_BITS == 64
			64, "IEEE double");
#endif
#if LIBCONFIG_FLOAT_BITS == 80
			80, "x86 extended");
#endif
#if LIBCONFIG_FLOAT_BITS == 128
			128, "IEEE quadruple");
#endif
	}
}

void	print_math_title(char const * title)
{
	if (g_test.config.verbose)
	{
		printf("\n\n" ANSI_COLOR_FG_BLUE "%s" ANSI_RESET "\n", title);
	}
}



#define SF_FORMAT	":\t%s%g"

static
void printf_colored(const char* label, t_float precision, t_float value)
{
	printf("%s", label);
	if (precision == 0.)
	{
		if (value == 0. || isnan(value))
			printf(SF_FORMAT "\n", "", value);
		else if (value < 0)
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_RED, value);
		else if (value > 0)
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_GREEN, value);
	}
	else
	{
		if (value < precision)
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_GREEN, value);
		else
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_RED, value);
	}
}



#define TEST_PERFORM_MATH_REALFUNCTION(CALL, RESULTS, FUNCTION) \
	x = interval.start; \
	timer_clock(&timer.CALL##_start); \
	for (int i = 0; i < tests; ++i) \
	{ \
		x += step; \
		RESULTS[i] = FUNCTION(x); \
	} \
	timer_clock(&timer.CALL##_end); \

#define TEST_PERFORM_MATH_REALOPERATOR(CALL, RESULTS, FUNCTION) \
	x = interval_x.start; \
	y = interval_y.start; \
	timer_clock(&timer.CALL##_start); \
	for (int i = 0; i < tests_interval; ++i) \
	{ \
		for (int j = 0; j < tests_interval; ++j) \
		{ \
			x += step_x; \
			RESULTS[i * tests_interval + j] = FUNCTION(x, y); \
		} \
		y += step_y; \
	} \
	timer_clock(&timer.CALL##_end); \



#define TEST_GET_RESULTS() \
	for (int i = 0; i < tests; ++i) \
	{ \
		if (expects[i] == results[i] || (isnan(expects[i]) && isnan(results[i]))) \
			errors[i] = 0; \
		else if (isnan(expects[i]) || isnan(results[i])) \
			errors[i] = NAN; \
		else \
			errors[i] = c_distance_float(expects[i], results[i]); \
		if (isnan(errors[i]) || errors[i] > fabs(precision * expects[i])) \
		{ \
			++failed_tests; \
			if (g_test.config.verbose && g_test.config.show_args && precision < fabs(results[i] - expects[i])) \
			{ \
				printf("TEST N°%d: -> returned %g but libc returned %g (difference is " ANSI_COLOR_FG_RED "%g" ANSI_RESET ")\n", \
					i, results[i], expects[i], errors[i]); \
			} \
		} \
	} \



#define TEST_PRINT_MATH(...) \
	g_test.suites[TESTSUITE_MATH].totals.tests += tests; \
	g_test.suites[TESTSUITE_MATH].totals.failed += failed_tests; \
	t_float percent = (tests - failed_tests) * 100. / tests; \
	if (g_test.config.verbose || percent < 90.) \
	{ \
		printf("\n%s\n", func_name); \
		printf(__VA_ARGS__); \
		printf("Success rate for %g precision: ", precision); \
		print_percent(percent); \
	} \

static void	print_test_math(s_timer timer, t_float* errors, t_float precision, int amount)
{
	if (g_test.config.verbose)
	{
		quicksort_float(errors, 0, amount);
		printf_colored("Largest error", precision,      stat_getmax_float   (errors, amount));
		printf_colored("Average error", precision,      stat_average_float  (errors, amount));
		printf_colored("Median error",  precision,      stat_median_float   (errors, amount));
		printf_colored("Standard dev.", precision, sqrt(stat_variance_float (errors, amount)));
	}
	if (g_test.config.show_speed)
	{
		printf("-> Execution time:");
		print_timer_result(&timer, TRUE);
	}
	if (g_test.config.verbose)
	{
		printf("\n");
	}
	fflush(stdout);
}



int		test_math_realfunction_libc(
	char const *		func_name,
	f_float_function	func_libc,
	f_float_function	func_libccc,
	t_float				precision,
	int					tests,
	s_interval			interval)
{
	t_float* expects = malloc(tests * sizeof(t_float));
	t_float* results = malloc(tests * sizeof(t_float));
	t_float* errors  = malloc(tests * sizeof(t_float));
	unsigned int failed_tests = 0;
	s_timer timer = {0};
	t_float	x;
	t_float	step = (interval.end - interval.start) / tests;
	TEST_PERFORM_MATH_REALFUNCTION(result, results, func_libccc)
	if (func_libc)
	{
		TEST_PERFORM_MATH_REALFUNCTION(expect, expects, func_libc)
	}
	TEST_GET_RESULTS()
	TEST_PRINT_MATH("Ran %d tests on interval [%g,%g], with increment=%g\n", tests, interval.start, interval.end, step)
	print_test_math(timer, errors, precision, tests);
	free(expects);
	free(results);
	free(errors);
	return (OK);
}

int		test_math_realoperator_libc(
	char const *		func_name,
	f_float_operator	func_libc,
	f_float_operator	func_libccc,
	t_float				precision,
	int					tests,
	s_interval			interval_x,
	s_interval			interval_y)
{
	int tests_interval = tests;
	tests *= tests;
	t_float* expects = malloc(tests * sizeof(t_float));
	t_float* results = malloc(tests * sizeof(t_float));
	t_float* errors  = malloc(tests * sizeof(t_float));
	unsigned int failed_tests = 0;
	s_timer timer = {0};
	t_float	x;
	t_float	y;
	t_float	step_x = (interval_x.end - interval_x.start) / tests_interval;
	t_float	step_y = (interval_y.end - interval_y.start) / tests_interval;
	TEST_PERFORM_MATH_REALOPERATOR(result, results, func_libccc)
	if (func_libc)
	{
		TEST_PERFORM_MATH_REALOPERATOR(expect, expects, func_libc)
	}
	TEST_GET_RESULTS()
	TEST_PRINT_MATH("Ran %d tests with:\n"
		"arg1: interval [%g,%g], with increment=%g\n"
		"arg2: interval [%g,%g], with increment=%g\n",
		tests,
		interval_x.start, interval_x.end, step_x,
		interval_y.start, interval_y.end, step_y)
	print_test_math(timer, errors, precision, tests);
	free(expects);
	free(results);
	free(errors);
	return (OK);
}

//	#define _f(x)	f(x)
#if LIBCONFIG_FLOAT_BITS == 32
	#define _nearbyint	nearbyintf
	#define _nextafter	nextafterf
	#define _copysign	copysignf
	#define _getexp		ilogbf
	#define _fabs		fabsf
	#define _fmod		fmodf
	#define _rem		remainderf
	#define _remquo		remquof
	#define _round		roundf
	#define _trunc		truncf
	#define _floor		floorf
	#define _ceil		ceilf
	#define _pow		powf
	#define _sqrt		sqrtf
	#define _cbrt		cbrtf
	#define _hypot		hypotf
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

#if LIBCONFIG_FLOAT_BITS == 64
	#define _nearbyint	nearbyint
	#define _nextafter	nextafter
	#define _copysign	copysign
	#define _getexp		ilogb
	#define _fabs		fabs
	#define _fmod		fmod
	#define _rem		remainder
	#define _remquo		remquo
	#define _round		round
	#define _trunc		trunc
	#define _floor		floor
	#define _ceil		ceil
	#define _pow		pow
	#define _sqrt		sqrt
	#define _cbrt		cbrt
	#define _hypot		hypot
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

#if LIBCONFIG_FLOAT_BITS == 80 || LIBCONFIG_FLOAT_BITS == 128
	#define _nearbyint	nearbyintl
	#define _nextafter	nextafterl
	#define _copysign	copysignl
	#define _getexp		ilogbl
	#define _fabs		fabsl
	#define _fmod		fmodl
	#define _rem		remainderl
	#define _remquo		remquol
	#define _round		roundl
	#define _trunc		truncl
	#define _floor		floorl
	#define _ceil		ceill
	#define _pow		powl
	#define _sqrt		sqrtl
	#define _cbrt		cbrtl
	#define _hypot		hypotl
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



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

#ifndef TARGET_PRECISION
#define TARGET_PRECISION	0.0001
#endif

int		testsuite_math(void)
{
	print_suite_title("libccc/math");

	print_math_foreword();


/*
	print_math_title("Split Float");
	test_math_realfunction_libc("frexp", &_frexp, &c_frexp, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});

	print_math_title("Get Exponent (base-2)");
	test_math_realfunction_libc("getexp", &_getexp, &c_fgetexp2, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});
*/
	print_math_title("Nearby Int");
	test_math_realfunction_libc("nearbyint", &_nearbyint, &c_nearbyint, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9});

	print_math_title("Next After");
	test_math_realoperator_libc("nextafter", &_nextafter, &c_nextafter, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e9,+1e9});

	print_math_title("Copy Sign");
	test_math_realoperator_libc("copysign", &_copysign, &c_copysign, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e9,+1e9});



	print_math_title("Absolute Value");
	test_math_realfunction_libc("abs", &_fabs, &c_fabs, TARGET_PRECISION, 10000, (s_interval){-1e1,+1e1});
	test_math_realfunction_libc("abs", &_fabs, &c_fabs, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});

	print_math_title("Round");
	test_math_realfunction_libc("round", &_round, &c_fround, TARGET_PRECISION, 10000, (s_interval){-1e1,+1e1});
	test_math_realfunction_libc("round", &_round, &c_fround, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});

	print_math_title("Truncate");
	test_math_realfunction_libc("trunc", &_trunc, &c_ftrunc, TARGET_PRECISION, 10000, (s_interval){-1e1,+1e1});
	test_math_realfunction_libc("trunc", &_trunc, &c_ftrunc, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});

	print_math_title("Floor");
	test_math_realfunction_libc("floor", &_floor, &c_ffloor, TARGET_PRECISION, 10000, (s_interval){-1e1,+1e1});
	test_math_realfunction_libc("floor", &_floor, &c_ffloor, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});

	print_math_title("Ceiling");
	test_math_realfunction_libc("ceil", &_ceil, &c_fceil, TARGET_PRECISION, 10000, (s_interval){-1e1,+1e1});
	test_math_realfunction_libc("ceil", &_ceil, &c_fceil, TARGET_PRECISION, 10000, (s_interval){-1e9,+1e9});



	print_math_title("Modulo");
	test_math_realoperator_libc("mod", &_fmod, &c_fmod, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("mod", &_fmod, &c_fmod, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("mod", &_fmod, &c_fmod, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e9,+1e9});
	test_math_realoperator_libc("mod", &_fmod, &c_fmod, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e9,+1e9});

	print_math_title("Remainder");
	test_math_realoperator_libc("rem", &_rem, &c_frem, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("rem", &_rem, &c_frem, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("rem", &_rem, &c_frem, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e9,+1e9});
	test_math_realoperator_libc("rem", &_rem, &c_frem, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e9,+1e9});



	print_math_title("Power");
	test_math_realoperator_libc("pow", &_pow, &c_fpow, TARGET_PRECISION, 100, (s_interval){ 0e0,+4e0}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("pow", &_pow, &c_fpow, TARGET_PRECISION, 100, (s_interval){-1e1,+1e9}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("pow", &_pow, &c_fpow, TARGET_PRECISION, 100, (s_interval){ 0e0,+4e0}, (s_interval){-1e6,+1e6});
	test_math_realoperator_libc("pow", &_pow, &c_fpow, TARGET_PRECISION, 100, (s_interval){-1e1,+1e9}, (s_interval){-1e6,+1e6});

//	TODO
//	print_math_title("N-Power");
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, TARGET_PRECISION, 100, (s_interval){ 0e0,+4e0}, (s_interval){-1e1,+1e1});
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, TARGET_PRECISION, 100, (s_interval){-1e1,+1e9}, (s_interval){-1e1,+1e1});
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, TARGET_PRECISION, 100, (s_interval){ 0e0,+4e0}, (s_interval){-1e6,+1e6});
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, TARGET_PRECISION, 100, (s_interval){-1e1,+1e9}, (s_interval){-1e6,+1e6});

	print_math_title("Square root");
	test_math_realfunction_libc("sqrt", &_sqrt, &c_fsqrt, TARGET_PRECISION, 1000, (s_interval){ 0e0,+5e0});
	test_math_realfunction_libc("sqrt", &_sqrt, &c_fsqrt, TARGET_PRECISION, 1000, (s_interval){-1e1,+1e9});

	print_math_title("Cubic root");
	test_math_realfunction_libc("cbrt", &_cbrt, &c_fcbrt, TARGET_PRECISION, 1000, (s_interval){ 0e0,+5e0});
	test_math_realfunction_libc("cbrt", &_cbrt, &c_fcbrt, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

//	TODO
//	print_math_title("N-Power root");
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, TARGET_PRECISION, 100, (s_interval){ 0e0,+5e0}, (s_interval){-1e1,+1e1});
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e1,+1e1});
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, TARGET_PRECISION, 100, (s_interval){ 0e0,+5e0}, (s_interval){-1e6,+1e6});
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e6,+1e6});

	print_math_title("Hypotenuse");
	test_math_realoperator_libc("hypot", &_hypot, &c_hypot, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("hypot", &_hypot, &c_hypot, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("hypot", &_hypot, &c_hypot, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e9,+1e9});
	test_math_realoperator_libc("hypot", &_hypot, &c_hypot, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e9,+1e9});



	print_math_title("Exponential");
	test_math_realfunction_libc("exp", &_exp, &c_fexp, TARGET_PRECISION, 1000, (s_interval){-1e3,+1e0});
	test_math_realfunction_libc("exp", &_exp, &c_fexp, TARGET_PRECISION, 1000, (s_interval){+1e0,+1e9});

	print_math_title("Natural Logarithm");
	test_math_realfunction_libc("ln", &_ln, &c_fln, TARGET_PRECISION, 1000, (s_interval){0e0,+1e0});
	test_math_realfunction_libc("ln", &_ln, &c_fln, TARGET_PRECISION, 1000, (s_interval){1e0,+1e9});

	print_math_title("Logarithm, base 2");
	test_math_realfunction_libc("lg", &_lg, &c_flog2, TARGET_PRECISION, 1000, (s_interval){0e0,+1e0});
	test_math_realfunction_libc("lg", &_lg, &c_flog2, TARGET_PRECISION, 1000, (s_interval){1e0,+1e9});

	print_math_title("Logarithm, base 10");
	test_math_realfunction_libc("log", &_log, &c_flog10, TARGET_PRECISION, 1000, (s_interval){0e0,+1e0});
	test_math_realfunction_libc("log", &_log, &c_flog10, TARGET_PRECISION, 1000, (s_interval){1e0,+1e9});

//	TODO
//	print_math_title("Logarithm, base N");
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e1,+1e1});
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, TARGET_PRECISION, 100, (s_interval){-1e2,+1e9}, (s_interval){-1e1,+1e1});
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e9,+1e9});
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, TARGET_PRECISION, 100, (s_interval){-1e2,+1e9}, (s_interval){-1e9,+1e9});



	print_math_title("Cosine");
	test_math_realfunction_libc("cos", &_cos, &c_fcos, TARGET_PRECISION, 1000, (s_interval){-PI_HALF,+PI_HALF});
	test_math_realfunction_libc("cos", &_cos, &c_fcos, TARGET_PRECISION, 1000, (s_interval){-TAU,+TAU*2});
	test_math_realfunction_libc("cos", &_cos, &c_fcos, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Sine");
	test_math_realfunction_libc("sin", &_sin, &c_fsin, TARGET_PRECISION, 1000, (s_interval){ 0, +PI });
	test_math_realfunction_libc("sin", &_sin, &c_fsin, TARGET_PRECISION, 1000, (s_interval){-TAU,+TAU*2});
	test_math_realfunction_libc("sin", &_sin, &c_fsin, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Tangent");
	test_math_realfunction_libc("tan", &_tan, &c_ftan, TARGET_PRECISION, 1000, (s_interval){-PI_HALF,+PI_HALF});
	test_math_realfunction_libc("tan", &_tan, &c_ftan, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Arc-Cosine");
	test_math_realfunction_libc("acos", &_acos, &c_facos, TARGET_PRECISION, 1000, (s_interval){-1e0,+1e0});
	test_math_realfunction_libc("acos", &_acos, &c_facos, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Arc-Sine");
	test_math_realfunction_libc("asin", &_asin, &c_fasin, TARGET_PRECISION, 1000, (s_interval){-1e0,+1e0});
	test_math_realfunction_libc("asin", &_asin, &c_fasin, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Arc-Tangent");
	test_math_realfunction_libc("atan", &_atan, &c_fatan, TARGET_PRECISION, 1000, (s_interval){-TAU,+TAU});
	test_math_realfunction_libc("atan", &_atan, &c_fatan, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});



	print_math_title("Arc-Tangent of (Y / X)");
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e1,+1e1});
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, TARGET_PRECISION, 100, (s_interval){-1e1,+1e1}, (s_interval){-1e9,+1e9});
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, TARGET_PRECISION, 100, (s_interval){-1e9,+1e9}, (s_interval){-1e9,+1e9});



	print_math_title("Hyperbolic Cosine");
	test_math_realfunction_libc("cosh", &_cosh, &c_fcosh, TARGET_PRECISION, 1000, (s_interval){-TAU,+TAU});
	test_math_realfunction_libc("cosh", &_cosh, &c_fcosh, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Hyperbolic Sine");
	test_math_realfunction_libc("sinh", &_sinh, &c_fsinh, TARGET_PRECISION, 1000, (s_interval){-TAU,+TAU});
	test_math_realfunction_libc("sinh", &_sinh, &c_fsinh, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Hyperbolic Tangent");
	test_math_realfunction_libc("tanh", &_tanh, &c_ftanh, TARGET_PRECISION, 1000, (s_interval){-TAU,+TAU});
	test_math_realfunction_libc("tanh", &_tanh, &c_ftanh, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Hyperbolic Arc-Cosine");
	test_math_realfunction_libc("acosh", &_acosh, &c_facosh, TARGET_PRECISION, 1000, (s_interval){+1e0,+5e1});
	test_math_realfunction_libc("acosh", &_acosh, &c_facosh, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Hyperbolic Arc-Sine");
	test_math_realfunction_libc("asinh", &_asinh, &c_fasinh, TARGET_PRECISION, 1000, (s_interval){-5e1,+5e1});
	test_math_realfunction_libc("asinh", &_asinh, &c_fasinh, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	print_math_title("Hyperbolic Arc-Tangent");
	test_math_realfunction_libc("atanh", &_atanh, &c_fatanh, TARGET_PRECISION, 1000, (s_interval){-1e0,+1e0});
	test_math_realfunction_libc("atanh", &_atanh, &c_fatanh, TARGET_PRECISION, 1000, (s_interval){-1e9,+1e9});

	return (OK);
}
