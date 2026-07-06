
#ifndef LIBCCC_TEST_H
#define LIBCCC_TEST_H

/*!@file test.h
**
**	How to create a testing function for a libccc function:
**	```c
**	void    print_test_<func>(char const* test_name, t_testflags flags,
**	        <args>)
**	{
**	    TEST_INIT(<test_type>)
**	    TEST_PERFORM_<test_kind>(<func>, <args>)
**	    TEST_PRINT(<test_type>, <func>, <printf_format_for_args>, <args>)
**	    TEST_FREE()
**	}
**	```
**	- `<func>`: name of the function (in C-like lowercase namingstyle, so that the preprocessor can check if the function is `#define`d or not, and run the test accordingly)
**	- `<args>`: the arguments that the function takes
**	- `<test_type>`: the suffix part of the testing result-check function to use (for the list of available testing functions, see `libccc/test/test-utils.h`, lines ~100 to ~200)
**	- `<test_kind>`: this suffix part of the `TEST_PERFORM_*()` macro function indicates if there exists an approriate counterpart function in the stdlibc, or if the expected test result is manually written for each test
**
**	How to create a test suite function for a libccc function:	
**	```c
**	void    test_<func>(void)
**	{
**	//  | TEST FUNCTION  | TEST NAME             | CAN SEGFAULT     | TEST ARGS
**	    print_test_<func>("<func> (<argdetails>)",<expects_segfault>, <test_args>)
**	}
**	```
**	- `<argdetails>`: short string which tells how this test in particular is special
**	- `<expects_segfault>`: whether or not this test passes or fails if the function segfaults
**	- `<printf_format_for_args>`: format string to show arguments given for this test, for the `libccc-test -a` flag
**	- `<test_args>`: the actual hardcoded literal values to give as arguments for this test
*/

/*============================================================================*\
||                                   Includes                                 ||
\*============================================================================*/
#if (!defined(_WIN32) || defined(__MINGW32__))
#include <strings.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/text/char/ascii.h"
#include "libccc/text/char/unicode.h"
#include "libccc/sys/time.h"
#include "libccc/math/stat.h"
typedef struct array_int	s_array_int;	//!< @see "libccc/generic/array.h"
typedef struct  list_int	s_list_int;	//!< @see "libccc/generic/list.h"

#include "test_catch.h"
#include "test_timer.h"
#include "test_print.h"
#include "test_utils.h"



/*============================================================================*\
||                                   Defines                                  ||
\*============================================================================*/

//! The total amount of test suites for libccc
#define TEST_SUITE_AMOUNT	48



//! This type stores info about a program argument (ie: `argc`/`argv`)
typedef struct test_arg
{
	void	(*handle_arg)();  //!< The function to execute for this program argument
	char		arg;          //!< The "character version" of this argument (ie: `-a`)
	char const*	name;         //!< The "string version" of this argument (ie: `--arg`)
	char const* description;  //!< The description for this argument (displayed when doing `--help`)
}	s_test_arg;
//! The amount of different arguments accepted by the test suite
#define TEST_ARGS_AMOUNT	10

//! This struct stores the program argument boolean flags
typedef struct test_flags
{
	bool	verbose;        //!< if `TRUE`, display all logger output for each test
	bool	show_args;      //!< if `TRUE`, display arguments given to each test
	bool	show_speed;     //!< if `TRUE`, display performance (execution speed) for each test
	bool	show_result;    //!< if `TRUE`, display result, even when test passed
	bool	show_errors;    //!< if `TRUE`, display any errors output by libccc during function execution
	bool	show_escaped;   //!< if `TRUE`, display strings with non-printable characters as escape sequences
	bool	test_nullptrs;  //!< if `TRUE`, perform all NULL pointer tests
	bool	test_overflow;  //!< if `TRUE`, perform all the libccc_convert overflowing number tests
}	s_test_config;



//! This struct stores the total amount of tests failed/passed
typedef struct test_totals
{
	int	tests;     //!< The total amount of tests ran.
	int	failed;    //!< The total amount of tests which had an ERROR result.
	int	warnings;  //!< The total amount of warnings issued by the test suite.
}	s_test_totals;

//! This struct stores one test suite (typically, one header file)
typedef struct test_suite
{
	bool		run;		//!< If 0, does not run
	char const*	name;		//!< Name for test suite to identify
	int		(*test)(void);	//!< Test suite launcher
	s_test_totals	totals;	//!< Stores the total amounts of tests ran/failed
}	s_test_suite;



typedef enum test_suite_libccc
{
	#undef ENUM
	#define ENUM(_name_, _func_, _enum_, ...) \
	_enum_,
	#include "test_suites.enum"
	#undef ENUM
}	e_test_suite_libccc;



//! This struct holds all program state data
typedef struct program
{
	e_test_suite_libccc current_suite;			//!< Index of the currently running test suite
	bool			last_test_failed;			//!< Is `TRUE` if the latest test performed had an error.
	bool			last_test_warned;			//!< Is `TRUE` if the latest test performed issued a warning.
	char*			last_test_error;			//!< Contains any error output by libccc during the latest test
	s_test_config	config;						//!< Stores the main program argument options (as boolean flags)
	s_test_arg		args[TEST_ARGS_AMOUNT];		//!< Stores the chars/names and descriptions for each valid program argument
	s_test_suite	suites[TEST_SUITE_AMOUNT];	//!< Stores info of which test suites should be run or not
}	s_program;

//! Global variable to access the program state data from anywhere
extern s_program	g_test;



/*============================================================================*\
||                              Testing Functions                             ||
\*============================================================================*/



//! Initializes variables to prepare to run test suites
void	test_init(void);

/*
**	Test suite functions
*/
#undef ENUM
#define ENUM(_name_, _func_, _enum_, ...) \
int	_func_(void);
#include "test_suites.enum"
#undef ENUM



int	print_results(s_test_suite const* suites);



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

DEFINEFUNC_PRINT_TEST(u8,		t_u8)
DEFINEFUNC_PRINT_TEST(u16,		t_u16)
DEFINEFUNC_PRINT_TEST(u32,		t_u32)
DEFINEFUNC_PRINT_TEST(u64,		t_u64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_PRINT_TEST(u128,		t_u128)
#endif
DEFINEFUNC_PRINT_TEST(uint,		t_uint)

DEFINEFUNC_PRINT_TEST(s8,		t_s8)
DEFINEFUNC_PRINT_TEST(s16,		t_s16)
DEFINEFUNC_PRINT_TEST(s32,		t_s32)
DEFINEFUNC_PRINT_TEST(s64,		t_s64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_PRINT_TEST(s128,		t_s128)
#endif
DEFINEFUNC_PRINT_TEST(sint,		t_sint)

DEFINEFUNC_PRINT_TEST(q8,		t_q8)
DEFINEFUNC_PRINT_TEST(q16,		t_q16)
DEFINEFUNC_PRINT_TEST(q32,		t_q32)
DEFINEFUNC_PRINT_TEST(q64,		t_q64)
#if LIBCONFIG_USE_INT128
DEFINEFUNC_PRINT_TEST(q128,		t_q128)
#endif
DEFINEFUNC_PRINT_TEST(fixed,	t_fixed)

#if LIBCONFIG_USE_FLOAT16
DEFINEFUNC_PRINT_TEST(f16,		t_f16)
#endif
DEFINEFUNC_PRINT_TEST(f32,		t_f32)

DEFINEFUNC_PRINT_TEST(f64,		t_f64)
#if LIBCONFIG_USE_FLOAT80
DEFINEFUNC_PRINT_TEST(f80,		t_f80)
#endif
#if LIBCONFIG_USE_FLOAT128
DEFINEFUNC_PRINT_TEST(f128,		t_f128)
#endif
DEFINEFUNC_PRINT_TEST(float,	t_float)

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

//! Use this for (any_type)-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_LIBC_MATH_DEST(TYPENAME, FUNCTION, SUFFIX, ...) \
	TEST_PERFORM_(result, c_##TYPENAME##FUNCTION,         ##__VA_ARGS__, dest_libccc ) \
	TEST_PERFORM_(expect,               FUNCTION##SUFFIX, ##__VA_ARGS__, dest_libc   ) \



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
