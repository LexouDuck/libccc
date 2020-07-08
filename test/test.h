
#ifndef LIBFT_TEST_H
#define LIBFT_TEST_H

/*
** ************************************************************************** *|
**                                   Includes                                 *|
** ************************************************************************** *|
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <setjmp.h>
#include <signal.h>

#include "libft.h"
#include "libft_list.h"
#include "libft_stat.h"



/*
** ************************************************************************** *|
**                                   Defines                                  *|
** ************************************************************************** *|
*/

typedef struct	s_test_flags_
{
	bool	verbose;		// if 0, only display total amount of tests passed/failed
	bool	show_args;		// if 0, do not display arguments for each test
	bool	show_speed;		// if 0, do not display performance/speed for each test
	bool	test_nullptrs;	// if 0, do not perform any NULL pointer tests
	bool	test_overflow;	// if 0, do not perform libft_convert overflowing number tests
}				s_test_flags;

typedef struct	s_test_totals_
{
	int		tests;	// The total amount of tests ran.
	int		failed; // The amount of tests which had an ERROR result.
}				s_test_totals;

typedef struct	s_test_suite_
{
	bool		run;		// If 0, does not run
	char const*	name;		// Name for test suite to identify
	int		(*test)(void);	// Test suite launcher
}				s_test_suite;
#define TEST_SUITE_AMOUNT	12

//Args for main are: help, verbose, arguments, performance, overflow
typedef struct	s_test_arg_
{
	void	(*handle_arg)();
	char		arg;
	char const*	name;
	char const* description;
}				s_test_arg;
#define TEST_ARGS_AMOUNT	7



/*
**	This struct holds all program state data
*/
typedef struct	s_test_
{
	s_test_flags	flags;		// Stores the main program argument options
	s_test_totals	totals;		// Stores the amounts of tests ran/failed
	s_test_suite	suites[TEST_SUITE_AMOUNT];
	s_test_arg		args[TEST_ARGS_AMOUNT];
}				s_test;
// Global variable to access the program state data from anywhere
s_test		g_test;



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
**	This define is used as the 'can_segfault' arg for certain 'int' tests,
**	so as to have those tests expect a "(segfault)" result.
*/
#define SEGV	(TRUE | (1 << 2))



/*
** ************************************************************************** *|
**                              Segfault handling                             *|
** ************************************************************************** *|
*/

extern char*	nullstr;
extern char*	segstr;
int				segfault;
jmp_buf 		restore;

#ifdef __MINGW32__
void	signal_handler(int signaltype);
#else
struct sigaction sig;
void	signal_handler(int signaltype, siginfo_t *info, void *ptr);
#endif



/*
** ************************************************************************** *|
**                           Timer utility functions                          *|
** ************************************************************************** *|
*/

typedef struct timespec s_time;

typedef struct	s_timer_
{
	s_time	start1;
	s_time	start2;
	s_time	end1;
	s_time	end2;
	s_time	time1;
	s_time	time2;
}				s_timer;

void	timer_clock(s_time* t);
s_time	timer_getdiff(s_time start, s_time end);
t_s64	timer_compare(s_time a, s_time b);
void	print_timer_result(s_timer* timer, t_s64 compare);



/*
** ************************************************************************** *|
**                              Testing Functions                             *|
** ************************************************************************** *|
*/

/*
**	Test suite functions
*/
int		test_memory(void);
int		test_char(void);
int		test_string(void);
int		test_stringarray(void);
int		test_convert(void);
int		test_color(void);
int		tess_list(void);
int		test_math(void);
int		test_stat(void);
int		test_random(void);
int		test_vlq(void);
int		test_io(void);

/*
**	Global variables used in tests
*/
extern char const* test1; extern t_size const test1_len;
extern char const* test2; extern t_size const test2_len;
extern char const* test3; extern t_size const test3_len;



/*
** ************************************************************************** *|
**                              Utility Functions                             *|
** ************************************************************************** *|
*/

void	print_error(char const * format_error, ...);
void	print_percent(double percent);
void	print_totals(s_test_totals totals, char const * category);
void	print_usage(char const * program_name);
void	print_suite_title(char const * suite_name);
void	print_title(void);
void	print_endian_warning(void);
void	print_nonstd(void);

s_sortedlist_int	print_test_random(int samples);



int		bool_equals(int a, int b);

int		str_equals(char const* str1, char const* str2);

int		ptrarr_equals(void const** ptr1, void const** ptr2);

int		strarr_equals(char const** strarr1, char const** strarr2);

char	*print_memory(void const* ptr, t_size length);

char	*str_padleft(char const* str, char c, t_size length);

char*	str_to_escape(char const* str);



void	print_test_s8(char const *test_name, char const *function, t_s8 result, t_s8 expect, int can_segfault);
void	print_test_s16(char const *test_name, char const *function, t_s16 result, t_s16 expect, int can_segfault);
void	print_test_s32(char const *test_name, char const *function, t_s32 result, t_s32 expect, int can_segfault);
void	print_test_s64(char const *test_name, char const *function, t_s64 result, t_s64 expect, int can_segfault);

void	print_test_u8(char const *test_name, char const *function, t_u8 result, t_u8 expect, int can_segfault);
void	print_test_u16(char const *test_name, char const *function, t_u16 result, t_u16 expect, int can_segfault);
void	print_test_u32(char const *test_name, char const *function, t_u32 result, t_u32 expect, int can_segfault);
void	print_test_u64(char const *test_name, char const *function, t_u64 result, t_u64 expect, int can_segfault);

void	print_test_f32(char const *test_name, char const *function, t_f32 result, t_f32 expect, int can_segfault);
void	print_test_f64(char const *test_name, char const *function, t_f64 result, t_f64 expect, int can_segfault);

void	print_test_size(char const *test_name, char const *function, t_size result, t_size expect, int can_segfault);
void	print_test_bool(char const *test_name, char const *function, t_bool result, t_bool expect, int can_segfault);

void	print_test_sign(char const *test_name, char const *function, t_s64 result, t_s64 expect, int can_segfault);

void	print_test_str(char const *test_name, char const *function, char const *result, char const *expect, int can_segfault);
void	print_test_mem(char const *test_name, char const *function, void const *result, void const *expect, t_size length, int can_segfault);

void	print_test_alloc(char const *test_name, char const *function, char const *result, t_size length);

void	print_test_strarr(char const *test_name, char const *function, char const **result, char const **expect, int can_segfault);

void	print_test_lst(char const *test_name, char const *function, s_list const *result, char const *expect[], int can_segfault);



/*
** ************************************************************************** *|
**                               Testing Macros                               *|
** ************************************************************************** *|
*/

/*
**	The following macros are used for tests, to avoid boilerplate and code repetition.
*/

// Use this for void-return functions
#define TEST_PERFORM(RESULT, FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM(1, RESULT, ft_##FUNCTION, ##__VA_ARGS__) \

// Use this for void-return functions, which use a 'dest' argument
#define TEST_PERFORM_DEST(FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM(1, dest_libft, ft_##FUNCTION, dest_libft, ##__VA_ARGS__) \

// Use this for void-return functions that exist in libc
#define TEST_PERFORM_LIBC(PREFIX, FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM(1, PREFIX##_libft, ft_##FUNCTION, ##__VA_ARGS__) \
	_TEST_PERFORM(2, PREFIX##_libc,       FUNCTION, ##__VA_ARGS__) \

// Use this for void-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_LIBC_DEST(FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM(1, dest_libft, ft_##FUNCTION, dest_libft, ##__VA_ARGS__) \
	_TEST_PERFORM(2, dest_libc,       FUNCTION, dest_libc,  ##__VA_ARGS__) \


// Use this for string-return functions
#define TEST_PERFORM_RESULT(FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT_STR(1, libft, ft_##FUNCTION, ##__VA_ARGS__) \

// Use this for string-return functions, which use a 'dest' argument
#define TEST_PERFORM_RESULT_DEST(FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT_STR(1, libft, ft_##FUNCTION, dest_libft, ##__VA_ARGS__) \

// Use this for string-return functions that exist in libc
#define TEST_PERFORM_RESULT_LIBC(FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT_STR(1, libft, ft_##FUNCTION, ##__VA_ARGS__) \
	_TEST_PERFORM_RESULT_STR(2, libc,       FUNCTION, ##__VA_ARGS__) \

// Use this for string-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_RESULT_LIBC_DEST(FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT_STR(1, libft, ft_##FUNCTION, dest_libft, ##__VA_ARGS__) \
	_TEST_PERFORM_RESULT_STR(2, libc,       FUNCTION, dest_libc,  ##__VA_ARGS__) \


// Use this for (any_type)-return functions
#define TEST_PERFORM_RESULT_TYPE(TYPE, FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT(1, TYPE, libft, ft_##FUNCTION, ##__VA_ARGS__) \

// Use this for (any_type)-return functions, which use a 'dest' argument
#define TEST_PERFORM_RESULT_TYPE_DEST(TYPE, FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT(1, TYPE, libft, ft_##FUNCTION, dest_libft, ##__VA_ARGS__) \

// Use this for (any_type)-return functions that exist in libc
#define TEST_PERFORM_RESULT_TYPE_LIBC(TYPE, FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT(1, TYPE, libft, ft_##FUNCTION, ##__VA_ARGS__) \
	_TEST_PERFORM_RESULT(2, TYPE, libc,       FUNCTION, ##__VA_ARGS__) \

// Use this for (any_type)-return functions that exist in libc, which use a 'dest' argument
#define TEST_PERFORM_RESULT_TYPE_LIBC_DEST(TYPE, FUNCTION, ...) \
	_TEST_INIT() \
	_TEST_PERFORM_RESULT(1, TYPE, libft, ft_##FUNCTION, dest_libft, ##__VA_ARGS__) \
	_TEST_PERFORM_RESULT(2, TYPE, libc,       FUNCTION, dest_libc,  ##__VA_ARGS__) \



// Prints the given format string + values (if global flags demand so)
#define TEST_PRINT_ARGS(FORMAT, ...) \
	if (g_test.flags.verbose && g_test.flags.show_args) \
	{ \
		printf(" -> ("); \
		printf(FORMAT, ##__VA_ARGS__); \
		printf(")"); \
	} \

// Prints the given argument variable as a string with non-printable chars as escape sequences
#define TEST_PRINT_ARGS_ESCAPED(ARG) \
	char* tmp = str_to_escape(ARG); \
	TEST_PRINT_ARGS("%s", tmp); \
	if (tmp) \
	{ \
		free(tmp); \
		tmp = NULL; \
	} \



// Frees the 'result_libft' variable, if appropriate
#define TEST_FREE() \
	_TEST_FREE(libft) \

// Frees the 'result_libft' and 'result_libc' variables, if appropriate
#define TEST_FREE_LIBC() \
	_TEST_FREE(libft) \
	_TEST_FREE(libc) \

// Frees the 'result_libft', if appropriate, when that result is a nested allocation of rank 2 (ie, a char**/string array)
#define TEST_FREE_ARRAY_NULLTERM() \
	_TEST_FREE_ARRAY_NULLTERM(libft) \


/*
**	_PRIVATE MACROS
**	These are the core macro functions which are uses by all the macros above
*/

/*
**	This macro performs a test (with segfault handling and execution timer) for the given void-returning function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	CALL		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	RESULT		The name of the result variable to assign to (if segfault occurs)
**	@param	FUNCTION	The name of the function to test
**	@params				Variadic arguments are passed to FUNCTION
*/
#define _TEST_PERFORM(CALL, RESULT, FUNCTION, ...) \
	_TRY \
	{ \
		timer_clock(&t.start##CALL); \
		FUNCTION(__VA_ARGS__); \
		timer_clock(&t.end##CALL); \
	} \
	_CATCH \
	{ \
		RESULT = segstr; \
	} \
	_END

/*
**	This macro performs a test (with segfault handling and execution timer) for the given string-returning function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	CALL		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	LIB			The name of the result variable to assign to (token-pasted as 'result_##LIB')
**	@param	FUNCTION	The name of the function to test
**	@params				Variadic arguments are passed to FUNCTION
*/
#define _TEST_PERFORM_RESULT_STR(CALL, LIB, FUNCTION, ...) \
	char* result_##LIB = NULL; \
	_TRY \
	{ \
		timer_clock(&t.start##CALL); \
		result_##LIB = FUNCTION(__VA_ARGS__); \
		timer_clock(&t.end##CALL); \
	} \
	_CATCH \
	{ \
		result_##LIB = segstr; \
	} \
	_END

/*
**	This macro performs a test (with segfault handling and execution timer) for the given function.
**	Expects a 's_timer t' variable to be accessible and initialized.
**	@param	CALL		The number of this call (1 or 2), token-pasted to the timer 'start_' and 'end_' fields.
**	@param	TYPE		The type of the result variable
**	@param	LIB			The name of the result variable to assign to (token-pasted as 'result_##LIB')
**	@param	FUNCTION	The name of the function to test
**	@params				Variadic arguments are passed to FUNCTION
*/
#define _TEST_PERFORM_RESULT(CALL, TYPE, LIB, FUNCTION, ...) \
	TYPE result_##LIB; \
	_TRY \
	{ \
		timer_clock(&t.start##CALL); \
		result_##LIB = FUNCTION(__VA_ARGS__); \
		timer_clock(&t.end##CALL); \
	} \
	_CATCH \
	{ \
		can_segfault |= (1 << CALL); \
	} \
	_END

/*
**	Initialization logic for any test
*/
#define _TEST_INIT() \
	if (can_segfault && !g_test.flags.test_nullptrs) return; \
	s_timer t = {0}; \

/*
**	This macro frees the result variable for a test, if it is appropriate to do so
**	@param	LIB			The name of the result variable to freed (token-pasted as 'result_##LIB')
*/
#define _TEST_FREE(LIB) \
	if (result_##LIB && result_##LIB != segstr) \
	{ \
		free(result_##LIB); \
		result_##LIB = NULL; \
	} \

/*
**	This macro frees the result variable for a test, if it is appropriate to do so,
**	knowing this is an array of sub-results which should also be freed, and that
**	this array is a null-terminated pointer array.
**	@param	LIB			The name of the array result variable to freed (token-pasted as 'result_##LIB')
*/
#define _TEST_FREE_ARRAY_NULLTERM(LIB) \
	if (result_##LIB && *result_##LIB != segstr) \
	{ \
		for (int i = 0; result_##LIB[i]; ++i) \
		{ \
			free(result_##LIB[i]); \
			result_##LIB[i] = NULL; \
		} \
		free(result_##LIB); \
		result_##LIB = NULL; \
	} \


/*
**	These macros are used to have signal handling/checking during tests which can crash the program
*/

#define _TRY \
	segfault = setjmp(restore); \
	if (!segfault) \

#define _CATCH \
	else \

#ifdef __MINGW32__
#define _END \
	if (segfault) \
		signal(SIGSEGV,	signal_handler); \

#else
#define _END	;

#endif


/* TODO perhaps find a way to macro-ify result printing ? its probably not really necessary...

#define _TEST_PRINT(RESULT_STR, RESULT, EXPECT) \
	print_test_str(test_name, RESULT_STR, RESULT, EXPECT, can_segfault); \



#define TEST_PRINT(RESULT_STR, RESULT) \
	_TEST_PRINT(RESULT_STR, RESULT, expecting) \

#define TEST_PRINT_LIBC(RESULT_STR, PREFIX) \
	_TEST_PRINT(RESULT_STR, PREFIX##_libft, PREFIX##_libc) \

#define TEST_PRINT_RESULT(RESULT_STR) \
	_TEST_PRINT(RESULT_STR, result_libft, expecting) \

#define TEST_PRINT_RESULT_LIBC(RESULT_STR) \
	_TEST_PRINT(RESULT_STR, result_libft, result_libc) \


// lo and behold, what a typical testing function used to look like: very boilerplate!
#define DEFINE_TESTFUNC_LIBC_FREE(FUNCTION, ...) \
{ \
	s_timer t = {0}; \
	char* result_libft = NULL; \
	char* result_libc  = NULL; \
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start1); result_libft = ft_##FUNCTION(##__VA_ARGS__); timer_clock(&t.end1); } else result_libft = segstr; \
	segfault = setjmp(restore); if (!segfault) { timer_clock(&t.start2); result_libc  =      FUNCTION(##__VA_ARGS__); timer_clock(&t.end2); } else result_libc  = segstr; \
	print_test_str(test_name, #FUNCTION" return", result_libft, result_libc, can_segfault); \
	if (result_libft && result_libft != segstr) free(result_libft); \
	if (result_libc  && result_libc  != segstr) free(result_libc); \
	print_timer_result(&t, TRUE); \
} \
*/

#endif
