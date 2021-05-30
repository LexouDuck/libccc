
#include <math.h>
#include <time.h>

#include "libccc/sys/io.h"
#include "libccc/math/math.h"
#include "libccc/math/algebra.h"
#include "libccc/math/stat.h"
#define T			t_float
#define T_NAME		_float
#define T_DEFAULT	0.
#include "libccc/monad/array.c"

#include "test.h"



void	print_math_foreword(void)
{
	if (g_test.flags.verbose)
	{
		printf("\n\n"C_BLUE"Floating-point (%d-bit %s precision) math functions"C_RESET"\n\n",
#if LIBCONFIG_BITS_FLOAT == 32
			32, "IEEE single");
#endif
#if LIBCONFIG_BITS_FLOAT == 64
			64, "IEEE double");
#endif
#if LIBCONFIG_BITS_FLOAT == 80
			80, "x86 extended");
#endif
#if LIBCONFIG_BITS_FLOAT == 128
			128, "IEEE quadruple");
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



#define SF_FORMAT	":\t%s%g"
static inline void printf_colored(const char* label, t_float precision, t_float value)
{
	printf("%s", label);
	if (precision == 0.)
	{
		if (value == 0. || IS_NAN(value))
			printf(SF_FORMAT"\n", "", value);
		else if (value < 0)
			printf(SF_FORMAT"\n"C_RESET, C_RED, value);
		else if (value > 0)
			printf(SF_FORMAT"\n"C_RESET, C_GREEN, value);
	}
	else
	{
		if (value < precision)
			printf(SF_FORMAT"\n"C_RESET, C_GREEN, value);
		else
			printf(SF_FORMAT"\n"C_RESET, C_RED, value);
	}
}



static t_float	c_get_largest_f(s_array_float values)
{
	t_float result = 0.;
	for (t_u32 i = 0; i < values.length; ++i)
	{
		if (result < values.items[i])
			result = values.items[i];
		if (IS_NAN(values.items[i]))
			result = NAN;
	}
	return (result);
}



#define TEST_INIT_MATH() \
	s_timer			timer = {0};		\
	int				failed_tests = 0;	\

#define TEST_INIT_MATH_REALFUNCTION() \
	TEST_INIT_MATH()										\
	t_float			expects[tests];							\
	t_float			results[tests];							\
	s_array_float	errors = c_stat_new_flst(tests);		\
	t_float	x;												\
	t_float	step = (interval.end - interval.start) / tests;	\

#define TEST_INIT_MATH_REALOPERATOR() \
	TEST_INIT_MATH()														\
	int tests_interval = tests;												\
	tests *= tests;															\
	t_float			expects[tests];											\
	t_float			results[tests];											\
	s_array_float	errors = c_stat_new_flst(tests);						\
	t_float	x;																\
	t_float	y;																\
	t_float	step_x = (interval_x.end - interval_x.start) / tests_interval;	\
	t_float	step_y = (interval_y.end - interval_y.start) / tests_interval;	\
	



#define TEST_PERFORM_MATH_REALFUNCTION(CALL, RESULTS, FUNCTION) \
	x = interval.start;					\
	timer_clock(&timer.CALL##_start);	\
	for (int i = 0; i < tests; ++i)		\
	{									\
		x += step;						\
		RESULTS[i] = FUNCTION(x);		\
	}									\
	timer_clock(&timer.CALL##_end);		\

#define TEST_PERFORM_MATH_REALOPERATOR(CALL, RESULTS, FUNCTION) \
	x = interval_x.start;										\
	y = interval_y.start;										\
	timer_clock(&timer.CALL##_start);							\
	for (int i = 0; i < tests_interval; ++i)					\
	{															\
		for (int j = 0; j < tests_interval; ++j)				\
		{														\
			x += step_x;										\
			RESULTS[i * tests_interval + j] = FUNCTION(x, y);	\
		}														\
		y += step_y;											\
	}															\
	timer_clock(&timer.CALL##_end);								\



#define TEST_GET_RESULTS() \
	for (int i = 0; i < tests; ++i)																				\
	{																											\
		if (expects[i] == results[i] || (IS_NAN(expects[i]) && IS_NAN(results[i])))								\
			errors.items[i] = 0;																				\
		else if (IS_NAN(expects[i]) || IS_NAN(results[i]))														\
			errors.items[i] = NAN;																			\
		else																									\
			errors.items[i] = c_distance_float(expects[i], results[i]);										\
		if (IS_NAN(errors.items[i]) || errors.items[i] > fabs(precision * expects[i]))					\
		{																										\
			++failed_tests;																						\
			if (g_test.flags.verbose && g_test.flags.show_args && precision < fabs(results[i] - expects[i]))	\
			{																									\
				printf("TEST N°%d: -> returned %g but libc returned %g (difference is "C_RED"%g"C_RESET")\n",	\
					i, results[i], expects[i], errors.items[i]);												\
			}																									\
		}																										\
	}																											\



#define TEST_PRINT_MATH(FORMAT, ...) \
	g_test.totals.tests += tests;								\
	g_test.totals.failed += failed_tests;						\
	t_float percent = (tests - failed_tests) * 100. / tests;	\
	if (g_test.flags.verbose || percent < 90.)					\
	{															\
		printf("\n%s\n", func_name);							\
		printf(FORMAT, __VA_ARGS__);							\
		printf("Success rate for %g precision: ", precision);	\
		print_percent(percent);									\
	}															\

static void	print_test_math(s_timer timer, s_array_float errors, t_float precision)
{
	if (g_test.flags.verbose)
	{
		c_stat_quicksort_f(errors);
		printf_colored("Largest error",			precision, c_get_largest_f(errors));
		printf_colored("Average error",			precision, c_stat_average_f(errors));
		printf_colored("Median error",			precision, c_stat_median_f(errors));
		printf_colored("Standard deviation",	precision, sqrt(c_stat_variance_f(errors)));
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
	c_stat_free_flst(&errors);
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
	TEST_INIT_MATH_REALFUNCTION()
	TEST_PERFORM_MATH_REALFUNCTION(result, results, func_libccc)
	if (func_libc)
	{
		TEST_PERFORM_MATH_REALFUNCTION(expect, expects, func_libc)
	}
	TEST_GET_RESULTS()
	TEST_PRINT_MATH("Ran %d tests on interval [%g,%g], with increment=%g\n", tests, interval.start, interval.end, step)
	print_test_math(timer, errors, precision);
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
	TEST_INIT_MATH_REALOPERATOR()
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
	print_test_math(timer, errors, precision);
	return (OK);
}

//	#define _f(x)	f(x)
#if LIBCONFIG_BITS_FLOAT == 32
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

#if LIBCONFIG_BITS_FLOAT == 64
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

#if LIBCONFIG_BITS_FLOAT == 80
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

#if LIBCONFIG_BITS_FLOAT == 128
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



/*
** ************************************************************************** *|
**                            Test Suite Function                             *|
** ************************************************************************** *|
*/

int		testsuite_math(void)
{
	print_suite_title("libccc/math");

	print_math_foreword();



	// TODO test getexp()

	print_math_title("Absolute Value");
	test_math_realfunction_libc("fabs", &_fabs, &c_fabs, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("fabs", &_fabs, &c_fabs, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Modulo");
	test_math_realoperator_libc("fmod", &_fmod, &c_fmod, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-10, 10});
	test_math_realoperator_libc("fmod", &_fmod, &c_fmod, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-10, 10});
	test_math_realoperator_libc("fmod", &_fmod, &c_fmod, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-1e9, 1e9});
	test_math_realoperator_libc("fmod", &_fmod, &c_fmod, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-1e9, 1e9});



//	TODO
//	print_math_title("Round");
//	test_math_realfunction_libc("round", &_round, &c_round, 0.0001, 1000, (s_interval){-10, 10});
//	test_math_realfunction_libc("round", &_round, &c_round, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Truncate");
	test_math_realfunction_libc("trunc", &_trunc, &c_ftrunc, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("trunc", &_trunc, &c_ftrunc, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Floor");
	test_math_realfunction_libc("floor", &_floor, &c_ffloor, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("floor", &_floor, &c_ffloor, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Ceiling");
	test_math_realfunction_libc("ceil", &_ceil, &c_fceil, 0.0001, 1000, (s_interval){-10, 10});
	test_math_realfunction_libc("ceil", &_ceil, &c_fceil, 0.0001, 1000, (s_interval){-1e9, 1e9});



	print_math_title("Power");
	test_math_realoperator_libc("pow", &_pow, &c_fpow, 0.0001, 100, (s_interval){0, 4},		(s_interval){-10, 10});
	test_math_realoperator_libc("pow", &_pow, &c_fpow, 0.0001, 100, (s_interval){-100, 1e9},(s_interval){-10, 10});
	test_math_realoperator_libc("pow", &_pow, &c_fpow, 0.0001, 100, (s_interval){0, 4},		(s_interval){-1e6, 1e6});
	test_math_realoperator_libc("pow", &_pow, &c_fpow, 0.0001, 100, (s_interval){-100, 1e9},(s_interval){-1e6, 1e6});

//	TODO
//	print_math_title("N-Power");
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, 0.0001, 100, (s_interval){0, 4},		(s_interval){-10, 10});
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-10, 10});
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, 0.0001, 100, (s_interval){0, 4},		(s_interval){-1e6, 1e6});
//	test_math_realoperator_libc("pow_n", NULL, &c_fintpow, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-1e6, 1e6});



	print_math_title("Square root");
	test_math_realfunction_libc("sqrt", &_sqrt, &c_fsqrt, 0.0001, 1000, (s_interval){0., 5.});
	test_math_realfunction_libc("sqrt", &_sqrt, &c_fsqrt, 0.0001, 1000, (s_interval){-100., 1e9});

	print_math_title("Cubic root");
	test_math_realfunction_libc("cbrt", &_cbrt, &c_fcbrt, 0.0001, 1000, (s_interval){0., 5.});
	test_math_realfunction_libc("cbrt", &_cbrt, &c_fcbrt, 0.0001, 1000, (s_interval){-1e9, 1e9});

//	TODO
//	print_math_title("N-Power root");
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, 0.0001, 100, (s_interval){0, 5},		(s_interval){-10, 10});
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-10, 10});
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, 0.0001, 100, (s_interval){0, 5},		(s_interval){-1e6, 1e6});
//	test_math_realoperator_libc("nrt", NULL, &c_nrt, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-1e6, 1e6});



	print_math_title("Exponential");
	test_math_realfunction_libc("exp", &_exp, &c_fexp, 0.0001, 1000, (s_interval){-1000., 1.});
	test_math_realfunction_libc("exp", &_exp, &c_fexp, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Natural Logarithm");
	test_math_realfunction_libc("ln", &_ln, &c_fln, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("ln", &_ln, &c_fln, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Logarithm, base 2");
	test_math_realfunction_libc("lg", &_lg, &c_flog2, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("lg", &_lg, &c_flog2, 0.0001, 1000, (s_interval){1., 1e9});

	print_math_title("Logarithm, base 10");
	test_math_realfunction_libc("log", &_log, &c_flog10, 0.0001, 1000, (s_interval){0., 1.});
	test_math_realfunction_libc("log", &_log, &c_flog10, 0.0001, 1000, (s_interval){1., 1e9});

//	TODO
//	print_math_title("Logarithm, base N");
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-10, 10});
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-10, 10});
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-1e9, 1e9});
//	test_math_realoperator_libc("log_n", NULL, &c_flogn, 0.0001, 100, (s_interval){-100, 1e9},	(s_interval){-1e9, 1e9});



	print_math_title("Cosine");
	test_math_realfunction_libc("cos", &_cos, &c_fcos, 0.0001, 1000, (s_interval){-TAU, 2 * TAU});
	test_math_realfunction_libc("cos", &_cos, &c_fcos, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Sine");
	test_math_realfunction_libc("sin", &_sin, &c_fsin, 0.0001, 1000, (s_interval){-TAU, 2 * TAU});
	test_math_realfunction_libc("sin", &_sin, &c_fsin, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Tangent");
	test_math_realfunction_libc("tan", &_tan, &c_ftan, 0.0001, 1000, (s_interval){-HALF_PI, HALF_PI});
	test_math_realfunction_libc("tan", &_tan, &c_ftan, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Cosine");
	test_math_realfunction_libc("acos", &_acos, &c_facos, 0.0001, 1000, (s_interval){-1, 1});
	test_math_realfunction_libc("acos", &_acos, &c_facos, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Sine");
	test_math_realfunction_libc("asin", &_asin, &c_fasin, 0.0001, 1000, (s_interval){-1, 1});
	test_math_realfunction_libc("asin", &_asin, &c_fasin, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Arc-Tangent");
	test_math_realfunction_libc("atan", &_atan, &c_fatan, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("atan", &_atan, &c_fatan, 0.0001, 1000, (s_interval){-1e9, 1e9});



	print_math_title("Arc-Tangent of (Y / X)");
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-10, 10});
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-10, 10});
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, 0.0001, 100, (s_interval){-10, 10},	(s_interval){-1e9, 1e9});
	test_math_realoperator_libc("atan2", &_atan2, &c_fatan2, 0.0001, 100, (s_interval){-1e9, 1e9},	(s_interval){-1e9, 1e9});



	print_math_title("Hyperbolic Cosine");
	test_math_realfunction_libc("cosh", &_cosh, &c_fcosh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("cosh", &_cosh, &c_fcosh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Sine");
	test_math_realfunction_libc("sinh", &_sinh, &c_fsinh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("sinh", &_sinh, &c_fsinh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Tangent");
	test_math_realfunction_libc("tanh", &_tanh, &c_ftanh, 0.0001, 1000, (s_interval){-TAU, TAU});
	test_math_realfunction_libc("tanh", &_tanh, &c_ftanh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Cosine");
	test_math_realfunction_libc("acosh", &_acosh, &c_facosh, 0.0001, 1000, (s_interval){1., 50.});
	test_math_realfunction_libc("acosh", &_acosh, &c_facosh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Sine");
	test_math_realfunction_libc("asinh", &_asinh, &c_fasinh, 0.0001, 1000, (s_interval){-50., 50.});
	test_math_realfunction_libc("asinh", &_asinh, &c_fasinh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	print_math_title("Hyperbolic Arc-Tangent");
	test_math_realfunction_libc("atanh", &_atanh, &c_fatanh, 0.0001, 1000, (s_interval){-1., 1.});
	test_math_realfunction_libc("atanh", &_atanh, &c_fatanh, 0.0001, 1000, (s_interval){-1e9, 1e9});

	return (OK);
}
