
#include <math.h>
#include <time.h>

#include "libccc/sys/io.h"
#include "libccc/math.h"
#include "libccc/math/stat.h"

#include "test.h"
#include "test_utils.h"



void	print_math_title(char const * title)
{
	if (g_test.config.verbose)
	{
		printf("\n\n" ANSI_COLOR_FG_BLUE "%s" ANSI_RESET "\n", title);
	}
}



#define SF_FORMAT	":\t%s%g"
#define SF_NUMBER	ANSI_COLOR_FG_YELLOW "%-+9.6g" ANSI_RESET



#define TEST_PERFORM_MATH_REALFUNCTION(CALL, RESULTS, FUNCTION) \
	x = interval.start; \
	timer_clock(&timer.CALL##_start); \
	for (unsigned int i = 0; i < tests; ++i) \
	{ \
		x += step; \
		args[i] = x; \
		RESULTS[i] = FUNCTION(x); \
	} \
	timer_clock(&timer.CALL##_end); \

#define TEST_PERFORM_MATH_REALOPERATOR(CALL, RESULTS, FUNCTION) \
	x = interval_x.start; \
	y = interval_y.start; \
	timer_clock(&timer.CALL##_start); \
	for (unsigned int i = 0; i < tests_interval; ++i) \
	{ \
		for (unsigned int j = 0; j < tests_interval; ++j) \
		{ \
			x += step_x; \
			int index = i * tests_interval + j; \
			args_x[index] = x; \
			args_y[index] = y; \
			RESULTS[index] = FUNCTION(x, y); \
		} \
		y += step_y; \
	} \
	timer_clock(&timer.CALL##_end); \



#define TEST_GET_RESULTS(...) \
	for (unsigned int i = 0; i < tests; ++i) \
	{ \
		if (expects[i] == results[i])	errors[i] = 0; \
		else if (isnan(expects[i]) && isnan(results[i]))	errors[i] = 0; \
		else if (isnan(expects[i]) || isnan(results[i]))	errors[i] = INF; \
		else if (isinf(expects[i]) && isinf(results[i]))	errors[i] = INF; \
		else if (isinf(expects[i]) || isinf(results[i]))	errors[i] = INF; \
		else \
		{ \
			errors[i] = fabs(expects[i] - results[i]); \
		/*	errors[i] /= MAX(fabs(expects[i]), fabs(results[i])); / * uncomment this line for relative error */ \
		} \
		if (isinf(errors[i]) || errors[i] > fabs(precision * expects[i])) \
		{ \
			++failed_tests; \
			if (TRUE) /* (g_test.config.verbose && g_test.config.show_args) */ \
			{ \
				__VA_ARGS__ \
			} \
		} \
	} \



#define TEST_PRINT_MATH(...) \
	g_test.suites[TESTSUITE_MATH].totals.tests += tests; \
	g_test.suites[TESTSUITE_MATH].totals.failed += failed_tests; \
	t_float percent = (tests - failed_tests) * 100. / tests; \
	if (g_test.config.verbose || percent < 100.) \
	{ \
		printf("\n%s\n", func_name); \
		printf(__VA_ARGS__); \
		printf("Success rate for %g precision: ", precision); \
		print_percent(percent); \
	} \



#define DEFINETEST_MATH_FLOAT(BITS) \
typedef struct f##BITS##_interval \
{ \
	t_f##BITS start; \
	t_f##BITS end; \
}	s_f##BITS##_interval; \
 \
static \
void printf_colored_f##BITS(char const* label, t_f##BITS precision, t_f##BITS value) \
{ \
	printf("%s", label); \
	if (precision == 0.) \
	{ \
		if (value == 0. || isnan(value)) \
			printf(SF_FORMAT "\n", "", value); \
		else if (value < 0) \
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_RED, value); \
		else if (value > 0) \
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_GREEN, value); \
	} \
	else \
	{ \
		if (value < precision) \
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_GREEN, value); \
		else \
			printf(SF_FORMAT "\n" ANSI_RESET, ANSI_COLOR_FG_RED, value); \
	} \
} \
 \
static \
void	print_test_math_f##BITS( \
	s_timer timer, \
	t_f##BITS const* results, \
	t_f##BITS const* expects, \
	t_f##BITS* errors, \
	t_f##BITS precision, \
	int amount) \
{ \
	if (g_test.config.verbose) \
	{ \
		quicksort_f##BITS(errors, 0, amount); \
		printf_colored_f##BITS("largest error", precision, stat_getmax_f##BITS          (errors, amount)); \
		printf_colored_f##BITS("median error",  precision, stat_median_f##BITS          (errors, amount)); \
		printf_colored_f##BITS("mean error",    precision, stat_mean_arithmetic_f##BITS (errors, amount)); \
		printf_colored_f##BITS("standard dev",  precision, stat_variance_f##BITS        (errors, amount)); \
		printf_colored_f##BITS("sqrt mean dev", precision, stat_rmsd_f##BITS            (results, expects, amount)); \
	} \
	if (g_test.config.show_speed) \
	{ \
		printf("-> Execution time:"); \
		print_timer_result(&timer, TRUE); \
	} \
	if (g_test.config.verbose) \
	{ \
		printf("\n"); \
	} \
	fflush(stdout); \
} \
 \
int	test_math_realfunction_f##BITS( \
	char const*           func_name, \
	f_f##BITS##_function  func_libc, \
	f_f##BITS##_function  func_libccc, \
	t_f##BITS             precision, \
	unsigned int          tests, \
	s_f##BITS##_interval  interval) \
{ \
	t_f##BITS* expects = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* results = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* errors  = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* args    = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	unsigned int failed_tests = 0; \
	s_timer timer = {0}; \
	t_f##BITS	x; \
	t_f##BITS	step = (interval.end - interval.start) / tests; \
	TEST_PERFORM_MATH_REALFUNCTION(result, results, func_libccc) \
	if (func_libc) \
	{ \
		TEST_PERFORM_MATH_REALFUNCTION(expect, expects, func_libc) \
	} \
	TEST_GET_RESULTS( \
		printf("\n" ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET " #%03d: %s(" SF_NUMBER ") -> returned " SF_NUMBER " but libc returned " SF_NUMBER " (difference is " SF_NUMBER ")", \
			i, func_name, args[i], results[i], expects[i], errors[i]);) \
	TEST_PRINT_MATH("Ran %d tests on interval [%g,%g], with increment=%g\n", tests, interval.start, interval.end, step) \
	print_test_math_f##BITS(timer, results, expects, errors, precision, tests); \
	free(expects); \
	free(results); \
	free(errors); \
	return (OK); \
} \
 \
int	test_math_realoperator_f##BITS( \
	char const*           func_name, \
	f_f##BITS##_operator  func_libc, \
	f_f##BITS##_operator  func_libccc, \
	t_f##BITS             precision, \
	unsigned int          tests, \
	s_f##BITS##_interval  interval_x, \
	s_f##BITS##_interval  interval_y) \
{ \
	unsigned int tests_interval = tests; \
	tests *= tests; \
	t_f##BITS* expects = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* results = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* errors  = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* args_x  = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	t_f##BITS* args_y  = (t_f##BITS*)malloc(tests * sizeof(t_f##BITS)); \
	unsigned int failed_tests = 0; \
	s_timer timer = {0}; \
	t_f##BITS	x; \
	t_f##BITS	y; \
	t_f##BITS	step_x = (interval_x.end - interval_x.start) / tests_interval; \
	t_f##BITS	step_y = (interval_y.end - interval_y.start) / tests_interval; \
	TEST_PERFORM_MATH_REALOPERATOR(result, results, func_libccc) \
	if (func_libc) \
	{ \
		TEST_PERFORM_MATH_REALOPERATOR(expect, expects, func_libc) \
	} \
	TEST_GET_RESULTS( \
		printf("\n" ANSI_COLOR_FG_RED "TEST FAILED" ANSI_RESET " #%03d: %s(" SF_NUMBER ", " SF_NUMBER ") -> returned " SF_NUMBER " but libc returned " SF_NUMBER " (difference is " SF_NUMBER ")", \
			i, func_name, args_x[i], args_y[i], results[i], expects[i], errors[i]);) \
	TEST_PRINT_MATH("Ran %d tests with:\n" \
		"arg1: interval [%g,%g], with increment=%g\n" \
		"arg2: interval [%g,%g], with increment=%g\n", \
		tests, \
		interval_x.start, interval_x.end, step_x, \
		interval_y.start, interval_y.end, step_y) \
	print_test_math_f##BITS(timer, results, expects, errors, precision, tests); \
	free(expects); \
	free(results); \
	free(errors); \
	return (OK); \
} \



#if LIBCONFIG_USE_FLOAT16
DEFINETEST_MATH_FLOAT(16)
#endif
#if TRUE
DEFINETEST_MATH_FLOAT(32)
#endif
#if TRUE
DEFINETEST_MATH_FLOAT(64)
#endif
#if LIBCONFIG_USE_FLOAT80
DEFINETEST_MATH_FLOAT(80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINETEST_MATH_FLOAT(128)
#endif



#if LIBCONFIG_USE_FLOAT80 && LIBCONFIG_USE_FLOAT128
#error "impossible to have both 80-bit and 128-bit floating point types simultaneously"

#elif LIBCONFIG_USE_FLOAT80

	#if LIBCONFIG_USE_FLOAT16

#define RUNTESTS_MATH_FUNCTION(NAME, CNAME, AMOUNT, ARG_MIN,ARG_MAX) \
	test_math_realfunction_f16  ("(f16) "#NAME, &CNAME##f, &c_f16 ##NAME, 0.01,     AMOUNT, (s_f16_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f80  ("(f80) "#NAME, &CNAME##l, &c_f80 ##NAME, 0.00001,  AMOUNT, (s_f80_interval)ARG_MIN,ARG_MAX); \

#define RUNTESTS_MATH_OPERATOR(NAME, CNAME, AMOUNT, ARG1_MIN,ARG1_MAX, ARG2_MIN,ARG2_MAX) \
	test_math_realoperator_f16  ("(f16) "#NAME, &CNAME##f, &c_f16 ##NAME, 0.01,     AMOUNT, (s_f16_interval)ARG1_MIN,ARG1_MAX, (s_f16_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG1_MIN,ARG1_MAX, (s_f32_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG1_MIN,ARG1_MAX, (s_f64_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f80  ("(f80) "#NAME, &CNAME##l, &c_f80 ##NAME, 0.00001,  AMOUNT, (s_f80_interval)ARG1_MIN,ARG1_MAX, (s_f80_interval)ARG2_MIN,ARG2_MAX); \

	#else

#define RUNTESTS_MATH_FUNCTION(NAME, CNAME, AMOUNT, ARG_MIN,ARG_MAX) \
	test_math_realfunction_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f80  ("(f80) "#NAME, &CNAME##l, &c_f80 ##NAME, 0.00001,  AMOUNT, (s_f80_interval)ARG_MIN,ARG_MAX); \

#define RUNTESTS_MATH_OPERATOR(NAME, CNAME, AMOUNT, ARG1_MIN,ARG1_MAX, ARG2_MIN,ARG2_MAX) \
	test_math_realoperator_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG1_MIN,ARG1_MAX, (s_f32_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG1_MIN,ARG1_MAX, (s_f64_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f80  ("(f80) "#NAME, &CNAME##l, &c_f80 ##NAME, 0.00001,  AMOUNT, (s_f80_interval)ARG1_MIN,ARG1_MAX, (s_f80_interval)ARG2_MIN,ARG2_MAX); \

	#endif

#elif LIBCONFIG_USE_FLOAT128

	#if LIBCONFIG_USE_FLOAT16

#define RUNTESTS_MATH_FUNCTION(NAME, CNAME, AMOUNT, ARG_MIN,ARG_MAX) \
	test_math_realfunction_f16  ("(f16) "#NAME, &CNAME##f, &c_f16 ##NAME, 0.01,     AMOUNT, (s_f16_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f128 ("(f128)"#NAME, &CNAME##l, &c_f128##NAME, 0.000001, AMOUNT, (s_f128_interval)ARG_MIN,ARG_MAX); \

#define RUNTESTS_MATH_OPERATOR(NAME, CNAME, AMOUNT, ARG1_MIN,ARG1_MAX, ARG2_MIN,ARG2_MAX) \
	test_math_realoperator_f16  ("(f16) "#NAME, &CNAME##f, &c_f16 ##NAME, 0.01,     AMOUNT, (s_f16_interval)ARG1_MIN,ARG1_MAX, (s_f16_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG1_MIN,ARG1_MAX, (s_f32_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG1_MIN,ARG1_MAX, (s_f64_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f128 ("(f128)"#NAME, &CNAME##l, &c_f128##NAME, 0.000001, AMOUNT, (s_f128_interval)ARG1_MIN,ARG1_MAX, (s_f128_interval)ARG2_MIN,ARG2_MAX); \

	#else

#define RUNTESTS_MATH_FUNCTION(NAME, CNAME, AMOUNT, ARG_MIN,ARG_MAX) \
	test_math_realfunction_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f128 ("(f128)"#NAME, &CNAME##l, &c_f128##NAME, 0.000001, AMOUNT, (s_f128_interval)ARG_MIN,ARG_MAX); \

#define RUNTESTS_MATH_OPERATOR(NAME, CNAME, AMOUNT, ARG1_MIN,ARG1_MAX, ARG2_MIN,ARG2_MAX) \
	test_math_realoperator_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG1_MIN,ARG1_MAX, (s_f32_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG1_MIN,ARG1_MAX, (s_f64_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f128 ("(f128)"#NAME, &CNAME##l, &c_f128##NAME, 0.000001, AMOUNT, (s_f128_interval)ARG1_MIN,ARG1_MAX, (s_f128_interval)ARG2_MIN,ARG2_MAX); \

	#endif

#else

	#if LIBCONFIG_USE_FLOAT16

#define RUNTESTS_MATH_FUNCTION(NAME, CNAME, AMOUNT, ARG_MIN,ARG_MAX) \
	test_math_realfunction_f16  ("(f16) "#NAME, &CNAME##f, &c_f16 ##NAME, 0.01,     AMOUNT, (s_f16_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG_MIN,ARG_MAX); \

#define RUNTESTS_MATH_OPERATOR(NAME, CNAME, AMOUNT, ARG1_MIN,ARG1_MAX, ARG2_MIN,ARG2_MAX) \
	test_math_realoperator_f16  ("(f16) "#NAME, &CNAME##f, &c_f16 ##NAME, 0.01,     AMOUNT, (s_f16_interval)ARG1_MIN,ARG1_MAX, (s_f16_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG1_MIN,ARG1_MAX, (s_f32_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG1_MIN,ARG1_MAX, (s_f64_interval)ARG2_MIN,ARG2_MAX); \

	#else

#define RUNTESTS_MATH_FUNCTION(NAME, CNAME, AMOUNT, ARG_MIN,ARG_MAX) \
	test_math_realfunction_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG_MIN,ARG_MAX); \
	test_math_realfunction_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG_MIN,ARG_MAX); \

#define RUNTESTS_MATH_OPERATOR(NAME, CNAME, AMOUNT, ARG1_MIN,ARG1_MAX, ARG2_MIN,ARG2_MAX) \
	test_math_realoperator_f32  ("(f32) "#NAME, &CNAME##f, &c_f32 ##NAME, 0.001,    AMOUNT, (s_f32_interval)ARG1_MIN,ARG1_MAX, (s_f32_interval)ARG2_MIN,ARG2_MAX); \
	test_math_realoperator_f64  ("(f64) "#NAME, &CNAME   , &c_f64 ##NAME, 0.0001,   AMOUNT, (s_f64_interval)ARG1_MIN,ARG1_MAX, (s_f64_interval)ARG2_MIN,ARG2_MAX); \

	#endif

#endif




/*============================================================================*\
||                            Test Suite Function                             ||
\*============================================================================*/

int		testsuite_math(void)
{
	print_suite_title("libccc/math");
#if 0
	#if !LIBCONFIG_USE_STD_MATH
		#if TRUE
		TESTSUITE_MATH(f, 32, "IEEE single", 0.001)
		#endif
		#if TRUE
		TESTSUITE_MATH( , 64, "IEEE double", 0.0001)
		#endif
		#if LIBCONFIG_USE_FLOAT80
		TESTSUITE_MATH(l, 80, "x86 extended", 0.00001)
		#endif
		#if LIBCONFIG_USE_FLOAT128
		TESTSUITE_MATH(l, 128, "IEEE quadruple", 0.000001)
		#endif
	#endif
	if (g_test.config.verbose)
	{
		printf("\n\n" ANSI_COLOR_FG_BLUE "Floating-point (%d-bit %s precision) math functions" ANSI_RESET "\n\n", BITS, NAME);
	}
#endif
/*
	print_math_title("Split float exponent");
	RUNTESTS_MATH_FUNCTION(splitexp, frexp, 500, {-1e9,+1e9});
	print_math_title("Split float integer / fraction");
	RUNTESTS_MATH_FUNCTION(splitint, modf, 500, {-1e9,+1e9});
	print_math_title("Get Exponent (base-2)");
	RUNTESTS_MATH_FUNCTION(getexp2, ilogb, 500, {-1e9,+1e9});
	print_math_title("Get Exponent (base-10)");
	RUNTESTS_MATH_FUNCTION(getexp10, ilog, 500, {-1e9,+1e9});
*/
	print_math_title("Nearby Int");
	RUNTESTS_MATH_FUNCTION(nearbyint, nearbyint, 50, {-1e9,+1e9});
	print_math_title("Next After");
	RUNTESTS_MATH_OPERATOR(nextafter, nextafter, 50, {-1e9,+1e9}, {-1e9,+1e9});
	print_math_title("Copy Sign");
	RUNTESTS_MATH_OPERATOR(copysign, copysign, 50, {-1e9,+1e9}, {-1e9,+1e9});

	print_math_title("Absolute Value");
	RUNTESTS_MATH_FUNCTION(abs, fabs, 500, {-1e1,+1e1});
	RUNTESTS_MATH_FUNCTION(abs, fabs, 500, {-1e9,+1e9});
	print_math_title("Round");
	RUNTESTS_MATH_FUNCTION(round, round, 500, {-1e1,+1e1});
	RUNTESTS_MATH_FUNCTION(round, round, 500, {-1e9,+1e9});
	print_math_title("Trunc");
	RUNTESTS_MATH_FUNCTION(trunc, trunc, 500, {-1e1,+1e1});
	RUNTESTS_MATH_FUNCTION(trunc, trunc, 500, {-1e9,+1e9});
	print_math_title("Floor");
	RUNTESTS_MATH_FUNCTION(floor, floor, 500, {-1e1,+1e1});
	RUNTESTS_MATH_FUNCTION(floor, floor, 500, {-1e9,+1e9});
	print_math_title("Ceil");
	RUNTESTS_MATH_FUNCTION(ceil, ceil, 500, {-1e1,+1e1});
	RUNTESTS_MATH_FUNCTION(ceil, ceil, 500, {-1e9,+1e9});

	print_math_title("Modulo");
	RUNTESTS_MATH_OPERATOR(mod, fmod, 50, {-1e1,+1e1}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(mod, fmod, 50, {-1e9,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(mod, fmod, 50, {-1e1,+1e1}, {-1e9,+1e9});
	RUNTESTS_MATH_OPERATOR(mod, fmod, 50, {-1e9,+1e9}, {-1e9,+1e9});
	print_math_title("Remainder");
	RUNTESTS_MATH_OPERATOR(rem, remainder, 50, {-1e1,+1e1}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(rem, remainder, 50, {-1e9,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(rem, remainder, 50, {-1e1,+1e1}, {-1e9,+1e9});
	RUNTESTS_MATH_OPERATOR(rem, remainder, 50, {-1e9,+1e9}, {-1e9,+1e9});

	print_math_title("Power");
	RUNTESTS_MATH_OPERATOR(pow, pow, 50, { 0e0,+4e0}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(pow, pow, 50, {-1e1,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(pow, pow, 50, { 0e0,+4e0}, {-1e6,+1e6});
	RUNTESTS_MATH_OPERATOR(pow, pow, 50, {-1e1,+1e9}, {-1e6,+1e6});
/*
	print_math_title("N-Power");
	RUNTESTS_MATH_OPERATOR(pow_n, ?, 50, { 0e0,+4e0}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(pow_n, ?, 50, {-1e1,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(pow_n, ?, 50, { 0e0,+4e0}, {-1e6,+1e6});
	RUNTESTS_MATH_OPERATOR(pow_n, ?, 50, {-1e1,+1e9}, {-1e6,+1e6});
*/
	print_math_title("Square root");
	RUNTESTS_MATH_FUNCTION(sqrt, sqrt, 500, { 0e0,+5e0});
	RUNTESTS_MATH_FUNCTION(sqrt, sqrt, 500, {-1e1,+1e9});
	print_math_title("Cubic root");
	RUNTESTS_MATH_FUNCTION(cbrt, cbrt, 500, { 0e0,+5e0});
	RUNTESTS_MATH_FUNCTION(cbrt, cbrt, 500, {-1e9,+1e9});
/*
	print_math_title("N-Power root");
	RUNTESTS_MATH_OPERATOR(nrt, ?, 50, { 0e0,+5e0}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(nrt, ?, 50, {-1e9,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(nrt, ?, 50, { 0e0,+5e0}, {-1e6,+1e6});
	RUNTESTS_MATH_OPERATOR(nrt, ?, 50, {-1e9,+1e9}, {-1e6,+1e6});
*/
	print_math_title("Hypotenuse");
	RUNTESTS_MATH_OPERATOR(hypot, hypot, 50, {-1e1,+1e1}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(hypot, hypot, 50, {-1e9,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(hypot, hypot, 50, {-1e1,+1e1}, {-1e9,+1e9});
	RUNTESTS_MATH_OPERATOR(hypot, hypot, 50, {-1e9,+1e9}, {-1e9,+1e9});

	print_math_title("Exponential, base e");
	RUNTESTS_MATH_FUNCTION(exp, exp, 500, {-1e3,+1e0});
	RUNTESTS_MATH_FUNCTION(exp, exp, 500, {+1e0,+1e3});
	RUNTESTS_MATH_FUNCTION(exp, exp, 500, {+1e0,+1e9});
	print_math_title("Exponential, base 2");
	RUNTESTS_MATH_FUNCTION(exp2, exp2, 500, {-1e3,+1e0});
	RUNTESTS_MATH_FUNCTION(exp2, exp2, 500, {+1e0,+1e3});
	RUNTESTS_MATH_FUNCTION(exp2, exp2, 500, {+1e0,+1e9});
/*
	print_math_title("Exponential, base 10");
	RUNTESTS_MATH_FUNCTION(exp10, exp10, 500, {-1e3,+1e0});
	RUNTESTS_MATH_FUNCTION(exp10, exp10, 500, {+1e0,+1e3});
	RUNTESTS_MATH_FUNCTION(exp10, exp10, 500, {+1e0,+1e9});
*/
	print_math_title("Logarithm, base e");
	RUNTESTS_MATH_FUNCTION(log, log, 500, { 0e0,+1e0});
	RUNTESTS_MATH_FUNCTION(log, log, 500, {+1e0,+1e3});
	RUNTESTS_MATH_FUNCTION(log, log, 500, {+1e0,+1e9});
	print_math_title("Logarithm, base 2");
	RUNTESTS_MATH_FUNCTION(log2, log2, 500, { 0e0,+1e0});
	RUNTESTS_MATH_FUNCTION(log2, log2, 500, {+1e0,+1e3});
	RUNTESTS_MATH_FUNCTION(log2, log2, 500, {+1e0,+1e9});
	print_math_title("Logarithm, base 10");
	RUNTESTS_MATH_FUNCTION(log10, log10, 500, { 0e0,+1e0});
	RUNTESTS_MATH_FUNCTION(log10, log10, 500, {+1e0,+1e3});
	RUNTESTS_MATH_FUNCTION(log10, log10, 500, {+1e0,+1e9});
/*
	print_math_title("Logarithm, base N");
	RUNTESTS_MATH_OPERATOR(log_n, logn, 50, {-1e1,+1e1}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(log_n, logn, 50, {-1e2,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(log_n, logn, 50, {-1e1,+1e1}, {-1e9,+1e9});
	RUNTESTS_MATH_OPERATOR(log_n, logn, 50, {-1e2,+1e9}, {-1e9,+1e9});
*/
	print_math_title("Error function");
	RUNTESTS_MATH_FUNCTION(erf, erf, 500, {-3e0,+3e0});
	RUNTESTS_MATH_FUNCTION(erf, erf, 500, {-1e9,+1e9});
	print_math_title("Error function complementary");
	RUNTESTS_MATH_FUNCTION(erfc, erfc, 500, {-3e0,+3e0});
	RUNTESTS_MATH_FUNCTION(erfc, erfc, 500, {-1e9,+1e9});

	print_math_title("Gamma function");
	RUNTESTS_MATH_FUNCTION(gamma, tgamma, 500, {-1e1,+0e0});
	RUNTESTS_MATH_FUNCTION(gamma, tgamma, 500, {-0e0,+1e1});
	RUNTESTS_MATH_FUNCTION(gamma, tgamma, 500, {-1e9,+1e9});
	print_math_title("Log-Gamma function");
	RUNTESTS_MATH_FUNCTION(lngamma, lgamma, 500, {-1e1,+0e0});
	RUNTESTS_MATH_FUNCTION(lngamma, lgamma, 500, {-0e0,+1e1});
	RUNTESTS_MATH_FUNCTION(lngamma, lgamma, 500, {-1e9,+1e9});

	print_math_title("Sine");
	RUNTESTS_MATH_FUNCTION(sin, sin, 500, { 0, +PI });
	RUNTESTS_MATH_FUNCTION(sin, sin, 500, {-TAU,+TAU*2});
	RUNTESTS_MATH_FUNCTION(sin, sin, 500, {-1e9,+1e9});
	print_math_title("Cosine");
	RUNTESTS_MATH_FUNCTION(cos, cos, 500, {-PI_HALF,+PI_HALF});
	RUNTESTS_MATH_FUNCTION(cos, cos, 500, {-TAU,+TAU*2});
	RUNTESTS_MATH_FUNCTION(cos, cos, 500, {-1e9,+1e9});
	print_math_title("Tangent");
	RUNTESTS_MATH_FUNCTION(tan, tan, 500, {-PI_HALF,+PI_HALF});
	RUNTESTS_MATH_FUNCTION(tan, tan, 500, {-1e9,+1e9});
	print_math_title("Arc-Sine");
	RUNTESTS_MATH_FUNCTION(asin, asin, 500, {-1e0,+1e0});
	RUNTESTS_MATH_FUNCTION(asin, asin, 500, {-1e9,+1e9});
	print_math_title("Arc-Cosine");
	RUNTESTS_MATH_FUNCTION(acos, acos, 500, {-1e0,+1e0});
	RUNTESTS_MATH_FUNCTION(acos, acos, 500, {-1e9,+1e9});
	print_math_title("Arc-Tangent");
	RUNTESTS_MATH_FUNCTION(atan, atan, 500, {-TAU,+TAU});
	RUNTESTS_MATH_FUNCTION(atan, atan, 500, {-1e9,+1e9});

	print_math_title("Arc-Tangent of (Y / X)");
	RUNTESTS_MATH_OPERATOR(atan2, atan2, 50, {-1e1,+1e1}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(atan2, atan2, 50, {-1e9,+1e9}, {-1e1,+1e1});
	RUNTESTS_MATH_OPERATOR(atan2, atan2, 50, {-1e1,+1e1}, {-1e9,+1e9});
	RUNTESTS_MATH_OPERATOR(atan2, atan2, 50, {-1e9,+1e9}, {-1e9,+1e9});

	print_math_title("Hyperbolic Sine");
	RUNTESTS_MATH_FUNCTION(sinh, sinh, 500, {-TAU,+TAU});
	RUNTESTS_MATH_FUNCTION(sinh, sinh, 500, {-1e9,+1e9});
	print_math_title("Hyperbolic Cosine");
	RUNTESTS_MATH_FUNCTION(cosh, cosh, 500, {-TAU,+TAU});
	RUNTESTS_MATH_FUNCTION(cosh, cosh, 500, {-1e9,+1e9});
	print_math_title("Hyperbolic Tangent");
	RUNTESTS_MATH_FUNCTION(tanh, tanh, 500, {-TAU,+TAU});
	RUNTESTS_MATH_FUNCTION(tanh, tanh, 500, {-1e9,+1e9});
	print_math_title("Hyperbolic Arc-Sine");
	RUNTESTS_MATH_FUNCTION(asinh, asinh, 500, {-5e1,+5e1});
	RUNTESTS_MATH_FUNCTION(asinh, asinh, 500, {-1e9,+1e9});
	print_math_title("Hyperbolic Arc-Cosine");
	RUNTESTS_MATH_FUNCTION(acosh, acosh, 500, {+1e0,+5e1});
	RUNTESTS_MATH_FUNCTION(acosh, acosh, 500, {-1e9,+1e9});
	print_math_title("Hyperbolic Arc-Tangent");
	RUNTESTS_MATH_FUNCTION(atanh, atanh, 500, {-1e0,+1e0});
	RUNTESTS_MATH_FUNCTION(atanh, atanh, 500, {-1e9,+1e9});

	return (OK);
}



