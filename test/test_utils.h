
#ifndef LIBCCCTEST_UTILS_H_
#define LIBCCCTEST_UTILS_H_

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <stdbool.h>
#ifndef bool
#define bool	_Bool
#endif

#include "libccc.h"
#include "libccc/char.h"
#include "libccc/monad/list.h"
#include "libccc/math/stat.h"
#include "libccc/sys/time.h"

#include "test_catch.h"
#include "test_timer.h"



/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

/*
**	Output color string codes for tty terminal/shell.
*/
#ifndef __COLORS__
#define __COLORS__
#define C_RED		"\x1b[31m"
#define C_GREEN		"\x1b[32m"
#define C_YELLOW	"\x1b[33m"
#define C_BLUE		"\x1b[34m"
#define C_MAGENTA	"\x1b[35m"
#define C_CYAN		"\x1b[36m"
#define C_RESET		"\x1b[0m"
#endif



/*
** ************************************************************************** *|
**                              Utility Functions                             *|
** ************************************************************************** *|
*/

void	print_error(char const* format_error, ...);
void	print_percent(double percent);
void	print_totals(int amount, int failed, char const* category);
void	print_usage(char const* program_name);
void	print_suite_title(char const* suite_name);
void	print_title(void);
void	print_endian_warning(void);
void	print_nonstd(void);

s_sortedlist_int	print_test_random(int samples);



int		bool_equals(int a, int b);

int		str_equals(char const* str1, char const* str2);

int		ptrarr_equals(void const** ptr1, void const** ptr2);

int		strarr_equals(char const** strarr1, char const** strarr2);

int		str_equals_until(char const* str1, char const* str2, char c);


char*	print_memory(void const* ptr, t_size length);

char*	str_padleft(char const* str, char c, t_size length);

#define STRING_ESCAPE_THRESHOLD	128
char*	strtoescape(char const* str);

char*	int_stostr(t_s64 number);

char*	int_utostr(t_u64 number);

char*	ptrtostr(void const* ptr);



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

#define DEFINEFUNC_PRINT_TEST(NAME, TYPE) \
typedef struct test_##NAME	\
{							\
	char const*	name;		/*!< the name of this unit test */\
	char const*	function;	/*!< the name of the function tested */\
	bool		can_sig;	/*!< if TRUE, this test may cause a program-ending error */\
	TYPE		result;		/*!< the result of the tested function */\
	e_signal	result_sig;	/*!< the signal emitted by the tested function, if any */\
	TYPE		expect;		/*!< the result which is expected to pass this test */\
	e_signal	expect_sig;	/*!< the signal emitted by the expect function, if any */\
	size_t		length;		/*!< used by certain types, notably 'mem'(void*) and 'list'(s_list*) */\
	s_timer		timer;		/*!< the execution performance timer for this test */\
}			s_test_##NAME;	\
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
#ifdef __int128
DEFINEFUNC_PRINT_TEST(s128,		t_s128)
#endif

DEFINEFUNC_PRINT_TEST(uint,		t_uint)
DEFINEFUNC_PRINT_TEST(u8,		t_u8)
DEFINEFUNC_PRINT_TEST(u16,		t_u16)
DEFINEFUNC_PRINT_TEST(u32,		t_u32)
DEFINEFUNC_PRINT_TEST(u64,		t_u64)
#ifdef __int128
DEFINEFUNC_PRINT_TEST(u128,		t_u128)
#endif

DEFINEFUNC_PRINT_TEST(fixed,	t_fixed)
DEFINEFUNC_PRINT_TEST(q16,		t_q16)
DEFINEFUNC_PRINT_TEST(q32,		t_q32)
DEFINEFUNC_PRINT_TEST(q64,		t_q64)
#ifdef __int128
DEFINEFUNC_PRINT_TEST(q128,		t_q128)
#endif

DEFINEFUNC_PRINT_TEST(float,	t_float)
DEFINEFUNC_PRINT_TEST(f32,		t_f32)
DEFINEFUNC_PRINT_TEST(f64,		t_f64)
#ifdef __float80
DEFINEFUNC_PRINT_TEST(f80,		t_f80)
#endif
#ifdef __float128
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
DEFINEFUNC_PRINT_TEST(ptrarr,	void const**)
DEFINEFUNC_PRINT_TEST(str,		char const*)
DEFINEFUNC_PRINT_TEST(strarr,	char const**)

DEFINEFUNC_PRINT_TEST(list,		s_list const*)

DEFINEFUNC_PRINT_TEST(date,		s_date)

DEFINEFUNC_PRINT_TEST(sign,		t_s64)
DEFINEFUNC_PRINT_TEST(alloc,	char const*)


/*
** ************************************************************************** *|
**                               Testing Macros                               *|
** ************************************************************************** *|
*/

/*
**	The following macros are used for tests, to avoid boilerplate and code repetition.
*/

/*!
**	Initialization logic for any test
*/
#define TEST_INIT(TYPENAME) \
	char*	args = NULL;							\
	char*	tmp = NULL;								\
	size_t	len = 0;								\
	s_test_##TYPENAME test = (s_test_##TYPENAME)	\
	{												\
		.name = test_name,							\
		.can_sig = can_segfault,					\
	};												\
	if (can_segfault && !g_test.flags.test_nullptrs)\
		return;										\



/*!
**	This macro performs a test (with segfault handling and execution timer) for the given void-returning function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	KIND		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	RESULT		The name of the result variable to assign to (if segfault occurs)
**	@param	FUNCTION	The name of the function to test
**	@param	...			Variadic arguments are passed to FUNCTION
*/
#define TEST_PERFORM_VOID_(KIND, RESULT, FUNCTION, ...) \
	_TRY										\
	{											\
		timer_clock(&test.timer.KIND##_start);	\
		FUNCTION(__VA_ARGS__);					\
		test.KIND = RESULT;						\
		timer_clock(&test.timer.KIND##_end);	\
	}											\
	_CATCH										\
	{											\
		test.KIND##_sig = sig;					\
	}											\
	_END										\

//! Use this for void-return functions
#define TEST_PERFORM_VOID(RESULT, FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, RESULT, c_##FUNCTION, ##__VA_ARGS__)	\
	test.expect = expecting;										\

//! Use this for void-return functions that exist in libc
#define TEST_PERFORM_VOID_LIBC(RESULT, FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, RESULT, c_##FUNCTION, ##__VA_ARGS__)	\
	TEST_PERFORM_VOID_(expect, RESULT,     FUNCTION, ##__VA_ARGS__)	\

//! Use this for void-return functions, which use a 'dest' argument
#define TEST_PERFORM_VOID_DEST(FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, dest_libccc, c_##FUNCTION, dest_libccc, ##__VA_ARGS__)	\
	test.expect = expecting;															\

//! Use this for void-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_VOID_LIBC_DEST(FUNCTION, ...) \
	TEST_PERFORM_VOID_(result, dest_libccc, c_##FUNCTION, dest_libccc, ##__VA_ARGS__)	\
	TEST_PERFORM_VOID_(expect, dest_libc,       FUNCTION, dest_libc,   ##__VA_ARGS__)	\



/*!
**	This macro performs a test (with segfault handling and execution timer) for the given function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	TYPE		The type of the result variable
**	@param	KIND		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	FUNCTION	The name of the function to test
**	@param	...			Variadic arguments are passed to FUNCTION
*/
#define TEST_PERFORM_(KIND, FUNCTION, ...) \
	_TRY										\
	{											\
		timer_clock(&test.timer.KIND##_start);	\
		test.KIND = FUNCTION(__VA_ARGS__);		\
		timer_clock(&test.timer.KIND##_end);	\
	}											\
	_CATCH										\
	{											\
		test.KIND##_sig = sig;					\
	}											\
	_END										\

//! Use this for (any_type)-return functions
#define TEST_PERFORM(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, ##__VA_ARGS__)	\
	test.expect = expecting;							\

//! Use this for (any_type)-return functions that exist in libc
#define TEST_PERFORM_LIBC(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, ##__VA_ARGS__)	\
	TEST_PERFORM_(expect,     FUNCTION, ##__VA_ARGS__)	\

//! Use this for (any_type)-return functions, which use a 'dest' argument
#define TEST_PERFORM_DEST(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, dest_libccc, ##__VA_ARGS__)	\
	test.expect = expecting;										\

//! Use this for (any_type)-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_LIBC_DEST(FUNCTION, ...) \
	TEST_PERFORM_(result, c_##FUNCTION, dest_libccc, ##__VA_ARGS__)	\
	TEST_PERFORM_(expect,     FUNCTION, dest_libc,   ##__VA_ARGS__)	\



/*
//! Prints the given argument variable as a string with non-printable chars as escape sequences
#define TEST_PRINT_ARGS_ESCAPED(ARG) \
	char* tmp = strtoescape(ARG);	\
	TEST_PRINT_ARGS("\"%s\"", tmp);	\
	if (tmp)						\
	{								\
		free(tmp);					\
		tmp = NULL;					\
	}								\
*/

/*!
**	This macro will prepare the test result struct, so as to print the test result output
*/
#define TEST_PRINT_(FORMAT, ...) \
	len = snprintf(NULL, (0), FORMAT, ##__VA_ARGS__);		\
	if (len < 0)		return;								\
	args = (char*)malloc((size_t)len + sizeof(""));			\
	if (args == NULL)	return;								\
	len = snprintf((args), len + 1, FORMAT, ##__VA_ARGS__);	\
	if (len < 0)		return;								\



//! Prints the test result for a "expect test" (one which does not have an equivalent function in the C standard library)
#define TEST_PRINT(TYPENAME, FUNCTION, FORMAT, ...) \
	print_timer_result(&test.timer, FALSE);	\
	TEST_PRINT_(FORMAT, ##__VA_ARGS__)		\
	test.function = "_"#FUNCTION;			\
	print_test_##TYPENAME(&test, args);		\
	free(args);								\
	args = NULL;							\

//! Prints the test result for a "compare test" (one which has an equivalent function in the C standard library)
#define TEST_PRINT_LIBC(TYPENAME, FUNCTION, FORMAT, ...) \
	print_timer_result(&test.timer, TRUE);	\
	TEST_PRINT_(FORMAT, ##__VA_ARGS__)		\
	test.function = #FUNCTION;				\
	print_test_##TYPENAME(&test, args);		\
	free(args);								\
	args = NULL;							\






/*!
**	This macro frees the result variable for a test, if it is appropriate to do so
**	@param	KIND	The name of the result variable to freed
*/
#define TEST_FREE_(KIND) \
	if (test.KIND &&					\
		test.KIND##_sig == SIGNAL_NULL)	\
	{									\
		free((void*)test.KIND);			\
		test.KIND = NULL;				\
	}									\

/*!
**	This macro frees the result variable for a test, if it is appropriate to do so,
**	knowing this is an array of sub-results which should also be freed, and that
**	this array is a null-terminated pointer array.
**	@param	KIND	The name of the array result variable to freed
*/
#define TEST_FREE_ARRAY_NULLTERM_(KIND) \
	if (test.KIND &&						\
		test.KIND##_sig == SIGNAL_NULL)		\
	{										\
		for (int i = 0; test.KIND[i]; ++i)	\
		{									\
			free((void*)test.KIND[i]);		\
			test.KIND[i] = NULL;			\
		}									\
		free((void*)test.KIND);				\
		test.KIND = NULL;					\
	}										\

//! Frees the 'result_libccc' variable, if appropriate
#define TEST_FREE() \
	TEST_FREE_(result)	\

//! Frees the 'result_libccc' and 'result_libc' variables, if appropriate
#define TEST_FREE_LIBC() \
	TEST_FREE_(result)	\
	TEST_FREE_(expect)	\

//! Frees the 'result_libccc', if appropriate, when that result is a nested allocation of rank 2 (ie, a char**/string array)
#define TEST_FREE_ARRAY_NULLTERM() \
	TEST_FREE_ARRAY_NULLTERM_(result)	\



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
