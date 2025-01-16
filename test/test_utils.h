
#ifndef LIBCCCTEST_UTILS_H_
#define LIBCCCTEST_UTILS_H_

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/

#include <stdbool.h>
#ifndef __cplusplus
#ifndef bool
#define bool	_Bool
#endif
#endif

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/text/char_ascii.h"
#include "libccc/text/char_unicode.h"
#include "libccc/sys/time.h"
#include "libccc/math/stat.h"

typedef struct array_int	s_array_int;	//!< @see "libccc/monad/array.h"
typedef struct  list_int	s_list_int;	//!< @see "libccc/monad/list.h"

#include "test_catch.h"
#include "test_timer.h"
#include "test_print.h"



/*============================================================================*\
||                                   Defines                                  ||
\*============================================================================*/



/*============================================================================*\
||                              Utility Functions                             ||
\*============================================================================*/

int		bool_equals(int a, int b);
int		str_equals(char const* str1, char const* str2);
int		ptrarr_equals(void const** ptr1, void const** ptr2);
int		strarr_equals(char const** strarr1, char const** strarr2);
int		str_equals_until(char const* str1, char const* str2, char c);

char*	strtoescape(char const* str);
char*	strsurround(char const* str, char begin, char end);
char*	print_memory(void const* ptr, t_size length);

char*	ptrtostr(void const* ptr);

s_sorted_sint	print_test_random(int samples);



#define DECLARE_NUMBER_UTILITY_FUNCTIONS(TYPE, NAME) \
char*	NAME##tostr(TYPE number); \
void	quicksort_##NAME(TYPE * array, unsigned int start, unsigned int end); \
TYPE	stat_getmin_                     ##NAME(const TYPE * values, unsigned int length); \
TYPE	stat_getmax_                     ##NAME(const TYPE * values, unsigned int length); \
double*	stat_quantiles_                  ##NAME(const TYPE * values, unsigned int length, unsigned int n); \
double	stat_median_                     ##NAME(const TYPE * values, unsigned int length); \
double	stat_mode_                       ##NAME(const TYPE * values, unsigned int length); \
double	stat_range_                      ##NAME(const TYPE * values, unsigned int length); \
double	stat_midrange_                   ##NAME(const TYPE * values, unsigned int length); \
double	stat_midhinge_                   ##NAME(const TYPE * values, unsigned int length); \
double	stat_trimean_                    ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_arithmetic_            ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_geometric_             ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_harmonic_              ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_contraharmonic_        ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_lehmer_                ##NAME(const TYPE * values, unsigned int length, int power); \
double	stat_mean_interquartile_         ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_quadratic_             ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_cubic_                 ##NAME(const TYPE * values, unsigned int length); \
double	stat_mean_power_                 ##NAME(const TYPE * values, unsigned int length, double power); \
double	stat_variance_                   ##NAME(const TYPE * values, unsigned int length); \
double	stat_stddev_                     ##NAME(const TYPE * values, unsigned int length); \
double	stat_cv_                         ##NAME(const TYPE * values, unsigned int length); \
double	stat_iqr_                        ##NAME(const TYPE * values, unsigned int length); \
double	stat_mad_                        ##NAME(const TYPE * values, unsigned int length); \
double	stat_aad_                        ##NAME(const TYPE * values, unsigned int length, TYPE center); \
double	stat_agm_                        ##NAME(TYPE x, TYPE y); \
double	stat_msd_                        ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mse_                        ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mae_                        ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_md_                         ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_rmd_                        ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_rmsd_                       ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mpe_                        ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mape_                       ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_mspe_                       ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
double	stat_rss_                        ##NAME(const TYPE * values, const TYPE * expect, unsigned int length); \
/*
double	stat_moving_average_simple_      ##NAME(const TYPE * values, unsigned int length); \
double	stat_moving_average_cumulative_  ##NAME(const TYPE * values, unsigned int length); \
double	stat_moving_average_weighted_    ##NAME(const TYPE * values, unsigned int length); \
*/

DECLARE_NUMBER_UTILITY_FUNCTIONS(t_uint  , uint)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u8    , u8)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u16   , u16)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u32   , u32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u64   , u64)
#if LIBCONFIG_USE_INT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_u128  , u128)
#endif
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_sint  , sint)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s8    , s8)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s16   , s16)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s32   , s32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s64   , s64)
#if LIBCONFIG_USE_INT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_s128  , s128)
#endif
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_fixed , fixed)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q16   , q16)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q32   , q32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q64   , q64)
#if LIBCONFIG_USE_INT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_q128  , q128)
#endif
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_float , float)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f32   , f32)
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f64   , f64)
#if LIBCONFIG_USE_FLOAT80
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f80   , f80)
#endif
#if LIBCONFIG_USE_FLOAT128
DECLARE_NUMBER_UTILITY_FUNCTIONS(t_f128  , f128)
#endif



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/

#define DEFINEFUNC_PRINT_TEST(NAME, TYPE) \
typedef struct test_##NAME \
{ \
	char const*	name;		/*!< the name of this unit test */\
	char const*	function;	/*!< the name of the function tested */\
	t_testflags	flags;		/*!< the various test bitflags, see #t_testflags */\
	TYPE		result;		/*!< the result of the tested function */\
	e_signal	result_sig;	/*!< the signal emitted by the tested function, if any */\
	TYPE		expect;		/*!< the result which is expected to pass this test */\
	e_signal	expect_sig;	/*!< the signal emitted by the expect function, if any */\
	size_t		length;		/*!< used by certain types, notably 'mem'(`void*`) and 'list'(`s_list*`) */\
	s_timer		timer;		/*!< the execution performance timer for this test */\
}			s_test_##NAME; \
void	print_test_##NAME(s_test_##NAME* test, char const* args);

DEFINEFUNC_PRINT_TEST(enum,		int)

DEFINEFUNC_PRINT_TEST(bool,		t_bool)

DEFINEFUNC_PRINT_TEST(char,		t_char)
DEFINEFUNC_PRINT_TEST(utf8,		t_utf8)
DEFINEFUNC_PRINT_TEST(utf16,	t_utf16)
DEFINEFUNC_PRINT_TEST(utf32,	t_utf32)

DEFINEFUNC_PRINT_TEST(sint,		t_sint)
DEFINEFUNC_PRINT_TEST(s8,		t_s8)
DEFINEFUNC_PRINT_TEST(s16,		t_s16)
DEFINEFUNC_PRINT_TEST(s32,		t_s32)
DEFINEFUNC_PRINT_TEST(s64,		t_s64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_PRINT_TEST(s128,		t_s128)
#endif

DEFINEFUNC_PRINT_TEST(uint,		t_uint)
DEFINEFUNC_PRINT_TEST(u8,		t_u8)
DEFINEFUNC_PRINT_TEST(u16,		t_u16)
DEFINEFUNC_PRINT_TEST(u32,		t_u32)
DEFINEFUNC_PRINT_TEST(u64,		t_u64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_PRINT_TEST(u128,		t_u128)
#endif

DEFINEFUNC_PRINT_TEST(fixed,	t_fixed)
DEFINEFUNC_PRINT_TEST(q16,		t_q16)
DEFINEFUNC_PRINT_TEST(q32,		t_q32)
DEFINEFUNC_PRINT_TEST(q64,		t_q64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_PRINT_TEST(q128,		t_q128)
#endif

DEFINEFUNC_PRINT_TEST(float,	t_float)
DEFINEFUNC_PRINT_TEST(f32,		t_f32)
DEFINEFUNC_PRINT_TEST(f64,		t_f64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_PRINT_TEST(f80,		t_f80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_PRINT_TEST(f128,		t_f128)
#endif

DEFINEFUNC_PRINT_TEST(size,		t_size)
DEFINEFUNC_PRINT_TEST(ptrdiff,	t_ptrdiff)
DEFINEFUNC_PRINT_TEST(sintptr,	t_sintptr)
DEFINEFUNC_PRINT_TEST(uintptr,	t_uintptr)
DEFINEFUNC_PRINT_TEST(sintmax,	t_sintmax)
DEFINEFUNC_PRINT_TEST(uintmax,	t_uintmax)

DEFINEFUNC_PRINT_TEST(mem,		void const*)
DEFINEFUNC_PRINT_TEST(ptr,		void const*)
DEFINEFUNC_PRINT_TEST(ptrarr,	void**)
DEFINEFUNC_PRINT_TEST(str,		char const*)
DEFINEFUNC_PRINT_TEST(strarr,	char**)

DEFINEFUNC_PRINT_TEST(array,	s_array_int const*)
DEFINEFUNC_PRINT_TEST(list,		s_list_int const*)

DEFINEFUNC_PRINT_TEST(date,		s_date)

DEFINEFUNC_PRINT_TEST(sign,		t_sintmax)
DEFINEFUNC_PRINT_TEST(alloc,	void*)


/*============================================================================*\
||                               Testing Macros                               ||
\*============================================================================*/

/*
**	The following macros are used for tests, to avoid boilerplate and code repetition.
*/

/*!
**	Initialization logic for any test
*/
#define TEST_INIT(TYPENAME) \
	char*	args = NULL; \
	int		len = 0; \
	s_test_##TYPENAME test = (s_test_##TYPENAME) \
	{ \
		.name = test_name, \
		.flags = flags, \
	}; \
	if (!g_test.config.test_nullptrs && \
		(flags & FLAG_SIGSEGV)) \
		return; \



/*!
**	This macro performs a test (with segfault handling and execution timer) for the given void-returning function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	KIND		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	RESULT		The name of the result variable to assign to (if segfault occurs)
**	@param	FUNCTION	The name of the function to test
**	@param	...			Variadic arguments are passed to FUNCTION
*/
#define TEST_PERFORM_VOID_(KIND, RESULT, FUNCTION, ...) \
	_TRY \
	{ \
		timer_clock(&test.timer.KIND##_start); \
		FUNCTION(__VA_ARGS__); \
		test.KIND = RESULT; \
		timer_clock(&test.timer.KIND##_end); \
	} \
	_CATCH \
	{ \
		test.KIND##_sig = sig; \
	} \
	_END \

//! Use this for void-return functions
#define TEST_PERFORM_VOID(RESULT, FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, RESULT, c_##FUNCTION, ##__VA_ARGS__) \
	test.expect = expecting; \

//! Use this for void-return functions, which use a 'dest' argument
#define TEST_PERFORM_VOID_DEST(FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, dest_libccc, c_##FUNCTION, dest_libccc, ##__VA_ARGS__) \
	test.expect = expecting; \

//! Use this for void-return functions that exist in libc
#define TEST_PERFORM_VOID_LIBC(RESULT, FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, RESULT, c_##FUNCTION, ##__VA_ARGS__) \
	TEST_PERFORM_VOID_(expect, RESULT,     FUNCTION, ##__VA_ARGS__) \

//! Use this for void-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_VOID_LIBC_DEST(FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, dest_libccc, c_##FUNCTION, dest_libccc, ##__VA_ARGS__) \
	TEST_PERFORM_VOID_(expect, dest_libc,       FUNCTION, dest_libc,   ##__VA_ARGS__) \



/*!
**	This macro performs a test (with segfault handling and execution timer) for the given function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	TYPE		The type of the result variable
**	@param	KIND		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	FUNCTION	The name of the function to test
**	@param	...			Variadic arguments are passed to FUNCTION
*/
#define TEST_PERFORM_(KIND, FUNCTION, ...) \
	_TRY \
	{ \
		timer_clock(&test.timer.KIND##_start); \
		test.KIND = FUNCTION(__VA_ARGS__); \
		timer_clock(&test.timer.KIND##_end); \
	} \
	_CATCH \
	{ \
		test.KIND##_sig = sig; \
	} \
	_END \

//! Use this for (any_type)-return functions
#define TEST_PERFORM(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, ##__VA_ARGS__) \
	test.expect = expecting; \

//! Use this for (any_type)-return functions, which use a 'dest' argument
#define TEST_PERFORM_DEST(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, dest_libccc, ##__VA_ARGS__) \
	test.expect = expecting; \

//! Use this for (any_type)-return functions that exist in libc
#define TEST_PERFORM_LIBC(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, ##__VA_ARGS__) \
	TEST_PERFORM_(expect,     FUNCTION, ##__VA_ARGS__) \

//! Use this for (any_type)-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_LIBC_DEST(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, dest_libccc, ##__VA_ARGS__) \
	TEST_PERFORM_(expect,     FUNCTION, dest_libc,   ##__VA_ARGS__) \

//! Use this for (any_type)-return functions, which are math library functions
#define TEST_PERFORM_LIBC_MATH(TYPENAME, FUNCTION, SUFFIX, ...) \
	TEST_PERFORM_(result, c_##TYPENAME##FUNCTION,         ##__VA_ARGS__) \
	TEST_PERFORM_(expect,               FUNCTION##SUFFIX, ##__VA_ARGS__) \



/*
//! Prints the given argument variable as a string with non-printable chars as escape sequences
#define TEST_PRINT_ARGS_ESCAPED(ARG) \
	char* tmp = strtoescape(ARG); \
	TEST_PRINT_ARGS("\"%s\"", tmp); \
	if (tmp) \
	{ \
		free(tmp); \
		tmp = NULL; \
	} \
*/

/*!
**	This macro will prepare the test result struct, so as to print the test result output
*/
#define TEST_PRINT_(FORMAT, ...) \
	len = snprintf(NULL, (0), FORMAT, ##__VA_ARGS__); \
	if (len < 0)		return; \
	args = (char*)malloc((size_t)len + sizeof("")); \
	if (args == NULL)	return; \
	len = snprintf((args), len + 1, FORMAT, ##__VA_ARGS__); \
	if (len < 0)		return; \



//! Prints the test result for a "expect test" (one which does not have an equivalent function in the C standard library)
#define TEST_PRINT(TYPENAME, FUNCTION, FORMAT, ...) \
	print_timer_result(&test.timer, FALSE); \
	TEST_PRINT_(FORMAT, ##__VA_ARGS__) \
	test.function = "_"#FUNCTION; \
	print_test_##TYPENAME(&test, args); \
	if (args)	free(args); \
	args = NULL; \

//! Prints the test result for a "compare test" (one which has an equivalent function in the C standard library)
#define TEST_PRINT_LIBC(TYPENAME, FUNCTION, FORMAT, ...) \
	print_timer_result(&test.timer, TRUE); \
	TEST_PRINT_(FORMAT, ##__VA_ARGS__) \
	test.function = #FUNCTION; \
	print_test_##TYPENAME(&test, args); \
	if (args)	free(args); \
	args = NULL; \






/*!
**	This macro frees the result variable for a test, if it is appropriate to do so
**	@param	KIND	The name of the result variable to freed
*/
#define TEST_FREE_(KIND) \
	if (test.KIND && \
		test.KIND##_sig == SIGNAL_NULL) \
	{ \
		free((void*)test.KIND); \
		test.KIND = NULL; \
	} \

//! Frees the 'result_libccc' variable, if appropriate
#define TEST_FREE() \
	TEST_FREE_(result) \

//! Frees the 'result_libccc' and 'result_libc' variables, if appropriate
#define TEST_FREE_LIBC() \
	TEST_FREE_(result) \
	TEST_FREE_(expect) \

//! Frees the 'result_libccc', if appropriate, with a user-supplied function
#define TEST_FREE_RESULT(DELETE_FUNCTION) \
	if (test.result && \
		test.result##_sig == SIGNAL_NULL) \
	{ \
		DELETE_FUNCTION(test.result); \
		test.result = NULL; \
	} \



/* TODO perhaps find a way to macro-ify result printing ? its probably not really necessary...

#define TEST_PRINT_(RESULT_STR, RESULT, EXPECT) \
	print_test_str(test_name, RESULT_STR, RESULT, EXPECT, can_segfault); \



#define TEST_PRINT(RESULT_STR, RESULT) \
	TEST_PRINT_(RESULT_STR, RESULT, expecting) \

#define TEST_PRINT_LIBC(RESULT_STR, PREFIX) \
	TEST_PRINT_(RESULT_STR, PREFIX##_libccc, PREFIX##_libc) \

#define TEST_PRINT_RESULT(RESULT_STR) \
	TEST_PRINT_(RESULT_STR, result_libccc, expecting) \

#define TEST_PRINT_RESULT_LIBC(RESULT_STR) \
	TEST_PRINT_(RESULT_STR, result_libccc, result_libc) \


// lo and behold, what a typical testing function used to look like: very boilerplate!
#define DEFINE_TESTFUNC_LIBC_FREE(FUNCTION, ...) \
{ \
	s_timer t = {0}; \
	char* result_libccc = NULL; \
	char* result_libc  = NULL; \
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libccc = c_##FUNCTION(##__VA_ARGS__); timer_clock(&t.end1); } else result_libccc = segstr; \
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc   =     FUNCTION(##__VA_ARGS__); timer_clock(&t.end2); } else result_libc   = segstr; \
	print_test_str(test_name, #FUNCTION" return", result_libccc, result_libc, can_segfault); \
	if (result_libccc && result_libccc != segstr)	free(result_libccc); \
	if (result_libc   && result_libc  != segstr)	free(result_libc); \
	print_timer_result(&t, TRUE); \
} \
*/

#endif
