
#include <math.h>
#include <time.h>

#include "libccc/sys/io.h"
#include "libccc/math.h"
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



void	print_math_title(char const * title)
{
	if (g_test.config.verbose)
	{
		printf("\n\n" ANSI_COLOR_FG_BLUE "%s" ANSI_RESET "\n", title);
	}
}



#define SF_FORMAT	":\t%s%g"



#define TEST_PERFORM_MATH_REALFUNCTION(CALL, RESULTS, FUNCTION) \
	x = interval.start; \
	timer_clock(&timer.CALL##_start); \
	for (unsigned int i = 0; i < tests; ++i) \
	{ \
		x += step; \
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
			RESULTS[i * tests_interval + j] = FUNCTION(x, y); \
		} \
		y += step_y; \
	} \
	timer_clock(&timer.CALL##_end); \



#define TEST_GET_RESULTS() \
	for (unsigned int i = 0; i < tests; ++i) \
	{ \
		if (expects[i] == results[i] || (isnan(expects[i]) && isnan(results[i]))) \
			errors[i] = 0; \
		else if (isnan(expects[i]) || isnan(results[i])) \
			errors[i] = NAN; \
		else \
			errors[i] = ABS(expects[i] - results[i]); \
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
void	print_test_math_f##BITS(s_timer timer, t_f##BITS* errors, t_f##BITS precision, int amount) \
{ \
	if (g_test.config.verbose) \
	{ \
		quicksort_f##BITS(errors, 0, amount); \
		printf_colored_f##BITS("Largest error", precision, stat_getmax_f##BITS   (errors, amount)); \
		printf_colored_f##BITS("Average error", precision, stat_average_f##BITS  (errors, amount)); \
		printf_colored_f##BITS("Median error",  precision, stat_median_f##BITS   (errors, amount)); \
		printf_colored_f##BITS("Standard dev.", precision, stat_variance_f##BITS (errors, amount)); \
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
	unsigned int failed_tests = 0; \
	s_timer timer = {0}; \
	t_f##BITS	x; \
	t_f##BITS	step = (interval.end - interval.start) / tests; \
	TEST_PERFORM_MATH_REALFUNCTION(result, results, func_libccc) \
	if (func_libc) \
	{ \
		TEST_PERFORM_MATH_REALFUNCTION(expect, expects, func_libc) \
	} \
	TEST_GET_RESULTS() \
	TEST_PRINT_MATH("Ran %d tests on interval [%g,%g], with increment=%g\n", tests, interval.start, interval.end, step) \
	print_test_math_f##BITS(timer, errors, precision, tests); \
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
	TEST_GET_RESULTS() \
	TEST_PRINT_MATH("Ran %d tests with:\n" \
		"arg1: interval [%g,%g], with increment=%g\n" \
		"arg2: interval [%g,%g], with increment=%g\n", \
		tests, \
		interval_x.start, interval_x.end, step_x, \
		interval_y.start, interval_y.end, step_y) \
	print_test_math_f##BITS(timer, errors, precision, tests); \
	free(expects); \
	free(results); \
	free(errors); \
	return (OK); \
} \



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



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math(void)
{
	print_suite_title("libccc/math");

#define TESTSUITE_MATH(STD_SUFFIX, BITS, NAME, TARGET_PRECISION) \
	if (g_test.config.verbose) \
	{ \
		printf("\n\n" ANSI_COLOR_FG_BLUE "Floating-point (%d-bit %s precision) math functions" ANSI_RESET "\n\n", BITS, NAME); \
	} \
/* \
	print_math_title("Split Float (f"#BITS")"); \
	test_math_realfunction_f##BITS("frexp", &frexp##STD_SUFFIX, &c_f##BITS##frexp, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Get Exponent (base-2) (f"#BITS")"); \
	test_math_realfunction_f##BITS("getexp", &ilogb##STD_SUFFIX, &c_f##BITS##getexp2, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
*/ \
	print_math_title("Nearby Int (f"#BITS")"); \
	test_math_realfunction_f##BITS("nearbyint", &nearbyint##STD_SUFFIX, &c_f##BITS##nearbyint, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Next After (f"#BITS")"); \
	test_math_realoperator_f##BITS("nextafter", &nextafter##STD_SUFFIX, &c_f##BITS##nextafter, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Copy Sign (f"#BITS")"); \
	test_math_realoperator_f##BITS("copysign", &copysign##STD_SUFFIX, &c_f##BITS##copysign, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Absolute Value (f"#BITS")"); \
	test_math_realfunction_f##BITS("abs", &fabs##STD_SUFFIX, &c_f##BITS##abs, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realfunction_f##BITS("abs", &fabs##STD_SUFFIX, &c_f##BITS##abs, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Round (f"#BITS")"); \
	test_math_realfunction_f##BITS("round", &round##STD_SUFFIX, &c_f##BITS##round, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realfunction_f##BITS("round", &round##STD_SUFFIX, &c_f##BITS##round, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Trunc (f"#BITS")"); \
	test_math_realfunction_f##BITS("trunc", &trunc##STD_SUFFIX, &c_f##BITS##trunc, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realfunction_f##BITS("trunc", &trunc##STD_SUFFIX, &c_f##BITS##trunc, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Floor (f"#BITS")"); \
	test_math_realfunction_f##BITS("floor", &floor##STD_SUFFIX, &c_f##BITS##floor, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realfunction_f##BITS("floor", &floor##STD_SUFFIX, &c_f##BITS##floor, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Ceil (f"#BITS")"); \
	test_math_realfunction_f##BITS("ceil", &ceil##STD_SUFFIX, &c_f##BITS##ceil, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realfunction_f##BITS("ceil", &ceil##STD_SUFFIX, &c_f##BITS##ceil, TARGET_PRECISION, 10000, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Modulo (f"#BITS")"); \
	test_math_realoperator_f##BITS("mod", &fmod##STD_SUFFIX, &c_f##BITS##mod, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("mod", &fmod##STD_SUFFIX, &c_f##BITS##mod, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("mod", &fmod##STD_SUFFIX, &c_f##BITS##mod, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e9,+1e9}); \
	test_math_realoperator_f##BITS("mod", &fmod##STD_SUFFIX, &c_f##BITS##mod, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Remainder (f"#BITS")"); \
	test_math_realoperator_f##BITS("rem", &remainder##STD_SUFFIX, &c_f##BITS##rem, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("rem", &remainder##STD_SUFFIX, &c_f##BITS##rem, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("rem", &remainder##STD_SUFFIX, &c_f##BITS##rem, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e9,+1e9}); \
	test_math_realoperator_f##BITS("rem", &remainder##STD_SUFFIX, &c_f##BITS##rem, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Power (f"#BITS")"); \
	test_math_realoperator_f##BITS("pow", &pow##STD_SUFFIX, &c_f##BITS##pow, TARGET_PRECISION, 100, (s_f##BITS##_interval){ 0e0,+4e0}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("pow", &pow##STD_SUFFIX, &c_f##BITS##pow, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("pow", &pow##STD_SUFFIX, &c_f##BITS##pow, TARGET_PRECISION, 100, (s_f##BITS##_interval){ 0e0,+4e0}, (s_f##BITS##_interval){-1e6,+1e6}); \
	test_math_realoperator_f##BITS("pow", &pow##STD_SUFFIX, &c_f##BITS##pow, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e9}, (s_f##BITS##_interval){-1e6,+1e6}); \
/* \
	print_math_title("N-Power (f"#BITS")"); \
	test_math_realoperator_f##BITS("pow_n", NULL##STD_SUFFIX, &c_f##BITS##intpow, TARGET_PRECISION, 100, (s_f##BITS##_interval){ 0e0,+4e0}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("pow_n", NULL##STD_SUFFIX, &c_f##BITS##intpow, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("pow_n", NULL##STD_SUFFIX, &c_f##BITS##intpow, TARGET_PRECISION, 100, (s_f##BITS##_interval){ 0e0,+4e0}, (s_f##BITS##_interval){-1e6,+1e6}); \
	test_math_realoperator_f##BITS("pow_n", NULL##STD_SUFFIX, &c_f##BITS##intpow, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e9}, (s_f##BITS##_interval){-1e6,+1e6}); \
*/ \
	print_math_title("Square root (f"#BITS")"); \
	test_math_realfunction_f##BITS("sqrt", &sqrt##STD_SUFFIX, &c_f##BITS##sqrt, TARGET_PRECISION, 1000, (s_f##BITS##_interval){ 0e0,+5e0}); \
	test_math_realfunction_f##BITS("sqrt", &sqrt##STD_SUFFIX, &c_f##BITS##sqrt, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e1,+1e9}); \
	print_math_title("Cubic root (f"#BITS")"); \
	test_math_realfunction_f##BITS("cbrt", &cbrt##STD_SUFFIX, &c_f##BITS##cbrt, TARGET_PRECISION, 1000, (s_f##BITS##_interval){ 0e0,+5e0}); \
	test_math_realfunction_f##BITS("cbrt", &cbrt##STD_SUFFIX, &c_f##BITS##cbrt, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
/* \
	print_math_title("N-Power root (f"#BITS")"); \
	test_math_realoperator_f##BITS("nrt", NULL##STD_SUFFIX, &c_f##BITS##nrt, TARGET_PRECISION, 100, (s_f##BITS##_interval){ 0e0,+5e0}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("nrt", NULL##STD_SUFFIX, &c_f##BITS##nrt, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("nrt", NULL##STD_SUFFIX, &c_f##BITS##nrt, TARGET_PRECISION, 100, (s_f##BITS##_interval){ 0e0,+5e0}, (s_f##BITS##_interval){-1e6,+1e6}); \
	test_math_realoperator_f##BITS("nrt", NULL##STD_SUFFIX, &c_f##BITS##nrt, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e6,+1e6}); \
*/ \
	print_math_title("Hypotenuse (f"#BITS")"); \
	test_math_realoperator_f##BITS("hypot", &hypot##STD_SUFFIX, &c_f##BITS##hypot, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("hypot", &hypot##STD_SUFFIX, &c_f##BITS##hypot, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("hypot", &hypot##STD_SUFFIX, &c_f##BITS##hypot, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e9,+1e9}); \
	test_math_realoperator_f##BITS("hypot", &hypot##STD_SUFFIX, &c_f##BITS##hypot, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Exponential, base e (f"#BITS")"); \
	test_math_realfunction_f##BITS("exp", &exp##STD_SUFFIX, &c_f##BITS##exp, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e3,+1e0}); \
	test_math_realfunction_f##BITS("exp", &exp##STD_SUFFIX, &c_f##BITS##exp, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+1e9}); \
	print_math_title("Exponential, base 2 (f"#BITS")"); \
	test_math_realfunction_f##BITS("exp2", &exp2##STD_SUFFIX, &c_f##BITS##exp2, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e3,+1e0}); \
	test_math_realfunction_f##BITS("exp2", &exp2##STD_SUFFIX, &c_f##BITS##exp2, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+1e9}); \
/* \
	print_math_title("Exponential, base 10 (f"#BITS")"); \
	test_math_realfunction_f##BITS("exp10", &exp10##STD_SUFFIX, &c_f##BITS##exp10, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e3,+1e0}); \
	test_math_realfunction_f##BITS("exp10", &exp10##STD_SUFFIX, &c_f##BITS##exp10, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+1e9}); \
*/ \
	print_math_title("Logarithm, base e (f"#BITS")"); \
	test_math_realfunction_f##BITS("log", &log##STD_SUFFIX, &c_f##BITS##ln, TARGET_PRECISION, 1000, (s_f##BITS##_interval){ 0e0,+1e0}); \
	test_math_realfunction_f##BITS("log", &log##STD_SUFFIX, &c_f##BITS##ln, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+1e9}); \
	print_math_title("Logarithm, base 2 (f"#BITS")"); \
	test_math_realfunction_f##BITS("log2", &log2##STD_SUFFIX, &c_f##BITS##log2, TARGET_PRECISION, 1000, (s_f##BITS##_interval){ 0e0,+1e0}); \
	test_math_realfunction_f##BITS("log2", &log2##STD_SUFFIX, &c_f##BITS##log2, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+1e9}); \
	print_math_title("Logarithm, base 10 (f"#BITS")"); \
	test_math_realfunction_f##BITS("log10", &log10##STD_SUFFIX, &c_f##BITS##log10, TARGET_PRECISION, 1000, (s_f##BITS##_interval){ 0e0,+1e0}); \
	test_math_realfunction_f##BITS("log10", &log10##STD_SUFFIX, &c_f##BITS##log10, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+1e9}); \
/* \
	print_math_title("Logarithm, base N (f"#BITS")"); \
	test_math_realoperator_f##BITS("log_n", &logn##STD_SUFFIX, &c_f##BITS##logn, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("log_n", &logn##STD_SUFFIX, &c_f##BITS##logn, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e2,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("log_n", &logn##STD_SUFFIX, &c_f##BITS##logn, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e9,+1e9}); \
	test_math_realoperator_f##BITS("log_n", &logn##STD_SUFFIX, &c_f##BITS##logn, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e2,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
*/ \
	print_math_title("Error function (f"#BITS")"); \
	test_math_realfunction_f##BITS("erf", &erf##STD_SUFFIX, &c_f##BITS##erf, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-3e0,+3e0}); \
	test_math_realfunction_f##BITS("erf", &erf##STD_SUFFIX, &c_f##BITS##erf, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Error function complementary (f"#BITS")"); \
	test_math_realfunction_f##BITS("erfc", &erfc##STD_SUFFIX, &c_f##BITS##erfc, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-3e0,+3e0}); \
	test_math_realfunction_f##BITS("erfc", &erfc##STD_SUFFIX, &c_f##BITS##erfc, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Gamma function (f"#BITS")"); \
	test_math_realfunction_f##BITS("gamma", &tgamma##STD_SUFFIX, &c_f##BITS##gamma, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-5e0,+5e0}); \
	test_math_realfunction_f##BITS("gamma", &tgamma##STD_SUFFIX, &c_f##BITS##gamma, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Log-Gamma function (f"#BITS")"); \
	test_math_realfunction_f##BITS("lngamma", &lgamma##STD_SUFFIX, &c_f##BITS##lngamma, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-5e0,+5e0}); \
	test_math_realfunction_f##BITS("lngamma", &lgamma##STD_SUFFIX, &c_f##BITS##lngamma, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Sine (f"#BITS")"); \
	test_math_realfunction_f##BITS("sin", &sin##STD_SUFFIX, &c_f##BITS##sin, TARGET_PRECISION, 1000, (s_f##BITS##_interval){ 0, +PI }); \
	test_math_realfunction_f##BITS("sin", &sin##STD_SUFFIX, &c_f##BITS##sin, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-TAU,+TAU*2}); \
	test_math_realfunction_f##BITS("sin", &sin##STD_SUFFIX, &c_f##BITS##sin, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Cosine (f"#BITS")"); \
	test_math_realfunction_f##BITS("cos", &cos##STD_SUFFIX, &c_f##BITS##cos, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-PI_HALF,+PI_HALF}); \
	test_math_realfunction_f##BITS("cos", &cos##STD_SUFFIX, &c_f##BITS##cos, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-TAU,+TAU*2}); \
	test_math_realfunction_f##BITS("cos", &cos##STD_SUFFIX, &c_f##BITS##cos, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Tangent (f"#BITS")"); \
	test_math_realfunction_f##BITS("tan", &tan##STD_SUFFIX, &c_f##BITS##tan, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-PI_HALF,+PI_HALF}); \
	test_math_realfunction_f##BITS("tan", &tan##STD_SUFFIX, &c_f##BITS##tan, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Arc-Sine (f"#BITS")"); \
	test_math_realfunction_f##BITS("asin", &asin##STD_SUFFIX, &c_f##BITS##asin, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e0,+1e0}); \
	test_math_realfunction_f##BITS("asin", &asin##STD_SUFFIX, &c_f##BITS##asin, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Arc-Cosine (f"#BITS")"); \
	test_math_realfunction_f##BITS("acos", &acos##STD_SUFFIX, &c_f##BITS##acos, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e0,+1e0}); \
	test_math_realfunction_f##BITS("acos", &acos##STD_SUFFIX, &c_f##BITS##acos, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Arc-Tangent (f"#BITS")"); \
	test_math_realfunction_f##BITS("atan", &atan##STD_SUFFIX, &c_f##BITS##atan, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-TAU,+TAU}); \
	test_math_realfunction_f##BITS("atan", &atan##STD_SUFFIX, &c_f##BITS##atan, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Arc-Tangent of (Y / X) (f"#BITS")"); \
	test_math_realoperator_f##BITS("atan2", &atan2##STD_SUFFIX, &c_f##BITS##atan2, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("atan2", &atan2##STD_SUFFIX, &c_f##BITS##atan2, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e1,+1e1}); \
	test_math_realoperator_f##BITS("atan2", &atan2##STD_SUFFIX, &c_f##BITS##atan2, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e1,+1e1}, (s_f##BITS##_interval){-1e9,+1e9}); \
	test_math_realoperator_f##BITS("atan2", &atan2##STD_SUFFIX, &c_f##BITS##atan2, TARGET_PRECISION, 100, (s_f##BITS##_interval){-1e9,+1e9}, (s_f##BITS##_interval){-1e9,+1e9}); \
 \
	print_math_title("Hyperbolic Sine (f"#BITS")"); \
	test_math_realfunction_f##BITS("sinh", &sinh##STD_SUFFIX, &c_f##BITS##sinh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-TAU,+TAU}); \
	test_math_realfunction_f##BITS("sinh", &sinh##STD_SUFFIX, &c_f##BITS##sinh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Hyperbolic Cosine (f"#BITS")"); \
	test_math_realfunction_f##BITS("cosh", &cosh##STD_SUFFIX, &c_f##BITS##cosh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-TAU,+TAU}); \
	test_math_realfunction_f##BITS("cosh", &cosh##STD_SUFFIX, &c_f##BITS##cosh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Hyperbolic Tangent (f"#BITS")"); \
	test_math_realfunction_f##BITS("tanh", &tanh##STD_SUFFIX, &c_f##BITS##tanh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-TAU,+TAU}); \
	test_math_realfunction_f##BITS("tanh", &tanh##STD_SUFFIX, &c_f##BITS##tanh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Hyperbolic Arc-Sine (f"#BITS")"); \
	test_math_realfunction_f##BITS("asinh", &asinh##STD_SUFFIX, &c_f##BITS##asinh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-5e1,+5e1}); \
	test_math_realfunction_f##BITS("asinh", &asinh##STD_SUFFIX, &c_f##BITS##asinh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Hyperbolic Arc-Cosine (f"#BITS")"); \
	test_math_realfunction_f##BITS("acosh", &acosh##STD_SUFFIX, &c_f##BITS##acosh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){+1e0,+5e1}); \
	test_math_realfunction_f##BITS("acosh", &acosh##STD_SUFFIX, &c_f##BITS##acosh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \
	print_math_title("Hyperbolic Arc-Tangent (f"#BITS")"); \
	test_math_realfunction_f##BITS("atanh", &atanh##STD_SUFFIX, &c_f##BITS##atanh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e0,+1e0}); \
	test_math_realfunction_f##BITS("atanh", &atanh##STD_SUFFIX, &c_f##BITS##atanh, TARGET_PRECISION, 1000, (s_f##BITS##_interval){-1e9,+1e9}); \



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

	return (OK);
}



